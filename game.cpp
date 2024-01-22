#include "tetris.hpp"

void Play(Game game) { 
    int COUNT = 1; 
    // In Micorseconds : 
    int DeltaTime = 1000000 / game.FPS;
    
    // This must change to game.Gameover 
    // or something , but for now 
    while (!game.CannotMove) {
        Draw(game.Board); 
        // Level is gonna based on the number we mod with COUNT 
        if (COUNT % 10 == 0) {
            Drop(game.Board , game.CannotMove);
        }

        usleep(DeltaTime); 
        Cls();
        COUNT++;

    }
}


std::vector<std::vector<int>> DroppingBlock(Block Board[20][10]) {
    std::vector<std::vector<int>> Cords; 
    for (int Col = 0 ; Col < 20 ; Col++) {
        for (int Row = 0 ; Row < 10 ; Row++) {
            if (Board[Col][Row].Dropping) {
                std::vector<int> Cord = {Col , Row};
                Cords.push_back(Cord);
            }
        }
    }

    return Cords;      

}

void Drop(Block Board[20][10] , bool& CannotMove) {
    std::vector<std::vector<int> > Cords = DroppingBlock(Board);
    int Shape = Board[Cords[0][0]][Cords[0][1]].Shape; 
    
    for (int i = 0 ; i < Cords.size() ; i++) {
        if (Cords[i][0] + 1 > 19 ) {
            CannotMove = true ; 
            return ; 
        }

        if (Board[Cords[i][0] + 1][Cords[i][1]].Shape != 0) {
            CannotMove = true; 
            Board[Cords[i][0] + 1][Cords[i][1]].Dropping = false ; 
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