#include <iostream>

#include "Lib.h"
#include <cstdlib>
#include <ctime>

int main() {
	std::srand(static_cast<unsigned>(std::time(nullptr)));

	std::cout << "Choose mode:\n"
		<< "1 - random tasks (default generator)\n"
		<< "2 - range tasks (min..max)\n"
		<< "3 - range tasks with fixed operation\n"
		<< "Your choice: ";

	int mode = 0;
	if (!(std::cin >> mode)) {
		std::cout << "Error: not a number.\n";
		return 1;
	}

	if (mode != 1 && mode != 2 && mode != 3) {
		std::cout << "Error: mode must be 1, 2 or 3. Got " << mode << ".\n";
		return 1;
	}

	MathTest* test = nullptr;

	if (mode == 1) {
		int count;
		std::cout << "How many tasks? ";
		if (!(std::cin >> count) || count <= 0) {
			std::cout << "Error: bad count.\n";
			return 1;
		}
		test = new MathTest(count);
	}
	else if (mode == 2) {
		int count, min, max;
		std::cout << "count:";
		std::cin >> count;
		std::cout << "min:";
		std::cin >> min;
		std::cout << "max:";
		std::cin >> max;
		if (!std::cin || count <= 0) {
			std::cout << "Error: bad input.\n";
			return 1;
		}
		test = new MathTest(count, min, max);
	}
	else {
		int count, min, max;
		char op;
		std::cout << "count:";
		std::cin >> count;
		std::cout << "min:";
		std::cin >> min;
		std::cout << "max:";
		std::cin >> max;
		std::cout << "operation(+ - * /): ";
		std::cin >> op;
		if (!std::cin || count <= 0) {
			std::cout << "Error: bad input.\n";
			return 1;
		}
		if (op != '+' && op != '-' && op != '*' && op != '/') {
			std::cout << "Error: operation must be + - * /.\n";
			return 1;
		}
		test = new MathTest(count, min, max, op);
	}

	test->run();
	test->show_statistics();

	delete test;
	return 0;
}