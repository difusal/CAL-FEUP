/*
 * State.h
 *
 *  Created on: Apr 26, 2014
 *      Author: henrique
 */

#ifndef STATE_H_
#define STATE_H_

#include <string>

class State {
	int id, init, final;
	std::string label;

public:
	State(int id, int init, int final, std::string label);
	virtual ~State();

	std::string getLabel();

	bool operator ==(const State &s2) const;
	friend std::ostream & operator <<(std::ostream &os, State &s);
};

#endif /* STATE_H_ */
