#include "CheckersEngine.h"

CheckersEngine::CheckersEngine()
{
}

CheckersEngine::~CheckersEngine()
{
}

CheckersEngine::STATUS CheckersEngine::status() const
{
	int blackCount = 0;
	int redCount = 0;

	for (int r = 0; r < 8; r++)
	{
		for (int c = (r % 2); c < 8; c++)
		{
			if (isOccupied(r, c))
			{
				if (isPieceBlack(r, c))
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
		return RED_WINS;	// Red wins
	if (redCount == 0)
		return BLACK_WINS;	// Black wins
	
	return CONTINUE;		// Continueing Game

	return DRAW;			// Draw
}

vector<CheckersEngine::move_t> CheckersEngine::getPossibleMoves(bool playerIsBlack) const
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
			// Is this space occupied by the correct color Piece?
			if (!isOccupied(fromRow, fromCol) ||
				(isPieceBlack(fromRow, fromCol) != playerIsBlack))
				continue;	// No, Skip this space

			// UP RIGHT
			if (isMoveUpRightPossible(fromRow, fromCol))
			{
				toRow = fromRow - 1;
				toCol = fromCol + 1;
				
				move =
					(fromRow << 12) |
					(fromCol << 8) |
					(toRow << 4) |
					(toCol);

				possibleMoves.push_back(move);
			}
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
			// UP LEFT
			if (isMoveUpLeftPossible(fromRow, fromCol))
			{
				toRow = fromRow - 1;
				toCol = fromCol - 1;

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
			// DOWN LEFT
			if (isMoveDownLeftPossible(fromRow, fromCol))
			{
				toRow = fromRow + 1;
				toCol = fromCol - 1;

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
			// DOWN RIGHT
			if (isMoveDownRightPossible(fromRow, fromCol))
			{
				toRow = fromRow + 1;
				toCol = fromCol + 1;

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
			
		} // end for (int c = 
	} // end for (int r = 0

	possibleMoves.shrink_to_fit();
	return possibleMoves;
}

void CheckersEngine::movePiece(int fromRow, int fromCol, int toRow, int toCol)
{
	Checkers::movePiece(fromRow, fromCol, toRow, toCol);

	//// Was there a jump (Jumps only occure if moving 2 spaces)
	//int temp = abs(fromRow - toRow);
	//if (temp == 2)
	//{
	//	// Jump occured

	//	// Which piece was jumped
	//	int jumpedRow = (fromRow + toRow) >> 1;
	//	int jumpedCol = (fromCol + toCol) >> 1;

	//	// Take that piece
	//	removePiece(jumpedRow, jumpedCol);
	//}
	//
	//// Was there a promotion?
	//// Black starts at rows 0, 1 and 2
	//// Red starts at rows 5, 6 and 7
	//// Is piece Black?
	//if (isPieceBlack(fromRow, fromCol))
	//{
	//	// Yes its Black. Now did it reach the end zone?
	//	if (toRow == 7)
	//	{
	//		// Yes, Black piece becomes a King
	//		placePiece(toRow, toCol, false, true);
	//	}
	//	else
	//		placePiece(toRow, toCol, false, false);
	//}
	//else
	//{
	//	// Then piece must be Red. Did it reach the end zone
	//	if (toRow == 0)
	//	{
	//		// Yes, Red piece becomes a King
	//		placePiece(toRow, toCol, true, true);
	//	}
	//	else
	//		placePiece(toRow, toCol, true, false);
	//}

	//// Remove piece from [fromRow][fromCol]
	//removePiece(fromRow, fromCol);
}

bool CheckersEngine::isMoveUpRightPossible(int r, int c) const
{
	bool isBlack = isPieceBlack(r, c);
	bool isPawn = !isKing(r, c);

	// Black pawns can't move up
	if (isBlack && isPawn)	return false;

	return isMoveXYPossible(r, c, r - 1, c + 1);
}

bool CheckersEngine::isMoveUpLeftPossible(int r, int c) const
{
	bool isBlack = isPieceBlack(r, c);
	bool isPawn = !isKing(r, c);

	// Black pawns can't move up
	if (isBlack && isPawn)	return false;

	return isMoveXYPossible(r, c, r - 1, c - 1);
}

bool CheckersEngine::isMoveDownLeftPossible(int r, int c) const
{
	bool isRed = isPieceRed(r, c);
	bool isPawn = !isKing(r, c);

	// Red pawns can't move down
	if (isRed && isPawn)	return false; 
	
	return isMoveXYPossible(r, c, r + 1, c - 1);
}

bool CheckersEngine::isMoveDownRightPossible(int r, int c) const
{
	bool isRed = isPieceRed(r, c);
	bool isPawn = !isKing(r, c);

	// Red pawns can't move down
	if (isRed && isPawn)	return false;

	return isMoveXYPossible(r, c, r + 1, c + 1);
}

bool CheckersEngine::isMoveXYPossible(int fromRow, int fromCol, int toRow, int toCol) const
{
	if (toRow < 0) return false;
	if (toRow > 7) return false;
	if (toCol < 0) return false;
	if (toCol > 7) return false;
	
	return !isOccupied(toRow, toCol);
}

bool CheckersEngine::isJumpUpRightPossible(int r, int c) const
{
	bool imBlack = isPieceBlack(r, c);

	int r1 = r - 1;
	int r2 = r - 2;
	int c1 = c + 1;
	int c2 = c + 2;

	return isJumpXYPossible(r1, r2, c1, c2, imBlack);
}

bool CheckersEngine::isJumpUpLeftPossible(int r, int c) const
{
	bool imBlack = isPieceBlack(r, c);

	int r1 = r - 1;
	int r2 = r - 2;
	int c1 = c - 1;
	int c2 = c - 2;

	return isJumpXYPossible(r1, r2, c1, c2, imBlack);
}

bool CheckersEngine::isJumpDownLeftPossible(int r, int c) const
{
	bool imBlack = isPieceBlack(r, c);

	int r1 = r + 1;
	int r2 = r + 2;
	int c1 = c - 1;
	int c2 = c - 2;

	return isJumpXYPossible(r1, r2, c1, c2, imBlack);
}

bool CheckersEngine::isJumpDownRightPossible(int r, int c) const
{
	bool imBlack = isPieceBlack(r, c);

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
	if (r2 > 7) return false;
	if (c2 < 0) return false;
	if (c2 > 7)	return false;

	// Is there something to jump over
	if (isOccupied(r1, c1))
	{
		// Is jump space an opponent
		if (isPieceBlack(r1, c1) != imBlack)
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
