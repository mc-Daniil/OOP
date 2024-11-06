#include "cocktail.h"

#include <utility>
#include "../main.h"

Cocktail::Cocktail() : name(), alcoholPercentage(0), volume(0) {}

Cocktail::Cocktail(string n, int alcohol, int vol) : name(std::move(n)), alcoholPercentage(alcohol), volume(vol) {}

Cocktail::Cocktail(int vol) : name("Water"), alcoholPercentage(0), volume(vol) {}

Cocktail Cocktail::operator+(const Cocktail &other) {
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

Cocktail Cocktail::operator*(int multiplier) {
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
    int res = 0;
    for (char c: name) {
        res = (res * 31 + c) % capacity;
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


void HashTable::clearTable() {
    for (int i = 0; i < capacity; ++i) {
        Node *current = table[i];
        while (current) {
            Node *temp = current;
            current = current->next;
            delete temp->cocktail;
            delete temp;
        }
        table[i] = nullptr;
    }
    size = 0;
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

int HashTable::getSize() const {
    return size;
}

Node *HashTable::getElem(int ind) const {
    return table[ind];
}


HashTable::~HashTable() {
    clearTable();
    delete[]table;
}


CocktailTable::CocktailTable(Cocktail *cocktailsArray[], int n) {
    for (int i = 0; i < n; ++i) {
        cocktails.insert(cocktailsArray[i]);
    }
}


CocktailTable::CocktailTable(const CocktailTable &other) {
    for (int i = 0; i < other.cocktails.getCapacity(); ++i) {
        Node *node = other.getElemViaIndex(i);
        while (node) {
            auto *newCocktail = new Cocktail(*node->cocktail);
            cocktails.insert(newCocktail);
            node = node->next;
        }
    }
}


CocktailTable::CocktailTable(CocktailTable &&other) noexcept {
    cocktails = std::move(other.cocktails);
}


CocktailTable &CocktailTable::operator=(const CocktailTable &other) {
    if (this != &other) {
        cocktails.clearTable();

        for (int i = 0; i < other.cocktails.getCapacity(); ++i) {
            Node *node = other.cocktails.getElem(i);
            while (node) {
                auto *newCocktail = new Cocktail(*node->cocktail);
                cocktails.insert(newCocktail);
                node = node->next;
            }
        }
    }
    return *this;
}


CocktailTable &CocktailTable::operator=(CocktailTable &&other) noexcept {
    if (this != &other) {
        cocktails.clearTable();
        cocktails = std::move(other.cocktails);
    }
    return *this;
}


int CocktailTable::getCapacity() {
    return cocktails.getCapacity();
}

int CocktailTable::getSize() {
    return cocktails.getSize();
}

bool CocktailTable::isEmpty() const {
    return cocktails.getSize() == 0;
}

bool CocktailTable::isFilled() const {
    return cocktails.getSize() > 0 && cocktails.getSize() < cocktails.getCapacity();
}

bool CocktailTable::isFull() const {
    return cocktails.getSize() == cocktails.getCapacity();
}

CocktailTable &CocktailTable::operator+=(const Cocktail &cocktail) {
    auto *newCock = new Cocktail(cocktail);
    cocktails.insert(newCock);
    return *this;
}

Cocktail &CocktailTable::operator[](const string &name) {
    Cocktail *cock = cocktails.get(name);
    if (!cock) {
        throw std::runtime_error("Cocktail not found!");
    }
    return *cock;
}

void CocktailTable::removeCocktail(const string &name) {
    cocktails.remove(name);
}


Node *CocktailTable::getElemViaIndex(int ind) const {
    return cocktails.getElem(ind);
}

Cocktail CocktailTable::getCocktail(int minAlcohol, int maxAlcohol) {
    Cocktail resultCock((string &) "Mixed", 0, 0);
    int totalVolume = 0;

    for (int i = 0; i < cocktails.getCapacity(); ++i) {
        Node *current = cocktails.getElem(i);

        while (current) {
            Cocktail *currentCock = current->cocktail;
            int alcohol = currentCock->getAlcoholPercentage();

            if (alcohol >= minAlcohol && alcohol <= maxAlcohol) {
                if (currentCock->getVolume() >= 500) {
                    string newName = currentCock->getName();
                    int newAlcohol = currentCock->getAlcoholPercentage();
                    int newVolume = 500;
                    currentCock->setVolume(currentCock->getVolume() - 500);
                    if (currentCock->getVolume() == 0) {
                        cocktails.remove(currentCock->getName());
                    }
                    return Cocktail(newName, newAlcohol, newVolume);
                }
            }

            resultCock = resultCock + *currentCock;
            totalVolume += currentCock->getVolume();

            auto *res = new Cocktail;
            res->setName(resultCock.getName());
            res->setAlcoholPercentage(resultCock.getAlcoholPercentage());
            res->setVolume(resultCock.getVolume());
            cocktails.insert(res);

            if (totalVolume >= 500) {
                res->setVolume(res->getVolume() - 500);
                Cocktail ret;
                ret.setName(res->getName());
                ret.setAlcoholPercentage(res->getAlcoholPercentage());
                ret.setVolume(500);
                if (res->getVolume() == 0) {
                    cocktails.remove(res->getName());
                }
                return ret;
            }

            current = current->next;
        }
    }

    throw std::out_of_range("Cocktail not found");
}

int CocktailTable::totalVolume(int lowerBound, int upperBound) const {
    int totalVolume = 0;

    for (int i = 0; i < cocktails.getCapacity(); ++i) {
        Node *current = cocktails.getElem(i);

        while (current) {
            Cocktail *currentCock = current->cocktail;
            int alcohol = currentCock->getAlcoholPercentage();

            if (alcohol >= lowerBound && alcohol <= upperBound) {
                totalVolume += currentCock->getVolume();
            }

            current = current->next;
        }
    }

    return totalVolume;
}

void CocktailTable::renameCocktail(const string &oldName, const string &newName) {
    Cocktail *target = cocktails.get(oldName);

    if (target) {
        target->setName(newName);
    } else {
        throw std::out_of_range("Cocktail not found");
    }
}

// IO operators
ostream &operator<<(ostream &out, const CocktailTable &table) {
    for (int i = 0; i < table.cocktails.getCapacity(); ++i) {
        Node *node = table.getElemViaIndex(i);
        while (node) {
            out << "Name: " << node->cocktail->getName()
                << ", Alcohol: " << node->cocktail->getAlcoholPercentage()
                << "%, Volume: " << node->cocktail->getVolume() << " ml\n";
            node = node->next;
        }
    }
    return out;
}


istream &operator>>(istream &in, CocktailTable &table) {
    std::cout << "Enter number of cocktails: ";
    int count;
    in >> count;
    for (int i = 0; i < count; ++i) {
        Cocktail cocktail;
        in >> cocktail;
        table += cocktail;
    }
    return in;
}

