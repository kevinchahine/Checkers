#pragma once

#include <time.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <tuple>
#include <Windows.h>

#include "Player.h"

#include "CheckersEngine.h"

using namespace std;

//#define CLOCK_MAX LONG_MAX;
const clock_t CLOCK_MAX = LONG_MAX;

/*
Black plays 1st (MAX)
Red plays 2nd (MIN)
*/
class Solver : public Player
{
public:
	enum MINIMAX
	{
		// A "Bluff Move" is a move that could not
		// be fully analyzed before the time limit
		// and therefore its heuristic cannot be
		// compared with the heuristics of other moves. 
		// It is called bluff because it acts as a 
		// place holder when some value needs to be 
		// returned.
		BLUFF_MOVE,
		// A "Real Move" is a move that is fully 
		// analyzed till a depth limit is reached. 
		// The heuristic of a "Read Move" can be 
		// compared with the heuristics of other moves.
		REAL_MOVE
	};
	// get<0> - heuristic of a move according to search
	// get<1> - move
	// get<2> - real/bluff move (MINIMAX::REAL_MOVE or MINIMAX::BLUFF_MOVE)
	typedef tuple<int, move_t, bool> minimax_t;

public:
	Solver();
	Solver(int depthLimit, clock_t timeLimit = CLOCK_MAX);
	~Solver();

	virtual move_t getDecision(const CheckersEngine & game, bool isBlack) const;
	virtual move_t getDecisionAsBlack(const CheckersEngine & game) const;
	virtual move_t getDecisionAsRed(const CheckersEngine & game) const;

	virtual move_pair_t playAsRed(CheckersEngine & game);
	virtual move_pair_t playAsBlack(CheckersEngine & game);

	virtual move_pair_t playAsX(CheckersEngine & game, bool maxPlayersMove);

	// Minimax 
	///pair<int, move_t> minimax(CheckersEngine & game, int depth, bool maxPlayersMove);

	// Minimax with Alpha Beta Prunning
	minimax_t alphabeta(const CheckersEngine & game, int depth, int alpha, int beta, bool maxPlayersMove) const;
	
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

