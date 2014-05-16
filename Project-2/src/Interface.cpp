#include "Interface.h"

#include <iostream>

using namespace std;

Interface::Interface() {
	done = false;
}

Interface::~Interface() {
}

bool Interface::isDone() {
	return done;
}

void Interface::clearStdInAndPressEnterToContinue() {
	cin.clear();
	cin.ignore(10000, '\n');

	cout << "Press <Enter> to continue...";
	cin.get();
}

void Interface::showMainMenu() {
	cout << endl;
	cout << "-------------------" << endl;
	cout << "Contacts management" << endl;
	cout << "-------------------" << endl;
	cout << endl;
	cout << "1. Search" << endl;
	cout << "2. Add Contact" << endl;
	cout << "3. Remove Contact" << endl;
	cout << "4. Exit" << endl;
	cout << endl;

	int input;
	cout << "Choose an option:" << endl;
	cout << "> ";
	cin >> input;
	input--;

	switch ((Action) input) {
	case SEARCH:
		break;
	case ADD:
		break;
	case REMOVE:
		break;
	case EXIT:
		done = true;
		break;
	default:
		cout << endl;
		cout << "Invalid input." << endl;
		clearStdInAndPressEnterToContinue();
		break;
	}
}
