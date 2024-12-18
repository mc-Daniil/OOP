#ifndef INC_3_WEAPONMODULE_H
#define INC_3_WEAPONMODULE_H

#include "Module.h"

using uint = unsigned int;

class WeaponModule : public Module {
private:
    uint range;
    uint chargingTime;
    bool isCharging;
public:
    WeaponModule(ModuleType type, uint energyConsumptionActive, uint energyConsumptionPassive,
                 uint slotsRequired, uint range, uint chargingTime);

    [[nodiscard]] uint getRange() const;

    void startCharging();

    void stopCharging();

    void neutralizeTarget();
};

#endif //INC_3_WEAPONMODULE_H
