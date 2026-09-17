#include "pch.h"
#include "Lib1.cpp"

TEST(TaskTest, DefaultConstructor_CorrectAnswer) {
    for (int i = 0; i < 10000; ++i) {
        Task t;
        int expected = 0;
        if (t._operation == '+') {
            expected = t.number1() + t.number2();
        }
        else if (t._operation == '-') {
            expected = t.number1() - t.number2();
        }
        else {
            expected = t.number1() * t.number2();
        }
        EXPECT_EQ(t._answer, expected)
            << "iteration " << i
            << ", a=" << t.number1() << ", b=" << t.number2()
            << ", op=" << t._operation;
    }
}

TEST(TaskTest, ParamConstructor_CorrectAnswer_Addition) {
    for (int i = 0; i < 5000; ++i) {
        Task t(1, 10, '+');
        EXPECT_EQ(t._answer, t.number1() + t.number2())
            << "iteration " << i << ", a=" << t.number1() << ", b=" << t.number2();
    }
}

TEST(TaskTest, ParamConstructor_CorrectAnswer_Subtraction) {
    for (int i = 0; i < 5000; ++i) {
        Task t(1, 10, '-');
        EXPECT_EQ(t._answer, t.number1() - t.number2())
            << "iteration " << i << ", a=" << t.number1() << ", b=" << t.number2();
    }
}

TEST(TaskTest, ParamConstructor_CorrectAnswer_Multiplication) {
    for (int i = 0; i < 5000; ++i) {
        Task t(1, 10, '*');
        EXPECT_EQ(t.answer(), t.number1() * t.number2())
            << "iteration " << i << ", a=" << t.number1() << ", b=" << t.number2();
    }
}

TEST(MathTestTest, TrueRunTest) {
    MathTest mt(5, 1, 10, '+');

    std::stringstream input;
    for (int i = 0; i < 3; ++i) {
        input << mt.task(i).answer() << "\n";
    }
    std::streambuf* old_in = std::cin.rdbuf(input.rdbuf());
    std::stringstream output;
    std::streambuf* old_out = std::cout.rdbuf(output.rdbuf());

    mt.run();

    std::cin.rdbuf(old_in);
    std::cout.rdbuf(old_out);

    EXPECT_EQ(mt.correct_count(), 3);
    EXPECT_EQ(mt.get_mark(), 'A');
}

TEST(MathTestTest, FalseRunTest) {
    MathTest mt(2, 1, 10, '+');

    std::stringstream input;
    input << "99999\n";
    input << "99999\n";

    std::streambuf* old_in = std::cin.rdbuf(input.rdbuf());
    std::stringstream output;
    std::streambuf* old_out = std::cout.rdbuf(output.rdbuf());

    mt.run();

    std::cin.rdbuf(old_in);
    std::cout.rdbuf(old_out);

    EXPECT_EQ(mt.correct_count(), 0);
    EXPECT_EQ(mt.get_mark(), 'F');
}