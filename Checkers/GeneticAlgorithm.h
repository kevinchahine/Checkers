#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <random>
#include <time.h>
#include <vector>

#include "CheckersManager.h"
#include "Solver1.h"

using namespace std;

extern default_random_engine generator;

namespace GeneticAlgorithm
{
	vector<pair<Solver1, int>> generateInitialPopulation();

	int evaluateFitnessOfPopulation(vector<pair<Solver1, int>> & population);
	
	pair<Solver1, int> & selectRandomIndividual(vector<pair<Solver1, int>> & population, int sumOfFitness);

	void reproduce(const Solver1 & parent1, const Solver1 & parent2, Solver1 & newIndividual);
	
	void splice(const Solver1 & parent1, const Solver1 & parent2, Solver1 & newIndividual);

	void singleMutation(Solver1 & individual);

	Solver1 solve();

	static const size_t POPULATION_SIZE = 4;
	
	static const bool LIMIT_BY_TIME = true;
	static const bool LIMIT_BY_GENERATIONS = false;

	static const size_t N_GENERATIONS = 30;
	static const clock_t TIME_LIMIT = 5 * 60 * 1000;	// 5 minutes
}
