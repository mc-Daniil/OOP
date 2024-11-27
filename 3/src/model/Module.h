#ifndef INC_3_MODULE_H
#define INC_3_MODULE_H

using uint = unsigned int;

enum class ModuleType {
    NETWORK, SENSOR, WEAPON
};

class Module {
protected:
    ModuleType type;
    uint energyConsumptionActive;
    uint energyConsumptionPassive;
    uint slotsRequired;
    bool isActive;
public:
    Module(ModuleType type, uint energyConsumptionActive, uint energyConsumptionPassive, uint slotsRequired);

    virtual ~Module() = default;

    [[nodiscard]] ModuleType getType() const;

    [[nodiscard]] uint getEnergyConsumption() const;

    [[nodiscard]] uint getSlotsRequired() const;

    virtual void on();

    virtual void off();

    [[nodiscard]] bool isOn() const;

    virtual void work();
};

#endif //INC_3_MODULE_H
