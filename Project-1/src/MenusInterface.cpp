#include "MenusInterface.h"

#include <iostream>
#include <vector>

#include "GraphUtilities.h"
#include "Graph.hpp"
#include "State.h"

using namespace std;

void clearStdInAndPressEnterToContinue() {
	cin.clear();
	cin.ignore(10000, '\n');
	cout << "Pressione <Enter> para continuar...";
	cin.get();
}

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
	cout << "5. Determinar equivalencia entre maquinas de estados" << endl;
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
		showShortestPathToStateMenu();
		break;
	case 4:
		showFindMinimumTotalPathsMenu();
		break;
	case 5:
		showTestStateMachinesEqualityMenu();
		break;
	case 6:
		return true;
	default:
		cout << endl;
		cout << "Input invalido." << endl;
		clearStdInAndPressEnterToContinue();
		break;
	}

	return false;
}

void showViewGraphMenu() {
	displayGraph(chooseGraphAndGetItsPath());
}

void showValidateGraphMenu() {
	string pathToGraphData = chooseGraphAndGetItsPath();

	Graph<State>* graph = loadGraph(pathToGraphData);
	vector<Vertex<State>*> sources = graph->getSources();

	bool initStateFlag = graph->getNumInitStates() != 1;
	bool finalStateFlag = graph->getNumFinalStates() < 1;
	bool unreachableStateFlag = sources.size() > 1
			|| (sources.size() == 1
					&& sources[0]->getInfo()
							!= graph->getInitialState().getInfo());
	bool nfaFlag = graph->getNfaFlag();

	bool invalidStateMachine = initStateFlag || finalStateFlag
			|| unreachableStateFlag || nfaFlag;

	cout << endl;
	if (invalidStateMachine) {
		cout << "A maquina de estados e invalida." << endl;
		cout << "Detalhes:" << endl;

		if (initStateFlag)
			cout << "\tNao tem um e um so estado inicial (tem "
					<< graph->getNumInitStates() << ")." << endl;

		if (finalStateFlag)
			cout << "\tNao tem pelo menos um estado final." << endl;

		if (unreachableStateFlag)
			cout << "\tNem todos os estados são atingiveis." << endl;

		if (nfaFlag)
			cout << "\tA maquina de estados e nao determinista." << endl;
	} else
		cout << "A maquina de estados e valida." << endl;

	delete (graph);
	clearStdInAndPressEnterToContinue();
}

void showShortestPathToStateMenu() {
	string pathToGraphData = chooseGraphAndGetItsPath();
	Graph<State>* graph = loadGraph(pathToGraphData);

	cout << endl;
	cout << "Estados de destino" << endl;
	cout << "------------------" << endl;
	for (unsigned int i = 0; i < graph->getVertexSet().size(); i++)
		cout << i + 1 << ". " << graph->getVertexSet()[i]->getInfo().getLabel()
				<< endl;

	unsigned int input;
	cout << endl;
	cout << "Escolha um estado de destino:" << endl;
	cout << "> ";
	cin >> input;

	if (1 <= input && input <= graph->getVertexSet().size())
		input--;
	else {
		cout << endl;
		cout << "Input invalido." << endl;
		clearStdInAndPressEnterToContinue();
		return;
	}

	// saving destiny state
	State destState = graph->getVertexSet()[input]->getInfo();
	if (destState.isInit()) {
		cout << endl;
		cout << "O estado selecionado foi o estado inicial." << endl;
		clearStdInAndPressEnterToContinue();
		return;
	}

	// getting shortest path
	vector<State> path = graph->getPath(graph->getInitialState().getInfo(),
			destState);

	cout << endl;
	cout << "Caminho mais curto para \"" << destState << "\":\n";
	for (unsigned int i = 0; i < path.size(); i++) {
		cout << path[i] << endl;

		if (i < path.size() - 1) {
			string label = path[i].getTransitionTo(path[i + 1])->getLabel();
			cout << "\t-> " << label << endl;
		}
	}
	cout << endl;

	delete (graph);
	clearStdInAndPressEnterToContinue();
}

void showFindMinimumTotalPathsMenu() {
	clearStdInAndPressEnterToContinue();
}

void showTestStateMachinesEqualityMenu() {
	string pathToGraphData1, pathToGraphData2;
	Graph<State> *graph1, *graph2;

	pathToGraphData1 = chooseGraphAndGetItsPath();
	pathToGraphData2 = chooseGraphAndGetItsPath();

	if (pathToGraphData1 == pathToGraphData2) {
		cout << endl;
		cout << "Se as maquinas de estado escolhidas forem" << endl
				<< "as mesmas, e obvio que sao equivalentes." << endl;
	} else {
		graph1 = loadGraph(pathToGraphData1);
		graph2 = loadGraph(pathToGraphData2);
		vector<State> dfs1 = graph1->dfs();
		vector<State> dfs2 = graph2->dfs();

		bool difNumStatesFlag = dfs1.size() != dfs2.size();
		bool difInitialStateFlag = false;
		bool difFinalStateFlag = false;
		bool difTransitionsFlag = false;
		inspectGraphsEquality(dfs1, dfs2, difInitialStateFlag,
				difFinalStateFlag, difTransitionsFlag);

		bool difStateMachinesFlag = difNumStatesFlag || difInitialStateFlag
				|| difFinalStateFlag || difTransitionsFlag;

		if (difStateMachinesFlag) {
			cout << endl;
			cout << "As maquinas de estado nao sao equivalentes." << endl;
			cout << "Detalhes:" << endl;

			if (difNumStatesFlag)
				cout << "\tO numero de estados nao e o mesmo." << endl;
			if (difInitialStateFlag)
				cout << "\tO estado inicial e diferente." << endl;
			if (difFinalStateFlag)
				cout << "\tO estado final nao e o mesmo." << endl;
			if (difTransitionsFlag)
				cout << "\tAs transicao entre estados sao diferentes." << endl;
		} else {
			cout << endl;
			cout << "As maquinas de estado sao equivalentes." << endl;
		}

		delete (graph1);
		delete (graph2);
	}

	clearStdInAndPressEnterToContinue();
}
