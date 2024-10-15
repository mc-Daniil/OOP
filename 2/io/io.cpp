#include "io.h"

auto checkChoice(int &choice) -> bool {
    return (choice >= 0 && choice <= 7);
}