#pragma once

#include "CheckersSolver.h"

class CheckersSolver1 : public CheckersSolver
{
public:
	CheckersSolver1();
	~CheckersSolver1();

	int calcHeuristic(const CheckersEngine & game) const;


};

