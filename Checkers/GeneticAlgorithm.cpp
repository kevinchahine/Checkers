#include "GeneticAlgorithm.h"

vector<pair<Solver1, int>> GeneticAlgorithm::generateInitialPopulation()
{
	vector<pair<Solver1, int>> population;

	population.reserve(POPULATION_SIZE);

	uniform_int_distribution<int> dist(-40, 40);

	for (size_t i = 0; i < population.capacity(); i++)
	{
		Solver1 solver;

		for (size_t j = 0; j < solver.N_WEIGHTS; j++)
		{
			solver.weights[j] = dist(generator);
		}

		population.push_back(pair<Solver1, int>(solver, 0));
	}

	return population;
}

int GeneticAlgorithm::evaluateFitnessOfPopulation(vector<pair<Solver1, int>>& population)
{
	// To evaluate the fitness of each individual in the population
	// we need to play them against each other and count their wins
	size_t popSize = population.size();

	// Clear fitness values
	for (size_t i = 0; i < popSize; i++)
	{
		population[i].second = 0;
	}

	// Play each solver against all other solvers and count their wins and losses
	for (size_t player1 = 0; player1 = popSize; player1++)
	{
		for (size_t player2 = 0; player2 < popSize; player2++)
		{
			if (player1 != player2)
			{
				Solver1 & blackSolver = population[player1].first;
				Solver1 & redSolver = population[player2].first;

				CheckersManager game;
				game.playComputerVsComputer(blackSolver, redSolver);

				switch (game.status())
				{
				case Checkers::BLACK_WINS:
					population[player1].second++;
					population[player2].second--;
				case Checkers::RED_WINS:
					population[player1].second--;
					population[player2].second++;
				}
			}
		}
	}

	// Calculate the sum of all fitness values
	int fitnessSum = 0;
	for (size_t i = 0; i < popSize; i++)
	{
		fitnessSum += population[i].second;
	}

	return fitnessSum;
}

pair<Solver1, int> & GeneticAlgorithm::selectRandomIndividual(vector<pair<Solver1, int>>& population, int sumOfFitness)
{
	uniform_int_distribution<int> dist(0, sumOfFitness);
	int r = dist(generator);

	int temp = 0;
	for (size_t i = 0; i < population.size(); i++)
	{
		temp += population[i].second;

		if (r < temp)
			return population[i];
	}

	return population[0];
}

void GeneticAlgorithm::reproduce(const Solver1 & parent1, const Solver1 & parent2, Solver1 & newIndividual)
{
	splice(parent1, parent2, newIndividual);

	singleMutation(newIndividual);
}

void GeneticAlgorithm::splice(const Solver1 & parent1, const Solver1 & parent2, Solver1 & newIndividual)
{
	// Where should we perform the splice?
	uniform_int_distribution<int> dist1(0, Solver1::N_WEIGHTS - 1);
	int crossOverPoint = dist1(generator);

	// Copy values from parent1 in the range [0, crossOverPoint)
	for (size_t i = 0; i < crossOverPoint; i++)
	{
		newIndividual.weights[i] = parent1.weights[i];
	}

	// Copy value fromparent2 in the range [crossOverPoint, N_WEIGHTS)
	for (size_t i = crossOverPoint; i < Solver1::N_WEIGHTS; i++)
	{
		newIndividual.weights[i] = parent2.weights[i];
	}
}

void GeneticAlgorithm::singleMutation(Solver1 & individual)
{
	// Should we perform a mutation?
	uniform_int_distribution<int> dist1(0, 100);
	int probabilityOfMutation = dist1(generator);
	if (probabilityOfMutation < 20)
	{
		// Yes. Which value should we mutate
		uniform_int_distribution<int> dist2(0, Solver1::N_WEIGHTS - 1);
		int index = dist2(generator);

		// What value should we mutate it to?
		uniform_int_distribution<int> dist3(-40, 40);
		int newValue = dist3(generator);

		// Mutate the value
		individual.weights[index] = newValue;
	}
}

Solver1 GeneticAlgorithm::solve()
{
	vector<pair<Solver1, int>> population;
	vector<pair<Solver1, int>> newPopulation;

	// 1.) Generation the initial population (1st Genteration)
	population = generateInitialPopulation();
	newPopulation.resize(POPULATION_SIZE);

	// 2.) Train until limit is reached
	size_t generationNumber = 1;
	while (true)
	{
		// 2-1.) Test break case
		if ((LIMIT_BY_GENERATIONS && generationNumber >= N_GENERATIONS) ||
			(LIMIT_BY_TIME && clock() >= TIME_LIMIT))
			break;

		// 2-2.)
		cout << "Generation " << generationNumber << endl;

		// 2-3.) Evaluate fitness of each individual
		//	 *** THIS FUNCTION WILL TAKE A LONG TIME ***
		int fitnessSum = evaluateFitnessOfPopulation(population);

		// 2-4.) Create next generation
		for (size_t i = 0; i < POPULATION_SIZE; i++)
		{
			pair<Solver1, int> & parent1 =
				selectRandomIndividual(population, fitnessSum);
			pair<Solver1, int> & parent2 =
				selectRandomIndividual(population, fitnessSum);

			reproduce(parent1.first, parent2.first, newPopulation[i].first);

			singleMutation(newPopulation[i].first);
		}

		// 2-5.) Copy the new population over the old one
		swap(population, newPopulation);
		// now population contains the new individuals
		// WARNING: population does not have valid fitness values

		// 2- .) Increment generation number
		generationNumber++;
	} // end while (true)

	// 3.) Evaluate the fitness of the most recent generation
	//	 *** THIS FUNCTION WILL TAKE A LONG TIME ***
	int fitnessSum = evaluateFitnessOfPopulation(population);

	// 3.) Return individual with the best fitness 
	size_t indexOfBest = 0;
	for (size_t i = 0; i < population.size(); i++)
	{
		if (population[i].second > population[indexOfBest].second)
		{
			indexOfBest = i;
		}
	}

	return population[indexOfBest].first;
}
