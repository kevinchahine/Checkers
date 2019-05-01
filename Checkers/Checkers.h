#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <Windows.h>

#include "CheckerBoard.h"
#include "E:\Documents\Programming\C++\ASCII\ASCII\ASCII.h"
#include "Colors.h"

class Checkers
{
#pragma region typedef and enum
public:
	// A move_t 
	// [fromRow][fromCol][toRow ][toCol ]
	// [4-bits ][4-bits ][4-bits][4-bits]
	typedef uint16_t move_t;

	enum STATUS {
		BLACK_WINS,
		DRAW,
		RED_WINS,
		CONTINUE
	};
#pragma endregion

public:
#pragma region Constructors

	Checkers();
	Checkers(const Checkers& game);
	Checkers(const Checkers&& game);
	~Checkers();

#pragma endregion

#pragma region Public Functions
	
	bool isOccupied(uint8_t row, uint8_t col) const;

	bool isPieceRed(uint8_t row, uint8_t col) const;
	bool isPieceBlack(uint8_t row, uint8_t col) const;
	bool isKing(uint8_t row, uint8_t col) const;
	
	bool isSpaceRed(uint8_t row, uint8_t col) const;
	bool isSpaceBlack(uint8_t row, uint8_t col) const;

	// !!!Warning: 
	//	Assumes that [fromRow, fromCol] is occupied by a piece
	//	Calling this function on an empty space will cause unexpected results
	// !!!Warning:
	//	If [toRow, toCol] is occupied, then this function will replace that piece
	//	with [fromRow, fromCol]
	void movePiece(uint8_t fromRow, uint8_t fromCol, uint8_t toRow, uint8_t toCol);
	void removePiece(uint8_t row, uint8_t col);

	// Places a piece in the corresponding row and column.
	// If a piece already exists there, it replaces it with the 
	// new piece
	void placePiece(uint8_t row, uint8_t col, bool red, bool king);
	void print(uint8_t indent = 20, move_t highlightMove = 0) const;

	static void setColor(HANDLE console, uint8_t color);
	static bool getColor(uint8_t & color);

#pragma endregion

#pragma region Private Functions
private:

	// initializes the pieces as they would be at the start of a game
	void init();

	char getSpaceCharacter(uint8_t row, uint8_t col) const;
	
#pragma endregion

#pragma region Protected Variables
protected:

	/*
	Represents the board and all the pieces on it.
	Each bit represents to a single space on the board.
	ex: bit 0  represents the upper left  most corner of the board
		bit 63 represents the lower right most corner of the board

	occupied determins if a space is occupied or not
	1 means space is occupied by a piece
	0 means space is not occupied (empty)
	*/
	uint64_t occupied;

	/*
	Represents the board and all the pieces on it.
	Each bit represents to a single space on the board.
	ex: bit 0  represents the upper left  most corner of the board
		bit 63 represents the lower right most corner of the board

	pieceColor determins the color of the piece on that space
	if a piece is there
	1 means red piece
	0 means black piece
	*/
	uint64_t red;

	/*
	Represents the board and all the pieces on it.
	Each bit represents to a single space on the board.
	ex: bit 0  represents the upper left  most corner of the board
		bit 63 represents the lower right most corner of the board

	king determines if the piece on that space is a king
	if a piece is there
	1 means king
	0 means pawn
	*/
	uint64_t king;

#pragma endregion

#pragma region Public Variables
public:

	const char KING_CHAR = 'K';
	const char PAWN_CHAR = 'P';

#pragma endregion
};

