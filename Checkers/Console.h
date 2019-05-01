#pragma once

#include <iostream>
#include <Windows.h>

using namespace std;

namespace Console
{
	void setColor(HANDLE console, uint8_t color);

	void setColor(HANDLE console, uint8_t foreColor, uint8_t backColor);

	// returns true if successfull
	// returns false is unseccessfull
	bool getColor(uint8_t & color) ;
}