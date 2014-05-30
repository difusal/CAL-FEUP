#include "Contact.h"

using namespace std;

Contact::Contact(string firstName, string lastName, string phoneNumber,
		string email, string address) {
	this->firstName = firstName;
	this->lastName = lastName;
	this->phoneNumber = phoneNumber;
	this->email = email;
	this->address = address;
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
	return (lastName.compare(NULL_FIELD) == 0) ?
			firstName : firstName + " " + lastName;
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
