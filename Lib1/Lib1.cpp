#include "pch.h"
#include <iostream>
#include <random>
#include "Lib.h"

Task::Task() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> random_num(-1000, 1000);
    std::uniform_int_distribution<> random_operation(0, 3);

    int op = random_operation(gen);   
    if (op == 0) {
        _operation = '+';
    }
    else if (op == 1) {
        _operation = '-';
    }
    else if (op == 2){
        _operation = '*';
    }
    else {
        _operation = '/';
    }

    if (_operation == '/') {
        std::uniform_int_distribution<> divisor_dist(1, 100);
        std::uniform_int_distribution<> quotient_dist(-10, 10);
        std::uniform_int_distribution<> sign(0, 1);

        _number2 = divisor_dist(gen);
        if (sign(gen) == 1) {
            _number2 = -_number2;
        }

        int k = quotient_dist(gen);
        if (k == 0) {
            k = 1;
        }

        _number1 = _number2 * k;
        _answer = k;
    }
    else {
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
}

Task::Task(int a, int b, char operation) {
    if (a > b) {
        throw std::logic_error("min>max");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> random_num(a, b);
    std::uniform_int_distribution<> random_operation(0, 3);

    if (operation == '+' || operation == '-' || operation == '*'|| operation == '/') {
        _operation = operation;
    }
    else {
        int op = random_operation(gen);
        if (op == 0) {
            _operation = '+';
        }
        else if (op == 1) {
            _operation = '-';
        }
        else if (op == 2) {
            _operation = '*';
        }
        else {
            _operation = '/';
        }
    }

    if (_operation == '/') {
        int x = 0, y = 0;
        for (int attempt = 0; attempt < 10000; ++attempt) {
            int new_x = random_num(gen);
            int new_y = random_num(gen);
            if (new_y != 0 && new_x % new_y == 0) {
                x = new_x;
                y = new_y;
                break;
            }

            if (y == 0) {
                for (int j = a; j <= b; ++j) {
                    if (j != 0) {
                        y = j;
                        break;
                    }
                }
                if (y == 0) {
                    throw std::invalid_argument("Division by zero");
                }
                x = y;
            }

            _number1 = x;
            _number2 = y;
            _answer = x / y;
        }
    }
    
    else {
        _number1 = random_num(gen);
        _number2 = random_num(gen);

        if (_operation == '+') {
            _answer = _number1 + _number2;
    }
        else if (_operation == '-') {
            _answer = _number1 - _number2;
        }
        else if (_operation == '*') {
            _answer = _number1 * _number2;
        }
    }
}

MathTest::MathTest(int count) {
    _count = count;
    _correct_count = 0;
    _tasks = new Task[_count];
    _user_answers = new int[_count] {0};
    _answered = new bool[_count] {false};
    for (int i = 0; i < _count; ++i) {
        _tasks[i] = Task();
    }
}

MathTest::MathTest(int count, int min, int max) {
    _count = count;
    _correct_count = 0;
    _tasks = new Task[_count];
    _user_answers = new int[_count] {0};
    _answered = new bool[_count] {false};
    for (int i = 0; i < _count; ++i) {
        _tasks[i] = Task(min, max); 
    }
}

MathTest::MathTest(int count, int min, int max, char operation) {
    _count = count;
    _correct_count = 0;
    _tasks = new Task[_count];
    _user_answers = new int[_count] {0};
    _answered = new bool[_count] {false};
    for (int i = 0; i < _count; ++i) {
        _tasks[i] = Task(min, max, operation);
    }
}

MathTest::~MathTest() {
    delete[] _tasks;
    delete[] _user_answers;
    delete[] _answered;
}

bool MathTest::record_answer(int index, int answer) {
    if (index < 0 || index >= _count) return false;

    bool was_correct = _answered[index] && (_user_answers[index] == _tasks[index]._answer);

    _user_answers[index] = answer;
    _answered[index] = true;

    bool is_correct = (_user_answers[index] == _tasks[index]._answer);

    if (was_correct && !is_correct) {
        --_correct_count;
    }
    else if (!was_correct && is_correct) {
        ++_correct_count;
    }

    return is_correct;
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
    std::cout << "Number     |";
    for (int i = 0; i < _count; ++i) {
        std::cout << " " << (i + 1) << " |";
    }
    std::cout << "\n";

    std::cout << "Question   |";
    for (int i = 0; i < _count; ++i) {
        std::cout << " " << _tasks[i]._number1 << " "
            << _tasks[i].operation() << " "
            << _tasks[i].number2() << " |";
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