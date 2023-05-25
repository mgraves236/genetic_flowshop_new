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
						  float probabilityMutation) {
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



void geneticThread(Population& population, int **matrix, int n, int m, int p, int iterMax, float probabilityCrossover,
				   float probabilityMutation) {

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
}

solution geneticAlgorithmIslands(int **matrix, int n, int m, int p, int iterMax, float probabilityCrossover,
						  float probabilityMutation, int islandNumber, int islandIter) {
	// initialize populations
	std::vector<Population> islands;
	std::thread threads[islandNumber];

	for (int i = 0; i < islandNumber; i++) {
		islands.emplace_back(p, n, m, matrix);
		islands[i].findBest();
	}
	for(Population i : islands) {
		std::cout << "ISLAND BEFORE\n";
		i.print();
	}

	int iter = 0;
	while (iter < islandIter) {
		for (int i = 0; i < islandNumber; i++) {
			threads[i] = std::thread(geneticThread,std::ref(islands[i]), matrix, n, m, p,
									 iterMax, probabilityCrossover, probabilityMutation);
		}
		// wait till all threads finish computing
		for (int i = 0; i < islandNumber; i++) {
			threads[i].join();
		}
		for(Population i : islands) {
			std::cout << "ISLAND\n";
			i.print();
		}

		// perform migration between islands 1 - 2
		//									 2 - 3
		//									 3 - 4
		// 									 4 - 1

		for (int i = 0; i < islandNumber; i++) {}



		iter++;
	}

}

#endif //GENETIC_FLOWSHOP_GENETICALGORITHM_H
