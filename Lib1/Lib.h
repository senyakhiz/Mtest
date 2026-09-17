#pragma once
struct Task {
	int _number1;
	int _number2;
	char _operation;
	int _answer;

	Task();
	Task(int a, int b, char operation = '\0');

	char operation() const noexcept {
		return _operation;
	}
	int number1() const noexcept {
		return _number1;
	}
	int number2() const noexcept {
		return _number2;
	}
	int answer() const noexcept {
		return _answer;
	}

};

class MathTest {
	Task* _tasks;
	int _count;
	int* _user_answers;
	int _correct_count;
	bool* _answered;

public:
	MathTest(int count);
	MathTest(int count, int min, int max);
	MathTest(int count, int min, int max, char operation);
	~MathTest();

	void run();
	void show_statistics() const;
	bool record_answer(int index, int answer);
	char get_mark() const;

	int count() const noexcept {
		return _count;
	}
	const Task& task(int i) const noexcept {
		return _tasks[i];
	}
	int user_answer(int i) const noexcept {
		return _user_answers[i];
	}
	int correct_count() const noexcept {
		return _correct_count;
	}
	bool answered(int i) const noexcept {
		return _answered[i];
	}
};