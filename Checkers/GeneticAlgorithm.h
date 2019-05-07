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

// https://en.wikipedia.org/wiki/Selection_(genetic_algorithm)

namespace GeneticAlgorithm
{
	typedef double fitness_t;
	typedef Solver1 solver_t;
	typedef pair<solver_t, fitness_t> individual_t;
	typedef vector<individual_t> population_t;

	// Generates the initial population (Generation 0) to be
	// used in the GA. Individuals are generated with random
	// values between 
	population_t generateInitialPopulation();

	int evaluateFitnessOfPopulation(population_t & population);
	
	// Call this after evaluateFitnessOfPopulation()
	// This function will Normalize the individuals fitness
	// and sort them in descending order, so that the selection
	// function can select the better individuals for breeding
	void sortAndScale(population_t & population, fitness_t sumOfFitness);

	individual_t & selectRandomIndividual(population_t & population, fitness_t sumOfFitness);

	void reproduce(const solver_t & parent1, const solver_t & parent2, solver_t & newIndividual);
	
	void splice(const solver_t & parent1, const solver_t & parent2, solver_t & newIndividual);

	void singleMutation(solver_t & individual);

	solver_t solve();

	void writePopulationToFile(string fileName, const population_t & population);

	bool _compareFunction(const individual_t & i, const individual_t & j);

	const size_t POPULATION_SIZE = 100;

	const fitness_t MIN_WEIGHT = -40;
	const fitness_t MAX_WEIGHT = 40;
	const int PROBABILITY_OF_SINGLE_MUTATION = 20;	// 20%
	const int DEPTH_LIMIT = 1;

	const bool LIMIT_BY_GENERATIONS = false;
	const bool LIMIT_BY_TIME = false;

	const size_t N_GENERATIONS = 100;
	const clock_t TIME_LIMIT = 10 * 60 * 1000;	// 10 minutes

	const bool WRITE_TO_FILE = true;
}
