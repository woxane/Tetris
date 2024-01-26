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
#include <iomanip>
#include <sstream>
#include <fstream>


struct Block {
    // Between 1 , 7  
    int Shape = 0;
    bool Dropping = false; 
    bool IsGhost = false;

};

struct Game {
    int FPS;
    bool CannotMove = false; 
    bool NewShape = true;
    bool GameOver = false;
    int CurrentShape = 0;
    int NextShape = 0;
    int Pivot[2] = {0,0};
    int Score = 0;
    long long int ElapsedTime = 0;
    int BoardWidth = 15;
    int BoardHeight = 24;
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
    std::vector<std::vector<Block>> Board;

};

//LB = Leaderboard
struct LB {
	std::string Name ;
	int Score ;
    long long ElapsedTime;
} ;

// utils.cpp Part : 
char Getch();
void Cls();
std::string ConvertTime(long long int ElapsedTime);
void LeaderboardAdd(LB Data , int Level);
std::vector<LB> LeaderboardRead(int Level);
bool Compare(const LB& a, const LB& b);

// game.cpp Part : 
void Play(Game game);
std::vector<std::vector<int>> DroppingBlock(std::vector<std::vector<Block>>& Board , int Height , int Width);
void Drop(std::vector<std::vector<Block>>& Board , bool& CannotMove , bool& NewShape , int Pivot[2] , int& Score , int Height , int Width , bool UserInput = false , bool Fall = false , bool Ghost = false);
void CheckDeath(std::vector<std::vector<Block>>& Board , bool& GameOver , int Width);
void RandomShape(int& CurrentShape , int& NextShape , bool FirstTime = false);
void AddShape(std::vector<std::vector<Block>>& Board, int ShapeType , bool& GameOver , std::vector<std::vector<int>> BlockCords , int Pivot[2]);
void BlockFall(std::vector<std::vector<Block>>& Board , std::vector<std::vector<int>> Cords);
void MoveRight(std::vector<std::vector<Block>>& Board , bool& NewShape , int Pivot[2] , int Height , int Width);
void MoveLeft(std::vector<std::vector<Block>>& Board , bool& NewShape , int Pivot[2] , int Height , int Width);
void Rotate(std::vector<std::vector<Block>>& Board , bool& NewShape , int Pivot[2] , int Height , int Width);
void CompletedRows(std::vector<std::vector<Block>>& Board , int& Score , int NextShape , std::vector<std::vector<int>> NextShapeCords , long long int ElapsedTime , int Height , int Width);
void ShiftDown(std::vector<std::vector<Block>>& Board , int Row);
int CalculateScore(int Nth);
void GhostBlock(std::vector<std::vector<Block>>& Board , bool CannotMove , bool NewShape , int Pivot[2] , int Score , int Height , int Width);

// screen.cpp Part :
void Draw(std::vector<std::vector<Block>> Board , int NextShapeType , std::vector<std::vector<int>> NextShapeCords , int Score , long long int ElapsedTime , int Height , int Width);
int Menu();
int Level();
std::string Nickname();
int GameOver();
void LeaderboardDraw(std::vector<LB> Leaderboard);
int Pause();
std::string TetrisSize ();