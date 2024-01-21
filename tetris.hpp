#include <iostream>
#include <termios.h>
#include <unistd.h>

// utils.cpp Part : 
char Getch();
void Cls();

// screen.cpp Part :
void Draw(Block Board[10][20]); 

struct Block {
    // Between 0 , 6  
    int Shape;
    bool Dropping; 

};

struct Game {
    int FPS;
    Block Board[10][20];

};