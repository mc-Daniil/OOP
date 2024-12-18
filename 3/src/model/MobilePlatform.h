/**
 * @file MobilePlatform.h
 * @brief Mobile platform class
 */
#ifndef INC_3_MOBILEPLATFORM_H
#define INC_3_MOBILEPLATFORM_H

#include "Platform.h"
#include "Map.h"

/**
 * @class MobilePlatform
 * @brief Represents a mobile platform in the security system
 *
 * A mobile platform has coordinates, a description, energy level, slots for modules,
 * and the ability to move. It can perform the following operations:
 * 1) Retrieve and modify its properties (coordinates, description, energy level, speed).
 * 2) Install and remove modules.
 * 3) Move to a new location.
 */
class MobilePlatform : public Platform {
private:
    /**
     * @brief Current coordinates of the platform
     */
    std::pair<uint, uint> coordinates;

    /**
     * @brief Description of the platform
     */
    std::string description;

    /**
     * @brief Current energy level of the platform
     */
    uint energyLevel;

    /**
     * @brief Number of slots available for modules
     */
    uint moduleSlots;

    /**
     * @brief Movement speed of the platform
     */
    uint speed;

    /**
     * @brief List of installed modules
     */
    std::vector<std::shared_ptr<Module>> modules;

public:
    /**
     * @brief Constructor for the MobilePlatform class
     * @param x - Initial x-coordinate of the platform
     * @param y - Initial y-coordinate of the platform
     * @param description - Description of the platform
     * @param energyLevel - Initial energy level
     * @param moduleSlots - Number of slots available for modules
     */
    MobilePlatform(uint x, uint y, const std::string &description, uint energyLevel, uint moduleSlots);

    /**
     * @brief Get the current coordinates of the platform
     * @return Pair of x and y coordinates
     */
    [[nodiscard]] std::pair<uint, uint> getCoordinates() const override;

    /**
     * @brief Set new coordinates for the platform
     * @param x - New x-coordinate
     * @param y - New y-coordinate
     */
    void setCoordinates(uint x, uint y) override;

    /**
     * @brief Get the description of the platform
     * @return Description as a string
     */
    [[nodiscard]] std::string getDescription() const override;

    /**
     * @brief Set the description of the platform
     * @param description - New description
     */
    void setDescription(const std::string &description) override;

    /**
     * @brief Get the current energy level of the platform
     * @return Energy level as an unsigned integer
     */
    [[nodiscard]] uint getEnergyLevel() const override;

    /**
     * @brief Set a new energy level for the platform
     * @param energyLevel - New energy level
     */
    void setEnergyLevel(uint energyLevel) override;

    /**
     * @brief Install a module onto the platform
     * @param module - Shared pointer to the module to be installed
     */
    void installModule(const std::shared_ptr<Module> &module) override;

    /**
     * @brief Remove a module from the platform
     * @param module - Shared pointer to the module to be removed
     */
    void removeModule(const std::shared_ptr<Module> &module) override;

    /**
     * @brief Get the list of installed modules
     * @return Vector of shared pointers to the modules
     */
    [[nodiscard]] const std::vector<std::shared_ptr<Module>> &getModules() const override;

    /**
     * @brief Get the speed of the platform
     * @return Speed as an unsigned integer
     */
    [[nodiscard]] uint getSpeed() const;

    /**
     * @brief Set a new speed for the platform
     * @param speed - New speed value
     */
    void setSpeed(uint speed);

    /**
     * @brief Move the platform to new coordinates
     * @param x - New x-coordinate
     * @param y - New y-coordinate
     */
    void move(uint x, uint y, const Map &map);
};

#endif //INC_3_MOBILEPLATFORM_H
