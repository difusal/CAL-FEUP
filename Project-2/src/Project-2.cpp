#include <iostream>
#include "Interface.h"

using namespace std;

int main() {
	// create interface
	Interface interface;

	do {
		// show interface menu
		interface.showMainMenu();

		// while interface is not done
	} while (!interface.isDone());

	cout << endl;
	cout << "Program terminated." << endl;

	return 0;
}
