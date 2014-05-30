#pragma once

#include <string>
#include <vector>

#define foreach(v, it) for(typeof((v).begin()) it = (v).begin(); it != (v).end(); it++)

bool fieldIsNull(std::string field);
std::vector<std::string> getTokens(std::string str);

char getch();
bool isValid(char c);
