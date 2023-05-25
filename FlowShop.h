//
// Created by Magda on 24.05.2023.
//

#ifndef GENETIC_FLOWSHOP_FLOWSHOP_H
#define GENETIC_FLOWSHOP_FLOWSHOP_H


int score(std::vector<int> schedule, int** matrix, int n, int m) {
	int* machine = new int[m];
	for (int i = 0; i < m; i++) {
		machine[i] = 0;
	}
	machine[0] = 0;
	for (int j = 0; j < n; j++) {
		int current = schedule[j];
		machine[0] += matrix[current][0];
		for (int i = 1; i < m; i++) {
			if (machine[i] < machine[i-1]) {
				machine[i] = (machine[i-1] - machine[i]) + machine[i]
							 + matrix[current][i];
			} else {
//				std::cout << '\n' << i << '\t' <<  matrix[current][i] << '\t' << machine[i];
				machine[i] += matrix[current][i];
			}
		}
	}
//	std::cout << '\n';
	for (int i = 0; i < m; i++) {
//		std:: cout <<  machine[i] << '\t';
	}
//	std::cout << machine[m-1] << '\n';
	return machine[m-1];
}

void printSchedule(std::vector<int> schedule, int** matrix, int n, int m) {
	std::string* machineString = new std::string[m];

	for (int j = 0; j < n; j++) {
		int current = schedule[j];
		for (int k = 0; k < matrix[current][0]; k++) {
			machineString[0].append(std::to_string(current));
		}
		for (int i = 1; i < m; i++) {
			if (machineString[i].length() < machineString[i-1].length()) {
				for (int k = 0; machineString[i-1].length() - machineString[i].length(); k++) {
					machineString[i].append("-");
				}
				for (int k = 0; k < matrix[current][i]; k++) {
					machineString[i].append(std::to_string(current));
				}
			} else {
				for (int k = 0; k < matrix[current][i]; k++) {
					machineString[i].append(std::to_string(current));
				}
			}
		}
	}


	int totalDuration = score(schedule, matrix, n, m);
	for(int j = 0; j < m; j++) {
		if (machineString[j].length() < totalDuration) {
			for (int i = 0; i < totalDuration - machineString[j].length(); i++) {
				machineString[j].append("-");
			}
		}
	}
	for (int i = 0; i < m; i++) {
		std::cout << "Machine " << i << ":\t" <<  machineString[i] << '\n';
	}
}

#endif //GENETIC_FLOWSHOP_FLOWSHOP_H
