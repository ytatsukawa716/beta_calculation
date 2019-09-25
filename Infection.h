#ifndef INFECTION_H
#define INFECTION_H

#include "Beta_test_class.h"
#include "random.h"

void Infection::initialize_infection() {
	std::vector<int> list(N);
	for (int i = 0; i < N; i++) list[i] = i;
	agent = initial_agent;	//agent‚Ì‰Šú‰»
	information.S_number = N;
	information.I_number = 0;
	information.R_number = 0;
	for (int i = 0; i < parameter.Io; i++) {
		int size = list.size() - 1;
		int xsize = random(size);
		int number = list[xsize];
		list.erase(list.begin() + xsize);
		agent[number].state = State::I;
		for (int j = 0; j < agent[number].neighbor.size(); j++) {
			int num = agent[number].neighbor[j];
			agent[num].NI++;
		}
		information.S_number--;
		information.I_number++;
	}
}

void Infection::transition_state() {
	trans_p = std::vector<double>(N);
	calculate_transition_p();
	select_transition_agent();
	update_information();
}

void Infection::calculate_transition_p() {
	ramda = 0;
	for (int i = 0; i < N; i++) {
		if (agent[i].state == State::S) trans_p[i] = beta * agent[i].NI;
		else if(agent[i].state == State::I) trans_p[i] = parameter.ganma;
		else if (agent[i].state == State::R) trans_p[i] = 0;
		ramda += trans_p[i];
	}
}

void Infection::select_transition_agent() {
	double p = 0;
	double random_number = random(1.0);
	for (int i = 0; i < N; i++) {
		p += trans_p[i] / ramda;
		if (random_number <= p) {
			selected_num = i;
			break;
		}
	}
}

void Infection::update_information() {
	int sn = selected_num;
	if (agent[sn].state == State::S) {
		agent[sn].state = State::I;
		for (int i = 0; i < agent[sn].neighbor.size(); i++) {
			int num = agent[sn].neighbor[i];
			agent[num].NI++;
		}
		information.S_number--;
		information.I_number++;
	}
	else if (agent[sn].state == State::I) {
		agent[sn].state = State::R;
		for (int i = 0; i < agent[sn].neighbor.size(); i++) {
			int num = agent[sn].neighbor[i];
			agent[num].NI--;
		}
		information.I_number--;
		information.R_number++;
	}
}

#endif // ! INFECTION_H

