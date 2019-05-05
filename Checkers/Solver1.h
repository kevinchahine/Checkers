#pragma once

#include <list>
#include <sstream>

#include "Solver.h"

class Solver1 : public Solver
{
public:
	Solver1();
	Solver1(int depthLimit);
	Solver1(const Solver1 & solver1);
	Solver1(const Solver1 && solver1);
	~Solver1();

	virtual stringstream toStream() const;

	virtual int calcHeuristic(const CheckersEngine & game) const;

	//8.) # of unoccupied fields on promotion line
	int8_t countUnoccupiedSpacesOnPromotionLine(const CheckersEngine & game) const;

	//9.) # of defender pieces (pieces in 2 lower most rows)
	int8_t countDefenderPieces(const CheckersEngine & game) const;

	//10.) # of attacking pawns(pieces in 3 upper most rows)
	int8_t countAttackingPawns(const CheckersEngine & game) const;

	//11.) # of centrally positioned pawns(pawns in 8 central positions on board)
	int8_t countCentralPawns(const CheckersEngine & game) const;

	//12.) # of centrally positioned kings
	int8_t countCentralKings(const CheckersEngine & game) const;

	//13.) # of pawns positioned on the main diagonal
	int8_t countMainDiagonalPawns(const CheckersEngine & game) const;

	//14.) # of kings positioned on the main diagonal
	int8_t countMainDiagonalKings(const CheckersEngine & game) const;

	//15.) # of pawns positioned on the double diagonal
	int8_t countDoubleDiagonalPawns(const CheckersEngine & game) const;

	//16.) # of kings positioned on the double diagonal
	int8_t countDoubleDiagonalKings(const CheckersEngine & game) const;
	
	/*Below components will have boolean values
	20.) Presence of a Triangle pattern NOT COUNTED
	21.) Presence of an Oreo pattern NOT COUNTED
	22.) Presence of a Bridge pattern NOT COUNTED
	23.) Presence of a Dog pattern NOT COUNTED*/

	// 24.) Presence of a pawn in corner
	int8_t countCornerPawns(const CheckersEngine & game) const;

	// 25.) Presence of a knig in corner
	int8_t countCornerKings(const CheckersEngine & game) const;

public:
	static const size_t N_WEIGHTS = 25;
	// 1.) # of Pawns 
	// 2.) # of Kings
	// 4.) # of safe Kings
	// 5.) # of moveable pawns (able to make a move other than capture)
	// 6.) # of moveable kings (able to make a move other than capture)
	// 7.) Aggregated distance of Pawns to promotion line
	// 8.) # of unoccupied fields on promotion line
	// 9.) # of defender pieces (pieces in 2 lower most rows)
	// 10.) # of attacking pawns (pieces in 3 upper most rows)
	// 11.) # of centrally positioned pawns (pawns in 8 central positions on board)
	// 12.) # of centrally positioned kings 
	// 13.) # of pawns positioned on the main diagonal
	// 14.) # of kings positioned on the main diagonal
	// 15.) # of pawns positioned on the double diagonal
	// 16.) # of kings positioned on the double diagonal
	// 17.) # on loner pawns (pawn not adjacent to any other piece)
	// 18.) # of loner kings (king not adjacent to any other piece)
	// 19.) # of holes (empty spaces adjacent to at least 3 pieces of the same color)
	// Below components will have boolean values
	// 20.) Presence of a Triangle pattern *  Not yet counted
	// 21.) Presence of an Oreo pattern *  Not yet counted
	// 22.) Presence of a Bridge pattern *  Not yet counted
	// 23.) Presence of a Dog pattern *  Not yet counted
	// 24.) Presence of a pawn in corner
	// 25.) Presence of a king in corner
	int weights[N_WEIGHTS];
};

