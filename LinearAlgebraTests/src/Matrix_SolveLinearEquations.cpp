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