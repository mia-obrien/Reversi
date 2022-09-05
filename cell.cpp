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

void Cell::setX(const int NewX)
{
    x = NewX;
}

void Cell::setY(const int NewY)
{
    y = NewY;
}

void Cell::setChar(const char NewChar)
{
    cellChar = NewChar;
}
