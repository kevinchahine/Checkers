#include "GeneticAlgorithm.h"

using namespace GeneticAlgorithm;

population_t GeneticAlgorithm::generateInitialPopulation()
{
	population_t population;

	population.reserve(POPULATION_SIZE);

	uniform_real_distribution<fitness_t> dist(MIN_WEIGHT, MAX_WEIGHT);

	for (size_t i = 0; i < population.capacity(); i++)
	{
		// Create a 1-ply solver 
		solver_t solver(DEPTH_LIMIT);

		for (size_t j = 0; j < solver.N_WEIGHTS; j++)
		{
			solver.weights[j] = (int) dist(generator);
		}

		population.push_back(individual_t(solver, 0));
	}

	return population;
}

int GeneticAlgorithm::evaluateFitnessOfPopulation(population_t & population)
{
	// To evaluate the fitness of each individual in the population
	// we need to play them against each other and count their wins
	size_t popSize = population.size();

	// Clear fitness values
	for (size_t i = 0; i < popSize; i++)
	{
		population[i].second = 0;
	}

	// Play each solver against all OTHER solvers twice
	// (once as black, once as red)
	// and count their wins and loses
	// Wins count as +1 point loses count as -1 point
	for (size_t player1 = 0; player1 < popSize; player1++)
	{
		for (size_t player2 = 0; player2 < popSize; player2++)
		{
			if (player1 != player2)
			{
				solver_t & blackSolver = population[player1].first;
				solver_t & redSolver = population[player2].first;

				CheckersManager game;
				game.play(blackSolver, redSolver, false);
				
				switch (game.status())
				{
				case Checkers::BLACK_WINS:
					///cout << "Black Wins" << endl;
					///cout << "B";
					//population[player1].second++;
					//population[player2].second--;
					population[player1].second += 2;
					population[player2].second += 0;
					break;
				case Checkers::RED_WINS:
					///cout << "Red Wins" << endl;
					///cout << "R";
					//population[player1].second--;
					//population[player2].second++;
					population[player1].second += 0;
					population[player2].second += 2;
					break;
				case Checkers::DRAW:
					///cout << "Draw" << endl;
					///cout << "D";
					population[player1].second += 1;
					population[player2].second += 1;
					break;
				}
			} // end if (player1 != player2)
		} // end for (size_t player2 = player1 + 1; 
	} // end for (size_t player1 = 0;

	// Calculate the sum of all fitness values
	int fitnessSum = 0;
	for (size_t i = 0; i < popSize; i++)
	{
		fitnessSum += (int) population[i].second;
	}

	return fitnessSum;
}

void GeneticAlgorithm::sortAndScale(population_t & population, fitness_t sumOfFitness)
{
	// 1.) Normalize fitness scores
	//		Divide the current fitness score of each individual
	//		by the sum of all fitness scores
	//		The sum of all normalized fitness scores should equal 1 (or 100%)
	for (individual_t & i : population)
	{
		i.second /= sumOfFitness;
	}

	// 2.) Sort population in decending order
	sort(population.begin(), population.end(), GeneticAlgorithm::_compareFunction);
	
	// 3.) Accumulate normalized fitness values
	//		Take each fitness score starting with the 1st one (which 
	//		should be the greatest) and add up the fitness scores
	//		of the previous individuals.
	//		ex: let f be the array of all fitness scores
	//			f[i] = f[0] + f[1] + ... + f[i + 1]
	//		ex: (As an recursive function)
	//			f[i] = f[i - 1]	where size > i >= 1
	//		Note: The value of the final fitness score should be 1
	for (size_t i = 1; i < POPULATION_SIZE; i++)
	{
		population[i].second += population[i - 1].second;
	}

	// -.) After function return call selectRandomIndividual()
	//		to select the parents of the next child
}

individual_t & GeneticAlgorithm::selectRandomIndividual(population_t & population, fitness_t sumOfFitness)
{
	// 4.) Choose a random number r between 0 and 1
	uniform_real_distribution<fitness_t> dist(0.0, 1.0);
	fitness_t r = dist(generator);
	
	// 5.) Choose the individual whose fitness score is 

	for (size_t i = 0; i < population.size(); i++)
	{
		if (r < population[i].second)
		{
			return population[i];
		}
	}

	cerr << "Error: " << __FILE__ << " line " << __LINE__
		<< " a random individual could not be chosen" << endl
		<< "r = " << r << " sumOfFitness = " << sumOfFitness << endl;

	return population.back();	// return last value as a bluff
}

void GeneticAlgorithm::reproduce(const solver_t & parent1, const solver_t & parent2, solver_t & newIndividual)
{
	splice(parent1, parent2, newIndividual);

	singleMutation(newIndividual);
}

void GeneticAlgorithm::splice(const solver_t & parent1, const solver_t & parent2, solver_t & newIndividual)
{
	// Where should we perform the splice?
	uniform_real_distribution<fitness_t> dist1(0, solver_t::N_WEIGHTS - 1);
	int crossOverPoint = (int) dist1(generator);

	// Copy values from parent1 in the range [0, crossOverPoint)
	for (size_t i = 0; i < crossOverPoint; i++)
	{
		newIndividual.weights[i] = parent1.weights[i];
	}

	// Copy value fromparent2 in the range [crossOverPoint, N_WEIGHTS)
	for (size_t i = crossOverPoint; i < solver_t::N_WEIGHTS; i++)
	{
		newIndividual.weights[i] = parent2.weights[i];
	}
}

void GeneticAlgorithm::singleMutation(solver_t & individual)
{
	// Should we perform a mutation?
	uniform_int_distribution<int> dist1(0, 100);
	int probabilityOfMutation = dist1(generator);
	if (probabilityOfMutation < PROBABILITY_OF_SINGLE_MUTATION)
	{
		// Yes. Which value should we mutate
		uniform_int_distribution<int> dist2(0, solver_t::N_WEIGHTS - 1);
		int index = dist2(generator);

		// What value should we change it to?
		uniform_int_distribution<int> dist3(MIN_WEIGHT, MAX_WEIGHT);
		int newValue = dist3(generator);

		// Mutate the value
		individual.weights[index] = newValue;
	}
}

solver_t GeneticAlgorithm::solve()
{
	population_t population;
	population_t newPopulation;
	int fitnessSum = 0;

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
		cout << "Generation: " << generationNumber << endl;

		// 2-3.) Evaluate fitness of each individual
		//	 *** THIS FUNCTION WILL TAKE A LONG TIME ***
		cout << "\tEvaluating Fitness Of Population..." << endl;
		fitnessSum = evaluateFitnessOfPopulation(population);
		for (const individual_t & i : population)
		{
			cout << '\t' << left << setw(10) << i.second
				<< i.first.toStream().str() << endl;
		}
		sortAndScale(population, fitnessSum);
		
		// 2-4.) Write population to file
		if (WRITE_TO_FILE)
		{
			stringstream filename;
			
			filename << "GA Generation " << generationNumber << ".txt";

			writePopulationToFile(filename.str(), population);
		}

		// 2-4.) Create next generation
		cout << "\tCreating Next Generation" << endl;
		for (size_t i = 0; i < POPULATION_SIZE; i++)
		{
			individual_t & parent1 =
				selectRandomIndividual(population, fitnessSum);
			individual_t & parent2 =
				selectRandomIndividual(population, fitnessSum);

			reproduce(parent1.first, parent2.first, newPopulation[i].first);

			singleMutation(newPopulation[i].first);

			cout << "\t\t" << population[i].second << endl;
		}
		cout << "done" << endl;

		// 2-5.) Copy the new population over the old one
		for (size_t i = 0; i < POPULATION_SIZE; i++)
		{
			population.at(i).first = newPopulation.at(i).first;
			population.at(i).second = newPopulation.at(i).second;
		}
		
		// now population contains the new individuals
		// WARNING: population does not have valid fitness values

		// 2- .) Increment generation number
		generationNumber++;
	} // end while (true)

	// 3.) Evaluate the fitness of the most recent generation
	//	 *** THIS FUNCTION WILL TAKE A LONG TIME ***
	fitnessSum = evaluateFitnessOfPopulation(population);

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

void GeneticAlgorithm::writePopulationToFile(string fileName, const population_t & population)
{
	static clock_t prevWriteTime = 0;

	ofstream outFile(fileName);

	cout << "Opening file...";
	while (!outFile);
	cout << "done" << endl;

	outFile << "duration = "
		<< (clock() - prevWriteTime) / 1000.0 << " mSec"
		<< endl;

	prevWriteTime = clock();

	for (const individual_t & i : population)
	{
		outFile 
			<< setprecision(5)
			<< setw(9)
			<< "fitness = "
			<< i.second
			<< "\t"
			<< i.first.toStream().str()
			<< endl;
	}

	outFile.close();
}

bool GeneticAlgorithm::_compareFunction(const individual_t & i, const individual_t & j)
{
	return i.second > j.second;
}
