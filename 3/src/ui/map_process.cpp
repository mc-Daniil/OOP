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
        case 'M':
            return CellType::MOBACTIVEPLATFORM;
        case 'I':
            return CellType::INTRUDER;
        case 'Q':
            return CellType::QUANTUMPLATFORM;
        case 'W':
            return CellType::WEAPONACTIVE;
        case 'O':
            return CellType::SENSOROPTICACTIVE;
        default:
            std::cout << c << std::endl;
            throw std::invalid_argument("Unknown cell type in map file");
    }
}


std::vector<std::string> parseModules(const std::string &data) {
    std::vector<std::string> modules;
    std::stack<char> brackets;
    std::string module;

    for (char ch: data) {
        if (ch == '(') {
            brackets.push(ch);
        } else if (ch == ')') {
            if (brackets.empty()) {
                throw std::invalid_argument("Mismatched parentheses in module data");
            }
            brackets.pop();
        }

        if (brackets.empty() && ch == ',') {
            modules.push_back(module);
            module.clear();
        } else {
            module += ch;
        }
    }

    if (!module.empty()) {
        modules.push_back(module);
    }

    if (!brackets.empty()) {
        throw std::invalid_argument("Unclosed parentheses in module data");
    }

    return modules;
}

// Чтение карты из файла
Map read_map_from_file(const std::string &filename,
                       std::vector<Intruder> &intruders,
                       std::vector<MobilePlatform> &mobilePlatforms,
                       std::vector<StationaryPlatform> &stationaryPlatforms,
                       std::vector<QuantumPlatform> &quantumPlatforms) {
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

    uint height = lines.size();
    uint width = 0;

    for (const auto &line: lines) {
        std::stringstream ss(line);
        std::string cell;
        uint current_width = 0;
        while (std::getline(ss, cell, ';')) {
            current_width++;
        }
        width = std::max(width, current_width);
    }

    Map map(width, height);
    map.resizeMap({width, height});

    std::regex cell_regex(R"(([PMQI#\.Q])(\((.*)\))?)");

    for (uint y = 0; y < height; ++y) {
        const auto &line = lines[y];
        std::stringstream ss(line);
        std::string cell;
        uint x = 0;

        while (std::getline(ss, cell, ';')) {
            try {
                std::cout << "Processing cell at (" << x << ", " << y << "): \"" << cell << "\"" << std::endl;

                std::smatch match;
                if (std::regex_match(cell, match, cell_regex)) {
                    char type_char = match[1].str()[0];
                    std::string module_data = match[3].str();

                    CellType type = charToCellType(type_char);
                    std::shared_ptr<Cell> cell_ptr = std::make_shared<Cell>(type, x, y);
                    map.setCell({x, y}, cell_ptr);

                    if (!module_data.empty()) {
                        auto modules = parseModules(module_data);
                        for (const auto &module: modules) {
                            std::cout << "  Found module: " << module << std::endl;
                            if (type == CellType::MOBACTIVEPLATFORM) {
                                mobilePlatforms.emplace_back(x, y, module, 100, 3);
                            } else if (type == CellType::STATACTIVEPLATFORM) {
                                stationaryPlatforms.emplace_back(x, y, module, 100, 3);
                            } else if (type == CellType::QUANTUMPLATFORM) {
                                quantumPlatforms.emplace_back(x, y, std::string(module), 100, 1);

                            }
                        }
                    }

                    if (type == CellType::INTRUDER) {
                        intruders.emplace_back(x, y);
                    }
                } else {
                    throw std::invalid_argument("Invalid cell format");
                }
            } catch (const std::exception &e) {
                std::cerr << "Error processing cell at (" << x << ", " << y << "): " << e.what() << std::endl;
                throw;
            }
            x++;
        }
    }

    return map;
}

// Добавляем поддержку цветов (опционально)
#ifdef _WIN32
#include <windows.h>
void enableAnsiColors() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;

    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}
#else

void enableAnsiColors() {}

#endif


// Цвета для типов ячеек
const std::map<CellType, std::string> cellColors = {
        {CellType::EMPTY,               "\033[0;37m"},
        {CellType::OBSTACLE,            "\033[1;30m"},
        {CellType::STATACTIVEPLATFORM,  "\033[0;32m"},
        {CellType::STATPASSIVEPLATFORM, "\033[0;34m"},
        {CellType::MOBACTIVEPLATFORM,   "\033[1;32m"},
        {CellType::MOBPASSIVEPLATFORM,  "\033[1;34m"},
        {CellType::NETACTIVE,           "\033[0;33m"},
        {CellType::NETPASSIVE,          "\033[1;33m"},
        {CellType::SENSOROPTICACTIVE,   "\033[0;36m"},
        {CellType::SENSOROPTICPASSIVE,  "\033[1;36m"},
        {CellType::SENSORXRAYACTIVE,    "\033[0;35m"},
        {CellType::SENSORXRAYPASSIVE,   "\033[1;35m"},
        {CellType::WEAPONACTIVE,        "\033[0;31m"},
        {CellType::WEAPONPASSIVE,       "\033[1;31m"},
        {CellType::INTRUDER,            "\033[1;37m"},
        {CellType::QUANTUMPLATFORM,     "\033[0;35m"}, // Цвет для квантовой платформы
};


// Сброс цвета
const std::string resetColor = "\033[0m";

void show_map(const Map &map) {
    enableAnsiColors();

    auto [width, height] = map.getShape();

    // Верхняя рамка
    std::cout << "   ";
    for (uint x = 0; x < width; ++x) {
        std::cout << (x % 10); // Номера колонок (по модулю 10)
    }
    std::cout << "\n  +" << std::string(width, '-') << "+\n"; // Верхняя рамка карты

    for (uint y = 0; y < height; ++y) {
        std::cout << (y % 10) << " |"; // Номер строки (по модулю 10)
        for (uint x = 0; x < width; ++x) {
            std::shared_ptr<Cell> cell = map.getCell({x, y});
            if (cell) {
                auto type = cell->getType();
                auto color = cellColors.count(type) ? cellColors.at(type) : "";
                std::cout << color;

                switch (type) {
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
                    case CellType::QUANTUMPLATFORM:
                        std::cout << "Q";
                        break;
                    default:
                        std::cout << "?";
                        break;
                }

                std::cout << resetColor;
            } else {
                std::cout << " ";
            }
        }
        std::cout << "|" << std::endl; // Правая рамка карты
    }

    // Нижняя рамка
    std::cout << "  +" << std::string(width, '-') << "+\n";
}


// Легенда
void show_legend() {
    std::cout << "Legend:\n";
    std::cout << "  . - Empty\n";
    std::cout << "  # - Obstacle\n";
    std::cout << "  P - Static Active Platform\n";
    std::cout << "  p - Static Passive Platform\n";
    std::cout << "  M - Mobile Active Platform\n";
    std::cout << "  m - Mobile Passive Platform\n";
    std::cout << "  I - Intruder\n";
    std::cout << "  N, n - Network\n";
    std::cout << "  O, o - Optical Sensor\n";
    std::cout << "  X, x - X-ray Sensor\n";
    std::cout << "  W, w - Weapon\n";
    std::cout << "  Q - Quantum Platform\n";
    std::cout << std::endl;
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

void update_map(Map &map, std::vector<Intruder> &intruders,
                std::vector<MobilePlatform> &mobilePlatforms,
                std::vector<QuantumPlatform> &quantumPlatforms) {
    std::mutex map_mutex; // Мьютекс для защиты карты

    std::vector<std::thread> threads;

    // Создаем потоки для Intruders
    for (auto &intruder: intruders) {
        threads.emplace_back(move_intruder, std::ref(intruder), std::ref(map), std::ref(map_mutex));
    }

    // Создаем потоки для MobilePlatforms
    for (auto &platform: mobilePlatforms) {
        threads.emplace_back(move_platform, std::ref(platform), std::ref(map), std::ref(map_mutex));
    }

    // Создаем потоки для QuantumPlatforms
    for (auto &platform: quantumPlatforms) {
        threads.emplace_back(move_quantum_platform, std::ref(platform), std::ref(map),
                             std::ref(map_mutex), std::ref(intruders));
    }

    // Ожидаем завершения всех потоков
    for (auto &thread: threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}


void move_quantum_platform(QuantumPlatform &platform, Map &map, std::mutex &map_mutex,
                           std::vector<Intruder> &intruders) {
    try {
        auto current_coords = platform.getCoordinates();
        auto next_coords = platform.calculateNextMove(map); // Реализуйте метод calculateNextMove

        std::lock_guard<std::mutex> lock(map_mutex);

        if (map.getCell(next_coords)->isAccessible()) {
            // Телепортируем нарушителей
            std::vector<std::pair<uint, uint>> intruderPositions;
            for (auto &intruder: intruders) {
                if (platform.isWithinDetectionRadius(intruder.getCoordinates())) { // Реализуйте isWithinDetectionRadius
                    intruderPositions.push_back(intruder.getCoordinates());
                    intruder.setCoordinates(next_coords.first, next_coords.second);
                }
            }

            platform.teleportIntruders(intruderPositions);

            // Обновляем карту
            map.getCell(current_coords)->setType(CellType::EMPTY);
            map.getCell(next_coords)->setType(CellType::QUANTUMPLATFORM);
            platform.setCoordinates(next_coords.first, next_coords.second);
        } else {
            std::cout << "Cell (" << next_coords.first << ", " << next_coords.second
                      << ") is not accessible for QuantumPlatform. Stays in place.\n";
        }
    } catch (const std::exception &e) {
        std::cerr << "Error during quantum platform movement: " << e.what() << std::endl;
    }
}
