#include "main.h"
#include "io/io.h"

#define PROMPT "Choose:\n\t0 - exit\n\t1 - add new cocktail\n\t2 - view cocktail\n\t3 - view table status\n\t4 - delete cocktail\n\t5 - get 500 ml of cocktail\n\t6 - get number of cocktails with %\n\t7 - rename cocktail\n>> "
#define PROMPT_NAME "Enter name of cocktail ('Water' if you want water):\n>> "


auto addNew() {
    std::string name = "Water";
    int volume = 0;
    int alcohol = 0;
    while (!getInput(name, PROMPT_NAME));
}


auto finish() -> void {
    std::cout << "Goodbye" << std::endl;
}


auto main() -> int {
    auto(*funcs[8]) = {finish, addNew, viewCocktail, viewTable, deleteCocktail, get500ml, getNumber, renameCockail};

    try {
        int choice = 0;
        while (!getInput(choice, PROMPT) || !checkChoice(choice));

    }
    catch (const std::exception &e) {
        std::cerr << "Error:" << e.what() << std::endl;
    }
}