#include "Checkers.h"

Checkers::Checkers() :
	occupied(0xaa55aa000055aa55),
	red(0xffffffffaa000000),
	king(0x0)
{
	//init();
}

Checkers::Checkers(const Checkers & game) :
	occupied(game.occupied),
	red(game.red),
	king(game.king)
{
}

Checkers::Checkers(const Checkers && game) :
	occupied(game.occupied),
	red(game.red),
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
	return (red & mask) == mask;
}

bool Checkers::isPieceBlack(uint8_t row, uint8_t col) const
{
	uint64_t mask = ((uint64_t) 1 << ((row * 8) + col));
	return (red & mask) != mask;
}

bool Checkers::isKing(uint8_t row, uint8_t col) const
{
	uint64_t mask = ((uint64_t)1 << ((row << 3) + col));
	return (king & mask) == mask;
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
	b = (this->red & fromMask);

	// 2.) Set piece color at [toRow, toCol]
	this->red &= ~toMask;						// Clear to bit
	b = (b == fromMask ? toMask : (uint64_t) 0);// Is piece red?
	this->red |= b;								// Set to bit

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

void Checkers::placePiece(uint8_t row, uint8_t col, bool color, bool king)
{
	uint64_t r = row;
	uint64_t c = col;
	uint64_t b;
	
	uint64_t mask = (uint64_t) 1 << ((r << 3) + c);
	
	b = (color ? (uint64_t)1 : (uint64_t)0);
	uint64_t colorMask = (b << ((r << 3) + c));
	
	b = (king ? (uint64_t)1 : (uint64_t)0);
	uint64_t kingMask = (b << ((r << 3) + c));

	this->occupied |= mask;
	
	this->red &= ~mask;
	this->red |= colorMask;

	this->king &= ~mask;
	this->king |= kingMask;
}

void Checkers::print(uint8_t indent) const
{
	// Take care of text color
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	// Remember the fill char (and set the new one at the same time)
	char prevFillCh = cout.fill(ASCII::lines[ASCII::HORIZONTAL_DOUBLE]);

	const size_t nRows = 8;
	const size_t nCols = 8;

	// Print Top Boarder
	cout << setfill(' ') << setw(indent) 
		<< ASCII::lines[ASCII::DOWN_DOUBLE | ASCII::RIGHT_DOUBLE]
		<< setfill(ASCII::lines[ASCII::LEFT_DOUBLE | ASCII::RIGHT_DOUBLE])
		<< setw(nCols + 3)
		<< ASCII::lines[ASCII::DOWN_DOUBLE | ASCII::LEFT_DOUBLE]
		<< endl;

	// Print top coordinates
	cout << setfill(' ') << setw(indent)
		<< ASCII::lines[ASCII::UP_DOUBLE | ASCII::DOWN_DOUBLE]
		<< char(178);

	for (uint8_t r = 0; r < nRows; r++) {
		char textColor = Colors::WHITE;
		char backColor = ((r % 2 == 1) ? Colors::LIGHTGREEN : Colors::GREEN);
		
		setColor(console, textColor + (backColor << 4));

		cout << char('A' + r);
	}

	char textColor = Colors::WHITE;
	char backColor = Colors::GREEN;

	setColor(console, textColor + (backColor << 4));
	
	cout << char(178)
		<< ASCII::lines[ASCII::UP_DOUBLE | ASCII::DOWN_DOUBLE] 
		<< endl;

	// Print MIDDLE 
	for (uint8_t r = 0; r < nRows; r++) {
		// Indent
		cout << setfill(' ') << setw(indent)
			<< ASCII::lines[ASCII::VERTICAL_DOUBLE];

		// Remember the current text color
		uint8_t prevColor;
		getColor(prevColor);

		// Print Left Coordinate
		char textColor = Colors::WHITE;
		char backColor = ((r % 2 == 1) ? Colors::LIGHTGREEN : Colors::GREEN);
		setColor(console, textColor + (backColor << 4));
		cout << (int) r;

		for (uint8_t c = 0; c < nCols; c++) {
			char textColor = (isPieceRed(r, c) ? Colors::RED : Colors::BLACK);
			char backColor = (((r + c) % 2 == 0) ? Colors::LIGHTGREEN : Colors::GREEN);

			setColor(console, textColor + (backColor << 4));
			
			cout << getSpaceCharacter(r, c);
		}

		textColor = Colors::WHITE;
		backColor = ((r % 2 == 0) ? Colors::LIGHTGREEN : Colors::GREEN);
		setColor(console, textColor + (backColor << 4));
		cout << (int)r;

		// Reassign the original text color
		setColor(console, prevColor);

		cout << ASCII::lines[ASCII::VERTICAL_DOUBLE]
			<< endl;
	}

	// Print bottom coordinates
	cout << setfill(' ') << setw(indent)
		<< ASCII::lines[ASCII::UP_DOUBLE | ASCII::DOWN_DOUBLE]
		<< char(178);

	for (uint8_t r = 0; r < nRows; r++) {
		char textColor = Colors::WHITE;
		char backColor = ((r % 2 == 0) ? Colors::LIGHTGREEN : Colors::GREEN);

		setColor(console, textColor + (backColor << 4));

		cout << char('A' + r);
	}
	
	cout << char(178)
		<< ASCII::lines[ASCII::UP_DOUBLE | ASCII::DOWN_DOUBLE] 
		<< endl;

	cout << setfill(' ')
		<< setw(indent)
		<< ASCII::lines[ASCII::UP_DOUBLE | ASCII::RIGHT_DOUBLE]
		<< setfill(ASCII::lines[ASCII::HORIZONTAL_DOUBLE])
		<< setw(nCols + 3)
		<< ASCII::lines[ASCII::UP_DOUBLE | ASCII::LEFT_DOUBLE] << endl;

	// Restore the previous fill character
	cout.fill(prevFillCh);
}

void Checkers::init()
{
	placePiece(0, 0, 0, 0);
	placePiece(0, 2, 0, 0);
	placePiece(0, 4, 0, 0);
	placePiece(0, 6, 0, 0);
	
	placePiece(1, 1, 0, 0);
	placePiece(1, 3, 0, 0);
	placePiece(1, 5, 0, 0);
	placePiece(1, 7, 0, 0);

	placePiece(2, 0, 0, 0);
	placePiece(2, 2, 0, 0);
	placePiece(2, 4, 0, 0);
	placePiece(2, 6, 0, 0);

	placePiece(5, 1, 1, 0);
	placePiece(5, 3, 1, 0);
	placePiece(5, 5, 1, 0);
	placePiece(5, 7, 1, 0);

	placePiece(6, 0, 1, 0);
	placePiece(6, 2, 1, 0);
	placePiece(6, 4, 1, 0);
	placePiece(6, 6, 1, 0);

	placePiece(7, 1, 1, 0);
	placePiece(7, 3, 1, 0);
	placePiece(7, 5, 1, 0);
	placePiece(7, 7, 1, 0);

	cout << hex  
		<< this->occupied << endl
		<< this->red << endl
		<< this->king << endl;
}

void Checkers::setColor(HANDLE console, uint8_t color) const
{
	SetConsoleTextAttribute(console, color);
}

bool Checkers::getColor(uint8_t & color) const
{
	CONSOLE_SCREEN_BUFFER_INFO info;

	if (!GetConsoleScreenBufferInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&info)) {
		return false;
	}

	color = (uint8_t) info.wAttributes;

	return true;
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
