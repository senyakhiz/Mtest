#pragma once
struct Task {
	int _number1;
	int _number2;
	char _operation;
	int _answer;

	Task();
	Task(int a, int b, char operation = '\0');

	char operation() const {
		return _operation;
	}
	int number1() const {
		return _number1;
	}
	int number2() const {
		return _number2;
	}
	int answer() const {
		return _answer;
	}

};

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
	bool record_answer(int index, int answer);
	char get_mark() const;

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