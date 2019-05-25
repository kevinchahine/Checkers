#include "Solver.h"

extern CheckersEngine win1;
extern CheckersEngine win2;
extern CheckersEngine win3;
extern CheckersEngine win0;

Solver::Solver() :
	depthLimit(1),
	timeLimit(CLOCK_MAX) {}

Solver::Solver(int depthLimit, clock_t timeLimit) :
	depthLimit(depthLimit),
	timeLimit(timeLimit) {}

Solver::~Solver() {}

move_t Solver::getDecision(const CheckersEngine & game, bool isBlack)
{
	// Save the bestMove in here.
	minimax_t bestMove;

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
		
		minimax_t plyBestMove = alphabeta(
			game, depthLimit - ply, INT_MIN, INT_MAX, isBlack);
		
		if (get<2>(plyBestMove) == BLUFF_MOVE)
		{
			/*cerr << __FILE__ << " line " << __LINE__
				<< " bluff move was returned"
				<< get<0>(plyBestMove) << '\t'
				<< get<1>(plyBestMove) << endl
				<< " clock = " << clock()
				<< " startTime = " << startTime
				<< " timeLimit = " << timeLimit << endl
				<< " ply = " << ply
				<< endl;*/
			//system("pause");
		}
		else {
			bestMove = plyBestMove;
		}
	}

	// Return the best move (get<1> of bestMove)
	// the we found for the
	// deepest ply that we searched completely.
	// without making that move in the real game.
	return get<1>(bestMove);
}

move_t Solver::getDecisionAsBlack(const CheckersEngine & game)
{
	return getDecision(game, true);
}

move_t Solver::getDecisionAsRed(const CheckersEngine & game)
{
	return getDecision(game, false);
}

Solver::minimax_t Solver::alphabeta(const CheckersEngine & game, int depth, int alpha, int beta, bool maxPlayersMove) const
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
		// Yes. return a BLUFF value,
		// This value is not usable because we 
		// had to stop early and did not
		// search to the desired depth
		return minimax_t(0, 0, MINIMAX::BLUFF_MOVE);
	}

	// 3.) -------- Non Terminal states -------------------
	   
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

			int retHeuristic = get<0>(ret);

			if (retHeuristic > bestMoveValue)
			{
				bestMoveIndex = i;
				bestMoveValue = retHeuristic;
			}

			alpha = max(alpha, retHeuristic);
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

			int retHeuristic = get<0>(ret);

			if (retHeuristic < bestMoveValue)
			{
				bestMoveIndex = i;
				bestMoveValue = retHeuristic;
			}

			beta = min(beta, retHeuristic);
			if (alpha >= beta)
				break;	// cut-off
		}

		// Return best heuristic and move
		get<0>(ret) = bestMoveValue;
		get<1>(ret) = validMovesRed.at(bestMoveIndex);

		return ret;
	} // -------------------- MIN -------------------------
}



