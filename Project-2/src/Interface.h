#pragma once

#include "ContactsAPI.h"

enum MainMenuAction {
	LIST_ALL, SEARCH, ADD, REMOVE, SETTINGS, EXIT
};

class Interface {
private:
	bool done;
	ContactsAPI* contactsAPI;

public:
	Interface();
	virtual ~Interface();

	bool isDone();

	void showMainMenu();
	void showContactsList();
	Contact* searchContact();
	void addContact();
	void removeContact();
	void editSettings();
};
