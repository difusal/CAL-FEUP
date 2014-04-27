#pragma once

#include <string>
#include <vector>

#include "Graph.hpp"
#include "State.h"

extern std::vector<std::string> graphsList;

void loadGraphs();
std::string chooseGraphAndGetItsPath();
Graph<State>* loadGraph(std::string pathToGraphData);
void inspectGraphsEquality(std::vector<State> dfs1, std::vector<State> dfs2,
		bool &difInitialStateFlag, bool &difFinalStateFlag,
		bool &difTransitionsFlag);
void displayGraph(std::string pathToGraphData);
