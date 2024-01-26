#include "tetris.hpp"

void Play(Game game) { 
    int COUNT = 1; 
    // In Micorseconds : 
    int DeltaTime = 1000000 / game.FPS;
    
    while (!game.GameOver) {
        if (game.NewShape) {
            int ShapeType = RandomShape(game.CurrentShape); 
            AddShape(game.Board , ShapeType , game.GameOver , game.ShapeCords[ShapeType - 1] , game.Pivot); 
            game.CurrentShape = ShapeType;

            if (game.GameOver) {
                break;
            }

            Drop(game.Board , game.CannotMove , game.NewShape , game.Pivot , game.Score);
            game.NewShape = false;  
        
        }

        // Level is gonna based on the number we mod with COUNT 
        if (COUNT % 10 == 0) {
            Drop(game.Board , game.CannotMove , game.NewShape , game.Pivot , game.Score);
        }

        char ch = Getch();
        
        if (ch == 's') {
            Drop(game.Board , game.CannotMove , game.NewShape , game.Pivot , game.Score);

        } else if (ch == 'a') {
            MoveLeft(game.Board , game.NewShape , game.Pivot);

        } else if (ch == 'd') {
            MoveRight(game.Board , game.NewShape , game.Pivot);

        } else if (ch == 'w') {
            Rotate(game.Board , game.NewShape , game.Pivot);

        }

        usleep(DeltaTime); 
        Cls();
        COUNT++;
        Draw(game.Board);
        CompletedRows(game.Board , game.Score);

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

void Drop(Block Board[18][10] , bool& CannotMove , bool& NewShape , int Pivot[2] , int& Score) {
    std::vector<std::vector<int>> Cords = DroppingBlock(Board); 
    int Shape = Board[Cords[0][0]][Cords[0][1]].Shape; 

    for (int i = 0 ; i < Cords.size() ; i++) {
        if (Cords[i][0] + 1 > 17 ) {
            CannotMove = true ; 
            NewShape= true;
            BlockFall(Board , Cords , Score);
            return ; 
        }

        if (Board[Cords[i][0] + 1][Cords[i][1]].Shape != 0 & Board[Cords[i][0] + 1][Cords[i][1]].Dropping == true) {
            continue;

        } else if (Board[Cords[i][0] + 1][Cords[i][1]].Shape != 0) {
            CannotMove = true; 
            NewShape = true;
            BlockFall(Board , Cords , Score);
            return; 
        }
    } 

    for (int i = 0 ; i < Cords.size() ; i++) {
        Board[Cords[i][0]][Cords[i][1]].Shape = 0; 
        Board[Cords[i][0]][Cords[i][1]].Dropping = false; 
    } 

    for (int i = 0 ; i < Cords.size() ; i++) {
        Board[Cords[i][0] + 1][Cords[i][1]].Shape = Shape; 
        Board[Cords[i][0] + 1][Cords[i][1]].Dropping = true;
    }

    Pivot[0] += 1;

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

void RandomShape(int CurrentShape , int& NextShape) {
    std::random_device rd ; 
    std::mt19937 gen(rd()) ;
    std::uniform_int_distribution<int> Distr(1, 7); 
    int NextShape= Distr(gen); 

    // Prevent to generate repetative Shape
    while (NextShape == CurrentShape) {
        NextShape = Distr(gen); 
    }

    return; 
}


void AddShape(Block Board[18][10] , int ShapeType , bool& GameOver , std::vector<std::vector<int>> BlockCords , int Pivot[2]) {
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
    
    Pivot[0] = BlockCords[0][0];
    Pivot[1] = BlockCords[0][1];

    return;
}


void BlockFall(Block Board[18][10] , std::vector<std::vector<int>> Cords , int& Score) {
    for (int i = 0 ; i < Cords.size() ; i++) {
        Board[Cords[i][0]][Cords[i][1]].Dropping = false; 
    }

    Score += 16;
    return;
}


void MoveRight(Block Board[18][10] , bool& NewShape , int Pivot[2]) {
    std::vector<std::vector<int>> Cords = DroppingBlock(Board); 
    int Shape = Board[Cords[0][0]][Cords[0][1]].Shape;
    
    for (int i = 0 ; i < Cords.size() ; i++) {
        if (Cords[i][1] + 1 > 9 ) {
            // beep sound
            return;

        }

        if (Board[Cords[i][0]][Cords[i][1] + 1].Shape != 0 & Board[Cords[i][0]][Cords[i][1] + 1].Dropping == true) {
            continue;

        } else if (Board[Cords[i][0]][Cords[i][1] + 1].Shape != 0) {
            // beep sound
            return;

        } 
    }

    for (int i = 0 ; i < Cords.size() ; i++) {
        Board[Cords[i][0]][Cords[i][1]].Shape = 0; 
        Board[Cords[i][0]][Cords[i][1]].Dropping = false;

    }

    for (int i = 0 ; i < Cords.size() ; i++) {
        Board[Cords[i][0]][Cords[i][1] + 1].Shape = Shape; 
        Board[Cords[i][0]][Cords[i][1] + 1].Dropping = true;
    }

    Pivot[1] += 1;

}


void MoveLeft(Block Board[18][10] , bool& NewShape , int Pivot[2]){
    std::vector<std::vector<int> > Cords = DroppingBlock(Board); 
    int Shape = Board[Cords[0][0]][Cords[0][1]].Shape;
    
    for (int i = 0 ; i < Cords.size() ; i++) {
        if (Cords[i][1] - 1 < 0) {
            // beep sound
            return;

        }

        if (Board[Cords[i][0]][Cords[i][1] - 1].Shape != 0 & Board[Cords[i][0]][Cords[i][1] - 1].Dropping == true) {
            continue;

        } else if (Board[Cords[i][0]][Cords[i][1] - 1].Shape != 0) {
            // beep sound
            return; 

        }
    }

    for (int i = 0 ; i < Cords.size() ; i++) {
        Board[Cords[i][0]][Cords[i][1]].Shape = 0; 
        Board[Cords[i][0]][Cords[i][1]].Dropping = false;
    } 

    for (int i = 0 ; i < Cords.size() ; i++) {
        Board[Cords[i][0]][Cords[i][1] - 1].Shape = Shape; 
        Board[Cords[i][0]][Cords[i][1] - 1].Dropping = true;
    }

    Pivot[1] -= 1;

}


void Rotate(Block Board[18][10] , bool& NewShape , int Pivot[2]) {
    std::vector<std::vector<int>> Cords = DroppingBlock(Board);
    std::vector<std::vector<int>> RotatedCords;
    int Shape = Board[Cords[0][0]][Cords[0][1]].Shape;
    float XCenter = 0.0 , YCenter = 0.0;

    if (Shape == 1 || Shape == 2) {
        for (int i = 0 ; i < Cords.size() ; i++) {
            XCenter += Cords[i][0];
            YCenter += Cords[i][1];
        }
        XCenter /= Cords.size();
        YCenter /= Cords.size();

    } else {
        XCenter = Pivot[0];
        YCenter = Pivot[1];
    }

    for (int i = 0 ; i < Cords.size() ; i++) {
        float XO = Cords[i][0] - XCenter;
        float YO = Cords[i][1] - YCenter;

        int X = XCenter + YO;
        int Y = YCenter - XO;

        RotatedCords.push_back({X,Y});
    }

    for (int i = 0 ; i < Cords.size() ; i++) {
        if (RotatedCords[i][0] > 17 || RotatedCords[i][0] < 0) {
            // beep sound
            return;

        } else if (RotatedCords[i][1] > 9 || RotatedCords[i][1] < 0) {
            // beep sound
            return;

        } else if (Board[RotatedCords[i][0]][RotatedCords[i][1]].Shape != 0 & Board[RotatedCords[i][0]][RotatedCords[i][1]].Dropping == true) {
            continue;

        } else if (Board[RotatedCords[i][0]][RotatedCords[i][1]].Shape != 0) {
            // beep sound
            return;
        }
    }

    for (int i = 0 ; i < Cords.size() ; i++) {
        Board[Cords[i][0]][Cords[i][1]].Shape = 0; 
        Board[Cords[i][0]][Cords[i][1]].Dropping = false;
    } 

    for (int i = 0 ; i < RotatedCords.size() ; i++) {
        Board[RotatedCords[i][0]][RotatedCords[i][1]].Shape = Shape;
        Board[RotatedCords[i][0]][RotatedCords[i][1]].Dropping = true;

    }
}


void CompletedRows(Block Board[18][10] , int& Score) {
    std::vector<int> Rows; 
    int NumberOfRows = 0;

    for (int i = 0 ; i < 18 ; i++) {
        bool Completed = true;
        for (int j = 0 ; j < 10 ; j++) {
            if (Board[i][j].Shape == 0) {
                Completed = false;
            }
        } 

        if (Completed) {
            for (int j = 0 ; j < 10 ; j++) {
                Board[i][j].Shape = 0;
            }

            NumberOfRows++;
            Rows.push_back(i);
        }
    }

    int TotalScore = CalculateScore(NumberOfRows);
    Score += TotalScore;

    Cls();
    Draw(Board);
    
    for (int i = 0 ; i < Rows.size() ; i++) {
        std::cout << Rows[i] ; 
        ShiftDown(Board , Rows[i]);

    }

}


void ShiftDown(Block Board[18][10] , int Row) {
    for (int i = Row ; i > 0 ; i--) {
        for (int j = 0 ; j < 10 ; j++) {
            Board[i][j].Shape = Board[i - 1][j].Shape;
            Board[i][j].Dropping = Board[i - 1][j].Dropping;
        }
    }
} 

// Calculate Score based on NES Scoring : 
// X[n]=X[n-1]*(2+2^(n-3))​
int CalculateScore(int Nth) {
    if (Nth == 0) {
        return 0;
    } else if (Nth == 1) {
        return 40;
    }

    return CalculateScore(Nth - 1) * (2 + std::pow(2, Nth - 3));
}