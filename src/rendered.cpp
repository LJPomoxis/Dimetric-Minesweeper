#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "renderer/renderer.hpp"

void FieldDisplay::setSpritesheet(std::string texPath) {
    sf::Texture tex(texPath);
    spritesheet = tex;
}

void Renderer::loadSpritesheet() {
    fieldDisplay.setSpritesheet("textures/minesweeperSpritesheet.png");
}

Renderer::Renderer(int w, int h) : windowW(w), windowH(h) {

}

void Renderer::renderField(sf::Window &window) {

}

void Renderer::resetRenderWindow(const sf::Window &window, int width, int height) {
    sf::Vector2u windowDim = window.getSize();
    windowW = windowDim.x;
    windowH = windowDim.y;
}

sf::Vector2i Renderer::screenToField(int width, int height) {
    int x, y; //tmp for illustration of usage, get screen pos, translate to interger coords, return
    return sf::Vector2i{x,y};
}