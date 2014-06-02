#include "ContactsAPI.h"

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

const int DEFAULT_MAX_RES_TO_DISPLAY = 3;

ContactsAPI::ContactsAPI() {
	loadContacts();
	loadSettings();
}

ContactsAPI::~ContactsAPI() {
	foreach(contacts, it)
		delete (*it);
}

const ContactsList& ContactsAPI::getContacts() const {
	return contacts;
}

unsigned int ContactsAPI::getMaxResToDisplay() {
	return maxResToDisplay;
}

void ContactsAPI::setMaxResToDisplay(unsigned int maxResToDisplay) {
	this->maxResToDisplay = maxResToDisplay;
	saveSettings();
}

const SearchResults& ContactsAPI::getSearchResults() const {
	return searchResults;
}

// Loads an existing contacts list.
int ContactsAPI::loadContacts() {
	// clear vector current content
	contacts.clear();

	// try to open file
	ifstream fin;
	fin.open(contactsListPath.c_str());
	if (!fin) {
		cerr << endl;
		cerr << "Error: Unable to open file: " << contactsListPath << endl;
		cerr << "Warning: Contacts list may be empty." << endl;
		pressEnterToContinue();

		return -1;
	}

	// read number of contacts to be read from file
	int nContacts;
	fin >> nContacts;

	// load each contact from file
	for (int i = 0; i < nContacts; i++) {
		string firstName, lastName, phoneNumber, email, address;

		// read firstName, lastName, phoneNumber and email
		fin >> firstName >> lastName >> phoneNumber >> email;

		// read address
		getline(fin, address);

		// erase first character, since it is a ' ' (space)
		address.erase(address.begin());

		addContact(firstName, lastName, phoneNumber, email, address);
	}

	return 0;
}

// Saves the current contacts list.
void ContactsAPI::saveContacts() {
	cout << endl;
	cout << "Updating: " << contactsListPath << endl;

	// try to open output stream
	ofstream fout;
	fout.open(contactsListPath.c_str());
	if (!fout) {
		cerr << "Error: Unable to open file: " << contactsListPath << endl;
		exit(1);
	}

	// save number of contacts
	fout << contacts.size() << endl;

	// save each contact
	foreach(contacts, it)
	{
		// save firstName and lastName
		fout << (*it)->getFirstName() << " " << (*it)->getLastName();

		// save phoneNumber
		fout << " " << (*it)->getPhoneNumber();

		// save email
		fout << " " << (*it)->getEmail();

		// save address
		fout << " " << (*it)->getAddress();

		fout << endl;
	}
}

// Loads the program settings.
int ContactsAPI::loadSettings() {
	// try to open file
	ifstream fin;
	fin.open(settingsPath.c_str());
	if (!fin) {
		maxResToDisplay = DEFAULT_MAX_RES_TO_DISPLAY;

		cerr << endl;
		cerr << "Error: Unable to open file: " << settingsPath << endl;
		cerr << "Warning: Using default settings values." << endl;
		pressEnterToContinue();

		return -1;
	}

	// read number of search results to display
	fin >> maxResToDisplay;

	return 0;
}

// Saves the current program settings.
void ContactsAPI::saveSettings() {
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

// Updates the search results using the specified search string.
void ContactsAPI::updateSearchResults(string search) {
	// clean previous results
	searchResults.clear();

	// if search is equal to "" (empty string)
	if (search.size() == 0)
		// the results are the same as the contacts list
		foreach(contacts, it)
			searchResults.push_back(*it);
	else {
		// update each contact distance to the search keywords and put it in the results vector
		foreach(contacts, it)
			(*it)->updateDistanceToSearch(search), searchResults.push_back(*it);

		// sort the results vector by shortest distance
		sort(ALL(searchResults), shortestDistanceContact);
	}
}

// Adds the specified contact to the contacts list.
void ContactsAPI::addContact(Contact* contact) {
	contacts.insert(contact);
	saveContacts();
}

// Creates a contact with the specified arguments and adds it to the contacts list.
void ContactsAPI::addContact(string firstName, string lastName,
		string phoneNumber, string email, string address) {
	addContact(new Contact(firstName, lastName, phoneNumber, email, address));
}

// Deletes a contact from the contacts list.
void ContactsAPI::deleteContact(Contact* contact) {
	contacts.erase(contact);
	saveContacts();
}

std::ostream& operator<<(std::ostream& out, const ContactsList& contacts) {
	if (contacts.empty())
		out << "Contacts list is empty." << endl;
	else
		foreach(contacts, it)
			out << **it << std::endl;

	return out;
}
