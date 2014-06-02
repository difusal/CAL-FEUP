#include "Utilities.h"

#include <iostream>
#include <cstring>

using namespace std;

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

// Clears console screen.
void clearScreen() {
	for (int i = 0; i < 60; i++)
		cout << endl;
}

// Clears standard input.
void clearStdIn() {
	// clear buffer
	cin.clear();
	cin.ignore(10000, '\n');
}

// Wait for <Enter> key to be pressed.
void pressEnterToContinue() {
	cout << "Press <Enter> to continue...";
	cin.get();
}

// Clears standard input and wait for <Enter> key to be pressed.
void clearStdInAndPressEnterToContinue() {
	clearStdIn();
	pressEnterToContinue();
}
