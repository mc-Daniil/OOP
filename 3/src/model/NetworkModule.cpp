#include "NetworkModule.h"
#include <stdexcept>
#include <algorithm>

NetworkModule::NetworkModule(ModuleType type, uint energyConsumptionActive, uint energyConsumptionPassive,
                             uint slotsRequired, uint range, uint maxConnections) : Module(type,
                                                                                           energyConsumptionActive,
                                                                                           energyConsumptionPassive,
                                                                                           slotsRequired), range(range),
                                                                                    maxConnections(maxConnections) {}

uint NetworkModule::getRange() const {
    return range;
}

void NetworkModule::connect(std::shared_ptr<Module> &target) {
    if (activeConnections.size() == maxConnections) {
        throw std::runtime_error("Cannot establish connection: maximum number of connections reached.");
    }

    if (std::find(activeConnections.begin(), activeConnections.end(), target) != activeConnections.end()) {
        throw std::runtime_error("Connection already exists.");
    }
    activeConnections.push_back(target);
}

void NetworkModule::disconnect(std::shared_ptr<Module> &target) {
    auto connection = std::find(activeConnections.begin(), activeConnections.end(), target);
    if (connection == activeConnections.end()) {
        throw std::runtime_error("Connection not found.");
    }
    activeConnections.erase(connection);
}

const std::vector<std::shared_ptr<Module>> &NetworkModule::getActiveConnections() const {
    return activeConnections;
}

