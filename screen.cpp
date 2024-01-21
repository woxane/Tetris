#include "tetris.hpp"

void Draw(Block Board[20][10]) {
    for (int Col = 0 ; Col <= 20 ; Col++) {
        for (int Row = 0 ; Row <= 10 ; Row++) {
            if (Col == 0 & Row == 0) {
                std::cout << "┏━━━━━woxane/tetris━━┓";
                break; 

            } else if (Col == 20 & Row == 0) {
                std::cout << "┗━━━━━━━━━━━━━━━━━━━━┛";
                break; 
            }

            if (Row == 0 || Row == 20) {
                std::cout << "┃";
                continue;  
            }

            if (Board[Col - 1][Row - 1].Shape != 0 ) {
                std::cout << "█";
            }
        }
    }
}
