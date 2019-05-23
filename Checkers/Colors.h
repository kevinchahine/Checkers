#pragma once

namespace Colors {
	const unsigned char	BLACK = 0;
	const unsigned char	BLUE = 1;
	const unsigned char	GREEN = 2;
	const unsigned char	CYAN = 3;
	const unsigned char	RED = 4;
	const unsigned char	MAGENTA = 5;
	const unsigned char	BROWN = 6;
	const unsigned char	LIGHTGREY = 7;
	const unsigned char	DARKGREY = 8;
	const unsigned char	LIGHTBLUE = 9;
	const unsigned char	LIGHTGREEN = 10;
	const unsigned char	LIGHTCYAN = 11;
	const unsigned char	LIGHTRED = 12;
	const unsigned char	LIGHTMAGENTA = 13;
	const unsigned char	YELLOW = 14;
	const unsigned char	WHITE = 15;
	const unsigned char	BLINK = 128;

	inline unsigned char combine(unsigned char foreColor, unsigned char backColor)
	{
		return foreColor + (backColor << 4);
	}

	inline unsigned char backColor(unsigned char color)
	{
		return color >> 4;
	}

	inline unsigned char foreColor(unsigned char color)
	{
		return color & 0x0f;
	}
}