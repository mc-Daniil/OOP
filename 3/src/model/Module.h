/**
 * @file Module.h
 * @brief Abstract module class
 */
#ifndef INC_3_MODULE_H
#define INC_3_MODULE_H

using uint = unsigned int;

/**
 * @enum ModuleType
 * @brief Represents the type of the module
 *
 * Possible values:
 * - NETWORK: Network module
 * - SENSOR: Sensor module
 * - WEAPON: Weapon module
 */
enum class ModuleType {
    NETWORK,  /**< Network module */
    SENSOR,   /**< Sensor module */
    WEAPON    /**< Weapon module */
};

/**
 * @class Module
 * @brief Abstract base class for a module
 *
 * Represents a module that can be installed on a platform. Modules consume energy,
 * occupy a certain number of slots, and can be activated or deactivated.
 */
class Module {
protected:
    /**
     * @brief Type of the module
     */
    ModuleType type;

    /**
     * @brief Energy consumption in active mode
     */
    uint energyConsumptionActive;

    /**
     * @brief Energy consumption in passive mode
     */
    uint energyConsumptionPassive;

    /**
     * @brief Number of slots required by the module
     */
    uint slotsRequired;

    /**
     * @brief Indicates whether the module is active
     */
    bool isActive;

public:
    /**
     * @brief Constructor for the Module class
     * @param type - Type of the module
     * @param energyConsumptionActive - Energy consumption in active mode
     * @param energyConsumptionPassive - Energy consumption in passive mode
     * @param slotsRequired - Number of slots required by the module
     */
    Module(ModuleType type, uint energyConsumptionActive, uint energyConsumptionPassive, uint slotsRequired);

    /**
     * @brief Virtual destructor
     */
    virtual ~Module() = default;

    /**
     * @brief Get the type of the module
     * @return Type of the module as a ModuleType
     */
    [[nodiscard]] ModuleType getType() const;

    /**
     * @brief Get the current energy consumption of the module
     *
     * Energy consumption depends on whether the module is active or passive.
     * @return Energy consumption as an unsigned integer
     */
    [[nodiscard]] uint getEnergyConsumption() const;

    /**
     * @brief Get the number of slots required by the module
     * @return Number of slots as an unsigned integer
     */
    [[nodiscard]] uint getSlotsRequired() const;

    /**
     * @brief Activate the module
     *
     * Switches the module to active mode, increasing its energy consumption.
     */
    virtual void on();

    /**
     * @brief Deactivate the module
     *
     * Switches the module to passive mode, reducing its energy consumption.
     */
    virtual void off();

    /**
     * @brief Check if the module is active
     * @return True if the module is active, false otherwise
     */
    [[nodiscard]] bool isOn() const;
};

#endif //INC_3_MODULE_H
