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

default_random_engine generator((unsigned int) time(0));

int main()
{
	Solver1 blackSolver(6, WEIGHTS_COMBO_2), redSolver(6);
	CheckersManager game;
	//game.playUserVsUser();
	game.playComputerVsComputer(blackSolver, redSolver);

	//GeneticAlgorithm::solve();

	//TestCheckersEngine t;
	//t.isPieceSafe();
	//t.isPieceMovable();
	//t.isPieceLoner();
	//t.isSpaceAHole();

	//TestCheckersSolver1 t;
	//t.test();

	//TestGeneticAlgorithm t;
	//t.generateInitialPopulation();
	//t._evaluateFitnessOfPopulation();
	//t._produceASingleGeneration();

	system("pause");
	return 0;
}