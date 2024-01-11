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

TEST_F(Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols, Strang_Chapter_2_2_Example_3x4_rank2)
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

TEST_F(Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols, Strang_Chapter_2_2_Another_Example_3x4_rank2)
{
    const auto data = std::vector<int>{1,2,3,5,
                                       2,4,8,12,
                                       3,6,7,13};

    const auto mat = Matrix<int>(data, 3,4);
    const auto b = Vector<int>({0,6,-6});

    const auto solution = mat.solve(b).value();
    ASSERT_FALSE(solution.unique);
    ASSERT_TRUE(solution.uniqueSolution == std::nullopt);

    const auto particularSolution = solution.particularSolution.value();
    ASSERT_EQ(particularSolution.dim(), mat.cols());
    ASSERT_EQ(particularSolution[0], -9);
    ASSERT_EQ(particularSolution[1], 0);
    ASSERT_EQ(particularSolution[2], 3);
    ASSERT_EQ(particularSolution[3], 0);

    const auto specialSolutions = solution.specialSolutions.value();
    ASSERT_EQ(specialSolutions.size(), 2); //there are 2 free variables

    ASSERT_EQ(specialSolutions[0][0], -2);
    ASSERT_EQ(specialSolutions[0][1], 1);
    ASSERT_EQ(specialSolutions[0][2], 0);
    ASSERT_EQ(specialSolutions[0][3], 0);

    ASSERT_EQ(specialSolutions[1][0], -2);
    ASSERT_EQ(specialSolutions[1][1], 0);
    ASSERT_EQ(specialSolutions[1][2], -1);
    ASSERT_EQ(specialSolutions[1][3], 1);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols, Strang_Chapter_2_2_Problem_2a_3x4_rank2)
{
    const auto data = std::vector<int>{1,2,0,1,
                                       0,1,1,0,
                                       1,2,0,1};

    const auto mat = Matrix<int>(data, 3,4);
    const auto b = Vector<int>({0,0,0});

    const auto solution = mat.solve(b).value();
    ASSERT_FALSE(solution.unique);
    ASSERT_TRUE(solution.uniqueSolution == std::nullopt);

    const auto particularSolution = solution.particularSolution.value();
    ASSERT_EQ(particularSolution.dim(), mat.cols());
    ASSERT_EQ(particularSolution[0], 0);
    ASSERT_EQ(particularSolution[1], 0);
    ASSERT_EQ(particularSolution[2], 0);
    ASSERT_EQ(particularSolution[3], 0);

    const auto specialSolutions = solution.specialSolutions.value();
    ASSERT_EQ(specialSolutions.size(), 2); //there are 2 free variables

    ASSERT_EQ(specialSolutions[0][0], 2);
    ASSERT_EQ(specialSolutions[0][1], -1);
    ASSERT_EQ(specialSolutions[0][2], 1);
    ASSERT_EQ(specialSolutions[0][3], 0);

    ASSERT_EQ(specialSolutions[1][0], -1);
    ASSERT_EQ(specialSolutions[1][1], 0);
    ASSERT_EQ(specialSolutions[1][2], 0);
    ASSERT_EQ(specialSolutions[1][3], 1);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols, Strang_Chapter_2_2_Problem_2b_3x3_rank2)
{
    const auto data = std::vector<int>{1,2,3,
                                       0,-3,-6,
                                       0,-6,-12};


    const auto mat = Matrix<int>(data, 3,3);
    const auto b = Vector<int>({0,0,0});

    const auto solution = mat.solve(b).value();
    ASSERT_FALSE(solution.unique);
    ASSERT_TRUE(solution.uniqueSolution == std::nullopt);

    const auto particularSolution = solution.particularSolution.value();
    ASSERT_EQ(particularSolution.dim(), mat.cols());
    ASSERT_EQ(particularSolution[0], 0);
    ASSERT_EQ(particularSolution[1], 0);
    ASSERT_EQ(particularSolution[2], 0);

    const auto specialSolutions = solution.specialSolutions.value();
    ASSERT_EQ(specialSolutions.size(), 1); //there is 1 free variable

    ASSERT_EQ(specialSolutions[0][0], 1);
    ASSERT_EQ(specialSolutions[0][1], -2);
    ASSERT_EQ(specialSolutions[0][2], 1);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols, Strang_Chapter_2_2_Problem_3_2x4_rank1)
{
    const auto data = std::vector<int>{0,1,0,3,
                                       0,2,0,6};


    const auto mat = Matrix<int>(data, 2,4);
    const auto b = Vector<double>({2.5, 5});

    const auto solution = mat.solve(b).value();
    ASSERT_FALSE(solution.unique);
    ASSERT_TRUE(solution.uniqueSolution == std::nullopt);

    const auto particularSolution = solution.particularSolution.value();
    ASSERT_EQ(particularSolution.dim(), mat.cols());
    ASSERT_EQ(particularSolution[0], 0);
    ASSERT_EQ(particularSolution[1], 2.5);
    ASSERT_EQ(particularSolution[2], 0);
    ASSERT_EQ(particularSolution[3], 0);

    const auto specialSolutions = solution.specialSolutions.value();
    ASSERT_EQ(specialSolutions.size(), 3); // 3 free variables

    ASSERT_EQ(specialSolutions[0][0], 1);
    ASSERT_EQ(specialSolutions[0][1], 0);
    ASSERT_EQ(specialSolutions[0][2], 0);
    ASSERT_EQ(specialSolutions[0][3], 0);

    ASSERT_EQ(specialSolutions[1][0], 0);
    ASSERT_EQ(specialSolutions[1][1], 0);
    ASSERT_EQ(specialSolutions[1][2], 1);
    ASSERT_EQ(specialSolutions[1][3], 0);

    ASSERT_EQ(specialSolutions[2][0], 0);
    ASSERT_EQ(specialSolutions[2][1], -3);
    ASSERT_EQ(specialSolutions[2][2], 0);
    ASSERT_EQ(specialSolutions[2][3], 1);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols, Strang_Chapter_2_2_Problem_3_2x4_incompatible)
{
    const auto data = std::vector<int>{0,1,0,3,
                                       0,2,0,6};


    const auto mat = Matrix<int>(data, 2,4);
    const auto b = Vector<double>({2.5, 5.2});

    const auto solution = mat.solve(b);
    //There is only 1 independent column in mat, which spans a line; b is not in that line --> no solution
    ASSERT_TRUE(solution == std::nullopt);

}

TEST_F(Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols, Strang_Chapter_2_2_Problem_4_4x2_rank1)
{
    const auto data = std::vector<int>{0,0,
                                       1,2,
                                       0,0,
                                       3,6};

    const auto mat = Matrix<int>(data, 4,2);
    const auto b = Vector<double>({0, 3, 0, 9});

    const auto solution = mat.solve(b).value();
    ASSERT_FALSE(solution.unique);
    ASSERT_TRUE(solution.uniqueSolution == std::nullopt);

    const auto particularSolution = solution.particularSolution.value();
    ASSERT_EQ(particularSolution.dim(), mat.cols());
    ASSERT_EQ(particularSolution[0], 3);
    ASSERT_EQ(particularSolution[1], 0);

    const auto specialSolutions = solution.specialSolutions.value();
    ASSERT_EQ(specialSolutions.size(), 1); // 1 free variable

    ASSERT_EQ(specialSolutions[0][0], -2);
    ASSERT_EQ(specialSolutions[0][1], 1);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols, Strang_Chapter_2_2_Problem_4_4x2_rank1_incompatible)
{
    const auto data = std::vector<int>{0,0,
                                       1,2,
                                       0,0,
                                       3,6};

    const auto mat = Matrix<int>(data, 4,2);
    const auto b = Vector<double>({0, 3.5, 0, 12});

    const auto solution = mat.solve(b);
    ASSERT_TRUE(solution == std::nullopt);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols, Strang_Chapter_2_2_problem_5b_2x3_rank1_incompatible)
{
    const auto data = std::vector<int>{1,2,2,
                                       2,4,4};


    const auto mat = Matrix<int>(data, 2,3);
    const auto b = Vector<int>({1,4});

    const auto solution = mat.solve(b);
    ASSERT_TRUE(solution == std::nullopt); //incompatible system
}

TEST_F(Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols, Strang_Chapter_2_2_Problem_7_3x3_rank2)
{
    const auto data = std::vector<int>{1,1,2,
                                       2,3,-1,
                                       3,4,1};

    const auto mat = Matrix<int>(data, 3,3);
    const auto b = Vector<double>({2,5,7});

    const auto solution = mat.solve(b).value();
    ASSERT_FALSE(solution.unique);
    ASSERT_TRUE(solution.uniqueSolution == std::nullopt);

    const auto particularSolution = solution.particularSolution.value();
    ASSERT_EQ(particularSolution.dim(), mat.cols());
    ASSERT_EQ(particularSolution[0], 1);
    ASSERT_EQ(particularSolution[1], 1);
    ASSERT_EQ(particularSolution[2], 0);

    const auto specialSolutions = solution.specialSolutions.value();
    ASSERT_EQ(specialSolutions.size(), 1); // 1 free variable

    ASSERT_EQ(specialSolutions[0][0], -7);
    ASSERT_EQ(specialSolutions[0][1], 5);
    ASSERT_EQ(specialSolutions[0][2], 1);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols, Strang_Chapter_2_2_Problem_7_3x3_rank2_incompatible)
{
    const auto data = std::vector<int>{1,1,2,
                                       2,3,-1,
                                       3,4,1};

    const auto mat = Matrix<int>(data, 3,3);
    const auto b = Vector<double>({2.2,5,7});

    const auto solution = mat.solve(b);
    ASSERT_TRUE(solution == std::nullopt);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols, Strang_Chapter_2_2_Problem_9a_3x4_rank2)
{
    const auto data = std::vector<int>{1,2,3,4,
                                       0,0,1,2,
                                       0,0,0,0};

    const auto mat = Matrix<int>(data, 3,4);
    const auto b = Vector<double>({0,0,0});

    const auto solution = mat.solve(b).value();
    ASSERT_FALSE(solution.unique);
    ASSERT_TRUE(solution.uniqueSolution == std::nullopt);

    const auto particularSolution = solution.particularSolution.value();
    ASSERT_EQ(particularSolution.dim(), mat.cols());
    ASSERT_EQ(particularSolution[0], 0);
    ASSERT_EQ(particularSolution[1], 0);
    ASSERT_EQ(particularSolution[2], 0);
    ASSERT_EQ(particularSolution[3], 0);

    const auto specialSolutions = solution.specialSolutions.value();
    ASSERT_EQ(specialSolutions.size(), 2); // 2 free variables

    ASSERT_EQ(specialSolutions[0][0], -2);
    ASSERT_EQ(specialSolutions[0][1], 1);
    ASSERT_EQ(specialSolutions[0][2], 0);
    ASSERT_EQ(specialSolutions[0][3], 0);

    ASSERT_EQ(specialSolutions[1][0], 2);
    ASSERT_EQ(specialSolutions[1][1], 0);
    ASSERT_EQ(specialSolutions[1][2], -2);
    ASSERT_EQ(specialSolutions[1][3], 1);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols, Strang_Chapter_2_2_Problem_9b_3x4_rank2)
{
    const auto data = std::vector<int>{1,2,3,4,
                                       0,0,1,2,
                                       0,0,0,0};

    const auto mat = Matrix<int>(data, 3,4);
    const auto b = Vector<double>({2,3,0});

    const auto solution = mat.solve(b).value();
    ASSERT_FALSE(solution.unique);
    ASSERT_TRUE(solution.uniqueSolution == std::nullopt);

    const auto particularSolution = solution.particularSolution.value();
    ASSERT_EQ(particularSolution.dim(), mat.cols());
    ASSERT_EQ(particularSolution[0], -7);
    ASSERT_EQ(particularSolution[1], 0);
    ASSERT_EQ(particularSolution[2], 3);
    ASSERT_EQ(particularSolution[3], 0);

    const auto specialSolutions = solution.specialSolutions.value();
    ASSERT_EQ(specialSolutions.size(), 2); // 2 free variables

    ASSERT_EQ(specialSolutions[0][0], -2);
    ASSERT_EQ(specialSolutions[0][1], 1);
    ASSERT_EQ(specialSolutions[0][2], 0);
    ASSERT_EQ(specialSolutions[0][3], 0);

    ASSERT_EQ(specialSolutions[1][0], 2);
    ASSERT_EQ(specialSolutions[1][1], 0);
    ASSERT_EQ(specialSolutions[1][2], -2);
    ASSERT_EQ(specialSolutions[1][3], 1);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols, Strang_Chapter_2_2_Problem_19a_3x4_rank2)
{
    const auto data = std::vector<int>{1,0,2,3,
                                       0,1,4,5,
                                       0,0,0,0};

    const auto mat = Matrix<int>(data, 3,4);
    const auto b = Vector<double>({0,0,0});

    const auto solution = mat.solve(b).value();
    ASSERT_FALSE(solution.unique);
    ASSERT_TRUE(solution.uniqueSolution == std::nullopt);

    const auto particularSolution = solution.particularSolution.value();
    ASSERT_EQ(particularSolution.dim(), mat.cols());
    ASSERT_EQ(particularSolution[0], 0);
    ASSERT_EQ(particularSolution[1], 0);
    ASSERT_EQ(particularSolution[2], 0);
    ASSERT_EQ(particularSolution[3], 0);

    const auto specialSolutions = solution.specialSolutions.value();
    ASSERT_EQ(specialSolutions.size(), 2); // 2 free variables

    ASSERT_EQ(specialSolutions[0][0], -2);
    ASSERT_EQ(specialSolutions[0][1], -4);
    ASSERT_EQ(specialSolutions[0][2], 1);
    ASSERT_EQ(specialSolutions[0][3], 0);

    ASSERT_EQ(specialSolutions[1][0], -3);
    ASSERT_EQ(specialSolutions[1][1], -5);
    ASSERT_EQ(specialSolutions[1][2], 0);
    ASSERT_EQ(specialSolutions[1][3], 1);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols, Strang_Chapter_2_2_Problem_19b_3x3_rank2)
{
    const auto data = std::vector<int>{0,1,2,
                                       0,0,0,
                                       0,0,0};

    const auto mat = Matrix<int>(data, 3,3);
    const auto b = Vector<double>({0,0,0});

    const auto solution = mat.solve(b).value();
    ASSERT_FALSE(solution.unique);
    ASSERT_TRUE(solution.uniqueSolution == std::nullopt);

    const auto particularSolution = solution.particularSolution.value();
    ASSERT_EQ(particularSolution.dim(), mat.cols());
    ASSERT_EQ(particularSolution[0], 0);
    ASSERT_EQ(particularSolution[1], 0);
    ASSERT_EQ(particularSolution[2], 0);

    const auto specialSolutions = solution.specialSolutions.value();
    ASSERT_EQ(specialSolutions.size(), 2); // 2 free variables

    ASSERT_EQ(specialSolutions[0][0], 1);
    ASSERT_EQ(specialSolutions[0][1], 0);
    ASSERT_EQ(specialSolutions[0][2], 0);

    ASSERT_EQ(specialSolutions[1][0], 0);
    ASSERT_EQ(specialSolutions[1][1], -2);
    ASSERT_EQ(specialSolutions[1][2], 1);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols, Strang_Chapter_2_2_Problem_30_3x4_rank2)
{
    const auto data = std::vector<int>{2,4,6,4,
                                       2,5,7,6,
                                       2,3,5,2};

    const auto mat = Matrix<int>(data, 3,4);
    const auto b = Vector<double>({4,3,5});

    const auto solution = mat.solve(b).value();
    ASSERT_FALSE(solution.unique);
    ASSERT_TRUE(solution.uniqueSolution == std::nullopt);

    const auto particularSolution = solution.particularSolution.value();
    ASSERT_EQ(particularSolution.dim(), mat.cols());
    ASSERT_EQ(particularSolution[0], 4);
    ASSERT_EQ(particularSolution[1], -1);
    ASSERT_EQ(particularSolution[2], 0);
    ASSERT_EQ(particularSolution[3], 0);

    const auto specialSolutions = solution.specialSolutions.value();
    ASSERT_EQ(specialSolutions.size(), 2); // 2 free variables

    ASSERT_EQ(specialSolutions[0][0], -1);
    ASSERT_EQ(specialSolutions[0][1], -1);
    ASSERT_EQ(specialSolutions[0][2], 1);
    ASSERT_EQ(specialSolutions[0][3], 0);

    ASSERT_EQ(specialSolutions[1][0], 2);
    ASSERT_EQ(specialSolutions[1][1], -2);
    ASSERT_EQ(specialSolutions[1][2], 0);
    ASSERT_EQ(specialSolutions[1][3], 1);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols, Strang_Chapter_2_2_Problem_33a_3x3_rank2)
{
    const auto data = std::vector<int>{1,3,3,
                                       2,6,9,
                                       -1,-3,3};

    const auto mat = Matrix<int>(data, 3,3);
    const auto b = Vector<double>({1,5,5});

    const auto solution = mat.solve(b).value();
    ASSERT_FALSE(solution.unique);
    ASSERT_TRUE(solution.uniqueSolution == std::nullopt);

    const auto particularSolution = solution.particularSolution.value();
    ASSERT_EQ(particularSolution.dim(), mat.cols());
    ASSERT_EQ(particularSolution[0], -2);
    ASSERT_EQ(particularSolution[1], 0);
    ASSERT_EQ(particularSolution[2], 1);

    const auto specialSolutions = solution.specialSolutions.value();
    ASSERT_EQ(specialSolutions.size(), 1); // 1 free variable

    ASSERT_EQ(specialSolutions[0][0], -3);
    ASSERT_EQ(specialSolutions[0][1], 1);
    ASSERT_EQ(specialSolutions[0][2], 0);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols, Strang_Chapter_2_2_Problem_33b_3x4_rank2)
{
    const auto data = std::vector<int>{1,3,1,2,
                                        2,6,4,8,
                                        0,0,2,4};

    const auto mat = Matrix<int>(data, 3,4);
    const auto b = Vector<double>({1,3,1});

    const auto solution = mat.solve(b).value();
    ASSERT_FALSE(solution.unique);
    ASSERT_TRUE(solution.uniqueSolution == std::nullopt);

    const auto particularSolution = solution.particularSolution.value();
    ASSERT_EQ(particularSolution.dim(), mat.cols());
    ASSERT_EQ(particularSolution[0], 0.5);
    ASSERT_EQ(particularSolution[1], 0);
    ASSERT_EQ(particularSolution[2], 0.5);
    ASSERT_EQ(particularSolution[3], 0);

    const auto specialSolutions = solution.specialSolutions.value();
    ASSERT_EQ(specialSolutions.size(), 2); // 2 free variables

    ASSERT_EQ(specialSolutions[0][0], -3);
    ASSERT_EQ(specialSolutions[0][1], 1);
    ASSERT_EQ(specialSolutions[0][2], 0);
    ASSERT_EQ(specialSolutions[0][3], 0);

    ASSERT_EQ(specialSolutions[1][0], 0);
    ASSERT_EQ(specialSolutions[1][1], 0);
    ASSERT_EQ(specialSolutions[1][2], -2);
    ASSERT_EQ(specialSolutions[1][3], 1);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols, Strang_Chapter_2_2_Problem_34_3x3_rank2)
{
    const auto data = std::vector<int>{1,2,-2,
                                       2,5,-4,
                                       4,9,-8};

    const auto mat = Matrix<int>(data, 3,3);
    const auto b = Vector<double>({2,5,9});

    const auto solution = mat.solve(b).value();
    ASSERT_FALSE(solution.unique);
    ASSERT_TRUE(solution.uniqueSolution == std::nullopt);

    const auto particularSolution = solution.particularSolution.value();
    ASSERT_EQ(particularSolution.dim(), mat.cols());
    ASSERT_EQ(particularSolution[0], 0);
    ASSERT_EQ(particularSolution[1], 1);
    ASSERT_EQ(particularSolution[2], 0);

    const auto specialSolutions = solution.specialSolutions.value();
    ASSERT_EQ(specialSolutions.size(), 1); // 1 free variables

    ASSERT_EQ(specialSolutions[0][0], 2);
    ASSERT_EQ(specialSolutions[0][1], 0);
    ASSERT_EQ(specialSolutions[0][2], 1);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols, Strang_Chapter_2_2_Problem_34_3x3_rank2_incompatible)
{
    const auto data = std::vector<int>{1,2,-2,
                                       2,5,-4,
                                       4,9,-8};

    const auto mat = Matrix<int>(data, 3,3);
    const auto b = Vector<double>({2,4,9});

    const auto solution = mat.solve(b);
    ASSERT_TRUE(solution == std::nullopt);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols, Strang_Chapter_2_2_Problem_35b_4x2_rank2)
{
    const auto data = std::vector<int>{1,2,3,
                                       2,4,6,
                                       2,5,7,
                                       3,9,12};

    const auto mat = Matrix<int>(data, 4,3);
    const auto b = Vector<double>({2,4,6,12});

    const auto solution = mat.solve(b).value();
    ASSERT_FALSE(solution.unique);
    ASSERT_TRUE(solution.uniqueSolution == std::nullopt);

    const auto particularSolution = solution.particularSolution.value();
    ASSERT_EQ(particularSolution.dim(), mat.cols());
    ASSERT_EQ(particularSolution[0], -2);
    ASSERT_EQ(particularSolution[1], 2);
    ASSERT_EQ(particularSolution[2], 0);

    const auto specialSolutions = solution.specialSolutions.value();
    ASSERT_EQ(specialSolutions.size(), 1); // 1 free variables

    ASSERT_EQ(specialSolutions[0][0], -1);
    ASSERT_EQ(specialSolutions[0][1], -1);
    ASSERT_EQ(specialSolutions[0][2], 1);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols, Strang_Chapter_2_2_Problem_35b_4x2_rank2_incompatible)
{
    const auto data = std::vector<int>{1,2,3,
                                       2,4,6,
                                       2,5,7,
                                       3,9,12};

    const auto mat = Matrix<int>(data, 4,3);
    const auto b = Vector<double>({2,4,6,14});

    const auto solution = mat.solve(b);
    ASSERT_TRUE(solution == std::nullopt);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols, Strang_Chapter_2_2_Problem_36b_3x3_rank2)
{
    const auto data = std::vector<int>{1,1,1,
                                       1,2,4,
                                       2,4,8};

    const auto mat = Matrix<int>(data, 3,3);
    const auto b = Vector<double>({0,0,0});

    const auto solution = mat.solve(b).value();
    ASSERT_FALSE(solution.unique);
    ASSERT_TRUE(solution.uniqueSolution == std::nullopt);

    const auto particularSolution = solution.particularSolution.value();
    ASSERT_EQ(particularSolution.dim(), mat.cols());
    ASSERT_EQ(particularSolution[0], 0);
    ASSERT_EQ(particularSolution[1], 0);
    ASSERT_EQ(particularSolution[2], 0);

    const auto specialSolutions = solution.specialSolutions.value();
    ASSERT_EQ(specialSolutions.size(), 1); // 1 free variables

    ASSERT_EQ(specialSolutions[0][0], 2);
    ASSERT_EQ(specialSolutions[0][1], -3);
    ASSERT_EQ(specialSolutions[0][2], 1);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols, Strang_Chapter_2_2_Problem_47a_3x3_rank2)
{
    const auto data = std::vector<int>{3,0,6,
                                       0,0,2,
                                       0,0,0};

    const auto mat = Matrix<int>(data, 3,3);
    const auto b = Vector<double>({0,0,0});

    const auto solution = mat.solve(b).value();
    ASSERT_FALSE(solution.unique);
    ASSERT_TRUE(solution.uniqueSolution == std::nullopt);

    const auto particularSolution = solution.particularSolution.value();
    ASSERT_EQ(particularSolution.dim(), mat.cols());
    ASSERT_EQ(particularSolution[0], 0);
    ASSERT_EQ(particularSolution[1], 0);
    ASSERT_EQ(particularSolution[2], 0);

    const auto specialSolutions = solution.specialSolutions.value();
    ASSERT_EQ(specialSolutions.size(), 1); // 1 free variables

    ASSERT_EQ(specialSolutions[0][0], 0);
    ASSERT_EQ(specialSolutions[0][1], 1);
    ASSERT_EQ(specialSolutions[0][2], 0);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols, Strang_Chapter_2_2_Problem_47b_3x3_rank2_incompatible)
{
    const auto data = std::vector<int>{3,0,6,
                                       0,0,2,
                                       0,0,0};

    const auto mat = Matrix<int>(data, 3,3);
    const auto b = Vector<double>({9,4,5});

    const auto solution = mat.solve(b);
    ASSERT_TRUE(solution == std::nullopt);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols, Strang_Chapter_2_2_Problem_52a_3x5_rank2)
{
    const auto data = std::vector<int>{1,2,2,4,6,
                                       1,2,3,6,9,
                                       0,0,1,2,3};

    const auto mat = Matrix<int>(data, 3,5);
    const auto b = Vector<double>({0,0,0});

    const auto solution = mat.solve(b).value();
    ASSERT_FALSE(solution.unique);
    ASSERT_TRUE(solution.uniqueSolution == std::nullopt);

    const auto particularSolution = solution.particularSolution.value();
    ASSERT_EQ(particularSolution.dim(), mat.cols());
    ASSERT_EQ(particularSolution[0], 0);
    ASSERT_EQ(particularSolution[1], 0);
    ASSERT_EQ(particularSolution[2], 0);
    ASSERT_EQ(particularSolution[3], 0);
    ASSERT_EQ(particularSolution[4], 0);

    const auto specialSolutions = solution.specialSolutions.value();
    ASSERT_EQ(specialSolutions.size(), 3); // 3 free variables

    ASSERT_EQ(specialSolutions[0][0], -2);
    ASSERT_EQ(specialSolutions[0][1], 1);
    ASSERT_EQ(specialSolutions[0][2], 0);
    ASSERT_EQ(specialSolutions[0][3], 0);
    ASSERT_EQ(specialSolutions[0][4], 0);

    ASSERT_EQ(specialSolutions[1][0], 0);
    ASSERT_EQ(specialSolutions[1][1], 0);
    ASSERT_EQ(specialSolutions[1][2], -2);
    ASSERT_EQ(specialSolutions[1][3], 1);
    ASSERT_EQ(specialSolutions[1][4], 0);

    ASSERT_EQ(specialSolutions[2][0], 0);
    ASSERT_EQ(specialSolutions[2][1], 0);
    ASSERT_EQ(specialSolutions[2][2], -3);
    ASSERT_EQ(specialSolutions[2][3], 0);
    ASSERT_EQ(specialSolutions[2][4], 1);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols, Strang_Chapter_2_2_Problem_52b_3x3_rank2)
{
    const auto data = std::vector<int>{2,4,2,
                                       0,4,4,
                                       0,8,8};

    const auto mat = Matrix<int>(data, 3,3);
    const auto b = Vector<double>({0,0,0});

    const auto solution = mat.solve(b).value();
    ASSERT_FALSE(solution.unique);
    ASSERT_TRUE(solution.uniqueSolution == std::nullopt);

    const auto particularSolution = solution.particularSolution.value();
    ASSERT_EQ(particularSolution.dim(), mat.cols());
    ASSERT_EQ(particularSolution[0], 0);
    ASSERT_EQ(particularSolution[1], 0);
    ASSERT_EQ(particularSolution[2], 0);

    const auto specialSolutions = solution.specialSolutions.value();
    ASSERT_EQ(specialSolutions.size(),1); // 1 free variable

    ASSERT_EQ(specialSolutions[0][0], 1);
    ASSERT_EQ(specialSolutions[0][1], -1);
    ASSERT_EQ(specialSolutions[0][2], 1);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols, Solve_Strang_Chapter_1_review_problem_19_3x3_rank2)
{
    const auto data = std::vector<int>{1,1,1,
                                       1,2,3,
                                       3,5,7};

    const auto mat = Matrix<int>(data, 3,3);

    auto b = Vector<int>({1,2,5});

    const auto solution = mat.solve(b).value();

    const auto particularSolution = solution.particularSolution.value();
    ASSERT_EQ(particularSolution.dim(), mat.cols());
    ASSERT_EQ(particularSolution[0], 0);
    ASSERT_EQ(particularSolution[1], 1);
    ASSERT_EQ(particularSolution[2], 0);

    const auto specialSolutions = solution.specialSolutions.value();
    ASSERT_EQ(specialSolutions.size(),1); // 1 free variable

    ASSERT_EQ(specialSolutions[0][0], 1);
    ASSERT_EQ(specialSolutions[0][1], -2);
    ASSERT_EQ(specialSolutions[0][2], 1);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankSmallerThanNumRowsAndNumCols, Solve_Strang_Chapter_1_review_problem_19_3x3_rank2_incompatible)
{
    const auto data = std::vector<int>{1,1,1,
                                       1,2,3,
                                       3,5,7};

    const auto mat = Matrix<int>(data, 3,3);

    auto b = Vector<int>({1,2,5});

    const auto solution = mat.solve(b);
    ASSERT_TRUE(solution == std::nullopt);
}