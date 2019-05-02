#pragma once

#include <iostream>
 
// [fromRow][fromCol][toRow ][toCol ]
// [4-bits ][4-bits ][4-bits][4-bits]
typedef uint16_t move_t;

namespace Move
{
	void separate(move_t move, uint8_t & fromRow, uint8_t & fromCol, uint8_t & toRow, uint8_t & toCol);	

	move_t combine(uint8_t fromRow, uint8_t fromCol, uint8_t toRow, uint8_t toCol);

}
