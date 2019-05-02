#include <iostream>
#include <iomanip>

#include "Checkers.h"
#include "CheckerBoard.h"
#include "CheckersEngine.h"
#include "CheckersManager.h"
#include "CheckersSolver.h"

#include "TestCheckerBoard.h"
#include "TestCheckersEngine.h"

using namespace std;

int main()
{
	///CheckersManager game;
	///manager.playUserVsUser();
	///game.playComputerVsComputer();

	TestCheckersEngine t;
	//t.isPieceSafe();
	//t.isPieceMovable();
	t.isPieceLoner();

	system("pause");
	return 0;
}