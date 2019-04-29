#include "CheckersSolver.h"

CheckersSolver::CheckersSolver() :
	gamePtr(nullptr) {}

CheckersSolver::CheckersSolver(Checkers * gamePtr) :
	gamePtr(gamePtr) {}

CheckersSolver::~CheckersSolver() {}

void CheckersSolver::playAsRed()
{

}

int CheckersSolver::minimax(Checkers game, int depth, bool maxPlayersMove)
{
	// Did we reach the depth limit
	if (depth >= this->depthLimit)
	{
		// return a heuristic
		return heuristic1(game);
	}

	// Player Black
	if (maxPlayersMove)
	{

	}
	// Player Red
	else
	{

	}

	return 0;
}

int CheckersSolver::heuristic1(const Checkers & game) const
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
