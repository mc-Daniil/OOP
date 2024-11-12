// ЭТО ЕЩЁ НЕ РАБОЧАЯ ВЕРСИЯ. Если рабочая версия не будет на гите, пишите в тг @danissimurr
/**
 * @file cocktail.h
 * @brief File with classes of cocktail and cocktail table
 */
#ifndef INC_2_COCKTAIL_H
#define INC_2_COCKTAIL_H

#include <iostream>
#include <string>
#include "../io/io.h"

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
     */
    Cocktail();

    /**
     * @brief Makes cocktail with users' parameters
     * Gets name, alcohol and volume of cocktail from user and makes cocktail
     * @param n - name of cocktail
     * @param alcohol - alcohol percentage
     * @param vol - volume
     */
    explicit Cocktail(string n, int alcohol, int vol);

    /**
     * @brief Makes glass of water
     * Gets only volume from user to make a glass of water
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
     * @brief Pour the cocktail over
     * Pour 100ml or less (if volume < 100 ml) to other cocktail
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
 * @class Node
 * @brief Node of hash table
 */
class Node {
public:
    Cocktail *cocktail;
    Node *next;

    /**
     * @brief Constructor for node with cocktail
     * @param cock - cocktail
     */
    explicit Node(Cocktail *cock);
};

/**
 * @class HashTable
 * @brief Hashtable to store cocktails
 */
class HashTable {
private:
    Node **table;
    int capacity;
    int size;

    /**
     * @brief Calculate hash sum
     * @param name - name of cocktail
     * @return Hash sum
     */
    [[nodiscard]] int hash(const string &name) const;

public:
    /**
     * @brief Constructor for empty hash table
     * @param cap - capacity of hash table (default = 10)
     */
    explicit HashTable(int cap = 10);

    /**
     * @brief Copy constructor
     * @param other - other cocktail
     */
    HashTable(const HashTable &other);

    /**
     * @brief Copy =
     * @param other - other cocktail
     * @return
     */
    HashTable &operator=(const HashTable &other);

    /**
     * @brief Moving constructor
     * @param other - source cocktail
     */
    HashTable(HashTable &&other) noexcept;

    /**
     * @brief Moving =
     * @param other - source cocktail
     * @return this cocktail
     */
    HashTable &operator=(HashTable &&other) noexcept;

    /**
     * @brief Resize hash table if it's full
     */
    void rehash();

    /**
     * @brief Insert new cocktail, if it's not in table
     * @param cock - cocktail to insert
     */
    void insert(Cocktail *cock);

    /**
     * @brief Remove cocktail from table via name
     * @param name - name of cocktail
     */
    void remove(const string &name);

    /**
     * @brief Free memory from table
     */
    void clearTable();

    /**
     * @brief Get cocktail from table via it's name
     * @param name - name of cocktail
     * @return pointer to cocktail
     */
    Cocktail *get(const string &name);

    /**
     * @brief Get number of cocktail the table can store
     * @return capacity
     */
    [[nodiscard]] int getCapacity() const;

    /**
     * @brief Get number of cocktail stored in the table
     * @return number of cocktail in the table
     */
    [[nodiscard]] int getSize() const;

    /**
     * @brief Get element from table via it's index
     * @param ind - index of element
     * @return pointer to node
     */
    [[nodiscard]] Node *getElem(int ind) const;

    /**
     * @brief Destructor
     */
    ~HashTable();
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
    HashTable cocktails;

public:
    /**
     * @brief Empty constructor
     */
    CocktailTable() = default;

    /**
     * @brief Makes table with n cocktails from array of pointers to cocktails
     * @param cocktailsArray - array of cocktails
     * @param n - number of cocktails
     */
    explicit CocktailTable(Cocktail *cocktailsArray[], int n);

    /**
     * @brief Copy constructor
     * @param other - source cocktail
     */
    CocktailTable(const CocktailTable &other);

    /**
     * @brief Copy =
     * @param other - source cocktail
     * @return this cocktail
     */
    CocktailTable &operator=(const CocktailTable &other);

    /**
     * @brief Moving constructor
     * @param other - source cocktail
     */
    CocktailTable(CocktailTable &&other) noexcept;

    /**
     * @brief Moving =
     * @param other - source cocktail
     * @return this cocktail
     */
    CocktailTable &operator=(CocktailTable &&other) noexcept;

    /**
     * @brief Destructor
     */
    ~CocktailTable() = default;

    /**
    * @brief Get number of cocktails in table
    * @return  number of cocktails in table
    */
    int getSize();

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
     * @brief Get pointer to nedo via index
     * @param ind - index
     * @return pointer to node
     */
    [[nodiscard]] Node *getElemViaIndex(int ind) const;

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
