/**
 * @file Platform.h
 * @brief Abstract class for platform
 */
#ifndef INC_3_PLATFORM_H
#define INC_3_PLATFORM_H

#include <string>
#include <vector>
#include <memory>
#include "Module.h"

using uint = unsigned int;

/**
 * @class Platform
 * @brief Abstract base class for platforms in the security system
 *
 * Represents a platform that can have a position in space, a description, an energy level,
 * and a set of installed modules. The platform can install or remove modules and modify
 * certain properties like coordinates, description, and energy level.
 */
class Platform {
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~Platform() = default;

    /**
     * @brief Get the current coordinates of the platform
     * @return Pair of x and y coordinates
     */
    [[nodiscard]] virtual std::pair<uint, uint> getCoordinates() const = 0;

    /**
     * @brief Set new coordinates for the platform
     * @param x - New x-coordinate
     * @param y - New y-coordinate
     */
    virtual void setCoordinates(uint x, uint y) = 0;

    /**
     * @brief Get the description of the platform
     * @return Description as a string
     */
    [[nodiscard]] virtual std::string getDescription() const = 0;

    /**
     * @brief Set the description of the platform
     * @param description - New description
     */
    virtual void setDescription(const std::string &description) = 0;

    /**
     * @brief Get the current energy level of the platform
     * @return Energy level as an unsigned integer
     */
    [[nodiscard]] virtual uint getEnergyLevel() const = 0;

    /**
     * @brief Set a new energy level for the platform
     * @param energyLevel - New energy level
     */
    virtual void setEnergyLevel(uint energyLevel) = 0;

    /**
     * @brief Install a module onto the platform
     * @param module - Shared pointer to the module to be installed
     */
    virtual void installModule(const std::shared_ptr<Module> &module) = 0;

    /**
     * @brief Remove a module from the platform
     * @param module - Shared pointer to the module to be removed
     */
    virtual void removeModule(const std::shared_ptr<Module> &module) = 0;

    /**
     * @brief Get the list of installed modules
     * @return Vector of shared pointers to the modules
     */
    [[nodiscard]] virtual const std::vector<std::shared_ptr<Module>> &getModules() const = 0;
};

#endif //INC_3_PLATFORM_H
