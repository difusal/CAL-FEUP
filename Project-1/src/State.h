/*
 * State.h
 *
 *  Created on: Apr 26, 2014
 *      Author: henrique
 */

#ifndef STATE_H_
#define STATE_H_

#include <string>
#include <vector>

#include "Transition.h"

class State {
	int id, init, final;
	std::string label;
	std::vector<Transition*> transitions;

public:
	State(int id, int init, int final, std::string label);
	virtual ~State();

	int getID();
	bool isInit() const;
	bool isFinal() const;
	std::string getLabel();
	std::vector<Transition*> getTransitions();

	/**
	 * Retorna true se ja existir a transicao.
	 */
	bool addTransition(Transition *transition);

	bool operator ==(const State &s2) const;
	bool operator !=(const State &s2) const;
	friend std::ostream & operator <<(std::ostream &os, State &s);
};

#endif /* STATE_H_ */
