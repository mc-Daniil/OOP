#ifndef INC_3_MOBILEPLATFORM_H
#define INC_3_MOBILEPLATFORM_H

#include "Platform.h"

class MobilePlatform : public Platform {
private:
    int speed;
public:
    MobilePlatform(uint x, uint y, const std::string &description, uint energyLevel, uint moduleSlots);
    [[nodiscard]] int getSpeed() const;
    void setSpeed(int speed);
    void setCoordinates(uint x, uint y) override;
    void work() override;
    void move(uint x, uint y);
};

#endif //INC_3_MOBILEPLATFORM_H
