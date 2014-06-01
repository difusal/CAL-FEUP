#include "ConsoleUtilities.h"

#include <cstdio>

// System dependent includes necessary to implement getChar() function.
#ifdef __linux__
// linux system
#include <unistd.h>
#include <termios.h>
#elif _WIN32
// windows system
#include <conio.h>
#endif

using namespace std;

// System independent function to read a char from the console
// without the need of the <Enter> key to be pressed.
#ifdef __linux__
// linux system
char getChar() {
	char buf = 0;

	struct termios old = { 0 };
	if (tcgetattr(0, &old) < 0)
		perror("tcgetattr()");

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
		perror("tcsetattr ~ICANON");

	return (buf);
}
#elif _WIN32
// windows system
char getChar() {
	return _getch();
}
#endif
