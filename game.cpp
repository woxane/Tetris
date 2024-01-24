#include "tetris.hpp"

void Play(Game game) { 
    int COUNT = 1; 
    // In Micorseconds : 
    int DeltaTime = 1000000 / game.FPS;
    
    while (!game.GameOver) {
        if (game.NewShape) {
            int ShapeType = RandomShape(game.CurrentShape); 
            AddShape(game.Board , ShapeType , game.GameOver , game.ShapeCords[ShapeType - 1]); 
            game.CurrentShape = ShapeType;

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
        COUNT++;
        Draw(game.Board);

        if (game.CannotMove) {
            CheckDeath(game.Board , game.GameOver); 
        }
    }
    std::cout << std::endl << "HEH YOU FUCKING LOSER YOU LOST";
}


std::vector<std::vector<int>> DroppingBlock(Block Board[18][10]) {
    std::vector<std::vector<int>> Cords; 
    for (int Col = 0 ; Col < 18 ; Col++) {
        for (int Row = 0 ; Row < 10 ; Row++) {
             if (Board[Col][Row].Dropping) {
                 std::vector<int> Cord = {Col , Row};
                 Cords.push_back(Cord);
             }
         }
     }

    return Cords;       
}

void Drop(Block Board[18][10] , bool& CannotMove , bool& NewShape) {
    std::vector<std::vector<int>> Cords = DroppingBlock(Board); 
    int Shape = Board[Cords[0][0]][Cords[0][1]].Shape; 

    std::sort(Cords.begin() , Cords.end() , MoveDownCompare);

    for (int i = 0 ; i < Cords.size() ; i++) {
        if (Cords[i][0] + 1 > 17 ) {
            CannotMove = true ; 
            NewShape= true;
            BlockFall(Board , Cords);
            return ; 
        }

        if (Board[Cords[i][0] + 1][Cords[i][1]].Shape != 0 & Board[Cords[i][0] + 1][Cords[i][1]].Dropping == true) {
            continue;

        } else if (Board[Cords[i][0] + 1][Cords[i][1]].Shape != 0) {
            CannotMove = true; 
            NewShape = true;
            BlockFall(Board , Cords);
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


void CheckDeath(Block Board[18][10] , bool& GameOver) {
    for (int Row = 0 ; Row < 10 ; Row++) {
        if (Board[0][Row].Dropping == false & Board[0][Row].Shape != 0 ) {
            GameOver = true;
            return ; 
        }
    }

    GameOver = false;
    return ; 
}

int RandomShape(int CurrentShape) {
    std::random_device rd ; 
    std::mt19937 gen(rd()) ;
    std::uniform_int_distribution<int> Distr(1, 7); 
    int Num = Distr(gen); 

    // Prevent to generate repetative Shape
    while (Num == CurrentShape) {
        Num = Distr(gen); 
    }

    return Num ; 
}


void AddShape(Block Board[18][10] , int ShapeType , bool& GameOver , std::vector<std::vector<int>> BlockCords) {
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


void BlockFall(Block Board[18][10] , std::vector<std::vector<int>> Cords) {
    for (int i = 0 ; i < Cords.size() ; i++) {
        Board[Cords[i][0]][Cords[i][1]].Dropping = false; 
    }

    return;
}


void MoveRight(Block Board[18][10] , bool& CannotMove , bool& NewShape) {
    std::vector<std::vector<int>> Cords = DroppingBlock(Board); 
    int Shape = Board[Cords[0][0]][Cords[0][1]].Shape;
    
    std::sort(Cords.begin() , Cords.end() , MoveRightCompare);

    for (int i = 0 ; i < Cords.size() ; i++) {
        if (Cords[i][1] + 1 > 9 ) {
            CannotMove = true;
            NewShape = true; 
            BlockFall(Board , Cords);
            return;

        }

        if (Board[Cords[i][0]][Cords[i][1] + 1].Shape != 0 & Board[Cords[i][0]][Cords[i][1] + 1].Dropping == true) {
            continue;

        } else if (Board[Cords[i][0]][Cords[i][1] + 1].Shape != 0) {
            CannotMove = true;
            NewShape = true;
            BlockFall(Board , Cords);
            return; 

        }
    }

    for (int i = 0 ; i < Cords.size() ; i++) {
        Board[Cords[i][0]][Cords[i][1]].Shape = 0; 
        Board[Cords[i][0]][Cords[i][1]].Dropping = false; 
        Board[Cords[i][0]][Cords[i][1] + 1].Shape = Shape; 
        Board[Cords[i][0]][Cords[i][1] + 1].Dropping = true;
    }
}


void MoveLeft(Block Board[18][10] , bool& CannotMove , bool& NewShape){
    std::vector<std::vector<int> > Cords = DroppingBlock(Board); 
    int Shape = Board[Cords[0][0]][Cords[0][1]].Shape;
    
    std::sort(Cords.begin() , Cords.end() , MoveLeftCompare);

    for (int i = 0 ; i < Cords.size() ; i++) {
        if (Cords[i][1] - 1 < 0) {
            CannotMove = true;
            NewShape = true; 
            BlockFall(Board , Cords);
            return;

        }

        if (Board[Cords[i][0]][Cords[i][1] - 1].Shape != 0 & Board[Cords[i][0]][Cords[i][1] - 1].Dropping == true) {
            continue;

        } else if (Board[Cords[i][0]][Cords[i][1] - 1].Shape != 0) {
            CannotMove = true;
            NewShape = true;
            BlockFall(Board , Cords);
            return; 

        }
    }

    for (int i = 0 ; i < Cords.size() ; i++) {
        Board[Cords[i][0]][Cords[i][1]].Shape = 0; 
        Board[Cords[i][0]][Cords[i][1]].Dropping = false; 
        Board[Cords[i][0]][Cords[i][1] - 1].Shape = Shape; 
        Board[Cords[i][0]][Cords[i][1] - 1].Dropping = true;
    }
}