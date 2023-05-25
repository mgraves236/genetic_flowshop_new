#include <iostream>
#include "instance.h"
#include "GeneticAlgorithm.h"

int main() {
	int n = 3;
	int m = 3;
	int iterMax = 2;
	int totalPopulation = 3;
	float probabilityCrossover = 1;

	int** jobs = initialize(n, m);
	printInstance(n, m, jobs);
	solution genetic = geneticAlgorithm(jobs, n, m, totalPopulation, iterMax, probabilityCrossover);

	return 0;
}
