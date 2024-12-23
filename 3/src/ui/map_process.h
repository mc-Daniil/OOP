#ifndef LAB3_MAP_PROCESS_H
#define LAB3_MAP_PROCESS_H

#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <fstream>
#include <vector>
#include <memory>
#include "../model/Map.h"
#include "../model/Cell.h"
#include "../model/Intruder.h"
#include "../model/MobilePlatform.h"

CellType charToCellType(char c);

Map read_map_from_file(const std::string &filename);

void show_map(const Map &map);

void update_map(Map &map, std::vector<Intruder> &intruders, std::vector<MobilePlatform> &platforms);

Map read_map_from_file(const std::string &filename, std::vector<Intruder> &intruders,
                       std::vector<MobilePlatform> &platforms);

#endif //LAB3_MAP_PROCESS_H
