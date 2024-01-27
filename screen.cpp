#include "tetris.hpp"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define ORANGE  "\033[38;2;255;165;0m"
#define PURPLE  "\033[38;2;128;0;128m"

void Draw(std::vector<std::vector<Block>> Board , int NextShapeType , std::vector<std::vector<int>> NextShapeCords , int Score , long long int ElapsedTime , int Height , int Width) {
    std::string ConvertedTime = ConvertTime(ElapsedTime);
    std::cout << "Elapsed Time : " << ConvertedTime << std::endl;

    for (int Col = 0 ; Col < Height + 2 ; Col++) {
        for (int Row = 0 ; Row < Width + 2; Row++) {
            if (Col == 0) {
                std::string Name = "woxane/tetris";
                std::string Head; 
                int LeftLines =  (2*Width - Name.length() ) / 2;
                int RightLines = 2*Width - LeftLines - Name.length();

                Head += "┏";
                for (int i = 0 ; i < LeftLines ; i++) {
                    Head += "━";    
                }
                Head += Name;
                for (int i = 0 ; i < RightLines ; i++) {
                    Head += "━";    
                }
                Head += "┓";

                std::cout << Head;
                break; 

            } else if (Col == Height + 1) {
                std::string End; 

                End += "┗";
                for (int i = 0 ; i < 2*Width ; i++) {
                    End += "━";
                }
                End += "┛";

                std::cout << End;
                break; 

            } else if (Row == 0 || Row == Width + 1) {
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

            } else if (Board[Col - 1][Row - 1].Shape == 0 & Board[Col - 1][Row - 1].IsGhost) {
                std::cout << "░░";

            } else {
                std::cout << "  " ;  

            }
            // XXX
            if (0 < Col & Col < 6 & Row == Width + 1) {
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
            // XXX
            if (5 < Col & Col < 11 & Row == Width + 1) {
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
    const char *options[] = {"New Game", "Saved Game" ,"How To Play", "Leaderboard", "Exit"};

    int boxHeight = 6;
    int boxWidth = 20;
    int boxStartY = (maxY - boxHeight) / 2;
    int boxStartX = (maxX - boxWidth) / 2;

    while (true) {
        clear();

        box(stdscr, 0, 0);
        refresh();

        for (int i = 0; i < 5; i++) {
            if (i == highlight) {
                attron(A_REVERSE);
            }
            mvprintw(boxStartY + i + 1, boxStartX + (boxWidth - std::strlen(options[i])) / 2, "%s", options[i]);
            attroff(A_REVERSE);
        }

        choice = getch();
        switch (choice) {
            case KEY_UP:
                highlight = (highlight + 3) % 5;
                break;
            case KEY_DOWN:
                highlight = (highlight + 1) % 5;
                break;
            case 10:
                endwin();
                return highlight;
        }
    }

    endwin();
    return 5;
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
                currentOption = (currentOption + 1) % 5;
                break;

            case KEY_LEFT:
                currentOption = (currentOption + 2) % 5;
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


int GameOver() {
    initscr();
    raw();
    keypad(stdscr, TRUE);

    int maxRows, maxCols;
    getmaxyx(stdscr, maxRows, maxCols);

    int centerX = maxCols / 2;
    int centerY = maxRows / 2;

    box(stdscr, 0, 0);

    mvprintw(centerY, centerX - 4, std::string("Game over!").c_str());
    mvprintw(centerY + 1, centerX - 7, std::string("Try again? (y/n)").c_str());

    int ch = getch();
    endwin(); 

    if (ch == 'y' || ch == 'Y') {
        return 1;
    } else if (ch == 'n' || ch == 'N') {
        return 0;
    } else {
        return 0;
    }


}


void LeaderboardDraw(std::vector<LB> Leaderboard) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    int height, width;
    getmaxyx(stdscr, height, width);

    int box_height = Leaderboard.size() + 2;
    int box_width = 0;

    box_width += 2;

    int start_y = 0;
    int start_x = 0;

    WINDOW* box_win = newwin(height, width, start_y, start_x);

    box(box_win, 0, 0);
    wrefresh(box_win);

    int center_y = height / 2;
    int center_x = width / 2;

    for (size_t i = 0; i < Leaderboard.size(); ++i) {
        mvwprintw(box_win, center_y - Leaderboard.size() / 2 + i , center_x - box_width / 2 - 10 ,
                  "%d) %s %d %s", i + 1, Leaderboard[i].Name.c_str() , Leaderboard[i].Score , ConvertTime(Leaderboard[i].ElapsedTime).c_str());
    }

    wrefresh(box_win);

    getch();
    endwin();

    return;

}


int Pause() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    std::vector<std::string> options = {"Resume", "Save and Quit", "Quit"};
    int height, width;
    getmaxyx(stdscr, height, width);

    int box_height = options.size() + 2;
    int box_width = 0;

    for (const auto& option : options) {
        box_width = std::max(box_width, static_cast<int>(option.length()) + 3);
    }

    box_width += 2;

    int start_y = height / 2 - box_height / 2;
    int start_x = width / 2 - box_width / 2;

    WINDOW* menu_win = newwin(box_height, box_width, start_y, start_x);

    int highlight = 1;
    int choice = 0;

    while (true) {
        box(menu_win, 0, 0);
        for (int i = 0; i < options.size(); i++) {
            if (highlight == i + 1) {
                wattron(menu_win, A_REVERSE);
                mvwprintw(menu_win, i + 1, 1, options[i].c_str());
                wattroff(menu_win, A_REVERSE);
            } else {
                mvwprintw(menu_win, i + 1, 1, options[i].c_str());
            }
        }
        wrefresh(menu_win);

        int ch = getch();
        switch (ch) {
            case KEY_UP:
                highlight = (highlight - 1 == 0) ? options.size() : highlight - 1;
                break;
            case KEY_DOWN:
                highlight = (highlight + 1 > options.size()) ? 1 : highlight + 1;
                break;
            case 10: 
                choice = highlight;
                break;
        }

        if (choice != 0) {
            break;
        }
    }

    endwin();

    return choice;

}


std::pair<int , int> TetrisSize () {
    initscr();
    cbreak();
    noecho();

    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    char* Msg = "Enter height and width (e.g., 20 10) : ";
    int col = (maxX - strlen(Msg)) / 2;

    char userInput[10];
    memset(userInput , 0 , sizeof(userInput));

    int ch; 
    int cursorPosition = 0;
    bool editing = true;

    while (editing) {
        clear();
        box(stdscr, 0, 0);
        refresh();

        mvprintw(maxY / 2 + 2, col, Msg );
        mvprintw(maxY / 2 + 4, col, "> ");

        mvprintw(maxY / 2 + 4 , col + 5 , "%s", userInput);

        move(maxY / 2 + 4 , col + 5 + cursorPosition );

        ch = getch();
        switch (ch) {
            case 10: 
                editing = false;
                break;

            case 127:
                if (cursorPosition > 0) {
                    cursorPosition--;
                    userInput[cursorPosition] = '\0';
                }
                break;

            default:
                if (std::isprint(ch) && cursorPosition < 29) {
                    userInput[cursorPosition] = ch;
                    cursorPosition++;
                }
                break;
        }

    }



    endwin(); // End the library


    std::string InputString(userInput);
    std::istringstream SSInput(InputString);

    int H,W;

    if (SSInput >> H >> W) {
        return std::make_pair(H , W);
    } else {
        return std::make_pair(18,10);
    }



}