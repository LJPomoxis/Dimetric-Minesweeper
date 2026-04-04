#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

struct Tile {
    bool isMine;
    bool isRevealed;
    int numMines;
};

class Board {
private:
    std::vector<Tile> tiles;

public:
    Board() {}

    void createBoard();
    void clearBoard();
    void revealBoard();
};

int main() {

}

void Board::createBoard() {

}

void Board::clearBoard() {

}

void Board::revealBoard() {
    
}