#include "tetris.hpp"

void Play(Game game) { 
    int COUNT = 1; 
    // In Micorseconds : 
    int DeltaTime = 1000000 / game.FPS;
    
    while (!game.GameOver) {
        if (game.NewShape) {
            RandomShape(game.CurrentShape , game.NextShape); 
            AddShape(game.Board , game.CurrentShape , game.GameOver , game.ShapeCords[game.CurrentShape - 1] , game.Pivot); 


            CheckDeath(game.Board , game.GameOver , game.BoardWidth); 
            
            if (game.GameOver) {
                break;
            }

            Drop(game.Board , game.CannotMove , game.NewShape , game.Pivot , game.Score , game.BoardHeight , game.BoardWidth);

            game.CannotMove = false;
            game.NewShape = false;  
            
            if (game.Level == 0) {
                GhostBlock(game.Board , game.CannotMove , game.NewShape , game.Pivot , game.Score , game.BoardHeight , game.BoardWidth); 
            }
        }

        // Level is gonna based on the number we mod with COUNT
        std::cout << game.Level ;
        if (COUNT % (10 - 2 * game.Level) == 0) {
            Drop(game.Board , game.CannotMove , game.NewShape , game.Pivot , game.Score , game.BoardHeight , game.BoardWidth);
        }

        char ch = Getch();
        
        if (ch == 's') {
            Drop(game.Board , game.CannotMove , game.NewShape , game.Pivot , game.Score , game.BoardHeight , game.BoardWidth , true);

        } else if (ch == 'a') {
            MoveLeft(game.Board , game.NewShape , game.Pivot , game.BoardHeight , game.BoardWidth);

        } else if (ch == 'd') {
            MoveRight(game.Board , game.NewShape , game.Pivot , game.BoardHeight , game.BoardWidth);

        } else if (ch == 'w') {
            Rotate(game.Board , game.NewShape , game.Pivot , game.BoardHeight , game.BoardWidth);

        } else if (ch == ' ') {
            while (!game.CannotMove) {
                Drop(game.Board , game.CannotMove , game.NewShape , game.Pivot , game.Score , game.BoardHeight , game.BoardWidth , true , true);
            }
        } else if (ch == 'p') {
            int Choose = Pause();
            std::cout << Choose;
            switch (Choose) {
                case 1 : 
                    break;
                
                case 2 : 
                    // Save game 
                    // Not implemented
                    break;
                
                case 3 : 
                    // Quit
                    return;
                    break;

            }
        }

        if (game.Level == 0) {
            GhostBlock(game.Board , game.CannotMove , game.NewShape , game.Pivot , game.Score , game.BoardHeight , game.BoardWidth); 
        }

        usleep(DeltaTime); 
        Cls();
        COUNT++;
        game.ElapsedTime += DeltaTime;
        Draw(game.Board , game.NextShape , game.ShapeCords[game.NextShape - 1] , game.Score , game.ElapsedTime , game.BoardHeight , game.BoardWidth);

        if (game.CannotMove) {
            CompletedRows(game.Board , game.Score , game.NextShape , game.ShapeCords[game.NextShape - 1] , game.ElapsedTime , game.BoardHeight , game.BoardWidth , DeltaTime);
        }

        if (game.CannotMove) {
            CheckDeath(game.Board , game.GameOver , game.BoardWidth); 
        }
    }
    LB Data ; 
    Data.Name = game.Name;
    Data.Score = game.Score;
    Data.ElapsedTime = game.ElapsedTime; 
    LeaderboardAdd(Data , game.Level);

}


std::vector<std::vector<int>> DroppingBlock(std::vector<std::vector<Block>>& Board , int Height , int Width) {
    std::vector<std::vector<int>> Cords; 
    for (int Col = 0 ; Col < Height ; Col++) {
        for (int Row = 0 ; Row < Width ; Row++) {
             if (Board[Col][Row].Dropping) {
                 std::vector<int> Cord = {Col , Row};
                 Cords.push_back(Cord);
             }
         }
     }

    return Cords;       
}

void Drop(std::vector<std::vector<Block>>& Board , bool& CannotMove , bool& NewShape , int Pivot[2] , int& Score , int Height , int Width , bool UserInput , bool Fall , bool Ghost) {
    std::vector<std::vector<int>> Cords = DroppingBlock(Board , Height , Width); 

    // When Neither we can have any New Shape or Move
    if (Cords.size() == 0) {
        CannotMove = true;
        return;
    }

    int Shape = Board[Cords[0][0]][Cords[0][1]].Shape; 

    for (int i = 0 ; i < Cords.size() ; i++) {
        if (Cords[i][0] + 1 > Height - 1 ) {
            CannotMove = true ; 
            NewShape= true;

            if (Ghost) {
                return; 
            }

            BlockFall(Board , Cords);
            return ; 
        }

        if (Board[Cords[i][0] + 1][Cords[i][1]].Shape != 0 & Board[Cords[i][0] + 1][Cords[i][1]].Dropping == true) {
            continue;

        } else if (Board[Cords[i][0] + 1][Cords[i][1]].Shape != 0) {
            CannotMove = true; 
            NewShape = true;

            if (Ghost) {
                return; 
            }

            BlockFall(Board , Cords);
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

    if (UserInput) { 
        if (Fall) {
            Score += 2;
        } else {
            Score++;
        }
    }

    Pivot[0] += 1;

}


void CheckDeath(std::vector<std::vector<Block>>& Board , bool& GameOver , int Width) {
    for (int Row = 0 ; Row < Width ; Row++) {
        if (Board[0][Row].Dropping == false & Board[0][Row].Shape != 0 ) {
            GameOver = true;
            return ; 
        }
    }

    GameOver = false;
    return ; 
}

void RandomShape(int& CurrentShape , int& NextShape , bool FirstTime) {
    std::random_device rd ; 
    std::mt19937 gen(rd()) ;
    std::uniform_int_distribution<int> Distr(1, 7); 
    int Num = Distr(gen);

    // Prevent to generate repetative Shape
    while (Num == NextShape) {
        Num = Distr(gen); 
    }

    if (CurrentShape == NextShape) {
        CurrentShape = Num;
        RandomShape(CurrentShape , NextShape , 1);

    } else if (FirstTime) {
        while (Num == CurrentShape) {
            Num = Distr(gen);
        }

        NextShape = Num;
    } else {
        CurrentShape = NextShape; 
        NextShape = Num;
    }

    return; 
}


void AddShape(std::vector<std::vector<Block>>& Board , int ShapeType , bool& GameOver , std::vector<std::vector<int>> BlockCords , int Pivot[2]) {
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


void BlockFall(std::vector<std::vector<Block>>& Board , std::vector<std::vector<int>> Cords) {
    for (int i = 0 ; i < Cords.size() ; i++) {
        Board[Cords[i][0]][Cords[i][1]].Dropping = false; 
    }

    return;
}


void MoveRight(std::vector<std::vector<Block>>& Board , bool& NewShape , int Pivot[2] , int Height , int Width) {
    std::vector<std::vector<int>> Cords = DroppingBlock(Board , Height , Width); 
    int Shape = Board[Cords[0][0]][Cords[0][1]].Shape;
    
    for (int i = 0 ; i < Cords.size() ; i++) {
        if (Cords[i][1] + 1 > Width - 1 ) {
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


void MoveLeft(std::vector<std::vector<Block>>& Board , bool& NewShape , int Pivot[2] , int Height , int Width){
    std::vector<std::vector<int> > Cords = DroppingBlock(Board , Height , Width); 
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


void Rotate(std::vector<std::vector<Block>>& Board , bool& NewShape , int Pivot[2] , int Height , int Width) {
    std::vector<std::vector<int>> Cords = DroppingBlock(Board , Height , Width);
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
        if (RotatedCords[i][0] > Height - 1 || RotatedCords[i][0] < 0) {
            // beep sound
            return;

        } else if (RotatedCords[i][1] > Width - 1 || RotatedCords[i][1] < 0) {
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


void CompletedRows(std::vector<std::vector<Block>>& Board , int& Score , int NextShape , std::vector<std::vector<int>> NextShapeCords , long long int ElapsedTime , int Height , int Width , int& DeltaTime) {
    std::vector<int> Rows; 
    int NumberOfRows = 0;

    for (int i = 0 ; i < Height ; i++) {
        bool Completed = true;
        for (int j = 0 ; j < Width ; j++) {
            if (Board[i][j].Shape == 0) {
                Completed = false;
            }
        } 

        if (Completed) {
            for (int j = 0 ; j < Width ; j++) {
                Board[i][j].Shape = 0;
            }

            NumberOfRows++;
            Rows.push_back(i);
        }
    }

    int TotalScore = (Height / 18.0) * (Width / 10.0) * CalculateScore(NumberOfRows);
    Score += TotalScore;
    if (DeltaTime > 15000) {
        DeltaTime -= 1000;

    } 
    Cls();
    Draw(Board , NextShape , NextShapeCords , Score , ElapsedTime , Height , Width);
    
    for (int i = 0 ; i < Rows.size() ; i++) {
        std::cout << Rows[i] ; 
        ShiftDown(Board , Rows[i]);

    }

}


void ShiftDown(std::vector<std::vector<Block>>& Board , int Row) {
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



void GhostBlock(std::vector<std::vector<Block>>& Board , bool CannotMove , bool NewShape , int Pivot[2] , int Score , int Height , int Width) { 
    std::vector<std::vector<Block>> Temp = Board;
    int PivotTemp[2];
    PivotTemp[0] = Pivot[0];
    PivotTemp[1] = Pivot[1];

    while (!CannotMove) {
        Drop(Temp, CannotMove , NewShape , PivotTemp , Score , Height , Width , false , false , true);
    }

    for (int i = 0 ; i < Height ; i++) {
        for (int j = 0 ; j < Width ; j++) {
            Board[i][j].IsGhost = false;
        }
    }

    std::vector<std::vector<int>> Cords = DroppingBlock(Temp, Height , Width);
    for (int i = 0 ; i < Cords.size() ; i++) {
        Board[Cords[i][0]][Cords[i][1]].IsGhost = true;

    }
}