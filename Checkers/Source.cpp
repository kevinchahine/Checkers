#include <iostream>
#include <iomanip>
#include <random>
#include <time.h>

#include "Checkers.h"
#include "CheckerBoard.h"
#include "CheckersEngine.h"
#include "CheckersManager.h"
#include "CheckersSolver.h"

#include "TestCheckerBoard.h"
#include "TestCheckersEngine.h"

using namespace std;

default_random_engine generator(time(0));

int main()
{
	CheckersManager game;
	//game.playUserVsUser();
	game.playComputerVsComputer();

	//TestCheckersEngine t;
	//t.isPieceSafe();
	//t.isPieceMovable();
	//t.isPieceLoner();
	//t.isSpaceAHole();

	system("pause");
	return 0;
}