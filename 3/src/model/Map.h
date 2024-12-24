/**
 * @file Map.h
 * @brief Environment with cells
 */
#ifndef INC_3_ENVIRONMENT_H
#define INC_3_ENVIRONMENT_H

#include <vector>
#include <memory>
#include "Cell.h"

using uint = unsigned int;

/**
 * @class Map
 * @brief Environment with cells
 * Available operations:
 * 1) Construct
 * 2) Set cell with coordinates
 * 3) Resize map (multiple variants)
 * 4) Get width and height
 */
class Map {
private:
    /**
     * @brief Width and height
     */
    std::pair<uint, uint> shape;
    /**
     * @brief Vector of cells
     */
    std::vector<std::vector<std::shared_ptr<Cell>>> grid;
public:
    /**
     * @brief Empty constructor
     */
    Map() = default;

    /**
     * @brief Constructor of map with width and height
     * @param width - width of field
     * @param height - height of field
     */
    Map(uint width, uint height);

    /**
     * @brief Set the cell with coordinates
     * @param coords - x and y of the cell
     * @param cell - pointer to the cell
     * @throws std::out_of_range
     */
    void setCell(std::pair<uint, uint> coords, std::shared_ptr<Cell> cell);

    /**
     * @brief Resize the environment with given parameters
     * @param newShape - new width and height
     */
    void resizeMap(std::pair<uint, uint> newShape);

    /**
     * @brief Get width and height of the map
     * @return pair of width and height
     */
    [[nodiscard]] std::pair<uint, uint> getShape() const;

    /**
     * @brief Get the cell at specified coordinates
     * @param coords - pair of x and y coordinates
     * @return Shared pointer to the cell
     * @throws std::out_of_range if coordinates are out of bounds
     */
    [[nodiscard]] std::shared_ptr<Cell> getCell(std::pair<uint, uint> coords) const;

    /**
     * @brief Check if the given coordinates are valid for the map
     * @param x - x coordinate
     * @param y - y coordinate
     * @return True if the coordinates are valid, false otherwise
     */
    [[nodiscard]] bool isValidCoordinate(uint x, uint y) const {
        return x < shape.first && y < shape.second;
    }
};

#endif //INC_3_ENVIRONMENT_H
