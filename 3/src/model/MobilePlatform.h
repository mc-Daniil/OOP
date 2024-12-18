#ifndef INC_3_MOBILEPLATFORM_H
#define INC_3_MOBILEPLATFORM_H

#include "Platform.h"

class MobilePlatform : public Platform {
private:
    std::pair<uint, uint> coordinates;
    std::string description;
    uint energyLevel;
    uint moduleSlots;
    uint speed;
    std::vector<std::shared_ptr<Module>> modules;

public:
    MobilePlatform(uint x, uint y, const std::string &description, uint energyLevel, uint moduleSlots);

    [[nodiscard]] std::pair<uint, uint> getCoordinates() const override;

    void setCoordinates(uint x, uint y) override;

    [[nodiscard]] std::string getDescription() const override;

    void setDescription(const std::string &description) override;

    [[nodiscard]] uint getEnergyLevel() const override;

    void setEnergyLevel(uint energyLevel) override;

    void installModule(const std::shared_ptr<Module> &module) override;

    void removeModule(const std::shared_ptr<Module> &module) override;

    [[nodiscard]] const std::vector<std::shared_ptr<Module>> &getModules() const override;

    [[nodiscard]] uint getSpeed() const;

    void setSpeed(uint speed);

    void move(uint x, uint y);
};

#endif //INC_3_MOBILEPLATFORM_H
