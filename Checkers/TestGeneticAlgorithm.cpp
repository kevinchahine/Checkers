#include "TestGeneticAlgorithm.h"



TestGeneticAlgorithm::TestGeneticAlgorithm()
{
}


TestGeneticAlgorithm::~TestGeneticAlgorithm()
{
}

void TestGeneticAlgorithm::test()
{
	vector<pair<Solver1, int>> population(
		GeneticAlgorithm::generateInitialPopulation());

	cout << "population size = " << population.size() << endl;
	for (pair<Solver1, int> individual : population)
	{
		cout << individual.first.toStream().str() << endl;
	}
}
