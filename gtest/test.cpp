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

TEST(MathTestTest, RunTest) {

}

TEST(MathTestTest, ShowTest) {

}