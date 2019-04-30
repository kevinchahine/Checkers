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
	CheckersEngine game;
	CheckersManager manager;
	manager.gamePtr = &game;
	
	manager.playUserVsUser();

	/*TestCheckerBoard board;
	board.print();*/

	system("pause");
	return 0;
}