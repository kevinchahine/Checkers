#pragma once

#include <algorithm>
#include <sstream>
#include <time.h>

#include "CheckersEngine.h"
#include "CheckersSolver.h"
#include "Console.h"

using namespace std;

class CheckersManager
{
public:
	CheckersManager();
	~CheckersManager();

	void playUserVsComputer();
	void playUserVsUser();
	void playComputerVsUser();
	void playComputerVsComputer();
	
	stringstream getEndGameMessage() const;

private:
	CheckersEngine::move_t getUserInput(
		int & fromRow, int & fromCol, int & toRow, int & toCol,
		const vector<CheckersEngine::move_t> & validMoves) const;
	
public:
	CheckersEngine * gamePtr;
};

