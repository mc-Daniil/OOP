#ifndef INC_3_BEHAVIOURALGORITHM_H
#define INC_3_BEHAVIOURALGORITHM_H

#include <utility>

using uint = unsigned int;

class BehaviourAlgorithm {
public:
    [[nodiscard]] std::pair<uint, uint> getNextPosition(std::pair<uint, uint> currentCoords);
};

#endif //INC_3_BEHAVIOURALGORITHM_H
