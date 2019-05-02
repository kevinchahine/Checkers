#pragma once

#include <time.h>

#include "CheckersEngine.h"

class TestCheckersEngine : private CheckersEngine
{
public:
	TestCheckersEngine();
	~TestCheckersEngine();

	void possibleMoves();

	void validMoves();

	void print() const;

	bool isPieceSafe();

	bool isPieceMovable();

	bool isPieceLoner();

	bool isSpaceAHole();

};

