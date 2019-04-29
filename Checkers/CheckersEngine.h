#pragma once

#include <vector>

#include "Checkers.h"

class CheckersEngine : public Checkers
{
public:
	// A move_t 
	// [fromRow][fromCol][toRow ][toCol ]
	// [4-bits ][4-bits ][4-bits][4-bits]
	typedef uint16_t move_t;

public:
	CheckersEngine();
	~CheckersEngine();

	// returns -1 if Red wins
	// returns 0 if continuing
	// returns 1 if Black wins
	// returns 2 if Draw
	int status() const;

	vector<move_t> possibleMovesBlack() const;
	vector<move_t> possibleMovesRed() const;

public:
	// Warning: Assumes Space is Occupied
	bool isJumpUpRightPossible(int r, int c) const;
	// Warning: Assumes Space is Occupied
	bool isJumpUpLeftPossible(int r, int c) const;
	// Warning: Assumes Space is Occupied
	bool isJumpDownLeftPossible(int r, int c) const;
	// Warning: Assumes Space is Occupied
	bool isJumpDownRightPossible(int r, int c) const;

	bool isJumpXYPossible(int r1, int r2, int c1, int c2, bool imBlack) const;
};

