#include <iostream>
#include "Interface.h"

using namespace std;

int main() {
	Interface interface;

	do {
		interface.ShowMainMenu();
	} while (!interface.IsDone());

	cout << endl;
	cout << "Program terminated." << endl;

	return 0;
}
