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

	bool IsDone();
	void ClearStdIn();
	void PressEnterToContinue();
	void ClearStdInAndPressEnterToContinue();

	void LoadContacts();
	void SaveContacts();

	void ShowMainMenu();
	void ShowContactsList();
	void AddContact();
};
