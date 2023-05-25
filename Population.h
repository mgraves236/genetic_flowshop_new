#ifndef GENETIC_FLOWSHOP_POPULATION_H
#define GENETIC_FLOWSHOP_POPULATION_H

#include <vector>
#include "Chromosome.h"
#include "RandomNumberGenerator.h"

RandomNumberGenerator random = RandomNumberGenerator(659465295);


class Population {
public:
	std::vector<Chromosome> specimen;
	int p = 0;
	int bestScore = INT_MAX;

public:
	~Population() = default;

	Population() = default;

	explicit Population(int p, int n, int m, int** matrix) {
		this->p = p;
		for (int i = 0; i < p; i++) {
			specimen.emplace_back(n, m, matrix);
		}
	}

	void print() {
		for (int i = 0; i < p; i++) {
			specimen[i].print();
			std::cout << '\n';
		}
	}

	void findBest() {
		for (int i = 0; i < p; i++) {
			if(specimen[i].fitness < bestScore) {
				bestScore = specimen[i].fitness;
			}
		}
		std::cout << "Best Score: " << bestScore << '\n';
	}

	int findParentWheel() {
		float totalScore = 0;
		for (int i = 0; i < this->p; i++) {
			totalScore += (float) this->specimen[i].fitness;
		}
		auto* normScore = new float[this->p];
		for (int i = 0; i < this->p; i++) {
			normScore[i] = static_cast<float>(this->specimen[i].fitness) / static_cast<float>(totalScore);
		}

		while (true) {
			float rand = random.nextFloat(0.0, 1.0);

			int randIndex = random.nextInt(0, this->p);

			if (rand < normScore[randIndex]) {
				return randIndex;
			}
		}
	}
};

#endif //GENETIC_FLOWSHOP_POPULATION_H
