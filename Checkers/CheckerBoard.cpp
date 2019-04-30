#include "CheckerBoard.h"

CheckerBoard::CheckerBoard() {}

CheckerBoard::~CheckerBoard() {}

void CheckerBoard::print(int indent) const
{
	// Take care of text color
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	setColor(console, (Colors::WHITE + (Colors::BLACK << 4)));
	
	for (size_t r = 0; r < N_ROWS; r++)
	{
		// 0.) Remember prev color
		uint8_t prevColor;
		getColor(prevColor);

		// 1.) Indent Board
		cout << right << setfill(' ') << setw(indent) << '\0';

		// 2.) Print row
		for (size_t c = 0; c < N_COLS; c++)
		{
			setColor(console, (foreColor[r][c] + (backColor[r][c] << 4)));

			cout << text[r][c];
		}

		// .) ENDL
		setColor(console, prevColor);
		cout << endl;
	}
}

void CheckerBoard::initBase()
{
	resetArrays();

	initBoarders();

	initCoordinates();

	initSpaces();

	placePieces();
}

void CheckerBoard::resetArrays()
{
	for (size_t r = 0; r < 8; r++)
	{
		for (size_t c = 0; c < 8; c++)
		{
			peices[r][c] = ' ';
			peicesForeColor[r][c] = Colors::WHITE;
		}
	}

	for (size_t r = 0; r < N_ROWS; r++)
	{
		for (size_t c = 0; c < N_COLS; c++)
		{
			text[r][c] = ' ';
			foreColor[r][c] = Colors::WHITE;
			backColor[r][c] = Colors::BLACK;
		}
	}
}

void CheckerBoard::initBoarders()
{
	size_t r, c;
	char temp;
	char tempForeColor = lightColor;
	char tempBackColor = darkColor;

	// Top Bottom Borders
	temp = ASCII::lines[ASCII::HORIZONTAL_DOUBLE];
	for (c = 0; c < N_COLS; c++)
	{
		text[0][c] = temp;
		foreColor[0][c] = tempForeColor;
		backColor[0][c] = tempBackColor;

		text[N_ROWS - 1][c] = temp;
		foreColor[N_ROWS - 1][c] = tempForeColor;
		backColor[N_ROWS - 1][c] = tempBackColor;
	}

	// Left and Right Borders
	temp = ASCII::lines[ASCII::VERTICAL_DOUBLE];
	for (r = 0; r < N_ROWS; r++)
	{
		text[r][0] = temp;
		foreColor[r][0] = tempForeColor;
		backColor[r][0] = tempBackColor;

		text[r][N_COLS - 1] = temp;
		foreColor[r][N_COLS - 1] = tempForeColor;
		backColor[r][N_COLS - 1] = tempBackColor;
	}

	// Corners
	text[0][0] = ASCII::lines[ASCII::RIGHT_DOUBLE | ASCII::DOWN_DOUBLE];
	foreColor[0][0] = tempForeColor;
	backColor[0][0] = tempBackColor;
	
	text[0][N_COLS - 1] = ASCII::lines[ASCII::LEFT_DOUBLE | ASCII::DOWN_DOUBLE];
	foreColor[0][N_COLS - 1] = tempForeColor;
	backColor[r][N_COLS - 1] = tempBackColor; 
	
	text[N_ROWS - 1][0] = ASCII::lines[ASCII::UP_DOUBLE | ASCII::RIGHT_DOUBLE];
	foreColor[N_ROWS - 1][0] = tempForeColor;
	backColor[N_ROWS - 1][0] = tempBackColor;
	
	text[N_ROWS - 1][N_COLS - 1] = ASCII::lines[ASCII::UP_DOUBLE | ASCII::LEFT_DOUBLE];
	foreColor[N_ROWS - 1][N_COLS - 1]  = tempForeColor;
	backColor[N_ROWS - 1][N_COLS - 1] = tempBackColor;
}

void CheckerBoard::initCoordinates()
{
	// Top Bottom Coordinates
	for (size_t spaceCol = 0; spaceCol < 8; spaceCol++)
	{
		const char TEMP_BACK_COLOR_TOP =
			((spaceCol) % 2) ? lightColor : darkColor;
		const char TEMP_BACK_COLOR_BOTTOM = 
			((spaceCol) % 2) ? darkColor : lightColor;
		
		const size_t CHAR_COL = 2 + spaceCol * SPACE_WIDTH + SPACE_WIDTH / 2;

		text[1][CHAR_COL] = 'A' + spaceCol;
		text[N_ROWS - VERTICAL_OFFSET][CHAR_COL] = 'A' + spaceCol;

		for (size_t c = 0; c < SPACE_WIDTH; c++)
		{
			const size_t ROW = 1;
			const size_t COL =
				2 +
				spaceCol * SPACE_WIDTH +
				c;

			backColor[ROW][COL] = TEMP_BACK_COLOR_TOP;
			backColor[N_ROWS - VERTICAL_OFFSET][COL] = TEMP_BACK_COLOR_BOTTOM;
		}
	}
	
	// LEFT AND RIGHT Coordinates
	for (size_t spaceRow = 0; spaceRow < 8; spaceRow++)
	{
		const char TEMP_BACK_COLOR_TOP =
			((spaceRow) % 2) ? lightColor : darkColor;
		const char TEMP_BACK_COLOR_BOTTOM =
			((spaceRow) % 2) ? darkColor : lightColor;
		
		const size_t CHAR_ROW = 2 + spaceRow * SPACE_HEIGHT + SPACE_HEIGHT / 2;

		text[CHAR_ROW][HORIZONTAL_OFFSET - 1] = '0' + (spaceRow + 1);
		text[CHAR_ROW][N_COLS - HORIZONTAL_OFFSET] = '0' + (spaceRow + 1);
		
		for (size_t r = 0; r < SPACE_HEIGHT; r++)
		{
			const size_t ROW = 
				VERTICAL_OFFSET +
				spaceRow * SPACE_HEIGHT +
				r;

			const size_t COL = 1;

			backColor[ROW][COL] = TEMP_BACK_COLOR_TOP;
			backColor[ROW][N_COLS - HORIZONTAL_OFFSET] = TEMP_BACK_COLOR_BOTTOM;
		}
	}
}

void CheckerBoard::initSpaces()
{
	for (size_t spaceRow = 0; spaceRow < 8; spaceRow++)
	{
		for (size_t spaceCol = 0; spaceCol < 8; spaceCol++)
		{
			const char TEMP_BACK_COLOR = 
				((spaceRow + spaceCol) % 2) ? darkColor : lightColor;

			for (size_t r = 0; r < SPACE_HEIGHT; r++)
			{
				for (size_t c = 0; c < SPACE_WIDTH; c++)
				{
					const size_t ROW =
						VERTICAL_OFFSET +
						spaceRow * SPACE_HEIGHT +
						r;

					const size_t COL =
						HORIZONTAL_OFFSET +
						spaceCol * SPACE_WIDTH +
						c;

					backColor[ROW][COL] = TEMP_BACK_COLOR;
				} // end for (size_t c = 0
			} // end for (size_t r = 0
		} // end for (size_t spaceCol = 0
	} // end for (size_t spaceRow = 0
}

void CheckerBoard::placePieces()
{
	for (size_t spaceRow = 0; spaceRow < 8; spaceRow++)
	{
		for (size_t spaceCol = 0; spaceCol < 8; spaceCol++)
		{
			const size_t ROW =
				VERTICAL_OFFSET +
				spaceRow * SPACE_HEIGHT +
				SPACE_HEIGHT / 2;

			const size_t COL =
				HORIZONTAL_OFFSET +
				spaceCol * SPACE_WIDTH +
				SPACE_WIDTH / 2;

			text[ROW][COL] = peices[spaceRow][spaceCol];
			foreColor[ROW][COL] = peicesForeColor[spaceRow][spaceCol];
		} // end for (size_t spaceCol = 0
	} // end for (size_t spaceRow = 0
}

void CheckerBoard::setColor(HANDLE console, uint8_t color) const
{
	SetConsoleTextAttribute(console, color);
}

bool CheckerBoard::getColor(uint8_t & color) const
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


