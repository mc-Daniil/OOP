#ifndef INC_3_ENVIRONMENT_H
#define INC_3_ENVIRONMENT_H

#include <vector>
#include <memory>
#include "Cell.h"

using uint = unsigned int;

class Map {
private:
    std::pair<uint, uint> shape;
    std::vector<std::vector<std::shared_ptr<Cell>>> grid;
public:
    Map() = default;

    Map(uint width, uint height);

    auto setCell(std::pait<uint, uint> coords, std::shared_ptr<Cell> cell);

    auto resizeField(std::pair<uint, uint> newShape);

    [[nodiscard]] std::pair<uint, uint> getShape() const;
};

#endif //INC_3_ENVIRONMENT_H
