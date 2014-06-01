#include "Contact.h"

#include <iostream>
#include "StringSearchTools.h"

using namespace std;

Contact::Contact() {
	Contact(NULL_FIELD_LABEL, NULL_FIELD_LABEL, NULL_FIELD_LABEL,
			NULL_FIELD_LABEL, NULL_FIELD_LABEL);
	this->distanceToSearch = 0;
}

Contact::Contact(string firstName, string lastName, string phoneNumber,
		string email, string address) {
	this->firstName = firstName;
	this->lastName = lastName;
	this->phoneNumber = phoneNumber;
	this->email = email;
	this->address = address;
	this->distanceToSearch = 0;
}

Contact::~Contact() {
}

const std::string& Contact::getAddress() const {
	return address;
}

void Contact::setAddress(const std::string& address) {
	this->address = address;
}

const std::string& Contact::getEmail() const {
	return email;
}

void Contact::setEmail(const std::string& email) {
	this->email = email;
}

const std::string Contact::getName() const {
	return fieldIsNull(lastName) ? firstName : firstName + " " + lastName;
}

const std::string& Contact::getFirstName() const {
	return firstName;
}

void Contact::setFirstName(const std::string& firstName) {
	this->firstName = firstName;
}

const std::string& Contact::getLastName() const {
	return lastName;
}

void Contact::setLastName(const std::string& lastName) {
	this->lastName = lastName;
}

const std::string& Contact::getPhoneNumber() const {
	return phoneNumber;
}

void Contact::setPhoneNumber(const std::string& phoneNumber) {
	this->phoneNumber = phoneNumber;
}

int Contact::getDistanceToSearch() const {
	return distanceToSearch;
}

void Contact::setDistanceToSearch(int distanceToSearch) {
	this->distanceToSearch = distanceToSearch;
}

void Contact::updateDistanceToSearch(std::string search) {
	// name comparison
	distanceToSearch = min(
			getEditDistanceOT(search,
					getFirstName().substr(0, search.length())),
			getEditDistanceOT(search,
					toLower(getFirstName().substr(0, search.length()))));
	if (!fieldIsNull(getLastName())) {
		int temp1 = min(
				getEditDistanceOT(search,
						getLastName().substr(0, search.length())),
				getEditDistanceOT(search,
						toLower(getLastName().substr(0, search.length()))));

		int temp2 = min(
				getEditDistanceOT(search, getName().substr(0, search.length())),
				getEditDistanceOT(search,
						toLower(getName().substr(0, search.length()))));

		distanceToSearch = min(distanceToSearch, min(temp1, temp2));
	}

	// phone comparison
	if (!fieldIsNull(getPhoneNumber()))
		distanceToSearch = min(distanceToSearch,
				getEditDistanceOT(search,
						getPhoneNumber().substr(0, search.length())));

	// email comparison
	if (!fieldIsNull(getEmail()))
		distanceToSearch = min(distanceToSearch,
				getEditDistanceOT(search,
						getEmail().substr(0, search.length())));

	// address comparison
	if (!fieldIsNull(getAddress())) {
		vector<string> adrsTks = getTokens(getAddress(), " ");

		for (unsigned int i = 0; i < adrsTks.size(); i++) {
			int temp = min(
					getEditDistanceOT(search,
							adrsTks[i].substr(0, search.length())),
					getEditDistanceOT(search,
							toLower(adrsTks[i]).substr(0, search.length())));

			distanceToSearch = min(distanceToSearch, temp);
		}
	}
}

bool shortestDistanceContact(const Contact* c1, const Contact* c2) {
	return c1->getDistanceToSearch() < c2->getDistanceToSearch();
}

std::ostream& operator<<(std::ostream& out, const Contact& contact) {
	int fieldsLabelWidth = 9;

	// output name
	if (!fieldIsNull(contact.getFirstName())
			|| !fieldIsNull(contact.getLastName())) {
		out.width(fieldsLabelWidth);
		out << "Name: ";

		if (!fieldIsNull(contact.getFirstName()))
			out << contact.getFirstName();

		if (!fieldIsNull(contact.getLastName()))
			out << " " << contact.getLastName();

		out << std::endl;
	}

	// output phone number
	if (!fieldIsNull(contact.getPhoneNumber())) {
		out.width(fieldsLabelWidth);
		out << "Phone: ";

		for (int i = 0; i < 3; i++) {
			out << contact.getPhoneNumber().substr(i * 3, 3);
			if (i < 2)
				out << " ";
		}
		out << std::endl;
	}

	// output email
	if (!fieldIsNull(contact.getEmail())) {
		out.width(fieldsLabelWidth);
		out << "Email: " << contact.getEmail() << std::endl;
	}

	// output address
	if (!fieldIsNull(contact.getAddress())) {
		out.width(fieldsLabelWidth);
		out << "Address: " << contact.getAddress() << std::endl;
	}

	return out;
}
