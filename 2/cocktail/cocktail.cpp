#include "cocktail.h"

namespace lab2 {
    Cocktail::Cocktail() : name(), alcoholPercentage(0), volume(0) {}

    Cocktail::Cocktail(string &n, int alcohol, int vol) : name(n), alcoholPercentage(alcohol), volume(vol) {}

    Cocktail::Cocktail(int vol) : name("Water"), alcoholPercentage(0), volume(vol) {}

    Cocktail Cocktail::operator+(const Cocktail &other) const {
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

    Cocktail Cocktail::operator*(int multiplier) const {
        int newVolume = volume * multiplier;
        string newName = name;
        int newAlcoholPercentage = alcoholPercentage;
        return Cocktail(newName, newAlcoholPercentage, newVolume);
    }

    ostream &operator<<(ostream &out, const Cocktail &cocktail) {
        out << "Cocktail: " << cocktail.name
            << " | Alcohol: " << cocktail.alcoholPercentage << "%"
            << " | Volume: " << cocktail.volume << "ml";
        return out;
    }

    istream &operator>>(istream &in, Cocktail &cocktail) {
        std::cout << "Enter name alcohol volume";
        in >> cocktail.name >> cocktail.alcoholPercentage >> cocktail.volume;
        return in;
    }
}
