#include <iostream>
#include <random>
#include "Lib.h"

Task::Task() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> random_num(-1000, 1000);
	std::uniform_int_distribution<> random_operation(0, 2);
	
	_operation = random_operation(gen);
	_number1 = random_num(gen);
	_number2 = random_num(gen);
	if (_operation == '+') {
		_answer = _number1 + _number2;
	}
	else if (_operation == '-') {
		_answer = _number1 - _number2;
	}
	else {
		_answer = _number1 * _number2;
	}
}

Task::Task(int a, int b, char operation) {
	_operation = operation;
	_number1 = a + std::rand() % (b - a + 1);
	_number2 = a + std::rand() % (b - a + 1);

	if (_operation == '+') {
		_answer = _number1 + _number2;
	}
	else if (_operation == '-') {
		_answer = _number1 - _number2;
	}
	else {
		_answer = _number1 * _number2;
	}
}

MathTest::~MathTest() {
	delete[] _tasks;
	delete[] _user_answers;
	delete[] _answered;
}
bool MathTest::record_answer(int index, int answer) {
	if (index < 0 || index >= _count) return false;

	_user_answers[index] = answer;
	_answered[index] = true;

	if (_user_answers[index] == _tasks[index]._answer) {
		_correct_count++;
		return true;
	}
	return false;
}

char MathTest::get_mark() const {
	if (_count == 0) return 'F';
	double percentage = static_cast<double>(_correct_count) / _count * 100.0;
	if (percentage >= 90) return 'A';
	if (percentage >= 80) return 'B';
	if (percentage >= 70) return 'C';
	if (percentage >= 60) return 'D';
	return 'F';
}

void MathTest::run() {
	std::cout << "\n=== START MATH TEST (" << _count << " tasks) ===\n\n";
	for (int i = 0; i < _count; ++i) {
		std::cout << "Task " << (i + 1) << ": "
			<< _tasks[i].number1() << " "
			<< _tasks[i].operation() << " "
			<< _tasks[i].number2() << " = ";

		int ans;
		std::cin >> ans;
		record_answer(i, ans);
	}
	std::cout << "\nTest completed!\n";
}


void MathTest::show_statistics() const {
	std::cout << "No         |";
	for (int i = 0; i < _count; ++i) {
		std::cout << " " << (i + 1) << " |";
	}
	std::cout << "\n";

	std::cout << "Question   |";
	for (int i = 0; i < _count; ++i) {
		std::cout << " " << _tasks[i]._number1 << " "
			<< _tasks[i].operation() << " "
			<< _tasks[i].number1() << " |";
	}
	std::cout << "\n";

	std::cout << "True Answer|";
	for (int i = 0; i < _count; ++i) {
		std::cout << " " << _tasks[i]._answer << " |";
	}
	std::cout << "\n";

	std::cout << "Your Answer|";
	for (int i = 0; i < _count; ++i) {
		if (_answered[i]) {
			std::cout << " " << _user_answers[i] << " |";
		}
		else {
			std::cout << " N/A |";
		}
	}
	std::cout << "\n";

	std::cout << "Result     |";
	for (int i = 0; i < _count; ++i) {
		char res = (_answered[i] && _user_answers[i] == _tasks[i]._answer) ? '+' : '-';
		std::cout << " " << res << " |";
	}
	std::cout << "\n\n";

	std::cout << "Total Result: " << _correct_count << " / " << _count
		<< " (mark: " << get_mark() << ")\n";
}