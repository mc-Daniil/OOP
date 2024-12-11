#include "main.h"
#include "src/model/Vector.h"

int main() {
    static_assert(std::random_access_iterator<VectorIterator<int, false>>);
    static_assert(std::random_access_iterator<VectorIterator<int, true>>);
    return 0;
}