#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <Windows.h>

#include "E:\Documents\Programming\C++\ASCII\ASCII\ASCII.h"
#include "Colors.h"

class Checkers
{
public:
	Checkers();
	Checkers(const Checkers& game);
	Checkers(const Checkers&& game);
	~Checkers();

	bool isOccupied(uint8_t row, uint8_t col) const;

	bool isPeiceRed(uint8_t row, uint8_t col) const;
	bool isPeiceBlack(uint8_t row, uint8_t col) const;
	bool isKing(uint8_t row, uint8_t col) const;
	
	bool isSpaceRed(uint8_t row, uint8_t col) const;
	bool isSpaceBlack(uint8_t row, uint8_t col) const;

	// !!!Warning: 
	//	Assumes that [fromRow, fromCol] is occupied by a peice
	//	Calling this function on an empty space will cause unexpected results
	// !!!Warning:
	//	If [toRow, toCol] is occupied, then this function will replace that peice
	//	with [fromRow, fromCol]
	void movePeice(uint8_t fromRow, uint8_t fromCol, uint8_t toRow, uint8_t toCol);
	void removePeice(uint8_t row, uint8_t col);

	// Places a peice in the corresponding row and column.
	// If a peice already exists there, it replaces it with the 
	// new peice
	void placePiece(uint8_t row, uint8_t col, bool color, bool king);
	void print(uint8_t indent = 20) const;

private:
	// initializes the peices as they would be at the start of a game
	void init();

	void setColor(HANDLE console, uint8_t color) const;
	bool getColor(uint8_t & color) const;

	char getSpaceCharacter(uint8_t row, uint8_t col) const;
	
public:
	/*
	Represents the board and all the peices on it.
	Each bit represents to a single space on the board.
	ex: bit 0  represents the upper left  most corner of the board
		bit 63 represents the lower right most corner of the board

	occupied determins if a space is occupied or not
	1 means space is occupied by a peice
	0 means space is not occupied (empty)
	*/
	uint64_t occupied;

	/*
	Represents the board and all the peices on it.
	Each bit represents to a single space on the board.
	ex: bit 0  represents the upper left  most corner of the board
		bit 63 represents the lower right most corner of the board

	peiceColor determins the color of the peice on that space
	if a peice is there
	1 means red peice
	0 means black peice
	*/
	uint64_t red;

	/*
	Represents the board and all the peices on it.
	Each bit represents to a single space on the board.
	ex: bit 0  represents the upper left  most corner of the board
		bit 63 represents the lower right most corner of the board

	king determines if the peice on that space is a king
	if a peice is there
	1 means king
	0 means pawn
	*/
	uint64_t king;

private:
	const char KING_CHAR = 'K';
	const char PAWN_CHAR = 'p';
};

