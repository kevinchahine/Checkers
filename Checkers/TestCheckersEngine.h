#pragma once

#include <time.h>
#include <sstream>

#include "CheckersEngine.h"
#include "Move.h"

class TestCheckersEngine : private CheckersEngine
{
public:
	TestCheckersEngine();
	~TestCheckersEngine();

	void possibleMoves();

	void validMoves();

	void validMoves(const CheckersEngine & gameState);

	void print() const;

	bool isPieceSafe();

	bool isPieceMovable();

	bool isPieceLoner();

	bool isSpaceAHole();

};

