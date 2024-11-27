#ifndef INC_3_CELL_H
#define INC_3_CELL_H

enum class CellType {
    EMPTY, OBSTACLE, COMPONENT, INTRUDER
};
using uint = unsigned int;

class Cell {
private:
    CellType type;
    std::pair<uint, uint> coordinates;
public:
    Cell() = default;

    Cell(CellType type, uint x, uint y);

    [[nodiscard]] CellType getType() const;

    auto setType(CellType newType);

    [[nodiscard]]std::pair<uint, uint> getCoordinates() const;
};

#endif //INC_3_CELL_H
