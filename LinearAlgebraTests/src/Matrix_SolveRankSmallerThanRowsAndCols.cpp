//
// Created by dorian on 10.01.2024.
// stoicadorian@gmail.com
//

#include "gtest/gtest.h"
#include "Matrix.hpp"

#include "cmath"

using namespace LinearAlgebra::Matrix;
using namespace LinearAlgebra::Vector;


class Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols: public ::testing::Test
{

protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols, Strang_Chapter_2_2_Example)
{
    const auto data = std::vector<int>{1,3,3,2,
                                       2,6,9,7,
                                       -1,-3,3,4};



    const auto mat = Matrix<int>(data, 3,4);
    const auto b = Vector<int>({1,5,5});

    const auto solution = mat.solve(b).value();
    ASSERT_FALSE(solution.unique);
    ASSERT_TRUE(solution.uniqueSolution == std::nullopt);

    const auto particularSolution = solution.particularSolution.value();
    ASSERT_EQ(particularSolution.dim(), mat.cols());
    ASSERT_EQ(particularSolution[0], -2);
    ASSERT_EQ(particularSolution[1], 0);
    ASSERT_EQ(particularSolution[2], 1);
    ASSERT_EQ(particularSolution[3], 0);

    const auto specialSolutions = solution.specialSolutions.value();
    ASSERT_EQ(specialSolutions.size(), 2); //there are 2 free variables

    ASSERT_EQ(specialSolutions[0][0], -3);
    ASSERT_EQ(specialSolutions[0][1], 1);
    ASSERT_EQ(specialSolutions[0][2], 0);
    ASSERT_EQ(specialSolutions[0][3], 0);

    ASSERT_EQ(specialSolutions[1][0], 1);
    ASSERT_EQ(specialSolutions[1][1], 0);
    ASSERT_EQ(specialSolutions[1][2], -1);
    ASSERT_EQ(specialSolutions[1][3], 1);

}

TEST_F(Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols, Strang_Chapter_2_2_problem_5)
{
    const auto data = std::vector<int>{1,2,2,
                                       2,4,4};



    const auto mat = Matrix<int>(data, 2,3);
    const auto b = Vector<int>({1,4});

    const auto solution = mat.solve(b);
    ASSERT_TRUE(solution == std::nullopt); //incompatible system


    //TODO test linear combinations
}