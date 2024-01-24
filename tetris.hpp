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
    int CurrentShape = 0;
    // Note : The diffrence between ShapeCords And  
    // ShapeMainCords is that ShapeCords save all the Cordination of a Block  
    // But ShapeMainCords just save those that important for Dropping a Block .
    // Thats my solution for checking of a Block could drop or not .
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
    std::vector<std::vector<std::vector<int>>> ShapeMainCords = {
        { // O Block 
            {1,4} , {1,5}
        },
        { // Long Block
            {0,3} , {0,4} , {0,5} , {0,6}
        },
        { // L Block
            {3,4} , {0,5}
        },
        { // J Block 
            {0,4} , {3,5} 
        },
        { // Zag Block
            {1,5} , {2,4} 
        },
        { // Zig Block 
            {1,4} , {2,5} 
        },
        { // T Block
            {1,4} , {1,5} , {1,6}
        }

    };
    Block Board[18][10];

};

// utils.cpp Part : 
char Getch();
void Cls();
bool MoveDownCompare(const std::vector<int>& a, const std::vector<int>& b);
bool MoveRightCompare(const std::vector<int>& a, const std::vector<int>& b);
bool MoveLeftCompare(const std::vector<int>& a, const std::vector<int>& b);

// game.cpp Part : 
void Play(Game game);
std::pair<std::vector<std::vector<int>> , std::vector<std::vector<int>>> DroppingBlock(Block Board[18][10]);
void Drop(Block Board[18][10] , bool& CannotMove , bool& NewShape);
void CheckDeath(Block Board[18][10] , bool& GameOver);
int RandomShape(int CurrentShape);
void AddShape(Block Board[18][10] , int ShapeType , bool& GameOver , std::vector<std::vector<int>> BlockCords);
void BlockFall(Block Board[18][10] , std::vector<std::vector<int>> Cords);
void MoveRight(Block Board[18][10] , bool& CannotMove , bool& NewShape);
void MoveLeft(Block Board[18][10] , bool& CannotMove , bool& NewShape);

// screen.cpp Part :
void Draw(Block Board[18][10]); 
