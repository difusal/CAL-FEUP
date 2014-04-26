#include <iostream>
#include <string>
#include <vector>

#include "MenusInterface.h"
#include "GraphUtilities.h"

using namespace std;

vector<string> graphsList;

int main() {
	loadGraphs();

	bool done;
	do {
		done = showMainMenu();
	} while (!done);

	cout << endl;
	cout << "Programa terminado." << endl;

	return 0;
}
