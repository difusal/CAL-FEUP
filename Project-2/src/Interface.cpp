#include "Interface.h"

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

const string contactsListPath = "contacts.txt";

Interface::Interface() {
	done = false;
	LoadContacts();
}

Interface::~Interface() {
	foreach(contacts, it)
		delete (*it);
}

bool Interface::IsDone() {
	return done;
}

void Interface::ClearStdIn() {
	// clearing buffer
	cin.clear();
	cin.ignore(10000, '\n');
}

void Interface::PressEnterToContinue() {
	cout << "Press <Enter> to continue...";
	cin.get();
}

void Interface::ClearStdInAndPressEnterToContinue() {
	ClearStdIn();
	PressEnterToContinue();
}

void Interface::LoadContacts() {
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

void Interface::SaveContacts() {
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

void Interface::ShowMainMenu() {
	cout << endl;
	cout << "-------------------" << endl;
	cout << "Contacts management" << endl;
	cout << "-------------------" << endl;
	cout << endl;
	cout << "1. Contacts List" << endl;
	cout << "2. Search" << endl;
	cout << "3. Add Contact" << endl;
	cout << "4. Remove Contact" << endl;
	cout << "5. Exit" << endl;
	cout << endl;
	cout << "Choose an option:" << endl;
	cout << "> ";

	int input;
	cin >> input;
	input--;

	switch ((Action) input) {
	case LIST_ALL:
		ShowContactsList();
		break;
	case SEARCH:
		break;
	case ADD:
		ClearStdIn();
		AddContact();
		break;
	case REMOVE:
		break;
	case EXIT:
		done = true;
		break;
	default:
		cout << endl;
		cout << "Invalid input." << endl;
		ClearStdInAndPressEnterToContinue();
		break;
	}
}
void Interface::ShowContactsList() {
	cout << endl;
	foreach(contacts, it)
		cout << **it << endl;

	ClearStdInAndPressEnterToContinue();
}

void Interface::AddContact() {
	string name, firstName, lastName, phoneNumber, email, address;

	cout << endl;
	cout << "Name: ";
	getline(cin, name);

	// processing name
	vector<string> names = getTokens(name);
	firstName = names[0];
	lastName = names[names.size() - 1];

	cout << "Phone number: ";
	getline(cin, phoneNumber);

	cout << "Email: ";
	getline(cin, email);

	cout << "Address: ";
	getline(cin, address);

	// adding new contact to contacts
	Contact* newContact = new Contact(firstName, lastName, phoneNumber, email,
			address);
	contacts.insert(newContact);

	SaveContacts();
	cout << "Contact successfully added." << endl;
	PressEnterToContinue();
}
