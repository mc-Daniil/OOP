#include "WeaponModule.h"
#include <stdexcept>

WeaponModule::WeaponModule(ModuleType type, uint energyConsumptionActive, uint energyConsumptionPassive,
                           uint slotsRequired, uint range, uint chargingTime) : Module(type, energyConsumptionActive,
                                                                                       energyConsumptionPassive,
                                                                                       slotsRequired), range(range),
                                                                                chargingTime(chargingTime),
                                                                                isCharging(false) {}

uint WeaponModule::getRange() const {
    return range;
}

void WeaponModule::startCharging() {
    if (!isCharging) {
        isCharging = true;
        isActive = true;
    }
}

void WeaponModule::stopCharging() {
    if (isCharging) {
        isCharging = false;
        isActive = false;
    }
}

void WeaponModule::neutralizeTarget() {

}


