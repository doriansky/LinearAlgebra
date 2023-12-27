//
// Created by dorian on 27.12.2023.
// stoicadorian@gmail.com
//
#include "gtest/gtest.h"
#include "Matrix.hpp"

using namespace LinearAlgebra::Matrix;
using namespace LinearAlgebra::Vector;

class MatrixLUFactorization_StrangTests : public ::testing::Test
{

protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(MatrixLUFactorization_StrangTests, Chapter_1_5_problem_2)
{
    const auto data = std::vector<int>{5,7,8,
                                       10,16,19,
                                       5,15,26};

    const auto mat = Matrix<int>(data, 3, 3);

    const auto LU_Result  = mat.LU();
    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 2);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 1);  ASSERT_EQ(LU_Result.lower(2,1),  4);   ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 5);   ASSERT_EQ(LU_Result.upper(0,1), 7);   ASSERT_EQ(LU_Result.upper(0,2), 8);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), 2);  ASSERT_EQ(LU_Result.upper(1,2), 3);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), 6);
}

TEST_F(MatrixLUFactorization_StrangTests, Chapter_1_5_problem_4b)
{
    const auto data = std::vector<int>{3,1, 1,
                                       1, 3, 1,
                                       1, 1, 3};

    const auto mat = Matrix<int>(data, 3, 3);

    const auto LU_Result  = mat.LU();
    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    const double epsilon = 1e-9;
    ASSERT_EQ(LU_Result.lower(0,0), 1);                       ASSERT_EQ(LU_Result.lower(0,1), 0);                   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_NEAR(LU_Result.lower(1,0), 1./3, epsilon);         ASSERT_EQ(LU_Result.lower(1,1), 1);                   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_NEAR(LU_Result.lower(2,0), 1./3, epsilon);         ASSERT_NEAR(LU_Result.lower(2,1), 1./4, epsilon);     ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper(0,0), 3);   ASSERT_EQ(LU_Result.upper(0,1), 1);                   ASSERT_EQ(LU_Result.upper(0,2), 1);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_NEAR(LU_Result.upper(1,1), 8./3, epsilon);     ASSERT_NEAR(LU_Result.upper(1,2), 2./3, epsilon);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);                   ASSERT_NEAR(LU_Result.upper(2,2), 15./6, epsilon);
}

TEST_F(MatrixLUFactorization_StrangTests, Chapter_1_5_problem_4c)
{
    const auto data = std::vector<int>{1,1,1,
                                       1,4,4,
                                       1,4,8};

    const auto mat = Matrix<int>(data, 3, 3);

    const auto LU_Result  = mat.LU();
    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 1);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 1);  ASSERT_EQ(LU_Result.lower(2,1),  1);   ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 1);   ASSERT_EQ(LU_Result.upper(0,1), 1);   ASSERT_EQ(LU_Result.upper(0,2), 1);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), 3);   ASSERT_EQ(LU_Result.upper(1,2), 3);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), 4);
}

TEST_F(MatrixLUFactorization_StrangTests, Chapter_1_5_problem_5)
{
    const auto data = std::vector<int>{2,3,3,
                                       0,5,7,
                                       6,9,8};

    const auto mat = Matrix<int>(data, 3, 3);

    const auto LU_Result  = mat.LU();
    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 0);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 3);  ASSERT_EQ(LU_Result.lower(2,1),  0);   ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 2);   ASSERT_EQ(LU_Result.upper(0,1), 3);   ASSERT_EQ(LU_Result.upper(0,2), 3);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), 5);   ASSERT_EQ(LU_Result.upper(1,2), 7);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), -1);
}

TEST_F(MatrixLUFactorization_StrangTests, Chapter_1_5_problem_13a_row_swap)
{
    const auto data = std::vector<int>{1,4,2,
                                       -2,-8,3,
                                       0,1,1};

    const auto mat = Matrix<int>(data, 3, 3);

    const auto LU_Result  = mat.LU();
    ASSERT_FALSE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 0);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), -2);  ASSERT_EQ(LU_Result.lower(2,1), 0);   ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 1);   ASSERT_EQ(LU_Result.upper(0,1), 4);   ASSERT_EQ(LU_Result.upper(0,2), 2);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), 1);   ASSERT_EQ(LU_Result.upper(1,2), 1);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), 7);
}

TEST_F(MatrixLUFactorization_StrangTests, Chapter_1_5_problem_13b_row_swap)
{
    const auto data = std::vector<int>{0,1,1,
                                       1,1,0,
                                       1,1,1};

    const auto mat = Matrix<int>(data, 3, 3);

    const auto LU_Result  = mat.LU();
    ASSERT_FALSE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 0);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 1);  ASSERT_EQ(LU_Result.lower(2,1), 0);   ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 1);   ASSERT_EQ(LU_Result.upper(0,1), 1);   ASSERT_EQ(LU_Result.upper(0,2), 0);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), 1);   ASSERT_EQ(LU_Result.upper(1,2), 1);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), 1);
}


TEST_F(MatrixLUFactorization_StrangTests, Chapter_1_5_problem_15a_row_swap)
{
    const auto data = std::vector<int>{0,1,1,
                                       1,0,1,
                                       2,3,4};

    const auto mat = Matrix<int>(data, 3, 3);

    const auto LU_Result  = mat.LU();
    ASSERT_FALSE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 0);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 2);   ASSERT_EQ(LU_Result.lower(2,1), 3);   ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 1);   ASSERT_EQ(LU_Result.upper(0,1), 0);   ASSERT_EQ(LU_Result.upper(0,2), 1);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), 1);   ASSERT_EQ(LU_Result.upper(1,2), 0);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), -1);
}

TEST_F(MatrixLUFactorization_StrangTests, Chapter_1_5_problem_15b_row_swap)
{
    const auto data = std::vector<int>{1,2,1,
                                       2,4,2,
                                       1,1,1};

    const auto mat = Matrix<int>(data, 3, 3);

    const auto LU_Result  = mat.LU();
    ASSERT_FALSE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 1);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 2);   ASSERT_EQ(LU_Result.lower(2,1), 0);   ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 1);   ASSERT_EQ(LU_Result.upper(0,1), 2);   ASSERT_EQ(LU_Result.upper(0,2), 1);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), -1);   ASSERT_EQ(LU_Result.upper(1,2), 0);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), 0);
}

TEST_F(MatrixLUFactorization_StrangTests, Chapter_1_5_problem_21)
{
    const auto data = std::vector<int>{1,1,1,
                                       1,2,3,
                                       1,3,6};

    const auto mat = Matrix<int>(data, 3, 3);

    const auto LU_Result  = mat.LU();
    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 1);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 1);  ASSERT_EQ(LU_Result.lower(2,1),  2);   ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 1);   ASSERT_EQ(LU_Result.upper(0,1), 1);   ASSERT_EQ(LU_Result.upper(0,2), 1);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), 1);   ASSERT_EQ(LU_Result.upper(1,2), 2);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), 1);
}

TEST_F(MatrixLUFactorization_StrangTests, Chapter_1_5_problem_23)
{
    const auto data = std::vector<int>{1,1,1,
                                       2,4,5,
                                       0,4,0};

    const auto mat = Matrix<int>(data, 3, 3);

    const auto LU_Result  = mat.LU();
    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 2);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 0);  ASSERT_EQ(LU_Result.lower(2,1),  2);   ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 1);   ASSERT_EQ(LU_Result.upper(0,1), 1);   ASSERT_EQ(LU_Result.upper(0,2), 1);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), 2);   ASSERT_EQ(LU_Result.upper(1,2), 3);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), -6);
}

TEST_F(MatrixLUFactorization_StrangTests, Chapter_1_5_problem_24)
{
    const auto data = std::vector<int>{1,0,1,
                                       2,2,2,
                                       3,4,5};

    const auto mat = Matrix<int>(data, 3, 3);

    const auto LU_Result  = mat.LU();
    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 2);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 3);  ASSERT_EQ(LU_Result.lower(2,1),  2);   ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 1);   ASSERT_EQ(LU_Result.upper(0,1), 0);   ASSERT_EQ(LU_Result.upper(0,2), 1);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), 2);   ASSERT_EQ(LU_Result.upper(1,2), 0);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), 2);
}

TEST_F(MatrixLUFactorization_StrangTests, Chapter_1_5_problem_27)
{
    const auto data = std::vector<int>{2,4,8,
                                       0,3,9,
                                       0,0,7};

    const auto mat = Matrix<int>(data, 3, 3);

    const auto LU_Result  = mat.LU();
    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 0);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 0);  ASSERT_EQ(LU_Result.lower(2,1),  0);   ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 2);   ASSERT_EQ(LU_Result.upper(0,1), 4);   ASSERT_EQ(LU_Result.upper(0,2), 8);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), 3);   ASSERT_EQ(LU_Result.upper(1,2), 9);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), 7);
}

TEST_F(MatrixLUFactorization_StrangTests, Chapter_1_5_problem_28b)
{
    const auto data = std::vector<int>{1,4,0,
                                       4,12,4,
                                       0,4,0};

    const auto mat = Matrix<int>(data, 3, 3);

    const auto LU_Result  = mat.LU();
    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 4);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 0);  ASSERT_EQ(LU_Result.lower(2,1),  -1);   ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 1);   ASSERT_EQ(LU_Result.upper(0,1), 4);   ASSERT_EQ(LU_Result.upper(0,2), 0);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), -4);   ASSERT_EQ(LU_Result.upper(1,2), 4);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), 4);
}

TEST_F(MatrixLUFactorization_StrangTests, Chapter_1_5_problem_31a)
{
    const auto data = std::vector<int>{1,1,0,
                                       1,2,1,
                                       0,1,2};

    const auto mat = Matrix<int>(data, 3, 3);

    const auto LU_Result  = mat.LU();
    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 1);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 0);  ASSERT_EQ(LU_Result.lower(2,1),  1);   ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 1);   ASSERT_EQ(LU_Result.upper(0,1), 1);   ASSERT_EQ(LU_Result.upper(0,2), 0);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), 1);   ASSERT_EQ(LU_Result.upper(1,2), 1);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), 1);
}

TEST_F(MatrixLUFactorization_StrangTests, Chapter_1_5_problem_33)
{
    const auto data = std::vector<int>{1,1,1,
                                       1,2,2,
                                       1,2,3};

    const auto mat = Matrix<int>(data, 3, 3);

    const auto LU_Result  = mat.LU();
    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 1);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 1);  ASSERT_EQ(LU_Result.lower(2,1),  1);   ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 1);   ASSERT_EQ(LU_Result.upper(0,1), 1);   ASSERT_EQ(LU_Result.upper(0,2), 1);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), 1);   ASSERT_EQ(LU_Result.upper(1,2), 1);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), 1);
}