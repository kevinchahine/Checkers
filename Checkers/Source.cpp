#include <iostream>
#include <iomanip>

#include "Checkers.h"
#include "CheckersEngine.h"

#include "TestCheckersEngine.h"

using namespace std;

int main()
{
	TestCheckersEngine test;

	test.possibleMoves();
	
	system("pause");
	return 0;
}