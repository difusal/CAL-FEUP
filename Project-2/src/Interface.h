#pragma once

#include <set>
#include "Contact.h"

const std::string contactsListPath = "contacts.txt";
const std::string settingsPath = "settings.txt";

enum Action {
	LIST_ALL, SEARCH, ADD, REMOVE, EXIT
};

struct ContactsComp {
	bool operator()(const Contact* lhs, const Contact* rhs) const {
		if (lhs->getFirstName().compare(rhs->getFirstName()) == 0)
			return (fieldIsNull(lhs->getLastName()) ? "" : lhs->getLastName())
					< (fieldIsNull(rhs->getLastName()) ? "" : rhs->getLastName());
		else
			return lhs->getFirstName() < rhs->getFirstName();
	}
};

class Interface {
private:
	bool done;
	std::set<Contact*, ContactsComp> contacts;
	unsigned int maxResToDisplay;

public:
	Interface();
	virtual ~Interface();

	bool isDone();
	void clearStdIn();
	void pressEnterToContinue();
	void clearStdInAndPressEnterToContinue();

	void loadContacts();
	void saveContacts();

	int loadSettings();
	void saveSettings();

	std::set<Contact*, ContactsComp> getSearchResults(std::string search);
	void displaySearchResults(std::set<Contact*, ContactsComp> searchResults);

	void showMainMenu();
	void showContactsList();
	void addContact();
	void searchContact();
};
