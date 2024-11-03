#include <catch.hpp>
#include "../cocktail/cocktail.h"

TEST_CASE("Cocktail Constructor and Accessors") {
    Cocktail defaultCocktail;
    REQUIRE(defaultCocktail.getName() == "");
    REQUIRE(defaultCocktail.getAlcoholPercentage() == 0);
    REQUIRE(defaultCocktail.getVolume() == 0);

    std::string name = "Mojito";
    int alcohol = 15;
    int volume = 250;
    Cocktail mojito(name, alcohol, volume);
    REQUIRE(mojito.getName() == "Mojito");
    REQUIRE(mojito.getAlcoholPercentage() == 15);
    REQUIRE(mojito.getVolume() == 250);
}

TEST_CASE("Cocktail Addition Operator") {
    std::string name1 = "Mojito";
    std::string name2 = "Martini";
    Cocktail mojito(name1, 15, 250);
    Cocktail martini(name2, 20, 150);

    Cocktail result = mojito + martini;
    REQUIRE(result.getName() == "Mojito + Martini");
    REQUIRE(result.getAlcoholPercentage() == 17);
    REQUIRE(result.getVolume() == 400);
}

TEST_CASE("Cocktail Transfer Operator") {
    std::string name1 = "Mojito";
    Cocktail mojito(name1, 15, 250);
    Cocktail glass;

    mojito >> glass;
    REQUIRE(mojito.getVolume() == 150);
    REQUIRE(glass.getVolume() == 100);
    REQUIRE(glass.getAlcoholPercentage() == 15);
}

TEST_CASE("CocktailTable Constructor and IsEmpty") {
    CocktailTable table;
    REQUIRE(table.isEmpty() == true);

    std::string name = "Mojito";
    Cocktail mojito(name, 15, 250);
    table += mojito;

    REQUIRE(table.isEmpty() == false);
}

TEST_CASE("CocktailTable Operator[] Access and Remove") {
    Cocktail mojito("Mojito", 15, 250);
    Cocktail martini("Martini", 20, 150);
    CocktailTable table;

    table += mojito;
    table += martini;

    REQUIRE(table["Mojito"].getName() == "Mojito");
    REQUIRE(table["Martini"].getAlcoholPercentage() == 20);

    table.removeCocktail("Mojito");
    REQUIRE_THROWS_AS(table["Mojito"], std::out_of_range);
}

TEST_CASE("CocktailTable Total Volume") {
    Cocktail mojito("Mojito", 15, 250);
    Cocktail martini("Martini", 20, 150);
    CocktailTable table;

    table += mojito;
    table += martini;

    REQUIRE(table.totalVolume(10, 20) == 400);
    REQUIRE(table.totalVolume(15, 15) == 250);
    REQUIRE(table.totalVolume(30, 40) == 0);
}


TEST_CASE("CocktailTable Rename Cocktail") {
    Cocktail mojito("Mojito", 15, 250);
    CocktailTable table;
    table += mojito;

    table.renameCocktail("Mojito", "Mint Mojito");
    REQUIRE(table["Mint Mojito"].getName() == "Mint Mojito");
    REQUIRE_THROWS_AS(table["Mojito"], std::out_of_range);
}

TEST_CASE("CocktailTable Get Cocktail") {
    Cocktail mojito("Mojito", 15, 600);
    CocktailTable table;
    table += mojito;

    Cocktail result = table.getCocktail(10, 20);
    REQUIRE(result.getName() == "Mojito");
    REQUIRE(result.getVolume() == 500);
    REQUIRE(table["Mojito"].getVolume() == 100);
}

TEST_CASE("Cocktail IO Operators") {
    std::ostringstream oss;
    Cocktail mojito("Mojito", 15, 250);
    oss << mojito;
    REQUIRE(oss.str() == "Cocktail: Mojito | Alcohol: 15% | Volume: 250ml");

    std::istringstream iss("Mojito\n15\n250\n");
    Cocktail inputCocktail;
    iss >> inputCocktail;
    REQUIRE(inputCocktail.getName() == "Mojito");
    REQUIRE(inputCocktail.getAlcoholPercentage() == 15);
    REQUIRE(inputCocktail.getVolume() == 250);
}
