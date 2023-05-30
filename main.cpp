#include <iostream>
#include <conio.h>
#include "instance.h"
#include "GeneticAlgorithm.h"
#include "tests.h"

int main() {
	int n = 115;
	int m = 3;
	int iterMax = 100;
	int totalPopulation = 3; // choose an even number
	float probabilityCrossover = 0.78; // 0.7 - 1
	float probabilityMutation = 0.4; // 0.05 - 0.5
	int islandNumber = 3;
	int islandIter = 6;
	int migratingNumber = (int) totalPopulation / 3;
	bool tournament = true;
	int crossover = 1;

	int** jobs = initialize(n, m);
	std::cout << n << '\t';
//	printInstance(n, m, jobs);
	solution genetic = geneticAlgorithm(jobs, n, m, totalPopulation, iterMax, probabilityCrossover, probabilityMutation, tournament, crossover);
//	std::cout << "BEST SCORE:\t" << genetic.objective << '\n';
	std::cout << genetic.objective << '\t';

//	printSchedule(genetic.schedule, jobs, n, m);
//	std::cout << '\n';
	solution geneticIslands = geneticAlgorithmIslands(jobs, n, m, totalPopulation, iterMax, probabilityCrossover, probabilityMutation,
							islandNumber, islandIter, migratingNumber, tournament, crossover);
//	std::cout << "BEST SCORE:\t" << geneticIslands.objective << '\n';
	std::cout << geneticIslands.objective << '\n';

	printSchedule(geneticIslands.schedule, jobs, n, m);
	getch();
	return 0;
}
