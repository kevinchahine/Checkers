#pragma once

#include <iostream>
#include <iomanip>
#include <vector>

#include "E:\Documents\Programming\C++\ASCII\ASCII\ASCII.h"
#include "Colors.h"
#include "Console.h"

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
	void print(int indent = 10);

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

#pragma endregion

#pragma region VARIABLES

public:
	static const char DARK_COLOR = Colors::DARKGREY;
	static const char LIGHT_COLOR = Colors::GREEN;
	static const char DARK_HIGHLIGHT = Colors::LIGHTGREY;
	static const char LIGHT_HIGHLIGHT = Colors::LIGHTGREEN;

	char peices[8][8] = { 'X' };
	char peicesForeColor[8][8] = { Colors::WHITE };
	bool highlightedSpaces[8][8] = { false };

protected:
	static const size_t SPACE_WIDTH = 5;
	static const size_t SPACE_HEIGHT = 3;

	static const size_t N_ROWS = 4 + SPACE_HEIGHT * 8;
	static const size_t N_COLS = 4 + SPACE_WIDTH * 8;

	const size_t HORIZONTAL_OFFSET = 2;
	const size_t VERTICAL_OFFSET = 2;

	char text[N_ROWS][N_COLS] = { ' ' };
	char foreColor[N_ROWS][N_COLS] = { Colors::WHITE };
	char backColor[N_ROWS][N_COLS] = { Colors::BLACK };

#pragma endregion
};

