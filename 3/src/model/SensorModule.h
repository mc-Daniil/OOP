/**
 * @file SensorModule.h
 * @brief Sensor module class
 */
#ifndef INC_3_SENSORMODULE_H
#define INC_3_SENSORMODULE_H

#include "Module.h"

using uint = unsigned int;

/**
 * @enum SensorType
 * @brief Represents the type of the sensor
 *
 * Possible values:
 * - OPTICAL: Optical sensor
 * - XRAY: X-ray sensor
 */
enum class SensorType {
    OPTICAL, /**< Optical sensor */
    XRAY     /**< X-ray sensor */
};

/**
 * @class SensorModule
 * @brief Represents a sensor module in the security system
 *
 * The sensor module detects objects or entities in the environment. It has a specific range
 * and type (optical or X-ray) and can scan the surroundings to gather information.
 */
class SensorModule : public Module {
private:
    /**
     * @brief Type of the sensor
     */
    SensorType type;

    /**
     * @brief Detection range of the sensor
     */
    uint range;

public:
    /**
     * @brief Constructor for the SensorModule class
     * @param type - Type of the module
     * @param energyConsumptionActive - Energy consumption in active mode
     * @param energyConsumptionPassive - Energy consumption in passive mode
     * @param slotsRequired - Number of slots required by the module
     * @param range - Detection range of the sensor
     * @param sensorType - Type of the sensor (optical or X-ray)
     */
    SensorModule(ModuleType type, uint energyConsumptionActive, uint energyConsumptionPassive,
                 uint slotsRequired, uint range, SensorType sensorType);

    /**
     * @brief Get the type of the sensor
     * @return Type of the sensor as a SensorType
     */
    [[nodiscard]] SensorType getSensorType() const;

    /**
     * @brief Get the detection range of the sensor
     * @return Detection range as an unsigned integer
     */
    [[nodiscard]] uint getRange() const;

    /**
     * @brief Scan the environment
     *
     * Performs a scanning operation based on the sensor's type and range. The
     * results of the scan can be used to detect nearby objects or entities.
     */
    void scanEnvironment();
};

#endif //INC_3_SENSORMODULE_H
