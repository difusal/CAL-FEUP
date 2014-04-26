/*
 * Transition.h
 *
 *  Created on: Apr 26, 2014
 *      Author: henrique
 */

#ifndef TRANSITION_H_
#define TRANSITION_H_

#include <string>

class Transition {
	int id, srcID, destID;
	std::string label;

public:
	Transition(int id, int srcID, int destID, std::string label);
	virtual ~Transition();

	int getID();
	int getSrcID();
	int getDestID();
	std::string getLabel();

	bool operator ==(const Transition &s2) const;
	friend std::ostream & operator <<(std::ostream &os, Transition &s);
};

#endif /* TRANSITION_H_ */
