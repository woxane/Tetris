#include "tetris.hpp"

std::vector<std::vector<int>> DropingBlock(Block Board[20][10]) {
    std::vector<std::vector<int>> Cords; 
    for (int Col = 0 ; Col < 20 ; Col++) {
        for (int Row = 0 ; Row < 10 ; Row++) {
            if (Board[Col][Row].Dropping) {
                std::vector<int> Cord = {Col , Row};
                Cords.push_back(Cord);
            }
        }
    }
    std::sort(Cords.begin() , Cords.end() , Compare);

    return Cords;      

}