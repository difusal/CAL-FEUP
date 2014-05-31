#include "Utilities.h"

#include <stdio.h>
#include <cstring>

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

// Returns true if the received char is valid.
bool isValid(char c) {
	// backspace, enter or esc
	if (c == BACKSPACE_CODE || c == ENTER_CODE || c == ESC_CODE)
		return true;

	// a-z or 0-9 and others...
	if (32 <= c && c <= 126)
		return true;

	return false;
}

// Returns a lower case version of the received string.
string toLower(string str) {
	string res = "";

	for (unsigned int i = 0; i < str.size(); i++)
		res += tolower(str[i]);

	return res;
}

// Returns an upper case version of the received string.
string toUpper(string str) {
	string res = "";

	for (unsigned int i = 0; i < str.size(); i++)
		res += toupper(str[i]);

	return res;
}

// Returns true if the specified field is null.
bool fieldIsNull(string field) {
	return field.compare(NULL_FIELD_LABEL) == 0;
}

// Returns a vector of strings containing the tokens of str separated by separator
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
