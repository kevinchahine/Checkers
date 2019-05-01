#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <Windows.h>

#include "CheckersEngine.h"

/*
Black plays 1st (MAX)
Red plays 2nd (MIN)
*/
class CheckersSolver
{
public:
	CheckersSolver();
	~CheckersSolver();

	pair<bool, move_t> playAsRed(CheckersEngine & game);
	pair<bool, move_t> playAsBlack(CheckersEngine & game);

	// Player 
	pair<int, move_t> minimax(CheckersEngine & game, int depth, bool maxPlayersMove);

	// Minimax with Alpha Beta Prunning
	pair<int, move_t> alphabeta(CheckersEngine & game, int depth, int alpha, int beta, bool maxPlayersMove);

	int heuristic(const CheckersEngine & game) const;

	int heuristic1(const CheckersEngine & game) const;
	 
	int heuristic2(const CheckersEngine & game) const;

public:
	const static int depthLimit = 4;

};

