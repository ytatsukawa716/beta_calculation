#include <iostream>
#include "Calculate_beta.h"


int main() {
	int N = 10000;
	Calculate_beta result(N);
	result.loop();
	getchar();
	return 0;
}