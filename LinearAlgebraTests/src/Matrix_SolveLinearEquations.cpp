//
// Created by dorian on 29.12.2023.
// stoicadorian@gmail.com
//

#include "gtest/gtest.h"
#include "Matrix.hpp"

#include "cmath"

using namespace LinearAlgebra::Matrix;
using namespace LinearAlgebra::Vector;


class Matrix_SolveSystemLinearEquations : public ::testing::Test
{

protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(Matrix_SolveSystemLinearEquations, Test)
{
    const auto data = std::vector<int>{2,1,1,
                                     4,-6,0,
                                    -2,7,2};

    const auto mat = Matrix<int>(data, 3,3);

    const auto b = Vector<int>({5,-2,9});

    const auto solution = mat.solve(b);
    ASSERT_TRUE(solution.dim() == 3);
    const double epsilon = 1e-9;
    ASSERT_NEAR(solution[0], 1, epsilon);
    ASSERT_NEAR(solution[1], 1, epsilon);
    ASSERT_NEAR(solution[2], 2, epsilon);
}

TEST_F(Matrix_SolveSystemLinearEquations, Strang_Chapter_1_5_problem_5)
{
    const auto data = std::vector<int>{2,3,3,
                                       0,5,7,
                                       6,9,8};

    const auto mat = Matrix<int>(data, 3,3);

    const auto b = Vector<int>({2,2,5});

    const auto solution = mat.solve(b);

    ASSERT_TRUE(solution.dim() == 3);
    const double epsilon = 1e-9;
    ASSERT_NEAR(solution[0], 1, epsilon);
    ASSERT_NEAR(solution[1], -1, epsilon);
    ASSERT_NEAR(solution[2], 1, epsilon);
}

TEST_F(Matrix_SolveSystemLinearEquations, Strang_Chapter_1_5_problem_13_row_swap)
{
    const auto data = std::vector<int>{1,4,2,
                                       -2,-8,3,
                                       0,1,1};

    const auto mat = Matrix<int>(data, 3,3);

    const auto b = Vector<int>({-2,32,1});

    const auto solution = mat.solve(b);

    ASSERT_TRUE(solution.dim() == 3);
    const double epsilon = 1e-9;
    ASSERT_NEAR(solution[0], 2, epsilon);
    ASSERT_NEAR(solution[1], -3, epsilon);
    ASSERT_NEAR(solution[2], 4, epsilon);
}

TEST_F(Matrix_SolveSystemLinearEquations, Strang_Chapter_1_5_problem_18c_row_swap)
{
    const auto data = std::vector<int>{0,1,1,
                                       1,1,0,
                                       1,0,1};

    const auto mat = Matrix<int>(data, 3,3);

    const auto b = Vector<int>({1,1,1});

    const auto solution = mat.solve(b);

    ASSERT_TRUE(solution.dim() == 3);
    const double epsilon = 1e-9;
    ASSERT_NEAR(solution[0], 1./2, epsilon);
    ASSERT_NEAR(solution[1], 1./2, epsilon);
    ASSERT_NEAR(solution[2], 1./2, epsilon);
}

TEST_F(Matrix_SolveSystemLinearEquations, Strang_Chapter_1_5_problem_21)
{
    const auto data = std::vector<int>{1,1,1,
                                       1,2,3,
                                       1,3,6};

    const auto mat = Matrix<int>(data, 3,3);

    const auto b = Vector<int>({5,7,11});

    const auto solution = mat.solve(b);

    ASSERT_TRUE(solution.dim() == 3);
    const double epsilon = 1e-9;
    ASSERT_NEAR(solution[0], 5, epsilon);
    ASSERT_NEAR(solution[1], -2, epsilon);
    ASSERT_NEAR(solution[2], 2, epsilon);
}

TEST_F(Matrix_SolveSystemLinearEquations, Strang_Chapter_1_7_ill_conditioned)
{
    const auto data = std::vector<double>{1,1,
                                       1, 1.0001};

    const auto mat = Matrix<double>(data, 2,2);

    const auto b_1 = Vector<double>({2,2});
    const auto b_2 = Vector<double>({2,2.0001});

    const auto solution_1 = mat.solve(b_1);

    const double epsilon = 1e-9;
    ASSERT_NEAR(solution_1[0], 2, epsilon);
    ASSERT_NEAR(solution_1[1], 0, epsilon);

    const auto solution_2 = mat.solve(b_2);
    ASSERT_NEAR(solution_2[0], 1, epsilon);
    ASSERT_NEAR(solution_2[1], 1, epsilon);

    const auto data_2 = std::vector<double>{0.0001,1,
                                          1, 1};

    const auto mat_2 = Matrix<double>(data_2, 2,2);

    const auto b_3 = Vector<double>({1,2});
    const auto sol = mat_2.solve(b_3);

    ASSERT_NEAR(sol[0], 1, 1e-3);
    ASSERT_NEAR(sol[1], 0.9999, 1e-3);

}

TEST_F(Matrix_SolveSystemLinearEquations, Strang_Chapter_Chapter_1_7__Problem_5)
{
    const auto data = std::vector<int>{2, -1, 0,
                                       -1, 2, -1,
                                       0, -1, 2};

    const auto mat = Matrix<int>(data, 3,3);

    auto b = Vector<int>({1,0,-1});
    b *= M_PI*M_PI/4;

    const auto solution = mat.solve(b);

    ASSERT_TRUE(solution.dim() == 3);
    const double epsilon = 1e-9;
    ASSERT_NEAR(solution[0], std::sin(2*M_PI/4),    epsilon);
    ASSERT_NEAR(solution[1], std::sin(2*M_PI/2),    epsilon);
    ASSERT_NEAR(solution[2], std::sin(2*M_PI*3./4), epsilon);
}

TEST_F(Matrix_SolveSystemLinearEquations, Solve_Strang_Chapter_1_review_problem_4a)
{
    const auto data = std::vector<int>{1,0,1,
                                       1,1,0,
                                       1,1,1};

    const auto mat = Matrix<int>(data, 3,3);

    auto b = Vector<int>({4,3,6});

    const auto solution = mat.solve(b);

    ASSERT_TRUE(solution.dim() == 3);
    const double epsilon = 1e-9;
    ASSERT_NEAR(solution[0], 1,    epsilon);
    ASSERT_NEAR(solution[1], 2,    epsilon);
    ASSERT_NEAR(solution[2], 3,     epsilon);
}

TEST_F(Matrix_SolveSystemLinearEquations, Solve_Strang_Chapter_1_review_problem_4b)
{
    const auto data = std::vector<int>{0,1,1,
                                       1,0,1,
                                       1,1,0};

    const auto mat = Matrix<int>(data, 3,3);

    auto b = Vector<int>({0,0,6});

    const auto solution = mat.solve(b);

    ASSERT_TRUE(solution.dim() == 3);
    const double epsilon = 1e-9;
    ASSERT_NEAR(solution[0], 3,    epsilon);
    ASSERT_NEAR(solution[1], 3,    epsilon);
    ASSERT_NEAR(solution[2], -3,     epsilon);
}

TEST_F(Matrix_SolveSystemLinearEquations, Solve_System_9x9)
{
    const auto data = std::vector<double>{
                                          1,    2,  1.12,   101, -1.23,  0.5,    1,  1, 11,
                                          1,    2,  1.13,   201, -2.34,  1.5,    4,  0,  22,
                                          2,    3,  1.14,   30, -3.45,  2.5,    9,  1,  33,
                                          3,    4,  1.15,   40, -4.56,  3.5,    16, 0,  44,
                                          4,    5,  1.16,   50, -5.67,  4.5,    25, 1,  55,
                                          5,    6,  1.17,   60, -6.78,  6.5,    36, 0,  66,
                                          6,    7,  1.18,   70, -7.89,  7.5,    49, 1,  77,
                                          7,    8,  1.19,   80, -8.9,   8.5,    64, 0,  88,
                                          8,    9,  1.2,    90, -9.1,   9.5,    81, 1,  100};

    const auto mat = Matrix<double>(data, 9,9);
    const auto b = Vector<double>({      569.0241,
                                          1126.5869,
                                          544.0397,
                                          744.8125,
                                          978.4853,
                                          1216.4981,
                                          1480.8509,
                                          1743.5287,
                                          2053.411
                                    });


    const auto solution = mat.solve(b);

    ASSERT_TRUE(solution.dim() == 9);
    const double epsilon = 1e-8;
    ASSERT_NEAR(solution[0], 1.01, epsilon);
    ASSERT_NEAR(solution[1], 2.12, epsilon);
    ASSERT_NEAR(solution[2], 3.23, epsilon);
    ASSERT_NEAR(solution[3], 4.34, epsilon);
    ASSERT_NEAR(solution[4], 5.45, epsilon);
    ASSERT_NEAR(solution[5], 6.56, epsilon);
    ASSERT_NEAR(solution[6], 7.67, epsilon);
    ASSERT_NEAR(solution[7], 8.78, epsilon);
    ASSERT_NEAR(solution[8], 9.89, epsilon);

    //  Check Ax=b
    const auto same_b = mat*solution;
    ASSERT_NEAR(same_b[0], b[0], epsilon);
    ASSERT_NEAR(same_b[1], b[1], epsilon);
    ASSERT_NEAR(same_b[2], b[2], epsilon);
    ASSERT_NEAR(same_b[3], b[3], epsilon);
    ASSERT_NEAR(same_b[4], b[4], epsilon);
    ASSERT_NEAR(same_b[5], b[5], epsilon);
    ASSERT_NEAR(same_b[6], b[6], epsilon);
    ASSERT_NEAR(same_b[7], b[7], epsilon);
    ASSERT_NEAR(same_b[8], b[8], epsilon);

}

TEST_F(Matrix_SolveSystemLinearEquations, Solve_Strang_Chapter_1_review_problem_19)
{
    const auto data = std::vector<int>{1,1,1,
                                       1,2,3,
                                       3,5,7};

    const auto mat = Matrix<int>(data, 3,3);

    auto b = Vector<int>({0,0,1});

    // Singular matrix (row3 = 2*row_2 + row_1 in this case).  "solve" throws when zero-pivots are obtained in LU.
    ASSERT_THROW(mat.solve(b), std::runtime_error);
}