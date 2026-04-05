#pragma once
#include <vector>

void printGrayscale(int val);

struct Cell {
    bool isMine = false;
    bool isRevealed = false;
    bool isFlagged = false;
    int neighborMineCount = 0;
};

class Field {
private:
    std::vector<Cell> cells;
    bool gameStarted = false;
    bool gameRunning = true;
    int width;
    int height;
    int numMines;

public:
    Field(int w, int h);

    bool getGameState() { return gameRunning; }
    std::vector<int> generateMinePositions();
    void incrementMineNeighbors(int pos);
    void setMines(int x, int y);
    void revealCell(int x, int y);
    void checkNeighbors(int x, int y);
    void cellSelected(int x, int y);
    void clearField();
    void revealField();

    void printAsciiField();
};