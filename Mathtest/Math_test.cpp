#include <iostream>

#include "Lib1.cpp"
#include <cstdlib>
#include <ctime>

int main() {
	std::srand(static_cast<unsigned>(std::time(nullptr)));

	std::cout << "Choose mode:\n"
		<< "1 - random tasks (default generator)\n"
		<< "2 - range tasks (min..max)\n"
		<< "3 - range tasks with fixed operation\n"
		<< "Your choice: ";

	int mode = 1;
	std::cin >> mode;

	MathTest* test = nullptr;

	if (mode == 1) {
		int count;
		std::cout << "How many tasks? ";
		std::cin >> count;
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
		test = new MathTest(count, min, max, op);
	}

	test->run();
	test->show_statistics();

	delete test;
	return 0;
}