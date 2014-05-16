#pragma once

enum Action {
	SEARCH, ADD, REMOVE, EXIT
};

class Interface {
private:
	bool done;

public:
	Interface();
	virtual ~Interface();

	bool isDone();
	void clearStdInAndPressEnterToContinue();

	void showMainMenu();
};
