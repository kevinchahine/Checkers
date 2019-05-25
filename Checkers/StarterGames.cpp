#include "StarterGames.h"

CheckersEngine StarterGames::initWin1()
{
	CheckersEngine win1;
	
	win1.clearBoard();
	win1.placePiece(7, 1, false, false);
	win1.placePiece(7, 3, false, false);
	win1.placePiece(7, 5, false, false);
	win1.placePiece(7, 7, false, false);
	win1.placePiece(6, 2, true, false);
	win1.placePiece(6, 6, false, false);
	win1.placePiece(5, 1, false, false);
	win1.placePiece(5, 3, false, false);
	win1.placePiece(5, 5, true, false);
	win1.placePiece(3, 1, true, false);
	win1.placePiece(3, 3, true, false);
	win1.placePiece(3, 5, true, false);
	win1.placePiece(2, 0, true, false);
	win1.placePiece(2, 4, true, false);
	win1.placePiece(1, 1, true, false);
	win1.placePiece(1, 7, true, false);
	win1.placePiece(0, 4, false, true);
	win1.placePiece(0, 6, true, false);

	return win1;
}

CheckersEngine StarterGames::initWin2()
{
	CheckersEngine win2(initWin1());

	win2.movePiece(6, 6, 4, 4);

	return win2;
}

CheckersEngine StarterGames::initWin3()
{
	CheckersEngine win3(initWin2());

	win3.movePiece(4, 4, 2, 2);

	return win3;
}

CheckersEngine StarterGames::initWin4()
{
	CheckersEngine win4(initWin3());
	
	win4.movePiece(2, 2, 0, 0);

	return win4;
}
