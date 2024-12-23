#include "MobilePlatform.h"
#include <algorithm>

MobilePlatform::MobilePlatform(uint x, uint y, const std::string &description, uint energyLevel, uint moduleSlots)
        : coordinates({x, y}), description(description), energyLevel(energyLevel), moduleSlots(moduleSlots), speed(0) {}

std::pair<uint, uint> MobilePlatform::getCoordinates() const {
    return coordinates;
}

void MobilePlatform::setCoordinates(uint x, uint y) {
    coordinates = {x, y};
}

std::string MobilePlatform::getDescription() const {
    return description;
}

void MobilePlatform::setDescription(const std::string &newDescription) {
    description = newDescription;
}

uint MobilePlatform::getEnergyLevel() const {
    return energyLevel;
}

void MobilePlatform::setEnergyLevel(uint newEnergyLevel) {
    energyLevel = newEnergyLevel;
}

void MobilePlatform::installModule(const std::shared_ptr<Module> &module) {
    if (modules.size() == moduleSlots) {
        throw std::runtime_error("No available slots");
    }
    if (module->getSlotsRequired() > (moduleSlots - modules.size())) {
        throw std::runtime_error("Not enough slots");
    }
    if (module->getEnergyConsumption() > energyLevel) {
        throw std::runtime_error("Not enough energy");
    }
    modules.push_back(module);
    energyLevel -= module->getEnergyConsumption();
}

void MobilePlatform::removeModule(const std::shared_ptr<Module> &module) {
    auto iterator = std::find(modules.begin(), modules.end(), module);
    if (iterator == modules.end()) {
        throw std::runtime_error("No module");
    }
    energyLevel += module->getEnergyConsumption();
    modules.erase(iterator);
}

const std::vector<std::shared_ptr<Module>> &MobilePlatform::getModules() const {
    return modules;
}

uint MobilePlatform::getSpeed() const {
    return speed;
}

void MobilePlatform::setSpeed(uint newSpeed) {
    speed = newSpeed;
}

void MobilePlatform::move(uint x, uint y, const Map &map) {
    auto currentCoordinates = getCoordinates();

    auto targetCell = map.getCell({x, y});
    if (!targetCell || !targetCell->isAccessible()) {
        throw std::runtime_error("Target cell is not accessible");
    }

    uint distance = std::abs(static_cast<int>(x) - static_cast<int>(currentCoordinates.first)) +
                    std::abs(static_cast<int>(y) - static_cast<int>(currentCoordinates.second));

    uint energyCost = distance * speed;
    if (energyCost > energyLevel) {
        throw std::runtime_error("Not enough energy to move");
    }

    energyLevel -= energyCost;
    setCoordinates(x, y);

    map.getCell(currentCoordinates)->setType(CellType::EMPTY);
    targetCell->setType(CellType::MOBACTIVEPLATFORM);
}


std::pair<uint, uint> MobilePlatform::calculateNextMove(const Map &map) {
    std::pair<uint, uint> current_coords = this->getCoordinates();
    uint x = current_coords.first;
    uint y = current_coords.second;

    // Определяем возможные смещения
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    int direction = rand() % 4;

    // Рассчитываем новые координаты с учетом скорости
    uint new_x = x + dx[direction] * speed;
    uint new_y = y + dy[direction] * speed;

    // Получаем размер карты
    auto shape = map.getShape();

    // Проверяем, не выходят ли новые координаты за пределы карты
    if (new_x < shape.first && new_y < shape.second) {
        // Проверяем, доступна ли целевая клетка для перемещения
        if (map.getCell({new_x, new_y})->isAccessible()) {
            return {new_x, new_y};
        }
    }

    // Если клетка недоступна или координаты некорректны, остаёмся на месте
    return current_coords;
}


