#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <algorithm>
#include <random>


struct Block {
    // Between 1 , 7  
    int Shape = 0;
    bool Dropping = false; 

};

struct Game {
    int FPS;
    bool CannotMove = false; 
    bool NewShape = true;
    bool GameOver = false;
    Block Board[20][10];

};

// utils.cpp Part : 
char Getch();
void Cls();
bool Compare(const std::vector<int>& a, const std::vector<int>& b);

// game.cpp Part : 
void Play(Game game);
std::pair<std::vector<std::vector<int>> , std::vector<std::vector<int>>> DroppingBlock(Block Board[20][10]);
void Drop(Block Board[20][10] , bool& CannotMove , bool& NewShape);
void CheckDeath(Block Board[20][10] , bool& GameOver);
int RandomShape();
void AddShape(Block Board[20][10] , int ShapeType);

// screen.cpp Part :
void Draw(Block Board[20][10]); 
