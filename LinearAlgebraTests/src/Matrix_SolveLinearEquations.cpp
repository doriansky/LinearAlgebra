//
// Created by dorian on 29.12.2023.
// stoicadorian@gmail.com
//

#include "gtest/gtest.h"
#include "Matrix.hpp"

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