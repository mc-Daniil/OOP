#include "MobilePlatform.h"
#include <stdexcept>

MobilePlatform::MobilePlatform(uint x, uint y, const std::string &description, uint energyLevel, uint moduleSlots)
        : Platform(x, y, description, energyLevel, moduleSlots), speed(0) {}

uint MobilePlatform::getSpeed() const {
    return speed;
}

void MobilePlatform::setSpeed(uint newSpeed) {
    speed = newSpeed;
}

void MobilePlatform::setCoordinates(uint x, uint y) {
    coordinates = {x, y};
}

void MobilePlatform::move(uint x, uint y) {
    // ?..
    setCoordinates(x, y);
}