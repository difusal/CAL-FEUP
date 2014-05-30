#pragma once

#include <set>
#include "Contact.h"

const std::string contactsListPath = "contacts.txt";
const std::string settingsPath = "settings.txt";

enum MainMenuAction {
	LIST_ALL, SEARCH, ADD, REMOVE, SETTINGS, EXIT
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
	Contact* searchContact();
	void addContact();
	void removeContact();
	void editSettings();
};
