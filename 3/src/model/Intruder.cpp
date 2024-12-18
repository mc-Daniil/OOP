#include "Intruder.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

/**
 * @brief Constructor for the Intruder class
 * @param x - Initial x-coordinate
 * @param y - Initial y-coordinate
 */
Intruder::Intruder(uint x, uint y) : coordinates(x, y), state("wandering") {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

/**
 * @brief Get the current coordinates of the intruder
 * @return Pair of x and y coordinates
 */
std::pair<uint, uint> Intruder::getCoordinates() const {
    return coordinates;
}

/**
 * @brief Set the coordinates of the intruder
 * @param x - New x-coordinate
 * @param y - New y-coordinate
 */
void Intruder::setCoordinates(uint x, uint y) {
    coordinates = {x, y};
}

/**
 * @brief Get the current state of the intruder
 * @return State as a string
 */
std::string Intruder::getState() const {
    return state;
}

/**
 * @brief Set the state of the intruder
 * @param state - New state
 */
void Intruder::setState(const std::string &newState) {
    state = newState;
}

/**
 * @brief Move the intruder randomly within the environment
 * @param map - Reference to the environment map
 */
void Intruder::moveRandomly(const Map &map) {
    std::vector<std::pair<int, int>> directions = {{-1, 0},
                                                   {1,  0},
                                                   {0,  -1},
                                                   {0,  1}};
    std::shuffle(directions.begin(), directions.end(), std::mt19937(std::random_device()()));

    for (const auto &[dx, dy]: directions) {
        uint newX = coordinates.first + dx;
        uint newY = coordinates.second + dy;

        if (map.getShape().first > newX && map.getShape().second > newY &&
            map.getCell({newX, newY})->isAccessible()) {
            setCoordinates(newX, newY);
            return;
        }
    }
}

/**
 * @brief Move the intruder to evade security platforms
 * @param map - Reference to the environment map
 * @param platforms - List of security platforms
 */
void Intruder::moveToEvade(const Map &map, const std::vector<std::shared_ptr<Platform>> &platforms) {
    int dx = 0, dy = 0;

    for (const auto &platform: platforms) {
        auto [px, py] = platform->getCoordinates();
        dx += static_cast<int>(coordinates.first - px);
        dy += static_cast<int>(coordinates.second - py);
    }

    if (platforms.size() > 0) {
        dx /= static_cast<int>(platforms.size());
        dy /= static_cast<int>(platforms.size());
    }

    uint newX = coordinates.first + (dx > 0 ? 1 : (dx < 0 ? -1 : 0));
    uint newY = coordinates.second + (dy > 0 ? 1 : (dy < 0 ? -1 : 0));

    if (map.getShape().first > newX && map.getShape().second > newY &&
        map.getCell({newX, newY})->isAccessible()) {
        setCoordinates(newX, newY);
    }
}

/**
 * @brief Determine the next coordinates based on behavior
 * @param map - Reference to the environment map
 * @param platforms - List of security platforms
 * @return Pair of new x and y coordinates
 */
std::pair<uint, uint>
Intruder::getNextCoordinates(const Map &map, const std::vector<std::shared_ptr<Platform>> &platforms) {
    if (state == "wandering") {
        moveRandomly(map);
    } else if (state == "escaping") {
        moveToEvade(map, platforms);
    }

    return coordinates;
}

std::pair<uint, uint> Intruder::calculateNextMove(const Map &map) {
    std::pair<uint, uint> current_coords = this->getCoordinates();
    uint x = current_coords.first;
    uint y = current_coords.second;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    int direction = rand() % 4;

    uint new_x = x + dx[direction];
    uint new_y = y + dy[direction];

    auto shape = map.getShape();
    if (new_x < shape.first && new_y < shape.second) {
        return {new_x, new_y};
    }

    return current_coords;
}
