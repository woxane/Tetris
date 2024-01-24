#include "tetris.hpp"


char Getch() {
	char buf = 0;
	struct termios old = {0};

	if (tcgetattr(0, &old) < 0)
		perror("tcsetattr()");

	old.c_lflag &= ~ICANON;
	old.c_lflag &= ~ECHO;
	old.c_cc[VMIN] = 1;
	old.c_cc[VTIME] = 0;

	if (tcsetattr(0, TCSANOW, &old) < 0)
		perror("tcsetattr ICANON");

	if (read(0, &buf, 1) < 0)
		perror("read()");

	old.c_lflag |= ICANON;
	old.c_lflag |= ECHO;

	if (tcsetattr(0, TCSADRAIN, &old) < 0)
		perror ("tcsetattr ~ICANON");

	return buf;
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