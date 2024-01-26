#include <iostream>
#include "tetris.hpp"



void NewGame() {
	std::string Name = Nickname();
	int GameLevel = Level();

	Game tetris; 
	tetris.FPS = 25;
	tetris.Name = Name;
	tetris.Level = GameLevel; 
	for (int i = 0 ; i < tetris.BoardHeight ; i++) {
		std::vector<Block> Row;
		for (int j = 0 ; j < tetris.BoardWidth ; j++) {
			Block temp;
			Row.push_back(temp);
		}
		tetris.Board.push_back(Row);
	}

	Play(tetris);
}



int main() {

	while (true) {
		int MenuChoose = Menu();
		bool Quit = false;
		int GameLevel;

		switch (MenuChoose) {
			case 0 : 
				// New Game
				while (!Quit) {
					NewGame();
					int GameOverChoose = GameOver();
					if (GameOverChoose == 0) {
						Quit = true;
					}
				}
				break;
			
			case 1 : 
				std::cout << "Saved Game";
				// Saved Game
				break;

			case 2 : 
				std::cout << "How to play";
				// How To play 
				break;

			case 3 : 
				// Leaderboard 
				GameLevel = Level();
				LeaderboardDraw(LeaderboardRead(GameLevel));
				break;

			case 4 : 
				// Exit
				std::cout << "FUc";
				return 0;
				break;

		}

	}


	return 0 ;
}
