#include "tetris.hpp"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define ORANGE  "\033[38;2;255;165;0m"
#define PURPLE  "\033[38;2;128;0;128m"

void Draw(Block Board[18][10]) {
    for (int Col = 0 ; Col < 20 ; Col++) {
        for (int Row = 0 ; Row < 12 ; Row++) {
            if (Col == 0) {
                std::cout << "┏━━━━━woxane/tetris━━┓";
                break; 

            } else if (Col == 19) {
                std::cout << "┗━━━━━━━━━━━━━━━━━━━━┛";
                break; 

            } else if (Row == 0 || Row == 11) {
                std::cout << "┃";

            } else if (Board[Col - 1][Row - 1].Shape != 0 ) {
                switch (Board[Col - 1][Row - 1].Shape) {
                    case 1 : 
                        std::cout << YELLOW;
                        break;

                    case 2 : 
                        std::cout << CYAN;
                        break;

                    case 3 :
                        std::cout << BLUE;
                        break;

                    case 4 :
                        std::cout << ORANGE;
                        break;

                    case 5 : 
                        std::cout << RED;
                        break;

                    case 6 : 
                        std::cout << GREEN;
                        break;

                    case 7 :
                        std::cout << PURPLE; 
                        break;
                }

                std::cout << "██" << RESET;

            } else {
                std::cout << "  " ;  

            }
        }
        std::cout << std::endl ; 
    }
}



int Menu() {
    initscr();
    raw();
    keypad(stdscr, TRUE);

    int choice;
    int highlight = 0;
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    const char *options[] = {"New Game", "How To Play", "Leaderboard", "Exit"};

    int boxHeight = 6;
    int boxWidth = 20;
    int boxStartY = (maxY - boxHeight) / 2;
    int boxStartX = (maxX - boxWidth) / 2;

    while (true) {
        clear();

        box(stdscr, 0, 0);
        refresh();

        for (int i = 0; i < 4; i++) {
            if (i == highlight) {
                attron(A_REVERSE);
            }
            mvprintw(boxStartY + i + 1, boxStartX + (boxWidth - std::strlen(options[i])) / 2, "%s", options[i]);
            attroff(A_REVERSE);
        }

        choice = getch();
        switch (choice) {
            case KEY_UP:
                highlight = (highlight + 3) % 4;
                break;
            case KEY_DOWN:
                highlight = (highlight + 1) % 4;
                break;
            case 10:
                endwin();
                return highlight;
        }
    }

    endwin();
    return 3;
}