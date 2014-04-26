#pragma once

#include <string>
#include <vector>

#include "Graph.hpp"
#include "State.h"

extern std::vector<std::string> graphsList;

void loadGraphs();
std::string chooseGraphAndGetItsPath();
Graph<State> loadGraph(std::string pathToGraphData);
void displayGraph(std::string pathToGraphData);
