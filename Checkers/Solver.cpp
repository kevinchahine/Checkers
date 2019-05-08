#include "Solver.h"

Solver::Solver() :
	depthLimit(1),
	timeLimit(CLOCK_MAX) {}

Solver::Solver(int depthLimit, clock_t timeLimit) :
	depthLimit(depthLimit),
	timeLimit(timeLimit) {}

Solver::~Solver() {}

pair<bool, move_t> Solver::playAsRed(CheckersEngine & game)
{
	minimax_t ret;

	startTime = clock();

	///ret = minimax(game, 0, false);
	ret = alphabeta(game, 0, INT_MIN, INT_MAX, false);

	return pair<bool, move_t>(
		game.movePiece(get<1>(ret)), get<1>(ret));
}

pair<bool, move_t> Solver::playAsBlack(CheckersEngine & game)
{
	minimax_t ret;

	startTime = clock();

	///ret = minimax(game, 0, true);
	ret = alphabeta(game, 0, INT_MIN, INT_MAX, true);

	return pair<bool, move_t>(
		game.movePiece(get<1>(ret)), get<1>(ret));
}

pair<bool, move_t> Solver::playAsX(CheckersEngine & game, bool maxPlayersMove)
{
	// Save the bestMove in here.
	minimax_t bestMove;

	// What time did we start at?
	startTime = clock();

	// Use Iterative Deepening and only return the best move
	// of the deepest search.
	for (int ply = 1; ply <= depthLimit; ply++)
	{
		// Do we still have time left?
		if (clock() - startTime > timeLimit)
		{
			break; // No, we're out of time.
		}

		// Then evaluate all valid moves of the next depth.
		bestMove = alphabeta(
			game, depthLimit - ply, INT_MIN, INT_MAX, maxPlayersMove);
	}

	// Return the best move we found for the
	// deepest ply that we searched completely.
	// And make that move in the real game.
	return pair<bool, move_t>(
		game.movePiece(get<1>(bestMove)), get<1>(bestMove));
}

//pair<int, move_t> Solver::minimax(CheckersEngine & game, int depth, bool maxPlayersMove)
//{
//	// 1.) Did we reach a terminal node?
//	auto s = game.status();
//	switch (s)
//	{
//	case CheckersEngine::RED_WINS:
//		return pair<int, move_t>(INT_MIN, 0);
//		break;
//	case CheckersEngine::BLACK_WINS:
//		return pair<int, move_t>(INT_MAX, 0);
//		break;
//	case CheckersEngine::DRAW:
//		return pair<int, move_t>(0, 0);
//		break;
//	}
//
//	// 2.) Did we reach the depth limit?
//	if (depth >= this->depthLimit && 
//		(clock() - startTime > this->timeLimit))
//	{
//		// return a heuristic
//		int h = calcHeuristic(game);
//
//		return pair<int, move_t>(h, 0);
//	}
//
//	// 3.) Non Terminal states
//
//	// Player Black (MAX)
//	if (maxPlayersMove)
//	{
//		int bestMoveIndex = 0;
//		int bestMoveValue = INT_MIN;
//
//		vector<move_t> validMovesBlack = game.getValidMoves(true);
//
//		pair<int, move_t> ret;
//
//		for (int i = 0; i < validMovesBlack.size(); i++)
//		{
//			CheckersEngine nextState = game;
//
//			bool jumpOccured;
//			jumpOccured = nextState.movePiece(validMovesBlack[i]);
//
//			if (jumpOccured)
//				ret = minimax(nextState, depth + 1, maxPlayersMove);
//			else
//				ret = minimax(nextState, depth + 1, !maxPlayersMove);
//
//			int result = ret.first;
//			if (result > bestMoveValue)
//			{
//				bestMoveIndex = i;
//				bestMoveValue = result;
//			}
//		}
//
//		// Return best heuristic and move
//		ret.first = bestMoveValue;
//		ret.second = validMovesBlack.at(bestMoveIndex);
//
//		return ret;
//	} // -------------------- MAX -------------------------
//	// Player Red (MIN)
//	else
//	{
//		int bestMoveIndex = 0;
//		int bestMoveValue = INT_MAX;
//
//		vector<move_t> validMovesRed = game.getValidMoves(false);
//
//		pair<int, move_t> ret;
//
//		for (int i = 0; i < validMovesRed.size(); i++)
//		{
//			CheckersEngine nextState = game;
//			bool jumpOccured;
//			jumpOccured = nextState.movePiece(validMovesRed[i]);
//
//			if (jumpOccured)
//				ret = minimax(nextState, depth + 1, maxPlayersMove);
//			else
//				ret = minimax(nextState, depth + 1, !maxPlayersMove);
//
//			int result = ret.first;
//
//			if (result < bestMoveValue)
//			{
//				bestMoveIndex = i;
//				bestMoveValue = result;
//			}
//		}
//
//		// Return best heuristic and move
//		ret.first = bestMoveValue;
//		ret.second = validMovesRed.at(bestMoveIndex);
//
//		return ret;
//	} // -------------------- MIN -------------------------
//}

Solver::minimax_t Solver::alphabeta(CheckersEngine & game, int depth, int alpha, int beta, bool maxPlayersMove)
{
	// 1.) Did we reach a terminal node?
	auto s = game.status();
	switch (s)
	{
	case CheckersEngine::RED_WINS:
		return minimax_t(INT_MIN, 0, MINIMAX::REAL_MOVE);
		break;
	case CheckersEngine::BLACK_WINS:
		return minimax_t(INT_MAX, 0, MINIMAX::REAL_MOVE);
		break;
	case CheckersEngine::DRAW:
		return minimax_t(0, 0, MINIMAX::REAL_MOVE);
		break;
	}

	// 2.) Did we reach the depth?
	if (depth >= this->depthLimit)
	{
		// Yes. return a heuristic
		int h = calcHeuristic(game);

		return minimax_t(h, 0, MINIMAX::REAL_MOVE);
	}

	// 2-2.) Did we reach the time limit?
	if (clock() - startTime > this->timeLimit)
	{
		// Yes. return a bluff value,
		// This value is not usable because we 
		// had to stop early and did not
		// search to the desired depth
		return minimax_t(0, 0, MINIMAX::BLUFF_MOVE);
	}

	// 3.) Non Terminal states

	// Player Black (MAX)
	if (maxPlayersMove)
	{
		int bestMoveIndex = 0;
		int bestMoveValue = INT_MIN;

		vector<move_t> validMovesBlack = game.getValidMoves(true);

		minimax_t ret;

		for (int i = 0; i < validMovesBlack.size(); i++)
		{
			CheckersEngine nextState = game;

			bool jumpOccured;
			jumpOccured = nextState.movePiece(validMovesBlack[i]);

			if (jumpOccured)
				ret = alphabeta(nextState, depth + 1, alpha, beta, maxPlayersMove);
			else
				ret = alphabeta(nextState, depth + 1, alpha, beta, !maxPlayersMove);

			int result = get<0>(ret);

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
		get<0>(ret) = bestMoveValue;
		get<1>(ret) = validMovesBlack.at(bestMoveIndex);

		return ret;
	} // -------------------- MAX -------------------------
	// Player Red (MIN)
	else
	{
		int bestMoveIndex = 0;
		int bestMoveValue = INT_MAX;

		vector<move_t> validMovesRed = game.getValidMoves(false);

		minimax_t ret;

		for (int i = 0; i < validMovesRed.size(); i++)
		{
			CheckersEngine nextState = game;
			bool jumpOccured;
			jumpOccured = nextState.movePiece(validMovesRed[i]);

			if (jumpOccured)
				ret = alphabeta(nextState, depth + 1, alpha, beta, maxPlayersMove);
			else
				ret = alphabeta(nextState, depth + 1, alpha, beta, !maxPlayersMove);

			int result = get<0>(ret);

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
		get<0>(ret) = bestMoveValue;
		get<1>(ret) = validMovesRed.at(bestMoveIndex);

		return ret;
	} // -------------------- MIN -------------------------
}



