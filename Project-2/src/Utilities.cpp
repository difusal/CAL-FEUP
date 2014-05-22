#include "Utilities.h"

#include <stdio.h>
#include <cstring>

using namespace std;

bool fieldIsNull(std::string field) {
	return field.compare("null") == 0;
}

vector<string> getTokens(string str) {
	vector<string> vec;

	char temp[1024];
	strcpy(temp, str.c_str());

	char *p = strtok(temp, " ");
	while (p) {
		vec.push_back(string(p));

		p = strtok(NULL, " ");
	}

	return vec;
}
