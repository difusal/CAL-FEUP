#include <iostream>
#include <vector>
#include <fstream>

#include "MenusInterface.h"
#include "graphviewer.h"

extern vector<string> graphsList;

void displayGraph(string pathToGraphData) {
	GraphViewer *gv = new GraphViewer(600, 600, true);
	gv->createWindow(600, 600);
	gv->defineVertexColor("white");
	gv->defineEdgeColor("black");

	ifstream fin;
	fin.open(pathToGraphData.c_str());
	if (!fin) {
		cerr << "Unable to open file " << pathToGraphData;
		exit(1);
	}

	int nVertexes;
	int id, init, final;
	string label;
	fin >> nVertexes;
	for (int i = 0; i < nVertexes; i++) {
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
	for (int i = 0; i < nEdges; i++) {
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
}

int showMainMenu() {
	cout << endl;
	cout << "-------------------------------" << endl;
	cout << "Suporte para geracao de testes" << endl;
	cout << "a partir de maquinas de estados" << endl;
	cout << "-------------------------------" << endl;
	cout << endl;
	cout << "1. Adicionar grafo" << endl;
	cout << "2. Visualizar grafo" << endl;
	cout << "3. Validar grafo" << endl;
	cout << "4. Determinar caminho mais curto" << endl;
	cout << "5. Encontrar caminhos totais minimos" << endl;
	cout << "6. Determinar equivalencia de maquinas de estados" << endl;
	cout << "7. Sair" << endl;
	cout << endl;

	int input;
	cout << "Escolha uma opcao:" << endl;
	cout << "> ";
	cin >> input;

	switch (input) {
	case 1:
		break;
	case 2:
		showViewGraphMenu();
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		return true;
	default:
		cin.clear();
		cin.ignore(10000, '\n');

		cout << endl;
		cout << "Input invalido." << endl;
		cout << "Pressione <Enter> para continuar...";
		cin.get();
		break;
	}

	return false;
}

void showAddGraphMenu() {

}

void showViewGraphMenu() {
	cout << endl;
	cout << "Lista de grafos existentes" << endl;
	cout << "--------------------------" << endl;
	for (unsigned int i = 0; i < graphsList.size(); i++)
		cout << i + 1 << ". " << graphsList[i] << endl;

	unsigned int input;
	cout << endl;
	cout << "Escolha um grafo:" << endl;
	cout << "> ";
	cin >> input;

	if (1 <= input && input <= graphsList.size())
		displayGraph(graphsList[input - 1]);
	else {
		cin.clear();
		cin.ignore(10000, '\n');

		cout << endl;
		cout << "Input invalido." << endl;
		cout << "Pressione <Enter> para continuar...";
		cin.get();
	}
}
