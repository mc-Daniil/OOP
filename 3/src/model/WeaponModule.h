/**
 * @file WeaponModule.h
 * @brief Class representing a weapon module
 */
#ifndef INC_3_WEAPONMODULE_H
#define INC_3_WEAPONMODULE_H

#include "Module.h"

using uint = unsigned int;

/**
 * @class WeaponModule
 * @brief Represents a weapon module in the security system
 *
 * The weapon module is designed to neutralize intruders. It has a defined range,
 * charging time, and supports operations to start and stop charging, as well as neutralizing a target.
 */
class WeaponModule : public Module {
private:
    /**
     * @brief Effective range of the weapon
     */
    uint range;

    /**
     * @brief Time required to fully charge the weapon
     */
    uint chargingTime;

    /**
     * @brief Charging state of the weapon
     */
    bool isCharging;

public:
    /**
     * @brief Constructor for the WeaponModule class
     * @param type - Type of the module
     * @param energyConsumptionActive - Energy consumption in active mode
     * @param energyConsumptionPassive - Energy consumption in passive mode
     * @param slotsRequired - Number of slots required by the module
     * @param range - Effective range of the weapon
     * @param chargingTime - Time required to charge the weapon
     */
    WeaponModule(ModuleType type, uint energyConsumptionActive, uint energyConsumptionPassive,
                 uint slotsRequired, uint range, uint chargingTime);

    /**
     * @brief Get the effective range of the weapon
     * @return Effective range as an unsigned integer
     */
    [[nodiscard]] uint getRange() const;

    /**
     * @brief Start the weapon's charging process
     *
     * Puts the weapon in charging mode, increasing energy consumption.
     * Charging is required before the weapon can be used to neutralize a target.
     */
    void startCharging();

    /**
     * @brief Stop the weapon's charging process
     *
     * Ends the charging mode and reduces energy consumption to the passive level.
     */
    void stopCharging();

    /**
     * @brief Neutralize a target
     *
     * Executes the weapon's function to neutralize a target within its range.
     * Can only be used when the weapon is fully charged.
     * @throws std::runtime_error if the weapon is not fully charged
     */
    void neutralizeTarget();
};

#endif //INC_3_WEAPONMODULE_H
