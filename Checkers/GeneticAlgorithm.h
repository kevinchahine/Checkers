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
	typedef Solver1 solver_t;
	typedef pair<solver_t, int> individual_t;
	typedef vector<individual_t> population_t;

	// Generates the initial population (Generation 0) to be
	// used in the GA. Individuals are generated with random
	// values between 
	population_t generateInitialPopulation();

	int evaluateFitnessOfPopulation(population_t & population);
	
	individual_t & selectRandomIndividual(population_t & population, int sumOfFitness);

	void reproduce(const solver_t & parent1, const solver_t & parent2, solver_t & newIndividual);
	
	void splice(const solver_t & parent1, const solver_t & parent2, solver_t & newIndividual);

	void singleMutation(solver_t & individual);

	solver_t solve();

	void writePopulationToFile(string fileName, const population_t & population);

	const size_t POPULATION_SIZE = 10; // 50;
	const int MIN_WEIGHT = -40;
	const int MAX_WEIGHT = 40;
	const int PROBABILITY_OF_SINGLE_MUTATION = 10;	// 10%
	const int DEPTH_LIMIT = 1;

	const bool LIMIT_BY_GENERATIONS = false;
	const bool LIMIT_BY_TIME = false;

	const size_t N_GENERATIONS = 100;
	const clock_t TIME_LIMIT = 1 * 60 * 1000;	// 1 minutes
}
