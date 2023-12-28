//
// Created by dorian on 28.12.2023.
// stoicadorian@gmail.com
//
#include "gtest/gtest.h"
#include "Matrix.hpp"

using namespace LinearAlgebra::Matrix;
using namespace LinearAlgebra::Vector;

// Test scenarios involving row swaps during LU decomposition.
// In these cases the output result contains the permutation matrix and L*U = P*A

class MatrixLUFactorization_RowSwap : public ::testing::Test
{

protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(MatrixLUFactorization_RowSwap, Strang_Chapter_1_5_problem_13a_row_swap)
{
    const auto data = std::vector<int>{1,4,2,
                                       -2,-8,3,
                                       0,1,1};

    const auto matrix = Matrix<int>(data, 3, 3);

    const auto LU_Result  = matrix.LU();
    ASSERT_FALSE(LU_Result.permutation == std::nullopt); // P_23

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 0);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), -2);  ASSERT_EQ(LU_Result.lower(2,1), 0);   ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 1);   ASSERT_EQ(LU_Result.upper(0,1), 4);   ASSERT_EQ(LU_Result.upper(0,2), 2);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), 1);   ASSERT_EQ(LU_Result.upper(1,2), 1);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), 7);

    // Ensure L*U = P*A
    const auto LU = LU_Result.lower.multiply(LU_Result.upper);
    const auto PA = LU_Result.permutation->multiply(matrix);

    const double epsilon = 1e-9;
    ASSERT_NEAR(LU(0,0), PA(0,0), epsilon); ASSERT_NEAR(LU(0,1), PA(0,1), epsilon); ASSERT_NEAR(LU(0,2), PA(0,2), epsilon);
    ASSERT_NEAR(LU(1,0), PA(1,0), epsilon); ASSERT_NEAR(LU(1,1), PA(1,1), epsilon); ASSERT_NEAR(LU(1,2), PA(1,2), epsilon);
    ASSERT_NEAR(LU(2,0), PA(2,0), epsilon); ASSERT_NEAR(LU(2,1), PA(2,1), epsilon); ASSERT_NEAR(LU(2,2), PA(2,2), epsilon);
}

TEST_F(MatrixLUFactorization_RowSwap, Chapter_1_5_problem_13b_row_swap)
{
    const auto data = std::vector<int>{0,1,1,
                                       1,1,0,
                                       1,1,1};

    const auto matrix = Matrix<int>(data, 3, 3);

    const auto LU_Result  = matrix.LU();
    ASSERT_FALSE(LU_Result.permutation == std::nullopt);    // P_12

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 0);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 1);  ASSERT_EQ(LU_Result.lower(2,1), 0);   ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 1);   ASSERT_EQ(LU_Result.upper(0,1), 1);   ASSERT_EQ(LU_Result.upper(0,2), 0);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), 1);   ASSERT_EQ(LU_Result.upper(1,2), 1);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), 1);

    // Ensure L*U = P*A
    const auto LU = LU_Result.lower.multiply(LU_Result.upper);
    const auto PA = LU_Result.permutation->multiply(matrix);

    const double epsilon = 1e-9;
    ASSERT_NEAR(LU(0,0), PA(0,0), epsilon); ASSERT_NEAR(LU(0,1), PA(0,1), epsilon); ASSERT_NEAR(LU(0,2), PA(0,2), epsilon);
    ASSERT_NEAR(LU(1,0), PA(1,0), epsilon); ASSERT_NEAR(LU(1,1), PA(1,1), epsilon); ASSERT_NEAR(LU(1,2), PA(1,2), epsilon);
    ASSERT_NEAR(LU(2,0), PA(2,0), epsilon); ASSERT_NEAR(LU(2,1), PA(2,1), epsilon); ASSERT_NEAR(LU(2,2), PA(2,2), epsilon);
}


TEST_F(MatrixLUFactorization_RowSwap, Chapter_1_5_problem_15a_row_swap)
{
    const auto data = std::vector<int>{0,1,1,
                                       1,0,1,
                                       2,3,4};

    const auto matrix = Matrix<int>(data, 3, 3);

    const auto LU_Result  = matrix.LU();
    ASSERT_FALSE(LU_Result.permutation == std::nullopt);    // P_12

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 0);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 2);   ASSERT_EQ(LU_Result.lower(2,1), 3);   ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 1);   ASSERT_EQ(LU_Result.upper(0,1), 0);   ASSERT_EQ(LU_Result.upper(0,2), 1);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), 1);   ASSERT_EQ(LU_Result.upper(1,2), 1);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), -1);

    // Ensure L*U = P*A
    const auto LU = LU_Result.lower.multiply(LU_Result.upper);
    const auto PA = LU_Result.permutation->multiply(matrix);

    const double epsilon = 1e-9;
    ASSERT_NEAR(LU(0,0), PA(0,0), epsilon); ASSERT_NEAR(LU(0,1), PA(0,1), epsilon); ASSERT_NEAR(LU(0,2), PA(0,2), epsilon);
    ASSERT_NEAR(LU(1,0), PA(1,0), epsilon); ASSERT_NEAR(LU(1,1), PA(1,1), epsilon); ASSERT_NEAR(LU(1,2), PA(1,2), epsilon);
    ASSERT_NEAR(LU(2,0), PA(2,0), epsilon); ASSERT_NEAR(LU(2,1), PA(2,1), epsilon); ASSERT_NEAR(LU(2,2), PA(2,2), epsilon);
}

TEST_F(MatrixLUFactorization_RowSwap, Chapter_1_5_problem_15b_row_swap)
{
    const auto data = std::vector<int>{1,2,1,
                                       2,4,2,
                                       1,1,1};

    const auto matrix = Matrix<int>(data, 3, 3);

    const auto LU_Result  = matrix.LU();
    ASSERT_FALSE(LU_Result.permutation == std::nullopt);    // P_23

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 1);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 2);   ASSERT_EQ(LU_Result.lower(2,1), 0);   ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 1);   ASSERT_EQ(LU_Result.upper(0,1), 2);   ASSERT_EQ(LU_Result.upper(0,2), 1);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), -1);   ASSERT_EQ(LU_Result.upper(1,2), 0);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), 0);

    // Ensure L*U = P*A
    const auto LU = LU_Result.lower.multiply(LU_Result.upper);
    const auto PA = LU_Result.permutation->multiply(matrix);

    const double epsilon = 1e-9;
    ASSERT_NEAR(LU(0,0), PA(0,0), epsilon); ASSERT_NEAR(LU(0,1), PA(0,1), epsilon); ASSERT_NEAR(LU(0,2), PA(0,2), epsilon);
    ASSERT_NEAR(LU(1,0), PA(1,0), epsilon); ASSERT_NEAR(LU(1,1), PA(1,1), epsilon); ASSERT_NEAR(LU(1,2), PA(1,2), epsilon);
    ASSERT_NEAR(LU(2,0), PA(2,0), epsilon); ASSERT_NEAR(LU(2,1), PA(2,1), epsilon); ASSERT_NEAR(LU(2,2), PA(2,2), epsilon);
}
