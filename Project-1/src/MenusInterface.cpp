#include "MenusInterface.h"

#include <iostream>
#include <vector>

#include "GraphUtilities.h"
#include "Graph.hpp"
#include "State.h"

using namespace std;

int showMainMenu() {
	cout << endl;
	cout << "-------------------------------" << endl;
	cout << "Suporte para geracao de testes" << endl;
	cout << "a partir de maquinas de estados" << endl;
	cout << "-------------------------------" << endl;
	cout << endl;
	cout << "1. Visualizar grafo" << endl;
	cout << "2. Validar grafo" << endl;
	cout << "3. Determinar caminho mais curto" << endl;
	cout << "4. Encontrar caminhos totais minimos" << endl;
	cout << "5. Determinar equivalencia de maquinas de estados" << endl;
	cout << "6. Sair" << endl;
	cout << endl;

	int input;
	cout << "Escolha uma opcao:" << endl;
	cout << "> ";
	cin >> input;

	switch (input) {
	case 1:
		showViewGraphMenu();
		break;
	case 2:
		showValidateGraphMenu();
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
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

void showViewGraphMenu() {
	displayGraph(chooseGraphAndGetItsPath());
}

void showValidateGraphMenu() {
	string pathToGraphData = chooseGraphAndGetItsPath();

	Graph<State> graph = loadGraph(pathToGraphData);

	cout << endl;
	if (graph.getNumInitStates() != 1 || graph.getNumFinalStates() < 1) {
		cout << "A maquina de estados e invalida." << endl;
		cout << "Detalhes:" << endl;

		if (graph.getNumInitStates() != 1)
			cout << "\tNao tem um e um so estado inicial (tem "
					<< graph.getNumInitStates() << ")." << endl;

		if (graph.getNumFinalStates() < 1)
			cout << "\tNao tem pelo menos um estado final." << endl;
	} else
		cout << "A maquina de estados e valida." << endl;
}
