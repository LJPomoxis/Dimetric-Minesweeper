#pragma once
#include <SFML/Window.hpp>

enum class CellState { MINE, FLAG, HIDDEN, EMPTY, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT };

class FieldDisplay : public sf::Drawable {
private:
    sf::VertexArray vertices;
    sf::Texture spritesheet;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.texture = &spritesheet;
        target.draw(vertices, states);
    }

public:
    void setSpritesheet(std::string texPath);
};

class Renderer {
private:
    FieldDisplay fieldDisplay;
    int buffer = 10;
    int windowW;
    int windowH;

public:
    Renderer(int w, int h);

    void renderField(sf::Window &window);
    void resetRenderWindow(const sf::Window &window, int width, int height);
    sf::Vector2i screenToField(int width, int height);
    void loadSpritesheet();
};