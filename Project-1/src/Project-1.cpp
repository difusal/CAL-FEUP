#include <iostream>
#include <fstream>
#include "graphviewer.h"

#define GRAPH "graphs/Multibanco.txt"
#define FOR(i, a, b) for(int i = a; i < b; i++)

int main() {
	GraphViewer *gv = new GraphViewer(600, 600, true);
	gv->createWindow(600, 600);

	gv->defineVertexColor("white");
	gv->defineEdgeColor("black");

	ifstream fin;
	fin.open(GRAPH);
	if (!fin) {
		cerr << "Unable to open file datafile.txt";
		exit(1);
	}

	int nVertexes;
	int id, init, final;
	string label;

	fin >> nVertexes;
	FOR (i, 0, nVertexes)
	{
		fin >> id >> init >> final;
		getline(fin, label);

		/*
		 // Uncomment for console output
		 cout << "id: " << id << "\tinit: " << init << "\tfinal: " << final << "\tlabel: " << label << endl;
		 */

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
	FOR (i, 0, nEdges)
	{
		fin >> id >> srcID >> destID;
		getline(fin, label);

		/*
		 // Uncomment for console output
		 cout << "id: " << id << "\tsrcID: " << srcID << "\tdestID: " << destID << "\tlabel: " << label << endl;
		 */

		gv->addEdge(id, srcID, destID, EdgeType::DIRECTED);
		gv->setEdgeLabel(id, label);
	}

	gv->rearrange();

	cin.get();
	return 0;
}
