#include "Interface.h"

#include <iostream>
#include "ConsoleUtilities.h"

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
		if (contactsAPI->getContacts().empty()) {
			cout << endl;
			cout << "Impossible to search contacts with an empty contacts list."
					<< endl;
			pressEnterToContinue();
		} else
			searchContact();
		break;
	case ADD:
		clearStdIn();
		addContact();
		break;
	case REMOVE:
		clearStdIn();
		if (contactsAPI->getContacts().empty()) {
			cout << endl;
			cout
					<< "Impossible to remove a contact from an empty contacts list."
					<< endl;
			pressEnterToContinue();
		} else
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
	cout << contactsAPI->getContacts();

	clearStdInAndPressEnterToContinue();
}

Contact* Interface::searchContact() {
	// initialize search string
	string search = "";

	bool escWasPressed = false, typing = true;
	do {
		// update search results
		contactsAPI->updateSearchResults(search);

		// get search results
		SearchResults l = contactsAPI->getSearchResults();

		// calculate number of results to display
		unsigned int settingsMaxRes = contactsAPI->getMaxResToDisplay();
		int nRes = (l.size() < settingsMaxRes) ? l.size() : settingsMaxRes;

		// print search user interface
		clearScreen();
		cout << "---------------------------------------------" << endl;
		cout << "Search: " << search << "|" << endl;
		cout << "Showing " << nRes << " of " << l.size() << " results." << endl;
		cout << "- - - - - - - - - - - - - - - - - - - - - - -";
		for (int i = 0; i < nRes; i++) {
			if (i == 1)
				cout << "- - - - - - - - - - - - - - - - - - - - - - -";

			cout << endl;
			cout << *l[i];
		}
		cout << "- - - - - - - - - - - - - - - - - - - - - - -" << endl;
		cout << "Usage:" << endl;
		cout << "    Press <Enter> to select the first contact" << endl;
		cout << "    Press <Esc> to go back" << endl;
		cout << "---------------------------------------------" << endl;

		// read character
		char c;
		do {
			c = getChar();
		} while (!isValid(c));

		// process character
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

	// if <Esc> was pressed, return null contact
	Contact* selectedContact = NULL;

	// if <Esc> was not pressed
	if (!escWasPressed) {
		// if search results is not empty
		if (!contactsAPI->getSearchResults().empty()) {
			// update selected contact
			selectedContact = (*contactsAPI->getSearchResults().begin());

			// display selected contact
			clearScreen();
			cout << "Selected contact:" << endl;
			cout << *selectedContact << endl;
			pressEnterToContinue();

			// prompt user what to do with the selected contact
			// TODO
		} else {
			// if no contact is selected
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
	cout << endl;
	pressEnterToContinue();
}

void Interface::removeContact() {
	// get a contact to remove
	Contact* contact = searchContact();

	// if a contact has been selected
	if (contact) {
		bool done = false;

		do {
			cout << endl;
			cout << "Remove " << contact->getName() << "? [Y/n] ";

			// get input
			char input;
			cin >> input;

			// lower case input
			input = tolower(input);

			// if user confirms action
			if (input == 'y') {
				// delete contact
				contactsAPI->deleteContact(contact);
				cout << "Contact successfully removed." << endl;
				done = true;
			} else if (input == 'n') {
				// cancel contact deletion
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
		cout << endl;
		cout << "Insert new value: ";

		// get input
		int input;
		cin >> input;

		// if input is valid
		if (0 < input && input <= 20) {
			// set new maximum number of results to display
			contactsAPI->setMaxResToDisplay(input);
			done = true;
		} else {
			cout << "Error: Input must be a value between 1-20." << endl;
			clearStdInAndPressEnterToContinue();
		}
	} while (!done);

	clearStdInAndPressEnterToContinue();
}
