#ifndef INC_3_STATIONARYPLATFORM_H
#define INC_3_STATIONARYPLATFORM_H

#include "Platform.h"

class StationaryPlatform : public Platform {
private:
    std::pair<uint, uint> coordinates;
    std::string description;
    uint energyLevel;
    uint moduleSlots;
    std::vector<std::shared_ptr<Module>> modules;

public:
    StationaryPlatform(uint x, uint y, const std::string &description, uint energyLevel, uint moduleSlots);

    [[nodiscard]] std::pair<uint, uint> getCoordinates() const override;

    void setCoordinates(uint x, uint y) override;

    [[nodiscard]] std::string getDescription() const override;

    void setDescription(const std::string &description) override;

    [[nodiscard]] uint getEnergyLevel() const override;

    void setEnergyLevel(uint energyLevel) override;

    void installModule(const std::shared_ptr<Module> &module) override;

    void removeModule(const std::shared_ptr<Module> &module) override;

    [[nodiscard]] const std::vector<std::shared_ptr<Module>> &getModules() const override;
};

#endif //INC_3_STATIONARYPLATFORM_H
