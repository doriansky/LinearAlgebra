//
// Created by dorian on 10.01.2024.
// stoicadorian@gmail.com
//

#include "gtest/gtest.h"
#include "Matrix.hpp"
#include "MatrixHelpers.hpp"

using namespace LinearAlgebra::Matrix;
using namespace LinearAlgebra::Vector;


class Matrix_SolveSystemLinearEquations_RankEqualsNumRows: public ::testing::Test
{

protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(Matrix_SolveSystemLinearEquations_RankEqualsNumRows, Strang_Chapter_2_2_problem_5_2x3)
{
    const auto data = std::vector<int>{1,2,2,
                                       2,4,5};


    const auto mat = Matrix<int>(data, 2,3);
    const auto b = Vector<int>({1,4});

    const auto solution = solve(mat, b).value();
    ASSERT_FALSE(solution.unique);
    ASSERT_TRUE(solution.uniqueSolution == std::nullopt);

    const auto particularSolution = solution.particularSolution.value();
    ASSERT_EQ(particularSolution.dim(), mat.cols());
    ASSERT_EQ(particularSolution[0], -3);
    ASSERT_EQ(particularSolution[1], 0);
    ASSERT_EQ(particularSolution[2], 2);

    const auto specialSolutions = solution.specialSolutions.value();
    ASSERT_EQ(specialSolutions.size(), 1); //there is one free variable, the second one
    ASSERT_EQ(specialSolutions[0][0], -2);
    ASSERT_EQ(specialSolutions[0][1], 1);
    ASSERT_EQ(specialSolutions[0][2], 0);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankEqualsNumRows, Strang_Chapter_2_2_problem_8_2x4_rank2)
{
    const auto data = std::vector<int>{1,2,0,3,
                                       2,4,0,7};


    const auto mat = Matrix<int>(data, 2,4);
    const auto b = Vector<int>({1,4});

    const auto solution = solve(mat, b).value();
    ASSERT_FALSE(solution.unique);
    ASSERT_TRUE(solution.uniqueSolution == std::nullopt);

    const auto particularSolution = solution.particularSolution.value();
    ASSERT_EQ(particularSolution.dim(), mat.cols());
    ASSERT_EQ(particularSolution[0], -5);
    ASSERT_EQ(particularSolution[1], 0);
    ASSERT_EQ(particularSolution[2], 0);
    ASSERT_EQ(particularSolution[3], 2);

    const auto specialSolutions = solution.specialSolutions.value();
    ASSERT_EQ(specialSolutions.size(), 2); //there are 2 free variables (2 columns without pivots)

    ASSERT_EQ(specialSolutions[0][0], -2);
    ASSERT_EQ(specialSolutions[0][1], 1);
    ASSERT_EQ(specialSolutions[0][2], 0);
    ASSERT_EQ(specialSolutions[0][3], 0);

    ASSERT_EQ(specialSolutions[1][0], 0);
    ASSERT_EQ(specialSolutions[1][1], 0);
    ASSERT_EQ(specialSolutions[1][2], 1);
    ASSERT_EQ(specialSolutions[1][3], 0);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankEqualsNumRows, Strang_Chapter_2_2_problem_46a_2x3_rank2)
{
    const auto data = std::vector<int>{1,2,3,
                                       0,0,4};


    const auto mat = Matrix<int>(data, 2,3);
    const auto b = Vector<int>({0,0});

    const auto solution = solve(mat, b).value();
    ASSERT_FALSE(solution.unique);
    ASSERT_TRUE(solution.uniqueSolution == std::nullopt);

    const auto particularSolution = solution.particularSolution.value();
    ASSERT_EQ(particularSolution.dim(), mat.cols());
    ASSERT_EQ(particularSolution[0], 0);
    ASSERT_EQ(particularSolution[1], 0);
    ASSERT_EQ(particularSolution[2], 0);

    const auto specialSolutions = solution.specialSolutions.value();
    ASSERT_EQ(specialSolutions.size(), 1); //1 free variable

    ASSERT_EQ(specialSolutions[0][0], -2);
    ASSERT_EQ(specialSolutions[0][1], 1);
    ASSERT_EQ(specialSolutions[0][2], 0);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankEqualsNumRows, Strang_Chapter_2_2_problem_46b_2x3_rank2)
{
    const auto data = std::vector<int>{1,2,3,
                                       0,0,4};


    const auto mat = Matrix<int>(data, 2,3);
    const auto b = Vector<int>({5,8});

    const auto solution = solve(mat, b).value();
    ASSERT_FALSE(solution.unique);
    ASSERT_TRUE(solution.uniqueSolution == std::nullopt);

    const auto particularSolution = solution.particularSolution.value();
    ASSERT_EQ(particularSolution.dim(), mat.cols());
    ASSERT_EQ(particularSolution[0], -1);
    ASSERT_EQ(particularSolution[1], 0);
    ASSERT_EQ(particularSolution[2], 2);

    const auto specialSolutions = solution.specialSolutions.value();
    ASSERT_EQ(specialSolutions.size(), 1); //1 free variable

    ASSERT_EQ(specialSolutions[0][0], -2);
    ASSERT_EQ(specialSolutions[0][1], 1);
    ASSERT_EQ(specialSolutions[0][2], 0);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankEqualsNumRows, Strang_Chapter_2_2_problem_48b_3x4_rank3)
{
    const auto data = std::vector<int>{1,0,2,3,
                                       1,3,2,0,
                                       2,0,4,9};


    const auto mat = Matrix<int>(data, 3,4);
    const auto b = Vector<int>({2,5,10});

    const auto solution = solve(mat, b).value();
    ASSERT_FALSE(solution.unique);
    ASSERT_TRUE(solution.uniqueSolution == std::nullopt);

    const auto particularSolution = solution.particularSolution.value();
    ASSERT_EQ(particularSolution.dim(), mat.cols());
    ASSERT_EQ(particularSolution[0], -4);
    ASSERT_EQ(particularSolution[1], 3);
    ASSERT_EQ(particularSolution[2], 0);
    ASSERT_EQ(particularSolution[3], 2);

    const auto specialSolutions = solution.specialSolutions.value();
    ASSERT_EQ(specialSolutions.size(), 1); //1 free variable

    ASSERT_EQ(specialSolutions[0][0], -2);
    ASSERT_EQ(specialSolutions[0][1], 0);
    ASSERT_EQ(specialSolutions[0][2], 1);
    ASSERT_EQ(specialSolutions[0][3], 0);
}