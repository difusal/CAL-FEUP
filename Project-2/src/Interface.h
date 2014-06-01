#pragma once

#include "ContactsAPI.h"

enum MainMenuAction {
	LIST_ALL, SEARCH, ADD, REMOVE, SETTINGS, EXIT
};

enum ContactAction {
	EDIT_NAME, EDIT_PHONE, EDIT_EMAIL, EDIT_ADDRESS, DELETE, CANCEL
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
	void performActionOnContact(Contact* contact);
	void addContact();
	void removeContact(Contact* contact);
	void editSettings();

	void setContactName(Contact* contact);
	void setContactPhone(Contact* contact);
	void setContactEmail(Contact* contact);
	void setContactAddress(Contact* contact);
};
