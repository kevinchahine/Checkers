#include "Solver.h"

Solver::Solver() {}

Solver::~Solver() {}

pair<bool, move_t> Solver::playAsRed(CheckersEngine & game)
{
	pair<int, move_t> ret;

	///ret = minimax(game, 0, false);
	ret = alphabeta(game, 0, INT_MIN, INT_MAX, false);

	return pair<bool, move_t>(
		game.movePiece(ret.second), ret.second);
}

pair<bool, move_t> Solver::playAsBlack(CheckersEngine & game)
{
	pair<int, move_t> ret;

	///ret = minimax(game, 0, true);
	ret = alphabeta(game, 0, INT_MIN, INT_MAX, true);

	return pair<bool, move_t>(
		game.movePiece(ret.second), ret.second);
}

pair<int, move_t> Solver::minimax(CheckersEngine & game, int depth, bool maxPlayersMove)
{
	// 1.) Did we reach a terminal node?
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

	// 2.) Did we reach the depth limit?
	if (depth >= this->DEPTH_LIMIT)
	{
		// return a heuristic
		int h = calcHeuristic(game);

		return pair<int, move_t>(h, 0);
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

pair<int, move_t> Solver::alphabeta(CheckersEngine & game, int depth, int alpha, int beta, bool maxPlayersMove)
{
	// 1.) Did we reach a terminal node?
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

	// 2.) Did we reach the depth limit?
	if (depth >= this->DEPTH_LIMIT)
	{
		// Yes. return a heuristic
		int h = calcHeuristic(game);

		return pair<int, move_t>(h, 0);
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



