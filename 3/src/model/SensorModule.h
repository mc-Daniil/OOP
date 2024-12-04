#ifndef INC_3_SENSORMODULE_H
#define INC_3_SENSORMODULE_H

#include "Module.h"

using uint = unsigned int;

enum class SensorType {
    OPTICAL, XRAY
};

class SensorModule : public Module {
private:
    SensorType type;
    uint range;
public:
    SensorModule(ModuleType type, uint energyConsumptionActive, uint energyConsumptionPassive,
                 uint slotsRequired, uint range, SensorType sensorType);

    [[nodiscard]] SensorType getSensorType() const;

    [[nodiscard]] uint getRange() const;

    void scanEnvironment();
};

#endif //INC_3_SENSORMODULE_H
