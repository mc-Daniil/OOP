#ifndef INC_3_NETWORKMODULE_H
#define INC_3_NETWORKMODULE_H

#include <vector>
#include <memory>
#include "Module.h"

using uint = unsigned int;

class NetworkModule : public Module {
private:
    uint range;
    uint maxConnections;
    std::vector<std::shared_ptr<Module>> activeConnections;
    std::vector<std::shared_ptr<Module>> commutationsTable;
public:
    NetworkModule(ModuleType type, uint energyConsumptionActive, uint energyConsumptionPassive,
                  uint slotsRequired, uint range, uint maxConnections);

    [[nodiscard]] uint getRange() const;

    void connect(std::shared_ptr<Module> &target);

    void disconnect(std::shared_ptr<Module> &target);

    [[nodiscard]] const std::vector<std::shared_ptr<Module>> &getActiveConnections() const;
};

#endif //INC_3_NETWORKMODULE_H
