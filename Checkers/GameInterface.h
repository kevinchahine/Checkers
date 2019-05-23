#pragma once

#include <iostream>
#include <iomanip>
#include <vector>

#include "E:\Documents\Programming\C++\ASCII\ASCII\ASCII.h"
#include "Colors.h"
#include "Console.h"
#include "View.h"
#include "ViewLayout.h"
#include "CheckerBoard.h"

using namespace std;

class GameInterface
{
public:
	GameInterface();
	GameInterface(const ViewLayout & layout);
	GameInterface(const ViewLayout && layout);
	GameInterface(const GameInterface & gameInterface);
	GameInterface(const GameInterface && gameInterface);
	~GameInterface();
	
	void print() const;

public:
	ViewLayout layout;

	const static size_t N_ROWS_DEFAULT = CheckerBoard::N_ROWS;
	const static size_t N_COLS_DEFAULT = CheckerBoard::N_COLS + 2 * 20;
};

