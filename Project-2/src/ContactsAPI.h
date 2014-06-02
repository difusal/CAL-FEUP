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

	/**
	 * Loads an existing contacts list.
	 *
	 * @return 0 if success, -1 otherwise.
	 */
	int loadContacts();

	/**
	 * Saves the current contacts list.
	 */
	void saveContacts();

	/**
	 * Loads the program settings.
	 *
	 * @return 0 if success, -1 otherwise.
	 */
	int loadSettings();

	/**
	 * Saves the current program settings.
	 */
	void saveSettings();

	/**
	 * Updates the search results using the specified search string.
	 *
	 * @param search The specified string.
	 */
	void updateSearchResults(std::string search);

	/**
	 * Adds the specified contact to the contacts list.
	 *
	 * @param contact The contact to be added to the contacts list.
	 */
	void addContact(Contact* contact);

	/**
	 * Creates a contact with the specified arguments and adds it to the contacts list.
	 *
	 * @param firstName The first name of the contact to be added.
	 * @param lastName The last name of the contact to be added.
	 * @param phoneNumber The phone number of the contact to be added.
	 * @param email The email of the contact to be added.
	 * @param address The address of the contact to be added.
	 */
	void addContact(std::string firstName, std::string lastName,
			std::string phoneNumber, std::string email, std::string address);

	/**
	 * Deletes a contact from the contacts list.
	 *
	 * @param contact The contact to be deleted.
	 */
	void deleteContact(Contact* contact);
};

std::ostream& operator<<(std::ostream& out, const ContactsList& contacts);
