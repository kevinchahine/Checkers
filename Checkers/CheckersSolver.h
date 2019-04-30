#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <Windows.h>

#include "Checkers.h"

/*
Black plays 1st (MAX)
Red plays 2nd (MIN)
*/
class CheckersSolver
{
public:
	CheckersSolver();
	CheckersSolver(Checkers * gamePtr);
	~CheckersSolver();

	void playAsRed();

	// Player 
	int minimax(Checkers game, int depth, bool maxPlayersMove);

	int heuristic(const Checkers & game) const;

	int heuristic1(const Checkers & game) const;
	
public:
	const static int depthLimit = 10;

protected:
	Checkers * gamePtr;

};

