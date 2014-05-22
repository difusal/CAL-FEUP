#pragma once

#define foreach(v, it) for(typeof((v).begin()) it = (v).begin(); it != (v).end(); it++)

// a contact has a null field if the string on that field is equal to "null"
inline bool fieldIsNull(std::string field) {
	return field.compare("null") == 0;
}
