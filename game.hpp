#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <utility>
#include "board.hpp"

extern int contador_wins; // contar cuando se gana

int findBestDirection( int a, int b, int c, int d,
                       int e, int f, int g, int h,
                       int i, int j, int k, int l,
                       int m, int n, int o, int p,
                       int depth);

double aiSolverMove(const Board& board, int depth);
double bestPossibleMove(const Board& board, int depth);
int bestDirection(const Board& board, int depth);
void printBoard(Board &board);
void generateRNum(Board &board);
void startGame(Board &board, int rnum = rand()%16);
void startGamePlay(Board &board, int rnum = rand()%16);
void theGame(Board &board);
void theGameData(Board &board);


void GameStart();
void GameData();
void bienvenida();
