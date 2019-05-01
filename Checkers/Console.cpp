#include "Console.h"

void Console::setColor(HANDLE console, uint8_t color)
{
	SetConsoleTextAttribute(console, color);
}

void Console::setColor(HANDLE console, uint8_t foreColor, uint8_t backColor)
{
	uint8_t color = foreColor + (backColor << 4);

	SetConsoleTextAttribute(console, color);
}

bool Console::getColor(uint8_t & color)
{
	CONSOLE_SCREEN_BUFFER_INFO info;

	if (!GetConsoleScreenBufferInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&info)) {
		return false;
	}

	color = (uint8_t)info.wAttributes;

	return true;
}


