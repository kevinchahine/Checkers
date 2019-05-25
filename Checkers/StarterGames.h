#pragma once

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

using namespace std;

namespace StarterGames
{
	CheckersEngine initWin1();
	CheckersEngine initWin2();
	CheckersEngine initWin3();
	CheckersEngine initWin4();
}
