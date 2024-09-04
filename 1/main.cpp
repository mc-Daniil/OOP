#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;
#define PROMPT "Выберите функцию: 1, 2, 3, 4"

auto getChoice() -> int{
    int choice;
    cout << PROMPT << endl;
    cin >> choice;
    return choice;
}


auto join(string absolute, string relative) -> int{
    return 0;
}


auto main() -> int{
    int choice(getChoice());
    while (choice) {
        cout << choice << endl;
        choice = getChoice();
    }

    return 0;
}