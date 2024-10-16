/**
 * @file cocktail.h
 * @brief File with classes of cocktail and cocktail table
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
    Cocktail operator+(const Cocktail &other);
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
    Cocktail operator*(int &multiplier);

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
 * @class CocktailTable
 * @brief Class cocktail table.
 * Allows:
 * 1. Make cocktail table
 * 2. Add new cocktail
 * 3. Get cocktail via name
 * 4. Delete cocktail
 * 5. Get 500 ml of cocktail with special percent of alcohol
 * 6. Count cocktails with alcohol percentage
 * 7. Rename cocktail
 */
class CocktailTable {
private:
    static const int MAX_COCKTAILS = 10;
    Cocktail cocktails[MAX_COCKTAILS];
    int numOfCocktails;

public:
    /**
     * @brief Empty constructor
     * Makes empty table
     */
    explicit CocktailTable();

    /**
     * @brief Makes table with n cocktails
     * @param cocktailsArray
     * @param n - number of cocktails
     */
    explicit CocktailTable(Cocktail *cocktailsArray, int n);

    /**
     * @brief Check if num of cocktails = 0
     * @return true if number of cocktails = 0
     */
    [[nodiscard]] bool isEmpty() const;

    /**
     * @brief Check if table is not full and not empty
     * @return true if not full and not empty
     */
    [[nodiscard]] bool isFilled() const;

    /**
     * @brief Check if table is full
     * @return true if table is full
     */
    [[nodiscard]] bool isFull() const;

    /**
     * @brief Remove cocktail from table via name
     * @param name - name of cocktail to remove
     */
    void removeCocktail(const string &name);

    /**
     * @brief Get cocktail with specific % of alcohol
     * @param minAlcohol - lower bound of alcohol percentage
     * @param maxAlcohol - upper bound of alcohol percentage
     * @return cocktail with specific alcohol percentage
     */
    Cocktail getCocktail(int minAlcohol, int maxAlcohol);

    /**
     * @brief Get total volume of cocktail with specific alcohol percentage
     * @param lowerBound - lower bound of alcohol percentage
     * @param upperBound - upper bound of alcohol percentage
     * @return total volume of cocktails with specific alcohol percentage
     */
    [[nodiscard]] int totalVolume(int lowerBound, int upperBound) const;

    /**
     * @brief Rename cocktail
     * @param oldName - old name of cocktail
     * @param newName - new name of cocktail
     */
    void renameCocktail(const string &oldName, const string &newName);

    /**
     * @brief Add new cocktail in table
     * @param cocktail - cocktail to add
     * @return cocktail table
     */
    CocktailTable &operator+=(const Cocktail &cocktail);

    /**
     * @brief Get cocktail via name
     * @param name - name of cocktail to get
     * @return cocktail user needs
     */
    Cocktail &operator[](const string &name);

    /**
     * @brief Print cocktail table
     * @param out - out-stream
     * @param table - table to print
     * @return out-stream
     */
    friend ostream &operator<<(ostream &out, const CocktailTable &table);

    /**
     * @brief Input num of cocktails, cocktails and add them in table
     * @param in - in-stream
     * @param table - table where to add
     * @return in-stream
     */
    friend istream &operator>>(istream &in, CocktailTable &table);
};

#endif //INC_2_COCKTAIL_H
