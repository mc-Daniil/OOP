#ifndef INC_3_MOBILEPLATFORM_H
#define INC_3_MOBILEPLATFORM_H

#include "Platform.h"

class MobilePlatform : public Platform {
private:
    uint speed;
public:
    MobilePlatform(uint x, uint y, const std::string &description, uint energyLevel, uint moduleSlots);
    [[nodiscard]] uint getSpeed() const;
    void setSpeed(uint speed);
    void setCoordinates(uint x, uint y) override;
    void MobilePlatform::move(uint x, uint y);
};

#endif //INC_3_MOBILEPLATFORM_H
