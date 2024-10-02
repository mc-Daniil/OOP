#include "cocktail.h"

namespace lab2 {
    class Cocktail {
    private:
        string name;
        int alcoholPercentage;
        int volume;

    public:
        // Constructors
        Cocktail(string &n, int &alcohol, int &vol) : name(n), alcoholPercentage(alcohol), volume(vol) {}

        explicit Cocktail(int &vol) : name("Water"), alcoholPercentage(0), volume(vol) {}

        // Getters
        [[nodiscard]] string getName() const {
            return name;
        }

        [[nodiscard]] int getAlcoholPercentage() const {
            return alcoholPercentage;
        }

        [[nodiscard]] int getVolume() const {
            return volume;
        }

        // Setters
        void setName(const string &n) {
            name = n;
        }
        void setAlcoholPercentage(int alcohol) {
            alcoholPercentage = alcohol;
        }
        void setVolume(int vol) {
            volume = vol;
        }

        // Input

     };
}
