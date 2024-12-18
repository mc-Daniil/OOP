/**
 * @file Intruder.h
 * @brief Class representing an intruder in the security system
 */

#ifndef INC_3_INTRUDER_H
#define INC_3_INTRUDER_H

#include <utility>
#include <string>
#include <vector>
#include "Map.h"
#include "Platform.h"

using uint = unsigned int;

/**
 * @class Intruder
 * @brief Represents an intruder in the security system
 *
 * The intruder moves within the environment and can exhibit different behaviors,
 * such as moving randomly or attempting to evade security platforms.
 */
class Intruder {
private:
    /**
     * @brief Current coordinates of the intruder
     */
    std::pair<uint, uint> coordinates;

    /**
     * @brief State of the intruder (e.g., "escaping", "wandering")
     */
    std::string state;

public:
    /**
     * @brief Constructor for the Intruder class
     * @param x - Initial x-coordinate
     * @param y - Initial y-coordinate
     */
    Intruder(uint x, uint y);

    /**
     * @brief Get the current coordinates of the intruder
     * @return Pair of x and y coordinates
     */
    [[nodiscard]] std::pair<uint, uint> getCoordinates() const;

    /**
     * @brief Set the coordinates of the intruder
     * @param x - New x-coordinate
     * @param y - New y-coordinate
     */
    void setCoordinates(uint x, uint y);

    /**
     * @brief Move the intruder randomly within the environment
     * @param map - Reference to the environment map
     */
    void moveRandomly(const Map& map);

    /**
     * @brief Move the intruder to evade security platforms
     * @param map - Reference to the environment map
     * @param platforms - List of security platforms
     */
    void moveToEvade(const Map& map, const std::vector<std::shared_ptr<Platform>>& platforms);

    /**
     * @brief Determine the next coordinates based on behavior
     * @param map - Reference to the environment map
     * @param platforms - List of security platforms
     * @return Pair of new x and y coordinates
     */
    [[nodiscard]] std::pair<uint, uint> getNextCoordinates(const Map& map, const std::vector<std::shared_ptr<Platform>>& platforms);

    /**
     * @brief Get the current state of the intruder
     * @return State as a string
     */
    [[nodiscard]] std::string getState() const;

    /**
     * @brief Set the state of the intruder
     * @param state - New state
     */
    void setState(const std::string& state);

    std::pair<uint, uint> calculateNextMove(const Map &map);
};

#endif // INC_3_INTRUDER_H
