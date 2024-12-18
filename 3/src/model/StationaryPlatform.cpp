#include "StationaryPlatform.h"
#include <stdexcept>

StationaryPlatform::StationaryPlatform(uint x, uint y, const std::string &description, uint energyLevel,
                                       uint moduleSlots)
        : coordinates({x, y}), description(description), energyLevel(energyLevel), moduleSlots(moduleSlots) {}

std::pair<uint, uint> StationaryPlatform::getCoordinates() const {
    return coordinates;
}

void StationaryPlatform::setCoordinates(uint x, uint y) {
    throw std::runtime_error("Stationary platform can't move");
}

std::string StationaryPlatform::getDescription() const {
    return description;
}

void StationaryPlatform::setDescription(const std::string &newDescription) {
    description = newDescription;
}

uint StationaryPlatform::getEnergyLevel() const {
    return energyLevel;
}

void StationaryPlatform::setEnergyLevel(uint newEnergyLevel) {
    energyLevel = newEnergyLevel;
}

void StationaryPlatform::installModule(const std::shared_ptr<Module> &module) {
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

void StationaryPlatform::removeModule(const std::shared_ptr<Module> &module) {
    auto iterator = std::find(modules.begin(), modules.end(), module);
    if (iterator == modules.end()) {
        throw std::runtime_error("No module");
    }
    energyLevel += module->getEnergyConsumption();
    modules.erase(iterator);
}

const std::vector<std::shared_ptr<Module>> &StationaryPlatform::getModules() const {
    return modules;
}
