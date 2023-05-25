#ifndef GENETIC_FLOWSHOP_GENETICALGORITHM_H
#define GENETIC_FLOWSHOP_GENETICALGORITHM_H

#include "RandomNumberGenerator.h"
#include "Population.h"

RandomNumberGenerator random2 = RandomNumberGenerator(65765295);

struct solution {
	int *schedule;
	int objective;
};

solution geneticAlgorithm(int **matrix, int n, int m, int p, int iterMax, float probabilityCrossover) {
	// initialize populations
	Population population(p, n, m, matrix);
	population.print();
	population.findBest();
	Population childPopulation;

	int iter = 0;
	while (iter < iterMax) {
		for (int i = 0; i < population.p * 2; i++) {
			int parentA = population.findParentWheel();
			int parentB = population.findParentWheel();

			while (parentB == parentA) {
				parentB = population.findParentWheel();
			}
//			std::cout << "FIND PARENTS\n";
//			population.specimen[parentA].print();
//			population.specimen[parentB].print();
//			std::cout << "\n";
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

		iter++;
	}

//	std::cout << "CHILD \n";
//	childPopulation.print();

}


#endif //GENETIC_FLOWSHOP_GENETICALGORITHM_H
