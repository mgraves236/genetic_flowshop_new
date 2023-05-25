#ifndef GENETIC_FLOWSHOP_GENETICALGORITHM_H
#define GENETIC_FLOWSHOP_GENETICALGORITHM_H

#include "RandomNumberGenerator.h"
#include "Population.h"
#include <thread>

RandomNumberGenerator random2 = RandomNumberGenerator(65765295);

struct solution {
	std::vector<int> schedule;
	int objective;
};

solution geneticAlgorithm(int **matrix, int n, int m, int p, int iterMax, float probabilityCrossover,
						  float probabilityMutation, bool tournament) {
	// initialize populations
	Population population(p, n, m, matrix);
	population.findBest();

	int iter = 0;
	while (iter < iterMax) {
		Population childPopulation;
		while (childPopulation.p < population.p) {
			int parentA = population.findParentWheel();
			int parentB = population.findParentWheel();

			while (parentB == parentA) {
				parentB = population.findParentWheel();
			}

			// perform crossover with probability
			float r = random2.nextFloat(0.0, 1.0);
			if (r <= probabilityCrossover) {
				std::pair<Chromosome, Chromosome> children = Chromosome::onePointCrossover(
						population.specimen[parentA], population.specimen[parentB]);
				childPopulation.specimen.push_back(children.first);
				childPopulation.p = childPopulation.p + 1;
				childPopulation.specimen.push_back(children.second);
				childPopulation.p = childPopulation.p + 1;

			} else if (r < 0.5) {
				Chromosome specimen;
				specimen.copy(population.specimen[parentA]);
				childPopulation.specimen.push_back(specimen);
				childPopulation.p = childPopulation.p + 1;
			} else {
				Chromosome specimen;
				specimen.copy(population.specimen[parentB]);
				childPopulation.specimen.push_back(specimen);
				childPopulation.p = childPopulation.p + 1;
			}
		} // children generated
		for (int i = 0; i < childPopulation.p; i++) {
			childPopulation.specimen[i].setScore(matrix, n, m);
		}
		childPopulation.findBest();
		// mutation
		for (int i = 0; i < childPopulation.p; i++) {
			float r = random2.nextFloat(0.0, 1.0);
			if (r <= probabilityMutation) {
				childPopulation.specimen[i].mutate();
				childPopulation.specimen[i].setScore(matrix, n, m);
			}
		}
		childPopulation.findBest();
		population.copy(childPopulation);
//		std::cout << "ITERATION:\t" << iter << "\t BEST SCORE: \t" << population.bestScore << '\n';
		iter++;
	}
	int index = 0;
	for (int i = 0; i < population.p; i++) {
		if (population.specimen[i].fitness == population.bestScore) {
			index = i;
			break;
		}
	}
	solution result;
	result.schedule = population.specimen[index].genotype;
	result.objective = population.specimen[index].fitness;
	return result;
}


void geneticThread(Population &population, int **matrix, int n, int m, int p, int iterMax, float probabilityCrossover,
				   float probabilityMutation, bool tournament) {

	int iter = 0;
	while (iter < iterMax) {
		Population childPopulation;
		childPopulation.p = 0;
//		std::cout << population.p << '\n';
		while (childPopulation.p < population.p) {
			int parentA;
			int parentB;
			if (tournament) {
				parentA = population.findParentTournament();
				parentB = population.findParentTournament();
			} else {
				parentA = population.findParentWheel();
				parentB = population.findParentWheel();
			}

			while (parentB == parentA) {
				if (tournament) {
				parentB = population.findParentTournament();
				} else {
					parentB = population.findParentWheel();
				}
			}

//			std::cout << "PARENTS\t" << parentA << '\t' << parentB << '\n';
			// perform crossover with probability

			float r = random2.nextFloat(0.0, 1.0);
			if (r <= probabilityCrossover) {
				std::pair<Chromosome, Chromosome> children = Chromosome::onePointCrossover(
						population.specimen[parentA], population.specimen[parentB]);
				childPopulation.specimen.push_back(children.first);
				childPopulation.p = childPopulation.p + 1;
				childPopulation.specimen.push_back(children.second);
				childPopulation.p = childPopulation.p + 1;
			} else if (r < 0.5) {
				Chromosome specimen;
				specimen.copy(population.specimen[parentA]);
				childPopulation.specimen.push_back(specimen);
				childPopulation.p = childPopulation.p + 1;
			} else {
				Chromosome specimen;
				specimen.copy(population.specimen[parentB]);
				childPopulation.specimen.push_back(specimen);
				childPopulation.p = childPopulation.p + 1;
			}
		} // children generated
//		std::cout << '\n';
		for (int i = 0; i < childPopulation.p; i++) {
			childPopulation.specimen[i].setScore(matrix, n, m);
		}
		childPopulation.findBest();
		// mutation
		for (int i = 0; i < childPopulation.p; i++) {
			float r = random2.nextFloat(0.0, 1.0);
			if (r <= probabilityMutation) {
				childPopulation.specimen[i].mutate();
				childPopulation.specimen[i].setScore(matrix, n, m);
			}
		}
		childPopulation.findBest();
		population.copy(childPopulation);
//		std::cout << "ITERATION:\t" << iter << "\t BEST SCORE: \t" << population.bestScore << '\n';
		iter++;
//		std::cout << '\n';
	}
}

solution geneticAlgorithmIslands(int **matrix, int n, int m, int p, int iterMax, float probabilityCrossover,
							 float probabilityMutation, int islandNumber, int islandIter, int migratingNumber, bool tournament) {
	// initialize populations
	std::vector<Population> islands;
	std::thread threads[islandNumber];

	for (int i = 0; i < islandNumber; i++) {
		islands.emplace_back(p, n, m, matrix);
		islands[i].findBest();
	}
//	for(Population i : islands) {
//		std::cout << "ISLAND BEFORE\n";
////		i.print();
//	std::cout << i.p << '\n';
//	}

	int iter = 0;
	while (iter < islandIter) {
//		std::cout << "ITER: \t" << iter << '\n';
		for (int i = 0; i < islandNumber; i++) {
			threads[i] = std::thread(geneticThread, std::ref(islands[i]), matrix, n, m, p,
									 iterMax, probabilityCrossover, probabilityMutation, tournament);
		}
		// wait till all threads finish computing
		for (int i = 0; i < islandNumber; i++) {
			threads[i].join();
		}
//		for(Population i : islands) {
//			std::cout << "ISLAND\n";
////			i.print();
//			std::cout << i.p << '\n';
//		}

		// perform migration between islands in ring
		for (int i = 0; i < islandNumber; i++) {
			// get random migrating individuals
			for (int j = 0; j < migratingNumber; j++) {
				int rand = -1;
				while (rand < 0 || rand > p - 1) {
					rand = random2.nextInt(0, p - 1);
				}
				Chromosome temp;
				temp.copy(islands[i].specimen[rand]);
//				std::cout << rand << '\t' << islands[i].p <<  '\n';
				if (i < islands.size() - 1) {
//					std::cout << "iter island\t" << i << '\n';
//					islands[i].specimen[rand].print();
//					islands[i+1].specimen[rand].print();
					islands[i].specimen[rand].copy(islands[i + 1].specimen[rand]);
					islands[i + 1].specimen[rand].copy(temp);
				} else {
					islands[i].specimen[rand].copy(islands[0].specimen[rand]);
					islands[0].specimen[rand].copy(temp);
				}
			}
		}
		for (int i = 0; i < islandNumber; i++) {
			islands[i].findBest();
		}
		iter++;
	}
	int index = 0;
	int bestIsland = 0;

	for (int i = 1; i < islandNumber; i++) {
		if (islands[i].bestScore < islands[bestIsland].bestScore) {
			bestIsland = i;
		}
	}
	for (int j = 0; j < p; j++) {
		if (islands[bestIsland].specimen[j].fitness == islands[bestIsland].bestScore) {
			index = j;
			break;
		}
	}
	solution result;
	result.schedule = islands[bestIsland].specimen[index].genotype;
	result.objective = islands[bestIsland].specimen[index].fitness;
	return result;
}

#endif //GENETIC_FLOWSHOP_GENETICALGORITHM_H
