/**
 * @file StationaryPlatform.h
 * @brief Class representing a stationary platform
 */
#ifndef INC_3_STATIONARYPLATFORM_H
#define INC_3_STATIONARYPLATFORM_H

#include "Platform.h"

/**
 * @class StationaryPlatform
 * @brief Represents a stationary platform in the security system
 *
 * A stationary platform is fixed at a specific location and cannot move.
 * It supports modules that extend its functionality and maintains energy levels and other properties.
 */
class StationaryPlatform : public Platform {
private:
    /**
     * @brief Coordinates of the platform
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
     * @brief Number of available module slots on the platform
     */
    uint moduleSlots;

    /**
     * @brief List of installed modules
     */
    std::vector<std::shared_ptr<Module>> modules;

public:
    /**
     * @brief Constructor for the StationaryPlatform class
     * @param x - X-coordinate of the platform
     * @param y - Y-coordinate of the platform
     * @param description - Description of the platform
     * @param energyLevel - Initial energy level of the platform
     * @param moduleSlots - Number of module slots available
     */
    StationaryPlatform(uint x, uint y, std::string description, uint energyLevel, uint moduleSlots);

    /**
     * @brief Get the coordinates of the platform
     * @return Pair of x and y coordinates
     */
    [[nodiscard]] std::pair<uint, uint> getCoordinates() const override;

    /**
     * @brief Get the description of the platform
     * @return Description as a string
     */
    [[nodiscard]] std::string getDescription() const override;

    void setCoordinates(uint x, uint y) override;

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
     * @brief Set the energy level of the platform
     * @param energyLevel - New energy level
     */
    void setEnergyLevel(uint energyLevel) override;

    /**
     * @brief Install a module onto the platform
     * @param module - Shared pointer to the module to be installed
     * @throws std::runtime_error if not enough module slots are available
     */
    void installModule(const std::shared_ptr<Module> &module) override;

    /**
     * @brief Remove a module from the platform
     * @param module - Shared pointer to the module to be removed
     * @throws std::runtime_error if the module is not installed
     */
    void removeModule(const std::shared_ptr<Module> &module) override;

    /**
     * @brief Get the list of installed modules
     * @return Vector of shared pointers to the modules
     */
    [[nodiscard]] const std::vector<std::shared_ptr<Module>> &getModules() const override;
};

#endif //INC_3_STATIONARYPLATFORM_H
