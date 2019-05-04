#pragma once

#include <algorithm>
#include <sstream>
#include <time.h>

#include "CheckersEngine.h"
#include "Solver.h"
#include "Solver1.h"
#include "Console.h"

using namespace std;

class CheckersManager : public CheckersEngine
{
public:
	CheckersManager();
	~CheckersManager();

	void playUserVsComputer();
	void playUserVsUser();
	void playComputerVsUser();
	void playComputerVsComputer();
	void playComputerVsComputer(Solver & blackSolver, Solver & redSolver);

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

