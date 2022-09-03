#include "cell.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <string>

using namespace std;

Cell::Cell(int X, int Y, char C)
{
    x = X;
    y = Y;
    cellChar = C;
}

void Cell::Set_X(const int NewX)
{
    x = NewX;
}

void Cell::Set_Y(const int NewY)
{
    y = NewY;
}

void Cell::Set_Char(const char NewChar)
{
    cellChar = NewChar;
}
