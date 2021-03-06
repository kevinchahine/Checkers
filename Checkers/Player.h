#pragma once

#include <tuple>

#include "CheckersEngine.h"
#include "Move.h"

using namespace std;

// first - true iff the move will involve a jump 
// second - the move itself (fromRow, fromCol, toRow, toCol)
typedef pair<bool, move_t> move_pair_t;

class Player
{
public:
	const static bool BLACK = true;
	const static bool RED = false;

public:
	Player();
	~Player();

	virtual move_t getDecision(const CheckersEngine & game, bool isBlack) = 0;
	virtual move_t getDecisionAsBlack(const CheckersEngine & game) = 0;
	virtual move_t getDecisionAsRed(const CheckersEngine & game) = 0;
};

