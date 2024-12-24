#include "main.h"
#include <thread>

int main() {
    std::string filename = "map.txt";
    try {
        std::vector<Intruder> intruders;
        std::vector<MobilePlatform> mobilePlatforms;
        std::vector<StationaryPlatform> stationaryPlatforms;
        std::vector<QuantumPlatform> quantumPlatforms;


        Map map = read_map_from_file(filename, intruders, mobilePlatforms, stationaryPlatforms, quantumPlatforms);

        if (!mobilePlatforms.empty()) {
            mobilePlatforms[0].setSpeed(1);
        }

        std::cout << "Initial map state:\n";
        show_legend();
        show_map(map);

        while (true) {
            std::cout << "Updating map...\n";

            update_map(map, intruders, mobilePlatforms, quantumPlatforms);

            show_map(map);

            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

