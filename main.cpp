#include <iostream>
#include "instance.h"
#include "GeneticAlgorithm.h"

int main() {
	int n = 5;
	int m = 3;
	int iterMax = 100;
	int totalPopulation = 4; // choose an even number
	float probabilityCrossover = 1; // 0.7 - 1
	float probabilityMutation = 0.1; // 0.05 - 5
	int islandNumber = 4;
	int islandIter = 2;

	int** jobs = initialize(n, m);
//	printInstance(n, m, jobs);
	solution genetic = geneticAlgorithm(jobs, n, m, totalPopulation, iterMax, probabilityCrossover, probabilityMutation);
	std::cout << "BEST SCORE:\t" << genetic.objective << '\n';
	printSchedule(genetic.schedule, jobs, n, m);

	geneticAlgorithmIslands(jobs, n, m, totalPopulation, iterMax, probabilityCrossover, probabilityMutation, islandNumber, islandIter);

	return 0;
}
