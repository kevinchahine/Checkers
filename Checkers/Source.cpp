#include <iostream>
#include <iomanip>

#include "Checkers.h"
#include "CheckersEngine.h"
#include "CheckersManager.h"
#include "CheckersSolver.h"

#include "TestCheckersEngine.h"

using namespace std;

int main()
{
	CheckersEngine game;
	CheckersManager manager;
	manager.gamePtr = &game;
	
	manager.playUserVsUser();

	system("pause");
	return 0;
}