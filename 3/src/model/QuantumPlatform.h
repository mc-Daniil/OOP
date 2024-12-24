#ifndef LAB3_QUANTUMPLATFORM_H
#define LAB3_QUANTUMPLATFORM_H

#include "Platform.h"
#include "Map.h"
#include "Intruder.h"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <stdexcept>

/**
 * @class QuantumPlatform
 * @brief A specialized platform that can swap places with another platform
 *        and teleport nearby intruders within its range to its new position.
 */
class QuantumPlatform : public Platform {
private:
    uint x;
    uint y;
    std::string description;
    uint energyLevel;
    uint moduleSlots;
    std::vector<std::shared_ptr<Module>> modules;
    uint detectionRadius;

public:
    /**
     * @brief Constructor for QuantumPlatform
     * @param startX - Initial X-coordinate
     * @param startY - Initial Y-coordinate
     * @param desc - Description of the platform
     * @param energy - Initial energy level
     * @param radius - Detection radius
     */
    QuantumPlatform(uint startX, uint startY, const std::string &desc, uint energy, uint radius)
            : x(startX), y(startY), description(desc), energyLevel(energy), moduleSlots(1), detectionRadius(radius) {}

    /**
     * @brief Get the current coordinates of the platform
     * @return Pair of x and y coordinates
     */
    [[nodiscard]] std::pair<uint, uint> getCoordinates() const override {
        return {x, y};
    }

    /**
     * @brief Set new coordinates for the platform
     * @param newX - New x-coordinate
     * @param newY - New y-coordinate
     */
    void setCoordinates(uint newX, uint newY) override {
        x = newX;
        y = newY;
    }

    /**
     * @brief Get the description of the platform
     * @return Description as a string
     */
    [[nodiscard]] std::string getDescription() const override {
        return description;
    }

    /**
     * @brief Set the description of the platform
     * @param desc - New description
     */
    void setDescription(const std::string &desc) override {
        description = desc;
    }

    /**
     * @brief Get the current energy level of the platform
     * @return Energy level as an unsigned integer
     */
    [[nodiscard]] uint getEnergyLevel() const override {
        return energyLevel;
    }

    /**
     * @brief Set a new energy level for the platform
     * @param energy - New energy level
     */
    void setEnergyLevel(uint energy) override {
        energyLevel = energy;
    }

    /**
     * @brief Install a module onto the platform
     * @param module - Shared pointer to the module to be installed
     */
    void installModule(const std::shared_ptr<Module> &module) override {
        modules.push_back(module);
    }

    /**
     * @brief Remove a module from the platform
     * @param module - Shared pointer to the module to be removed
     */
    void removeModule(const std::shared_ptr<Module> &module) override {
        modules.erase(std::remove(modules.begin(), modules.end(), module), modules.end());
    }

    /**
     * @brief Get the list of installed modules
     * @return Vector of shared pointers to the modules
     */
    [[nodiscard]] const std::vector<std::shared_ptr<Module>> &getModules() const override {
        return modules;
    }

    /**
     * @brief Swap places with another platform
     * @param other - The other platform to swap with
     */
    void swapWith(QuantumPlatform &other);

    /**
     * @brief Teleport intruders within detection radius to the platform's new position
     * @param intruderPositions - Vector of intruder positions (pairs of x and y coordinates)
     */
    void teleportIntruders(std::vector<std::pair<uint, uint>> &intruderPositions);

    /**
     * @brief Calculate the next move for the platform based on the map.
     * @param map - The map object
     * @return Pair of new coordinates (x, y)
     */
    std::pair<uint, uint> calculateNextMove(Map &map) {
        auto nextX = x + 1;
        auto nextY = y;
        if (map.isValidCoordinate(nextX, nextY) && map.getCell({nextX, nextY})->isAccessible()) {
            return {nextX, nextY};
        }
        // Если вправо нельзя, остаёмся на месте
        return {x, y};
    }

    /**
     * @brief Check if an intruder is within the detection radius
     * @param intruderCoords - Coordinates of the intruder
     * @return True if within detection radius, false otherwise
     */
    bool isWithinDetectionRadius(const std::pair<uint, uint> &intruderCoords) const {
        uint dx = std::abs(static_cast<int>(intruderCoords.first) - static_cast<int>(x));
        uint dy = std::abs(static_cast<int>(intruderCoords.second) - static_cast<int>(y));
        return std::sqrt(dx * dx + dy * dy) <= detectionRadius;
    }
};

#endif // LAB3_QUANTUMPLATFORM_H
