#include "pch.h"
#include "Lib1.cpp"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(TaskTest, DefaultConstructor_CorrectAnswer) {
    for (int i = 0; i < 10000; ++i) {
        Task t;
        int expected = 0;
        if (t._operation == '+') {
            expected = t.a() + t.b();
        }
        else if (t._operation == '-') {
            expected = t.a() - t.b();
        }
        else {
            expected = t.a() * t.b();
        }
        EXPECT_EQ(t._answer, expected)
            << "iteration " << i
            << ", a=" << t.a() << ", b=" << t.b()
            << ", op=" << t._operation;
    }
}

TEST(TaskTest, ParamConstructor_CorrectAnswer_Addition) {
    for (int i = 0; i < 5000; ++i) {
        Task t(1, 10, '+');
        EXPECT_EQ(t._answer, t.a() + t.b())
            << "iteration " << i << ", a=" << t.a() << ", b=" << t.b();
    }
}

TEST(TaskTest, ParamConstructor_CorrectAnswer_Subtraction) {
    for (int i = 0; i < 5000; ++i) {
        Task t(1, 10, '-');
        EXPECT_EQ(t._answer, t.a() - t.b())
            << "iteration " << i << ", a=" << t.a() << ", b=" << t.b();
    }
}

TEST(TaskTest, ParamConstructor_CorrectAnswer_Multiplication) {
    for (int i = 0; i < 5000; ++i) {
        Task t(1, 10, '*');
        EXPECT_EQ(t.answer(), t.a() * t.b())
            << "iteration " << i << ", a=" << t.a() << ", b=" << t.b();
    }
}

TEST(MathTestTest, RunTest) {

}

TEST(MathTestTest, ShowTest) {

}