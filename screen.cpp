#include "tetris.hpp"

void Draw(Block Board[20][10]) {
    for (int Col = 0 ; Col < 22 ; Col++) {
        for (int Row = 0 ; Row < 12 ; Row++) {
            if (Col == 0) {
                std::cout << "┏━━━━━woxane/tetris━━┓";
                break; 

            } else if (Col == 21) {
                std::cout << "┗━━━━━━━━━━━━━━━━━━━━┛";
                break; 

            } else if (Row == 0 || Row == 11) {
                std::cout << "┃";

            } else if (Board[Col - 1][Row - 1].Shape != 0 ) {
                std::cout << "██";
            } else {
                std::cout << "  " ;  

            }
        }
        std::cout << std::endl ; 
    }
}
