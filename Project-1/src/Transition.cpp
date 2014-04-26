/*
 * Transition.cpp
 *
 *  Created on: Apr 26, 2014
 *      Author: henrique
 */

#include "Transition.h"

using namespace std;

Transition::Transition(int id, int srcID, int destID, std::string label) :
		id(id), srcID(srcID), destID(destID), label(label) {

}

Transition::~Transition() {
	// TODO Auto-generated destructor stub
}

int Transition::getID() {
	return id;
}

int Transition::getSrcID() {
	return srcID;
}

int Transition::getDestID() {
	return destID;
}

string Transition::getLabel() {
	return label;
}

bool Transition::operator ==(const Transition &s2) const {
	return label == s2.label;
}

ostream & operator <<(ostream &os, Transition &s) {
	os << s.getLabel();
	return os;
}
