#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <random>
#include <time.h>
#include <vector>
#include <list>
#include <set>

#include "CheckersSolver1.h"

using namespace std;

extern default_random_engine generator;

namespace GeneticAlgorithm
{
	vector<CheckersSolver1> generateInitialPopulation();

	CheckersSolver1 & selectRandomIndividual(const vector<CheckersSolver1> & population);

	CheckersSolver1 reproduce(const CheckersSolver1 & x, const CheckersSolver1 & y);

	CheckersSolver1 solve();


}