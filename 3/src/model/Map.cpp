#include "Map.h"
#include "Cell.h"

Map::Map(uint width, uint height) : shape{width, height} {
    grid.resize(height, std::vector<std::shared_ptr<Cell>>(width, nullptr));
}


void Map::setCell(std::pair<uint, uint> coords, std::shared_ptr<Cell> cell) {
    auto [x, y] = coords;
    if (x >= shape.first || y >= shape.second) {
        throw std::out_of_range("Coordinates are out of map bounds");
    }
    grid[y][x] = std::move(cell);
}


void Map::resizeMap(std::pair<uint, uint> newShape) {
    auto [newWidth, newHeight] = newShape;
    auto [currentWidth, currentHeight] = shape;

    // Увеличиваем количество строк, если необходимо
    if (newHeight > currentHeight) {
        grid.resize(newHeight, std::vector<std::shared_ptr<Cell>>(currentWidth, nullptr));
    }

    // Изменяем ширину каждой строки
    for (auto &row: grid) {
        row.resize(newWidth, nullptr);
    }

    // Обновляем текущие размеры
    shape = newShape;
}


std::pair<uint, uint> Map::getShape() const {
    return shape;
}

std::shared_ptr<Cell> Map::getCell(std::pair<uint, uint> coords) const {
    auto [x, y] = coords;
    if (x >= shape.first || y >= shape.second) {
        throw std::out_of_range("Coordinates are out of bounds");
    }
    return grid[y][x];
}