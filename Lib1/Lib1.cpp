#include "pch.h"
#include "framework.h"
#include <iostream>

struct Task {
	int _a;
	int _b;
	char _operation;
	int _answer;

	Task();
	Task(int a, int b, char operation = '\0');

	char operation() const { 
		return _operation; 
	}
	int a() const { 
		return _a; 
	}
	int b() const { 
		return _b; 
	}
	int answer() const { 
		return _answer; 
	}

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
	Task* _tasks;
	int _count;
	int* _user_answers;
	int _correct_count;
	bool* _answered;

	void basic() {
		_tasks = new Task[_count];
		_user_answers = new int[_count] {0};
		_answered = new bool[_count] {false};
	}

public:
	MathTest(int count) : _count(count), _correct_count(0) {
		basic();
		for (int i = 0; i < _count; ++i) {
			_tasks[i] = Task();
		}
	}

	MathTest(int count, int min, int max) : _count(count), _correct_count(0) {
		basic();
		for (int i = 0; i < _count; ++i) {
			_tasks[i] = Task(min, max);
		}
	}

	MathTest(int count, int min, int max, char operation) : _count(count), _correct_count(0) {
		basic();
		for (int i = 0; i < _count; ++i) {
			_tasks[i] = Task(min, max, operation);
		}
	}
	~MathTest();

	void run();
	void show_statistics() const;
	bool recordAnswer(int index, int answer);
	char getMark() const;

	int count() const { 
		return _count; 
	}
	const Task& task(int i) const { 
		return _tasks[i]; 
	}
	int user_answer(int i) const { 
		return _user_answers[i]; 
	}
	int correct_count() const { 
		return _correct_count; 
	}
	bool answered(int i) const { 
		return _answered[i]; 
	}
};

MathTest::~MathTest() {
	delete[] _tasks;
	delete[] _user_answers;
	delete[] _answered;
}
bool MathTest::recordAnswer(int index, int answer) {
	if (index < 0 || index >= _count) return false;

	_user_answers[index] = answer;
	_answered[index] = true;

	if (_user_answers[index] == _tasks[index]._answer) {
		_correct_count++;
		return true;
	}
	return false;
}

char MathTest::getMark() const {
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
			<< _tasks[i]._a << " "
			<< _tasks[i]._operation << " "
			<< _tasks[i]._b << " = ";

		int ans;
		std::cin >> ans;
		recordAnswer(i, ans);
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
		std::cout << " " << _tasks[i]._a << " "
			<< _tasks[i]._operation << " "
			<< _tasks[i]._b << " |";
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
		<< " (mark: " << getMark() << ")\n";
}