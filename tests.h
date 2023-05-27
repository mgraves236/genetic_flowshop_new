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
	int totalPopulation = 3; // choose an even number
	float probabilityCrossover = 0.78; // 0.7 - 1
	float probabilityMutation = 0.4; // 0.05 - 0.5
	int islandNumber = 3;
	int islandIter = 15;
	int migratingNumber = 2;
	bool tournament = true;
	int crossover = 1;

	int n = 200;
	while (n <= 500) {
		std::cout << n << '\t';
		file << n << '\t';
		int **jobs = initialize(n, m);
		float sum = 0;
		float sumT = 0;

		for (int i = 0; i < 100; i++) {
			solution genetic = geneticAlgorithm(jobs, n, m, totalPopulation, iterMax, probabilityCrossover,
												probabilityMutation, tournament, crossover);
			sum += (float) genetic.objective;
			solution geneticIslands = geneticAlgorithmIslands(jobs, n, m, totalPopulation, 10, probabilityCrossover,
															  probabilityMutation,
															  islandNumber, islandIter, migratingNumber, tournament,
															  crossover);
			sumT += (float) geneticIslands.objective;
		}
		file << sum / 100 << '\t';
		std::cout << sum / 100 << '\t';
		file << sumT / 100 << '\n';
		std::cout << sumT / 100 << '\n';
		delete[] jobs;
		n = n + 100;

	}
	std::cout << "FINISHED\n";
	file.close();
}

void testWOIslandsTime() {
	std::fstream file;
	file.open("woIslandsTime.txt", std::ios::out);
//	int n = 5;
	int m = 3;
	int iterMax = 100;
	int totalPopulation = 3; // choose an even number
	float probabilityCrossover = 0.78; // 0.7 - 1
	float probabilityMutation = 0.4; // 0.05 - 0.5
	int islandNumber = 3;
	int islandIter = 15;
	int migratingNumber = 2;
	bool tournament = true;
	int crossover = 1;
	float sum = 0;
	float sumTime = 0;
	float sumT = 0;
	float sumTTime = 0;
	int n = 503;
	while (n <= 803) {
		std::cout << n << '\t';
		file << n << '\t';
		int **jobs = initialize(n, m);
		for (int i = 0; i < 20; i++ ) {
			auto start = std::chrono::high_resolution_clock::now();
			solution genetic = geneticAlgorithm(jobs, n, m, totalPopulation, iterMax, probabilityCrossover,
												probabilityMutation, tournament, crossover);
			auto stop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
			sum += genetic.objective;
			sumTime += duration.count();


			start = std::chrono::high_resolution_clock::now();
			solution geneticIslands = geneticAlgorithmIslands(jobs, n, m, totalPopulation, 10, probabilityCrossover,
															  probabilityMutation,
															  islandNumber, islandIter, migratingNumber, tournament,
															  crossover);
			stop = std::chrono::high_resolution_clock::now();
			duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
			sumT += geneticIslands.objective;
			sumTTime += duration.count();
		}
		file << sum / 20 << '\t';
		file << sumTime / 20 << '\t';
		std::cout << sum / 20 << '\t';
		std::cout << sumTime / 20 << '\t';
		file << sumT / 20 << '\t';
		file << sumTTime / 20 << '\t';
		std::cout << sumT / 20 << '\t';
		std::cout << sumTTime / 20 << '\n';
		delete[] jobs;
		n = n + 50;
	}
	std::cout << "FINISHED\n";
	file.close();
}

void testIter() {
	std::fstream file;
	file.open("itern50.txt", std::ios::out);
	int n = 150;
	int m = 10;
	int iter = 100;
	int totalPopulation = 3; // choose an even number
	float probabilityCrossover = 0.7; // 0.7 - 1
	float probabilityMutation = 0.3; // 0.05 - 0.5
	bool tournament = false;
	int crossover = 1;

	int iterMax = 1;

	int **jobs = initialize(n, m);

	while (iterMax <= iter) {
		std::cout << iterMax << '\t';
		file << iterMax << '\t';
		float sum = 0;
		for (int i = 0; i < 100; i++) {
			solution genetic = geneticAlgorithm(jobs, n, m, totalPopulation, iterMax, probabilityCrossover,
												probabilityMutation, tournament, crossover);

			sum += genetic.objective;
		}
		file << sum / 100 << '\n';
		std::cout << sum / 100 << '\n';
		iterMax = iterMax + 1;
	}
	delete[] jobs;

	file.close();
}


void testTotalPopulation() {
	std::fstream file;
	file.open("population2.txt", std::ios::out);
	int n = 10;
	int m = 3;
	int iterMax = 100;
	int totalPopulationMax = 100; // choose an even number
	float probabilityCrossover = 0.7; // 0.7 - 1
	float probabilityMutation = 0.3; // 0.05 - 0.5
	bool tournament = false;
	int crossover = 1;

	int totalPopulation = 5;
	int **jobs = initialize(n, m);
	while (totalPopulation <= totalPopulationMax) {
//		std::cout << totalPopulation << '\t';
		printf("%d\t", totalPopulation);
		file << totalPopulation << '\t';
		float sum = 0;
		for (int i = 0; i < 100; i++) {
			solution genetic = geneticAlgorithm(jobs, n, m, totalPopulation, iterMax, probabilityCrossover,
												probabilityMutation, tournament, crossover);

			sum += genetic.objective;

		}

		file << sum / 100 << '\n';
		printf("%f\n", sum / 100);

		totalPopulation = totalPopulation + 5;
	}
	delete[] jobs;

	file.close();
}

void testCrossover() {
	std::fstream file;
	file.open("crossoverp50.txt", std::ios::out);
	int n = 10;
	int m = 3;
	int iterMax = 5;
	int totalPopulation = 50; // choose an even number
	float probabilityCrossover = 0.1; // 0.7 - 1
	float probabilityMutation = 0.2; // 0.05 - 0.5
	bool tournament = false;
	int crossover = 1;

	float totalCrossover = 1;

	int **jobs = initialize(n, m);

	while (probabilityCrossover <= totalCrossover) {
		std::cout << probabilityCrossover << '\t';
		file << probabilityCrossover << '\t';
		float sum = 0;

		for (int i = 0; i < 1000; i++) {
			solution genetic = geneticAlgorithm(jobs, n, m, totalPopulation, iterMax, probabilityCrossover,
												probabilityMutation, tournament, crossover);

			sum += genetic.objective;

		}
		file << sum / 1000 << '\n';
		printf("%f\n", sum / 1000);
		probabilityCrossover = probabilityCrossover + 0.05;
	}
	delete[] jobs;

	file.close();
}


void testMutation() {
	std::fstream file;
	file.open("mutation.txt", std::ios::out);
	int n = 10;
	int m = 3;
	int iterMax = 100;
	int totalPopulation = 3; // choose an even number
	float probabilityCrossover = 0.78; // 0.7 - 1
	float probabilityMutation = 1.0; // 0.05 - 0.5
	bool tournament = false;
	int crossover = 1;

	float totalMutation = 1;

	int **jobs = initialize(n, m);

//	while (probabilityMutation <= totalMutation) {
	std::cout << probabilityMutation << '\t';
	file << probabilityMutation << '\t';
	float sum = 0;

	for (int i = 0; i < 1000; i++) {
		solution genetic = geneticAlgorithm(jobs, n, m, totalPopulation, iterMax, probabilityCrossover,
											probabilityMutation, tournament, crossover);

		sum += genetic.objective;

	}
	file << sum / 1000 << '\n';
	std::cout << sum / 1000 << '\n';
	probabilityMutation = probabilityMutation + 0.05;
//	}
	delete[] jobs;

	file.close();
}

void testSelectionType() {
	std::fstream file;
	file.open("tournament.txt", std::ios::out);
//	int n = 10;
	int m = 3;
	int iterMax = 100;
	int totalPopulation = 3; // choose an even number
	float probabilityCrossover = 0.78; // 0.7 - 1
	float probabilityMutation = 0.4; // 0.05 - 0.5
	int crossover = 1;


	for (int n = 30; n < 41; n++) {
		std::cout << n << '\t';
		file << n << '\t';
		float sum = 0;
		float sumT = 0;
		int **jobs = initialize(n, m);

		for (int i = 0; i < 100; i++) {

			solution genetic = geneticAlgorithm(jobs, n, m, totalPopulation, iterMax, probabilityCrossover,
												probabilityMutation, false, crossover);

			sum += genetic.objective;
			solution geneticT = geneticAlgorithm(jobs, n, m, totalPopulation, iterMax, probabilityCrossover,
												 probabilityMutation, true, crossover);

			sumT += geneticT.objective;

		}
		delete[] jobs;

		file << sum / 100 << '\t';
		std::cout << sum / 100 << '\t';
		file << sumT / 100 << '\n';
		std::cout << sumT / 100 << '\n';
	}
	file.close();
}

void testCrossoverType() {
	std::fstream file;
	file.open("crossoverType.txt", std::ios::out);
//	int n = 10;
	int m = 3;
	int iterMax = 100;
	int totalPopulation = 3; // choose an even number
	float probabilityCrossover = 0.78; // 0.7 - 1
	float probabilityMutation = 0.4; // 0.05 - 0.5
	bool tournament = true;


	for (int n = 10; n < 16; n++) {
		std::cout << n << '\t';
		file << n << '\t';
		float sum = 0;
		float sumT = 0;
		int **jobs = initialize(n, m);

		for (int i = 0; i < 100; i++) {

			solution genetic = geneticAlgorithm(jobs, n, m, totalPopulation, iterMax, probabilityCrossover,
												probabilityMutation, tournament, 1);

			sum += genetic.objective;
			solution geneticT = geneticAlgorithm(jobs, n, m, totalPopulation, iterMax, probabilityCrossover,
												 probabilityMutation, tournament, 2);

			sumT += geneticT.objective;
		}
		delete[] jobs;
		file << sum / 100 << '\t';
		std::cout << sum / 100 << '\t';
		file << sumT / 100 << '\n';
		std::cout << sumT / 100 << '\n';
	}
	file.close();
}

void testIslandNumber() {
	std::fstream file;
	file.open("islandNumber.txt", std::ios::out);
//	int n = 5;
	int m = 3;
	int iterMax = 100;
	int totalPopulation = 3; // choose an even number
	float probabilityCrossover = 0.78; // 0.7 - 1
	float probabilityMutation = 0.4; // 0.05 - 0.5
	int islandNumber = 2;
	int islandIter = 10;
	int migratingNumber = (int) totalPopulation / 3;
	bool tournament = true;
	int crossover = 1;

	int n = 4;
//	for (int n = 3; n < 21; n++) {
	std::cout << n << '\t';
	file << n << '\t';
	int **jobs = initialize(n, m);

	solution geneticIslands = geneticAlgorithmIslands(jobs, n, m, totalPopulation, iterMax, probabilityCrossover,
													  probabilityMutation,
													  2, islandIter, migratingNumber, tournament,
													  crossover);
	file << geneticIslands.objective << '\t';
	std::cout << geneticIslands.objective << '\t';

	geneticIslands = geneticAlgorithmIslands(jobs, n, m, totalPopulation, iterMax, probabilityCrossover,
											 probabilityMutation,
											 3, islandIter, migratingNumber, tournament,
											 crossover);
	file << geneticIslands.objective << '\t';

	std::cout << geneticIslands.objective << '\n';
	delete[] jobs;

//	}
	file.close();
}

void testIslandIter() {
	std::fstream file;
	file.open("islandIter.txt", std::ios::out);
	int n = 10;
	int m = 3;
	int iterMax = 10;
	int totalPopulation = 3; // choose an even number
	float probabilityCrossover = 0.78; // 0.7 - 1
	float probabilityMutation = 0.4; // 0.05 - 0.5
	int islandNumber = 3;
	int islandIter = 10;
	int migratingNumber = (int) totalPopulation / 3;
	bool tournament = true;
	int crossover = 1;

	int iter = 15;
	int **jobs = initialize(n, m);
//	islandIter = 1;
	while (islandIter <= iter) {
		std::cout << islandIter << '\t';
		file << islandIter << '\t';
		int sum = 0;

		for (int i = 0; i < 100; i++) {
			solution genetic = geneticAlgorithmIslands(jobs, n, m, totalPopulation, iterMax, probabilityCrossover,
													   probabilityMutation,
													   islandNumber, islandIter, migratingNumber, tournament,
													   crossover);

			sum += genetic.objective;
		}
		file << sum / 100 << '\n';
		std::cout << sum / 100 << '\n';
		islandIter = islandIter + 1;

	}
	delete[] jobs;

	file.close();
}

void testIslandMigration() {
	std::fstream file;
	file.open("islandMigration.txt", std::ios::out);
	int n = 10;
	int m = 3;
	int iterMax = 10;
	int totalPopulation = 10; // choose an even number
	float probabilityCrossover = 0.78; // 0.7 - 1
	float probabilityMutation = 0.4; // 0.05 - 0.5
	int islandNumber = 3;
	int islandIter = 6;
	int migratingNumber = 1;
	bool tournament = true;
	int crossover = 1;

	int iter = totalPopulation;
	int **jobs = initialize(n, m);

	while (migratingNumber <= iter) {
		std::cout << migratingNumber << '\t';
		file << iterMax << '\t';
		int sum = 0;

		for (int i = 0; i < 100; i++) {
			solution genetic = geneticAlgorithmIslands(jobs, n, m, totalPopulation, iterMax, probabilityCrossover,
													   probabilityMutation,
													   islandNumber, islandIter, migratingNumber, tournament,
													   crossover);

			sum += genetic.objective;

		}
		file << sum / 100 << '\n';
		std::cout << sum / 100 << '\n';
		migratingNumber = migratingNumber + 1;
	}
	delete[] jobs;

	file.close();
}

#endif //GENETIC_FLOWSHOP_NEW_TESTS_H
