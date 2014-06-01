#include "Interface.h"

#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

Interface::Interface() {
	done = false;
	contactsAPI = new ContactsAPI();
}

Interface::~Interface() {
	delete contactsAPI;
}

bool Interface::isDone() {
	return done;
}

void Interface::clearScreen() {
	for (int i = 0; i < 60; i++)
		cout << endl;
}

void Interface::clearStdIn() {
	// clearing buffer
	cin.clear();
	cin.ignore(10000, '\n');
}

void Interface::pressEnterToContinue() {
	cout << "Press <Enter> to continue...";
	cin.get();
}

void Interface::clearStdInAndPressEnterToContinue() {
	clearStdIn();
	pressEnterToContinue();
}

void Interface::showMainMenu() {
	clearScreen();
	cout << "-------------------" << endl;
	cout << "Contacts management" << endl;
	cout << "-------------------" << endl;
	cout << endl;
	cout << "1. Contacts List" << endl;
	cout << "2. Search" << endl;
	cout << "3. Add Contact" << endl;
	cout << "4. Remove Contact" << endl;
	cout << "5. Settings" << endl;
	cout << "6. Exit" << endl;
	cout << endl;
	cout << "Choose an option:" << endl;
	cout << "> ";

	int input;
	cin >> input;
	input--;

	switch ((MainMenuAction) input) {
	case LIST_ALL:
		showContactsList();
		break;
	case SEARCH:
		clearStdIn();
		searchContact();
		break;
	case ADD:
		clearStdIn();
		addContact();
		break;
	case REMOVE:
		clearStdIn();
		removeContact();
		break;
	case SETTINGS:
		clearStdIn();
		editSettings();
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

void Interface::showContactsList() {
	clearScreen();

	cout << contactsAPI->getContactsToString();

	clearStdInAndPressEnterToContinue();
}

Contact* Interface::searchContact() {
	string search = "";

	bool escWasPressed = false;
	bool typing = true;
	do {
		contactsAPI->updateSearchResults(search);

		clearScreen();
		cout << "---------------------------------------------" << endl;
		cout << contactsAPI->getSearchResults();
		cout << "Usage:" << endl;
		cout << "    Press <Enter> to select the first contact" << endl;
		cout << "    Press <Esc> to go back" << endl;
		cout << "---------------------------------------------" << endl;

		// read character
		char c;
		do {
			c = getChar();
			// cout << "CHAR CODE: " << (int) c << endl;
		} while (!isValid(c));

		if (c == BACKSPACE_CODE)
			// delete last string character
			search = search.substr(0, search.size() - 1);
		else if (c == ENTER_CODE)
			// done typing
			typing = false;
		else if (c == ESC_CODE) {
			typing = false;
			escWasPressed = true;
		} else
			search += c;
	} while (typing);

	Contact* selectedContact = NULL;
	if (!escWasPressed) {
		if (contactsAPI->getSearchResults().size() != 0) {
			selectedContact = (*contactsAPI->getSearchResults().begin());

			cout << endl;
			cout << "Selected contact:" << endl;
			cout << *selectedContact << endl;

			pressEnterToContinue();
		} else {
			cout << endl;
			cout << "Warning: No contact selected." << endl;
			pressEnterToContinue();
		}
	}

	return selectedContact;
}

void Interface::addContact() {
	bool valid;
	string name, firstName, lastName, phoneNumber, email, address;

	clearScreen();
	cout << "-----------" << endl;
	cout << "Add contact" << endl;
	cout << "-----------" << endl;

	// -------------------------------------------
	// name
	valid = false;
	do {
		cout << endl;
		cout << "Name: ";
		getline(cin, name);

		// processing name
		vector<string> names = getTokens(name, " ");

		if (names.size() >= 1) {
			valid = true;
			firstName = names[0];
			lastName = NULL_FIELD_LABEL;
		}

		if (names.size() >= 2)
			lastName = names[names.size() - 1];

		foreach(contactsAPI->getContacts(), it)
			if ((*it)->getName().compare(firstName + " " + lastName) == 0
					|| ((*it)->getFirstName().compare(firstName) == 0
							&& fieldIsNull((*it)->getLastName()))) {
				cout << "Error: A contact with this name already exists."
						<< endl;

				valid = false;
			}
	} while (!valid);

	// -------------------------------------------
	// phone number
	valid = false;
	do {
		cout << "Phone number: ";
		getline(cin, phoneNumber);

		if (phoneNumber.size() == 9)
			valid = true;
		else if (phoneNumber.size() == 0) {
			valid = true;
			phoneNumber = NULL_FIELD_LABEL;
		} else {
			cout << "Error: phone number must have exactly 9 digits." << endl;
			cout << endl;
		}
	} while (!valid);

	// -------------------------------------------
	// email
	valid = false;
	do {
		cout << "Email: ";
		getline(cin, email);

		if (email.size() == 0) {
			valid = true;
			email = NULL_FIELD_LABEL;
		} else if (email.size() < 5 || email.find(" ") != string::npos
				|| email.find("@") == string::npos
				|| email.find(".") == string::npos) {
			cout << "Error: invalid email." << endl;
			cout << endl;
		} else
			valid = true;

		/*
		 // when regex_match gets implemented,
		 // uncomment this to enable a decent email validation.

		 const tr1::regex pattern("[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}");

		 if (email.size() == 0) {
		 valid = true;
		 email = NULL_FIELD;
		 } else if (std::tr1::regex_match(email, pattern))
		 valid = true;
		 */
	} while (!valid);

	// -------------------------------------------
	// address
	cout << "Address: ";
	getline(cin, address);
	if (address.size() == 0)
		address = NULL_FIELD_LABEL;

	// -------------------------------------------
	// add new contact to contacts
	contactsAPI->addContact(firstName, lastName, phoneNumber, email, address);
	cout << "Contact successfully added." << endl;
	pressEnterToContinue();
}

void Interface::removeContact() {
	Contact* contact = searchContact();

	if (contact) {
		bool done = false;
		do {
			char input;

			cout << endl;
			cout << "Remove " << contact->getName() << "? [Y/n] ";
			cin >> input;

			input = tolower(input);
			if (input == 'y') {
				contactsAPI->deleteContact(contact);
				cout << "Contact successfully removed." << endl;
				done = true;
			} else if (input == 'n') {
				cout << "Operation canceled." << endl;
				done = true;
			}
		} while (!done);

		cout << endl;
		clearStdInAndPressEnterToContinue();
	}
}

void Interface::editSettings() {
	clearScreen();
	cout << "--------" << endl;
	cout << "Settings" << endl;
	cout << "--------" << endl;
	cout << "Current number of results to display: "
			<< contactsAPI->getMaxResToDisplay() << endl;

	bool done = false;
	do {
		int input;
		cout << endl;
		cout << "Insert new value: ";
		cin >> input;

		if (input <= 0 || 20 < input) {
			cout << "Error: Input must be a value between 1-20." << endl;
			clearStdInAndPressEnterToContinue();
		} else {
			contactsAPI->setMaxResToDisplay(input);
			done = true;
		}
	} while (!done);

	clearStdInAndPressEnterToContinue();
}
