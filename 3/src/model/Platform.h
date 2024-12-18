#ifndef INC_3_PLATFORM_H
#define INC_3_PLATFORM_H

#include <string>
#include <vector>
#include <memory>
#include "Module.h"

using uint = unsigned int;

class Platform {
public:
    virtual ~Platform() = default;

    [[nodiscard]] virtual std::pair<uint, uint> getCoordinates() const = 0;

    virtual void setCoordinates(uint x, uint y) = 0;

    [[nodiscard]] virtual std::string getDescription() const = 0;

    virtual void setDescription(const std::string &description) = 0;

    [[nodiscard]] virtual uint getEnergyLevel() const = 0;

    virtual void setEnergyLevel(uint energyLevel) = 0;

    virtual void installModule(const std::shared_ptr<Module> &module) = 0;

    virtual void removeModule(const std::shared_ptr<Module> &module) = 0;

    [[nodiscard]] virtual const std::vector<std::shared_ptr<Module>> &getModules() const = 0;
};

#endif //INC_3_PLATFORM_H
