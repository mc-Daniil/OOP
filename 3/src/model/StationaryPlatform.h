#ifndef INC_3_STATIONARYPLATFORM_H
#define INC_3_STATIONARYPLATFORM_H

#include "Platform.h"

using uint = unsigned int;

class StationaryPlatform : public Platform {
public:
    StationaryPlatform(uint x, uint y, const std::string &description, uint energyLevel, uint moduleSlots);
    void setCoordinates(uint x, uint y) override;
    void work() override;
};

#endif //INC_3_STATIONARYPLATFORM_H
