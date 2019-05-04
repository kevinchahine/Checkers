#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <Windows.h>

#include "CheckersEngine.h"

using namespace std;

/*
Black plays 1st (MAX)
Red plays 2nd (MIN)
*/
class Solver
{
public:
	Solver();
	~Solver();

	virtual pair<bool, move_t> playAsRed(CheckersEngine & game);
	virtual pair<bool, move_t> playAsBlack(CheckersEngine & game);

	// Minimax 
	pair<int, move_t> minimax(CheckersEngine & game, int depth, bool maxPlayersMove);

	// Minimax with Alpha Beta Prunning
	pair<int, move_t> alphabeta(CheckersEngine & game, int depth, int alpha, int beta, bool maxPlayersMove);
	
	virtual stringstream toStream() const = 0;

	virtual int calcHeuristic(const CheckersEngine & game) const = 0;

public:
	const static int DEPTH_LIMIT = 7;
};

