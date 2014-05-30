#include "Utilities.h"

#include <stdio.h>
#include <cstring>

#ifdef __linux__
// linux system
#include <unistd.h>
#include <termios.h>
#elif _WIN32
// windows system
// nothing
#endif

using namespace std;

bool fieldIsNull(std::string field) {
	return field.compare("null") == 0;
}

vector<string> getTokens(string str, string separator) {
	vector<string> vec;

	char temp[1024];
	strcpy(temp, str.c_str());

	char *p = strtok(temp, separator.c_str());
	while (p) {
		vec.push_back(string(p));

		p = strtok(NULL, separator.c_str());
	}

	return vec;
}

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
	return getchar();
}
#endif

bool isValid(char c) {
	// space
	if (c == 32)
		return true;

	// backspace
	if (c == 127)
		return true;

	// enter
	if (c == '\n')
		return true;

	// a-z or 0-9
	if (('a' <= c && c <= 'z') || ('0' <= c && c <= '9'))
		return true;

	return false;
}
