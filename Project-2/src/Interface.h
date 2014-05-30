#pragma once

#include <set>
#include "Contact.h"

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

public:
	Interface();
	virtual ~Interface();

	bool isDone();
	void clearStdIn();
	void pressEnterToContinue();
	void clearStdInAndPressEnterToContinue();

	void loadContacts();
	void saveContacts();

	void showMainMenu();
	void showContactsList();
	void addContact();
	void searchContact();
};
