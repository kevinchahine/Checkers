#pragma once

#include <vector>

#include "Checkers.h"

/*
	class CheckersEngine

	Purpose: Controls game mechanics: rules and piece movement 

*/
class CheckersEngine : public Checkers
{
public:
#pragma region Constructors

	CheckersEngine();
	~CheckersEngine();

#pragma endregion

#pragma region Public Functions

	// returns STATUS.BLACK_WINS
	// returns STATUS.RED_WINS
	// returns STATUS.DRAW
	// returns STATUS.CONTINUE
	STATUS status() const;

	vector<move_t> getValidMoves(bool playerIsBlack) const;
	
	// Moves a peice from (fromRow, fromCol) to (toRow, toCol)
	// WARNING: Assumes Move is Valid. calling this function
	//	on an invalid move may produce unexpected results.
	// Moves peice
	// Evaluates jumps
	// Evaluates promotions
	bool movePiece(int fromRow, int fromCol, int toRow, int toCol);

#pragma endregion

public:

#pragma region Move Validation Funcitions

	// Warning: Assumes Space is Occupied
	bool isMoveUpRightValid(int r, int c) const;
	// Warning: Assumes Space is Occupied
	bool isMoveUpLeftValid(int r, int c) const;
	// Warning: Assumes Space is Occupied
	bool isMoveDownLeftValid(int r, int c) const;
	// Warning: Assumes Space is Occupied
	bool isMoveDownRightValid(int r, int c) const;
	// Warning: Assumes Space is Occupied
	bool isMoveXYValid(int r, int c, int r1, int c1) const;

	// Warning: Assumes Space is Occupied
	bool isJumpUpRightValid(int r, int c) const;
	// Warning: Assumes Space is Occupied
	bool isJumpUpLeftValid(int r, int c) const;
	// Warning: Assumes Space is Occupied
	bool isJumpDownLeftValid(int r, int c) const;
	// Warning: Assumes Space is Occupied
	bool isJumpDownRightValid(int r, int c) const;
	// Warning: Assumes Space is Occupied
	bool isJumpXYValid(int r1, int r2, int c1, int c2, bool imBlack) const;

#pragma endregion

};

