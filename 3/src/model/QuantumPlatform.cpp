#include "QuantumPlatform.h"

void QuantumPlatform::swapWith(QuantumPlatform &other) {
    std::swap(x, other.x);
    std::swap(y, other.y);
    std::cout << "Swapped (" << x << "," << y << ") and (" << other.x << "," << other.y << ")" << std::endl;
}

void QuantumPlatform::teleportIntruders(std::vector<std::pair<uint, uint>> &intruderPositions) {
    for (auto &pos : intruderPositions) {
        uint distance = static_cast<uint>(std::sqrt(std::pow(pos.first - x, 2) + std::pow(pos.second - y, 2)));
        if (distance <= detectionRadius) {
            pos = {x, y};
            std::cout << "Intruder teleported to platform at (" << x << ", " << y << ")." << std::endl;
        }
    }
}
