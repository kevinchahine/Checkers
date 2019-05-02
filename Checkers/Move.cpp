#include "Move.h"

void Move::separate(move_t move, uint8_t & fromRow, uint8_t & fromCol, uint8_t & toRow, uint8_t & toCol)
{
	fromRow = (move >> 12) & 0xf;
	fromCol = (move >> 8) & 0xf;
	toRow = (move >> 4) & 0xf;
	toCol = move & 0xf;
}

move_t Move::combine(uint8_t fromRow, uint8_t fromCol, uint8_t toRow, uint8_t toCol)
{
	return (fromRow << 12) | (fromCol << 8) | (toRow << 4) | toCol;
}
