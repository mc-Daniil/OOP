#include "map_process.h"

// Функция для преобразования символа в тип клетки
CellType charToCellType(char c) {
    switch (c) {
        case '.':
            return CellType::EMPTY;
        case '#':
            return CellType::OBSTACLE;
        case 'P':
            return CellType::STATACTIVEPLATFORM;
        case 'p':
            return CellType::STATPASSIVEPLATFORM;
        case 'M':
            return CellType::MOBACTIVEPLATFORM;
        case 'm':
            return CellType::MOBPASSIVEPLATFORM;
        case 'N':
            return CellType::NETACTIVE;
        case 'n':
            return CellType::NETPASSIVE;
        case 'O':
            return CellType::SENSOROPTICACTIVE;
        case 'o':
            return CellType::SENSOROPTICPASSIVE;
        case 'X':
            return CellType::SENSORXRAYACTIVE;
        case 'x':
            return CellType::SENSORXRAYPASSIVE;
        case 'W':
            return CellType::WEAPONACTIVE;
        case 'w':
            return CellType::WEAPONPASSIVE;
        case 'I':
            return CellType::INTRUDER;
        default:
            throw std::invalid_argument("Unknown character in map file");
    }
}


Map read_map_from_file(const std::string &filename, std::vector<Intruder> &intruders,
                       std::vector<MobilePlatform> &platforms) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening map file");
    }

    std::string line;
    std::vector<std::string> lines;

    // Считываем строки из файла
    while (std::getline(file, line)) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }

    file.close();

    if (lines.empty()) {
        throw std::runtime_error("Map file is empty");
    }

    // Определяем размеры карты
    uint height = lines.size();
    uint width = 0;
    for (const auto &line: lines) {
        width = std::max(width, static_cast<uint>(line.length()));
    }

    // Создаём карту
    Map map(width, height);
    map.resizeMap({width, height});

    for (uint y = 0; y < height; ++y) {
        const auto &line = lines[y];
        for (uint x = 0; x < line.length(); ++x) {
            char c = line[x];
            try {
                CellType type = charToCellType(c);
                std::shared_ptr<Cell> cell = std::make_shared<Cell>(type, x, y);
                map.setCell({x, y}, cell);

                // Создание объектов Intruder и MobilePlatform
                if (type == CellType::INTRUDER) {
                    intruders.emplace_back(x, y);
                } else if (type == CellType::MOBACTIVEPLATFORM) {
                    platforms.emplace_back(x, y, "Samorez", 100, 3);
                }
            } catch (const std::exception &e) {
                std::cerr << "Error processing cell at (" << x << ", " << y << "): " << e.what() << std::endl;
                throw;
            }
        }
    }

    return map;
}


// Функция для отображения карты на экране
void show_map(const Map &map) {
    auto [width, height] = map.getShape();

    for (uint y = 0; y < height; ++y) {
        for (uint x = 0; x < width; ++x) {
            std::shared_ptr<Cell> cell = map.getCell({x, y});
            if (cell) {
                switch (cell->getType()) {
                    case CellType::EMPTY:
                        std::cout << ".";
                        break;
                    case CellType::OBSTACLE:
                        std::cout << "#";
                        break;
                    case CellType::STATACTIVEPLATFORM:
                        std::cout << "P";
                        break;
                    case CellType::STATPASSIVEPLATFORM:
                        std::cout << "p";
                        break;
                    case CellType::MOBACTIVEPLATFORM:
                        std::cout << "M";
                        break;
                    case CellType::MOBPASSIVEPLATFORM:
                        std::cout << "m";
                        break;
                    case CellType::NETACTIVE:
                        std::cout << "N";
                        break;
                    case CellType::NETPASSIVE:
                        std::cout << "n";
                        break;
                    case CellType::SENSOROPTICACTIVE:
                        std::cout << "O";
                        break;
                    case CellType::SENSOROPTICPASSIVE:
                        std::cout << "o";
                        break;
                    case CellType::SENSORXRAYACTIVE:
                        std::cout << "X";
                        break;
                    case CellType::SENSORXRAYPASSIVE:
                        std::cout << "x";
                        break;
                    case CellType::WEAPONACTIVE:
                        std::cout << "W";
                        break;
                    case CellType::WEAPONPASSIVE:
                        std::cout << "w";
                        break;
                    case CellType::INTRUDER:
                        std::cout << "I";
                        break;
                    default:
                        std::cerr << "Error: Unknown cell type!" << std::endl;
                        std::cout << "?";
                        break;
                }
            } else {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
}


// Функция перемещения для Intruder
void move_intruder(Intruder &intruder, Map &map, std::mutex &map_mutex) {
    try {
        auto current_coords = intruder.getCoordinates();
        auto next_coords = intruder.calculateNextMove(map);

        std::lock_guard<std::mutex> lock(map_mutex);
        if (map.getCell(next_coords)->isAccessible()) {
            map.getCell(current_coords)->setType(CellType::EMPTY);
            map.getCell(next_coords)->setType(CellType::INTRUDER);
            intruder.setCoordinates(next_coords.first, next_coords.second);
        } else {
            std::cout << "Cell (" << next_coords.first << ", " << next_coords.second
                      << ") is not accessible for Intruder. Stays in place.\n";
        }
    } catch (const std::exception &e) {
        std::cerr << "Error during intruder movement: " << e.what() << std::endl;
    }
}

// Функция перемещения для MobilePlatform
void move_platform(MobilePlatform &platform, Map &map, std::mutex &map_mutex) {
    try {
        auto current_coords = platform.getCoordinates();
        auto next_coords = platform.calculateNextMove(map);

        std::lock_guard<std::mutex> lock(map_mutex);
        if (map.getCell(next_coords)->isAccessible()) {
            map.getCell(current_coords)->setType(CellType::EMPTY);
            map.getCell(next_coords)->setType(CellType::MOBACTIVEPLATFORM);
            platform.setCoordinates(next_coords.first, next_coords.second);
        } else {
            std::cout << "Cell (" << next_coords.first << ", " << next_coords.second
                      << ") is not accessible for MobilePlatform. Stays in place.\n";
        }
    } catch (const std::exception &e) {
        std::cerr << "Error during platform movement: " << e.what() << std::endl;
    }
}

// Основная функция обновления карты
void update_map(Map &map, std::vector<Intruder> &intruders, std::vector<MobilePlatform> &platforms) {
    std::mutex map_mutex; // Мьютекс для защиты карты

    // Векторы потоков
    std::vector<std::thread> threads;

    // Создаём потоки для Intruders
    for (auto &intruder: intruders) {
        threads.emplace_back(move_intruder, std::ref(intruder), std::ref(map), std::ref(map_mutex));
    }

    // Создаём потоки для MobilePlatforms
    for (auto &platform: platforms) {
        threads.emplace_back(move_platform, std::ref(platform), std::ref(map), std::ref(map_mutex));
    }

    // Ожидаем завершения всех потоков
    for (auto &thread: threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}
