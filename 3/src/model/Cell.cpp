#include "Cell.h"
#include <stdexcept>

Cell::Cell() : type(CellType::EMPTY), coordinates(0, 0) {}

Cell::Cell(CellType type, uint x, uint y) : type(type), coordinates(x, y) {}

CellType Cell::getType() const {
    return type;
}

auto Cell::setType(CellType newType) {
    if (newType < CellType::EMPTY || newType > CellType::INTRUDER) {
        throw std::out_of_range("No such type");
    }
    type = newType;
}

std::pair<uint, uint> Cell::getCoordinates() const {
    return coordinates;
}

