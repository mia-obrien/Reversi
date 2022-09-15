#include "cell.h"
#include <vector>
#include <string>

using namespace std;

class Reversi
{
public:
    Reversi(); 
    Reversi(const int sizeX); 
    Reversi(const int sizeX, const int sizeY); 
    
    int getWidth() const {return width;}
    int getHeight() const {return height;}

    void setWidth(const int sizeX){width = sizeX;}
    void setHeight(const int sizeY){height = sizeY;}

    void displayBoard()const;
    void displayScore()const;
    
    bool isEnd()const;
    void play();
    
    static int numberOfLivingCell() {return livingCell;}
    static void addLivingCell() {livingCell += 1;}
    
private:
       
    int width; 
    int height; 
    static int livingCell;
    static const char player = 'X';
    static const char computer = 'O';
    static const char defaultChar = '.';

    vector< vector<Cell> > board;

    void compMove();
    bool attack(const int vertical, const int horizontal, const char player1, const char player2, int& filledCells)const;
    void playerMove(const int vertical, const int horizontal, const char player1, const char player2);
    void createBoard();
    void pickCoordinate(string coordinate, int &vertical, int &horizontal);
};
