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
 * @brief Class for one cocktail.
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

    /**
     * @brief Makes glass of water
     * Gets only volume to make a glass of water
     * @param vol - volume of water
     */
    explicit Cocktail(int vol);

    /**
     * @brief Sets cocktail name
     * @param n - name of cocktail
     */
    void setName(const string &n) {
        name = n;
    }
    /**
     * @brief Sets alcohol percentage
     * @param alcohol - alcohol percentage
     */
    void setAlcoholPercentage(int alcohol) {
        alcoholPercentage = alcohol;
    }

    /**
     * @brief Sets cocktail volume
     * @param vol - volume
     */
    void setVolume(int vol) {
        volume = vol;
    }

    /**
     * @brief Gets name of cocktail
     * @return Name of cocktail
     */
    [[nodiscard]] string getName() const {
        return name;
    }

    /**
     * @brief Gets alcohol percentage of cocktail
     * @return alcohol percentage
     */
    [[nodiscard]] int getAlcoholPercentage() const {
        return alcoholPercentage;
    }

    /**
     * @brief Gets cocktail volume
     * @return volume of cocktail
     */
    [[nodiscard]] int getVolume() const {
        return volume;
    }

    /**
     * @brief Mix cocktails
     * Overload for + to mix 2 cocktails and make new cocktail
     * @param other - second cocktail
     * @return New mixed cocktail
     */
    Cocktail operator+(const Cocktail &other) const;
    /**
     * @brief Put the cocktail over
     * Put 100ml or less (if volume < 100 ml) to other cocktail
     * @param other - destination cocktail
     * @return This cocktail with less volume
     */
    Cocktail &operator>>(Cocktail &other);

    /**
     * @brief Increase cocktail volume
     * Increases cocktail volume n times user wants
     * @param multiplier - on what increase
     * @return This cocktail with new volume
     */
    Cocktail operator*(int multiplier);

    /**
     * @brief Print cocktail information
     * @param out - out-stream
     * @param cocktail - out cocktail
     * @return out-stream
     */
    friend ostream &operator<<(ostream &out, const Cocktail &cocktail);
    /**
     * @brief Input parameters for new cocktail
     * @param in - in-stream
     * @param cocktail - new cocktail
     * @return in-stream
     */
    friend istream &operator>>(istream &in, Cocktail &cocktail);
};

/**
 * @class Cocktailtable
 * @brief Class cocktail table.
 * Allows:
 *
 */
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
