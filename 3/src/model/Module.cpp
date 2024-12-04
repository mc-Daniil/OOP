#include "Module.h"

Module::Module(ModuleType type, uint energyConsumptionActive, uint energyConsumptionPassive, uint slotsRequired)
        : type(type), energyConsumptionActive(energyConsumptionActive),
          energyConsumptionPassive(energyConsumptionPassive), slotsRequired(slotsRequired), isActive(false) {}

ModuleType Module::getType() const {
    return type;
}

uint Module::getEnergyConsumption() const {
    if (isActive) {
        return energyConsumptionActive;
    }
    return energyConsumptionPassive;
}

uint Module::getSlotsRequired() const {
    return slotsRequired;
}

void Module::on() {
    isActive = true;
}

void Module::off() {
    isActive = false;
}

bool Module::isOn() const {
    return isActive;
}