#pragma once

#include <set>
#include "Contact.h"
#include "Utilities.h"

const std::string contactsListPath = "contacts.txt";
const std::string settingsPath = "settings.txt";

struct ContactsComp {
	bool operator()(const Contact* lhs, const Contact* rhs) const {
		std::string lhsFN = toLower(lhs->getFirstName());
		std::string lhsLN = toLower(lhs->getLastName());
		std::string rhsFN = toLower(rhs->getFirstName());
		std::string rhsLN = toLower(rhs->getLastName());

		// if the first names are the same, compare last names
		// else, compare first names
		bool lastNamesComp = (fieldIsNull(lhsLN) ? "" : lhsLN)
				< (fieldIsNull(rhsLN) ? "" : rhsLN);
		return (lhsFN.compare(rhsFN) == 0) ? lastNamesComp : lhsFN < rhsFN;
	}
};

typedef std::set<Contact*, ContactsComp> ContactsList;
typedef std::vector<Contact*> SearchResults;

class ContactsAPI {
private:
	ContactsList contacts;

	unsigned int maxResToDisplay;
	SearchResults searchResults;

public:
	ContactsAPI();
	virtual ~ContactsAPI();

	const ContactsList& getContacts() const;
	unsigned int getMaxResToDisplay();
	void setMaxResToDisplay(unsigned int maxResToDisplay);
	const SearchResults& getSearchResults() const;

	int loadContacts();
	void saveContacts();

	int loadSettings();
	void saveSettings();

	void updateSearchResults(std::string search);
	void addContact(Contact* contact);
	void addContact(std::string firstName, std::string lastName,
			std::string phoneNumber, std::string email, std::string address);
	void deleteContact(Contact* contact);
};

std::ostream& operator<<(std::ostream& out, const ContactsList& contacts);
