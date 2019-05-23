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

#include "TestCheckerBoard.h"
#include "TestCheckersEngine.h"
#include "TestCheckersSolver1.h"
#include "TestGeneticAlgorithm.h"

using namespace std;

default_random_engine generator((unsigned int) time(0));

int main()
{
	//Solver1 baseSolver(1000000, 5000);
	//Solver1 combo2Solver(1000000, 5000, WEIGHTS_COMBO_2);
	//Solver1 combo3Solver(1000000, 5000, WEIGHTS_COMBO_3);
	//User user;
	//CheckersManager game;

	//game.play(blackSolver, user);
	//game.play(combo3Solver, combo2Solver);
	//GeneticAlgorithm::solve();

	View v(4, 4, Colors::combine(Colors::BLUE, Colors::RED), '-');
	v.print();
	View v2(2, 2, Colors::combine(Colors::YELLOW, Colors::GREEN), '@');

	ViewLayout l(BaseView(10, 10, '|'));
	l.stamp(v, 2, 1);
	l.stamp(v2, 7, 7);
	
	
	ViewLayout l2(BaseView(20, 20, '$'));
	l2.stamp(l, 3, 4);
	l2.print();

	v.colorText.at(0).at(0).second = '3';
	l.colorText.at(1).at(1).second = 'L';
	
	l2.print();

	system("pause");
	return 0;
}