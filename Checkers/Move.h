#pragma once

#include <iostream>
 
// [fromRow][fromCol][toRow ][toCol ]
// [4-bits ][4-bits ][4-bits][4-bits]
typedef uint16_t move_t;

namespace Move
{
	// Takes the move_t value
	// And separates it into its parts: fromRow, fromCol, toRow, toCol
	void separate(move_t move, uint8_t & fromRow, uint8_t & fromCol, uint8_t & toRow, uint8_t & toCol);	

	// Takes the 4 parts of a move: fromRow, fromCol, toRow, toCol
	// And combines them into a single value which it returns
	move_t combine(uint8_t fromRow, uint8_t fromCol, uint8_t toRow, uint8_t toCol);
}
