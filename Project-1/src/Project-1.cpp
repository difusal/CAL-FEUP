#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>

#include "MenusInterface.h"

using namespace std;

vector<string> graphsList;

void loadGraphs() {
	string graphsListPath = "graphsList.txt";
	graphsList.clear();

	ifstream fin;
	fin.open(graphsListPath.c_str());
	if (!fin) {
		cerr << "Unable to open file " << graphsListPath;
		exit(1);
	}

	int nGraphs;
	string path;
	fin >> nGraphs;
	for (int i = 0; i < nGraphs; i++) {
		fin >> path;
		graphsList.push_back(path);
	}
}

int main() {
	loadGraphs();

	bool done;
	do {
		done = showMainMenu();
	} while (!done);

	cout << endl;
	cout << "Programa terminado." << endl;

	return 0;
}
