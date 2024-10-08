#ifndef INC_2_COCKTAIL_H
#define INC_2_COCKTAIL_H

#include <iostream>
#include <string>

using std::string;
using std::istream;
using std::ostream;

namespace lab2 {
    class Cocktail {
    private:
        string name;
        int alcoholPercentage;
        int volume;

    public:
        // Constructors
        explicit Cocktail();

        explicit Cocktail(string &n, int alcohol, int vol);

        explicit Cocktail(int vol);

        // Setters
        void setName(const string &n) {
            name = n;
        }

        void setAlcoholPercentage(int alcohol) {
            alcoholPercentage = alcohol;
        }

        void setVolume(int vol) {
            volume = vol;
        }

        // Getters
        [[nodiscard]] string getName() const {
            return name;
        }

        [[nodiscard]] int getAlcoholPercentage() const {
            return alcoholPercentage;
        }

        [[nodiscard]] int getVolume() const {
            return volume;
        }

        // Overloads of operators
        Cocktail operator+(const Cocktail &other) const;

        Cocktail &operator>>(Cocktail &other);

        Cocktail operator*(int multiplier) const;

        // IO operators
        friend ostream &operator<<(ostream &out, const Cocktail &cocktail);
        friend istream &operator>>(istream &in, Cocktail &cocktail);
    };
}

#endif //INC_2_COCKTAIL_H
