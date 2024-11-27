#ifndef INC_3_PLATFORM_H
#define INC_3_PLATFORM_H

#include <string>
#include <vector>
#include <memory>
#include "Module.h"

using uint = unsigned int;

class Platform {
protected:
    std::pair<uint, uint> coordinates;
    std::string description;
    uint energyLevel;
    uint moduleSlots;
    std::vector<std::shared_ptr<Module>> modules;
public:
    Platform(uint x, uint y, const std::string &description, uint energyLevel, uint moduleSlots);

    virtual ~Platform() = default;

    [[nodiscard]] std::pair<uint, uint> getCoordinates() const;

    virtual void setCoordinates(uint x, uint y);

    [[nodiscard]] std::string getDescription() const;

    void setDescription(const std::string &description);

    [[nodiscard]] uint getEnergyLevel() const;

    void setEnergyLevel(uint energyLevel);

    virtual void installModule(const std::shared_ptr<Module> &module);

    virtual void removeModule(const std::shared_ptr<Module> &module);

    [[nodiscard]] const std::vector<std::shared_ptr<Module>> &getModules() const;

    virtual void work();
};

#endif //INC_3_PLATFORM_H
