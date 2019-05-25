#pragma once

#include <algorithm>
#include <sstream>
#include <time.h>

#include "CheckersEngine.h"
#include "Player.h"
#include "User.h"
#include "Solver.h"
#include "Solver1.h"
#include "Console.h"

using namespace std;

class CheckersManager : public CheckersEngine
{
public:
	CheckersManager();
	CheckersManager(const CheckersManager & checkersManager);
	CheckersManager(const CheckersManager && checkersManager);
	CheckersManager(const CheckersEngine & checkersEngine);
	CheckersManager(const CheckersEngine && checkersEngine);
	~CheckersManager();

	void play(Player & blackPlayer, Player & redPlayer, bool showOutput = true, bool blacksFirst = true);

	stringstream getEndGameMessage() const;

private:
	void printAnalytics(
		int nMovesSinceLastJumpOrPromotion,
		clock_t startTime,
		clock_t endTime,
		clock_t gameStartTime,
		int gameMoveCounter,
		int heuristic,
		HANDLE console);
};

