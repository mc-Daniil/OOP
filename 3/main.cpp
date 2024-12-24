#include "main.h"
#include <thread>
#include <dlfcn.h>

typedef Map (*read_map_from_file_func)(const std::string&, std::vector<Intruder>&, std::vector<MobilePlatform>&, std::vector<StationaryPlatform>&);
typedef void (*show_legend_func)();
typedef void (*show_map_func)(const Map&);
typedef void (*update_map_func)(Map&, std::vector<Intruder>&, std::vector<MobilePlatform>&);
typedef void (*set_speed_func)(MobilePlatform&, unsigned int);

int main() {
    std::string filename = "/mnt/d/code/c++/b23516_rudakov.da/3/cmake-build-wsl/map.txt";
    void* model_handle = nullptr;
    void* ui_handle = nullptr;

    try {
        model_handle = dlopen("/mnt/d/code/c++/b23516_rudakov.da/3/cmake-build-wsl/lib/libmodel.so", RTLD_LAZY);
        if (!model_handle) {
            throw std::runtime_error("Failed to load the model library: " + std::string(dlerror()));
        }

        ui_handle = dlopen("/mnt/d/code/c++/b23516_rudakov.da/3/cmake-build-wsl/lib/libui.so", RTLD_LAZY);
        if (!ui_handle) {
            throw std::runtime_error("Failed to load the UI library: " + std::string(dlerror()));
        }

        read_map_from_file_func read_map_from_file = (read_map_from_file_func)dlsym(ui_handle, "read_map_from_file");
        if (!read_map_from_file) {
            throw std::runtime_error("Failed to find function 'read_map_from_file' in model: " + std::string(dlerror()));
        }

        show_legend_func show_legend = (show_legend_func)dlsym(ui_handle, "show_legend");
        if (!show_legend) {
            throw std::runtime_error("Failed to find function 'show_legend' in UI: " + std::string(dlerror()));
        }

        show_map_func show_map = (show_map_func)dlsym(ui_handle, "show_map");
        if (!show_map) {
            throw std::runtime_error("Failed to find function 'show_map' in UI: " + std::string(dlerror()));
        }

        update_map_func update_map = (update_map_func)dlsym(ui_handle, "update_map");
        if (!update_map) {
            throw std::runtime_error("Failed to find function 'update_map' in UI: " + std::string(dlerror()));
        }

        std::vector<Intruder> intruders;
        std::vector<MobilePlatform> mobilePlatforms;
        std::vector<StationaryPlatform> stationaryPlatforms;

        Map map = read_map_from_file(filename, intruders, mobilePlatforms, stationaryPlatforms);

        std::cout << "Initial map state:\n";
        show_legend();
        show_map(map);

        while (true) {
            std::cout << "Updating map...\n";
            update_map(map, intruders, mobilePlatforms);
            show_map(map);
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }

        dlclose(model_handle);
        dlclose(ui_handle);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        if (model_handle) {
            dlclose(model_handle);
        }
        if (ui_handle) {
            dlclose(ui_handle);
        }
    }

    return 0;
}
