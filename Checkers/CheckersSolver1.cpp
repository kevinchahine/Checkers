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
	# of Pawns
	# of Kings
	# of safe pawns
	# of safe Kings
	# of moveable pawns
	# of moveable kings
	Aggregated distance of Pawns to promotion line
	# of unoccupied fields on promotion line
	# of defender pieces (pieces in 2 lower most rows)
	# of attacking pawns (pieces in 3 upper most rows)
	# of centrally positioned pawns (pawns in 8 central positions on board)
	# of pawns positioned on the main diagonal
	# of kings positioned on the main diagonal
	# of pawns positioned on the double diagonal
	# of kings positioned on the double diagonal
	# on loner pawns (pawn no adjacent to any other piece)
	# of loner kings
	# of holes (empty spaces adjacent to at least 3 pieces of the same color)

	Below components will have boolean values
	Presence of a Triangle pattern
	Presence of an Oreo pattern
	Presence of a Bridge pattern
	Presence of a Dog pattern
	Presence of a pawn in corner
	Presence of a knig in corner
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
