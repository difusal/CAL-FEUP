#include "StringSearchTools.h"

#include <vector>
#include <algorithm>

using namespace std;

// Returns the distance between two strings. Space complexity: O(|P|.|T|).
int getEditDistanceOPT(string needle, string haystack) {
	// initialization
	vector<vector<int> > D(haystack.length() + 1,
			vector<int>(needle.length() + 1));

	for (unsigned int i = 0; i <= needle.length(); i++)
		D[0][i] = i;
	for (unsigned int i = 0; i <= haystack.length(); i++)
		D[i][0] = i;

	// algorithm
	for (unsigned int i = 1; i <= haystack.length(); i++) {
		for (unsigned int j = 1; j <= needle.length(); j++) {
			if (haystack[i - 1] == needle[j - 1])
				D[i][j] = D[i - 1][j - 1];
			else
				D[i][j] = 1
						+ min(min(D[i - 1][j - 1], D[i - 1][j]), D[i][j - 1]);
		}
	}

	// return distance between strings
	return D[haystack.length()][needle.length()];
}

// Returns the distance between two strings. Space complexity: O(|T|).
int getEditDistanceOT(string needle, string haystack) {
	// initialization
	vector<int> D;
	for (unsigned int i = 0; i <= needle.length(); i++)
		D.push_back(i);

	// algorithm
	int oldN, newN;
	for (unsigned int i = 1; i <= haystack.length(); i++) {
		oldN = D[0];
		D[0] = i;

		for (unsigned int j = 1; j <= needle.length(); j++) {
			if (haystack[i - 1] == needle[j - 1])
				newN = oldN;
			else
				newN = 1 + min(min(oldN, D[j]), D[j - 1]);

			oldN = D[j];
			D[j] = newN;
		}
	}

	// return distance between strings
	return D[needle.length()];
}
