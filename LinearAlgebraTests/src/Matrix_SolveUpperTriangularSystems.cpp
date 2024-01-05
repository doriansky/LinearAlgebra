//
// Created by dorian on 29.12.2023.
// stoicadorian@gmail.com
//

#include "gtest/gtest.h"
#include "Matrix.hpp"

using namespace LinearAlgebra::Matrix;
using namespace LinearAlgebra::Vector;


class Matrix_SolveUpperTriangularSystems : public ::testing::Test
{

protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(Matrix_SolveUpperTriangularSystems, Test)
{
    const auto data = std::vector<int>{2,1,1,
                                       0,-8,-2,
                                       0,0,1};

    const auto mat = Matrix<int>(data, 3,3);
    const auto vec = Vector<int>({5,-12,2});

    const auto solution = mat.solveUpperTriangular(vec);
    ASSERT_EQ(solution[0], 1);
    ASSERT_EQ(solution[1], 1);
    ASSERT_EQ(solution[2], 2);

    const auto sameSolution = mat.solve(vec);
    ASSERT_EQ(sameSolution[0], 1);
    ASSERT_EQ(sameSolution[1], 1);
    ASSERT_EQ(sameSolution[2], 2);
}

TEST_F(Matrix_SolveUpperTriangularSystems, Strang_Chapter_1_5_problem_5)
{
    const auto data = std::vector<int>{2,3,3,
                                       0,5,7,
                                       0,0,-1};

    const auto mat = Matrix<int>(data, 3,3);
    const auto vec = Vector<int>({2,2,-1});

    const auto solution = mat.solveUpperTriangular(vec);
    ASSERT_EQ(solution[0], 1);
    ASSERT_EQ(solution[1], -1);
    ASSERT_EQ(solution[2], 1);

    const auto sameSolution = mat.solve(vec);
    ASSERT_EQ(sameSolution[0], 1);
    ASSERT_EQ(sameSolution[1], -1);
    ASSERT_EQ(sameSolution[2], 1);
}

TEST_F(Matrix_SolveUpperTriangularSystems, Strang_Chapter_1_5_problem_11)
{
    const auto data = std::vector<int>{2,4,4,
                                       0,1,2,
                                       0,0,1};

    const auto mat = Matrix<int>(data, 3,3);
    const auto vec = Vector<int>({2,-2,0});

    const auto solution = mat.solveUpperTriangular(vec);
    ASSERT_EQ(solution[0], 5);
    ASSERT_EQ(solution[1], -2);
    ASSERT_EQ(solution[2], 0);

    const auto sameSolution = mat.solve(vec);
    ASSERT_EQ(sameSolution[0], 5);
    ASSERT_EQ(sameSolution[1], -2);
    ASSERT_EQ(sameSolution[2], 0);
}

TEST_F(Matrix_SolveUpperTriangularSystems, Strang_Chapter_1_5_problem_13)
{
    const auto data = std::vector<int>{1,4,2,
                                       0,1,1,
                                       0,0,7};

    const auto mat = Matrix<int>(data, 3,3);
    const auto vec = Vector<int>({-2,1,28});

    const auto solution = mat.solveUpperTriangular(vec);
    ASSERT_EQ(solution[0], 2);
    ASSERT_EQ(solution[1], -3);
    ASSERT_EQ(solution[2], 4);

    const auto sameSolution = mat.solve(vec);
    ASSERT_EQ(sameSolution[0], 2);
    ASSERT_EQ(sameSolution[1], -3);
    ASSERT_EQ(sameSolution[2], 4);
}

TEST_F(Matrix_SolveUpperTriangularSystems, Strang_Chapter_1_5_problem_18c)
{
    const auto data = std::vector<int>{1,1,0,
                                       0,1,1,
                                       0,0,2};

    const auto mat = Matrix<int>(data, 3,3);
    const auto vec = Vector<int>({1,1,1});

    const auto solution = mat.solveUpperTriangular(vec);
    ASSERT_EQ(solution[0], 0.5);
    ASSERT_EQ(solution[1], 0.5);
    ASSERT_EQ(solution[2], 0.5);

    const auto sameSolution = mat.solve(vec);
    ASSERT_EQ(sameSolution[0], 0.5);
    ASSERT_EQ(sameSolution[1], 0.5);
    ASSERT_EQ(sameSolution[2], 0.5);
}

TEST_F(Matrix_SolveUpperTriangularSystems, Strang_Chapter_1_5_problem_21)
{
    const auto data = std::vector<int>{1,1,1,
                                       0,1,2,
                                       0,0,1};

    const auto mat = Matrix<int>(data, 3,3);
    const auto vec = Vector<int>({5,2,2});

    const auto solution = mat.solveUpperTriangular(vec);
    ASSERT_EQ(solution[0], 5);
    ASSERT_EQ(solution[1], -2);
    ASSERT_EQ(solution[2], 2);

    const auto sameSolution = mat.solve(vec);
    ASSERT_EQ(sameSolution[0], 5);
    ASSERT_EQ(sameSolution[1], -2);
    ASSERT_EQ(sameSolution[2], 2);
}

TEST_F(Matrix_SolveUpperTriangularSystems, Strang_Chapter_1_5_problem_33)
{
    const auto data = std::vector<int>{1,1,1,
                                       0,1,1,
                                       0,0,1};

    const auto mat = Matrix<int>(data, 3,3);
    const auto vec = Vector<int>({4,1,1});

    const auto solution = mat.solveUpperTriangular(vec);
    ASSERT_EQ(solution[0], 3);
    ASSERT_EQ(solution[1], 0);
    ASSERT_EQ(solution[2], 1);

    const auto sameSolution = mat.solve(vec);
    ASSERT_EQ(sameSolution[0], 3);
    ASSERT_EQ(sameSolution[1], 0);
    ASSERT_EQ(sameSolution[2], 1);
}

TEST_F(Matrix_SolveUpperTriangularSystems, Strang_Review_Chapter_1_problem_13)
{
    const auto data = std::vector<int>{2,2,4,
                                       0,1,3,
                                       0,0,1};

    const auto mat = Matrix<int>(data, 3,3);
    const auto vec = Vector<int>({0,0,1});

    const auto solution = mat.solveUpperTriangular(vec);
    ASSERT_EQ(solution[0], 1);
    ASSERT_EQ(solution[1], -3);
    ASSERT_EQ(solution[2], 1);

    const auto sameSolution = mat.solve(vec);
    ASSERT_EQ(sameSolution[0], 1);
    ASSERT_EQ(sameSolution[1], -3);
    ASSERT_EQ(sameSolution[2], 1);
}