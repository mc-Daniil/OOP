#include "main.h"
#include <thread>
#include <chrono>

void update_map(Map &map, Intruder &intruder) {
    try {
        auto current_coords = intruder.getCoordinates();

        auto next_coords = intruder.calculateNextMove(map);

        if (map.getCell(next_coords)->isAccessible()) {
            map.getCell(current_coords)->setType(CellType::EMPTY);
            map.getCell(next_coords)->setType(CellType::INTRUDER);
            intruder.setCoordinates(next_coords.first, next_coords.second);
        } else {
            std::cout << "Cell (" << next_coords.first << ", " << next_coords.second
                      << ") is not accessible. Intruder stays in place.\n";
        }
    } catch (const std::exception &e) {
        std::cerr << "Error during intruder movement: " << e.what() << std::endl;
    }
}

int main() {
    std::string filename = "map.txt";
    try {
        Map map = read_map_from_file(filename);
        Intruder intruder(1, 1);

        map.getCell({1, 1})->setType(CellType::INTRUDER);

        std::cout << "Initial map state:\n";
        show_map(map);

        while (true) {
            std::cout << "Updating map...\n";
            update_map(map, intruder);
            show_map(map);

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
