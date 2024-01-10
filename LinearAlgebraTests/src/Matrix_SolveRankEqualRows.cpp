//
// Created by dorian on 10.01.2024.
// stoicadorian@gmail.com
//

#include "gtest/gtest.h"
#include "Matrix.hpp"

#include "cmath"

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

    const auto solution = mat.solve(b).value();
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

    //TODO test linear combinations
}