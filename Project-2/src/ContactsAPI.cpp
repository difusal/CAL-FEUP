#include "ContactsAPI.h"

#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

unsigned int ContactsAPI::maxResToDisplay = 0;
std::string ContactsAPI::search = "";

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

const std::string ContactsAPI::getContactsToString() const {
	stringstream ss;

	foreach(contacts, it)
		ss << **it << endl;

	return ss.str();
}

void ContactsAPI::setContacts(const ContactsList& contacts) {
	this->contacts = contacts;
}

unsigned int ContactsAPI::getMaxResToDisplay() {
	return maxResToDisplay;
}

void ContactsAPI::setMaxResToDisplay(unsigned int maxResToDisplay) {
	this->maxResToDisplay = maxResToDisplay;
	saveSettings();
}

void ContactsAPI::deleteContact(Contact* contact) {
	contacts.erase(contact);
	saveContacts();
}

const SearchResults& ContactsAPI::getSearchResults() const {
	return searchResults;
}

void ContactsAPI::setSearchResults(const SearchResults& searchResults) {
	this->searchResults = searchResults;
}

void ContactsAPI::loadContacts() {
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

void ContactsAPI::saveContacts() {
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

int ContactsAPI::loadSettings() {
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

void ContactsAPI::updateSearchResults(string search) {
	// clean previous results
	searchResults.clear();

	// update search keywords
	this->search = search;

	// if search is equal to "" (empty string)
	if (search.size() == 0)
		foreach(contacts, it)
			searchResults.push_back(*it);
	else {
		foreach(contacts, it)
			(*it)->updateDistanceToSearch(search), searchResults.push_back(*it);

		sort(ALL(searchResults), shortestDistanceContact);
	}
}
void ContactsAPI::addContact(Contact* contact) {
	contacts.insert(contact);
	saveContacts();
}

void ContactsAPI::addContact(string firstName, string lastName,
		string phoneNumber, string email, string address) {
	addContact(new Contact(firstName, lastName, phoneNumber, email, address));
}

std::ostream& operator<<(std::ostream& out, const SearchResults l) {
	int nResToDisplay =
			(l.size() < ContactsAPI::maxResToDisplay) ?
					l.size() : ContactsAPI::maxResToDisplay;

	out << "Search: " << ContactsAPI::search << "|" << std::endl;
	out << "Showing " << nResToDisplay << " of " << l.size() << " results."
			<< std::endl;
	out << "- - - - - - - - - - - - - - - - - - - - - - -";
	for (int i = 0; i < nResToDisplay; i++) {
		if (i == 1)
			out << "- - - - - - - - - - - - - - - - - - - - - - -";

		out << std::endl;
		out << *l[i];
	}
	out << "- - - - - - - - - - - - - - - - - - - - - - -" << std::endl;

	return out;
}
