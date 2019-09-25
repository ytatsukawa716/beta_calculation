#ifndef INPUT_BA_SF_H
#define INPUT_BA_SF_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

void data_in(int N, std::vector<std::vector<int>> &neighbor) {
	neighbor = std::vector<std::vector<int>>(N);
	std::string  file_name = "C:/Users/rte19/source/repos/BA-SF_0809/BA-SF_0809/base_BA_SF_N" + std::to_string(N) + "_K8.dat";
	std::ifstream ifs(file_name);
	if (!ifs) {
		std::cout << "Can not open " << file_name << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string str;
	int num = 0;
	while (std::getline(ifs, str)) {
		std::string figure = "";
		for (int i = 0; i < str.size(); i++) {
			if (str[i] != ',') figure += str[i];
			else {
				neighbor[num].emplace_back(std::stoi(figure));
				figure = "";
			}
		}
		neighbor[num].emplace_back(std::stoi(figure));
		num++;
	}
}

#endif // !INPUT_BA_SF_H
