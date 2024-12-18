#ifndef LAB3_MAP_PROCESS_H
#define LAB3_MAP_PROCESS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "../model/Map.h"
#include "../model/Cell.h"

CellType charToCellType(char c);

Map read_map_from_file(const std::string &filename);

void show_map(const Map &map);

#endif //LAB3_MAP_PROCESS_H
