#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <vector>


char Getch();
void Cls();

struct Block {
    // Between 0 , 6  
    int Shape;
    bool Dropping; 

};

struct Game {
    int FPS;
    Block Board[10][20];

};