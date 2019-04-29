#include "CheckersEngine.h"

CheckersEngine::CheckersEngine()
{
}

CheckersEngine::~CheckersEngine()
{
}

int CheckersEngine::status() const
{
	int blackCount = 0;
	int redCount = 0;

	for (int r = 0; r < 8; r++)
	{
		for (int c = (r % 2); c < 8; c++)
		{
			if (isOccupied(r, c))
			{
				if (isPeiceBlack(r, c))
				{
					blackCount++;
				}
				else
				{
					redCount++;
				}
			}
		}
	}

	if (blackCount == 0)
		return -1;	// red wins
	if (redCount == 0)
		return 1;	// black wins
	return 0;	// Continueing Game

	return 2;	// Draw
}

vector<CheckersEngine::move_t> CheckersEngine::possibleMovesBlack() const
{
	vector<move_t> possibleMoves;
	possibleMoves.reserve(12 * 4);

	uint16_t move = 0;

	int toRow = 0;
	int toCol = 0;

	for (int fromRow = 0; fromRow < 8; fromRow++)
	{
		for (int fromCol = (fromRow % 2); fromCol < 8; fromCol++)
		{
			// Is this space occupied by a Black Peice?
			if (isOccupied(fromRow, fromCol) && isPeiceBlack(fromRow, fromCol))
				;
			else
				continue;

			// Can we move UP?
			toRow = fromRow - 1;
			if (toRow > 0)
			{
				// Can we move LEFT?
				toCol = fromCol - 1;
				if (toCol > 0)
				{
					if (!isOccupied(toRow, toCol))
					{
						move =
							(fromRow << 12) |
							(fromCol << 8) |
							(toRow << 4) |
							(toCol);

						possibleMoves.push_back(move);
					}
				}

				// Can we move RIGHT?
				toCol = fromCol + 1;
				if (toCol < 8)
				{
					if (!isOccupied(toRow, toCol))
					{
						move =
							(fromRow << 12) |
							(fromCol << 8) |
							(toRow << 4) |
							(toCol);

						possibleMoves.push_back(move);
					}
				}
			}

			// Can we move DOWN?
			if (fromRow + 1 > 0)
			{
				// Can we move LEFT?
				toCol = fromCol - 1;
				if (toCol > 0)
				{
					if (!isOccupied(toRow, toCol))
					{
						move =
							(fromRow << 12) |
							(fromCol << 8) |
							(toRow << 4) |
							(toCol);

						possibleMoves.push_back(move);
					}
				}

				// Can we move RIGHT?
				toCol = fromCol + 1;
				if (toCol < 8)
				{
					if (!isOccupied(toRow, toCol))
					{
						move =
							(fromRow << 12) |
							(fromCol << 8) |
							(toRow << 4) |
							(toCol);

						possibleMoves.push_back(move);
					}
				}
			}

			// Which Jumps are possible
			if (isJumpUpRightPossible(fromRow, fromCol))
			{
				toRow = fromRow - 2;
				toCol = fromCol + 2;
				move =
					(fromRow << 12) |
					(fromCol << 8) |
					(toRow << 4) |
					(toCol);

				possibleMoves.push_back(move);
			}
			if (isJumpUpLeftPossible(fromRow, fromCol)) 
			{
				toRow = fromRow - 2;
				toCol = fromCol - 2;
				move =
					(fromRow << 12) |
					(fromCol << 8) |
					(toRow << 4) |
					(toCol);

				possibleMoves.push_back(move);
			}
			if (isJumpDownLeftPossible(fromRow, fromCol)) 
			{
				toRow = fromRow + 2;
				toCol = fromCol - 2;
				move =
					(fromRow << 12) |
					(fromCol << 8) |
					(toRow << 4) |
					(toCol);

				possibleMoves.push_back(move);
			}
			if (isJumpDownRightPossible(fromRow, fromCol)) 
			{
				toRow = fromRow + 2;
				toCol = fromCol + 2;
				move =
					(fromRow << 12) |
					(fromCol << 8) |
					(toRow << 4) |
					(toCol);

				possibleMoves.push_back(move);
			}
		}
	}

	return possibleMoves;
}

vector<CheckersEngine::move_t> CheckersEngine::possibleMovesRed() const
{
	return vector<move_t>();
}

bool CheckersEngine::isJumpUpRightPossible(int r, int c) const
{
	bool imBlack = isPeiceBlack(r, c);

	int r1 = r - 1;
	int r2 = r - 2;
	int c1 = c + 1;
	int c2 = c + 2;

	return isJumpXYPossible(r1, r2, c1, c2, imBlack);
}

bool CheckersEngine::isJumpUpLeftPossible(int r, int c) const
{
	bool imBlack = isPeiceBlack(r, c);

	int r1 = r - 1;
	int r2 = r - 2;
	int c1 = c - 1;
	int c2 = c - 2;

	return isJumpXYPossible(r1, r2, c1, c2, imBlack);
}

bool CheckersEngine::isJumpDownLeftPossible(int r, int c) const
{
	bool imBlack = isPeiceBlack(r, c);

	int r1 = r + 1;
	int r2 = r + 2;
	int c1 = c - 1;
	int c2 = c - 2;

	return isJumpXYPossible(r1, r2, c1, c2, imBlack);
}

bool CheckersEngine::isJumpDownRightPossible(int r, int c) const
{
	bool imBlack = isPeiceBlack(r, c);

	int r1 = r + 1;
	int r2 = r + 2;
	int c1 = c - 1;
	int c2 = c - 2;

	return isJumpXYPossible(r1, r2, c1, c2, imBlack);
}

bool CheckersEngine::isJumpXYPossible(int r1, int r2, int c1, int c2, bool imBlack) const
{
	// Bounds checking
	if (r2 < 0)	return false;
	if (c2 > 7)	return false;

	// Is there something to jump over
	if (isOccupied(r1, c1))
	{
		// Is jump space an opponent
		if (isPeiceBlack(r1, c1) != imBlack)
		{
			// Is landing space empty
			if (!isOccupied(r2, c2))
			{
				return true;
			}
		}
	}

	return false;
}
