#include <vector>
#include <string>

using namespace std;

class Cell
{
public:
    Cell(int X, int Y, char C);
       
    int Get_X() const {return x;}
    int Get_Y() const {return y;} 
    char Get_Char() const {return cellChar;}
      
    void Set_X(const int NewX);
    void Set_Y(const int NewY);  
    void Set_Char(const char NewChar);
    
private:
    int y;
    int x;
    char cellChar;
};
