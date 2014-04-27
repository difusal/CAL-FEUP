#pragma once

#include <string>
#include <vector>

extern std::vector<std::string> graphsList;

void clearStdInAndPressEnterToContinue();

int showMainMenu();
void showViewGraphMenu();
void showValidateGraphMenu();
void showShortestPathToStateMenu();
void showFindMinimumTotalPathsMenu();
void showTestStateMachinesEqualityMenu();
