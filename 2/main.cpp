#include "main.h"
#include "io/io.h"
#include "cocktail/cocktail.h"

#define PROMPT "Choose:\n\t0 - exit\n\t1 - add new cocktail\n\t2 - view cocktail\n\t3 - view table status\n\t4 - delete cocktail\n\t5 - get 500 ml of cocktail\n\t6 - get number of cocktails with %\n\t7 - rename cocktail\n>> "
#define PROMPT_NAME "Enter name of cocktail ('Water' if you want water):\n>> "
#define PROMPT_ALCOHOL "Enter alcohol % of cocktail:\n>> "
#define PROMPT_VOLUME "Enter volume of cocktail:\n>> "


//auto viewCocktail() {
//
//}


auto addNew() -> void {
    Cocktail cock;
    std::cin >> cock;
}


auto finish() -> void {
    std::cout << "Goodbye" << std::endl;
}


auto main() -> int {
    auto(*funcs[8]) = {finish, addNew, viewCocktail, viewTable, deleteCocktail, get500ml, getNumber, renameCockail};

    try {
        CocktailTable table;
        int choice = 0;
        while (!getInput(choice, PROMPT) || !checkChoice(choice));
        funcs[choice];
    }
    catch (const std::exception &e) {
        std::cerr << "Error:" << e.what() << std::endl;
    }
}