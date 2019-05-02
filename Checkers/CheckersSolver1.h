#pragma once

#include "CheckersSolver.h"

class CheckersSolver1 : public CheckersSolver
{
public:
	CheckersSolver1();
	~CheckersSolver1();

	int calcHeuristic(const CheckersEngine & game) const;

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
	23.) Presence of a Dog pattern NOT COUNTED
	*/

	// 24.) Presence of a pawn in corner
	int8_t countCornerPawns(const CheckersEngine & game) const;

	// 25.) Presence of a knig in corner
	int8_t countCornerKings(const CheckersEngine & game) const;

public:
	// 1.) # of Pawns 
	int w1 = 0;

	// 2.) # of Kings
	int w2 = 0;

	// 3.) # of safe pawns
	int w3 = 0;

	// 4.) # of safe Kings
	int w4 = 0;

	// 5.) # of moveable pawns (able to make a move other than capture)
	int w5 = 0;

	// 6.) # of moveable kings (able to make a move other than capture)
	int w6 = 0;

	// 7.) Aggregated distance of Pawns to promotion line
	int w7 = 0;

	// 8.) # of unoccupied fields on promotion line
	int w8 = 0;

	// 9.) # of defender pieces (pieces in 2 lower most rows)
	int w9 = 0;

	// 10.) # of attacking pawns (pieces in 3 upper most rows)
	int w10 = 0;

	// 11.) # of centrally positioned pawns (pawns in 8 central positions on board)
	int w11 = 0;

	// 12.) # of centrally positioned kings 
	int w12 = 0;

	// 13.) # of pawns positioned on the main diagonal
	int w13 = 0;

	// 14.) # of kings positioned on the main diagonal
	int w14 = 0;

	// 15.) # of pawns positioned on the double diagonal
	int w15 = 0;

	// 16.) # of kings positioned on the double diagonal
	int w16 = 0;

	// 17.) # on loner pawns (pawn not adjacent to any other piece)
	int w17 = 0;

	// 18.) # of loner kings (king not adjacent to any other piece)
	int w18 = 0;

	// 19.) # of holes (empty spaces adjacent to at least 3 pieces of the same color)
	int w19 = 0;

	// Below components will have boolean values
	// 20.) Presence of a Triangle pattern *
	int w20 = 0; // Not yet counted

	// 21.) Presence of an Oreo pattern *
	int w21 = 0; // Not yet counted

	// 22.) Presence of a Bridge pattern *
	int w22 = 0; // Not yet counted

	// 23.) Presence of a Dog pattern *
	int w23 = 0; // Not yet counted

	// 24.) Presence of a pawn in corner
	int w24 = 0;

	// 25.) Presence of a king in corner
	int w25 = 0;
};

