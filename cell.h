#include <vector>
#include <string>

using namespace std;

class Cell
{
public:
    Cell(int X, int Y, char C);
       
    int getX() const {return x;}
    int getY() const {return y;} 
    char getChar() const {return cellChar;}
      
    void setX(const int NewX);
    void setY(const int NewY);  
    void setChar(const char NewChar);
    
private:
    int y;
    int x;
    char cellChar;
};
