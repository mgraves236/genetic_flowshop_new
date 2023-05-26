#ifndef GENETIC_FLOWSHOP_NEW_TESTS_H
#define GENETIC_FLOWSHOP_NEW_TESTS_H

#include <iostream>
#include <fstream>
#include <chrono>
#include "instance.h"
#include "GeneticAlgorithm.h"

void testWOIslands() {
	std::fstream file;
	file.open("woIslands.txt", std::ios::out);
//	int n = 5;
	int m = 3;
	int iterMax = 100;
	int totalPopulation = 100; // choose an even number
	float probabilityCrossover = 1; // 0.7 - 1
	float probabilityMutation = 0.2; // 0.05 - 0.5
	int islandNumber = 2;
	int islandIter = 100;
	int migratingNumber = (int) totalPopulation / 2;
	bool tournament = false;
	int crossover = 1;


	for (int n = 3; n < 7; n++) {
		std::cout << "N = \t" << n << '\n';
		file << n << '\t';
		int **jobs = initialize(n, m);
		solution genetic = geneticAlgorithm(jobs, n, m, totalPopulation, iterMax, probabilityCrossover,
											probabilityMutation, tournament, crossover);
		file << genetic.objective << '\t';
		solution geneticIslands = geneticAlgorithmIslands(jobs, n, m, totalPopulation, iterMax, probabilityCrossover,
														  probabilityMutation,
														  islandNumber, islandIter, migratingNumber, tournament,
														  crossover);
		file << geneticIslands.objective << '\n';
	}
	file.close();
}

void testIter() {
	std::fstream file;
	file.open("iter.txt", std::ios::out);
	int n = 20;
	int m = 3;
	int iter = 100;
	int totalPopulation = 100; // choose an even number
	float probabilityCrossover = 0.7; // 0.7 - 1
	float probabilityMutation = 0.3; // 0.05 - 0.5
	bool tournament = false;
	int crossover = 1;

	int iterMax = 1;

	int **jobs = initialize(n, m);

	while (iterMax <= iter) {
		std::cout << "iterMax = \t" << iterMax << '\n';
		file << iterMax << '\t';
		float sum = 0;
//			for (int i = 0; i < 100; i++) {
		solution genetic = geneticAlgorithm(jobs, n, m, totalPopulation, iterMax, probabilityCrossover,
											probabilityMutation, tournament, crossover);

//			sum += genetic.objective;
		file << genetic.objective << '\n';
//			delete[] jobs;
//		}
//		file << sum << '\n';
		iterMax = iterMax + 1;
	}
	file.close();
}


void testTotalPopulation() {
	std::fstream file;
	file.open("population.txt", std::ios::out);
	int n = 10;
	int m = 3;
	int iterMax = 1000;
	int totalPopulationMax =  150; // choose an even number
	float probabilityCrossover = 1; // 0.7 - 1
	float probabilityMutation = 0.2; // 0.05 - 0.5
	bool tournament = false;
	int crossover = 1;

	int totalPopulation = 125;
	int **jobs = initialize(n, m);
	while (totalPopulation <= totalPopulationMax) {
//		std::cout << totalPopulation << '\t';
		printf("%d\t", totalPopulation);
		file << totalPopulation << '\t';
		float sum = 0;
		for (int i = 0; i < 50; i++) {
			solution genetic = geneticAlgorithm(jobs, n, m, totalPopulation, iterMax, probabilityCrossover,
												probabilityMutation, tournament, crossover);

			sum += genetic.objective;

		}

		file << sum / 50 << '\n';
		printf("%f\n", sum / 50);

		totalPopulation = totalPopulation + 5;
	}
	delete[] jobs;

	file.close();
}

void testCrossover() {
	std::fstream file;
	file.open("crossover.txt", std::ios::out);
	int n = 10;
	int m = 3;
	int iterMax = 5120*4;
	int totalPopulation=  5120*2; // choose an even number
	float probabilityCrossover = 0.6; // 0.7 - 1
	float probabilityMutation = 0.2; // 0.05 - 0.5
	bool tournament = false;
	int crossover = 1;

	int totalCrossover = 1;

	while (probabilityCrossover <= totalCrossover) {
		std::cout  << probabilityCrossover << '\t';
		file << probabilityCrossover << '\t';
		float sum = 0;

		for (int i = 0; i < 100; i++) {
			int **jobs = initialize(n, m);
			solution genetic = geneticAlgorithm(jobs, n, m, totalPopulation, iterMax, probabilityCrossover,
												probabilityMutation, tournament, crossover);

			sum += genetic.objective;
			delete[] jobs;

		}
		file << sum / 100 << '\n';
		probabilityCrossover = probabilityCrossover + 0.5;
	}
	file.close();
}


void testMutation() {
	std::fstream file;
	file.open("mutation.txt", std::ios::out);
	int n = 10;
	int m = 3;
	int iterMax = 5120*4;
	int totalPopulation=  5120*2; // choose an even number
	float probabilityCrossover = 0.6; // 0.7 - 1
	float probabilityMutation = 0.05; // 0.05 - 0.5
	bool tournament = false;
	int crossover = 1;

	int totalMutation = 1;

	while (probabilityMutation <= totalMutation) {
		std::cout << probabilityMutation << '\t';
		file << probabilityMutation << '\t';
		float sum = 0;

		for (int i = 0; i < 100; i++) {
			int **jobs = initialize(n, m);
			solution genetic = geneticAlgorithm(jobs, n, m, totalPopulation, iterMax, probabilityCrossover,
												probabilityMutation, tournament, crossover);

			sum += genetic.objective;
			delete[] jobs;

		}
		file << sum / 100 << '\n';
		probabilityMutation = probabilityMutation + 0.05;
	}
	file.close();
}

void testSelectionType() {
	std::fstream file;
	file.open("tournament.txt", std::ios::out);
//	int n = 10;
	int m = 3;
	int iterMax = 5120*4;
	int totalPopulation=  5120*2; // choose an even number
	float probabilityCrossover = 0.6; // 0.7 - 1
	float probabilityMutation = 0.05; // 0.05 - 0.5
	int crossover = 1;



	for (int n = 3; n < 100; n++) {
		std::cout << n << '\t';
		file << n << '\t';
		float sum = 0;
		float sumT = 0;
		for (int i = 0; i < 100; i++) {
			int **jobs = initialize(n, m);

			solution genetic = geneticAlgorithm(jobs, n, m, totalPopulation, iterMax, probabilityCrossover,
												probabilityMutation, false, crossover);

			sum += genetic.objective;
			solution geneticT = geneticAlgorithm(jobs, n, m, totalPopulation, iterMax, probabilityCrossover,
												 probabilityMutation, true, crossover);

			sumT += geneticT.objective;
			delete[] jobs;

		}
		file << sum / 100 << '\t';
		file << sumT / 100 << '\n';
	}
	file.close();
}

void testCrossoverType() {
	std::fstream file;
	file.open("crossoverType.txt", std::ios::out);
//	int n = 10;
	int m = 3;
	int iterMax = 5120*4;
	int totalPopulation=  5120*2; // choose an even number
	float probabilityCrossover = 0.6; // 0.7 - 1
	float probabilityMutation = 0.05; // 0.05 - 0.5
	bool tournament = false;


	for (int n = 3; n < 100; n++) {
		std::cout << n << '\t';
		file << n << '\t';
		float sum = 0;
		float sumT = 0;
		for (int i = 0; i < 100; i++) {
			int **jobs = initialize(n, m);

			solution genetic = geneticAlgorithm(jobs, n, m, totalPopulation, iterMax, probabilityCrossover,
												probabilityMutation, tournament, 1);

			sum += genetic.objective;
			solution geneticT = geneticAlgorithm(jobs, n, m, totalPopulation, iterMax, probabilityCrossover,
												 probabilityMutation, tournament, 2);

			sumT += geneticT.objective;
			delete[] jobs;

		}
		file << sum / 100 << '\t';
		file << sumT / 100 << '\n';
	}
	file.close();
}

void testIslandNumber() {
	std::fstream file;
	file.open("islandNumber.txt", std::ios::out);
//	int n = 5;
	int m = 3;
	int iterMax = 100;
	int totalPopulation = 100; // choose an even number
	float probabilityCrossover = 1; // 0.7 - 1
	float probabilityMutation = 0.2; // 0.05 - 0.5
	int islandNumber = 2;
	int islandIter = 100;
	int migratingNumber = (int) totalPopulation / 2;
	bool tournament = false;
	int crossover = 1;


	for (int n = 3; n < 20; n++) {
		std::cout  << n << '\t';
		file << n << '\t';
		int **jobs = initialize(n, m);
		solution geneticIslands = geneticAlgorithmIslands(jobs, n, m, totalPopulation, iterMax, probabilityCrossover,
														  probabilityMutation,
														  1, islandIter, migratingNumber, tournament,
														  crossover);
		file << geneticIslands.objective << '\n';

		geneticIslands = geneticAlgorithmIslands(jobs, n, m, totalPopulation, iterMax, probabilityCrossover,
												 probabilityMutation,
												 2, islandIter, migratingNumber, tournament,
												 crossover);
		file << geneticIslands.objective << '\n';

		geneticIslands = geneticAlgorithmIslands(jobs, n, m, totalPopulation, iterMax, probabilityCrossover,
												 probabilityMutation,
												 3, islandIter, migratingNumber, tournament,
												 crossover);
		file << geneticIslands.objective << '\n';
		delete[] jobs;

	}
	file.close();
}

void testIslandIter() {
	std::fstream file;
	file.open("islandIter.txt", std::ios::out);
	int n = 10;
	int m = 3;
	int iterMax = 100;
	int totalPopulation = 100; // choose an even number
	float probabilityCrossover = 1; // 0.7 - 1
	float probabilityMutation = 0.2; // 0.05 - 0.5
	int islandNumber = 2;
	int islandIter = 100;
	int migratingNumber = (int) totalPopulation / 2;
	bool tournament = false;
	int crossover = 1;

	int iter = 1280;
	while (islandIter <= iter) {
		std::cout << iterMax << '\t';
		file << iterMax << '\t';
		int sum = 0;

		for (int i = 0; i < 100; i++) {
			int **jobs = initialize(n, m);
			solution genetic = geneticAlgorithm(jobs, n, m, totalPopulation, iterMax, probabilityCrossover,
												probabilityMutation, tournament, crossover);

			sum += genetic.objective;
			delete[] jobs;
		}
		file << sum / 100 << '\n';
		islandIter = 2 * islandIter;

	}
	file.close();
}

void testIslandMigration() {
	std::fstream file;
	file.open("islandMigration.txt", std::ios::out);
	int n = 5;
	int m = 3;
	int iterMax = 100;
	int totalPopulation = 100; // choose an even number
	float probabilityCrossover = 1; // 0.7 - 1
	float probabilityMutation = 0.2; // 0.05 - 0.5
	int islandNumber = 2;
	int islandIter = 100;
	int migratingNumber = 10;
	bool tournament = false;
	int crossover = 1;

	int iter = totalPopulation / 2;
	while (migratingNumber <= iter) {
		std::cout << migratingNumber << '\t';
		file << iterMax << '\t';
		int sum = 0;

		for (int i = 0; i < 100; i++) {
			int **jobs = initialize(n, m);
			solution genetic = geneticAlgorithm(jobs, n, m, totalPopulation, iterMax, probabilityCrossover,
												probabilityMutation, tournament, crossover);

			sum += genetic.objective;
			delete[] jobs;

		}
		file << sum / 100 << '\n';
		migratingNumber = migratingNumber + 1;
	}
	file.close();
}
#endif //GENETIC_FLOWSHOP_NEW_TESTS_H
