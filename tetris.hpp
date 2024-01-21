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
    Block Board[20][10];

};

// utils.cpp Part : 
char Getch();
void Cls();
bool Compare(); 

// game.cpp Part : 
std::vector<std::vector<int>> DroppingBlock(Block Board[20][10]);

// screen.cpp Part :
void Draw(Block Board[20][10]); 
