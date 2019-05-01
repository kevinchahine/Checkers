#include "CheckerBoard.h"

CheckerBoard::CheckerBoard() {}

CheckerBoard::~CheckerBoard() {}

void CheckerBoard::print(int indent)
{
	initBase();
	
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	Console::setColor(console, Colors::WHITE, Colors::BLACK);

	for (size_t r = 0; r < N_ROWS; r++)
	{
		// 0.) Remember prev color
		uint8_t prevColor;
		Console::getColor(prevColor);

		// 1.) Indent Board
		cout << right << setfill(' ') << setw(indent) << '\0';

		// 2.) Print row
		for (size_t c = 0; c < N_COLS; c++)
		{
			Console::setColor(console, foreColor[r][c], backColor[r][c]);

			cout << text[r][c];
		}

		// 3.) ENDL
		Console::setColor(console, prevColor);
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
	char tempForeColor = LIGHT_COLOR;
	char tempBackColor = DARK_COLOR;

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
			((spaceCol) % 2) ? LIGHT_COLOR : DARK_COLOR;
		const char TEMP_BACK_COLOR_BOTTOM = 
			((spaceCol) % 2) ? DARK_COLOR : LIGHT_COLOR;
		
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
			((spaceRow) % 2) ? LIGHT_COLOR : DARK_COLOR;
		const char TEMP_BACK_COLOR_BOTTOM =
			((spaceRow) % 2) ? DARK_COLOR : LIGHT_COLOR;
		
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
			char tempBackColor;

			// Do we need to highlight the space?
			if (highlightedSpaces[spaceRow][spaceCol] == true)
			{
				// Yes, highlight the space
				tempBackColor =	((spaceRow + spaceCol) % 2) ? 
					DARK_HIGHLIGHT : LIGHT_HIGHLIGHT;
			}
			else {
				// No, Don't highlight the space
				tempBackColor = ((spaceRow + spaceCol) % 2) ? 
					DARK_COLOR : LIGHT_COLOR;
			}

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

					backColor[ROW][COL] = tempBackColor;
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

