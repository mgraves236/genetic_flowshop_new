#ifndef GENETIC_FLOWSHOP_INSTANCE_H
#define GENETIC_FLOWSHOP_INSTANCE_H
#include "RandomNumberGenerator.h"
#include <iostream>

int** initialize(int n, int m) {
	RandomNumberGenerator random = RandomNumberGenerator(659465295);
	int** jobs = new int* [n];
	for (int i = 0; i < n ; i++ ) {
		jobs[i] = new int[m];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0 ; j < m; j++) {
			jobs[i][j] = random.nextInt(1, 10);
		}
	}
	return jobs;
}

void printInstance(int n, int m, int** jobs) {
	for (int i = 0; i < n; i++) {
		for (int j = 0 ; j < m; j++) {
			std::cout << jobs[i][j] << "\t";
		}
		std::cout << "\n";
	}
	std::cout << "\n";

}

#endif //GENETIC_FLOWSHOP_INSTANCE_H
