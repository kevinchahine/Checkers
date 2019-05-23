#include "CheckerBoard.h"

CheckerBoard::CheckerBoard() :
	boardView(N_ROWS, N_COLS) {}

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
			Console::setColor(console, boardView.colorText[r][c].first);
			
			cout << boardView.colorText[r][c].second;
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
			boardView.colorText[r][c].second = ' ';
			boardView.colorText[r][c].first = Colors::combine(Colors::WHITE, Colors::BLACK);
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
		boardView.colorText[0][c].second = temp;
		boardView.colorText[0][c].first = 
			Colors::combine(tempForeColor, tempBackColor);

		boardView.colorText[N_ROWS - 1][c].second = temp;
		boardView.colorText[N_ROWS - 1][c].first =
			Colors::combine(tempForeColor, tempBackColor);
	}

	// Left and Right Borders
	temp = ASCII::lines[ASCII::VERTICAL_DOUBLE];
	for (r = 0; r < N_ROWS; r++)
	{
		boardView.colorText[r][0].second = temp;
		boardView.colorText[r][0].first =
			Colors::combine(tempForeColor, tempBackColor);

		boardView.colorText[r][N_COLS - 1].second = temp;
		boardView.colorText[r][N_COLS - 1].first =
			Colors::combine(tempForeColor, tempBackColor);
	}

	// Corners
	boardView.colorText[0][0].second = 
		ASCII::lines[ASCII::RIGHT_DOUBLE | ASCII::DOWN_DOUBLE];;
	boardView.colorText[0][0].first =
		Colors::combine(tempForeColor, tempBackColor);

	boardView.colorText[0][N_COLS - 1].second = 
		ASCII::lines[ASCII::LEFT_DOUBLE | ASCII::DOWN_DOUBLE];
	boardView.colorText[0][N_COLS - 1].first =
		Colors::combine(tempForeColor, tempBackColor);
	
	boardView.colorText[N_ROWS - 1][0].second = 
		ASCII::lines[ASCII::UP_DOUBLE | ASCII::RIGHT_DOUBLE];
	boardView.colorText[N_ROWS - 1][0].first = 
		Colors::combine(tempForeColor, tempBackColor);

	boardView.colorText[N_ROWS - 1][N_COLS - 1].second =
		ASCII::lines[ASCII::UP_DOUBLE | ASCII::LEFT_DOUBLE];
	boardView.colorText[N_ROWS - 1][N_COLS - 1].first =
		Colors::combine(tempForeColor, tempBackColor);
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

		boardView.colorText[1][CHAR_COL].second = 'A' + spaceCol;
		boardView.colorText[N_ROWS - VERTICAL_OFFSET][CHAR_COL].second = 'A' + spaceCol;

		for (size_t c = 0; c < SPACE_WIDTH; c++)
		{
			const size_t ROW = 1;
			const size_t COL =
				2 +
				spaceCol * SPACE_WIDTH +
				c;

			char tempColor;
			tempColor = boardView.colorText[ROW][COL].first;
			tempColor = Colors::combine(Colors::foreColor(tempColor), TEMP_BACK_COLOR_TOP);
			boardView.colorText[ROW][COL].first = tempColor;

			tempColor = boardView.colorText[N_ROWS - VERTICAL_OFFSET][COL].first;
			tempColor = Colors::combine(Colors::foreColor(tempColor), TEMP_BACK_COLOR_BOTTOM);
			boardView.colorText[N_ROWS - VERTICAL_OFFSET][COL].first = tempColor;
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

		boardView.colorText[CHAR_ROW][HORIZONTAL_OFFSET - 1].second = '0' + (spaceRow + 1);
		boardView.colorText[CHAR_ROW][N_COLS - HORIZONTAL_OFFSET].second = '0' + (spaceRow + 1);
		
		for (size_t r = 0; r < SPACE_HEIGHT; r++)
		{
			const size_t ROW = 
				VERTICAL_OFFSET +
				spaceRow * SPACE_HEIGHT +
				r;

			const size_t COL = 1;

			char tempColor;
			tempColor = boardView.colorText[ROW][COL].first;
			tempColor = Colors::combine(Colors::foreColor(tempColor), TEMP_BACK_COLOR_TOP);
			boardView.colorText[ROW][COL].first = tempColor;

			tempColor = boardView.colorText[ROW][N_COLS - HORIZONTAL_OFFSET].first;
			tempColor = Colors::combine(Colors::foreColor(tempColor), TEMP_BACK_COLOR_BOTTOM);
			boardView.colorText[ROW][N_COLS - HORIZONTAL_OFFSET].first = tempColor;
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

					char tempColor = boardView.colorText[ROW][COL].first;
					tempColor = Colors::backColor(tempColor);
					tempColor = Colors::combine(tempColor, tempBackColor);
					boardView.colorText[ROW][COL].first = tempColor;
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

			boardView.colorText[ROW][COL].second = peices[spaceRow][spaceCol];
			char tempColor = boardView.colorText[ROW][COL].first;
			tempColor = Colors::backColor(tempColor);
			tempColor = Colors::combine(peicesForeColor[spaceRow][spaceCol], tempColor);
			boardView.colorText[ROW][COL].first = tempColor;
		} // end for (size_t spaceCol = 0
	} // end for (size_t spaceRow = 0
}

