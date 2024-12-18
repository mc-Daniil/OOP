#include "MobilePlatform.h"
#include <algorithm>

MobilePlatform::MobilePlatform(uint x, uint y, const std::string &description, uint energyLevel, uint moduleSlots)
        : coordinates({x, y}), description(description), energyLevel(energyLevel), moduleSlots(moduleSlots), speed(0) {}

std::pair<uint, uint> MobilePlatform::getCoordinates() const {
    return coordinates;
}

void MobilePlatform::setCoordinates(uint x, uint y) {
    coordinates = {x, y};
}

std::string MobilePlatform::getDescription() const {
    return description;
}

void MobilePlatform::setDescription(const std::string &newDescription) {
    description = newDescription;
}

uint MobilePlatform::getEnergyLevel() const {
    return energyLevel;
}

void MobilePlatform::setEnergyLevel(uint newEnergyLevel) {
    energyLevel = newEnergyLevel;
}

void MobilePlatform::installModule(const std::shared_ptr<Module> &module) {
    if (modules.size() == moduleSlots) {
        throw std::runtime_error("No available slots");
    }
    if (module->getSlotsRequired() > (moduleSlots - modules.size())) {
        throw std::runtime_error("Not enough slots");
    }
    if (module->getEnergyConsumption() > energyLevel) {
        throw std::runtime_error("Not enough energy");
    }
    modules.push_back(module);
    energyLevel -= module->getEnergyConsumption();
}

void MobilePlatform::removeModule(const std::shared_ptr<Module> &module) {
    auto iterator = std::find(modules.begin(), modules.end(), module);
    if (iterator == modules.end()) {
        throw std::runtime_error("No module");
    }
    energyLevel += module->getEnergyConsumption();
    modules.erase(iterator);
}

const std::vector<std::shared_ptr<Module>> &MobilePlatform::getModules() const {
    return modules;
}

uint MobilePlatform::getSpeed() const {
    return speed;
}

void MobilePlatform::setSpeed(uint newSpeed) {
    speed = newSpeed;
}

void MobilePlatform::move(uint x, uint y) {
    setCoordinates(x, y);
}
