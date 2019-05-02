#include "CheckersSolver1.h"

CheckersSolver1::CheckersSolver1()
{
}

CheckersSolver1::~CheckersSolver1()
{
}

int CheckersSolver1::calcHeuristic(const CheckersEngine & game) const
{
	int h = 0;

	/*
	HEURISTIC COMPONENTS:
	1.) # of Pawns
	2.) # of Kings
	3.) # of safe pawns	*
	4.) # of safe Kings *
	5.) # of moveable pawns (able to make a move other than capture) *
	6.) # of moveable kings (able to make a move other than capture) *
	7.) Aggregated distance of Pawns to promotion line
	8.) # of unoccupied fields on promotion line
	9.) # of defender pieces (pieces in 2 lower most rows)
	10.) # of attacking pawns (pieces in 3 upper most rows)
	11.) # of centrally positioned pawns (pawns in 8 central positions on board)
	12.) # of centrally positioned kings 
	13.) # of pawns positioned on the main diagonal
	14.) # of kings positioned on the main diagonal
	15.) # of pawns positioned on the double diagonal
	16.) # of kings positioned on the double diagonal
	17.) # on loner pawns (pawn not adjacent to any other piece)
	18.) # of loner kings (king not adjacent to any other piece)
	19.) # of holes (empty spaces adjacent to at least 3 pieces of the same color)

	Below components will have boolean values
	20.) Presence of a Triangle pattern *
	21.) Presence of an Oreo pattern *
	22.) Presence of a Bridge pattern *
	23.) Presence of a Dog pattern *
	24.) Presence of a pawn in corner
	25.) Presence of a knig in corner
	*/

	for (int r = 0; r < 8; r++)
	{
		for (int c = (r % 2); c < 8; c += 2)
		{
			// Is Space Occupied?
			if (game.isOccupied(r, c))
			{
				bool pieceIsBlack = game.isPieceBlack(r, c);

				int pieceHeuristic = 0;

				
			}
		}
	}

	return h;
}
