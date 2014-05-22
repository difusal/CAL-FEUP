#include <iostream>
#include "Interface.h"

using namespace std;

int main() {
	Interface interface;

	do {
		interface.showMainMenu();
	} while (!interface.isDone());

	cout << endl;
	cout << "Program terminated." << endl;

	return 0;
}
