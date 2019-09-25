#ifndef CALCULATE_BETA_H
#define CALCULATE_BETA_H

#include <cmath>
#include "Infection.h"

void Calculate_beta::loop() {
	agent = std::vector<Agent>(N);
	beta = 0;
	double add_val = pow(10, -2.0);
	double error = pow(10, -2.0);
	bool fg = false;
	while (!fg) {
		beta += add_val;
		initialize_infection();
		while (information.I_number != 0) {
			transition_state();
		}
		double fes = double(information.R_number) / N;
		std::cout << beta << " " << fes << std::endl;
		if (abs(fes - 0.9) < error) fg = true;
	}
	std::cout << beta;
}

#endif // !CALCULATE_BETA_H

