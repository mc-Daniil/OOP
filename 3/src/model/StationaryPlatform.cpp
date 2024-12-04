#include <stdexcept>
#include "StationaryPlatform.h"

StationaryPlatform::StationaryPlatform(uint x, uint y, const std::string &description, uint energyLevel,
                                       uint moduleSlots) : Platform(x, y, description, energyLevel, moduleSlots) {}

void StationaryPlatform::setCoordinates(uint x, uint y) {
    throw std::runtime_error("Stationary platform can't move");
}

