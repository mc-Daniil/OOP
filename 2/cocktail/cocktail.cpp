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
    out << "Cocktail: " << cocktail.name << " | Alcohol: " << cocktail.alcoholPercentage << "%" << " | Volume: " << cocktail.volume << "ml";
    return out;
}

istream &operator>>(istream &in, Cocktail &cocktail) {
    // TODO: check input
    std::cout << "Enter name ('Water' or sth else) | alcohol | volume";
    in >> cocktail.name >> cocktail.alcoholPercentage >> cocktail.volume;
    return in;
}

//Cocktailtable
CocktailTable::CocktailTable() : numOfCocktails(0) {}

CocktailTable::CocktailTable(Cocktail *cocktailsArray, int n) : numOfCocktails(n) {
    // TODO: array?..
    for (int i = 0; i < n; ++i) {
        cocktails[i] = cocktailsArray[i];
    }
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

