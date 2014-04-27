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

Graph<State>* loadGraph(string pathToGraphData) {
	Graph<State>* graph = new Graph<State>;

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
		graph->addVertex(state);
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
		graph->addEdge(transition);
	}

	return graph;
}

void inspectGraphsEquality(std::vector<State> dfs1, std::vector<State> dfs2,
		bool &difInitialStateFlag, bool &difFinalStateFlag,
		bool &difTransitionsFlag) {
	// para cada estado
	for (unsigned int i = 0; i < dfs1.size(); i++) {
		// ver se um e inicial e o outro nao
		if (dfs1[i].isInit() != dfs2[i].isInit())
			difInitialStateFlag = true;

		// ver se um e final e o outro nao
		if (dfs1[i].isFinal() != dfs2[i].isFinal())
			difFinalStateFlag = true;

		int dfs1StateNumTransitions = dfs1[i].getTransitions().size();
		int dfs2StateNumTransitions = dfs2[i].getTransitions().size();

		// ver se o numero de transicoes e o mesmo
		if (dfs1StateNumTransitions != dfs2StateNumTransitions)
			difTransitionsFlag = true;
		else {
			// se for, verificar que os eventos sao os mesmos
			for (int j = 0; j < dfs1StateNumTransitions; j++) {
				// para cada transicao do estado actual de dfs1
				Transition transition = *dfs1[i].getTransitions()[j];

				// procurar uma equivalente no estado actual de dfs2
				bool foundEquivalentTransition = false;
				for (int k = 0; k < dfs2StateNumTransitions; k++) {
					if (transition == *dfs2[i].getTransitions()[k]) {
						foundEquivalentTransition = true;
						break;
					}
				}

				// se nao tiver sido encontrado um evento equivalente
				if (!foundEquivalentTransition) {
					difTransitionsFlag = true;
					break;
				}
			}
		}

		// se todas as falhas ja tiverem sido detectadas,
		// ja nao vale a pena analisar mais o grafo
		if (difInitialStateFlag && difFinalStateFlag && difTransitionsFlag)
			break;
	}
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

	cin.clear();
	cin.ignore(10000, '\n');
	cout << endl;
	cout << "Pressione <Enter> para continuar...";
	cin.get();

	gv->closeWindow();
	delete (gv);
}
