#include "Solver0.h"

Solver0::Solver0()
{
}

Solver0::~Solver0()
{
}

stringstream Solver0::toStream() const
{
	return stringstream();
}

int Solver0::calcHeuristic(const CheckersEngine & game) const
{
	int h = 0;

	for (int r = 0; r < 8; r++)
	{
		for (int c = (r % 2); c < 8; c += 2)
		{
			// Is Space Occupied?
			if (game.isOccupied(r, c))
			{
				// Yes. By a black or red piece?
				if (game.isPieceBlack(r, c))
				{
					// Black. Is it a King or Pawn?
					if (game.isKing(r, c))
					{
						// King
						h += 3;
					}
					else
					{
						// Pawn
						h += 1;
					}
				}
				else
				{
					// Red. Is it a King or Pawn?
					if (game.isKing(r, c))
					{
						// King
						h -= 3;
					}
					else
					{
						// Pawn
						h -= 1;
					}
				}
			}
		}
	}

	return h;
}

int Solver0::heuristic2(const CheckersEngine & game) const
{
	int h = 0;

	for (int r = 0; r < 8; r++)
	{
		for (int c = (r % 2); c < 8; c += 2)
		{
			// Is Space Occupied?
			if (game.isOccupied(r, c))
			{
				bool pieceIsBlack = game.isPieceBlack(r, c);

				int pieceHeuristic = 0;

				// Black. Is it a King or Pawn?
				if (game.isKing(r, c))
				{
					// King
					pieceHeuristic += 30;
				}
				else
				{
					// Pawn
					pieceHeuristic += 10;

					// How far up is it?
					pieceHeuristic += (pieceIsBlack ? r : r - 7);
				}

				// Can the peice capture another piece?
				pieceHeuristic += 2 * game.isJumpUpRightValid(r, c);
				pieceHeuristic += 2 * game.isJumpUpLeftValid(r, c);
				pieceHeuristic += 2 * game.isJumpDownLeftValid(r, c);
				pieceHeuristic += 2 * game.isJumpDownRightValid(r, c);

				// Where can the piece move?
				pieceHeuristic += game.isMoveUpRightValid(r, c);
				pieceHeuristic += game.isMoveUpLeftValid(r, c);
				pieceHeuristic += game.isMoveDownLeftValid(r, c);
				pieceHeuristic += game.isMoveDownRightValid(r, c);

				// Add to the total heuristic
				h += (pieceIsBlack ? pieceHeuristic : -pieceHeuristic);
			}
		}
	}

	return h;
}
