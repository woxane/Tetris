#include <iostream>
#include <termios.h>
#include <unistd.h>


struct Block {
    // Between 1 , 7  
    int Shape;
    bool Dropping; 

};

struct Game {
    int FPS;
    Block Board[10][20];

};

// utils.cpp Part : 
char Getch();
void Cls();

// game.cpp Part : 
void Game();


// screen.cpp Part :
void Draw(Block Board[20][10]); 
