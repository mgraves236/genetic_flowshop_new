#include <iostream>
#include "instance.h"
#include "GeneticAlgorithm.h"

int main() {
	int n = 5;
	int m = 3;
	int iterMax = 1;
	int totalPopulation = 4; // choose an even number
	float probabilityCrossover = 1;

	int** jobs = initialize(n, m);
	printInstance(n, m, jobs);
	solution genetic = geneticAlgorithm(jobs, n, m, totalPopulation, iterMax, probabilityCrossover);

	return 0;
}
