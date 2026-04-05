#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "field/field.hpp"

int main() {
    int width = 20;
    int height = 20;
    Field field(width, height);

    int x;
    int y;
    while (field.getGameState()) {
        field.printAsciiField();
        std::cout << "Enter x pos:";
        std::cin >> x;
        std::cout << "Enter y pos:";
        std::cin >> y;
        field.cellSelected(x,y);
    }
    field.revealField();
    field.printAsciiField();
    return 0;
}