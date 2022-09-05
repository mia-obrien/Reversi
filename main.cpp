#include <iostream>
#include "reversi.h"
#include <vector>
#include <string>

using namespace std;
int Reversi::LivingCell = 0;

int main(int argc, char** argv) {

    Reversi game;    

    while(game.isEnd()!=true )
    {          
        game.play();
        cout << "\nNuber of living cell: " << Reversi::NumberOfLivingCell() << endl;            
    }
   
    return 0;
}
