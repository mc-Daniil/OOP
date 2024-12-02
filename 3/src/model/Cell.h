/**
 * @file Cell.h
 * @brief File with cell, map consists of cells
 */
#ifndef INC_3_CELL_H
#define INC_3_CELL_H

#include <utility>
/**
 * @enum CellType
 * @brief Types of cells
 * EMPTY - obvious
 * OBSTACLE - a wall, intruder can't go through
 * COMPONENT - sensor or weapon
 * INTRUDER - player
 */
enum class CellType {
    EMPTY, OBSTACLE, COMPONENT, INTRUDER
};
using uint = unsigned int;
/**
 * @class Cell
 * @brief Map consists of cells
 */
class Cell {
private:
    /**
     * @brief  Type of the cell
     */
    CellType type;
    /**
     * @brief x and y of the cell
     */
    std::pair<uint, uint> coordinates{};
public:
    /**
     * @brief Empty constructor of empty cell with (0, 0) coords
     */
    Cell();

    /**
     * @brief Constructor of cell with type and coords
     * @param type - type of the cell
     * @param x
     * @param y
     */
    Cell(CellType type, uint x, uint y);

    /**
     * @brief Get type of the cell
     * @return CellType
     */
    [[nodiscard]] CellType getType() const;

    /**
     * @brief Set type of the cell
     * @param newType - type of the cell
     * @throws std::out_of_range
     */
    auto setType(CellType newType);

    /**
     * @brief Get x and y of the cell
     * @return std::pair of x, y
     */
    [[nodiscard]]std::pair<uint, uint> getCoordinates() const;
};

#endif //INC_3_CELL_H
