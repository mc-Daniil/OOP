#include "main.h"


int main() {
    std::string filename = "map.txt";
    try {
        Map map = read_map_from_file(filename);

        std::cout << "Map contents:\n";
        show_map(map);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}