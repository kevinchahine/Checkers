#include "CheckersSolver.h"

CheckersSolver::CheckersSolver() {}

CheckersSolver::~CheckersSolver() {}

pair<bool, Checkers::move_t>  CheckersSolver::playAsRed(CheckersEngine & game)
{
	pair<int, CheckersEngine::move_t> ret;

	ret = minimax(game, 0, false);

	return pair<bool, Checkers::move_t> (game.movePiece(ret.second), ret.second);
}

pair<bool, Checkers::move_t>  CheckersSolver::playAsBlack(CheckersEngine & game)
{
	pair<int, CheckersEngine::move_t> ret;

	ret = minimax(game, 0, true);

	return pair<bool, Checkers::move_t> (game.movePiece(ret.second), ret.second);
}

pair<int, CheckersEngine::move_t> CheckersSolver::minimax(CheckersEngine & game, int depth, bool maxPlayersMove)
{
	// Did we reach the depth limit
	if (depth >= this->depthLimit)
	{
		// return a heuristic
		int h = heuristic(game);

		return pair<int, CheckersEngine::move_t>(h, 0);
	}

	// Did we reach a terminal node
	auto s = game.status();
	switch (s)
	{
	case CheckersEngine::RED_WINS:
		return pair<int, CheckersEngine::move_t>(INT_MIN, 0);
		break;
	case CheckersEngine::BLACK_WINS:
		return pair<int, CheckersEngine::move_t>(INT_MAX, 0);
		break;
	case CheckersEngine::DRAW:
		return pair<int, CheckersEngine::move_t>(0, 0);
		break;
	}

	// Player Black (MAX)
	if (maxPlayersMove)
	{
		int bestMoveIndex = 0;
		int bestMoveValue = INT_MIN;

		vector<CheckersEngine::move_t> validMovesBlack = game.getValidMoves(true);

		pair<int, CheckersEngine::move_t> ret;

		for (int i = 0; i < validMovesBlack.size(); i++)
		{
			CheckersEngine nextState = game;
			bool jumpOccured;
			jumpOccured = nextState.movePiece(validMovesBlack[i]);

			if (jumpOccured)
				ret = minimax(nextState, depth + 1, maxPlayersMove);
			else
				ret = minimax(nextState, depth + 1, !maxPlayersMove);

			int result = ret.first;
			if (result > bestMoveValue)
			{
				bestMoveIndex = i;
				bestMoveValue = result;
			}
		}

		// Return best heuristic and move
		ret.first = bestMoveValue;
		ret.second = validMovesBlack.at(bestMoveIndex);

		return ret;
	} // -------------------- MAX -------------------------
	// Player Red (MIN)
	else
	{
		int bestMoveIndex = 0;
		int bestMoveValue = INT_MAX;

		vector<CheckersEngine::move_t> validMovesRed = game.getValidMoves(false);
		
		pair<int, CheckersEngine::move_t> ret;

		for (int i = 0; i < validMovesRed.size(); i++)
		{
			CheckersEngine nextState = game;
			bool jumpOccured;
			jumpOccured = nextState.movePiece(validMovesRed[i]);

			if (jumpOccured)
				ret = minimax(nextState, depth + 1, maxPlayersMove);
			else
				ret = minimax(nextState, depth + 1, !maxPlayersMove);

			int result = ret.first;

			if (result < bestMoveValue)
			{
				bestMoveIndex = i;
				bestMoveValue = result;
			}
		}

		// Return best heuristic and move
		ret.first = bestMoveValue;
		ret.second = validMovesRed.at(bestMoveIndex);

		return ret;
	} // -------------------- MIN -------------------------
}

int CheckersSolver::heuristic(const CheckersEngine & game) const
{
	int h = heuristic1(game);
	return h;
}

int CheckersSolver::heuristic1(const CheckersEngine & game) const
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
