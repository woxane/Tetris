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
    std::vector<std::vector<std::vector<int>>> ShapeCords = {
        { // O Block 
            {0,4} , {0,5} , {1,4} , {1,5}
        },
        { // Long Block
            {0,3} , {0,4} , {0,5} , {0,6}
        },
        { // L Block
            {0,4} , {1,4} , {2,4} , {3,4} , {0,5}
        },
        { // J Block 
            {0,4} , {0,5} , {1,5} , {2,5} , {3,5} 
        },
        { // Zag Block
            {0,5} , {1,5} , {1,4} , {2,4} 
        },
        { // Zig Block 
            {0,4} , {1,4} , {1,5} , {2,5} 
        },
        { // T Block
            {0,5} , {1,4} , {1,5} , {1,6}
        }

    };
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
