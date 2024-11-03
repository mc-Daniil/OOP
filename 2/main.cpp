#include "main.h"
#include "io/io.h"
#include "cocktail/cocktail.h"

const std::string PROMPT("Choose:\n\t0 - exit\n\t1 - add new cocktail\n\t2 - view cocktail\n\t3 - view table status\n\t4 - delete cocktail\n\t5 - get 500 ml of cocktail\n\t6 - get number of cocktails with %\n\t7 - rename cocktail\n>> ");
const std::string PROMPT_NAME("Enter name of cocktail ('Water' if you want water):\n>> ");
const std::string PROMPT_OLD_NAME("Enter old name of cocktail ('Water' if you want water):\n>> ");
const std::string PROMPT_NEW_NAME("Enter new name of cocktail ('Water' if you want water):\n>> ");
const std::string PROMPT_ALCOHOL("Enter alcohol % of cocktail:\n>> ");
const std::string PROMPT_MIN_ALCOHOL("Enter minimum alcohol % of cocktail:\n>> ");
const std::string PROMPT_MAX_ALCOHOL("Enter maximum alcohol % of cocktail:\n>> ");
const std::string PROMPT_VOLUME("Enter volume of cocktail:\n>> ");


void renameCock(CocktailTable &table) {
    std::string oldName;
    std::string newName;
    while (!getInput(oldName, PROMPT_OLD_NAME));
    while (!getInput(newName, PROMPT_NEW_NAME));
    table.renameCocktail(oldName, newName);
}


void getTotalVolume(CocktailTable &table) {
    int minAlcohol = 0, maxAlcohol = 0;
    while (!getInput(minAlcohol, PROMPT_MIN_ALCOHOL) || !checkAlcohol(minAlcohol));
    while (!getInput(maxAlcohol, PROMPT_MAX_ALCOHOL) || !checkAlcohol(maxAlcohol));
    int total = table.totalVolume(minAlcohol, maxAlcohol);
    std::cout << total << std::endl;
}


void get500ml(CocktailTable &table) {
    int minAlcohol = 0, maxAlcohol = 0;
    while (!getInput(minAlcohol, PROMPT_MIN_ALCOHOL) || !checkAlcohol(minAlcohol));
    while (!getInput(maxAlcohol, PROMPT_MAX_ALCOHOL) || !checkAlcohol(maxAlcohol));
    Cocktail newCock = table.getCocktail(minAlcohol, maxAlcohol);
    std::cout << newCock;
    table += newCock;
}


void deleteCocktail(CocktailTable &table) {
    std::string name;
    while (!getInput(name, PROMPT_NAME));
    table.removeCocktail(name);
}


void viewTable(CocktailTable &table) {
    std::cout << table;
}


void viewCocktail(CocktailTable &table) {
    std::string name;
    while (!getInput(name, PROMPT_NAME));
    std::cout << table[name];
}


void addNew(CocktailTable &table) {
    Cocktail cock;
    std::cin >> cock;
    table += cock;
}


void finish(CocktailTable &table) {
    std::cout << "Goodbye" << std::endl;
}


auto main() -> int {
    void (*funcs[8])(CocktailTable &table) = {finish, addNew, viewCocktail, viewTable, deleteCocktail, get500ml,
                                              getTotalVolume, renameCock};

    try {
        int choice = 0;
        Cocktail water(1000);
        Cocktail cocktailArr[1] = {water};
        CocktailTable table(cocktailArr, 1);
        do {
            while (!getInput(choice, PROMPT) || !checkChoice(choice));
            funcs[choice](table);
        } while (choice);
    }
    catch (const std::exception &e) {
        std::cerr << "Error:" << e.what() << std::endl;
    }
}