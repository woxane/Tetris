#include "tetris.hpp"


char Getch() {
    struct termios original, modified;
    tcgetattr(STDIN_FILENO, &original);

    modified = original;
    modified.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &modified);

    char ch;
    if (read(STDIN_FILENO, &ch, sizeof(ch)) != -1) {
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        return ch;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &original);

    return '\0';
}

void Cls() {
	std::cout << "\033[2J\033[1;1H";
}

bool MoveDownCompare(const std::vector<int>& a, const std::vector<int>& b) {
	return a[0] > b[0] ; 
}

bool MoveRightCompare(const std::vector<int>& a, const std::vector<int>& b) {
	return a[1] > b[1];
}

bool MoveLeftCompare(const std::vector<int>& a, const std::vector<int>& b) {
	return a[1] < b[1];
}