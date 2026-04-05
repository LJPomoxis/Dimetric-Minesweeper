#include "field.hpp"
#include <iostream>
#include <random>

Field::Field(int w, int h) : width(w), height(h), cells(h*w) {
    numMines = (width * height) / 6;
}


void printGrayscale(int val) {
    int level = 9 - val;
    if (val > 8) level = 1;

    int ansiCode = 232 + (level - 1) * 3;

    std::cout << "\033[38;5;" << ansiCode << "m" << val << "\033[0m";
}

bool Field::getGameState() {
    return gameRunning;
}

std::vector<int> Field::generateMinePositions() {
    std::vector<int> cells(width*height);
    std::iota(cells.begin(), cells.end(), 0);

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i=0; i < (numMines + 1); ++i) {
        std::uniform_int_distribution<int> dist(i, cells.size() - 1);
        int j = dist(gen);

        std::swap(cells[i], cells[j]);
    }

    cells.resize(numMines + 1); // In the case that a selected index matches the position of the initial click
    return cells;
}

void Field::incrementMineNeighbors(int pos) {
    int x = pos % width;
    int y = pos / height;
    for (int diffX=-1; diffX < 2; ++diffX) {
        for (int diffY=-1; diffY < 2; ++diffY) {
            if (diffX == 0 && diffY == 0) continue;

            int xCheck = x + diffX;
            int yCheck = y + diffY;
            if (xCheck >= 0 && xCheck <= width && yCheck >= 0 && yCheck <= height) {
                int pos2 = yCheck * width + xCheck;
                cells[pos2].neighborMineCount++;
            }
        }
    }
}

void Field::setMines(int x, int y) {
    std::vector<int> mineIndices = generateMinePositions();
    bool skip = false;
    for (int i=0; i < (numMines + 1); ++i) {
        if (mineIndices[i] == (y * width + x)) {
            skip = true;
            continue;
        }

        if (i == numMines && skip == false) continue;

        cells[mineIndices[i]].isMine = true;
        incrementMineNeighbors(mineIndices[i]);
    }
    gameStarted = true;
}

void Field::revealCell(int x, int y) {
    int pos = y * width + x;
    if (!cells[pos].isMine) {
        cells[pos].isRevealed = true;
        if (cells[pos].neighborMineCount == 0) {
            checkNeighbors(x,y);
        }
    }
}

void Field::checkNeighbors(int x, int y) {
    for (int diffX=-1; diffX < 2; ++diffX) {
        for (int diffY=-1; diffY < 2; ++diffY) {
            if (diffX == 0 && diffY == 0) continue;

            int xCheck = x + diffX;
            int yCheck = y + diffY;
            if (xCheck >= 0 && xCheck <= width && yCheck >= 0 && yCheck <= height) {
                if (!cells[yCheck * width + xCheck].isRevealed) {
                    revealCell(xCheck, yCheck);
                }
            }
        }
    }
}

void Field::cellSelected(int x, int y) {
    if (!gameStarted) {
        setMines(x, y);
    }

    int pos = y * width + x;
    if (cells[pos].isMine) {
        std::cout << "\n" << "Game Over" << std::endl;
        gameRunning = false;
        return;
    } else {
        cells[pos].isRevealed = true;
    }

    if (cells[pos].neighborMineCount == 0) {
        checkNeighbors(x, y);
    }
}

void Field::clearField() {
    std::vector<Cell>().swap(cells);
}

void Field::revealField() {
    for (auto& cell : cells) {
        if (!cell.isRevealed) cell.isRevealed = true;
    }
}

void Field::printAsciiField() {