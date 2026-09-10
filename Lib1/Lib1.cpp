#include "pch.h"
#include "framework.h"
#include <iostream>

struct Task {
	int _a;
	int _b;
	char _operation;
	int _answer;

	Task();
	Task(int a, int b, char operation);

};

Task::Task() {
	_operation = "+-*"[std::rand() % 3];
	_a = 1 + std::rand() % 10;
	_b = 1 + std::rand() % 10;
	if (_operation == '+') {
		_answer = _a + _b;
	}
	else if (_operation == '-') {
		_answer = _a - _b;
	}
	else {
		_answer = _a * _b;
	}
}

Task::Task(int a, int b, char operation) {
	_operation = operation;
	_a = a + std::rand() % (b - a + 1);
	_b = a + std::rand() % (b - a + 1);

	if (_operation == '+') {
		_answer = _a + _b;
	}
	else if (_operation == '-') {
		_answer = _a - _b;
	}
	else {
		_answer = _a * _b;
	}
}

class MathTest {

};
