#include <iostream>
#include "reversi.h"
#include <vector>
#include <string>

using namespace std;
int Reversi::livingCell = 0;

int main(int argc, char** argv) {

    Reversi game;    

    while(game.isEnd()!=true)
    {   
        game.play();
        cout << "\nNuber of living cell: " << Reversi::numberOfLivingCell() << endl;            
    }
   
    return 0;
}
