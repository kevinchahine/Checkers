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

	vector<move_t> getPossibleMoves(bool playerIsBlack) const;
	//vector<move_t> getPossibleMovesBlack() const;
	//vector<move_t> getPossibleMovesRed() const;

public:
	// Warning: Assumes Space is Occupied
	bool isMoveUpRightPossible(int r, int c) const;
	// Warning: Assumes Space is Occupied
	bool isMoveUpLeftPossible(int r, int c) const;
	// Warning: Assumes Space is Occupied
	bool isMoveDownLeftPossible(int r, int c) const;
	// Warning: Assumes Space is Occupied
	bool isMoveDownRightPossible(int r, int c) const;
	// Warning: Assumes Space is Occupied
	bool isMoveXYPossible(int r, int c, int r1, int c1) const;

	// Warning: Assumes Space is Occupied
	bool isJumpUpRightPossible(int r, int c) const;
	// Warning: Assumes Space is Occupied
	bool isJumpUpLeftPossible(int r, int c) const;
	// Warning: Assumes Space is Occupied
	bool isJumpDownLeftPossible(int r, int c) const;
	// Warning: Assumes Space is Occupied
	bool isJumpDownRightPossible(int r, int c) const;
	// Warning: Assumes Space is Occupied
	bool isJumpXYPossible(int r1, int r2, int c1, int c2, bool imBlack) const;
};

