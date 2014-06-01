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

	static unsigned int maxResToDisplay;
	static std::string search;
	SearchResults searchResults;

public:
	ContactsAPI();
	virtual ~ContactsAPI();

	const ContactsList& getContacts() const;
	const std::string getContactsToString() const;
	void setContacts(const ContactsList& contacts);
	static unsigned int getMaxResToDisplay();
	void setMaxResToDisplay(unsigned int maxResToDisplay);
	const SearchResults& getSearchResults() const;
	void setSearchResults(const SearchResults& searchResults);

	void loadContacts();
	void saveContacts();

	int loadSettings();
	void saveSettings();

	void updateSearchResults(std::string search);

	void addContact(Contact* contact);
	void addContact(std::string firstName, std::string lastName,
			std::string phoneNumber, std::string email, std::string address);
	void deleteContact(Contact* contact);

	friend std::ostream& operator<<(std::ostream& out, const SearchResults l);
};

std::ostream& operator<<(std::ostream& out, const SearchResults l);
