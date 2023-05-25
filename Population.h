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
//		std::cout << "Best Score: " << bestScore << '\n';
	}

	int findParentWheel() {
		float totalScore = 0;
		for (int i = 0; i < this->p; i++) {
			totalScore += (float) specimen[i].fitness;
		}
		auto* normScore = new float[p];
		for (int i = 0; i < this->p; i++) {
			normScore[i] = static_cast<float>(this->specimen[i].fitness) / static_cast<float>(totalScore);
		}
		int counter = 0;
		while (true) {
			float rand = random.nextFloat(0.0, 1.0);

			int randIndex = -1;
			while (randIndex < 0 || randIndex > this->p-1) {
				randIndex = random.nextInt(0, this->p - 1);
			}

			if (rand < normScore[randIndex]) {
				return randIndex;
			}
			counter ++;
			if (counter > 10000) {
				return randIndex;
			}
		}
	}

	int findParentTournament() {
		const int pool = 6;
		int best = INT_MAX;
		int bestIndex = -1;
		int* randIndex = new int[pool];
		for (int i = 0; i < pool; i++) {
			while (randIndex[i] < 0 || randIndex[i] > this->p - 1) {
				randIndex[i] = random.nextInt(0, this->p - 1);
			}
		}
//		for (int i = 0; i < pool; i++) {
//			std::cout << randIndex[i] << '\t';
//		}
//		std::cout << '\n';

		for (int i = 0; i < pool; i++) {
			if (specimen[randIndex[i]].fitness < best) {
				best = specimen[randIndex[i]].fitness;
				bestIndex = randIndex[i];
			}
		}
		return bestIndex;
	}

	void copy(Population& old) {
		p = old.p;
		bestScore = old.bestScore;
		specimen.clear();
		for (int i = 0; i < p; i++) {
			specimen.push_back(old.specimen[i]);
		}
	}
};

#endif //GENETIC_FLOWSHOP_POPULATION_H
