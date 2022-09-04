#include <iostream>
#include "reversi.h"
#include <vector>
#include <string>

using namespace std;
int Reversi::LivingCell = 0;

int main(int argc, char** argv) {

    Reversi game;    

    do{          
        game.play();
        cout << "\nNuber of living cell: " << Reversi::NumberOfLivingCell() << endl;            
    }while(game.IsEnd()!=true );
   
    return 0;
}
