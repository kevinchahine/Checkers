#pragma once

#include "Solver.h"

class Solver0 : public Solver
{
public:
	Solver0();
	~Solver0();

	stringstream toStream() const;

	int calcHeuristic(const CheckersEngine & game) const;

	int heuristic2(const CheckersEngine & game) const;

};

