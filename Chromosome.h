#ifndef GENETIC_FLOWSHOP_NEW_CHROMOSOME_H
#define GENETIC_FLOWSHOP_NEW_CHROMOSOME_H

#include <random>
#include <algorithm>
#include <iostream>
#include "FlowShop.h"

auto rng = std::mt19937(std::random_device()());
RandomNumberGenerator random3 = RandomNumberGenerator(659465295);


class Chromosome {

public:

	std::vector<int> genotype;
	int n = 0;
	int fitness = 0;


	Chromosome() {}

	Chromosome(int n, int m, int **matrix) {
		this->n = n;
		for (int i = 0; i < n; i++) {
			genotype.push_back(i);
		}

		std::shuffle(std::begin(genotype), std::end(genotype), rng);
		this->setScore(matrix, n, m);
	}

	void copy(const Chromosome &old) {
		n = old.n;
		fitness = old.fitness;
		for (int i = 0; i < n; i++) {
			genotype.push_back(old.genotype[i]);
		}
	}

	void createNull(const Chromosome &old) {
		n = old.n;
		fitness = old.fitness;
		for (int i = 0; i < n; i++) {
			genotype.push_back(-1);
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

	void mutate() {
		// get two random indexes that will be swapped
		int index1 = random3.nextInt(0, n - 1);
		int index2 = random3.nextInt(0, n - 1);
		while (index2 ==  index1) {
			index2 = random3.nextInt(0, n - 1);
		}

		// perform swap
		int temp = genotype[index1];
		genotype[index1] = genotype[index2];
		genotype[index2] = temp;
	}


	static std::pair<Chromosome, Chromosome> onePointCrossover(Chromosome& parentA, Chromosome& parentB) {
		Chromosome childA, childB;
		childA.createNull(parentA);
		childB.createNull(parentB);


		// choose a random point
		int randIndex = -1;
		while (randIndex < 0 || randIndex > parentA.n) {
			randIndex = random3.nextInt(1, parentA.n - 1);

		}
		for (int i = 0; i < randIndex; i++) {
			childA.genotype[i] = parentA.genotype[i];
			childB.genotype[i] = parentB.genotype[i];
		}

		int iterIndex = childA.n - 1;
		for (int i = childA.n - 1; i >= 0; i--) {
			int temp = parentB.genotype[i];
			if (std::find(childA.genotype.begin(), childA.genotype.end(), temp) != childA.genotype.end()) {
				continue;
			} else {
				childA.genotype[iterIndex] = parentB.genotype[i];
				iterIndex--;
			}
		}

		iterIndex = childB.n - 1;
		for (int i = childB.n - 1; i >= 0; i--) {
			int temp = parentA.genotype[i];
			if (std::find(childB.genotype.begin(), childB.genotype.end(), temp) != childB.genotype.end()) {
				continue;
			} else {
				childB.genotype[iterIndex] = parentA.genotype[i];
				iterIndex--;
			}
		}

		return std::make_pair(childA, childB);
	}


	static std::pair<Chromosome, Chromosome> twoPointCrossover(Chromosome& parentA, Chromosome& parentB) {
		Chromosome childA, childB;
		childA.createNull(parentA);
		childB.createNull(parentB);


		// choose random points
		int randIndex1 = -1;
		int randIndex2 = -1;

		while (randIndex1 < 1 || randIndex1 > parentA.n - 1)
			randIndex1 = random3.nextInt(1, parentA.n - 1);

		while (randIndex2 < 1 || randIndex2 > parentA.n - 1)
			randIndex2 = random3.nextInt(1, parentA.n - 1);


		int temp = 0;
		if (randIndex1 > randIndex2) {
			temp = randIndex1;
			randIndex1 = randIndex2;
			randIndex2 = temp;
		}
		for (int i = randIndex1; i < randIndex2 + 1; i++) {
			childA.genotype[i] = parentA.genotype[i];
			childB.genotype[i] = parentB.genotype[i];
		}

		int iterIndex = childA.n - 1;
		for (int i = childA.n - 1; i >= 0; i--) {

			int temp2 = parentB.genotype[i];
			if (std::find(childA.genotype.begin(), childA.genotype.end(), temp2) != childA.genotype.end()) {
				continue;
			} else {
				while (iterIndex >= randIndex1 && iterIndex <= randIndex2){
					iterIndex--;
				}
				childA.genotype[iterIndex] = parentB.genotype[i];
				iterIndex--;
			}
		}

		iterIndex = childB.n - 1;
		for (int i = childB.n - 1; i >= 0; i--) {

			int temp2 = parentA.genotype[i];
			if (std::find(childB.genotype.begin(), childB.genotype.end(), temp2) != childB.genotype.end()) {
				continue;
			} else {
				while (iterIndex >= randIndex1 && iterIndex <= randIndex2){
					iterIndex--;
				}
				childB.genotype[iterIndex] = parentA.genotype[i];
				iterIndex--;
			}
		}

		return std::make_pair(childA, childB);
	}
};

#endif //GENETIC_FLOWSHOP_NEW_CHROMOSOME_H
