#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "field/field.hpp"
#include "renderer/renderer.hpp"

int main() {
    int width = 20;
    int height = 20;
    int windowW = 800;
    int windowH = 600;
    Field field(width, height);
    sf::Window window(sf::VideoMode({windowW, windowH}), "Iso Minesweeper");
    Renderer renderer(windowW, windowH); // change to use window

    const auto onClose = [&window](const sf::Event::Closed&) {
            window.close();
    };

    const auto onKeyPressed = [&window](const sf::Event::KeyPressed& keyPressed) {
        if (keyPressed.scancode == sf::Keyboard::Scancode::Escape)
            window.close();
    };

    const auto onClick = [&window, &renderer, &field](const sf::Event::MouseButtonReleased& mousePressed) {
        if (mousePressed.button == sf::Mouse::Button::Left) {
            field.cellSelected(renderer.screenToField(field.getWidth(), field.getHeight()));
        }
    };

    while (window.isOpen())
    {
        if (!field.getGameState()) {
            field.revealField();
            renderer.renderField(window);
        }

        window.handleEvents(onClose, onKeyPressed, onClick);

        //field.printAsciiField();
        renderer.renderField(window);

        // clear
        // draw
        // display
    }


    //field.printAsciiField();
    return 0;
}