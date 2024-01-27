#include <iostream>
#include "tetris.hpp"



void NewGame() {
	std::string Name = Nickname();
	int GameLevel = Level();
	std::pair<int , int> Size = TetrisSize();
	int H = Size.first;
	int W = Size.second;
	Game tetris; 
	tetris.FPS = 25;
	tetris.Name = Name;
	tetris.Level = GameLevel; 
	tetris.BoardHeight = H;
	tetris.BoardWidth = W;
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
				std::cout << "-KeyBinds : " << std::endl;
				std::cout << "-- 1) You could move right and left with d and a key . " << std::endl;
				std::cout << "-- 2) You could move down faster using s key ." << std::endl;
				std::cout << "-- 3) You could rotate your block using w key . " << std::endl;
				std::cout << "-- 4) You could fall your block using space key . " << std::endl; 
				std::cout << "-Game Flow : " << std::endl;
				std::cout << " -- 1) You must know that there are 5 types of level in this game : " << std::endl;
				std::cout << "---- Noob  ,  Beginner , Pro  ,  Hacker  ,  GODD ." << std::endl;
				std::cout << "-- 2) In the Noob level gaming you have ghost block to help your aim ." << std::endl;
				return 0;
				// How To play 
				break;

			case 3 : 
				// Leaderboard 
				GameLevel = Level();
				LeaderboardDraw(LeaderboardRead(GameLevel));
				break;

			case 4 : 
				// Exit
				return 0;
				break;

		}

	}


	return 0 ;
}
