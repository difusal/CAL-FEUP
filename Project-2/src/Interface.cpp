#include "Interface.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>

using namespace std;

Interface::Interface() {
	done = false;
	loadContacts();
	loadSettings();
}

Interface::~Interface() {
	foreach(contacts, it)
		delete (*it);
}

bool Interface::isDone() {
	return done;
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

void Interface::clearScreen() {
	for (int i = 0; i < 40; i++)
		cout << endl;
}

void Interface::loadContacts() {
	// clearing vector current content
	contacts.clear();

	// trying to open file
	ifstream fin;
	fin.open(contactsListPath.c_str());
	if (!fin) {
		cerr << "Error: Unable to open file: " << contactsListPath << endl;
		exit(1);
	}

	// reading number of contacts to be read from file
	int nContacts;
	fin >> nContacts;

	// loading each contact from file
	string firstName, lastName, phoneNumber, email, address;
	for (int i = 0; i < nContacts; i++) {
		// reading firstName, lastName, phoneNumber and email
		fin >> firstName >> lastName >> phoneNumber >> email;

		// reading address
		getline(fin, address);
		address.erase(address.begin());

		/*
		 // Debugging block
		 cout << "firstName: <" << firstName << ">" << endl;
		 cout << "lastName: <" << lastName << ">" << endl;
		 cout << "phoneNumber: <" << phoneNumber << ">" << endl;
		 cout << "email: <" << email << ">" << endl;
		 cout << "address: <" << address << ">" << endl;
		 cout << endl;
		 */

		Contact* contact = new Contact(firstName, lastName, phoneNumber, email,
				address);
		contacts.insert(contact);
	}
}

void Interface::saveContacts() {
	cout << endl;
	cout << "Updating: " << contactsListPath << endl;

	// trying to open output stream
	ofstream fout;
	fout.open(contactsListPath.c_str());
	if (!fout) {
		cerr << "Error: Unable to open file: " << contactsListPath << endl;
		exit(1);
	}

	// saving number of contacts
	fout << contacts.size() << endl;
	foreach(contacts, it)
	{
		// saving firstName and lastName
		fout << (*it)->getFirstName() << " " << (*it)->getLastName();

		// saving phoneNumber
		fout << " " << (*it)->getPhoneNumber();

		// saving email
		fout << " " << (*it)->getEmail();

		// saving address
		fout << " " << (*it)->getAddress();

		fout << endl;
	}
}

int Interface::loadSettings() {
	// trying to open file
	ifstream fin;
	fin.open(settingsPath.c_str());
	if (!fin) {
		cerr << "Error: Unable to open file: " << settingsPath << endl;
		cerr << "Warning: Using default settings values." << endl;

		maxResToDisplay = 3;
		return -1;
	}

	// read number of search results to display
	fin >> maxResToDisplay;

	return 0;
}

void Interface::saveSettings() {
	cout << endl;
	cout << "Updating: " << settingsPath << endl;

	// try to open output stream
	ofstream fout;
	fout.open(settingsPath.c_str());
	if (!fout) {
		cerr << "Error: Unable to open file: " << settingsPath << endl;
		exit(1);
	}

	// save number of search results to display
	fout << maxResToDisplay << endl;
}

vector<Contact*> Interface::getSearchResults(string search) {
	vector<Contact*> results;

	// if search is equal to "" (empty string)
	if (search.size() == 0)
		foreach(contacts, it)
			results.push_back(*it);
	else {
		foreach(contacts, it)
			(*it)->updateDistanceToSearch(search), results.push_back(*it);

		sort(ALL(results), shortestDistanceContact);
	}

	return results;
}

void Interface::displaySearchResults(vector<Contact*> results) {
	int nResToDisplay =
			(results.size() < maxResToDisplay) ?
					results.size() : maxResToDisplay;

	cout << "Showing " << nResToDisplay << " of " << results.size()
			<< " results." << endl;
	cout << "- - - - - - - - - - - - - - - - - - - - - - -";

	for (int i = 0; i < nResToDisplay; i++) {
		if (i == 1)
			cout << "- - - - - - - - - - - - - - - - - - - - - - -";

		cout << endl;
		cout << *results[i];
	}
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
	foreach(contacts, it)
		cout << **it << endl;

	clearStdInAndPressEnterToContinue();
}

Contact* Interface::searchContact() {
	string search = "";
	vector<Contact*> searchResults;

	bool escWasPressed = false;
	bool typing = true;
	do {
		clearScreen();
		cout << "---------------------------------------------" << endl;
		cout << "Search: " << search << "|" << endl;

		searchResults = getSearchResults(search);
		displaySearchResults(searchResults);

		cout << "- - - - - - - - - - - - - - - - - - - - - - -" << endl;
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

	if (escWasPressed)
		cout << "<Esc> has been pressed." << endl;
	else {
		if (searchResults.size() != 0) {
			cout << endl;
			cout << "Selected contact:" << endl;
			cout << **searchResults.begin();

			selectedContact = (*searchResults.begin());
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
			lastName = NULL_FIELD;
		}

		if (names.size() >= 2)
			lastName = names[names.size() - 1];

		foreach(contacts, it)
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
			phoneNumber = NULL_FIELD;
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
			email = NULL_FIELD;
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
		address = NULL_FIELD;

	// -------------------------------------------
	// add new contact to contacts
	Contact* newContact = new Contact(firstName, lastName, phoneNumber, email,
			address);
	contacts.insert(newContact);

	// -------------------------------------------
	// save contacts
	saveContacts();
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
				contacts.erase(contact);
				cout << "Contact successfully removed." << endl;
				saveContacts();
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
	cout << "Current number of results to display: " << maxResToDisplay << endl;

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
			maxResToDisplay = input;
			saveSettings();
			done = true;
		}
	} while (!done);

	clearStdInAndPressEnterToContinue();
}
