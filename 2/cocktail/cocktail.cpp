#include "cocktail.h"

Cocktail::Cocktail() : name(), alcoholPercentage(0), volume(0) {}

Cocktail::Cocktail(string &n, int alcohol, int vol) : name(n), alcoholPercentage(alcohol), volume(vol) {}

Cocktail::Cocktail(int vol) : name("Water"), alcoholPercentage(0), volume(vol) {}

Cocktail Cocktail::operator+(const Cocktail &other) {
    // TODO: Delete cocktails
    string newName = name + " + " + other.name;
    int totalVolume = volume + other.volume;
    int newAlcoholPercentage = (alcoholPercentage * volume + other.alcoholPercentage * other.volume) / totalVolume;
    return Cocktail(newName, newAlcoholPercentage, totalVolume);
}

Cocktail &Cocktail::operator>>(Cocktail &other) {
    int transferVolume;
    if (volume >= 100) {
        transferVolume = 100;
    } else {
        transferVolume = volume;
    }
    volume -= transferVolume;
    other.volume += transferVolume;
    other.alcoholPercentage = (other.alcoholPercentage * other.volume + alcoholPercentage * transferVolume) /
                              (other.volume + transferVolume);
    return *this;
}

Cocktail Cocktail::operator*(int &multiplier) {
    volume *= multiplier;
    return *this;
}

ostream &operator<<(ostream &out, const Cocktail &cocktail) {
    out << "Cocktail: " << cocktail.name << " | Alcohol: " << cocktail.alcoholPercentage << "%" << " | Volume: "
        << cocktail.volume << "ml";
    return out;
}

istream &operator>>(istream &in, Cocktail &cocktail) {
    std::string n;
    int alcohol = 0;
    int volume = 0;
    while (!getInput(n, PROMPT_NAME));
    while (!getInput(alcohol, PROMPT_ALCOHOL) || !checkAlcohol(alcohol));
    while (!getInput(volume, PROMPT_VOLUME) || !checkVolume(volume));
    cocktail.setName(n);
    cocktail.setAlcoholPercentage(alcohol);
    cocktail.setVolume(volume);
    return in;
}

Node::Node(Cocktail *cock) : cocktail(cock), next(nullptr) {}

HashTable::HashTable(int cap) : capacity(cap), size(0) {
    table = new Node *[capacity];
    for (int i = 0; i < capacity; ++i) {
        table[i] = nullptr;
    }
}

int HashTable::hash(const std::string &name) const {
    int res(0);
    for (char c: name) {
        res += (res * 52 + res) % capacity;
    }
    return res;
}


void HashTable::insert(Cocktail *cock) {
    int ind(hash(cock->getName()));
    Node *newNode = new Node(cock);

    newNode->next = table[ind];
    table[ind] = newNode;
    ++size;
}


void HashTable::remove(const std::string &name) {
    int ind(hash(name));
    Node *current = table[ind];
    Node *previous = nullptr;

    while (current && current->cocktail->getName() != name) {
        previous = current;
        current = current->next;
    }

    if (current) {
        if (previous) {
            previous->next = current->next;
        } else {
            table[ind] = current->next;
        }
        delete current->cocktail;
        delete current;
        --size;
    }
}


Cocktail *HashTable::get(const std::string &name) {
    int ind(hash(name));
    Node *current = table[ind];

    while (current) {
        if (current->cocktail->getName() == name) {
            return current->cocktail;
        }
        current = current->next;
    }
    return nullptr;
}

int HashTable::getCapacity() const {
    return capacity;
}

Node *HashTable::getElem(int ind) const {
    return table[ind];
}


HashTable::~HashTable() {
    for (int i = 0; i < capacity; ++i) {
        Node *current = table[i];
        while (current) {
            Node *temp = current;
            current = current->next;
            delete temp->cocktail;
            delete temp;
        }
    }
    delete[]table;
}


CocktailTable::CocktailTable(Cocktail cocktailsArray[], int n) {
    for (int i = 0; i < n; ++i) {
        cocktails += cocktailsArray[i];
    }
}


CocktailTable::CocktailTable(const CocktailTable &other) {
    for (int i = 0; i < other.cocktails.getCapacity(); ++i) {
        Node *nd = other.getElemViaIndex(i);
        while (nd) {
            cocktails += *nd->next;
        }
    }
}


CocktailTable::CocktailTable(CocktailTable &&other) noexcept: cocktails(std::move(other.cocktails)) {}


CocktailTable &CocktailTable::operator=(const CocktailTable &other) {
    if (this != &other) {
        // TODO: clearTable();
    }

    for (int i = 0; i < other.cocktails.getCapacity(); ++i) {
        Node *nd = other.cocktails.getElem(i);
        while (nd) {
            cocktails += *nd->cocktail;
        }
    }
    return *this;
}





int CocktailTable::getCapacity() {
    return cocktails.getCapacity();
}

bool CocktailTable::isEmpty() const {
    return numOfCocktails == 0;
}

bool CocktailTable::isFilled() const {
    return numOfCocktails > 0 && numOfCocktails < MAX_COCKTAILS;
}

bool CocktailTable::isFull() const {
    return numOfCocktails == MAX_COCKTAILS;
}

CocktailTable &CocktailTable::operator+=(const Cocktail &cocktail) {
    // TODO: Check if already in table
    if (!isFull()) {
        cocktails[numOfCocktails++] = cocktail;
    } else {
        std::cerr << "Table is full, cannot add more cocktails.\n";
    }
    return *this;
}

Cocktail &CocktailTable::operator[](const string &name) {
    for (int i = 0; i < numOfCocktails; ++i) {
        if (cocktails[i].getName() == name) {
            return cocktails[i];
        }
    }
    throw std::out_of_range("Cocktail not found");
}

void CocktailTable::removeCocktail(const string &name) {
    for (int i = 0; i < numOfCocktails; ++i) {
        if (cocktails[i].getName() == name) {
            for (int j = i; j < numOfCocktails - 1; ++j) {
                cocktails[j] = cocktails[j + 1];
            }
            --numOfCocktails;
            return;
        }
    }
    throw std::out_of_range("Cocktail not found");
}


Node *CocktailTable::getElemViaIndex(int ind) const {
    return cocktails.getElem(ind);
}

Cocktail CocktailTable::getCocktail(int minAlcohol, int maxAlcohol) {
    Cocktail result((string &) "Mixed", 0, 0);
    int totalVolume = 0;

    for (int i = 0; i < numOfCocktails; i++) {
        Cocktail currentCock = cocktails[i];
        int alcoholPerc = currentCock.getAlcoholPercentage();
        if (alcoholPerc >= minAlcohol && alcoholPerc <= maxAlcohol) {
            if (currentCock.getVolume() >= 500) {
                string newName = currentCock.getName();
                int newAlcohol = currentCock.getAlcoholPercentage();
                int newVolume = 500;
                currentCock.setVolume(currentCock.getVolume() - 500);
                return Cocktail(newName, newAlcohol, newVolume);
            }
        }

        result = result + currentCock;
        totalVolume += currentCock.getVolume();

        if (totalVolume >= 500) {
            result.setVolume(500);
            return result;
        }
    }
    throw std::out_of_range("Cocktail not found");
}

int CocktailTable::totalVolume(int lowerBound, int upperBound) const {
    int totalVolume = 0;
    for (int i = 0; i < numOfCocktails; ++i) {
        Cocktail currentCock = cocktails[i];
        int alcoholPerc = currentCock.getAlcoholPercentage();
        if (alcoholPerc >= lowerBound && alcoholPerc < upperBound) {
            totalVolume += currentCock.getVolume();
        }
    }
    return totalVolume;
}

void CocktailTable::renameCocktail(const string &oldName, const string &newName) {
    for (int i = 0; i < numOfCocktails; ++i) {
        Cocktail currentCock = cocktails[i];
        if (currentCock.getName() == oldName) {
            currentCock.setName(newName);
            return;
        }
    }
    std::cerr << "Cocktail not found." << std::endl;
}

// IO operators
ostream &operator<<(ostream &out, const CocktailTable &table) {
    out << "Cocktail Table: " << table.numOfCocktails << " cocktails" << std::endl;
    for (int i = 0; i < table.numOfCocktails; ++i) {
        out << table.cocktails[i] << std::endl;
    }
    return out;
}

istream &operator>>(istream &in, CocktailTable &table) {
    std::cout << "Enter number of cocktails: ";
    in >> table.numOfCocktails;
    for (int i = 0; i < table.numOfCocktails; ++i) {
        std::cout << "Enter details for cocktail " << i + 1 << ":" << std::endl;
        in >> table.cocktails[i];
    }
    return in;
}

