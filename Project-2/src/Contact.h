#pragma once

#include <iostream>
#include <string>
#include "Utilities.h"

class Contact {
private:
	std::string firstName, lastName, phoneNumber, email, address;

public:
	Contact(std::string firstName, std::string lastName,
			std::string phoneNumber, std::string email, std::string address);
	virtual ~Contact();

	const std::string& getAddress() const;
	void setAddress(const std::string& address);
	const std::string& getEmail() const;
	void setEmail(const std::string& email);
	const std::string& getFirstName() const;
	void setFirstName(const std::string& firstName);
	const std::string& getLastName() const;
	void setLastName(const std::string& lastName);
	const std::string& getPhoneNumber() const;
	void setPhoneNumber(const std::string& phoneNumber);

	friend std::ostream& operator<<(std::ostream& out, const Contact& contact) {
		out.width(9);
		out << "Name: " << contact.firstName;
		if (!fieldIsNull(contact.lastName))
			out << " " << contact.lastName;
		out << std::endl;

		if (!fieldIsNull(contact.phoneNumber)) {
			out.width(9);
			out << "Phone: " << contact.phoneNumber << std::endl;
		}

		if (!fieldIsNull(contact.email)) {
			out.width(9);
			out << "Email: " << contact.email << std::endl;
		}

		if (!fieldIsNull(contact.address)) {
			out.width(9);
			out << "Address: " << contact.address << std::endl;
		}

		return out;
	}
};
