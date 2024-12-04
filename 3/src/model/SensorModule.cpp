#include "SensorModule.h"
#include <iostream>

SensorModule::SensorModule(ModuleType type, uint energyConsumptionActive, uint energyConsumptionPassive,
                           uint slotsRequired, uint range, SensorType sensorType) : Module(type,
                                                                                           energyConsumptionActive,
                                                                                           energyConsumptionPassive,
                                                                                           slotsRequired),
                                                                                    type(sensorType),
                                                                                    range(range) {}

SensorType SensorModule::getSensorType() const {
    return type;
}

uint SensorModule::getRange() const {
    return range;
}

void SensorModule::scanEnvironment() {
    if (isOn()) {
        if (type == SensorType::XRAY) {
            std::cout << "XRAY is scanning" << std::endl;
        } else {
            std::cout << "OPTICAL is scanning" << std::endl;
        }
    }
}
