#pragma once

#include <string>
#include "Utilities.h"

class Contact {
private:
	std::string firstName, lastName, phoneNumber, email, address;
	int distanceToSearch;

public:
	Contact();
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

	/**
	 * Updates this contact distance to the specified search string.
	 *
	 * @param search The specified search string.
	 */
	void updateDistanceToSearch(std::string search);
};

bool shortestDistanceContactFirst(const Contact* c1, const Contact* c2);

std::ostream& operator<<(std::ostream& out, const Contact& contact);
