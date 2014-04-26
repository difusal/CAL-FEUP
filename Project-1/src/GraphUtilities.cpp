#include "GraphUtilities.h"

#include <iostream>
#include <cstdlib>
#include <fstream>

#include "graphviewer.h"
#include "State.h"
#include "Transition.h"

using namespace std;

void loadGraphs() {
	string graphsListPath = "graphsList.txt";
	graphsList.clear();

	ifstream fin;
	fin.open(graphsListPath.c_str());
	if (!fin) {
		cerr << "Unable to open file " << graphsListPath << endl;
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

string chooseGraphAndGetItsPath() {
	bool done;
	unsigned int input;

	do {
		done = false;

		cout << endl;
		cout << "Lista de grafos existentes" << endl;
		cout << "--------------------------" << endl;
		for (unsigned int i = 0; i < graphsList.size(); i++)
			cout << i + 1 << ". " << graphsList[i] << endl;

		cout << endl;
		cout << "Escolha um grafo:" << endl;
		cout << "> ";
		cin >> input;

		if (1 <= input && input <= graphsList.size())
			done = true;
		else {
			cin.clear();
			cin.ignore(10000, '\n');

			cout << endl;
			cout << "Input invalido." << endl;
			cout << "Pressione <Enter> para continuar...";
			cin.get();
		}
	} while (!done);

	return graphsList[input - 1];
}

Graph<State> loadGraph(string pathToGraphData) {
	Graph<State> graph;

	ifstream fin;
	fin.open(pathToGraphData.c_str());
	if (!fin) {
		cerr << "Unable to open file " << pathToGraphData << endl;
		exit(1);
	}

	int nVertexes;
	int id, init, final;
	string label;
	fin >> nVertexes;
	for (int i = 0; i < nVertexes; i++) {
		fin >> id >> init >> final;
		getline(fin, label);
		label.erase(label.begin());

		/*
		 // Uncomment for console output
		 cout << "id:" << id << "\tinit:" << init << "\tfinal:" << final << "\tlabel:" << label << endl;
		 */

		State state(id, init, final, label);
		graph.addVertex(state);
	}

	int nEdges;
	int srcID, destID;
	fin >> nEdges;
	for (int i = 0; i < nEdges; i++) {
		fin >> id >> srcID >> destID;
		getline(fin, label);
		label.erase(label.begin());

		/*
		 // Uncomment for console output
		 cout << "id:" << id << "\tsrcID:" << srcID << "\tdestID:" << destID << "\tlabel:" << label << endl;
		 */

		Transition *transition = new Transition(id, srcID, destID, label);
		graph.addEdge(transition);
	}

	return graph;
}

void displayGraph(string pathToGraphData) {
	ifstream fin;
	fin.open(pathToGraphData.c_str());
	if (!fin) {
		cerr << "Unable to open file " << pathToGraphData << endl;
		exit(1);
	}

	GraphViewer *gv = new GraphViewer(600, 600, true);
	gv->createWindow(600, 600);
	gv->defineVertexColor(WHITE);
	gv->defineEdgeColor(BLUE);

	int nVertexes;
	int id, init, final;
	string label;
	fin >> nVertexes;
	for (int i = 0; i < nVertexes; i++) {
		fin >> id >> init >> final;
		getline(fin, label);
		label.erase(label.begin());

		gv->addNode(id);
		gv->setVertexLabel(id, label);

		if (init && final)
			gv->setVertexColor(id, "yellow");
		else if (init)
			gv->setVertexColor(id, "green");
		else if (final)
			gv->setVertexColor(id, "red");
	}

	int nEdges;
	int srcID, destID;
	fin >> nEdges;
	for (int i = 0; i < nEdges; i++) {
		fin >> id >> srcID >> destID;
		getline(fin, label);
		label.erase(label.begin());

		gv->addEdge(id, srcID, destID, EdgeType::DIRECTED);
		gv->setEdgeLabel(id, label);
	}

	gv->rearrange();
	cin.get();
}
