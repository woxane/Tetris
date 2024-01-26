#include "tetris.hpp"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define ORANGE  "\033[38;2;255;165;0m"
#define PURPLE  "\033[38;2;128;0;128m"

void Draw(Block Board[18][10] , int NextShapeType , std::vector<std::vector<int>> NextShapeCords , int Score , long long int ElapsedTime) {
    std::string ConvertedTime = ConvertTime(ElapsedTime);
    std::cout << "Elapsed Time : " << ConvertedTime << std::endl;

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

            if (0 < Col & Col < 6 & Row == 11) {
                std::cout << "    ";
                if (Col == 1) {
                    std::cout << "┏━━next━━━┓";
                    continue;

                } else if (Col == 5) {
                    std::cout << "┗━━━━━━━━━┛";
                    continue;
                }

                for (int i = 0 ; i < 6 ; i++) {
                    if (i == 0) {
                        std::cout << "┃";
                        continue;
                        
                    } else if (i == 5) {
                        std::cout << " ┃";
                        continue;
                    } 

                    std::vector<int> Pos = {Col - 2 , i + 2};
                    std::vector<std::vector<int>>::iterator It = std::find(NextShapeCords.begin(), NextShapeCords.end(), Pos);

                    if (It != NextShapeCords.end()) {
                        switch (NextShapeType) {
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
                        std::cout << "  ";

                    }

                }

            }

            if (5 < Col & Col < 11 & Row == 11) {
                std::cout << "    ";
                if (Col == 6) {
                    std::cout << "┏━━score━━┓";
                    continue;

                } else if (Col == 10) {
                    std::cout << "┗━━━━━━━━━┛";
                    continue ; 
                } else {
                    if (Col == 8) { 
                        std::string BoxScore = "";
                        int NumLength = (std::to_string(Score)).length();
                        // WS as White space
                        int LeftWS = (9 - NumLength) / 2; 
                        int RightWS = 9 - NumLength - LeftWS; 

                        for (int i = 0 ; i < LeftWS ; i++) {
                            BoxScore += " ";
                        } 

                        BoxScore += std::to_string(Score);

                        for (int i = 0 ; i < RightWS ; i++) {
                            BoxScore += " ";
                        }
                        std::cout << "┃" << BoxScore << "┃";

                    } else {
                        std::cout << "┃         ┃";
                    }
                }
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


int Level() {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    int maxRows, maxCols;
    getmaxyx(stdscr, maxRows, maxCols);

    const char* options[] = {"Noob" , "Beginner" , "Pro", "Hacker" , "GODD!"};
    int currentOption = 0;

    int boxHeight = 3;
    int boxWidth = 15;
    int boxStartY = (maxRows - boxHeight) / 2;
    int boxStartX = (maxCols - boxWidth) / 2;

    int ch;
    do {
        clear();

        box(stdscr, 0, 0);
        refresh();

        mvprintw(boxStartY, boxStartX + (boxWidth - strlen("Level:")) / 2 - 3, "Level:");
        refresh();

        mvprintw(boxStartY + 1, boxStartX + (boxWidth - strlen(options[currentOption])) / 2, "< %s >", options[currentOption]);
        refresh();

        ch = getch();

        switch (ch) {
            case KEY_RIGHT:
                currentOption = (currentOption + 1) % 3;
                break;

            case KEY_LEFT:
                currentOption = (currentOption + 2) % 3;
                break;
        }

    } while (ch != 10); 
    endwin();
    return currentOption;
}


std::string Nickname() {
    initscr();
    raw();
    keypad(stdscr, TRUE);

    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    int boxHeight = 5;
    int boxWidth = 30;
    int boxStartY = (maxY - boxHeight) / 2;
    int boxStartX = (maxX - boxWidth) / 2;

    char nickname[30];
    memset(nickname, 0, sizeof(nickname));

    int ch;
    int cursorPosition = 0;
    bool editing = true;

    while (editing) {
        clear();

        box(stdscr, 0, 0);
        refresh();

        mvprintw(boxStartY + 1, boxStartX + (boxWidth - strlen("Profile's Nickname:")) / 2, "Profile's Nickname:");

        mvprintw(boxStartY + 2, boxStartX + (boxWidth - strlen(nickname)) / 2, "%s", nickname);

        move(boxStartY + 2, boxStartX + (boxWidth - strlen(nickname)) / 2 + cursorPosition);

        ch = getch();
        switch (ch) {
            case 10: 
                editing = false;
                break;

            case 127:
                if (cursorPosition > 0) {
                    cursorPosition--;
                    nickname[cursorPosition] = '\0';
                }
                break;

            default:
                if (std::isprint(ch) && cursorPosition < 29) {
                    nickname[cursorPosition] = ch;
                    cursorPosition++;
                }
                break;
        }
    }
    
    endwin();
    return std::string(nickname);
}