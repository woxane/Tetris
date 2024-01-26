#include "tetris.hpp"


char Getch() {
	struct termios original, modified;
    tcgetattr(STDIN_FILENO, &original);

    modified = original;
    modified.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &modified);

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    char ch = '\0';
    if (read(STDIN_FILENO, &ch, sizeof(ch)) != -1) {
        std::cin.ignore(std::cin.rdbuf()->in_avail()); // Clear input buffer
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &original);

    fcntl(STDIN_FILENO, F_SETFL, flags);

    return ch;
}

void Cls() {
	std::cout << "\033[2J\033[1;1H";
}


std::string ConvertTime(long long int ElapsedTime) {
    int Minutes = (ElapsedTime / 1000000) / 60;
    int Seconds = (ElapsedTime / 1000000) % 60;
    int MilliSeconds = (ElapsedTime / 1000) % 1000;
    std::stringstream Result;

    Result << std::setfill('0') << std::setw(2) << Minutes << ":"
           << std::setw(2) << Seconds << ":"
           << std::setw(3) << MilliSeconds;

    return Result.str();
}