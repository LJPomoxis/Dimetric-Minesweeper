#pragma once
#include <vector>
#include <SFML/Window.hpp>

void printGrayscale(int val);

struct Cell {
    bool isMine = false;
    bool isRevealed = false;
    bool isFlagged = false;
    int neighborMineCount = 0;
};

class Field {
private:
    int mineRatio = 6;
    std::vector<Cell> cells;
    bool gameStarted = false;
    bool gameRunning = true;
    int width;
    int height;
    int numMines;

public:
    Field(int w, int h);

    bool getGameState() { return gameRunning; }
    int getWidth() { return width; }
    int getHeight() { return height; }
    std::vector<int> generateMinePositions();
    void incrementMineNeighbors(int pos);
    void setMines(int x, int y);
    void revealCell(int x, int y);
    void checkNeighbors(int x, int y);
    void cellSelected(sf::Vector2i coords);
    void newField(int width, int height);
    void revealField();

    void printAsciiField();
};