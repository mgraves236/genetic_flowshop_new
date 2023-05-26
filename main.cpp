#include <iostream>
#include "instance.h"
#include "GeneticAlgorithm.h"
#include "tests.h"

int main() {
//	int n = 5;
//	int m = 3;
//	int iterMax = 100;
//	int totalPopulation = 100; // choose an even number
//	float probabilityCrossover = 1; // 0.7 - 1
//	float probabilityMutation = 0.2; // 0.05 - 0.5
//	int islandNumber = 3;
//	int islandIter = 100;
//	int migratingNumber = (int) totalPopulation / 2;
//	bool tournament = false;
//	int crossover = 2;
//
//	int** jobs = initialize(n, m);
//	printInstance(n, m, jobs);
////	solution genetic = geneticAlgorithm(jobs, n, m, totalPopulation, iterMax, probabilityCrossover, probabilityMutation, tournament, crossover);
////	std::cout << "BEST SCORE:\t" << genetic.objective << '\n';
////	printSchedule(genetic.schedule, jobs, n, m);
////	std::cout << '\n';
//solution geneticIslands = geneticAlgorithmIslands(jobs, n, m, totalPopulation, iterMax, probabilityCrossover, probabilityMutation,
//							islandNumber, islandIter, migratingNumber, tournament, crossover);
//	std::cout << "BEST SCORE:\t" << geneticIslands.objective << '\n';
//	printSchedule(geneticIslands.schedule, jobs, n, m);
	testIter();
	return 0;
}
