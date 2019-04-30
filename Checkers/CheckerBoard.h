#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <Windows.h>

#include "E:\Documents\Programming\C++\ASCII\ASCII\ASCII.h"
#include "Colors.h"

class CheckerBoard
{
public:
#pragma region Constructors
	CheckerBoard();
	CheckerBoard(const CheckerBoard & checkerBoard);
	CheckerBoard(const CheckerBoard && checkerBoard);
	~CheckerBoard();
#pragma endregion

#pragma region Functions
	void print(int indent = 10) const;

protected:
	// Initializes the background and foreground color 
	// Initializes the background text
	// Only needs to be called once 
	void initBase();

	void resetArrays();

	void initBoarders();

	void initCoordinates();

	void initSpaces();

	void placePieces();

	void setColor(HANDLE console, uint8_t color) const;
	bool getColor(uint8_t & color) const;

#pragma endregion

	// ====================== VARIABLES ===================
#pragma region VARIABLES
public:
	char peices[8][8] = { 'X' };
	char peicesForeColor[8][8] = { Colors::WHITE };
	
	static const char darkColor = Colors::DARKGREY;
	static const char lightColor = Colors::GREEN;

protected:
	static const size_t SPACE_WIDTH = 5;
	static const size_t SPACE_HEIGHT = 3;

	static const size_t N_ROWS = 4 + SPACE_HEIGHT * 8; // 28;
	static const size_t N_COLS = 4 + SPACE_WIDTH * 8; // 28;

	const size_t HORIZONTAL_OFFSET = 2;
	const size_t VERTICAL_OFFSET = 2;

	char text[N_ROWS][N_COLS] = { ' ' };
	char foreColor[N_ROWS][N_COLS] = { Colors::WHITE };
	char backColor[N_ROWS][N_COLS] = { Colors::BLACK };
#pragma endregion
};

