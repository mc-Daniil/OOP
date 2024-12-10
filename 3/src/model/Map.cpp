#include "Map.h"
#include "Cell.h"

Map::Map(uint width, uint height) : shape{width, height} {
    grid.resize(height, std::vector<std::shared_ptr<Cell>>(width, nullptr));
}


auto Map::setCell(std::pair<uint, uint> coords, std::shared_ptr<Cell> cell) {
    auto [x, y] = coords;
    if (x > shape.first || y > shape.second) {
        throw std::out_of_range("Coordinates are greater than the map");
    }

    grid[x][y] = std::move(cell);
}

auto Map::resizeMap(std::pair<uint, uint> newShape) {
    // дополнить пустыми клетками
}

std::pair<uint, uint> Map::getShape() const {
    return shape;
}