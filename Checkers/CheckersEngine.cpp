#include "CheckersEngine.h"

#pragma region Constructors

CheckersEngine::CheckersEngine()
{
}

CheckersEngine::CheckersEngine(const CheckersEngine & game) :
	Checkers(game.occupied, game.black, game.king)
{
}

CheckersEngine::~CheckersEngine()
{
}

#pragma endregion

#pragma region Public Functions

Checkers::STATUS CheckersEngine::status() const
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

	// Who wins
	if (nMovesSinceLastTakeOrPromotion >= 40)
		return DRAW;

	if (blackCount == 0)
		return RED_WINS;
	if (redCount == 0)
		return BLACK_WINS;
	
	size_t nValidMovesRed = getValidMoves(false).size();
	size_t nValidMovesBlack = getValidMoves(true).size();

	if (nValidMovesRed == 0 && nValidMovesBlack == 0)
		return DRAW;
	if (nValidMovesRed == 0)
		return BLACK_WINS;
	if (nValidMovesBlack == 0)
		return RED_WINS;

	return CONTINUE;
}

vector<move_t> CheckersEngine::getValidMoves(bool playerIsBlack) const
{
	vector<move_t> validMoves;
	validMoves.reserve(12 * 4);

	uint16_t move = 0;

	int toRow = 0;
	int toCol = 0;

	for (int fromRow = 0; fromRow < 8; fromRow++)
	{
		for (int fromCol = (fromRow % 2); fromCol < 8; fromCol++)
		{
			// Is this space occupied and by the correct color Piece?
			if (!isOccupied(fromRow, fromCol) ||
				(isPieceBlack(fromRow, fromCol) != playerIsBlack))
				continue;	// No, Skip this space

			// UP RIGHT
			if (isMoveUpRightValid(fromRow, fromCol))
			{
				toRow = fromRow - 1;
				toCol = fromCol + 1;
				
				move =
					(fromRow << 12) |
					(fromCol << 8) |
					(toRow << 4) |
					(toCol);

				validMoves.push_back(move);
			}
			if (isJumpUpRightValid(fromRow, fromCol))
			{
				toRow = fromRow - 2;
				toCol = fromCol + 2;

				move =
					(fromRow << 12) |
					(fromCol << 8) |
					(toRow << 4) |
					(toCol);

				validMoves.push_back(move);
			}
			// UP LEFT
			if (isMoveUpLeftValid(fromRow, fromCol))
			{
				toRow = fromRow - 1;
				toCol = fromCol - 1;

				move =
					(fromRow << 12) |
					(fromCol << 8) |
					(toRow << 4) |
					(toCol);

				validMoves.push_back(move);
			}
			if (isJumpUpLeftValid(fromRow, fromCol))
			{
				toRow = fromRow - 2;
				toCol = fromCol - 2;

				move =
					(fromRow << 12) |
					(fromCol << 8) |
					(toRow << 4) |
					(toCol);

				validMoves.push_back(move);
			}
			// DOWN LEFT
			if (isMoveDownLeftValid(fromRow, fromCol))
			{
				toRow = fromRow + 1;
				toCol = fromCol - 1;

				move =
					(fromRow << 12) |
					(fromCol << 8) |
					(toRow << 4) |
					(toCol);

				validMoves.push_back(move);
			}
			if (isJumpDownLeftValid(fromRow, fromCol))
			{
				toRow = fromRow + 2;
				toCol = fromCol - 2;

				move =
					(fromRow << 12) |
					(fromCol << 8) |
					(toRow << 4) |
					(toCol);

				validMoves.push_back(move);
			}
			// DOWN RIGHT
			if (isMoveDownRightValid(fromRow, fromCol))
			{
				toRow = fromRow + 1;
				toCol = fromCol + 1;

				move =
					(fromRow << 12) |
					(fromCol << 8) |
					(toRow << 4) |
					(toCol);

				validMoves.push_back(move);
			}
			if (isJumpDownRightValid(fromRow, fromCol))
			{
				toRow = fromRow + 2;
				toCol = fromCol + 2;

				move =
					(fromRow << 12) |
					(fromCol << 8) |
					(toRow << 4) |
					(toCol);

				validMoves.push_back(move);
			}
		} // end for (int c = 
	} // end for (int r = 0

	validMoves.shrink_to_fit();
	return validMoves;
}

bool CheckersEngine::movePiece(int fromRow, int fromCol, int toRow, int toCol)
{
	bool pieceIsBlack = isPieceBlack(fromRow, fromCol);
	bool pieceIsKing = isKing(fromRow, fromCol);
	bool jumpOccurred = false;

	Checkers::movePiece(fromRow, fromCol, toRow, toCol);

	// Was there a jump (Jumps only occure if moving 2 spaces)?
	int temp = abs(fromRow - toRow);
	if (temp == 2)
	{
		// Jump occured
		jumpOccurred = true;

		// Which piece was jumped
		int jumpedRow = (fromRow + toRow) >> 1;
		int jumpedCol = (fromCol + toCol) >> 1;

		// Remove that piece
		removePiece(jumpedRow, jumpedCol);

		nMovesSinceLastTakeOrPromotion = 0;
	}
	
	// Was there a promotion?
	// Black starts at rows 0, 1 and 2
	// Red starts at rows 5, 6 and 7
	// Is piece Black?
	if (pieceIsBlack == true)
	{
		if (pieceIsKing == false)
		{
			// Yes. Did it reach the end zone?
			if (toRow == 7)
			{
				// Yes, Black piece becomes a King.
				placePiece(toRow, toCol, false, true);
				// If Piece was already a BLACK king it will still work.

				nMovesSinceLastTakeOrPromotion = 0;
			}
		}
	}
	else
	{
		if (pieceIsKing == false)
		{// Then piece must be Red. Did it reach the end zone?
			if (toRow == 0)
			{
				// Yes. Red piece becomes a King.
				placePiece(toRow, toCol, true, true);
				// If Piece was already a RED king it will still work.

				nMovesSinceLastTakeOrPromotion = 0;
			}
		}
	}

	nMovesSinceLastTakeOrPromotion++;
	
	return jumpOccurred;
}

bool CheckersEngine::movePiece(move_t move)
{
	int fromRow = (move >> 12) & 0x0f;
	int fromCol = (move >> 8) & 0x0f;
	int toRow = (move >> 4) & 0x0f;
	int toCol = move & 0x0f;
	
	return movePiece(fromRow, fromCol, toRow, toCol);
}

#pragma endregion

#pragma region Move Validation Functions

bool CheckersEngine::isMoveUpRightValid(int r, int c) const
{
	bool isBlack = isPieceBlack(r, c);
	bool isPawn = !isKing(r, c);

	// Black pawns can't move up
	if (isBlack && isPawn)	return false;

	return isMoveXYValid(r, c, r - 1, c + 1);
}

bool CheckersEngine::isMoveUpLeftValid(int r, int c) const
{
	bool isBlack = isPieceBlack(r, c);
	bool isPawn = !isKing(r, c);

	// Black pawns can't move up
	if (isBlack && isPawn)	return false;

	return isMoveXYValid(r, c, r - 1, c - 1);
}

bool CheckersEngine::isMoveDownLeftValid(int r, int c) const
{
	bool isRed = isPieceRed(r, c);
	bool isPawn = !isKing(r, c);

	// Red pawns can't move down
	if (isRed && isPawn)	return false; 
	
	return isMoveXYValid(r, c, r + 1, c - 1);
}

bool CheckersEngine::isMoveDownRightValid(int r, int c) const
{
	bool isRed = isPieceRed(r, c);
	bool isPawn = !isKing(r, c);

	// Red pawns can't move down
	if (isRed && isPawn)	return false;

	return isMoveXYValid(r, c, r + 1, c + 1);
}

bool CheckersEngine::isMoveXYValid(int fromRow, int fromCol, int toRow, int toCol) const
{
	if (toRow < 0) return false;
	if (toRow > 7) return false;
	if (toCol < 0) return false;
	if (toCol > 7) return false;
	
	return !isOccupied(toRow, toCol);
}

bool CheckersEngine::isJumpUpRightValid(int r, int c) const
{
	bool imBlack = isPieceBlack(r, c);
	bool isPawn = !isKing(r, c);

	// Black pawns can't move down
	if (imBlack && isPawn)	return false;

	int r1 = r - 1;
	int r2 = r - 2;
	int c1 = c + 1;
	int c2 = c + 2;

	return isJumpXYValid(r1, r2, c1, c2, imBlack);
}

bool CheckersEngine::isJumpUpLeftValid(int r, int c) const
{
	bool imBlack = isPieceBlack(r, c);
	bool isPawn = !isKing(r, c);

	// Black pawns can't move down
	if (imBlack && isPawn)	return false;

	int r1 = r - 1;
	int r2 = r - 2;
	int c1 = c - 1;
	int c2 = c - 2;

	return isJumpXYValid(r1, r2, c1, c2, imBlack);
}

bool CheckersEngine::isJumpDownLeftValid(int r, int c) const
{
	bool imBlack = isPieceBlack(r, c);
	bool isPawn = !isKing(r, c);

	// Red pawns can't move down
	if (!imBlack && isPawn)	return false;
	
	int r1 = r + 1;
	int r2 = r + 2;
	int c1 = c - 1;
	int c2 = c - 2;

	return isJumpXYValid(r1, r2, c1, c2, imBlack);
}

bool CheckersEngine::isJumpDownRightValid(int r, int c) const
{
	bool imBlack = isPieceBlack(r, c);
	bool isPawn = !isKing(r, c);

	// Red pawns can't move down
	if (!imBlack && isPawn)	return false;
	
	int r1 = r + 1;
	int r2 = r + 2;
	int c1 = c + 1;
	int c2 = c + 2;

	return isJumpXYValid(r1, r2, c1, c2, imBlack);
}

bool CheckersEngine::isJumpXYValid(int r1, int r2, int c1, int c2, bool imBlack) const
{
	// Bounds checking
	if (r2 < 0)	return false;
	if (r2 > 7) return false;
	if (c2 < 0) return false;
	if (c2 > 7)	return false;

	// Is there something to jump over
	if (isOccupied(r1, c1))
	{
		// Is jump space occupied by an opponent
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

#pragma endregion
