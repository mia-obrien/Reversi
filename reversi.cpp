#include "reversi.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <unistd.h>

using namespace std;

//Default constructor
Reversi::Reversi()
{
    width = -1;
    height = -1;
}

//One parameter constructor
Reversi::Reversi(const int sizeX)
{
    if(sizeX<4)
    {    
        cout<< "The size of both coordinates cannot be less than 4.";
    }
    width = sizeX;
    height = sizeX;
    createBoard();
}

//Two parameters constructor
Reversi::Reversi(const int sizeX,const int sizeY)
{
    if(sizeX<4 || sizeY<4)
    {    
        cout<< "The size of both coordinates cannot be less than 4.";
    }
    
    width = sizeX; 
    height = sizeY;
    createBoard();
}

//Creating the board based on user inputs
void Reversi::createBoard()
{
    int x, y;

    do
    {
        cout << "Please enter an integer for width(bigger than 3) : ";
        cin >> x;        
    }while(x<4);
    setWidth(x);
  
    do
    {
        cout << "Please enter an integer for height(bigger than 3) : ";
        cin >> y;
    }while(y<4);
    setHeight(y);

    board.reserve(getHeight()+10);
    for(int i=0; i<getHeight(); ++i)
    {
        board[i].reserve(getWidth()+10);
        for(int j=0; j<getWidth(); ++j)
        {   
            board[i][j].setY(i);
            board[i][j].setX(j);
            board[i][j].setChar(defaultChar);  
                        
            if((i+1==(getHeight())/2 && j+1==(getWidth())/2) ||(i==(getHeight())/2 && j==(getWidth())/2))
            {
                board[i][j].setY(i);
                board[i][j].setX(j);
                board[i][j].setChar(computer);
                addLivingCell();
            }
            if((i==(getHeight())/2 && j+1==(getWidth())/2) ||(i+1==(getHeight())/2 && j==(getWidth())/2))
            {
                board[i][j].setY(i);
                board[i][j].setX(j);
                board[i][j].setChar(player);
                addLivingCell();
            }
        }
    }   
}

//Displays the board that user created
void Reversi::displayBoard() const
{   
    char c;
    int i;
  
    cout << "   ";
    for(c='a'; c<=96+getWidth(); ++c)
    {
        cout << c << " ";
    }
    cout << endl;
  
    for(i=1; i<=getHeight(); ++i)
    {
        //checks the column are in same line
        if(i<10)
        {
            cout << " " << i << " ";  
        }
        else
        {
            cout << i << " ";
        }
      
        for(int j=0; j<getWidth(); ++j)
        {
            cout << board[i-1][j].getChar() << " ";
        }
        cout << endl;
    }
}

//User Moves
void Reversi::playerMove(const int vertical, const int horizontal, const char player1, const char player2)
{
    //to right direction
    if(horizontal+1< getWidth() && board[vertical][horizontal+1].getChar() == player2)
    {
        for(int i=1; horizontal+i < getWidth() && board[vertical][horizontal+i].getChar() == player2; ++i)
        {
            if(horizontal+i+1 < getWidth() && board[vertical][horizontal+i+1].getChar() == player1)
            {
                for(int j=0; j<=i; ++j)
                {
                    board[vertical][horizontal+j].setChar(player1);
                }
            }
        }
    }
  
    //to left direction
    if(horizontal-1>=0 && board[vertical][horizontal-1].getChar() == player2)
    {
        for(int i=1; horizontal-i >= 0 && board[vertical][horizontal-i].getChar() == player2; ++i)
        {
            if(horizontal-i-1 >= 0 && board[vertical][horizontal-i-1].getChar() == player1)
            {
                for(int j=0; j<=i; ++j)
                {
                    board[vertical][horizontal-j].setChar(player1);
                }              
            }
        }
    }

    //to down
    if(vertical+1<getHeight() && board[vertical+1][horizontal].getChar() == player2)
    {
        for(int i=1; vertical+i < getHeight() && board[vertical+i][horizontal].getChar() == player2; ++i)
        {
            if(vertical+i+1 < getHeight() && board[vertical+i+1][horizontal].getChar() == player1)
            {
                for(int j=0; j<=i; ++j)
                {
                    board[vertical+j][horizontal].setChar(player1);
                }        
            }
        }
    }
  
    //to up
    if(vertical-1>=0 && board[vertical-1][horizontal].getChar() == player2)
    {
        for(int i=1; vertical-i >= 0 && board[vertical-i][horizontal].getChar() == player2; ++i)
        {
            if(vertical-i-1 >= 0 && board[vertical-i-1][horizontal].getChar() == player1)
            {
                for(int j=0; j<=i+1; ++j)
                {
                    board[vertical-j][horizontal].setChar(player1);
                }                 
            }
        }
    }

    //to diagonal right-up
    if(vertical-1>=0 && horizontal+1<getWidth() && board[vertical-1][horizontal+1].getChar() == player2)
    {
        for(int i=1; vertical-i >= 0 && horizontal+i < getWidth() && board[vertical-i][horizontal+i].getChar() == player2; ++i)
        {
            if(horizontal+i+1<getWidth() && vertical-i-1>=0 && board[vertical-i-1][horizontal+i+1].getChar() == player1)
            {
                for(int j=0; j<=i; ++j)
                {
                    board[vertical-j][horizontal+j].setChar(player1);
                }
            }
        }
    } 
  
    //to diagonal right-down
    if(vertical+1<getHeight() && horizontal+1<getWidth() && board[vertical+1][horizontal+1].getChar() == player2)
    {
        for(int i=1; vertical+i < getHeight() && horizontal+i < getWidth() && board[vertical+i][horizontal+i].getChar() == player2;++i)
        {
            if(vertical+i+1<getHeight() && horizontal+i+1<getWidth() && board[vertical+i+1][horizontal+i+1].getChar() == player1)
            {              
                for(int j=0; j<=i; ++j)
                {
                    board[vertical+j][horizontal+j].setChar(player1);
                }                      
            }
        }
    }

   //to diagonal left-up
    if(vertical-1>=0 && horizontal-1>=0 && board[vertical-1][horizontal-1].getChar() == player2)
    {
        for(int i=1; vertical-i >= 0 && horizontal-i >= 0 && board[vertical-i][horizontal-i].getChar() == player2; ++i)
        {
            if(vertical-i-1>=0 && horizontal-i-1>=0 && board[vertical-i-1][horizontal-i-1].getChar() == player1)
            {
                for(int j=0; j<=i; ++j)
                {
                    board[vertical-j][horizontal-j].setChar(player1);
                }                         
            }
        }
    }

    //to diagonal left-down
    if(vertical+1<getHeight() && horizontal-1>=0 && board[vertical+1][horizontal-1].getChar() == player2)
    {
        for(int i=1; vertical+i < getHeight() && horizontal-i >= 0 && board[vertical+i][horizontal-i].getChar() == player2; ++i)
        {
            if(horizontal-i-1>=0 && vertical+i+1<getHeight() && board[vertical+i+1][horizontal-i-1].getChar() == player1)
            {
                for(int j=0; j<=i; ++j)
                {
                    board[vertical+j][horizontal-j].setChar(player1);
                }                     
            }
        }
    }

}

//Computer Moves
void Reversi::compMove()
{
    int filledCells=0;
    int maxFilledCells=0;
    int numberOfWinnerCells=0;
    vector<Cell>winnerCells;
    
    for(int i=0; i<getHeight(); ++i)
    {
        for(int j=0; j<getWidth(); ++j)
        {
            if(attack(i, j, computer, player, filledCells)==true)
            {
                if(filledCells > maxFilledCells)
                {
                    winnerCells.clear();
                    maxFilledCells = filledCells;
                    winnerCells.push_back(board[i][j]);
                    numberOfWinnerCells=1;
                }
                if(maxFilledCells == filledCells)
                {
                    winnerCells.push_back(board[i][j]);
                    numberOfWinnerCells +=1;     
                }
            }       
        }
    }
    
    if(numberOfWinnerCells>0)
    {
        int randNum;
        srand (time(NULL));
        randNum = rand() % numberOfWinnerCells;
    
        int ver = winnerCells[randNum].getY();    
        int hor = winnerCells[randNum].getX();

        playerMove(ver, hor, computer, player);
    }
}

bool Reversi::attack(const int vertical, const int horizontal, const char player1, const char player2, int& filledCells) const
{
    bool result = false;
    filledCells = 0;
    
    if(board[vertical][horizontal].getChar() != defaultChar || vertical>= getHeight() || horizontal>= getWidth() ||vertical<0 || horizontal <0)
    {   
        result = false;
    }
    
    else
    { 
        //to right direction
        if(horizontal+1<getWidth() && board[vertical][horizontal+1].getChar() == player2)
        {
            for(int i=1; horizontal+i < getWidth() && board[vertical][horizontal+i].getChar() == player2; ++i)
            {
                if(horizontal+i+1 < getWidth() && board[vertical][horizontal+i+1].getChar() == player1)
                {
                    filledCells = filledCells+i;
                }
            }
        }
        
        //to left direction
        if(horizontal-1>=0 && board[vertical][horizontal-1].getChar() == player2)
        {
            for(int i=1; horizontal-i >= 0 && board[vertical][horizontal-i].getChar() == player2; ++i)
            {
                if(horizontal-i-1 >= 0 && board[vertical][horizontal-i-1].getChar() == player1)
                {
                    filledCells = filledCells+i;
                }
            }
        }
  
        //to down
        if(vertical+1<getHeight() && board[vertical+1][horizontal].getChar() == player2)
        {
            for(int i=1; vertical+i < getHeight() && (board[vertical+i][horizontal].getChar() == player2); ++i)
            {
                if(vertical+i+1 < getHeight() && board[vertical+i+1][horizontal].getChar() == player1)
                {
                    filledCells = filledCells+i;
                }
            }
        }
          
        //to up
        if(vertical-1>=0 && board[vertical-1][horizontal].getChar() == player2)
        {
            for(int i=1; vertical-i >= 0 && board[vertical-i][horizontal].getChar() == player2; ++i)
            {
                if(vertical-i-1>=0 && board[vertical-i-1][horizontal].getChar() == player1)
                {
                    filledCells = filledCells+i;
                }
            }
        }
          
        //to diagonal right-up
        if(vertical-1>=0 && horizontal+1<getWidth() && board[vertical-1][horizontal+1].getChar() == player2)
        {
            for(int i=1; vertical-i >= 0 && horizontal+i < getWidth() && board[vertical-i][horizontal+i].getChar() == player2; ++i)
            {
                if(vertical-i-1 >=0 &&  horizontal+i+1< getWidth() && board[vertical-i-1][horizontal+i+1].getChar() == player1)
                {
                    filledCells = filledCells+i;
                }
            }
        }
        
        //to diagonal right-down
        if(vertical+1<getHeight() && horizontal+1<getWidth() && board[vertical+1][horizontal+1].getChar() == player2)
        {
            for(int i=1; vertical+i < getHeight() && horizontal+i < getWidth() && board[vertical+i][horizontal+i].getChar() == player2; ++i)
            {
                if(vertical+i+1<getHeight() && horizontal+i+1<getWidth() && board[vertical+i+1][horizontal+i+1].getChar() == player1)
                {
                    filledCells = filledCells+i;
                }
            }
        }
        
        //to diagonal left-up
        if(vertical-1>=0 && horizontal-1>=0 && board[vertical-1][horizontal-1].getChar() == player2)
        {
            for(int i=1; vertical-i >= 0 && horizontal-i >= 0 && board[vertical-i][horizontal-i].getChar() == player2; ++i)
            {
                if(vertical-i-1>=0 && horizontal-i-1>=0 && board[vertical-i-1][horizontal-i-1].getChar() == player1)
                {
                    filledCells = filledCells+i;
                }
            }
        }
  
        //to diagonal left-down
        if(vertical+1<getHeight() && horizontal-1>=0 && board[vertical+1][horizontal-1].getChar() == player2)
        {
            for(int i=1; vertical+i < getHeight() && horizontal-i >= 0 && board[vertical+i][horizontal-i].getChar() == player2; ++i)
            {
                if(horizontal-i-1>=0 && vertical+i+1 < getHeight() && board[vertical+i+1][horizontal-i-1].getChar() == player1)
                {
                    filledCells = filledCells+i;
                }
            }
        }
    
        if(filledCells == 0)
            result = false;
  
        else 
            result = true;
      
        return result;
    }
    return result;
}

bool Reversi::isEnd() const
{
    bool IsEndUser = true;
    bool IsEndComputer = true;
  
    int filledCells;
    
    for(int i=0; i<getHeight(); ++i)
    {
        for(int j=0; j<getWidth(); ++j)
        {
            if(attack(i, j, player, computer, filledCells) == true )
            {
                IsEndUser = false;
            }  
            if(attack(i, j, computer, player, filledCells) == true )
            {
                IsEndComputer = false;
            }     
        }
    }
    if(getHeight()==-1 && getWidth()==-1)  
        return false;
    
    if(IsEndUser == true && IsEndComputer == true)
        return true;
    else
        return false;
}

void Reversi::pickCoordinate(string coordinate, int &vertical, int &horizontal) 
{
    if(coordinate[0]<='9' && coordinate[0]>'0')
    {
        if(coordinate[1]<='9' && coordinate[1]>='0')
        {
            vertical = ((int)(coordinate[0]-48)*10) + ((int)coordinate[1]-48) -1;
            if(coordinate[2]<='z' && coordinate[2]>='a')
            {
                horizontal = (int(coordinate[2])-97);
            }
        }
        else if(coordinate[1]<='z' && coordinate[1]>='a')
        {
            vertical = (int)coordinate[0]-49;
            horizontal = (int(coordinate[1])-97);
        }
    }
}

void Reversi::displayScore()const
{
    int playerScore = 0;
    int compScore = 0;
    
    for(int i=0; i<getHeight(); ++i)
    {
        for(int j=0; j<getWidth(); ++j)
        {
            if(board[i][j].getChar() == player)
                playerScore +=1;
            
            if(board[i][j].getChar() == computer)
                compScore +=1;
        }
    }
  
    if(playerScore > compScore)
    {
        cout << "\nGAME OVER!\nYOU WIN!\n";
    }
    else if(playerScore < compScore)
    {
        cout << "\nGAME OVER!\nYOU LOSE\n";
    }
    else
    {
        cout <<"\nDRAW\n";
    }

    cout << "Score of player : " << playerScore << endl;
    cout << "Score of computer : " << compScore << endl;
}

void Reversi::play()
{
    int vertical, horizontal, filledCells;
    bool IsEndUser;
    bool IsEndComputer;

    for(int i=0; i<getHeight(); ++i)
    {
        for(int j=0; j<getWidth(); ++j)
        {
            if(attack(i, j, player, computer, filledCells) == true )
            {
              IsEndUser = false;
            }
                
            if(attack(i, j, computer, player, filledCells) == true )
            {
              IsEndComputer = false;
            }  
        }
    }
  
    if(height == -1 && width == -1)
    {
        createBoard();     
    }
    displayBoard();

    if(isEnd()!=true && IsEndUser!=true)
    {
        string str;
        cout << "\n::Player Turn::\nEnter coordinate make your move(ex: 1a)> ";
        cin >> str;
        pickCoordinate(str, vertical, horizontal);
        
        while(vertical<0 || horizontal<0 || vertical>=getHeight() || horizontal>=getWidth() || attack(vertical, horizontal, player, computer, filledCells)!=true)
        {
            cout << "Wrong coordinate!\n"
                 << "Please enter a valid coordinate > ";
            cin >> str;
            pickCoordinate(str, vertical, horizontal);
            
        }
        playerMove(vertical, horizontal, player, computer);
        addLivingCell();
        displayBoard();
    }
    
    else if(isEnd()!=true && IsEndUser==true)
    {
        cout << "\nYou do not have any cell to play:(\n";
    }
    
    if(isEnd()!=true && IsEndComputer!=true)    
    {
        cout << "\n::Computer Turn::\n";
        sleep(3);
        compMove();
        addLivingCell();
    }
    
    else if(isEnd()!=true && IsEndComputer==true)
    {
        cout << "\nComputer does not have any cell to play!\n";
    }

    if(isEnd()==true)
    {  
        displayScore(); 
    }   
}
