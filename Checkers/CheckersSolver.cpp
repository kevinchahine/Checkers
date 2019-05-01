#include "CheckersSolver.h"

CheckersSolver::CheckersSolver() {}

CheckersSolver::~CheckersSolver() {}

pair<bool, move_t> CheckersSolver::playAsRed(CheckersEngine & game)
{
	pair<int, move_t> ret;

	//ret = minimax(game, 0, false);
	ret = alphabeta(game, 0, INT_MIN, INT_MAX, false);

	return pair<bool, move_t>(game.movePiece(ret.second), ret.second);
}

pair<bool, move_t> CheckersSolver::playAsBlack(CheckersEngine & game)
{
	pair<int, move_t> ret;

	//ret = minimax(game, 0, true);
	ret = alphabeta(game, 0, INT_MIN, INT_MAX, true);

	return pair<bool, move_t>(game.movePiece(ret.second), ret.second);
}

pair<int, move_t> CheckersSolver::minimax(CheckersEngine & game, int depth, bool maxPlayersMove)
{
	// 1.) Did we reach the depth limit?
	if (depth >= this->depthLimit)
	{
		// return a heuristic
		int h = heuristic(game);

		return pair<int, move_t>(h, 0);
	}

	// 2.) Did we reach a terminal node?
	auto s = game.status();
	switch (s)
	{
	case CheckersEngine::RED_WINS:
		return pair<int, move_t>(INT_MIN, 0);
		break;
	case CheckersEngine::BLACK_WINS:
		return pair<int, move_t>(INT_MAX, 0);
		break;
	case CheckersEngine::DRAW:
		return pair<int, move_t>(0, 0);
		break;
	}

	// 3.) Non Terminal states

	// Player Black (MAX)
	if (maxPlayersMove)
	{
		int bestMoveIndex = 0;
		int bestMoveValue = INT_MIN;

		vector<move_t> validMovesBlack = game.getValidMoves(true);

		pair<int, move_t> ret;

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

		vector<move_t> validMovesRed = game.getValidMoves(false);

		pair<int, move_t> ret;

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

pair<int, move_t> CheckersSolver::alphabeta(CheckersEngine & game, int depth, int alpha, int beta, bool maxPlayersMove)
{
	// 1.) Did we reach the depth limit?
	if (depth >= this->depthLimit)
	{
		// return a heuristic
		int h = heuristic(game);

		return pair<int, move_t>(h, 0);
	}

	// 2.) Did we reach a terminal node?
	auto s = game.status();
	switch (s)
	{
	case CheckersEngine::RED_WINS:
		return pair<int, move_t>(INT_MIN, 0);
		break;
	case CheckersEngine::BLACK_WINS:
		return pair<int, move_t>(INT_MAX, 0);
		break;
	case CheckersEngine::DRAW:
		return pair<int, move_t>(0, 0);
		break;
	}

	// 3.) Non Terminal states

	// Player Black (MAX)
	if (maxPlayersMove)
	{
		int bestMoveIndex = 0;
		int bestMoveValue = INT_MIN;

		vector<move_t> validMovesBlack = game.getValidMoves(true);

		pair<int, move_t> ret;

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

			alpha = max(alpha, result);
			if (alpha >= beta)
				break;	// cut-off
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

		vector<move_t> validMovesRed = game.getValidMoves(false);

		pair<int, move_t> ret;

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

			beta = min(beta, result);
			if (alpha >= beta)
				break;	// cut-off
		}

		// Return best heuristic and move
		ret.first = bestMoveValue;
		ret.second = validMovesRed.at(bestMoveIndex);

		return ret;
	} // -------------------- MIN -------------------------
}

int CheckersSolver::heuristic(const CheckersEngine & game) const
{
	int h = heuristic2(game);
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

int CheckersSolver::heuristic2(const CheckersEngine & game) const
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
