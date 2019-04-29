#pragma once

#include <time.h>

#include "CheckersEngine.h"

class TestCheckersEngine : private CheckersEngine
{
public:
	TestCheckersEngine();
	~TestCheckersEngine();

	void possibleMoves();

	void print() const;
};

