#include "game.hpp"
#include <iostream>
#include <string>
#include <time.h>
using namespace std;

//ARBOLES EXPECTIMINIMAX ----------------------------------------------------x

const int randomNumAdded[2] = {2, 4};
const double prob[2] = {1.0, 0.0}; 
int contador_wins = 0;

int bestDirection(const Board& board, int depth) //Funcion que le dice al programa la mejor dirreccion para jugar
{
  double maxScore = 0;
  int best_dir = -1;

  for(int direction = 0; direction < 4; direction++)
  {
    Board aiBoard = board;
    move(aiBoard, direction);
    
    if (aiBoard == board) 
    {
      continue;
    }
    double aiScore = aiSolverMove(aiBoard, 2 * depth - 1);
        
    if (aiScore >= maxScore)
    { 
      maxScore = aiScore;
      best_dir = direction;
    }
  }

  return best_dir;
}

int findBestDirection( int a, int b, int c, int d,  //Funcion que retorna la mejor dirreccion para un tablero fijo
                       int e, int f, int g, int h,
                       int i, int j, int k, int l,
                       int m, int n, int o, int p,
                       int depth)
{
  Board board;
  board.cells[getIndex(0, 0)] = a;
  board.cells[getIndex(0, 1)] = b;
  board.cells[getIndex(0, 2)] = c;
  board.cells[getIndex(0, 3)] = d;
  board.cells[getIndex(1, 0)] = e;
  board.cells[getIndex(1, 1)] = f;
  board.cells[getIndex(1, 2)] = g;
  board.cells[getIndex(1, 3)] = h;
  board.cells[getIndex(2, 0)] = i;
  board.cells[getIndex(2, 1)] = j;
  board.cells[getIndex(2, 2)] = k;
  board.cells[getIndex(2, 3)] = l;
  board.cells[getIndex(3, 0)] = m;
  board.cells[getIndex(3, 1)] = n;
  board.cells[getIndex(3, 2)] = o;
  board.cells[getIndex(3, 3)] = p;
  
  return bestDirection(board, depth);
}

double bestPossibleMove(const Board& board, int depth) //buscar el mejor movimiento 
{
  if (depth == 0)
  {   
    return hasMove(board) ? findHeuristic(board) : 0;
  }

  double maxScore = 0;

  for(int direction = 0; direction < 4; direction++)
  {
    Board aiBoard = board;
    move(aiBoard, direction);

    if (aiBoard == board)  
    {
      continue;
    }
    
    double aiScore = 0;

    aiScore = aiSolverMove(aiBoard, depth - 1);

    if (aiScore > maxScore)
    {
      maxScore = aiScore;
    }
  }
    
  return maxScore;
}

double aiSolverMove(const Board& board, int depth) //juego con la IA
{
  double totalScore = 0;
  double totalWt =0;
  
  for(int r=0; r < 4; r++)
  {
    for(int c = 0; c < 4; c++)
    {
      if (board.cells[getIndex(r, c)] == 0)
      {
        for(int i = 0; i<2; i++) 
        {
          Board player_board = board;
          player_board.cells[getIndex(r, c)] = randomNumAdded[i];

          double score = bestPossibleMove(player_board, depth - 1);

          totalScore += prob[i] * score;
          totalWt += prob[i];
        }
      }
    }
  }

  if(totalWt==0)
    return 0;
  else
  {
    return totalScore/totalWt;
  }
}

//GAME ------------------------------------------------------------------------x
void printBoard(Board &board) //mostrar el tablero en consola
{
  cout<<"\n\n";
  cout<< "+===========================+ \n";
  for(int i=0; i<16; ++i)
  {
    cout<<" | " << board.cells[i]<<" ";

    if(i%4==3)
    {
      cout<<"\n";
    }
  }
  cout <<"+===========================+";
  cout<<"\n";
}



void generateRNum(Board &board) //generar una ficha al alzar
{
  int rnum = rand()%16;

  while(board.cells[rnum]!=0)
  {
    rnum = rand()%16;
  }

  board.cells[rnum] = 2;
}

void corrector_eleccion(string &a, int b) //funcion que vuelve a pedir una dirrecion cuando el jugador ingresa un comando erroneo
{
  cout<< "eliga un movimiento: UP RIGHT DOWN LEFT (respetar mayusculas): ";
    cin >> a;

    if(a == "UP") b = 0;
    else if(a == "RIGHT") b = 1;
    else if(a == "DOWN") b = 2;
    else if(a == "LEFT") b = 3;
    else
    {
      cout << "\n dirrecion ingresada no valida";
      corrector_eleccion(a,b);
    }
}

void startGame(Board &board, int rnum) //Inicia el juego jugado por la maquina
{
  int  direction;
  bool gameSolved = false;
  contador_wins = 0;
  srand(time(NULL));

  board.cells[rnum] = 2;

  generateRNum(board);
  printBoard(board);

  while(hasMove(board))
  {
    for(int i=0; i<16; ++i)
    {
      if(board.cells[i]==2048)
      {
        gameSolved = true;
        break;
      }
    }

    if(gameSolved)
    {
      break;
    }

    direction = findBestDirection( board.cells[0], board.cells[1], board.cells[2], board.cells[3],
                                   board.cells[4], board.cells[5], board.cells[6], board.cells[7],
                                   board.cells[8], board.cells[9], board.cells[10],board.cells[11],
                                   board.cells[12],board.cells[13],board.cells[14],board.cells[15],
                                   3);

    cout<<"direction=="<<direction<<"\n";

    move(board, direction);

    generateRNum(board);
    printBoard(board);
  }

  if(gameSolved)
  {
    
    cout<<"ai solved it\n";
    contador_wins++;
  }
  else
    cout<<"ai didnt solve it\n";
}

void startGamePlay(Board &board, int rnum) //inicia el juego para que juege el jugador
{
  int  direction;
  bool gameSolved = false;
  srand(time(NULL));

  board.cells[rnum] = 2;

  generateRNum(board);
  printBoard(board);

  while(hasMove(board))
  {
    for(int i=0; i<16; ++i)
    {
      if(board.cells[i]==2048)
      {
        gameSolved = true;
        break;
      }
    }

    if(gameSolved)
    {
      break;
    }

    direction = findBestDirection( board.cells[0], board.cells[1], board.cells[2], board.cells[3],
                                   board.cells[4], board.cells[5], board.cells[6], board.cells[7],
                                   board.cells[8], board.cells[9], board.cells[10],board.cells[11],
                                   board.cells[12],board.cells[13],board.cells[14],board.cells[15],
                                   3 );

    string direction_string;

    if( direction == 0) direction_string = "LEFT";
    if( direction == 1) direction_string = "DOWN";
    if( direction == 2) direction_string = "RIGHT";
    if( direction == 3) direction_string = "UP";

    cout<<"mejor direccion ="<<direction_string<<"\n\n";

    int manual_direction;
    string chosen_direction;

    cout<< "eliga un movimiento: UP RIGHT DOWN LEFT (respetar mayusculas): ";
    cin >> chosen_direction;

    if(chosen_direction == "UP") manual_direction = 3;
    else if(chosen_direction == "RIGHT") manual_direction = 2;
    else if(chosen_direction == "DOWN") manual_direction = 1;
    else if(chosen_direction == "LEFT") manual_direction = 0;
    else
    {
      cout << "\n dirrecion ingresada no valida";
      corrector_eleccion(chosen_direction,manual_direction);
    }

    move(board, manual_direction);
    
    generateRNum(board);
    printBoard(board);
  }

  if(gameSolved)
    cout<<"Has ganado\n";
  else
    cout<<"Vuelve a intentarlo\n";
}


void theGame(Board &board) //jugar o que el algoritmo juegue, sin alasis de tiempo
{
  int n;

  cout << "Bienvenido a 2048 \n\n\n";
  cout << "1. Jugar \n2. Solucion ia master\n3. Salir";
  cin >> n;

  if(n == 1) startGamePlay(board);
  else if(n == 2) startGame(board);
  else if(n == 3) exit(1);
  else 
  {
    cout << "error ingrese una opcion valida\n";
    theGame(board);
  }
}

void theGameData(Board &board) //bienvenida del juego con analisis
{
  cout << "Bienvenido a 2048 \n\n\n";
  cout <<"Comenzando analisis";
  startGame(board);

}

/*Juego sin data*/
void GameStart(){ 
  Board br; //creacion de objeto del juego
  theGame(br); //funcion iniciar juego
}

/*Juego con data*/
void GameData(){ //al seleccionar el valor 2 en bienvenida, generara un n-loop que probara la IA
  int count = 0; //Contador de intentos
  float init_time, finish_time,time_execution; //datos del tiempo
  int contador = 0;
  float total_time = 0;
  FILE *file; //Crear puntero de archivo
  file = fopen("Data.txt","w+"); //abrir archivo.txt
  fprintf(file,"%s \t %s \t %s \n ","Intento NO:", "Tiempo de ejercucion:", "Resultado:"); //escribir titulos
  string str;
  int n;
  cout<<"Cuantos casos quiere analizar: ";cin>>n;cout<<endl;
  
  while (count != n)
  {
    init_time = clock(); //Tiempo inicial
    
    Board br; //creacion de objeto del juego
    theGameData(br); //funcion iniciar juego sin usuario

    finish_time = clock();

    time_execution = finish_time - init_time;
    time_execution = float(time_execution)/CLOCKS_PER_SEC;

    total_time += time_execution;
    contador+= contador_wins;

    if(contador_wins == 1) fprintf(file,"%d\t\t\t%lf\t\t%s\n",count + 1 , time_execution,"WIN");
    else fprintf(file,"%d\t\t\t%lf\t\t%s\n",count + 1 , total_time ,"NO WIN");

    count++;
  }
  fprintf(file,"========================================================\n");
  fprintf(file,"%d\t\t\t%lf\t\t%d\n",n,total_time,contador);
  fclose(file);
}


void bienvenida(){ //Lo primero que se muestra en el output de la consola que recibe un valor de entrada
  int respuesta;
  cout<<endl;
  cout<<"===================="<<endl;
  cout<<"BIENVENIDO AL SOLUCIONADOR DEL JUEGO 2048!!"<<endl;
  cout<<"PARA JUGAR PRESIONE 1"<<endl;
  cout<<"PARA REALIZAR UN ANALISIS DE EJECUCION PRESIONE 2"<<endl;
  cout<<"PARA SALIR DEL EJECUTABLE PRESIONE 3"<<endl;

  cin>>respuesta;cout<<endl;

  if (respuesta == 1) GameStart();
  else if(respuesta == 2) GameData();
  else if(respuesta == 3) exit(1);
  else bienvenida();
}
