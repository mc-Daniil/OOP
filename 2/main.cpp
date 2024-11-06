#include "main.h"
#include "io/io.h"
#include "cocktail/cocktail.h"

void increaseVolume(CocktailTable &table) {
    int n;
    std::string cock;
    while (!getInput(n, PROMPT_N) || !checkN(n));
    while(!getInput(cock, PROMPT_NAME));
    Cocktail cocktail = table[cock];
    cocktail = cocktail * n;
}


void pourCocktail(CocktailTable &table) {
    std::cout << "First, write the name of the cocktail that you will pour, then the name of the cocktail that you will pour into" << std::endl;
    std::string cock1;
    std::string cock2;
    while(!getInput(cock1, PROMPT_FIRST_NAME));
    Cocktail cocktail1 = table[cock1];
    while(!getInput(cock2, PROMPT_SECOND_NAME));
    Cocktail cocktail2 = table[cock2];
    cocktail1 >> cocktail2;
    if (cocktail1.getVolume() == 0) {
        table.removeCocktail(cock1);
    }
}


void mixCocktails(CocktailTable &table) {
    std::string cock1;
    std::string cock2;
    while(!getInput(cock1, PROMPT_FIRST_NAME));
    Cocktail cocktail1 = table[cock1];
    while(!getInput(cock2, PROMPT_SECOND_NAME));
    Cocktail cocktail2 = table[cock2];
    Cocktail cocktail3 = cocktail1 + cocktail2;
    table.removeCocktail(cock1);
    table.removeCocktail(cock2);
    table += cocktail3;
}


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
    std::cout << "Goodbye! You had " << table.getSize() << " cocktails" << std::endl;
}


auto main() -> int {
    void (*funcs[11])(CocktailTable &table) = {finish, addNew, viewCocktail, viewTable, deleteCocktail, get500ml,
                                              getTotalVolume, renameCock, mixCocktails, pourCocktail, increaseVolume};

    try {
        int choice = 0;
        auto *water = new Cocktail(1000);
        Cocktail *cocktailArr[1] = {water};
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