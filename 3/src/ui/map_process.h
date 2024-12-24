#ifndef LAB3_MAP_PROCESS_H
#define LAB3_MAP_PROCESS_H

#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <fstream>
#include <vector>
#include <memory>
#include <sstream>
#include <regex>
#include <map>
#include <string>
#include "../model/Map.h"
#include "../model/Cell.h"
#include "../model/Intruder.h"
#include "../model/MobilePlatform.h"
#include "../model/StationaryPlatform.h"

CellType charToCellType(char c);

std::vector<std::string> parseModules(const std::string &data);

extern "C" Map read_map_from_file(const std::string &filename,
                       std::vector<Intruder> &intruders,
                       std::vector<MobilePlatform> &mobilePlatforms,
                       std::vector<StationaryPlatform> &stationaryPlatforms);

extern "C" void show_map(const Map &map);

extern "C" void update_map(Map &map, std::vector<Intruder> &intruders,
                std::vector<MobilePlatform> &mobilePlatforms);

extern "C" void show_legend();

void move_intruder(Intruder &intruder, Map &map, std::mutex &map_mutex);

void move_platform(MobilePlatform &platform, Map &map, std::mutex &map_mutex);

#endif //LAB3_MAP_PROCESS_H
