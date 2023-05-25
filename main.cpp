#include <iostream>
#include "instance.h"
#include "GeneticAlgorithm.h"

int main() {
	int n = 5;
	int m = 3;
	int iterMax = 1;
	int totalPopulation = 10; // choose an even number
	float probabilityCrossover = 1; // 0.7 - 1
	float probabilityMutation = 0.1; // 0.05 - 5
	int islandNumber = 4;
	int islandIter = 30;
	int migratingNumber = (int) totalPopulation / 2;
	bool tournament = false;

	int** jobs = initialize(n, m);
	printInstance(n, m, jobs);
	solution genetic = geneticAlgorithm(jobs, n, m, totalPopulation, iterMax, probabilityCrossover, probabilityMutation, tournament);
	std::cout << "BEST SCORE:\t" << genetic.objective << '\n';
	printSchedule(genetic.schedule, jobs, n, m);
	std::cout << '\n';
//solution geneticIslands = geneticAlgorithmIslands(jobs, n, m, totalPopulation, iterMax, probabilityCrossover, probabilityMutation,
//							islandNumber, islandIter, migratingNumber, tournament);
//	std::cout << "BEST SCORE:\t" << geneticIslands.objective << '\n';
//	printSchedule(geneticIslands.schedule, jobs, n, m);

	return 0;
}
