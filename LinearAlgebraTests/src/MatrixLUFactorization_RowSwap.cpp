//
// Created by dorian on 28.12.2023.
// stoicadorian@gmail.com
//
#include "gtest/gtest.h"
#include "Matrix.hpp"
#include "MatrixHelpers.hpp"

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

    const auto LU_Result  = factorizeLU(matrix);
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
    const auto LU = LU_Result.lower * LU_Result.upper;
    const auto PA = LU_Result.permutation.value() * matrix;

    const double epsilon = 1e-9;
    ASSERT_NEAR(LU(0,0), PA(0,0), epsilon); ASSERT_NEAR(LU(0,1), PA(0,1), epsilon); ASSERT_NEAR(LU(0,2), PA(0,2), epsilon);
    ASSERT_NEAR(LU(1,0), PA(1,0), epsilon); ASSERT_NEAR(LU(1,1), PA(1,1), epsilon); ASSERT_NEAR(LU(1,2), PA(1,2), epsilon);
    ASSERT_NEAR(LU(2,0), PA(2,0), epsilon); ASSERT_NEAR(LU(2,1), PA(2,1), epsilon); ASSERT_NEAR(LU(2,2), PA(2,2), epsilon);

    // Test LU_echelon is outputting the same result (since this is non-singular matrix)
    const auto LU_echelon = factorizeLU_echelon(matrix);
    ASSERT_EQ(LU_echelon.upper.rows(), 3); ASSERT_EQ(LU_echelon.upper.cols(), 3);

    ASSERT_EQ(LU_Result.lower(0,0), LU_echelon.lower(0,0));   ASSERT_EQ(LU_Result.lower(0,1), LU_echelon.lower(0,1));   ASSERT_EQ(LU_Result.lower(0,2), LU_echelon.lower(0,2));
    ASSERT_EQ(LU_Result.lower(1,0), LU_echelon.lower(1,0));   ASSERT_EQ(LU_Result.lower(1,1), LU_echelon.lower(1,1));  ASSERT_EQ(LU_Result.lower(1,2),  LU_echelon.lower(1,2));
    ASSERT_EQ(LU_Result.lower(2,0), LU_echelon.lower(2,0));   ASSERT_EQ(LU_Result.lower(2,1), LU_echelon.lower(2,1));   ASSERT_EQ(LU_Result.lower(2,2), LU_echelon.lower(2,2));

    ASSERT_EQ(LU_Result.upper(0,0), LU_echelon.upper(0,0));   ASSERT_EQ(LU_Result.upper(0,1), LU_echelon.upper(0,1));   ASSERT_EQ(LU_Result.upper(0,2), LU_echelon.upper(0,2));
    ASSERT_EQ(LU_Result.upper(1,0), LU_echelon.upper(1,0));   ASSERT_EQ(LU_Result.upper(1,1), LU_echelon.upper(1,1));  ASSERT_EQ(LU_Result.upper(1,2),  LU_echelon.upper(1,2));
    ASSERT_EQ(LU_Result.upper(2,0), LU_echelon.upper(2,0));   ASSERT_EQ(LU_Result.upper(2,1), LU_echelon.upper(2,1));   ASSERT_EQ(LU_Result.upper(2,2), LU_echelon.upper(2,2));

    ASSERT_EQ(determinant(matrix), -7);
}

TEST_F(MatrixLUFactorization_RowSwap, Strang_Chapter_1_5_problem_13b_row_swap)
{
    const auto data = std::vector<int>{0,1,1,
                                       1,1,0,
                                       1,1,1};

    const auto matrix = Matrix<int>(data, 3, 3);

    const auto LU_Result  = factorizeLU(matrix);
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
    const auto LU = LU_Result.lower * LU_Result.upper;
    const auto PA = LU_Result.permutation.value() * matrix;

    const double epsilon = 1e-9;
    ASSERT_NEAR(LU(0,0), PA(0,0), epsilon); ASSERT_NEAR(LU(0,1), PA(0,1), epsilon); ASSERT_NEAR(LU(0,2), PA(0,2), epsilon);
    ASSERT_NEAR(LU(1,0), PA(1,0), epsilon); ASSERT_NEAR(LU(1,1), PA(1,1), epsilon); ASSERT_NEAR(LU(1,2), PA(1,2), epsilon);
    ASSERT_NEAR(LU(2,0), PA(2,0), epsilon); ASSERT_NEAR(LU(2,1), PA(2,1), epsilon); ASSERT_NEAR(LU(2,2), PA(2,2), epsilon);

    // Test LU_echelon is outputting the same result (since this is non-singular matrix)
    const auto LU_echelon = factorizeLU_echelon(matrix);
    ASSERT_EQ(LU_echelon.upper.rows(), 3); ASSERT_EQ(LU_echelon.upper.cols(), 3);

    ASSERT_EQ(LU_Result.lower(0,0), LU_echelon.lower(0,0));   ASSERT_EQ(LU_Result.lower(0,1), LU_echelon.lower(0,1));   ASSERT_EQ(LU_Result.lower(0,2), LU_echelon.lower(0,2));
    ASSERT_EQ(LU_Result.lower(1,0), LU_echelon.lower(1,0));   ASSERT_EQ(LU_Result.lower(1,1), LU_echelon.lower(1,1));  ASSERT_EQ(LU_Result.lower(1,2),  LU_echelon.lower(1,2));
    ASSERT_EQ(LU_Result.lower(2,0), LU_echelon.lower(2,0));   ASSERT_EQ(LU_Result.lower(2,1), LU_echelon.lower(2,1));   ASSERT_EQ(LU_Result.lower(2,2), LU_echelon.lower(2,2));

    ASSERT_EQ(LU_Result.upper(0,0), LU_echelon.upper(0,0));   ASSERT_EQ(LU_Result.upper(0,1), LU_echelon.upper(0,1));   ASSERT_EQ(LU_Result.upper(0,2), LU_echelon.upper(0,2));
    ASSERT_EQ(LU_Result.upper(1,0), LU_echelon.upper(1,0));   ASSERT_EQ(LU_Result.upper(1,1), LU_echelon.upper(1,1));  ASSERT_EQ(LU_Result.upper(1,2),  LU_echelon.upper(1,2));
    ASSERT_EQ(LU_Result.upper(2,0), LU_echelon.upper(2,0));   ASSERT_EQ(LU_Result.upper(2,1), LU_echelon.upper(2,1));   ASSERT_EQ(LU_Result.upper(2,2), LU_echelon.upper(2,2));

    ASSERT_EQ(determinant(matrix), -1);
}


TEST_F(MatrixLUFactorization_RowSwap, Strang_Chapter_1_5_problem_15a_row_swap)
{
    const auto data = std::vector<int>{0,1,1,
                                       1,0,1,
                                       2,3,4};

    const auto matrix = Matrix<int>(data, 3, 3);

    const auto LU_Result  = factorizeLU(matrix);
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
    const auto LU = LU_Result.lower * LU_Result.upper;
    const auto PA = LU_Result.permutation.value() * matrix;

    const double epsilon = 1e-9;
    ASSERT_NEAR(LU(0,0), PA(0,0), epsilon); ASSERT_NEAR(LU(0,1), PA(0,1), epsilon); ASSERT_NEAR(LU(0,2), PA(0,2), epsilon);
    ASSERT_NEAR(LU(1,0), PA(1,0), epsilon); ASSERT_NEAR(LU(1,1), PA(1,1), epsilon); ASSERT_NEAR(LU(1,2), PA(1,2), epsilon);
    ASSERT_NEAR(LU(2,0), PA(2,0), epsilon); ASSERT_NEAR(LU(2,1), PA(2,1), epsilon); ASSERT_NEAR(LU(2,2), PA(2,2), epsilon);

    // Test LU_echelon is outputting the same result (since this is non-singular matrix)
    const auto LU_echelon = factorizeLU_echelon(matrix);
    ASSERT_EQ(LU_echelon.upper.rows(), 3); ASSERT_EQ(LU_echelon.upper.cols(), 3);

    ASSERT_EQ(LU_Result.lower(0,0), LU_echelon.lower(0,0));   ASSERT_EQ(LU_Result.lower(0,1), LU_echelon.lower(0,1));   ASSERT_EQ(LU_Result.lower(0,2), LU_echelon.lower(0,2));
    ASSERT_EQ(LU_Result.lower(1,0), LU_echelon.lower(1,0));   ASSERT_EQ(LU_Result.lower(1,1), LU_echelon.lower(1,1));  ASSERT_EQ(LU_Result.lower(1,2),  LU_echelon.lower(1,2));
    ASSERT_EQ(LU_Result.lower(2,0), LU_echelon.lower(2,0));   ASSERT_EQ(LU_Result.lower(2,1), LU_echelon.lower(2,1));   ASSERT_EQ(LU_Result.lower(2,2), LU_echelon.lower(2,2));

    ASSERT_EQ(LU_Result.upper(0,0), LU_echelon.upper(0,0));   ASSERT_EQ(LU_Result.upper(0,1), LU_echelon.upper(0,1));   ASSERT_EQ(LU_Result.upper(0,2), LU_echelon.upper(0,2));
    ASSERT_EQ(LU_Result.upper(1,0), LU_echelon.upper(1,0));   ASSERT_EQ(LU_Result.upper(1,1), LU_echelon.upper(1,1));  ASSERT_EQ(LU_Result.upper(1,2),  LU_echelon.upper(1,2));
    ASSERT_EQ(LU_Result.upper(2,0), LU_echelon.upper(2,0));   ASSERT_EQ(LU_Result.upper(2,1), LU_echelon.upper(2,1));   ASSERT_EQ(LU_Result.upper(2,2), LU_echelon.upper(2,2));

    ASSERT_EQ(determinant(matrix), 1);
}

TEST_F(MatrixLUFactorization_RowSwap, Strang_Chapter_1_5_problem_15b_row_swap)
{
    const auto data = std::vector<int>{1,2,1,
                                       2,4,2,
                                       1,1,1};

    const auto matrix = Matrix<int>(data, 3, 3);

    const auto LU_Result  = factorizeLU(matrix);
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
    const auto LU = LU_Result.lower * LU_Result.upper;
    const auto PA = LU_Result.permutation.value() * matrix;

    const double epsilon = 1e-9;
    ASSERT_NEAR(LU(0,0), PA(0,0), epsilon); ASSERT_NEAR(LU(0,1), PA(0,1), epsilon); ASSERT_NEAR(LU(0,2), PA(0,2), epsilon);
    ASSERT_NEAR(LU(1,0), PA(1,0), epsilon); ASSERT_NEAR(LU(1,1), PA(1,1), epsilon); ASSERT_NEAR(LU(1,2), PA(1,2), epsilon);
    ASSERT_NEAR(LU(2,0), PA(2,0), epsilon); ASSERT_NEAR(LU(2,1), PA(2,1), epsilon); ASSERT_NEAR(LU(2,2), PA(2,2), epsilon);

    // Test LU_echelon is outputting the same result (since this is non-singular matrix)
    const auto LU_echelon = factorizeLU_echelon(matrix);
    ASSERT_EQ(LU_echelon.upper.rows(), 3); ASSERT_EQ(LU_echelon.upper.cols(), 3);

    ASSERT_EQ(LU_Result.lower(0,0), LU_echelon.lower(0,0));   ASSERT_EQ(LU_Result.lower(0,1), LU_echelon.lower(0,1));   ASSERT_EQ(LU_Result.lower(0,2), LU_echelon.lower(0,2));
    ASSERT_EQ(LU_Result.lower(1,0), LU_echelon.lower(1,0));   ASSERT_EQ(LU_Result.lower(1,1), LU_echelon.lower(1,1));  ASSERT_EQ(LU_Result.lower(1,2),  LU_echelon.lower(1,2));
    ASSERT_EQ(LU_Result.lower(2,0), LU_echelon.lower(2,0));   ASSERT_EQ(LU_Result.lower(2,1), LU_echelon.lower(2,1));   ASSERT_EQ(LU_Result.lower(2,2), LU_echelon.lower(2,2));

    ASSERT_EQ(LU_Result.upper(0,0), LU_echelon.upper(0,0));   ASSERT_EQ(LU_Result.upper(0,1), LU_echelon.upper(0,1));   ASSERT_EQ(LU_Result.upper(0,2), LU_echelon.upper(0,2));
    ASSERT_EQ(LU_Result.upper(1,0), LU_echelon.upper(1,0));   ASSERT_EQ(LU_Result.upper(1,1), LU_echelon.upper(1,1));  ASSERT_EQ(LU_Result.upper(1,2),  LU_echelon.upper(1,2));
    ASSERT_EQ(LU_Result.upper(2,0), LU_echelon.upper(2,0));   ASSERT_EQ(LU_Result.upper(2,1), LU_echelon.upper(2,1));   ASSERT_EQ(LU_Result.upper(2,2), LU_echelon.upper(2,2));

    ASSERT_EQ(determinant(matrix), 0);
}

TEST_F(MatrixLUFactorization_RowSwap, LUFactorization_4x4_WithRowSwap)
{
    const auto data = std::vector<int>{
                                        1,2,1,1,
                                        2,4,3,5,
                                        3,4,3,7,
                                        4,5,6,7};

    const auto matrix = Matrix<int>(data, 4, 4);

    const auto LU_Result  = factorizeLU(matrix);
    ASSERT_FALSE(LU_Result.permutation == std::nullopt);    // P_23

    const double epsilon = 1e-9;
    ASSERT_EQ(LU_Result.lower.rows(), 4); ASSERT_EQ(LU_Result.lower.cols(), 4);
    ASSERT_NEAR(LU_Result.lower(0,0), 1, epsilon);   ASSERT_NEAR(LU_Result.lower(0,1), 0, epsilon);   ASSERT_NEAR(LU_Result.lower(0,2), 0, epsilon); ASSERT_NEAR(LU_Result.lower(0,3), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(1,0), 3, epsilon);   ASSERT_NEAR(LU_Result.lower(1,1), 1, epsilon);   ASSERT_NEAR(LU_Result.lower(1,2), 0, epsilon); ASSERT_NEAR(LU_Result.lower(1,3), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(2,0), 2, epsilon);   ASSERT_NEAR(LU_Result.lower(2,1), 0, epsilon);   ASSERT_NEAR(LU_Result.lower(2,2), 1, epsilon); ASSERT_NEAR(LU_Result.lower(2,3), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(3,0), 4, epsilon);   ASSERT_NEAR(LU_Result.lower(3,1), 1.5, epsilon);   ASSERT_NEAR(LU_Result.lower(3,2), 2, epsilon); ASSERT_NEAR(LU_Result.lower(3,3), 1, epsilon);

    ASSERT_EQ(LU_Result.upper.rows(), 4); ASSERT_EQ(LU_Result.upper.cols(), 4);
    ASSERT_NEAR(LU_Result.upper(0,0), 1, epsilon);   ASSERT_NEAR(LU_Result.upper(0,1), 2, epsilon);   ASSERT_NEAR(LU_Result.upper(0,2), 1, epsilon); ASSERT_NEAR(LU_Result.upper(0,3), 1, epsilon);
    ASSERT_NEAR(LU_Result.upper(1,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(1,1), -2, epsilon);   ASSERT_NEAR(LU_Result.upper(1,2), 0, epsilon); ASSERT_NEAR(LU_Result.upper(1,3), 4, epsilon);
    ASSERT_NEAR(LU_Result.upper(2,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(2,1), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(2,2), 1, epsilon); ASSERT_NEAR(LU_Result.upper(2,3), 3, epsilon);
    ASSERT_NEAR(LU_Result.upper(3,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(3,1), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(3,2), 0, epsilon); ASSERT_NEAR(LU_Result.upper(3,3), -9, epsilon);

    // Ensure L*U = P*A
    const auto LU = LU_Result.lower * LU_Result.upper;
    const auto PA = LU_Result.permutation.value() * matrix;

    ASSERT_NEAR(LU(0,0), PA(0,0), epsilon); ASSERT_NEAR(LU(0,1), PA(0,1), epsilon); ASSERT_NEAR(LU(0,2), PA(0,2), epsilon); ASSERT_NEAR(LU(0,3), PA(0,3), epsilon);
    ASSERT_NEAR(LU(1,0), PA(1,0), epsilon); ASSERT_NEAR(LU(1,1), PA(1,1), epsilon); ASSERT_NEAR(LU(1,2), PA(1,2), epsilon); ASSERT_NEAR(LU(1,3), PA(1,3), epsilon);
    ASSERT_NEAR(LU(2,0), PA(2,0), epsilon); ASSERT_NEAR(LU(2,1), PA(2,1), epsilon); ASSERT_NEAR(LU(2,2), PA(2,2), epsilon); ASSERT_NEAR(LU(2,3), PA(2,3), epsilon);
    ASSERT_NEAR(LU(3,0), PA(3,0), epsilon); ASSERT_NEAR(LU(3,1), PA(3,1), epsilon); ASSERT_NEAR(LU(3,2), PA(3,2), epsilon); ASSERT_NEAR(LU(3,3), PA(3,3), epsilon);

    // Test LU_echelon is outputting the same result (since this is non-singular matrix)
    const auto LU_echelon = factorizeLU_echelon(matrix);
    ASSERT_EQ(LU_echelon.upper.rows(), 4); ASSERT_EQ(LU_echelon.upper.cols(), 4);

    ASSERT_EQ(LU_Result.lower(0,0), LU_echelon.lower(0,0));   ASSERT_EQ(LU_Result.lower(0,1), LU_echelon.lower(0,1));   ASSERT_EQ(LU_Result.lower(0,2), LU_echelon.lower(0,2));     ASSERT_EQ(LU_Result.lower(0,3), LU_echelon.lower(0,3));
    ASSERT_EQ(LU_Result.lower(1,0), LU_echelon.lower(1,0));   ASSERT_EQ(LU_Result.lower(1,1), LU_echelon.lower(1,1));   ASSERT_EQ(LU_Result.lower(1,2),  LU_echelon.lower(1,2));    ASSERT_EQ(LU_Result.lower(1,3), LU_echelon.lower(1,3));
    ASSERT_EQ(LU_Result.lower(2,0), LU_echelon.lower(2,0));   ASSERT_EQ(LU_Result.lower(2,1), LU_echelon.lower(2,1));   ASSERT_EQ(LU_Result.lower(2,2), LU_echelon.lower(2,2));     ASSERT_EQ(LU_Result.lower(2,3), LU_echelon.lower(2,3));
    ASSERT_EQ(LU_Result.lower(3,0), LU_echelon.lower(3,0));   ASSERT_EQ(LU_Result.lower(3,1), LU_echelon.lower(3,1));   ASSERT_EQ(LU_Result.lower(3,2), LU_echelon.lower(3,2));     ASSERT_EQ(LU_Result.lower(3,3), LU_echelon.lower(3,3));

    ASSERT_EQ(LU_Result.upper(0,0), LU_echelon.upper(0,0));   ASSERT_EQ(LU_Result.upper(0,1), LU_echelon.upper(0,1));   ASSERT_EQ(LU_Result.upper(0,2), LU_echelon.upper(0,2));     ASSERT_EQ(LU_Result.upper(0,3), LU_echelon.upper(0,3));
    ASSERT_EQ(LU_Result.upper(1,0), LU_echelon.upper(1,0));   ASSERT_EQ(LU_Result.upper(1,1), LU_echelon.upper(1,1));   ASSERT_EQ(LU_Result.upper(1,2),  LU_echelon.upper(1,2));    ASSERT_EQ(LU_Result.upper(1,3), LU_echelon.upper(1,3));
    ASSERT_EQ(LU_Result.upper(2,0), LU_echelon.upper(2,0));   ASSERT_EQ(LU_Result.upper(2,1), LU_echelon.upper(2,1));   ASSERT_EQ(LU_Result.upper(2,2), LU_echelon.upper(2,2));     ASSERT_EQ(LU_Result.upper(2,3), LU_echelon.upper(2,3));
    ASSERT_EQ(LU_Result.upper(3,0), LU_echelon.upper(3,0));   ASSERT_EQ(LU_Result.upper(3,1), LU_echelon.upper(3,1));   ASSERT_EQ(LU_Result.upper(3,2), LU_echelon.upper(3,2));     ASSERT_EQ(LU_Result.upper(3,3), LU_echelon.upper(3,3));

    ASSERT_EQ(determinant(matrix), -18);
}

TEST_F(MatrixLUFactorization_RowSwap, LUFactorization_5x5_WithRowSwap)
{
    const auto data = std::vector<int>{
            1,2,1,1,5,
            2,5,3,5,7,
            3,7,4,7,2,
            4,5,6,7,1,
            6,3,2,3,2};

    const auto matrix = Matrix<int>(data, 5, 5);

    const auto LU_Result  = factorizeLU(matrix);
    ASSERT_FALSE(LU_Result.permutation == std::nullopt);    // P_34  : the third pivot is zero, swap rows 3 and 4 (2 and 3 in this convention)

    const double epsilon = 1e-9;
    ASSERT_EQ(LU_Result.lower.rows(), 5); ASSERT_EQ(LU_Result.lower.cols(), 5);
    ASSERT_NEAR(LU_Result.lower(0,0), 1, epsilon);   ASSERT_NEAR(LU_Result.lower(0,1), 0, epsilon);     ASSERT_NEAR(LU_Result.lower(0,2), 0, epsilon); ASSERT_NEAR(LU_Result.lower(0,3), 0, epsilon); ASSERT_NEAR(LU_Result.lower(0,4), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(1,0), 2, epsilon);   ASSERT_NEAR(LU_Result.lower(1,1), 1, epsilon);     ASSERT_NEAR(LU_Result.lower(1,2), 0, epsilon); ASSERT_NEAR(LU_Result.lower(1,3), 0, epsilon); ASSERT_NEAR(LU_Result.lower(1,4), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(2,0), 4, epsilon);   ASSERT_NEAR(LU_Result.lower(2,1), -3, epsilon);    ASSERT_NEAR(LU_Result.lower(2,2), 1, epsilon); ASSERT_NEAR(LU_Result.lower(2,3), 0, epsilon); ASSERT_NEAR(LU_Result.lower(2,4), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(3,0), 3, epsilon);   ASSERT_NEAR(LU_Result.lower(3,1), 1, epsilon);     ASSERT_NEAR(LU_Result.lower(3,2), 0, epsilon); ASSERT_NEAR(LU_Result.lower(3,3), 1, epsilon); ASSERT_NEAR(LU_Result.lower(3,4), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(4,0), 6, epsilon);   ASSERT_NEAR(LU_Result.lower(4,1), -9, epsilon);    ASSERT_NEAR(LU_Result.lower(4,2), 1, epsilon); ASSERT_NEAR(LU_Result.lower(4,3), 12, epsilon); ASSERT_NEAR(LU_Result.lower(4,4), 1, epsilon);

    ASSERT_EQ(LU_Result.upper.rows(), 5); ASSERT_EQ(LU_Result.upper.cols(), 5);
    ASSERT_NEAR(LU_Result.upper(0,0), 1, epsilon);   ASSERT_NEAR(LU_Result.upper(0,1), 2, epsilon);     ASSERT_NEAR(LU_Result.upper(0,2), 1, epsilon); ASSERT_NEAR(LU_Result.upper(0,3), 1, epsilon); ASSERT_NEAR(LU_Result.upper(0,4), 5, epsilon);
    ASSERT_NEAR(LU_Result.upper(1,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(1,1), 1, epsilon);    ASSERT_NEAR(LU_Result.upper(1,2), 1, epsilon); ASSERT_NEAR(LU_Result.upper(1,3), 3, epsilon); ASSERT_NEAR(LU_Result.upper(1,4), -3, epsilon);
    ASSERT_NEAR(LU_Result.upper(2,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(2,1), 0, epsilon);     ASSERT_NEAR(LU_Result.upper(2,2), 5, epsilon); ASSERT_NEAR(LU_Result.upper(2,3), 12, epsilon); ASSERT_NEAR(LU_Result.upper(2,4), -28, epsilon);
    ASSERT_NEAR(LU_Result.upper(3,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(3,1), 0, epsilon);     ASSERT_NEAR(LU_Result.upper(3,2), 0, epsilon); ASSERT_NEAR(LU_Result.upper(3,3), 1, epsilon); ASSERT_NEAR(LU_Result.upper(3,4), -10, epsilon);
    ASSERT_NEAR(LU_Result.upper(4,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(4,1), 0, epsilon);     ASSERT_NEAR(LU_Result.upper(4,2), 0, epsilon); ASSERT_NEAR(LU_Result.upper(4,3), 0, epsilon); ASSERT_NEAR(LU_Result.upper(4,4), 93, epsilon);

    // Ensure L*U = P*A
    const auto LU = LU_Result.lower * LU_Result.upper;
    const auto PA = LU_Result.permutation.value() * matrix;

    ASSERT_NEAR(LU(0,0), PA(0,0), epsilon); ASSERT_NEAR(LU(0,1), PA(0,1), epsilon); ASSERT_NEAR(LU(0,2), PA(0,2), epsilon); ASSERT_NEAR(LU(0,3), PA(0,3), epsilon); ASSERT_NEAR(LU(0,4), PA(0,4), epsilon);
    ASSERT_NEAR(LU(1,0), PA(1,0), epsilon); ASSERT_NEAR(LU(1,1), PA(1,1), epsilon); ASSERT_NEAR(LU(1,2), PA(1,2), epsilon); ASSERT_NEAR(LU(1,3), PA(1,3), epsilon); ASSERT_NEAR(LU(1,4), PA(1,4), epsilon);
    ASSERT_NEAR(LU(2,0), PA(2,0), epsilon); ASSERT_NEAR(LU(2,1), PA(2,1), epsilon); ASSERT_NEAR(LU(2,2), PA(2,2), epsilon); ASSERT_NEAR(LU(2,3), PA(2,3), epsilon); ASSERT_NEAR(LU(2,4), PA(2,4), epsilon);
    ASSERT_NEAR(LU(3,0), PA(3,0), epsilon); ASSERT_NEAR(LU(3,1), PA(3,1), epsilon); ASSERT_NEAR(LU(3,2), PA(3,2), epsilon); ASSERT_NEAR(LU(3,3), PA(3,3), epsilon); ASSERT_NEAR(LU(3,4), PA(3,4), epsilon);
    ASSERT_NEAR(LU(4,0), PA(4,0), epsilon); ASSERT_NEAR(LU(4,1), PA(4,1), epsilon); ASSERT_NEAR(LU(4,2), PA(4,2), epsilon); ASSERT_NEAR(LU(4,3), PA(4,3), epsilon); ASSERT_NEAR(LU(4,4), PA(4,4), epsilon);

    // Test LU_echelon is outputting the same result (since this is non-singular matrix)
    const auto LU_echelon = factorizeLU_echelon(matrix);
    ASSERT_EQ(LU_echelon.upper.rows(), 5); ASSERT_EQ(LU_echelon.upper.cols(), 5);

    ASSERT_EQ(LU_Result.lower(0,0), LU_echelon.lower(0,0));   ASSERT_EQ(LU_Result.lower(0,1), LU_echelon.lower(0,1));   ASSERT_EQ(LU_Result.lower(0,2), LU_echelon.lower(0,2));     ASSERT_EQ(LU_Result.lower(0,3), LU_echelon.lower(0,3));     ASSERT_EQ(LU_Result.lower(0,4), LU_echelon.lower(0,4));
    ASSERT_EQ(LU_Result.lower(1,0), LU_echelon.lower(1,0));   ASSERT_EQ(LU_Result.lower(1,1), LU_echelon.lower(1,1));   ASSERT_EQ(LU_Result.lower(1,2),  LU_echelon.lower(1,2));    ASSERT_EQ(LU_Result.lower(1,3), LU_echelon.lower(1,3));     ASSERT_EQ(LU_Result.lower(1,4), LU_echelon.lower(1,4));
    ASSERT_EQ(LU_Result.lower(2,0), LU_echelon.lower(2,0));   ASSERT_EQ(LU_Result.lower(2,1), LU_echelon.lower(2,1));   ASSERT_EQ(LU_Result.lower(2,2), LU_echelon.lower(2,2));     ASSERT_EQ(LU_Result.lower(2,3), LU_echelon.lower(2,3));     ASSERT_EQ(LU_Result.lower(2,4), LU_echelon.lower(2,4));
    ASSERT_EQ(LU_Result.lower(3,0), LU_echelon.lower(3,0));   ASSERT_EQ(LU_Result.lower(3,1), LU_echelon.lower(3,1));   ASSERT_EQ(LU_Result.lower(3,2), LU_echelon.lower(3,2));     ASSERT_EQ(LU_Result.lower(3,3), LU_echelon.lower(3,3));     ASSERT_EQ(LU_Result.lower(3,4), LU_echelon.lower(3,4));
    ASSERT_EQ(LU_Result.lower(4,0), LU_echelon.lower(4,0));   ASSERT_EQ(LU_Result.lower(4,1), LU_echelon.lower(4,1));   ASSERT_EQ(LU_Result.lower(4,2), LU_echelon.lower(4,2));     ASSERT_EQ(LU_Result.lower(4,3), LU_echelon.lower(4,3));     ASSERT_EQ(LU_Result.lower(4,4), LU_echelon.lower(4,4));

    ASSERT_EQ(LU_Result.upper(0,0), LU_echelon.upper(0,0));   ASSERT_EQ(LU_Result.upper(0,1), LU_echelon.upper(0,1));   ASSERT_EQ(LU_Result.upper(0,2), LU_echelon.upper(0,2));     ASSERT_EQ(LU_Result.upper(0,3), LU_echelon.upper(0,3));     ASSERT_EQ(LU_Result.upper(0,4), LU_echelon.upper(0,4));
    ASSERT_EQ(LU_Result.upper(1,0), LU_echelon.upper(1,0));   ASSERT_EQ(LU_Result.upper(1,1), LU_echelon.upper(1,1));   ASSERT_EQ(LU_Result.upper(1,2),  LU_echelon.upper(1,2));    ASSERT_EQ(LU_Result.upper(1,3), LU_echelon.upper(1,3));     ASSERT_EQ(LU_Result.upper(1,4), LU_echelon.upper(1,4));
    ASSERT_EQ(LU_Result.upper(2,0), LU_echelon.upper(2,0));   ASSERT_EQ(LU_Result.upper(2,1), LU_echelon.upper(2,1));   ASSERT_EQ(LU_Result.upper(2,2), LU_echelon.upper(2,2));     ASSERT_EQ(LU_Result.upper(2,3), LU_echelon.upper(2,3));     ASSERT_EQ(LU_Result.upper(2,4), LU_echelon.upper(2,4));
    ASSERT_EQ(LU_Result.upper(3,0), LU_echelon.upper(3,0));   ASSERT_EQ(LU_Result.upper(3,1), LU_echelon.upper(3,1));   ASSERT_EQ(LU_Result.upper(3,2), LU_echelon.upper(3,2));     ASSERT_EQ(LU_Result.upper(3,3), LU_echelon.upper(3,3));     ASSERT_EQ(LU_Result.upper(3,4), LU_echelon.upper(3,4));
    ASSERT_EQ(LU_Result.upper(4,0), LU_echelon.upper(4,0));   ASSERT_EQ(LU_Result.upper(4,1), LU_echelon.upper(4,1));   ASSERT_EQ(LU_Result.upper(4,2), LU_echelon.upper(4,2));     ASSERT_EQ(LU_Result.upper(4,3), LU_echelon.upper(4,3));     ASSERT_EQ(LU_Result.upper(4,4), LU_echelon.upper(4,4));

    ASSERT_EQ(determinant(matrix), -465);
}

TEST_F(MatrixLUFactorization_RowSwap, LUFactorization_7x7_WithRowSwap_Example_1)
{
    const auto data = std::vector<int>{
            1,  1,  1,  1,  1,  1,  1,
            2,  5,  4,  5,  1,  7,  8,
            3,  4,  5,  6,  1,  8,  9,
            4,  8,  6,  7,  1,  9,  10,
            5,  12, 7,  18, 6,  10, 11,
            6,  7,  8,  11, 5,  17, 12,
            7,  8,  9,  10, 11, 12, 14};

    const auto matrix = Matrix<int>(data, 7, 7);

    const auto LU_Result  = factorizeLU(matrix);
    ASSERT_FALSE(LU_Result.permutation == std::nullopt);    // P_45  : the 4th pivot is zero, swap rows 4 and 5 (3 and 4 in this convention)

    const double epsilon = 1e-9;
    ASSERT_EQ(LU_Result.lower.rows(), 7); ASSERT_EQ(LU_Result.lower.cols(), 7);
    ASSERT_NEAR(LU_Result.lower(0,0), 1, epsilon);   ASSERT_NEAR(LU_Result.lower(0,1), 0, epsilon);             ASSERT_NEAR(LU_Result.lower(0,2), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(0,3), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(0,4), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(0,5), 0, epsilon);  ASSERT_NEAR(LU_Result.lower(0,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(1,0), 2, epsilon);   ASSERT_NEAR(LU_Result.lower(1,1), 1, epsilon);             ASSERT_NEAR(LU_Result.lower(1,2), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(1,3), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(1,4), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(1,5), 0, epsilon);  ASSERT_NEAR(LU_Result.lower(1,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(2,0), 3, epsilon);   ASSERT_NEAR(LU_Result.lower(2,1), 0.3333333333, epsilon);  ASSERT_NEAR(LU_Result.lower(2,2), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(2,3), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(2,4), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(2,5), 0, epsilon);  ASSERT_NEAR(LU_Result.lower(2,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(3,0), 5, epsilon);   ASSERT_NEAR(LU_Result.lower(3,1), 2.3333333333, epsilon);  ASSERT_NEAR(LU_Result.lower(3,2), -2, epsilon);     ASSERT_NEAR(LU_Result.lower(3,3), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(3,4), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(3,5), 0, epsilon);  ASSERT_NEAR(LU_Result.lower(3,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(4,0), 4, epsilon);   ASSERT_NEAR(LU_Result.lower(4,1), 1.3333333333, epsilon);  ASSERT_NEAR(LU_Result.lower(4,2), -0.5, epsilon);   ASSERT_NEAR(LU_Result.lower(4,3), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(4,4), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(4,5), 0, epsilon);  ASSERT_NEAR(LU_Result.lower(4,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(5,0), 6, epsilon);   ASSERT_NEAR(LU_Result.lower(5,1), 0.3333333333, epsilon);  ASSERT_NEAR(LU_Result.lower(5,2), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(5,3), 0.2, epsilon);    ASSERT_NEAR(LU_Result.lower(5,4), -0.4, epsilon);   ASSERT_NEAR(LU_Result.lower(5,5), 1, epsilon);  ASSERT_NEAR(LU_Result.lower(5,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(6,0), 7, epsilon);   ASSERT_NEAR(LU_Result.lower(6,1), 0.3333333333, epsilon);  ASSERT_NEAR(LU_Result.lower(6,2), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(6,3), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(6,4), -2.4, epsilon);   ASSERT_NEAR(LU_Result.lower(6,5), 0, epsilon);  ASSERT_NEAR(LU_Result.lower(6,6), 1, epsilon);

    ASSERT_EQ(LU_Result.upper.rows(), 7); ASSERT_EQ(LU_Result.upper.cols(), 7);
    ASSERT_NEAR(LU_Result.upper(0,0), 1, epsilon);   ASSERT_NEAR(LU_Result.upper(0,1), 1, epsilon);     ASSERT_NEAR(LU_Result.upper(0,2), 1, epsilon);              ASSERT_NEAR(LU_Result.upper(0,3), 1, epsilon);      ASSERT_NEAR(LU_Result.upper(0,4), 1, epsilon);              ASSERT_NEAR(LU_Result.upper(0,5), 1, epsilon);              ASSERT_NEAR(LU_Result.upper(0,6), 1, epsilon);
    ASSERT_NEAR(LU_Result.upper(1,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(1,1), 3, epsilon);     ASSERT_NEAR(LU_Result.upper(1,2), 2, epsilon);              ASSERT_NEAR(LU_Result.upper(1,3), 3, epsilon);      ASSERT_NEAR(LU_Result.upper(1,4), -1, epsilon);             ASSERT_NEAR(LU_Result.upper(1,5), 5, epsilon);              ASSERT_NEAR(LU_Result.upper(1,6), 6, epsilon);
    ASSERT_NEAR(LU_Result.upper(2,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(2,1), 0, epsilon);     ASSERT_NEAR(LU_Result.upper(2,2), 1.333333333, epsilon);    ASSERT_NEAR(LU_Result.upper(2,3), 2, epsilon);      ASSERT_NEAR(LU_Result.upper(2,4), -1.666666666, epsilon);   ASSERT_NEAR(LU_Result.upper(2,5), 3.333333333, epsilon);    ASSERT_NEAR(LU_Result.upper(2,6), 4, epsilon);
    ASSERT_NEAR(LU_Result.upper(3,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(3,1), 0, epsilon);     ASSERT_NEAR(LU_Result.upper(3,2), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(3,3), 10, epsilon);     ASSERT_NEAR(LU_Result.upper(3,4), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(3,5), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(3,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.upper(4,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(4,1), 0, epsilon);     ASSERT_NEAR(LU_Result.upper(4,2), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(4,3), 0, epsilon);      ASSERT_NEAR(LU_Result.upper(4,4), -2.5, epsilon);           ASSERT_NEAR(LU_Result.upper(4,5), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(4,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.upper(5,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(5,1), 0, epsilon);     ASSERT_NEAR(LU_Result.upper(5,2), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(5,3), 0, epsilon);      ASSERT_NEAR(LU_Result.upper(5,4), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(5,5), 6, epsilon);              ASSERT_NEAR(LU_Result.upper(5,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.upper(6,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(6,1), 0, epsilon);     ASSERT_NEAR(LU_Result.upper(6,2), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(6,3), 0, epsilon);      ASSERT_NEAR(LU_Result.upper(6,4), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(6,5), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(6,6), 1, epsilon);

    // Ensure L*U = P*A
    const auto LU = LU_Result.lower * LU_Result.upper;
    const auto PA = LU_Result.permutation.value() * matrix;

    ASSERT_NEAR(LU(0,0), PA(0,0), epsilon); ASSERT_NEAR(LU(0,1), PA(0,1), epsilon); ASSERT_NEAR(LU(0,2), PA(0,2), epsilon); ASSERT_NEAR(LU(0,3), PA(0,3), epsilon); ASSERT_NEAR(LU(0,4), PA(0,4), epsilon); ASSERT_NEAR(LU(0,5), PA(0,5), epsilon); ASSERT_NEAR(LU(0,6), PA(0,6), epsilon);
    ASSERT_NEAR(LU(1,0), PA(1,0), epsilon); ASSERT_NEAR(LU(1,1), PA(1,1), epsilon); ASSERT_NEAR(LU(1,2), PA(1,2), epsilon); ASSERT_NEAR(LU(1,3), PA(1,3), epsilon); ASSERT_NEAR(LU(1,4), PA(1,4), epsilon); ASSERT_NEAR(LU(1,5), PA(1,5), epsilon); ASSERT_NEAR(LU(1,6), PA(1,6), epsilon);
    ASSERT_NEAR(LU(2,0), PA(2,0), epsilon); ASSERT_NEAR(LU(2,1), PA(2,1), epsilon); ASSERT_NEAR(LU(2,2), PA(2,2), epsilon); ASSERT_NEAR(LU(2,3), PA(2,3), epsilon); ASSERT_NEAR(LU(2,4), PA(2,4), epsilon); ASSERT_NEAR(LU(2,5), PA(2,5), epsilon); ASSERT_NEAR(LU(2,6), PA(2,6), epsilon);
    ASSERT_NEAR(LU(3,0), PA(3,0), epsilon); ASSERT_NEAR(LU(3,1), PA(3,1), epsilon); ASSERT_NEAR(LU(3,2), PA(3,2), epsilon); ASSERT_NEAR(LU(3,3), PA(3,3), epsilon); ASSERT_NEAR(LU(3,4), PA(3,4), epsilon); ASSERT_NEAR(LU(3,5), PA(3,5), epsilon); ASSERT_NEAR(LU(3,6), PA(3,6), epsilon);
    ASSERT_NEAR(LU(4,0), PA(4,0), epsilon); ASSERT_NEAR(LU(4,1), PA(4,1), epsilon); ASSERT_NEAR(LU(4,2), PA(4,2), epsilon); ASSERT_NEAR(LU(4,3), PA(4,3), epsilon); ASSERT_NEAR(LU(4,4), PA(4,4), epsilon); ASSERT_NEAR(LU(4,5), PA(4,5), epsilon); ASSERT_NEAR(LU(4,6), PA(4,6), epsilon);
    ASSERT_NEAR(LU(5,0), PA(5,0), epsilon); ASSERT_NEAR(LU(5,1), PA(5,1), epsilon); ASSERT_NEAR(LU(5,2), PA(5,2), epsilon); ASSERT_NEAR(LU(5,3), PA(5,3), epsilon); ASSERT_NEAR(LU(5,4), PA(5,4), epsilon); ASSERT_NEAR(LU(5,5), PA(5,5), epsilon); ASSERT_NEAR(LU(5,6), PA(5,6), epsilon);
    ASSERT_NEAR(LU(6,0), PA(6,0), epsilon); ASSERT_NEAR(LU(6,1), PA(6,1), epsilon); ASSERT_NEAR(LU(6,2), PA(6,2), epsilon); ASSERT_NEAR(LU(6,3), PA(6,3), epsilon); ASSERT_NEAR(LU(6,4), PA(6,4), epsilon); ASSERT_NEAR(LU(6,5), PA(6,5), epsilon); ASSERT_NEAR(LU(6,6), PA(6,6), epsilon);

    // Test LU_echelon is outputting the same result (since this is non-singular matrix)
    const auto LU_echelon = factorizeLU_echelon(matrix);
    ASSERT_EQ(LU_echelon.upper.rows(), 7); ASSERT_EQ(LU_echelon.upper.cols(), 7);

    ASSERT_EQ(LU_Result.lower(0,0), LU_echelon.lower(0,0));   ASSERT_EQ(LU_Result.lower(0,1), LU_echelon.lower(0,1));   ASSERT_EQ(LU_Result.lower(0,2), LU_echelon.lower(0,2));     ASSERT_EQ(LU_Result.lower(0,3), LU_echelon.lower(0,3));     ASSERT_EQ(LU_Result.lower(0,4), LU_echelon.lower(0,4));     ASSERT_EQ(LU_Result.lower(0,5), LU_echelon.lower(0,5));     ASSERT_EQ(LU_Result.lower(0,6), LU_echelon.lower(0,6));
    ASSERT_EQ(LU_Result.lower(1,0), LU_echelon.lower(1,0));   ASSERT_EQ(LU_Result.lower(1,1), LU_echelon.lower(1,1));   ASSERT_EQ(LU_Result.lower(1,2),  LU_echelon.lower(1,2));    ASSERT_EQ(LU_Result.lower(1,3), LU_echelon.lower(1,3));     ASSERT_EQ(LU_Result.lower(1,4), LU_echelon.lower(1,4));     ASSERT_EQ(LU_Result.lower(1,5), LU_echelon.lower(1,5));     ASSERT_EQ(LU_Result.lower(1,6), LU_echelon.lower(1,6));
    ASSERT_EQ(LU_Result.lower(2,0), LU_echelon.lower(2,0));   ASSERT_EQ(LU_Result.lower(2,1), LU_echelon.lower(2,1));   ASSERT_EQ(LU_Result.lower(2,2), LU_echelon.lower(2,2));     ASSERT_EQ(LU_Result.lower(2,3), LU_echelon.lower(2,3));     ASSERT_EQ(LU_Result.lower(2,4), LU_echelon.lower(2,4));     ASSERT_EQ(LU_Result.lower(2,5), LU_echelon.lower(2,5));     ASSERT_EQ(LU_Result.lower(2,6), LU_echelon.lower(2,6));
    ASSERT_EQ(LU_Result.lower(3,0), LU_echelon.lower(3,0));   ASSERT_EQ(LU_Result.lower(3,1), LU_echelon.lower(3,1));   ASSERT_EQ(LU_Result.lower(3,2), LU_echelon.lower(3,2));     ASSERT_EQ(LU_Result.lower(3,3), LU_echelon.lower(3,3));     ASSERT_EQ(LU_Result.lower(3,4), LU_echelon.lower(3,4));     ASSERT_EQ(LU_Result.lower(3,5), LU_echelon.lower(3,5));     ASSERT_EQ(LU_Result.lower(3,6), LU_echelon.lower(3,6));
    ASSERT_EQ(LU_Result.lower(4,0), LU_echelon.lower(4,0));   ASSERT_EQ(LU_Result.lower(4,1), LU_echelon.lower(4,1));   ASSERT_EQ(LU_Result.lower(4,2), LU_echelon.lower(4,2));     ASSERT_EQ(LU_Result.lower(4,3), LU_echelon.lower(4,3));     ASSERT_EQ(LU_Result.lower(4,4), LU_echelon.lower(4,4));     ASSERT_EQ(LU_Result.lower(4,5), LU_echelon.lower(4,5));     ASSERT_EQ(LU_Result.lower(4,6), LU_echelon.lower(4,6));
    ASSERT_EQ(LU_Result.lower(5,0), LU_echelon.lower(5,0));   ASSERT_EQ(LU_Result.lower(5,1), LU_echelon.lower(5,1));   ASSERT_EQ(LU_Result.lower(5,2), LU_echelon.lower(5,2));     ASSERT_EQ(LU_Result.lower(5,3), LU_echelon.lower(5,3));     ASSERT_EQ(LU_Result.lower(5,4), LU_echelon.lower(5,4));     ASSERT_EQ(LU_Result.lower(5,5), LU_echelon.lower(5,5));     ASSERT_EQ(LU_Result.lower(5,6), LU_echelon.lower(5,6));
    ASSERT_EQ(LU_Result.lower(6,0), LU_echelon.lower(6,0));   ASSERT_EQ(LU_Result.lower(6,1), LU_echelon.lower(6,1));   ASSERT_EQ(LU_Result.lower(6,2), LU_echelon.lower(6,2));     ASSERT_EQ(LU_Result.lower(6,3), LU_echelon.lower(6,3));     ASSERT_EQ(LU_Result.lower(6,4), LU_echelon.lower(6,4));     ASSERT_EQ(LU_Result.lower(6,5), LU_echelon.lower(6,5));     ASSERT_EQ(LU_Result.lower(6,6), LU_echelon.lower(6,6));

    ASSERT_EQ(LU_Result.upper(0,0), LU_echelon.upper(0,0));   ASSERT_EQ(LU_Result.upper(0,1), LU_echelon.upper(0,1));   ASSERT_EQ(LU_Result.upper(0,2), LU_echelon.upper(0,2));     ASSERT_EQ(LU_Result.upper(0,3), LU_echelon.upper(0,3));     ASSERT_EQ(LU_Result.upper(0,4), LU_echelon.upper(0,4));     ASSERT_EQ(LU_Result.upper(0,5), LU_echelon.upper(0,5));     ASSERT_EQ(LU_Result.upper(0,6), LU_echelon.upper(0,6));
    ASSERT_EQ(LU_Result.upper(1,0), LU_echelon.upper(1,0));   ASSERT_EQ(LU_Result.upper(1,1), LU_echelon.upper(1,1));   ASSERT_EQ(LU_Result.upper(1,2),  LU_echelon.upper(1,2));    ASSERT_EQ(LU_Result.upper(1,3), LU_echelon.upper(1,3));     ASSERT_EQ(LU_Result.upper(1,4), LU_echelon.upper(1,4));     ASSERT_EQ(LU_Result.upper(1,5), LU_echelon.upper(1,5));     ASSERT_EQ(LU_Result.upper(1,6), LU_echelon.upper(1,6));
    ASSERT_EQ(LU_Result.upper(2,0), LU_echelon.upper(2,0));   ASSERT_EQ(LU_Result.upper(2,1), LU_echelon.upper(2,1));   ASSERT_EQ(LU_Result.upper(2,2), LU_echelon.upper(2,2));     ASSERT_EQ(LU_Result.upper(2,3), LU_echelon.upper(2,3));     ASSERT_EQ(LU_Result.upper(2,4), LU_echelon.upper(2,4));     ASSERT_EQ(LU_Result.upper(2,5), LU_echelon.upper(2,5));     ASSERT_EQ(LU_Result.upper(2,6), LU_echelon.upper(2,6));
    ASSERT_EQ(LU_Result.upper(3,0), LU_echelon.upper(3,0));   ASSERT_EQ(LU_Result.upper(3,1), LU_echelon.upper(3,1));   ASSERT_EQ(LU_Result.upper(3,2), LU_echelon.upper(3,2));     ASSERT_EQ(LU_Result.upper(3,3), LU_echelon.upper(3,3));     ASSERT_EQ(LU_Result.upper(3,4), LU_echelon.upper(3,4));     ASSERT_EQ(LU_Result.upper(3,5), LU_echelon.upper(3,5));     ASSERT_EQ(LU_Result.upper(3,6), LU_echelon.upper(3,6));
    ASSERT_EQ(LU_Result.upper(4,0), LU_echelon.upper(4,0));   ASSERT_EQ(LU_Result.upper(4,1), LU_echelon.upper(4,1));   ASSERT_EQ(LU_Result.upper(4,2), LU_echelon.upper(4,2));     ASSERT_EQ(LU_Result.upper(4,3), LU_echelon.upper(4,3));     ASSERT_EQ(LU_Result.upper(4,4), LU_echelon.upper(4,4));     ASSERT_EQ(LU_Result.upper(4,5), LU_echelon.upper(4,5));     ASSERT_EQ(LU_Result.upper(4,6), LU_echelon.upper(4,6));
    ASSERT_EQ(LU_Result.upper(5,0), LU_echelon.upper(5,0));   ASSERT_EQ(LU_Result.upper(5,1), LU_echelon.upper(5,1));   ASSERT_EQ(LU_Result.upper(5,2), LU_echelon.upper(5,2));     ASSERT_EQ(LU_Result.upper(5,3), LU_echelon.upper(5,3));     ASSERT_EQ(LU_Result.upper(5,4), LU_echelon.upper(5,4));     ASSERT_EQ(LU_Result.upper(5,5), LU_echelon.upper(5,5));     ASSERT_EQ(LU_Result.upper(5,6), LU_echelon.upper(5,6));
    ASSERT_EQ(LU_Result.upper(6,0), LU_echelon.upper(6,0));   ASSERT_EQ(LU_Result.upper(6,1), LU_echelon.upper(6,1));   ASSERT_EQ(LU_Result.upper(6,2), LU_echelon.upper(6,2));     ASSERT_EQ(LU_Result.upper(6,3), LU_echelon.upper(6,3));     ASSERT_EQ(LU_Result.upper(6,4), LU_echelon.upper(6,4));     ASSERT_EQ(LU_Result.upper(6,5), LU_echelon.upper(6,5));     ASSERT_EQ(LU_Result.upper(6,6), LU_echelon.upper(6,6));

    ASSERT_NEAR(determinant(matrix), 600, epsilon);
}

TEST_F(MatrixLUFactorization_RowSwap, LUFactorization_7x7_WithRowSwap_Singular_1)
{
    // Almost the same as Example_1 but mat(5,5) is 11 instead of 17
    // This matrix is singular and will not produce a full set of pivots !  upper(5,5) = 0 !
    const auto data = std::vector<int>{
            1,  1,  1,  1,  1,  1,  1,
            2,  5,  4,  5,  1,  7,  8,
            3,  4,  5,  6,  1,  8,  9,
            4,  8,  6,  7,  1,  9,  10,
            5,  12, 7,  18, 6,  10, 11,
            6,  7,  8,  11, 5,  11, 12,
            7,  8,  9,  10, 11, 12, 14};

    const auto matrix = Matrix<int>(data, 7, 7);

    const auto LU_Result  = factorizeLU(matrix);
    ASSERT_FALSE(LU_Result.permutation == std::nullopt);    // P_45  : the 4th pivot is zero, swap rows 4 and 5 (3 and 4 in this convention)

    const double epsilon = 1e-9;
    ASSERT_EQ(LU_Result.lower.rows(), 7); ASSERT_EQ(LU_Result.lower.cols(), 7);
    ASSERT_NEAR(LU_Result.lower(0,0), 1, epsilon);   ASSERT_NEAR(LU_Result.lower(0,1), 0, epsilon);             ASSERT_NEAR(LU_Result.lower(0,2), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(0,3), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(0,4), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(0,5), 0, epsilon);  ASSERT_NEAR(LU_Result.lower(0,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(1,0), 2, epsilon);   ASSERT_NEAR(LU_Result.lower(1,1), 1, epsilon);             ASSERT_NEAR(LU_Result.lower(1,2), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(1,3), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(1,4), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(1,5), 0, epsilon);  ASSERT_NEAR(LU_Result.lower(1,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(2,0), 3, epsilon);   ASSERT_NEAR(LU_Result.lower(2,1), 0.3333333333, epsilon);  ASSERT_NEAR(LU_Result.lower(2,2), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(2,3), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(2,4), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(2,5), 0, epsilon);  ASSERT_NEAR(LU_Result.lower(2,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(3,0), 5, epsilon);   ASSERT_NEAR(LU_Result.lower(3,1), 2.3333333333, epsilon);  ASSERT_NEAR(LU_Result.lower(3,2), -2, epsilon);     ASSERT_NEAR(LU_Result.lower(3,3), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(3,4), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(3,5), 0, epsilon);  ASSERT_NEAR(LU_Result.lower(3,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(4,0), 4, epsilon);   ASSERT_NEAR(LU_Result.lower(4,1), 1.3333333333, epsilon);  ASSERT_NEAR(LU_Result.lower(4,2), -0.5, epsilon);   ASSERT_NEAR(LU_Result.lower(4,3), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(4,4), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(4,5), 0, epsilon);  ASSERT_NEAR(LU_Result.lower(4,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(5,0), 6, epsilon);   ASSERT_NEAR(LU_Result.lower(5,1), 0.3333333333, epsilon);  ASSERT_NEAR(LU_Result.lower(5,2), 1, epsilon);     ASSERT_NEAR(LU_Result.lower(5,3), 0.2, epsilon);     ASSERT_NEAR(LU_Result.lower(5,4), -0.4, epsilon);   ASSERT_NEAR(LU_Result.lower(5,5), 1, epsilon);  ASSERT_NEAR(LU_Result.lower(5,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(6,0), 7, epsilon);   ASSERT_NEAR(LU_Result.lower(6,1), 0.3333333333, epsilon);  ASSERT_NEAR(LU_Result.lower(6,2), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(6,3), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(6,4), -2.4, epsilon);   ASSERT_NEAR(LU_Result.lower(6,5), 0, epsilon);  ASSERT_NEAR(LU_Result.lower(6,6), 1, epsilon);

    ASSERT_EQ(LU_Result.upper.rows(), 7); ASSERT_EQ(LU_Result.upper.cols(), 7);
    ASSERT_NEAR(LU_Result.upper(0,0), 1, epsilon);   ASSERT_NEAR(LU_Result.upper(0,1), 1, epsilon);     ASSERT_NEAR(LU_Result.upper(0,2), 1, epsilon);              ASSERT_NEAR(LU_Result.upper(0,3), 1, epsilon);      ASSERT_NEAR(LU_Result.upper(0,4), 1, epsilon);              ASSERT_NEAR(LU_Result.upper(0,5), 1, epsilon);              ASSERT_NEAR(LU_Result.upper(0,6), 1, epsilon);
    ASSERT_NEAR(LU_Result.upper(1,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(1,1), 3, epsilon);     ASSERT_NEAR(LU_Result.upper(1,2), 2, epsilon);              ASSERT_NEAR(LU_Result.upper(1,3), 3, epsilon);      ASSERT_NEAR(LU_Result.upper(1,4), -1, epsilon);             ASSERT_NEAR(LU_Result.upper(1,5), 5, epsilon);              ASSERT_NEAR(LU_Result.upper(1,6), 6, epsilon);
    ASSERT_NEAR(LU_Result.upper(2,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(2,1), 0, epsilon);     ASSERT_NEAR(LU_Result.upper(2,2), 1.333333333, epsilon);    ASSERT_NEAR(LU_Result.upper(2,3), 2, epsilon);      ASSERT_NEAR(LU_Result.upper(2,4), -1.666666666, epsilon);   ASSERT_NEAR(LU_Result.upper(2,5), 3.333333333, epsilon);    ASSERT_NEAR(LU_Result.upper(2,6), 4, epsilon);
    ASSERT_NEAR(LU_Result.upper(3,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(3,1), 0, epsilon);     ASSERT_NEAR(LU_Result.upper(3,2), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(3,3), 10, epsilon);     ASSERT_NEAR(LU_Result.upper(3,4), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(3,5), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(3,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.upper(4,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(4,1), 0, epsilon);     ASSERT_NEAR(LU_Result.upper(4,2), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(4,3), 0, epsilon);      ASSERT_NEAR(LU_Result.upper(4,4), -2.5, epsilon);           ASSERT_NEAR(LU_Result.upper(4,5), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(4,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.upper(5,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(5,1), 0, epsilon);     ASSERT_NEAR(LU_Result.upper(5,2), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(5,3), 0, epsilon);      ASSERT_NEAR(LU_Result.upper(5,4), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(5,5), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(5,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.upper(6,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(6,1), 0, epsilon);     ASSERT_NEAR(LU_Result.upper(6,2), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(6,3), 0, epsilon);      ASSERT_NEAR(LU_Result.upper(6,4), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(6,5), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(6,6), 1, epsilon);

    // Ensure L*U = P*A
    const auto LU = LU_Result.lower * LU_Result.upper;
    const auto PA = LU_Result.permutation.value() * matrix;

    ASSERT_NEAR(LU(0,0), PA(0,0), epsilon); ASSERT_NEAR(LU(0,1), PA(0,1), epsilon); ASSERT_NEAR(LU(0,2), PA(0,2), epsilon); ASSERT_NEAR(LU(0,3), PA(0,3), epsilon); ASSERT_NEAR(LU(0,4), PA(0,4), epsilon); ASSERT_NEAR(LU(0,5), PA(0,5), epsilon); ASSERT_NEAR(LU(0,6), PA(0,6), epsilon);
    ASSERT_NEAR(LU(1,0), PA(1,0), epsilon); ASSERT_NEAR(LU(1,1), PA(1,1), epsilon); ASSERT_NEAR(LU(1,2), PA(1,2), epsilon); ASSERT_NEAR(LU(1,3), PA(1,3), epsilon); ASSERT_NEAR(LU(1,4), PA(1,4), epsilon); ASSERT_NEAR(LU(1,5), PA(1,5), epsilon); ASSERT_NEAR(LU(1,6), PA(1,6), epsilon);
    ASSERT_NEAR(LU(2,0), PA(2,0), epsilon); ASSERT_NEAR(LU(2,1), PA(2,1), epsilon); ASSERT_NEAR(LU(2,2), PA(2,2), epsilon); ASSERT_NEAR(LU(2,3), PA(2,3), epsilon); ASSERT_NEAR(LU(2,4), PA(2,4), epsilon); ASSERT_NEAR(LU(2,5), PA(2,5), epsilon); ASSERT_NEAR(LU(2,6), PA(2,6), epsilon);
    ASSERT_NEAR(LU(3,0), PA(3,0), epsilon); ASSERT_NEAR(LU(3,1), PA(3,1), epsilon); ASSERT_NEAR(LU(3,2), PA(3,2), epsilon); ASSERT_NEAR(LU(3,3), PA(3,3), epsilon); ASSERT_NEAR(LU(3,4), PA(3,4), epsilon); ASSERT_NEAR(LU(3,5), PA(3,5), epsilon); ASSERT_NEAR(LU(3,6), PA(3,6), epsilon);
    ASSERT_NEAR(LU(4,0), PA(4,0), epsilon); ASSERT_NEAR(LU(4,1), PA(4,1), epsilon); ASSERT_NEAR(LU(4,2), PA(4,2), epsilon); ASSERT_NEAR(LU(4,3), PA(4,3), epsilon); ASSERT_NEAR(LU(4,4), PA(4,4), epsilon); ASSERT_NEAR(LU(4,5), PA(4,5), epsilon); ASSERT_NEAR(LU(4,6), PA(4,6), epsilon);
    ASSERT_NEAR(LU(5,0), PA(5,0), epsilon); ASSERT_NEAR(LU(5,1), PA(5,1), epsilon); ASSERT_NEAR(LU(5,2), PA(5,2), epsilon); ASSERT_NEAR(LU(5,3), PA(5,3), epsilon); ASSERT_NEAR(LU(5,4), PA(5,4), epsilon); ASSERT_NEAR(LU(5,5), PA(5,5), epsilon); ASSERT_NEAR(LU(5,6), PA(5,6), epsilon);
    ASSERT_NEAR(LU(6,0), PA(6,0), epsilon); ASSERT_NEAR(LU(6,1), PA(6,1), epsilon); ASSERT_NEAR(LU(6,2), PA(6,2), epsilon); ASSERT_NEAR(LU(6,3), PA(6,3), epsilon); ASSERT_NEAR(LU(6,4), PA(6,4), epsilon); ASSERT_NEAR(LU(6,5), PA(6,5), epsilon); ASSERT_NEAR(LU(6,6), PA(6,6), epsilon);

    ASSERT_NEAR(determinant(matrix), 0, epsilon);
}

TEST_F(MatrixLUFactorization_RowSwap, LUFactorization_7x7_WithRowSwap_Example_2)
{
    const auto data = std::vector<double>{
            1,  1,  1,  1,  1,  1,  1,
            2,  5,  4,  5,  1,  7,  8,
            3,  4,  5,  6,  1,  8,  9,
            4,  8,  6,  17, 1,  9,  10,
            5,  12, 7,  18, 7./2,15, 11,
            6,  7,  8,  11, 5,  11, 12,
            7,  8,  9,  10, 11, 12, 14};

    const auto matrix = Matrix<double>(data, 7, 7);

    const auto LU_Result  = factorizeLU(matrix);
    ASSERT_FALSE(LU_Result.permutation == std::nullopt);    // P_56  : the 5th pivot is zero, swap rows 5 and 6 (4 and 5 in this convention)

    const double epsilon = 1e-9;
    ASSERT_EQ(LU_Result.lower.rows(), 7); ASSERT_EQ(LU_Result.lower.cols(), 7);
    ASSERT_NEAR(LU_Result.lower(0,0), 1, epsilon);   ASSERT_NEAR(LU_Result.lower(0,1), 0, epsilon);             ASSERT_NEAR(LU_Result.lower(0,2), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(0,3), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(0,4), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(0,5), 0, epsilon);  ASSERT_NEAR(LU_Result.lower(0,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(1,0), 2, epsilon);   ASSERT_NEAR(LU_Result.lower(1,1), 1, epsilon);             ASSERT_NEAR(LU_Result.lower(1,2), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(1,3), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(1,4), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(1,5), 0, epsilon);  ASSERT_NEAR(LU_Result.lower(1,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(2,0), 3, epsilon);   ASSERT_NEAR(LU_Result.lower(2,1), 0.3333333333, epsilon);  ASSERT_NEAR(LU_Result.lower(2,2), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(2,3), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(2,4), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(2,5), 0, epsilon);  ASSERT_NEAR(LU_Result.lower(2,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(3,0), 4, epsilon);   ASSERT_NEAR(LU_Result.lower(3,1), 1.3333333333, epsilon);  ASSERT_NEAR(LU_Result.lower(3,2), -0.5, epsilon);   ASSERT_NEAR(LU_Result.lower(3,3), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(3,4), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(3,5), 0, epsilon);  ASSERT_NEAR(LU_Result.lower(3,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(4,0), 6, epsilon);   ASSERT_NEAR(LU_Result.lower(4,1), 0.3333333333, epsilon);  ASSERT_NEAR(LU_Result.lower(4,2), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(4,3), 0.2, epsilon);    ASSERT_NEAR(LU_Result.lower(4,4), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(4,5), 0, epsilon);  ASSERT_NEAR(LU_Result.lower(4,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(5,0), 5, epsilon);   ASSERT_NEAR(LU_Result.lower(5,1), 2.3333333333, epsilon);  ASSERT_NEAR(LU_Result.lower(5,2), -2, epsilon);    ASSERT_NEAR(LU_Result.lower(5,3), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(5,4), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(5,5), 1, epsilon);  ASSERT_NEAR(LU_Result.lower(5,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(6,0), 7, epsilon);   ASSERT_NEAR(LU_Result.lower(6,1), 0.3333333333, epsilon);  ASSERT_NEAR(LU_Result.lower(6,2), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(6,3), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(6,4), 4, epsilon);      ASSERT_NEAR(LU_Result.lower(6,5), 0, epsilon);  ASSERT_NEAR(LU_Result.lower(6,6), 1, epsilon);

    ASSERT_EQ(LU_Result.upper.rows(), 7); ASSERT_EQ(LU_Result.upper.cols(), 7);
    ASSERT_NEAR(LU_Result.upper(0,0), 1, epsilon);   ASSERT_NEAR(LU_Result.upper(0,1), 1, epsilon);     ASSERT_NEAR(LU_Result.upper(0,2), 1, epsilon);              ASSERT_NEAR(LU_Result.upper(0,3), 1, epsilon);      ASSERT_NEAR(LU_Result.upper(0,4), 1, epsilon);              ASSERT_NEAR(LU_Result.upper(0,5), 1, epsilon);              ASSERT_NEAR(LU_Result.upper(0,6), 1, epsilon);
    ASSERT_NEAR(LU_Result.upper(1,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(1,1), 3, epsilon);     ASSERT_NEAR(LU_Result.upper(1,2), 2, epsilon);              ASSERT_NEAR(LU_Result.upper(1,3), 3, epsilon);      ASSERT_NEAR(LU_Result.upper(1,4), -1, epsilon);             ASSERT_NEAR(LU_Result.upper(1,5), 5, epsilon);              ASSERT_NEAR(LU_Result.upper(1,6), 6, epsilon);
    ASSERT_NEAR(LU_Result.upper(2,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(2,1), 0, epsilon);     ASSERT_NEAR(LU_Result.upper(2,2), 1.333333333, epsilon);    ASSERT_NEAR(LU_Result.upper(2,3), 2, epsilon);      ASSERT_NEAR(LU_Result.upper(2,4), -1.666666666, epsilon);   ASSERT_NEAR(LU_Result.upper(2,5), 3.333333333, epsilon);    ASSERT_NEAR(LU_Result.upper(2,6), 4, epsilon);
    ASSERT_NEAR(LU_Result.upper(3,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(3,1), 0, epsilon);     ASSERT_NEAR(LU_Result.upper(3,2), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(3,3), 10, epsilon);     ASSERT_NEAR(LU_Result.upper(3,4), -2.5, epsilon);           ASSERT_NEAR(LU_Result.upper(3,5), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(3,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.upper(4,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(4,1), 0, epsilon);     ASSERT_NEAR(LU_Result.upper(4,2), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(4,3), 0, epsilon);      ASSERT_NEAR(LU_Result.upper(4,4), 1.5, epsilon);            ASSERT_NEAR(LU_Result.upper(4,5), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(4,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.upper(5,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(5,1), 0, epsilon);     ASSERT_NEAR(LU_Result.upper(5,2), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(5,3), 0, epsilon);      ASSERT_NEAR(LU_Result.upper(5,4), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(5,5), 5, epsilon);              ASSERT_NEAR(LU_Result.upper(5,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.upper(6,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(6,1), 0, epsilon);     ASSERT_NEAR(LU_Result.upper(6,2), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(6,3), 0, epsilon);      ASSERT_NEAR(LU_Result.upper(6,4), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(6,5), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(6,6), 1, epsilon);

    // Ensure L*U = P*A
    const auto LU = LU_Result.lower * LU_Result.upper;
    const auto PA = LU_Result.permutation.value() *matrix;

    ASSERT_NEAR(LU(0,0), PA(0,0), epsilon); ASSERT_NEAR(LU(0,1), PA(0,1), epsilon); ASSERT_NEAR(LU(0,2), PA(0,2), epsilon); ASSERT_NEAR(LU(0,3), PA(0,3), epsilon); ASSERT_NEAR(LU(0,4), PA(0,4), epsilon); ASSERT_NEAR(LU(0,5), PA(0,5), epsilon); ASSERT_NEAR(LU(0,6), PA(0,6), epsilon);
    ASSERT_NEAR(LU(1,0), PA(1,0), epsilon); ASSERT_NEAR(LU(1,1), PA(1,1), epsilon); ASSERT_NEAR(LU(1,2), PA(1,2), epsilon); ASSERT_NEAR(LU(1,3), PA(1,3), epsilon); ASSERT_NEAR(LU(1,4), PA(1,4), epsilon); ASSERT_NEAR(LU(1,5), PA(1,5), epsilon); ASSERT_NEAR(LU(1,6), PA(1,6), epsilon);
    ASSERT_NEAR(LU(2,0), PA(2,0), epsilon); ASSERT_NEAR(LU(2,1), PA(2,1), epsilon); ASSERT_NEAR(LU(2,2), PA(2,2), epsilon); ASSERT_NEAR(LU(2,3), PA(2,3), epsilon); ASSERT_NEAR(LU(2,4), PA(2,4), epsilon); ASSERT_NEAR(LU(2,5), PA(2,5), epsilon); ASSERT_NEAR(LU(2,6), PA(2,6), epsilon);
    ASSERT_NEAR(LU(3,0), PA(3,0), epsilon); ASSERT_NEAR(LU(3,1), PA(3,1), epsilon); ASSERT_NEAR(LU(3,2), PA(3,2), epsilon); ASSERT_NEAR(LU(3,3), PA(3,3), epsilon); ASSERT_NEAR(LU(3,4), PA(3,4), epsilon); ASSERT_NEAR(LU(3,5), PA(3,5), epsilon); ASSERT_NEAR(LU(3,6), PA(3,6), epsilon);
    ASSERT_NEAR(LU(4,0), PA(4,0), epsilon); ASSERT_NEAR(LU(4,1), PA(4,1), epsilon); ASSERT_NEAR(LU(4,2), PA(4,2), epsilon); ASSERT_NEAR(LU(4,3), PA(4,3), epsilon); ASSERT_NEAR(LU(4,4), PA(4,4), epsilon); ASSERT_NEAR(LU(4,5), PA(4,5), epsilon); ASSERT_NEAR(LU(4,6), PA(4,6), epsilon);
    ASSERT_NEAR(LU(5,0), PA(5,0), epsilon); ASSERT_NEAR(LU(5,1), PA(5,1), epsilon); ASSERT_NEAR(LU(5,2), PA(5,2), epsilon); ASSERT_NEAR(LU(5,3), PA(5,3), epsilon); ASSERT_NEAR(LU(5,4), PA(5,4), epsilon); ASSERT_NEAR(LU(5,5), PA(5,5), epsilon); ASSERT_NEAR(LU(5,6), PA(5,6), epsilon);
    ASSERT_NEAR(LU(6,0), PA(6,0), epsilon); ASSERT_NEAR(LU(6,1), PA(6,1), epsilon); ASSERT_NEAR(LU(6,2), PA(6,2), epsilon); ASSERT_NEAR(LU(6,3), PA(6,3), epsilon); ASSERT_NEAR(LU(6,4), PA(6,4), epsilon); ASSERT_NEAR(LU(6,5), PA(6,5), epsilon); ASSERT_NEAR(LU(6,6), PA(6,6), epsilon);

    // Test LU_echelon is outputting the same result (since this is non-singular matrix)
    const auto LU_echelon = factorizeLU_echelon(matrix);
    ASSERT_EQ(LU_echelon.upper.rows(), 7); ASSERT_EQ(LU_echelon.upper.cols(), 7);

    ASSERT_EQ(LU_Result.lower(0,0), LU_echelon.lower(0,0));   ASSERT_EQ(LU_Result.lower(0,1), LU_echelon.lower(0,1));   ASSERT_EQ(LU_Result.lower(0,2), LU_echelon.lower(0,2));     ASSERT_EQ(LU_Result.lower(0,3), LU_echelon.lower(0,3));     ASSERT_EQ(LU_Result.lower(0,4), LU_echelon.lower(0,4));     ASSERT_EQ(LU_Result.lower(0,5), LU_echelon.lower(0,5));     ASSERT_EQ(LU_Result.lower(0,6), LU_echelon.lower(0,6));
    ASSERT_EQ(LU_Result.lower(1,0), LU_echelon.lower(1,0));   ASSERT_EQ(LU_Result.lower(1,1), LU_echelon.lower(1,1));   ASSERT_EQ(LU_Result.lower(1,2),  LU_echelon.lower(1,2));    ASSERT_EQ(LU_Result.lower(1,3), LU_echelon.lower(1,3));     ASSERT_EQ(LU_Result.lower(1,4), LU_echelon.lower(1,4));     ASSERT_EQ(LU_Result.lower(1,5), LU_echelon.lower(1,5));     ASSERT_EQ(LU_Result.lower(1,6), LU_echelon.lower(1,6));
    ASSERT_EQ(LU_Result.lower(2,0), LU_echelon.lower(2,0));   ASSERT_EQ(LU_Result.lower(2,1), LU_echelon.lower(2,1));   ASSERT_EQ(LU_Result.lower(2,2), LU_echelon.lower(2,2));     ASSERT_EQ(LU_Result.lower(2,3), LU_echelon.lower(2,3));     ASSERT_EQ(LU_Result.lower(2,4), LU_echelon.lower(2,4));     ASSERT_EQ(LU_Result.lower(2,5), LU_echelon.lower(2,5));     ASSERT_EQ(LU_Result.lower(2,6), LU_echelon.lower(2,6));
    ASSERT_EQ(LU_Result.lower(3,0), LU_echelon.lower(3,0));   ASSERT_EQ(LU_Result.lower(3,1), LU_echelon.lower(3,1));   ASSERT_EQ(LU_Result.lower(3,2), LU_echelon.lower(3,2));     ASSERT_EQ(LU_Result.lower(3,3), LU_echelon.lower(3,3));     ASSERT_EQ(LU_Result.lower(3,4), LU_echelon.lower(3,4));     ASSERT_EQ(LU_Result.lower(3,5), LU_echelon.lower(3,5));     ASSERT_EQ(LU_Result.lower(3,6), LU_echelon.lower(3,6));
    ASSERT_EQ(LU_Result.lower(4,0), LU_echelon.lower(4,0));   ASSERT_EQ(LU_Result.lower(4,1), LU_echelon.lower(4,1));   ASSERT_EQ(LU_Result.lower(4,2), LU_echelon.lower(4,2));     ASSERT_EQ(LU_Result.lower(4,3), LU_echelon.lower(4,3));     ASSERT_EQ(LU_Result.lower(4,4), LU_echelon.lower(4,4));     ASSERT_EQ(LU_Result.lower(4,5), LU_echelon.lower(4,5));     ASSERT_EQ(LU_Result.lower(4,6), LU_echelon.lower(4,6));
    ASSERT_EQ(LU_Result.lower(5,0), LU_echelon.lower(5,0));   ASSERT_EQ(LU_Result.lower(5,1), LU_echelon.lower(5,1));   ASSERT_EQ(LU_Result.lower(5,2), LU_echelon.lower(5,2));     ASSERT_EQ(LU_Result.lower(5,3), LU_echelon.lower(5,3));     ASSERT_EQ(LU_Result.lower(5,4), LU_echelon.lower(5,4));     ASSERT_EQ(LU_Result.lower(5,5), LU_echelon.lower(5,5));     ASSERT_EQ(LU_Result.lower(5,6), LU_echelon.lower(5,6));
    ASSERT_EQ(LU_Result.lower(6,0), LU_echelon.lower(6,0));   ASSERT_EQ(LU_Result.lower(6,1), LU_echelon.lower(6,1));   ASSERT_EQ(LU_Result.lower(6,2), LU_echelon.lower(6,2));     ASSERT_EQ(LU_Result.lower(6,3), LU_echelon.lower(6,3));     ASSERT_EQ(LU_Result.lower(6,4), LU_echelon.lower(6,4));     ASSERT_EQ(LU_Result.lower(6,5), LU_echelon.lower(6,5));     ASSERT_EQ(LU_Result.lower(6,6), LU_echelon.lower(6,6));

    ASSERT_EQ(LU_Result.upper(0,0), LU_echelon.upper(0,0));   ASSERT_EQ(LU_Result.upper(0,1), LU_echelon.upper(0,1));   ASSERT_EQ(LU_Result.upper(0,2), LU_echelon.upper(0,2));     ASSERT_EQ(LU_Result.upper(0,3), LU_echelon.upper(0,3));     ASSERT_EQ(LU_Result.upper(0,4), LU_echelon.upper(0,4));     ASSERT_EQ(LU_Result.upper(0,5), LU_echelon.upper(0,5));     ASSERT_EQ(LU_Result.upper(0,6), LU_echelon.upper(0,6));
    ASSERT_EQ(LU_Result.upper(1,0), LU_echelon.upper(1,0));   ASSERT_EQ(LU_Result.upper(1,1), LU_echelon.upper(1,1));   ASSERT_EQ(LU_Result.upper(1,2),  LU_echelon.upper(1,2));    ASSERT_EQ(LU_Result.upper(1,3), LU_echelon.upper(1,3));     ASSERT_EQ(LU_Result.upper(1,4), LU_echelon.upper(1,4));     ASSERT_EQ(LU_Result.upper(1,5), LU_echelon.upper(1,5));     ASSERT_EQ(LU_Result.upper(1,6), LU_echelon.upper(1,6));
    ASSERT_EQ(LU_Result.upper(2,0), LU_echelon.upper(2,0));   ASSERT_EQ(LU_Result.upper(2,1), LU_echelon.upper(2,1));   ASSERT_EQ(LU_Result.upper(2,2), LU_echelon.upper(2,2));     ASSERT_EQ(LU_Result.upper(2,3), LU_echelon.upper(2,3));     ASSERT_EQ(LU_Result.upper(2,4), LU_echelon.upper(2,4));     ASSERT_EQ(LU_Result.upper(2,5), LU_echelon.upper(2,5));     ASSERT_EQ(LU_Result.upper(2,6), LU_echelon.upper(2,6));
    ASSERT_EQ(LU_Result.upper(3,0), LU_echelon.upper(3,0));   ASSERT_EQ(LU_Result.upper(3,1), LU_echelon.upper(3,1));   ASSERT_EQ(LU_Result.upper(3,2), LU_echelon.upper(3,2));     ASSERT_EQ(LU_Result.upper(3,3), LU_echelon.upper(3,3));     ASSERT_EQ(LU_Result.upper(3,4), LU_echelon.upper(3,4));     ASSERT_EQ(LU_Result.upper(3,5), LU_echelon.upper(3,5));     ASSERT_EQ(LU_Result.upper(3,6), LU_echelon.upper(3,6));
    ASSERT_EQ(LU_Result.upper(4,0), LU_echelon.upper(4,0));   ASSERT_EQ(LU_Result.upper(4,1), LU_echelon.upper(4,1));   ASSERT_EQ(LU_Result.upper(4,2), LU_echelon.upper(4,2));     ASSERT_EQ(LU_Result.upper(4,3), LU_echelon.upper(4,3));     ASSERT_EQ(LU_Result.upper(4,4), LU_echelon.upper(4,4));     ASSERT_EQ(LU_Result.upper(4,5), LU_echelon.upper(4,5));     ASSERT_EQ(LU_Result.upper(4,6), LU_echelon.upper(4,6));
    ASSERT_EQ(LU_Result.upper(5,0), LU_echelon.upper(5,0));   ASSERT_EQ(LU_Result.upper(5,1), LU_echelon.upper(5,1));   ASSERT_EQ(LU_Result.upper(5,2), LU_echelon.upper(5,2));     ASSERT_EQ(LU_Result.upper(5,3), LU_echelon.upper(5,3));     ASSERT_EQ(LU_Result.upper(5,4), LU_echelon.upper(5,4));     ASSERT_EQ(LU_Result.upper(5,5), LU_echelon.upper(5,5));     ASSERT_EQ(LU_Result.upper(5,6), LU_echelon.upper(5,6));
    ASSERT_EQ(LU_Result.upper(6,0), LU_echelon.upper(6,0));   ASSERT_EQ(LU_Result.upper(6,1), LU_echelon.upper(6,1));   ASSERT_EQ(LU_Result.upper(6,2), LU_echelon.upper(6,2));     ASSERT_EQ(LU_Result.upper(6,3), LU_echelon.upper(6,3));     ASSERT_EQ(LU_Result.upper(6,4), LU_echelon.upper(6,4));     ASSERT_EQ(LU_Result.upper(6,5), LU_echelon.upper(6,5));     ASSERT_EQ(LU_Result.upper(6,6), LU_echelon.upper(6,6));

    ASSERT_NEAR(determinant(matrix), -300, epsilon);
}


TEST_F(MatrixLUFactorization_RowSwap, LUFactorization_7x7_WithRowSwap_Singular_2)
{
    // This is the same matrix as in Example_3 but mat(5,5) is 10 instead of 15.
    // Matrix is singular and will not produce a full set of pivots !
    const auto data = std::vector<double>{
            1,  1,  1,  1,  1,  1,  1,
            2,  5,  4,  5,  1,  7,  8,
            3,  4,  5,  6,  1,  8,  9,
            4,  8,  6,  17, 1,  9,  10,
            5,  12, 7,  18, 7./2,10, 11,
            6,  7,  8,  11, 5,  11, 12,
            7,  8,  9,  10, 11, 12, 14};

    const auto matrix = Matrix<double>(data, 7, 7);

    const auto LU_Result  = factorizeLU(matrix);
    ASSERT_FALSE(LU_Result.permutation == std::nullopt);    // P_56  : the 5th pivot is zero, swap rows 5 and 6 (4 and 5 in this convention)

    const double epsilon = 1e-9;
    ASSERT_EQ(LU_Result.lower.rows(), 7); ASSERT_EQ(LU_Result.lower.cols(), 7);
    ASSERT_NEAR(LU_Result.lower(0,0), 1, epsilon);   ASSERT_NEAR(LU_Result.lower(0,1), 0, epsilon);             ASSERT_NEAR(LU_Result.lower(0,2), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(0,3), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(0,4), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(0,5), 0, epsilon);  ASSERT_NEAR(LU_Result.lower(0,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(1,0), 2, epsilon);   ASSERT_NEAR(LU_Result.lower(1,1), 1, epsilon);             ASSERT_NEAR(LU_Result.lower(1,2), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(1,3), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(1,4), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(1,5), 0, epsilon);  ASSERT_NEAR(LU_Result.lower(1,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(2,0), 3, epsilon);   ASSERT_NEAR(LU_Result.lower(2,1), 0.3333333333, epsilon);  ASSERT_NEAR(LU_Result.lower(2,2), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(2,3), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(2,4), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(2,5), 0, epsilon);  ASSERT_NEAR(LU_Result.lower(2,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(3,0), 4, epsilon);   ASSERT_NEAR(LU_Result.lower(3,1), 1.3333333333, epsilon);  ASSERT_NEAR(LU_Result.lower(3,2), -0.5, epsilon);   ASSERT_NEAR(LU_Result.lower(3,3), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(3,4), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(3,5), 0, epsilon);  ASSERT_NEAR(LU_Result.lower(3,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(4,0), 6, epsilon);   ASSERT_NEAR(LU_Result.lower(4,1), 0.3333333333, epsilon);  ASSERT_NEAR(LU_Result.lower(4,2), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(4,3), 0.2, epsilon);    ASSERT_NEAR(LU_Result.lower(4,4), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(4,5), 0, epsilon);  ASSERT_NEAR(LU_Result.lower(4,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(5,0), 5, epsilon);   ASSERT_NEAR(LU_Result.lower(5,1), 2.3333333333, epsilon);  ASSERT_NEAR(LU_Result.lower(5,2), -2, epsilon);    ASSERT_NEAR(LU_Result.lower(5,3), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(5,4), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(5,5), 1, epsilon);  ASSERT_NEAR(LU_Result.lower(5,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(6,0), 7, epsilon);   ASSERT_NEAR(LU_Result.lower(6,1), 0.3333333333, epsilon);  ASSERT_NEAR(LU_Result.lower(6,2), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(6,3), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(6,4), 4, epsilon);      ASSERT_NEAR(LU_Result.lower(6,5), 0, epsilon);  ASSERT_NEAR(LU_Result.lower(6,6), 1, epsilon);

    ASSERT_EQ(LU_Result.upper.rows(), 7); ASSERT_EQ(LU_Result.upper.cols(), 7);
    ASSERT_NEAR(LU_Result.upper(0,0), 1, epsilon);   ASSERT_NEAR(LU_Result.upper(0,1), 1, epsilon);     ASSERT_NEAR(LU_Result.upper(0,2), 1, epsilon);              ASSERT_NEAR(LU_Result.upper(0,3), 1, epsilon);      ASSERT_NEAR(LU_Result.upper(0,4), 1, epsilon);              ASSERT_NEAR(LU_Result.upper(0,5), 1, epsilon);              ASSERT_NEAR(LU_Result.upper(0,6), 1, epsilon);
    ASSERT_NEAR(LU_Result.upper(1,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(1,1), 3, epsilon);     ASSERT_NEAR(LU_Result.upper(1,2), 2, epsilon);              ASSERT_NEAR(LU_Result.upper(1,3), 3, epsilon);      ASSERT_NEAR(LU_Result.upper(1,4), -1, epsilon);             ASSERT_NEAR(LU_Result.upper(1,5), 5, epsilon);              ASSERT_NEAR(LU_Result.upper(1,6), 6, epsilon);
    ASSERT_NEAR(LU_Result.upper(2,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(2,1), 0, epsilon);     ASSERT_NEAR(LU_Result.upper(2,2), 1.333333333, epsilon);    ASSERT_NEAR(LU_Result.upper(2,3), 2, epsilon);      ASSERT_NEAR(LU_Result.upper(2,4), -1.666666666, epsilon);   ASSERT_NEAR(LU_Result.upper(2,5), 3.333333333, epsilon);    ASSERT_NEAR(LU_Result.upper(2,6), 4, epsilon);
    ASSERT_NEAR(LU_Result.upper(3,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(3,1), 0, epsilon);     ASSERT_NEAR(LU_Result.upper(3,2), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(3,3), 10, epsilon);     ASSERT_NEAR(LU_Result.upper(3,4), -2.5, epsilon);           ASSERT_NEAR(LU_Result.upper(3,5), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(3,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.upper(4,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(4,1), 0, epsilon);     ASSERT_NEAR(LU_Result.upper(4,2), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(4,3), 0, epsilon);      ASSERT_NEAR(LU_Result.upper(4,4), 1.5, epsilon);            ASSERT_NEAR(LU_Result.upper(4,5), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(4,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.upper(5,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(5,1), 0, epsilon);     ASSERT_NEAR(LU_Result.upper(5,2), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(5,3), 0, epsilon);      ASSERT_NEAR(LU_Result.upper(5,4), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(5,5), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(5,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.upper(6,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(6,1), 0, epsilon);     ASSERT_NEAR(LU_Result.upper(6,2), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(6,3), 0, epsilon);      ASSERT_NEAR(LU_Result.upper(6,4), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(6,5), 0, epsilon);              ASSERT_NEAR(LU_Result.upper(6,6), 1, epsilon);

    // Ensure L*U = P*A
    const auto LU = LU_Result.lower * LU_Result.upper;
    const auto PA = LU_Result.permutation.value() * matrix;

    ASSERT_NEAR(LU(0,0), PA(0,0), epsilon); ASSERT_NEAR(LU(0,1), PA(0,1), epsilon); ASSERT_NEAR(LU(0,2), PA(0,2), epsilon); ASSERT_NEAR(LU(0,3), PA(0,3), epsilon); ASSERT_NEAR(LU(0,4), PA(0,4), epsilon); ASSERT_NEAR(LU(0,5), PA(0,5), epsilon); ASSERT_NEAR(LU(0,6), PA(0,6), epsilon);
    ASSERT_NEAR(LU(1,0), PA(1,0), epsilon); ASSERT_NEAR(LU(1,1), PA(1,1), epsilon); ASSERT_NEAR(LU(1,2), PA(1,2), epsilon); ASSERT_NEAR(LU(1,3), PA(1,3), epsilon); ASSERT_NEAR(LU(1,4), PA(1,4), epsilon); ASSERT_NEAR(LU(1,5), PA(1,5), epsilon); ASSERT_NEAR(LU(1,6), PA(1,6), epsilon);
    ASSERT_NEAR(LU(2,0), PA(2,0), epsilon); ASSERT_NEAR(LU(2,1), PA(2,1), epsilon); ASSERT_NEAR(LU(2,2), PA(2,2), epsilon); ASSERT_NEAR(LU(2,3), PA(2,3), epsilon); ASSERT_NEAR(LU(2,4), PA(2,4), epsilon); ASSERT_NEAR(LU(2,5), PA(2,5), epsilon); ASSERT_NEAR(LU(2,6), PA(2,6), epsilon);
    ASSERT_NEAR(LU(3,0), PA(3,0), epsilon); ASSERT_NEAR(LU(3,1), PA(3,1), epsilon); ASSERT_NEAR(LU(3,2), PA(3,2), epsilon); ASSERT_NEAR(LU(3,3), PA(3,3), epsilon); ASSERT_NEAR(LU(3,4), PA(3,4), epsilon); ASSERT_NEAR(LU(3,5), PA(3,5), epsilon); ASSERT_NEAR(LU(3,6), PA(3,6), epsilon);
    ASSERT_NEAR(LU(4,0), PA(4,0), epsilon); ASSERT_NEAR(LU(4,1), PA(4,1), epsilon); ASSERT_NEAR(LU(4,2), PA(4,2), epsilon); ASSERT_NEAR(LU(4,3), PA(4,3), epsilon); ASSERT_NEAR(LU(4,4), PA(4,4), epsilon); ASSERT_NEAR(LU(4,5), PA(4,5), epsilon); ASSERT_NEAR(LU(4,6), PA(4,6), epsilon);
    ASSERT_NEAR(LU(5,0), PA(5,0), epsilon); ASSERT_NEAR(LU(5,1), PA(5,1), epsilon); ASSERT_NEAR(LU(5,2), PA(5,2), epsilon); ASSERT_NEAR(LU(5,3), PA(5,3), epsilon); ASSERT_NEAR(LU(5,4), PA(5,4), epsilon); ASSERT_NEAR(LU(5,5), PA(5,5), epsilon); ASSERT_NEAR(LU(5,6), PA(5,6), epsilon);
    ASSERT_NEAR(LU(6,0), PA(6,0), epsilon); ASSERT_NEAR(LU(6,1), PA(6,1), epsilon); ASSERT_NEAR(LU(6,2), PA(6,2), epsilon); ASSERT_NEAR(LU(6,3), PA(6,3), epsilon); ASSERT_NEAR(LU(6,4), PA(6,4), epsilon); ASSERT_NEAR(LU(6,5), PA(6,5), epsilon); ASSERT_NEAR(LU(6,6), PA(6,6), epsilon);

    ASSERT_NEAR(determinant(matrix), 0, epsilon);
}