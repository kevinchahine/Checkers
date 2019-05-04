#include <iostream>
#include <iomanip>
#include <random>
#include <time.h>

#include "Checkers.h"
#include "CheckerBoard.h"
#include "CheckersEngine.h"
#include "CheckersManager.h"
#include "Solver.h"

#include "TestCheckerBoard.h"
#include "TestCheckersEngine.h"
#include "TestCheckersSolver1.h"
#include "TestGeneticAlgorithm.h"

using namespace std;

default_random_engine generator(time(0));

int main()
{
	Solver1 blackSolver, redSolver;

	CheckersManager game;
	//game.playUserVsUser();
	game.playComputerVsComputer(blackSolver, redSolver);

	//TestCheckersEngine t;
	//t.isPieceSafe();
	//t.isPieceMovable();
	//t.isPieceLoner();
	//t.isSpaceAHole();

	//TestCheckersSolver1 t;
	//t.test();

	//TestGeneticAlgorithm t;
	//t.test();

	system("pause");
	return 0;
}