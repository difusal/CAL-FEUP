#pragma once

#include <string>
#include <vector>

#define foreach(v, it) for(typeof((v).begin()) it = (v).begin(); it != (v).end(); it++)

#ifdef __linux__
// linux system
const char BACKSPACE_CODE = 127;
const char ENTER_CODE = '\n';
#elif _WIN32
// windows system
const char BACKSPACE_CODE = 8;
const char ENTER_CODE = 13;
#endif

bool fieldIsNull(std::string field);
std::vector<std::string> getTokens(std::string str, std::string separator);

char getChar();
bool isValid(char c);
