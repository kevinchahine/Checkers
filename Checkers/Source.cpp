#include <iostream>
#include <iomanip>
#include <random>
#include <time.h>

#include "Checkers.h"
#include "CheckerBoard.h"
#include "CheckersEngine.h"
#include "CheckersManager.h"
#include "Player.h"
#include "Solver.h"
#include "User.h"

#include "BaseView.h"
#include "View.h"
#include "ViewLayout.h"
#include "GameInterface.h"

#include "TestCheckerBoard.h"
#include "TestCheckersEngine.h"
#include "TestCheckersSolver1.h"
#include "TestGeneticAlgorithm.h"
#include "TestSolver.h"

#include "StarterGames.h"

using namespace std;

default_random_engine generator((unsigned int) time(0));

int main()
{
	CheckersManager game(StarterGames::initWin1());
	
	Solver1 baseSolver(1000000, 7000);
	//Solver1 combo2Solver(1000000, 5000, WEIGHTS_COMBO_2);
	//Solver1 combo3Solver(1000000, 5000, WEIGHTS_COMBO_3);
	//Solver1 combo4Solver(1000000, 7000, WEIGHTS_COMBO_4);
	Solver1 combo5Solver(1000000, 7000, WEIGHTS_COMBO_5);
	//User user;
	//CheckersManager game;

	//game.play(combo3Solver, user);
	//game.play(combo3Solver, combo2Solver);
	//game.play(combo4Solver, baseSolver);
	game.play(baseSolver, combo5Solver, true, false);
	//GeneticAlgorithm::solve();

	//GameInterface inter;
	//inter.layout.stamp()
	//inter.print();

	//TestCheckersEngine t;
	//t.validMoves(StarterGames::initWin3());
	/*auto state = StarterGames::initWin4();
	state.print();

	int h = combo5Solver.
		calcHeuristic(state);

	cout << h << endl;*/

	system("pause");
	return 0;
}