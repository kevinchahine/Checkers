#include "TestGeneticAlgorithm.h"

using namespace GeneticAlgorithm;

TestGeneticAlgorithm::TestGeneticAlgorithm()
{
}

TestGeneticAlgorithm::~TestGeneticAlgorithm()
{
}

void TestGeneticAlgorithm::_generateInitialPopulation()
{
	population_t population(
		GeneticAlgorithm::generateInitialPopulation());

	cout << "population size = " << population.size() << endl;
	for (individual_t individual : population)
	{
		cout << individual.first.toStream().str() << endl;
	}
}

void TestGeneticAlgorithm::_evaluateFitnessOfPopulation()
{
	cout << "Generating population of size "
		<< GeneticAlgorithm::POPULATION_SIZE << "...";
	population_t population =
		GeneticAlgorithm::generateInitialPopulation();
	cout << "done" << endl;

	cout << "evaluate fitness of population...";
	GeneticAlgorithm::evaluateFitnessOfPopulation(population);
	cout << "done" << endl;

	for (individual_t & individual : population)
	{
		cout << individual.first.toStream().str()
			<< "\t fitness = " << individual.second << endl;
	}
}

void TestGeneticAlgorithm::_produceASingleGeneration()
{
	population_t population;
	
	// 1.) Generation the initial population (1st Genteration)
	cout << "Generating initial population. size = "
		<< POPULATION_SIZE << "...";
	population = GeneticAlgorithm::generateInitialPopulation();
	cout << "done" << endl;

	// 2-3.) Evaluate fitness of each individual
		//	 *** THIS FUNCTION WILL TAKE A LONG TIME ***
	cout << "Evaluating fitness of population...";
	int fitnessSum = GeneticAlgorithm::evaluateFitnessOfPopulation(population);
	cout << "done" << endl;

	// 2-4.) Create next generation
	for (size_t i = 0; i < POPULATION_SIZE; i++)
	{
		cout << "Creating generation " << i << "...";

		cout << "\tSelecting 2 individuals to breed" << endl;
		individual_t & parent1 =
			GeneticAlgorithm::selectRandomIndividual(population, fitnessSum);
		cout << "parent1 = " << parent1.first.toStream().str() << endl;
		individual_t & parent2 =
			GeneticAlgorithm::selectRandomIndividual(population, fitnessSum);
		cout << "parent2 = " << parent1.first.toStream().str() << endl;
		individual_t child;

		cout << "\tReproducing " << endl;
		reproduce(
			parent1.first,
			parent2.first,
			child.first);

		cout << "\tDoing single mutation" << endl;
		singleMutation(child.first);
		cout << "done";

		cout << child.first.toStream().str()
			<< "\tfitness = " << child.second << endl;
	}
}
