#pragma once

#include <algorithm>
#include <sstream>
#include <time.h>

#include "CheckersEngine.h"
#include "CheckersSolver.h"
#include "Console.h"

using namespace std;

class CheckersManager : CheckersEngine
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
	move_t getUserInput(
		int & fromRow, 
		int & fromCol, 
		int & toRow, 
		int & toCol,
		const vector<move_t> & validMoves) const;

	void printAnalytics(
		int nMovesSinceLastJumpOrPromotion,
		clock_t startTime,
		clock_t endTime,
		clock_t gameStartTime,
		int gameMoveCounter,
		int heuristic,
		HANDLE console);
};

