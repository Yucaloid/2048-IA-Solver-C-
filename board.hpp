#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>

struct Board
{
  int cells[16];

  Board();
  
  // Operador ==
  inline bool operator==(const Board &board) const
  {
    bool equal = true;
      for(int i=0; i<16; ++i)
      {
        if(cells[i]!=board.cells[i])
        {
          equal = false;
          break;
        }
      }
      return equal;
  }

};

//Funciones 2048
inline int getIndex(int r, int c) {return 4*r+c;}
int findHeuristic(const Board& board);
bool hasMove(const Board& board);
int maxCell(const Board& board);
void move1(int cells[4]);
void moveUP(Board& board);
void moveDOWN(Board& board);
void moveLEFT(Board& board);
void moveRIGHT(Board& board);
void move(Board& board, int direction);

