#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>
#include <numeric>
#include <algorithm>
#include <iostream>

struct Tile {
    bool isMine = false;
    bool isRevealed = false;
    bool isFlagged = false;
    int numNeighbors = 0;
};

class Board {
private:
    std::vector<Tile> tiles;
    bool gameStarted = false;
    bool gameOver = false;
    int width;  // Based on 0->n not 1->n
    int height; // Based on 0->n not 1->n
    int numMines;

public:
    Board(int w, int h) : width(w), height(h), tiles(h*w) {
        numMines = (width * height) / 8; // 1/8th for testing, subject to change
    }

    bool getGameState();
    Tile& getTile(int x, int y);
    std::vector<int> generateMinePositions();
    void setMines(int x, int y);
    void revealTile(int x, int y);
    void checkNeighbors(int x, int y);
    void tileSelected(int x, int y);
    void clearBoard();
    void revealBoard();

    void printAsciiBoard();
};

int main() {
    int width = 20 - 1;
    int height = 20 - 1;
    Board board(width, height);

    int x;
    int y;
    while (board.getGameState()) {
        board.printAsciiBoard();
        std::cout << "Enter x pos:";
        std::cin >> x;
        std::cout << "Enter y pos:";
        std::cin >> y;
        board.tileSelected(x,y);
    }

}

bool Board::getGameState() {
    return gameOver;
}

Tile& Board::getTile(int x, int y) {
    return tiles[y * width + x];
}

std::vector<int> Board::generateMinePositions() {
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

void Board::setMines(int x, int y) {
    std::vector<int> mineIndices = generateMinePositions();
    bool skip = false;
    for (int i=0; i < (numMines + 1); ++i) {
        if (mineIndices[i] == (y * width + x)) {
            skip = true;
            continue;
        }

        if (i == numMines && skip == false) continue;

        tiles[mineIndices[i]].isMine = true;
    }
    gameStarted = true;
}

void Board::revealTile(int x, int y) {
    int pos = y * width + x;
    if (!tiles[pos].isMine) {
        tiles[pos].isRevealed = true;
        if (tiles[pos].numNeighbors == 0) {
            checkNeighbors(x,y);
        }
    }
}

void Board::checkNeighbors(int x, int y) {
    for (int diffX=-1; diffX < 2; ++diffX) {
        for (int diffY=-1; diffY < 2; ++diffY) {
            if (diffX == 0 && diffY == 0) continue;

            int xCheck = x + diffX;
            int yCheck = y + diffY;
            if (xCheck >= 0 && xCheck <= width && yCheck >= 0 && yCheck <= height) {
                if (!tiles[yCheck * width + xCheck].isRevealed) {
                    revealTile(xCheck, yCheck);
                }
            }
        }
    }
}

void Board::tileSelected(int x, int y) {
    if (!gameStarted) {
        setMines(x, y);
    }

    if (tiles[y * width + x].isMine) {
        gameOver = true;
        std::cout << "\n" << "Game Over" << std::endl;
    }

    checkNeighbors(x, y);
}

void Board::clearBoard() {
    std::vector<Tile>().swap(tiles);
}

void Board::revealBoard() {
    for (auto& tile : tiles) {
        if (!tile.isRevealed) tile.isRevealed = true;
    }
}

void Board::printAsciiBoard() {
    for (size_t i=0; i < tiles.size(); ++i) {
        if (i > width && (i % width == 0)) {
            std::cout << std::endl;
        }
        
        if (tiles[i].isRevealed && !tiles[i].isMine) {
            std::cout << tiles[i].numNeighbors << " | ";
        } else if (!tiles[i].isRevealed) {
            std::cout << "-" << " | ";
        } else if (tiles[i].isMine) {
            std::cout << "M" << " | ";
        }
    }
    std::cout << std::endl;
}