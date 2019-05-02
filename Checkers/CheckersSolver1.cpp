#include "CheckersSolver1.h"

CheckersSolver1::CheckersSolver1()
{
}

CheckersSolver1::~CheckersSolver1()
{
}

int CheckersSolver1::calcHeuristic(const CheckersEngine & game) const
{
	// HEURISTIC COMPONENTS:
	// (BLACK pieces count as +1, RED pieces count as -1)

	// 1.) # of Pawns 
	int8_t nOfPawns = 0;

	// 2.) # of Kings
	int8_t nOfKings = 0;

	// 3.) # of safe pawns
	int8_t nOfSafePawns = 0;

	// 4.) # of safe Kings
	int8_t nOfSafeKings = 0;

	// 5.) # of moveable pawns (able to make a move other than capture)
	int8_t nOfMoveablePawns = 0;

	// 6.) # of moveable kings (able to make a move other than capture)
	int8_t nOfMovableKings = 0;

	// 7.) Aggregated distance of Pawns to promotion line
	int8_t distPawnsToPromotion = 0;

	// 8.) # of unoccupied fields on promotion line
	int8_t nUnoccupiedSpacesOnPromotionLine = 0;

	// 9.) # of defender pieces (pieces in 2 lower most rows)
	int8_t nDefenderPieces = 0;

	// 10.) # of attacking pawns (pieces in 3 upper most rows)
	int8_t nAttackigPawns = 0;

	// 11.) # of centrally positioned pawns (pawns in 8 central positions on board)
	int8_t nCentralPawns = 0;

	// 12.) # of centrally positioned kings 
	int8_t nCentralKings = 0;

	// 13.) # of pawns positioned on the main diagonal
	int8_t nMainDiagonalPawns = 0;

	// 14.) # of kings positioned on the main diagonal
	int8_t nMainDiagonalKings = 0;

	// 15.) # of pawns positioned on the double diagonal
	int8_t nDoubleDiagonalPawns = 0;

	// 16.) # of kings positioned on the double diagonal
	int8_t nDoubleDiagonalKings = 0;

	// 17.) # on loner pawns (pawn not adjacent to any other piece)
	int8_t nLonerPawns = 0;

	// 18.) # of loner kings (king not adjacent to any other piece)
	int8_t nLonerKings = 0;

	// 19.) # of holes (empty spaces adjacent to at least 3 pieces of the same color)
	int8_t nHoles = 0;

	// Below components will have boolean values
	// 20.) Presence of a Triangle pattern *
	bool triangleIsPresent = false; // Not yet counted

	// 21.) Presence of an Oreo pattern *
	bool oreoIsPresent = false; // Not yet counted

	// 22.) Presence of a Bridge pattern *
	bool bridgeIsPresent = false; // Not yet counted

	// 23.) Presence of a Dog pattern *
	bool dogIsPresent = false; // Not yet counted

	// 24.) Presence of a pawn in corner
	int8_t nOfCornerPawns = 0;

	// 25.) Presence of a king in corner
	int8_t nOfCornerKings = 0;

	for (int r = 0; r < 8; r++)
	{
		for (int c = (r % 2); c < 8; c += 2)
		{
			// Is Space Occupied?
			if (game.isOccupied(r, c))
			{
				// Yes, Space is Occupied
				
				bool pieceIsBlack = game.isPieceBlack(r, c);
				int8_t pieceAdder = (pieceIsBlack ? +1 : -1);

				// 1.) # of Pawns 
				if (game.isPawn(r, c))
				{
					nOfPawns += pieceAdder;

					// 3.) # of safe pawns
					if (game.isPieceSafe(r, c))
						nOfSafePawns += pieceAdder;

					// 5.) # of moveable pawns (able to make a move other than capture)
					if (game.isPieceMovable(r, c))
						nOfMoveablePawns += pieceAdder;
					
					// 7.) Aggregated distance of Pawns to promotion line
					if (pieceIsBlack)
					{
						distPawnsToPromotion += 7 - r;
					}
					else {
						distPawnsToPromotion -= r;
					}

					// 17.) # on loner pawns (pawn not adjacent to any other piece)
					if (game.isPieceLoner(r, c))
						nLonerPawns += pieceAdder;

					
				}

				// 2.) # of Kings
				if (game.isKing(r, c))
				{
					nOfKings += pieceAdder;

					// 4.) # of safe Kings
					if (game.isPieceSafe(r, c))
						nOfSafeKings += pieceAdder;

					// 6.) # of moveable kings (able to make a move other than capture)
					if (game.isPieceMovable(r, c))
						nOfMovableKings += pieceAdder;

					// 18.) # of loner kings (king not adjacent to any other piece)
					nLonerKings += pieceAdder;
				}

			} // end if (game.isOccupied(r, c))
			else
			{
				// No, Space is Empty
				// 19.) # of holes (empty spaces adjacent to at least 3 pieces of the same color)
				pair<bool, bool> p = game.isSpaceAHole(r, c);
				// Is space a hole?
				if (p.first)
				{
					// Yes. Is it surrounded by BLACK or RED
					nHoles += (p.second ? +1 : -1);
				}
			} // end else
		} // end for (int c = (r % 2);
	} // end for (int r = 0; 

	// 8.) # of unoccupied fields on promotion line
	nUnoccupiedSpacesOnPromotionLine =
		countUnoccupiedSpacesOnPromotionLine(game);

	// 9.) # of defender pieces (pieces in 2 lower most rows)
	nDefenderPieces =
		countDefenderPieces(game);

	// 10.) # of attacking pawns (pieces in 3 upper most rows)
	nAttackigPawns =
		countAttackingPawns(game);

	// 11.) # of centrally positioned pawns (pawns in 8 central positions on board)
	nCentralPawns =
		countCentralPawns(game);

	// 12.) # of centrally positioned kings 
	nCentralKings =
		countCentralKings(game);

	// 13.) # of pawns positioned on the main diagonal
	nMainDiagonalPawns =
		countMainDiagonalPawns(game);

	// 14.) # of kings positioned on the main diagonal
	nMainDiagonalKings =
		countMainDiagonalKings(game);

	// 15.) # of pawns positioned on the double diagonal
	nDoubleDiagonalPawns =
		countDoubleDiagonalPawns(game);

	// 16.) # of kings positioned on the double diagonal
	nDoubleDiagonalKings =
		countDoubleDiagonalKings(game);

	// 24.) Presence of a pawn in corner
	nOfCornerPawns = 
		countCornerPawns(game);

	// 25.) Presence of a king in corner
	nOfCornerKings =
		countCornerKings(game);
	
	// ------------- SUM UP HUERISTIC COMPONENTS ----------
	int h =
		// 1.) # of Pawns 
		w1 * nOfPawns +
		// 2.) # of Kings
		w2 * nOfKings +
		// 3.) # of safe pawns
		w3 * nOfSafePawns +
		// 4.) # of safe Kings
		w4 * nOfSafeKings +
		// 5.) # of moveable pawns (able to make a move other than capture)
		w5 * nOfMoveablePawns +
		// 6.) # of moveable kings (able to make a move other than capture)
		w6 * nOfMovableKings +
		// 7.) Aggregated distance of Pawns to promotion line
		w7 * distPawnsToPromotion +
		// 8.) # of unoccupied fields on promotion line
		w8 * nUnoccupiedSpacesOnPromotionLine +
		// 9.) # of defender pieces (pieces in 2 lower most rows)
		w9 * nDefenderPieces +
		// 10.) # of attacking pawns (pieces in 3 upper most rows)
		w10 * nAttackigPawns +
		// 11.) # of centrally positioned pawns (pawns in 8 central positions on board)
		w11 * nCentralPawns +
		// 12.) # of centrally positioned kings 
		w12 * nCentralKings +
		// 13.) # of pawns positioned on the main diagonal
		w13 * nMainDiagonalPawns +
		// 14.) # of kings positioned on the main diagonal
		w14 * nMainDiagonalKings +
		// 15.) # of pawns positioned on the double diagonal
		w15 * nDoubleDiagonalPawns +
		// 16.) # of kings positioned on the double diagonal
		w16 * nDoubleDiagonalKings +
		// 17.) # on loner pawns (pawn not adjacent to any other piece)
		w17 * nLonerPawns +
		// 18.) # of loner kings (king not adjacent to any other piece)
		w18 * nLonerKings +
		// 19.) # of holes (empty spaces adjacent to at least 3 pieces of the same color)
		w19 * nHoles +
		// 20.) Presence of a Triangle pattern *
		w20 * triangleIsPresent +
		// 21.) Presence of an Oreo pattern *
		w21 * oreoIsPresent +
		// 22.) Presence of a Bridge pattern *
		w22 * bridgeIsPresent +
		// 23.) Presence of a Dog pattern *
		w23 * dogIsPresent +
		// 24.) Presence of a pawn in corner
		w24 * nOfCornerPawns +
		// 25.) Presence of a king in corner
		w25 * nOfCornerKings;

	return h;
}

int8_t CheckersSolver1::countUnoccupiedSpacesOnPromotionLine(const CheckersEngine & game) const
{
	int8_t count = 0;

	// BLACK promotion line 1st
	int8_t r = 0;
	for (int8_t c = (r % 2); c < 8; c += 2)
	{
		if (game.isOccupied(r, c))
			count++;
	}
	r = 7;
	// RED promotion line next
	for (int8_t c = (r % 2); c < 8; c += 2)
	{
		if (game.isOccupied(r, c))
			count--;
	}

	return count;
}

int8_t CheckersSolver1::countDefenderPieces(const CheckersEngine & game) const
{
	int8_t count = 0;

	// BLACK 1st
	for (int8_t r = 0; r < 2; r++)
	{
		for (int8_t c = (r % 2); c < 8; c += 2)
		{
			if (game.isOccupied(r, c) && game.isPieceBlack(r, c))
				count++;
		}
	}

	// RED next
	for (int8_t r = 6; r < 8; r++)
	{
		for (int8_t c = (r % 2); c < 8; c += 2)
		{
			if (game.isOccupied(r, c) && game.isPieceRed(r, c))
				count--;
		}
	}

	return count;
}

int8_t CheckersSolver1::countAttackingPawns(const CheckersEngine & game) const
{
	int8_t count = 0;

	// BLACK 1st
	for (int8_t r = 5; r < 8; r++)
	{
		for (int8_t c = (r % 2); c < 8; c += 2)
		{
			if (game.isOccupied(r, c) && 
				game.isPieceBlack(r, c) &&
				game.isPawn(r, c))
				count++;
		}
	}

	// RED next
	for (int8_t r = 0; r < 3; r++)
	{
		for (int8_t c = (r % 2); c < 8; c += 2)
		{
			if (game.isOccupied(r, c) && 
				game.isPieceRed(r, c) &&
				game.isPawn(r, c))
				count--;
		}
	}

	return count;
}

int8_t CheckersSolver1::countCentralPawns(const CheckersEngine & game) const
{
	int8_t count = 0;

	for (int8_t r = 2; r < 6; r++)
	{
		for (int8_t c = (r % 2) + 1; c < 6; c += 2)
		{
			if (game.isOccupied(r, c) && game.isPawn(r, c))
			{
				count += (game.isPieceBlack(r, c) ? +1 : -1);
			}
		}
	}

	return count;
}

int8_t CheckersSolver1::countCentralKings(const CheckersEngine & game) const
{
	int8_t count = 0;

	for (int8_t r = 2; r < 6; r++)
	{
		for (int8_t c = (r % 2) + 1; c < 6; c += 2)
		{
			if (game.isOccupied(r, c) && game.isKing(r, c))
			{
				count += (game.isPieceBlack(r, c) ? +1 : -1);
			}
		}
	}

	return count;
}

int8_t CheckersSolver1::countMainDiagonalPawns(const CheckersEngine & game) const
{
	int8_t count = 0;

	for (int8_t i = 0; i < 7; i++)
	{
		if (game.isOccupied(i, i) && game.isPawn(i, i))
		{
			count += (game.isPieceBlack(i, i) ? +1 : -1);
		}
	}

	return count;
}

int8_t CheckersSolver1::countMainDiagonalKings(const CheckersEngine & game) const
{
	int8_t count = 0;

	for (int8_t i = 0; i < 7; i++)
	{
		if (game.isOccupied(i, i) && game.isKing(i, i))
		{
			count += (game.isPieceBlack(i, i) ? +1 : -1);
		}
	}

	return count;
}

int8_t CheckersSolver1::countDoubleDiagonalPawns(const CheckersEngine & game) const
{
	int8_t count = 0;

	for (int8_t c = 0; c < 7; c++)
	{
		int8_t r = 7 - c;

		int8_t rTop = r - 1;
		if (game.isOccupied(rTop, c) && game.isPawn(rTop, c))
		{
			count += (game.isPieceBlack(rTop, c) ? +1 : -1);
		}

		int8_t cBot = c + 1;
		if (game.isOccupied(r, cBot) && game.isPawn(r, cBot))
		{
			count += (game.isPieceBlack(r, cBot) ? +1 : -1);
		}
	}

	return count;
}

int8_t CheckersSolver1::countDoubleDiagonalKings(const CheckersEngine & game) const
{
	int8_t count = 0;

	for (int8_t c = 0; c < 7; c++)
	{
		int8_t r = 7 - c;

		int8_t rTop = r - 1;
		if (game.isOccupied(rTop, c) && game.isKing(rTop, c))
		{
			count += (game.isPieceBlack(rTop, c) ? +1 : -1);
		}

		int8_t cBot = c + 1;
		if (game.isOccupied(r, cBot) && game.isKing(r, cBot))
		{
			count += (game.isPieceBlack(r, cBot) ? +1 : -1);
		}
	}

	return count;
}

int8_t CheckersSolver1::countCornerPawns(const CheckersEngine & game) const
{
	int8_t count = 0;

	// Is a BLACK pawn in its upper left corner?
	if (game.isOccupied(0, 0) &&
		game.isPawn(0, 0) &&
		game.isPieceRed(0, 0))
		count++;

	// Is a RED pawn in its lower right corner?
	if (game.isOccupied(7, 7) &&
		game.isPawn(7, 7) &&
		game.isPieceRed(7, 7))
		count--;

	return count;
}

int8_t CheckersSolver1::countCornerKings(const CheckersEngine & game) const
{
	int8_t count = 0;

	// Is a BLACK pawn in its upper left corner?
	if (game.isOccupied(0, 0) &&
		game.isKing(0, 0) &&
		game.isPieceRed(0, 0))
		count++;

	// Is a RED pawn in its lower right corner?
	if (game.isOccupied(7, 7) &&
		game.isKing(7, 7) &&
		game.isPieceRed(7, 7))
		count--;

	return count;
}

