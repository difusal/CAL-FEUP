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
	/**
	 * Creates and initializes an interface.
	 */
	Interface();
	virtual ~Interface();

	/**
	 * Returns true if interface is done.
	 *
	 * @return True if interface is done.
	 */
	bool isDone();

	/**
	 * Show the interface main menu.
	 * Here the user can choose one of the MainMenuActions.
	 */
	void showMainMenu();

	/**
	 * Shows the contacts list.
	 */
	void showContactsList();

	/**
	 * Shows the search interface.
	 * If the user presses <Esc> or the contacts list is empty, returns null;
	 * else, returns the selected contact, which is the first contact of the
	 * search results when the user presses <Enter>.
	 *
	 * @return The selected contact.
	 */
	Contact* searchContact();

	/**
	 * Shows a menu with actions that can be performed on the specified contact.
	 *
	 * @param contact The specified contact.
	 */
	void performActionOnContact(Contact* contact);

	/**
	 * Shows add contact interface.
	 */
	void addContact();

	/**
	 * Shows remove contact interface for the specified contact.
	 *
	 * @param contact The specified contact.
	 */
	void removeContact(Contact* contact);

	/**
	 * Shows the edit setting interface.
	 */
	void editSettings();

	/**
	 * Prompts user to input a new valid name for the specified contact.
	 *
	 * @param contact The specified contact.
	 */
	void setContactName(Contact* contact);

	/**
	 * Prompts user to input a new valid phone number for the specified contact.
	 *
	 * @param contact The specified contact
	 */
	void setContactPhone(Contact* contact);

	/**
	 * Prompts user to input a new valid email for the specified contact.
	 *
	 * @param contact The specified contact
	 */
	void setContactEmail(Contact* contact);

	/**
	 * Prompts user to input a new valid address for the specified contact.
	 *
	 * @param contact The specified contact
	 */
	void setContactAddress(Contact* contact);
};
