#include "Checkers.h"

Checkers::Checkers() :
	occupied(0xaa55aa000055aa55),
	black(0x55aa55ffaa55aa55),
	king(0x0)
{
	//init();
}

Checkers::Checkers(uint64_t occupied, uint64_t black, uint64_t king) :
	occupied(occupied),
	black(black),
	king(king)
{
}

Checkers::Checkers(const Checkers & game) :
	occupied(game.occupied),
	black(game.black),
	king(game.king)
{
}

Checkers::Checkers(const Checkers && game) :
	occupied(game.occupied),
	black(game.black),
	king(game.king)
{
}

Checkers::~Checkers()
{
}

bool Checkers::isOccupied(uint8_t row, uint8_t col) const
{
	uint64_t mask = ((uint64_t)1 << ((row << 3) + col));
	return (occupied & mask) == mask;
}

bool Checkers::isPieceRed(uint8_t row, uint8_t col) const
{
	uint64_t mask = ((uint64_t) 1 << ((row * 8) + col));
	return (black & mask) != mask;
}

bool Checkers::isPieceBlack(uint8_t row, uint8_t col) const
{
	uint64_t mask = ((uint64_t) 1 << ((row * 8) + col));
	return (black & mask) == mask;
}

bool Checkers::isKing(uint8_t row, uint8_t col) const
{
	uint64_t mask = ((uint64_t)1 << ((row << 3) + col));
	return (king & mask) == mask;
}

bool Checkers::isPawn(uint8_t row, uint8_t col) const
{
	uint64_t mask = ((uint64_t)1 << ((row << 3) + col));
	return (king & mask) != mask;
}

bool Checkers::isSpaceRed(uint8_t row, uint8_t col) const
{
	return (row + col) % 2 == 1;
}

bool Checkers::isSpaceBlack(uint8_t row, uint8_t col) const
{
	return (row + col) % 2 == 0;
}

void Checkers::movePiece(uint8_t fromRow, uint8_t fromCol, uint8_t toRow, uint8_t toCol)
{
	uint64_t r;
	uint64_t c;
	uint64_t b;
	uint64_t fromMask;
	uint64_t toMask;

	r = toRow;
	c = toCol;
	toMask = (uint64_t)1 << ((r << 3) + c);

	r = fromRow;
	c = fromCol;
	fromMask = (uint64_t)1 << ((r << 3) + c);
	
	// A.) Move Occupied bit
	this->occupied &= ~fromMask;
	this->occupied |= toMask;

	// B.) Move Piece Color bit
	// B-1.) Get piece color at [fromRow, fromCol]
	b = (this->black & fromMask);

	// 2.) Set piece color at [toRow, toCol]
	this->black &= ~toMask;						// Clear to bit
	b = (b == fromMask ? toMask : (uint64_t) 0);// Is piece black?
	this->black |= b;							// Set to bit

	// C.) Move Rank bit
	// C-1.) Get rank at [fromRow, fromCol]
	b = (this->king & fromMask);

	// C-2.) Set piece rank at [toRow, toCol]
	this->king &= ~toMask;						// Clear to bit
	b = (b == fromMask ? toMask : (uint64_t) 0); // Is piece a king?
	this->king |= b;							// Set to bit
}

void Checkers::removePiece(uint8_t row, uint8_t col)
{
	uint64_t r = row;
	uint64_t c = col;
	uint64_t mask = (uint64_t)1 << ((r << 3) + c);
	
	occupied &= ~mask;
}

void Checkers::placePiece(uint8_t row, uint8_t col, bool black, bool king)
{
	uint64_t r = row;
	uint64_t c = col;
	uint64_t b;
	
	uint64_t mask = (uint64_t) 1 << ((r << 3) + c);
	
	b = (black ? (uint64_t)1 : (uint64_t)0);
	uint64_t colorMask = (b << ((r << 3) + c));
	
	b = (king ? (uint64_t)1 : (uint64_t)0);
	uint64_t kingMask = (b << ((r << 3) + c));

	this->occupied |= mask;
	
	this->black &= ~mask;
	this->black |= colorMask;

	this->king &= ~mask;
	this->king |= kingMask;
}

void Checkers::print(uint8_t indent, move_t highlightMove) const
{
	CheckerBoard board;

	// 1.) Add peices and their color
	for (uint8_t r = 0; r < 8; r++)
	{
		for (uint8_t c = 0; c < 8; c++)
		{
			board.peices[r][c] = getSpaceCharacter(r, c);

			char color = (isPieceBlack(r, c) ? Colors::BLACK : Colors::RED);
			board.peicesForeColor[r][c] = color;
		}
	}

	// 2.) Set highlighted spaces
	if (highlightMove != 0)
	{
		int fromRow = (highlightMove >> 12) & 0x0f;
		int fromCol = (highlightMove >> 8) & 0x0f;
		int toRow = (highlightMove >> 4) & 0x0f;
		int toCol = highlightMove & 0x0f;
		board.highlightedSpaces[fromRow][fromCol] = true;
		board.highlightedSpaces[toRow][toCol] = true;
	}

	// 3.) Print Board
	board.print(indent);
}

void Checkers::init()
{
	placePiece(0, 0, 1, 0);
	placePiece(0, 2, 1, 0);
	placePiece(0, 4, 1, 0);
	placePiece(0, 6, 1, 0);
	
	placePiece(1, 1, 1, 0);
	placePiece(1, 3, 1, 0);
	placePiece(1, 5, 1, 0);
	placePiece(1, 7, 1, 0);

	placePiece(2, 0, 1, 0);
	placePiece(2, 2, 1, 0);
	placePiece(2, 4, 1, 0);
	placePiece(2, 6, 1, 0);

	placePiece(5, 1, 0, 0);
	placePiece(5, 3, 0, 0);
	placePiece(5, 5, 0, 0);
	placePiece(5, 7, 0, 0);

	placePiece(6, 0, 0, 0);
	placePiece(6, 2, 0, 0);
	placePiece(6, 4, 0, 0);
	placePiece(6, 6, 0, 0);

	placePiece(7, 1, 0, 0);
	placePiece(7, 3, 0, 0);
	placePiece(7, 5, 0, 0);
	placePiece(7, 7, 0, 0);

	cout << hex  
		<< this->occupied << endl
		<< this->black << endl
		<< this->king << endl;
}

char Checkers::getSpaceCharacter(uint8_t row, uint8_t col) const
{
	uint64_t r = row;
	uint64_t c = col;

	uint64_t bitMask = (uint64_t) 1 << (r * 8 + c);

	// Is space occupied?
	uint64_t v = occupied & bitMask;
	bool equal = (v == bitMask);
	if (equal)
	{
		// Yes, but with what?
		if ((king & bitMask) == bitMask)
		{
			// Its filled with a king
			return KING_CHAR;
		}
		else
		{
			return PAWN_CHAR;
		}
	}
	else {
		// No, its empty
		return ' ';
	}

	return '!';
}
