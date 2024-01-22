#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <algorithm>


struct Block {
    // Between 1 , 7  
    int Shape = 0;
    bool Dropping = false; 

};

struct Game {
    int FPS;
    bool CannotMove = false; 
    Block Board[20][10];

};

// utils.cpp Part : 
char Getch();
void Cls();
bool Compare(); 

// game.cpp Part : 
void Play(Game game);
std::vector<std::vector<int> > DroppingBlock(Block Board[20][10]);
void Drop(Block Board[20][10] , bool& CannotMove);

// screen.cpp Part :
void Draw(Block Board[20][10]); 
