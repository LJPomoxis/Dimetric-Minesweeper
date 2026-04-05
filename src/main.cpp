#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "field/field.hpp"

int main() {
    int width = 20;
    int height = 20;
    Field field(width, height);
    sf::Window window(sf::VideoMode({800, 600}), "Iso Minesweeper");

    const auto onClose = [&window](const sf::Event::Closed&) {
            window.close();
    };

    const auto onKeyPressed = [&window](const sf::Event::KeyPressed& keyPressed) {
            if (keyPressed.scancode == sf::Keyboard::Scancode::Escape)
                window.close();
        };

    int x;
    int y;
    while (window.isOpen())
    {
        if (field.getGameState()) {
            window.close();
        }

        window.handleEvents(onClose, onKeyPressed);

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