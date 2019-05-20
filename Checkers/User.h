#pragma once

#include <iostream>
#include <string>

#include "Player.h"

using namespace std;

class User : public Player
{
public:
	User();
	~User();

	virtual move_t getDecision(const CheckersEngine & game, bool isBlack);
	virtual move_t getDecisionAsBlack(const CheckersEngine & game);
	virtual move_t getDecisionAsRed(const CheckersEngine & game);
};

