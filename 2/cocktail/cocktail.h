/**
 * @file cocktail.h
 * File with classes of cocktail and cocktail table
 */
#ifndef INC_2_COCKTAIL_H
#define INC_2_COCKTAIL_H

#include <iostream>
#include <string>

using std::string;
using std::istream;
using std::ostream;

/**
 * @class Cocktail
 * @brief Class for one cocktail
 * Allows:
 * 1. Make cocktail
 * 2. Mix cocktails
 * 3. Pour the cocktail over
 * 4. Increase volume of cocktail
 */
class Cocktail {
private:
    string name;
    int alcoholPercentage;
    int volume;

public:
    /**
     * @brief Empty constructor
     * Makes empty cocktail
     */
    explicit Cocktail();

    /**
     * @brief Makes cocktail with users parameters
     * Gets name, alcohol and volume of cocktail from user and makes cocktail
     * @param n - name of cocktail
     * @param alcohol - alcohol percentage
     * @param vol - volume
     */
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


class CocktailTable {
private:
    static const int MAX_COCKTAILS = 10;
    Cocktail cocktails[MAX_COCKTAILS];
    int numOfCocktails;

public:
    // Constructors
    explicit CocktailTable();

    explicit CocktailTable(Cocktail *cocktailsArray, int n);

    // Methods
    [[nodiscard]] bool isEmpty() const;

    [[nodiscard]] bool isFilled() const;

    [[nodiscard]] bool isFull() const;

    void removeCocktail(const string &name);

    Cocktail getCocktail(int minAlcohol, int maxAlcohol);

    [[nodiscard]] int totalVolume(int lowerBound, int upperBound) const;

    void renameCocktail(const string &oldName, const string &newName);

    // Overloads of operators
    CocktailTable &operator+=(const Cocktail &cocktail);

    Cocktail &operator[](const string &name);

    // IO operators
    friend ostream &operator<<(ostream &out, const CocktailTable &table);

    friend istream &operator>>(istream &in, CocktailTable &table);
};

#endif //INC_2_COCKTAIL_H
