#include "State.h"

using namespace std;

State::State(int id, int init, int final, string label) :
		id(id), init(init), final(final), label(label) {
	transitions.clear();
}

State::~State() {
	// TODO Auto-generated destructor stub
}

int State::getID() {
	return id;
}

bool State::isInit() const {
	return init;
}

bool State::isFinal() const {
	return final;
}

string State::getLabel() {
	return label;
}

vector<Transition*> State::getTransitions() {
	return transitions;
}

bool State::addTransition(Transition *transition) {
	bool nfaDetected = false;

	for (unsigned int i = 0; i < transitions.size(); i++)
		if (*transition == *transitions[i])
			nfaDetected = true;

	transitions.push_back(transition);

	return nfaDetected;
}

bool State::operator ==(const State &s2) const {
	return (id == s2.id && label == s2.label);
}

bool State::operator !=(const State &s2) const {
	return !(*this == s2);
}

ostream & operator <<(ostream &os, State &s) {
	os << s.getLabel();
	return os;
}
