#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <algorithm>
#include <random>
#include <termios.h>
#include <fcntl.h>
#include <cmath>
#include <ncurses.h>
#include <cstring>
#include <cctype>


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
    int Pivot[2] = {0,0};
    int Score = 0;
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
        { // J Block
            {1,4} , {0,4} , {0,5} , {2,4} 
        },
        { // L Block 
            {1,5} , {0,4} , {0,5} , {2,5} 
        },
        { // Zag Block
            {1,4} , {0,5} , {1,5} , {2,4} 
        },
        { // Zig Block 
            {1,4} , {0,4} , {1,5} , {2,5} 
        },
        { // T Block
            {1,5} , {0,5} , {1,4} , {1,6}
        }

    };
    Block Board[18][10];

};

// utils.cpp Part : 
char Getch();
void Cls();

// game.cpp Part : 
void Play(Game game);
std::vector<std::vector<int>> DroppingBlock(Block Board[18][10]);
void Drop(Block Board[18][10] , bool& CannotMove , bool& NewShape , int Pivot[2] , int& Score);
void CheckDeath(Block Board[18][10] , bool& GameOver);
int RandomShape(int CurrentShape);
void AddShape(Block Board[18][10] , int ShapeType , bool& GameOver , std::vector<std::vector<int>> BlockCords , int Pivot[2]);
void BlockFall(Block Board[18][10] , std::vector<std::vector<int>> Cords , int& Score);
void MoveRight(Block Board[18][10] , bool& NewShape , int Pivot[2]);
void MoveLeft(Block Board[18][10] , bool& NewShape , int Pivot[2]);
void Rotate(Block Board[18][10] , bool& NewShape , int Pivot[2]);
void CompletedRows(Block Board[18][10] , int& Score);
void ShiftDown(Block Board[18][10] , int Row);
int CalculateScore(int Nth);

// screen.cpp Part :
void Draw(Block Board[18][10]); 
int Menu();
int Level();
std::string Nickname();
