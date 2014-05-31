#include "Utilities.h"

#include <stdio.h>
#include <cstring>

#ifdef __linux__
// linux system
#include <unistd.h>
#include <termios.h>
#elif _WIN32
// windows system
#include <conio.h>
#endif

using namespace std;

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

bool isValid(char c) {
	// backspace, enter or esc
	if (c == BACKSPACE_CODE || c == ENTER_CODE || c == ESC_CODE)
		return true;

	// a-z or 0-9 or space
	if (('a' <= c && c <= 'z') || ('0' <= c && c <= '9') || c == ' ')
		return true;

	return false;
}

string toLower(string str) {
	string res = "";

	for (unsigned int i = 0; i < str.size(); i++)
		res += tolower(str[i]);

	return res;
}

string toUpper(string str) {
	string res = "";

	for (unsigned int i = 0; i < str.size(); i++)
		res += toupper(str[i]);

	return res;
}

bool fieldIsNull(std::string field) {
	return field.compare(NULL_FIELD) == 0;
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
