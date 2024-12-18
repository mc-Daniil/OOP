/**
 * @file NetworkModule.h
 * @brief Network module class
 */
#ifndef INC_3_NETWORKMODULE_H
#define INC_3_NETWORKMODULE_H

#include <vector>
#include <memory>
#include "Module.h"

using uint = unsigned int;

/**
 * @class NetworkModule
 * @brief Represents a network module in the security system
 *
 * The network module enables communication between components of the security system.
 * It supports establishing and managing active connections and provides a commutation table
 * for routing data through intermediate nodes.
 */
class NetworkModule : public Module {
private:
    /**
     * @brief Communication range of the module
     */
    uint range;

    /**
     * @brief Maximum number of active connections
     */
    uint maxConnections;

    /**
     * @brief List of active connections
     */
    std::vector<std::shared_ptr<Module>> activeConnections;

    /**
     * @brief Commutation table for routing connections
     */
    std::vector<std::shared_ptr<Module>> commutationsTable;

public:
    /**
     * @brief Constructor for the NetworkModule class
     * @param type - Type of the module
     * @param energyConsumptionActive - Energy consumption in active mode
     * @param energyConsumptionPassive - Energy consumption in passive mode
     * @param slotsRequired - Number of slots required by the module
     * @param range - Communication range of the module
     * @param maxConnections - Maximum number of active connections
     */
    NetworkModule(ModuleType type, uint energyConsumptionActive, uint energyConsumptionPassive,
                  uint slotsRequired, uint range, uint maxConnections);

    /**
     * @brief Get the communication range of the module
     * @return Communication range as an unsigned integer
     */
    [[nodiscard]] uint getRange() const;

    /**
     * @brief Establish a connection with another module
     * @param target - Shared pointer to the module to connect to
     * @throws std::runtime_error if the maximum number of connections is exceeded
     */
    void connect(std::shared_ptr<Module> &target);

    /**
     * @brief Disconnect from an active connection
     * @param target - Shared pointer to the module to disconnect from
     * @throws std::runtime_error if the target module is not in the active connections list
     */
    void disconnect(std::shared_ptr<Module> &target);

    /**
     * @brief Get the list of active connections
     * @return Vector of shared pointers to active connections
     */
    [[nodiscard]] const std::vector<std::shared_ptr<Module>> &getActiveConnections() const;
};

#endif //INC_3_NETWORKMODULE_H
