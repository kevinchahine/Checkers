#pragma once

#include <time.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <tuple>
#include <Windows.h>

#include "CheckersEngine.h"

using namespace std;

//#define CLOCK_MAX LONG_MAX;
const clock_t CLOCK_MAX = LONG_MAX;

/*
Black plays 1st (MAX)
Red plays 2nd (MIN)
*/
class Solver
{
public:
	typedef tuple<int, move_t, bool> minimax_t;
	enum MINIMAX
	{
		BLUFF_MOVE,
		REAL_MOVE
	};

public:
	Solver();
	Solver(int depthLimit, clock_t timeLimit = CLOCK_MAX);
	~Solver();

	virtual pair<bool, move_t> playAsRed(CheckersEngine & game);
	virtual pair<bool, move_t> playAsBlack(CheckersEngine & game);

	virtual pair<bool, move_t> playAsX(CheckersEngine & game, bool maxPlayersMove);

	// Minimax 
	///pair<int, move_t> minimax(CheckersEngine & game, int depth, bool maxPlayersMove);

	// Minimax with Alpha Beta Prunning
	minimax_t alphabeta(CheckersEngine & game, int depth, int alpha, int beta, bool maxPlayersMove);
	
	virtual stringstream toStream() const = 0;

	virtual int calcHeuristic(const CheckersEngine & game) const = 0;

public:
	int depthLimit;
	clock_t timeLimit;

protected:
	// keeps track of the start time of the minimax algorithm
	// set this to clock() before of every non-recursive
	// minimax() or alphabeta() function call.
	clock_t startTime;
};

