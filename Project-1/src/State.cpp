#include "State.h"

using namespace std;

State::State(int id, int init, int final, string label) :
		id(id), init(init), final(final), label(label) {

}

State::~State() {
	// TODO Auto-generated destructor stub
}

int State::getID() {
	return id;
}

string State::getLabel() {
	return label;
}

bool State::operator ==(const State &s2) const {
	return (id == s2.id && label == s2.label);
}

ostream & operator <<(ostream &os, State &s) {
	os << s.getLabel();
	return os;
}
