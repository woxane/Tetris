#include "tetris.hpp"

void Play(Game game) { 
    int COUNT = 1; 
    // In Micorseconds : 
    int DeltaTime = 1000000 / game.FPS;
    
    while (!game.GameOver) {
        Draw(game.Board); 

        if (game.NewShape) {
            int ShapeType = RandomShape(); 
            AddShape(game.Board , ShapeType , game.GameOver , game.ShapeCords[ShapeType]); 

            if (game.GameOver) {
                break;
            }

            Drop(game.Board , game.CannotMove , game.NewShape);
            game.NewShape = false;  
        
        }

        // Level is gonna based on the number we mod with COUNT 
        if (COUNT % 10 == 0) {
            Drop(game.Board , game.CannotMove , game.NewShape);
        }

        usleep(DeltaTime); 
        Cls();
        CheckDeath(game.Board , game.GameOver); 
        COUNT++;

    }
}


std::pair<std::vector<std::vector<int>> , std::vector<std::vector<int>>> DroppingBlock(Block Board[20][10]) {
    std::vector<std::vector<int>> Cords; 
    for (int Col = 0 ; Col < 20 ; Col++) {
        for (int Row = 0 ; Row < 10 ; Row++) {
             if (Board[Col][Row].Dropping) {
                 std::vector<int> Cord = {Col , Row};
                 Cords.push_back(Cord);
             }
         }
     }
    // MainCords are cordination that is important for drop 
    std::vector<std::vector<int>> MainCords; 
    for (int Row = 0 ; Row < 10 ; Row++) {
        for (int Col = 19 ; Col >= 0 ; Col--) {
            if (Board[Col][Row].Dropping) {
                std::vector<int> Cord = {Col , Row};
                MainCords.push_back(Cord); 
                break ; 
            }
        }
    }

    std::sort(Cords.begin() , Cords.end() , Compare);
    std::sort(MainCords.begin() , MainCords.end() , Compare);

    return {MainCords , Cords};       
}

void Drop(Block Board[20][10] , bool& CannotMove , bool& NewShape) {
    std::pair<std::vector<std::vector<int>> , std::vector<std::vector<int>>> Data = DroppingBlock(Board);
    std::vector<std::vector<int> > Cords = Data.second; 
    std::vector<std::vector<int> > MainCords = Data.first;  

    int Shape = Board[Cords[0][0]][Cords[0][1]].Shape; 

    for (int i = 0 ; i < MainCords.size() ; i++) {
        if (MainCords[i][0] + 1 > 19 ) {
            CannotMove = true ; 
            NewShape= true;
            Board[MainCords[i][0]][MainCords[i][1]].Dropping = false ; 
            return ; 
        }

        if (Board[MainCords[i][0] + 1][MainCords[i][1]].Shape != 0) {
            CannotMove = true; 
            NewShape = true;
            Board[MainCords[i][0]][MainCords[i][1]].Dropping = false ; 
            return; 
        }
    } 

    for (int i = 0 ; i < Cords.size() ; i++) {
        Board[Cords[i][0]][Cords[i][1]].Shape = 0; 
        Board[Cords[i][0]][Cords[i][1]].Dropping = false; 
        Board[Cords[i][0] + 1][Cords[i][1]].Shape = Shape; 
        Board[Cords[i][0] + 1][Cords[i][1]].Dropping = true;
    }
}


void CheckDeath(Block Board[20][10] , bool& GameOver) {
    for (int Row = 0 ; Row < 10 ; Row++) {
        if (Board[0][Row].Dropping == false & Board[0][Row].Shape != 0 ) {
            GameOver = true;
            return ; 
        }
    }

    GameOver = false;
    return ; 
}

int RandomShape() {
    std::random_device rd ; 
    std::mt19937 gen(rd()) ;
    std::uniform_int_distribution<int> Distr(1, 7); 
    int Num = Distr(gen); 

    return Num ; 
}


void AddShape(Block Board[20][10] , int ShapeType , bool& GameOver , std::vector<std::vector<int>> BlockCords) {
    for (int i = 0 ; i < BlockCords.size() ; i++) {
        if (Board[BlockCords[i][0]][BlockCords[i][1]].Shape != 0) {
            GameOver = true;
            return;
        }
    }

    for (int i = 0 ; i < BlockCords.size() ; i++) {
        Board[BlockCords[i][0]][BlockCords[i][1]].Shape = ShapeType;
        Board[BlockCords[i][0]][BlockCords[i][1]].Dropping = true;
    }
    
    return;
}