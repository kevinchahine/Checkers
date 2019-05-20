#pragma once

#include "Player.h"

class User : public Player
{
public:
	User();
	~User();

	virtual move_t getDecision(const CheckersEngine & game, COLOR asPlayer) const;
	virtual move_t getDecisionAsBlack(const CheckersEngine & game) const;
	virtual move_t getDecisionAsRed(const CheckersEngine & game) const;
};

