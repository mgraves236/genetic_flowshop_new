#ifndef GENETIC_FLOWSHOP_NEW_CHROMOSOME_H
#define GENETIC_FLOWSHOP_NEW_CHROMOSOME_H

#include <random>
#include <algorithm>
#include <iostream>
#include "FlowShop.h"

auto rng = std::mt19937(std::random_device()());

class Chromosome {

public:

	std::vector<int> genotype;
	int n = 0;
	int fitness = 0;


	Chromosome() {}

	Chromosome(int n, int m, int** matrix) {
		this-> n = n;
		for (int i = 0; i < n; i++) {
			genotype.push_back(i);
		}

		std::shuffle(std::begin(genotype), std::end(genotype), rng);
		this->setScore(matrix, n, m);
	}

	void copy(const Chromosome& old) {
		n = old.n;
		fitness = old.fitness;
		for (int i = 0; i < n; i++) {
			genotype.push_back(old.genotype[i]);
		}
	}

	void print() {
		for (int i = 0; i < this->n; i++) {
			std::cout << genotype[i] << "\t";
		}
		std::cout << '\n';
	}

	void setScore(int **matrix, int n, int m) {
		this->fitness = score(this->genotype, matrix, n, m);
	}

};

#endif //GENETIC_FLOWSHOP_NEW_CHROMOSOME_H
