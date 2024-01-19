//
// Created by dorian on 10.01.2024.
// stoicadorian@gmail.com
//

#include "gtest/gtest.h"
#include "Matrix.hpp"
#include "MatrixToolbox.hpp"


using namespace LinearAlgebra::Matrix;
using namespace LinearAlgebra::Vector;


class Matrix_SolveSystemLinearEquations_RankEqualsNumColumns : public ::testing::Test
{

protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(Matrix_SolveSystemLinearEquations_RankEqualsNumColumns, Strang_Chapter_2_2_problem_6_3x2_rank2)
{
    const auto data = std::vector<int>{1,0,
                                       0,1,
                                       2,3};

    const auto mat = Matrix<int>(data, 3,2);
    const auto b = Vector<int>({2, 3, 13});

    const auto solution = solve(mat, b).value();
    ASSERT_TRUE(solution.unique);

    const auto uniqueSolution = solution.uniqueSolution.value();
    ASSERT_EQ(uniqueSolution.dim(), mat.cols());
    ASSERT_EQ(uniqueSolution[0], 2);
    ASSERT_EQ(uniqueSolution[1], 3);

    const auto same_b = mat*uniqueSolution;
    ASSERT_EQ(same_b[0], b[0]);
    ASSERT_EQ(same_b[1], b[1]);
    ASSERT_EQ(same_b[2], b[2]);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankEqualsNumColumns, Strang_Chapter_2_2_problem_6_3x2_rank2_incompatible)
{
    const auto data = std::vector<int>{1,0,
                                       0,1,
                                       2,3};

    const auto mat = Matrix<int>(data, 3,2);
    const auto b = Vector<int>({2, 3, 14});

    const auto solution = solve(mat, b);
    ASSERT_TRUE(solution == std::nullopt);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankEqualsNumColumns, Strang_Chapter_2_2_problem_35a_4x2)
{
    const auto data = std::vector<int>{1,2,
                                       2,4,
                                       2,5,
                                       3,9};

    const auto mat = Matrix<int>(data, 4,2);
    const auto b = Vector<int>({1,2,3,6});

    const auto solution = solve(mat, b).value();
    ASSERT_TRUE(solution.unique);

    const auto uniqueSolution = solution.uniqueSolution.value();
    ASSERT_EQ(uniqueSolution.dim(), mat.cols());
    ASSERT_EQ(uniqueSolution[0], -1);
    ASSERT_EQ(uniqueSolution[1], 1);

    const auto same_b = mat*uniqueSolution;
    ASSERT_EQ(same_b[0], b[0]);
    ASSERT_EQ(same_b[1], b[1]);
    ASSERT_EQ(same_b[2], b[2]);
    ASSERT_EQ(same_b[3], b[3]);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankEqualsNumColumns, Strang_Chapter_2_2_problem_35a_4x2_incompatible)
{
    const auto data = std::vector<int>{1,2,
                                       2,4,
                                       2,5,
                                       3,9};
    ;

    const auto mat = Matrix<int>(data, 4,2);
    const auto vec = Vector<int>({1,2,3,4});

    const auto solution = solve(mat, vec);

    ASSERT_TRUE(solution == std::nullopt);
}

TEST_F(Matrix_SolveSystemLinearEquations_RankEqualsNumColumns, Ganga_chapter_4_4_problem8d_5x3_rank3_incompatible)
{
    const auto data = std::vector<int>{2,1,-1,
                                       3,-2,1,
                                       4,-2,1,
                                       1,1,1,
                                       1,3,-2};

    const auto mat = Matrix<int>(data, 5,3);

    auto b = Vector<int>({3,2,3,6,1});

    const auto solution = solve(mat, b);
    ASSERT_TRUE(solution == std::nullopt);
}
