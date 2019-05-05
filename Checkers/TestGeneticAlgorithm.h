#pragma once

#include "GeneticAlgorithm.h"

class TestGeneticAlgorithm
{
public:
	TestGeneticAlgorithm();
	~TestGeneticAlgorithm();

	void _generateInitialPopulation();

	void _evaluateFitnessOfPopulation();

	void _produceASingleGeneration();

};

