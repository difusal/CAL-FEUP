#include "Interface.h"

#include <iostream>
#include "ConsoleUtilities.h"

using namespace std;

// Creates and initializes an interface.
Interface::Interface() {
	done = false;

	// initialize the contacts API
	contactsAPI = new ContactsAPI();
}

Interface::~Interface() {
	delete contactsAPI;
}

// Returns true if interface is done.
bool Interface::isDone() {
	return done;
}

// Show the interface main menu.
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

	// get input
	int input;
	cin >> input;
	clearStdIn();
	input--;

	switch ((MainMenuAction) input) {
	case LIST_ALL:
		showContactsList();
		break;
	case SEARCH:
		performActionOnContact(searchContact());
		break;
	case ADD:
		addContact();
		break;
	case REMOVE:
		removeContact(searchContact());
		break;
	case SETTINGS:
		editSettings();
		break;
	case EXIT:
		done = true;
		break;
	default:
		cout << endl;
		cout << "Invalid input." << endl;
		pressEnterToContinue();
		break;
	}
}

// Shows the contacts list.
void Interface::showContactsList() {
	clearScreen();
	cout << contactsAPI->getContacts();

	pressEnterToContinue();
}

// Shows the search interface.
Contact* Interface::searchContact() {
	// if contacts list is empty
	if (contactsAPI->getContacts().empty()) {
		cout << endl;
		cout << "Impossible to search contacts with an empty contacts list."
				<< endl;
		pressEnterToContinue();

		return NULL;
	}

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
			typing = false;
		else if (c == ESC_CODE) {
			typing = false;
			escWasPressed = true;
		} else
			search += c;
	} while (typing);

	// initialize selected contact
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
		} else {
			// if no contact is selected
			cout << endl;
			cout << "Warning: No contact selected." << endl;
			pressEnterToContinue();
		}
	}

	return selectedContact;
}

// Shows a menu with actions that can be performed on the specified contact.
void Interface::performActionOnContact(Contact* contact) {
	if (contact) {
		cout << "1. Edit name" << endl;
		cout << "2. Edit phone number" << endl;
		cout << "3. Edit email" << endl;
		cout << "4. Edit address" << endl;
		cout << "5. Delete contact" << endl;
		cout << "6. Cancel" << endl;

		bool done = false;
		do {
			cout << endl;
			cout << "Choose an option:" << endl;
			cout << "> ";

			int input;
			cin >> input;
			clearStdIn();
			input--;

			switch ((ContactAction) input) {
			case EDIT_NAME:
				setContactName(contact);
				contactsAPI->saveContacts();
				done = true;
				break;
			case EDIT_PHONE:
				cout << endl;
				setContactPhone(contact);
				contactsAPI->saveContacts();
				done = true;
				break;
			case EDIT_EMAIL:
				cout << endl;
				setContactEmail(contact);
				contactsAPI->saveContacts();
				done = true;
				break;
			case EDIT_ADDRESS:
				cout << endl;
				setContactAddress(contact);
				contactsAPI->saveContacts();
				done = true;
				break;
			case DELETE:
				cout << endl;
				removeContact(contact);
				contactsAPI->saveContacts();
				done = true;
				break;
			case CANCEL:
				done = true;
				break;
			default:
				break;
			}
		} while (!done);
	}
}

// Shows add contact interface.
void Interface::addContact() {
	clearScreen();
	cout << "-----------" << endl;
	cout << "Add contact" << endl;
	cout << "-----------" << endl;

	Contact* contact = new Contact();
	setContactName(contact);
	setContactPhone(contact);
	setContactEmail(contact);
	setContactAddress(contact);

	// add new contact to contacts
	contactsAPI->addContact(contact);

	cout << "Contact successfully added." << endl;
	cout << endl;
	pressEnterToContinue();
}

// Shows remove contact interface for the specified contact.
void Interface::removeContact(Contact* contact) {
	// if a contact has been selected
	if (contact) {
		bool done = false;

		do {
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

// Shows the edit setting interface.
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

// Prompts user to input a new valid name for the specified contact.
void Interface::setContactName(Contact* contact) {
	string name, firstName, lastName;

	bool valid = false;
	do {
		cout << endl;
		cout << "Name: ";
		getline(cin, name);

		// processing name
		vector<string> names = getTokens(name, " ");

		// if names size is greater than 1
		if (names.size() >= 1) {
			valid = true;

			// assign first name
			firstName = names[0];
			lastName = NULL_FIELD_LABEL;
		}

		// if names size is greater than 2
		if (names.size() >= 2)
			// reassign last name
			lastName = names[names.size() - 1];

		// check if a contact with the inputed name already exists
		foreach(contactsAPI->getContacts(), it)
			if ((*it)->getName().compare(firstName + " " + lastName) == 0
					|| ((*it)->getFirstName().compare(firstName) == 0
							&& fieldIsNull((*it)->getLastName()))) {
				cout << "Error: A contact with this name already exists."
						<< endl;

				valid = false;
			}
	} while (!valid);

	// set first and last name
	contact->setFirstName(firstName);
	contact->setLastName(lastName);
}

// Prompts user to input a new valid name for the specified contact.
void Interface::setContactPhone(Contact* contact) {
	string phoneNumber;

	bool valid = false;
	do {
		cout << "Phone number: ";
		getline(cin, phoneNumber);

		if (phoneNumber.size() == 9)
			valid = true;
		else if (phoneNumber.empty()) {
			valid = true;
			phoneNumber = NULL_FIELD_LABEL;
		} else {
			cout << "Error: phone number must have exactly 9 digits." << endl;
			cout << endl;
		}
	} while (!valid);

	contact->setPhoneNumber(phoneNumber);
}

// Prompts user to input a new valid email for the specified contact.
void Interface::setContactEmail(Contact* contact) {
	string email;

	bool valid = false;
	do {
		// get input
		cout << "Email: ";
		getline(cin, email);

		if (email.empty()) {
			valid = true;
			email = NULL_FIELD_LABEL;
		} else if (email.size() < 5 || email.find(" ") != string::npos
				|| email.find("@") == string::npos
				|| email.find(".") == string::npos) {
			// if input does not have a '@' or a '.' or the input length is less than 5
			cout << "Error: invalid email." << endl;
			cout << endl;
		} else
			valid = true;
	} while (!valid);

	contact->setEmail(email);
}

// Prompts user to input a new valid address for the specified contact.
void Interface::setContactAddress(Contact* contact) {
	string address;

	// get input
	cout << "Address: ";
	getline(cin, address);

	if (address.empty())
		address = NULL_FIELD_LABEL;

	contact->setAddress(address);
}
