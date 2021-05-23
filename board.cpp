#include <cstdlib>
#include <vector>
#include "board.hpp"

using namespace std;

//Constructor
Board::Board()
{
  for(int i = 0; i < 16; cells[i] = 0, i++); //Constructor del tablero 4x4
}

//Matrices ponderadas
static int weight_matrices[2][4][4] = 
{
    {{3,2,1,0},
     {2,1,0,-1},
     {1,0,-1,-2},
     {0,-1,-2,-3}},

    {{0,1,2,3},
     {-1,0,1,2},
     {-2,-1,0,1},
     {-3,-2,-1,0}}
};

/*Una matriz representada por una lista es el tablero,
por eso algunas funciones simulan recorrer una matriz 
por culumnas y filas*/

//funciones de movimiento
void move1(int cells[4])
{
  int target = 0;
  for (int i = 1; i < 4; i++)
  {
    int tVal = cells[target];  
    int cVal = cells[i];  
    if (cVal != 0){
      if (tVal == 0){
        cells[target] = cVal;
        cells[i] = 0;
      }
      else{
        if (tVal == cVal){
          cells[i] = 0;
          cells[target] <<= 1;
        }
        else{
          cells[i] = 0;
          cells[target + 1] = cVal;
        }
        target++;
      }
    }
  }
}

/*metodos como moveUP, moveDOWN, moveLEFT y moveRIGHT 
*/

void moveUP(Board& board) //Movimiento hacia arriba
{
  for (int column = 0; column < 4; column++) //recorrer la lista por "columnas"
  {
    int cells[4];
    for (int y = 0; y < 4; y++) //recorre los elementos de la columna
    {
      cells[y] = board.cells[getIndex(column, y)]; //obtener posicion de la lista
    }
    move1(cells);
    for (int y = 0; y < 4; y++) //recorre los elementos de la columna
    {
      board.cells[getIndex(column, y)] = cells[y]; //obtener nueva posicion de la lista
    }
  }
}


void moveDOWN(Board& board) //movimiento abajo
{
  for (int column = 0; column < 4; column++) //recorrer la lista por "columnas"
  {
    int cells[4];
    for (int y = 0; y < 4; y++) //recorre los elementos de la columna
    {
      cells[y] = board.cells[getIndex(column, 3 - y)]; //obtener posicion de la lista
    }
    move1(cells);
    for (int y = 0; y < 4; y++) //recorre los elementos de la columna
    {
      board.cells[getIndex(column, 3 - y)] = cells[y]; //obtener nueva posicion de la lista
    }
  }
}


void moveLEFT(Board& board) //movimiento arriba
{
  for (int row = 0; row < 4; row++) //recorrer lista por "filas"
  {
    int cells[4];
    for (int x = 0; x < 4; x++) //recorre los elementos de la fila
    {
      cells[x] = board.cells[getIndex(x, row)];
    }
    move1(cells);
    for (int x = 0; x < 4; x++) //recorre los elementos de la fila
    {
      board.cells[getIndex(x, row)] = cells[x];
    }
  }
}


void moveRIGHT(Board& board) //movimiento derecha
{
  for (int row = 0; row < 4; row++) //recorrer la lista por "filas"
  {
    int cells[4];
    for (int x = 0; x < 4; x++) //recorre los elementos de la fila
    {
      cells[x] = board.cells[getIndex(3 - x, row)];
    }
    move1(cells);
    for (int x = 0; x < 4; x++) //recorre los elementos de la fila
    {
      board.cells[getIndex(3 - x, row)] = cells[x];
    }
  }
}


void move(Board& board, int direccion) //llamar(usar) funciones de movimiento
{
  if(direccion==0) //generar movimiento hacia arriba
  {
    moveUP(board);
  }
  else if(direccion==1)
  {
    moveRIGHT(board); //generar movimiento hacia la derecha
  }
  else if(direccion==2)
  {
    moveDOWN(board); //generar movimiento hacia abajo
  }
  else if(direccion==3)
  {
    moveLEFT(board); //generar movimiento hacia la izquierda
  }
}

/* Heuristic algorithm es un algoritmo para resolver
problemas de decision del tipo NP-completos, intentado 
no sacrificar optimizacion*/
int findHeuristic(const Board& board)
{
  int best = 0;
  
  for (int i = 0; i < 2; i++)
  {
    int s = 0;
    for (int y = 0; y < 4; y++)
    {
      for (int x = 0; x < 4; x++)
      {
        s += weight_matrices[i][y][x] * (int)board.cells[getIndex(x, y)];
      }
    }
    s = abs(s); 
    if (s > best)
    {
      best = s;
    }
  }
  return best;
}


bool hasMove(const Board& board)
{
  for (int x = 0; x < 4; x++)
  {
    for (int y = 0; y < 4; y++)
    {
      if (board.cells[getIndex(x, y)] == 0)
        return true;
      if (x < 3 && board.cells[getIndex(x, y)] == board.cells[getIndex(x + 1, y)])
        return true;
      if (y < 3 && board.cells[getIndex(x, y)] == board.cells[getIndex(x, y + 1)])
        return true;
    }
  }
  return false;
}


int maxCell(const Board& board)
{
  int h = 0;
  for (int i = 0; i < 16; i++)
  {
    if (board.cells[i] > h)
    {
      h = board.cells[i];
    }
  }
  return h;
}