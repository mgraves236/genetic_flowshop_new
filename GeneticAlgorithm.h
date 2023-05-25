#ifndef GENETIC_FLOWSHOP_GENETICALGORITHM_H
#define GENETIC_FLOWSHOP_GENETICALGORITHM_H

#include "RandomNumberGenerator.h"
#include "Population.h"


struct solution {
	int* schedule;
	int objective;
};

solution geneticAlgorithm(int** matrix, int n, int m, int p, int iterMax, float probabilityCrossover) {
	// initialize populations
	Population population(p, n, m, matrix);
	population.print();
	population.findBest();
	Population childPopulation;

	for (int i = 0; i < population.p; i++) {
		Chromosome specimen;
		specimen.copy(population.specimen[0]);
		childPopulation.specimen.push_back(specimen);
		childPopulation.p = childPopulation.p + 1;
	}

	std::cout << "CHILD \n";
	childPopulation.print();

}


#endif //GENETIC_FLOWSHOP_GENETICALGORITHM_H
