#include "io.h"

auto checkChoice(int &choice) -> bool {
    return (choice >= 0 && choice <= 7);
}

auto checkAlcohol(int &alcohol) -> bool {
    return (alcohol >= 0 && alcohol <= 100);
}

auto checkVolume(int &volume) -> bool {
    return (volume > 0);
}