#ifndef BETA_TEST_CLASS_H
#define BETA_TEST_CLASS_H
#include <vector>
#include "input_BA_SF.h"

struct State {
	static const int S = 0;
	static const int I = 1;
	static const int R = 2;
};

struct Agent {
	std::vector<int> neighbor;
	int NI;
	int state;
};

struct Information {
	int S_number;
	int I_number;
	int R_number;
};

struct Parameter {
	const int Io = 5;
	const double ganma = 1.0 / 3.0;
	const int ensemble = 100;
};

class Infection {
public:
	int N;
	double beta;
	std::vector<Agent> agent;
	Information information;
	Parameter parameter;
	void initialize_infection();
	void transition_state();
	void get_initial_agent() { initial_agent = agent; }
private:
	std::vector<Agent> initial_agent;
	std::vector<double> trans_p;
	double ramda;
	int selected_num;
	void calculate_transition_p();
	void select_transition_agent();
	void update_information();
};

class Calculate_beta :public Infection {
public:
	Calculate_beta(int Nsize) {
		N = Nsize;
		std::vector<std::vector<int>> *neighbor = new std::vector<std::vector<int>>;
		data_in(N, *neighbor);
		Agent _ag;
		_ag.NI = 0;
		_ag.state = State::S;
		agent = std::vector<Agent>(N, _ag);
		for (int i = 0; i < N; i++) agent[i].neighbor = (*neighbor)[i];
		delete neighbor;
		get_initial_agent();
	}
	void loop();
};

#endif // !BETA_TEST_CLASS_H

