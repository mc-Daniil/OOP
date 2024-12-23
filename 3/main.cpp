#include "main.h"
#include <thread>

int main() {
    std::string filename = "map.txt";
    try {
        std::vector<Intruder> intruders;
        std::vector<MobilePlatform> platforms;

        // Считываем карту и создаём объекты
        Map map = read_map_from_file(filename, intruders, platforms);

        // Пример настройки MobilePlatform
        if (!platforms.empty()) {
            platforms[0].setSpeed(1);
        }

        std::cout << "Initial map state:\n";
        show_map(map);

        while (true) {
            std::cout << "Updating map...\n";

            // Обновление карты для всех объектов
            update_map(map, intruders, platforms);

            // Отображение карты
            show_map(map);

            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

