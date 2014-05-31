#pragma once

#include <iostream>
#include <string>
#include "Utilities.h"

class Contact {
private:
	std::string firstName, lastName, phoneNumber, email, address;
	int distanceToSearch;

public:
	Contact(std::string firstName, std::string lastName,
			std::string phoneNumber, std::string email, std::string address);
	virtual ~Contact();

	const std::string& getAddress() const;
	void setAddress(const std::string& address);
	const std::string& getEmail() const;
	void setEmail(const std::string& email);
	const std::string getName() const;
	const std::string& getFirstName() const;
	void setFirstName(const std::string& firstName);
	const std::string& getLastName() const;
	void setLastName(const std::string& lastName);
	const std::string& getPhoneNumber() const;
	void setPhoneNumber(const std::string& phoneNumber);
	int getDistanceToSearch() const;
	void setDistanceToSearch(int distanceToSearch);
	void updateDistanceToSearch(std::string search);

	friend std::ostream& operator<<(std::ostream& out, const Contact& contact) {
		int fieldsLabelWidth = 9;

		// output name
		if (!fieldIsNull(contact.firstName) || !fieldIsNull(contact.lastName)) {
			out.width(fieldsLabelWidth);
			out << "Name: ";

			if (!fieldIsNull(contact.firstName))
				out << contact.firstName;

			if (!fieldIsNull(contact.lastName))
				out << " " << contact.lastName;

			out << std::endl;
		}

		// output phone number
		if (!fieldIsNull(contact.phoneNumber)) {
			out.width(fieldsLabelWidth);
			out << "Phone: ";

			for (int i = 0; i < 3; i++) {
				out << contact.phoneNumber.substr(i * 3, 3);
				if (i < 2)
					out << " ";
			}
			out << std::endl;
		}

		// output email
		if (!fieldIsNull(contact.email)) {
			out.width(fieldsLabelWidth);
			out << "Email: " << contact.email << std::endl;
		}

		// output address
		if (!fieldIsNull(contact.address)) {
			out.width(fieldsLabelWidth);
			out << "Address: " << contact.address << std::endl;
		}

		return out;
	}
};

bool shortestDistanceContact(const Contact* c1, const Contact* c2);

struct ContactsComp {
	bool operator()(const Contact* lhs, const Contact* rhs) const {
		std::string lhsFirstName = toLower(lhs->getFirstName());
		std::string lhsLastName = toLower(lhs->getLastName());

		std::string rhsFirstName = toLower(rhs->getFirstName());
		std::string rhsLastName = toLower(rhs->getLastName());

		// if the first names are the same
		if (lhsFirstName.compare(rhsFirstName) == 0)
			// compare last names
			return (fieldIsNull(lhsLastName) ? "" : lhsLastName)
					< (fieldIsNull(rhsLastName) ? "" : rhsLastName);
		else
			// compare first names
			return lhsFirstName < rhsFirstName;
	}
};
