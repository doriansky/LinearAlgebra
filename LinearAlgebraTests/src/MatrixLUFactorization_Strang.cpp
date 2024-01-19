//
// Created by dorian on 27.12.2023.
// stoicadorian@gmail.com
//
#include "gtest/gtest.h"
#include "Matrix.hpp"
#include "MatrixHelpers.hpp"

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

    const auto matrix = Matrix<int>(data, 3, 3);

    const auto LU_Result  = factorizeLU(matrix);
    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 2);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 1);  ASSERT_EQ(LU_Result.lower(2,1),  4);   ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 5);   ASSERT_EQ(LU_Result.upper(0,1), 7);   ASSERT_EQ(LU_Result.upper(0,2), 8);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), 2);  ASSERT_EQ(LU_Result.upper(1,2), 3);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), 6);

    // Ensure L*U reconstructs the initial matrix
    const auto result = LU_Result.lower.multiply(LU_Result.upper);
    const double epsilon = 1e-9;
    ASSERT_NEAR(result(0,0), matrix(0,0), epsilon); ASSERT_NEAR(result(0,1), matrix(0,1), epsilon); ASSERT_NEAR(result(0,2), matrix(0,2), epsilon);
    ASSERT_NEAR(result(1,0), matrix(1,0), epsilon); ASSERT_NEAR(result(1,1), matrix(1,1), epsilon); ASSERT_NEAR(result(1,2), matrix(1,2), epsilon);
    ASSERT_NEAR(result(2,0), matrix(2,0), epsilon); ASSERT_NEAR(result(2,1), matrix(2,1), epsilon); ASSERT_NEAR(result(2,2), matrix(2,2), epsilon);

    // Test LU_echelon is outputting the same result (since this is non-singular matrix)
    const auto LU_echelon = factorizeLU_echelon(matrix);
    ASSERT_EQ(LU_echelon.upper.rows(), 3); ASSERT_EQ(LU_echelon.upper.cols(), 3);

    ASSERT_EQ(LU_Result.lower(0,0), LU_echelon.lower(0,0));   ASSERT_EQ(LU_Result.lower(0,1), LU_echelon.lower(0,1));   ASSERT_EQ(LU_Result.lower(0,2), LU_echelon.lower(0,2));
    ASSERT_EQ(LU_Result.lower(1,0), LU_echelon.lower(1,0));   ASSERT_EQ(LU_Result.lower(1,1), LU_echelon.lower(1,1));  ASSERT_EQ(LU_Result.lower(1,2),  LU_echelon.lower(1,2));
    ASSERT_EQ(LU_Result.lower(2,0), LU_echelon.lower(2,0));   ASSERT_EQ(LU_Result.lower(2,1), LU_echelon.lower(2,1));   ASSERT_EQ(LU_Result.lower(2,2), LU_echelon.lower(2,2));

    ASSERT_EQ(LU_Result.upper(0,0), LU_echelon.upper(0,0));   ASSERT_EQ(LU_Result.upper(0,1), LU_echelon.upper(0,1));   ASSERT_EQ(LU_Result.upper(0,2), LU_echelon.upper(0,2));
    ASSERT_EQ(LU_Result.upper(1,0), LU_echelon.upper(1,0));   ASSERT_EQ(LU_Result.upper(1,1), LU_echelon.upper(1,1));  ASSERT_EQ(LU_Result.upper(1,2),  LU_echelon.upper(1,2));
    ASSERT_EQ(LU_Result.upper(2,0), LU_echelon.upper(2,0));   ASSERT_EQ(LU_Result.upper(2,1), LU_echelon.upper(2,1));   ASSERT_EQ(LU_Result.upper(2,2), LU_echelon.upper(2,2));
}

TEST_F(MatrixLUFactorization_StrangTests, Chapter_1_5_problem_4b)
{
    const auto data = std::vector<int>{3,1, 1,
                                       1, 3, 1,
                                       1, 1, 3};

    const auto matrix = Matrix<int>(data, 3, 3);

    const auto LU_Result  = factorizeLU(matrix);
    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    const double epsilon = 1e-9;
    ASSERT_EQ(LU_Result.lower(0,0), 1);                       ASSERT_EQ(LU_Result.lower(0,1), 0);                   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_NEAR(LU_Result.lower(1,0), 1./3, epsilon);         ASSERT_EQ(LU_Result.lower(1,1), 1);                   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_NEAR(LU_Result.lower(2,0), 1./3, epsilon);         ASSERT_NEAR(LU_Result.lower(2,1), 1./4, epsilon);     ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper(0,0), 3);   ASSERT_EQ(LU_Result.upper(0,1), 1);                   ASSERT_EQ(LU_Result.upper(0,2), 1);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_NEAR(LU_Result.upper(1,1), 8./3, epsilon);     ASSERT_NEAR(LU_Result.upper(1,2), 2./3, epsilon);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);                   ASSERT_NEAR(LU_Result.upper(2,2), 15./6, epsilon);

    // Ensure L*U reconstructs the initial matrix
    const auto result = LU_Result.lower.multiply(LU_Result.upper);
    ASSERT_NEAR(result(0,0), matrix(0,0), epsilon); ASSERT_NEAR(result(0,1), matrix(0,1), epsilon); ASSERT_NEAR(result(0,2), matrix(0,2), epsilon);
    ASSERT_NEAR(result(1,0), matrix(1,0), epsilon); ASSERT_NEAR(result(1,1), matrix(1,1), epsilon); ASSERT_NEAR(result(1,2), matrix(1,2), epsilon);
    ASSERT_NEAR(result(2,0), matrix(2,0), epsilon); ASSERT_NEAR(result(2,1), matrix(2,1), epsilon); ASSERT_NEAR(result(2,2), matrix(2,2), epsilon);

    // Test LU_echelon is outputting the same result (since this is non-singular matrix)
    const auto LU_echelon = factorizeLU_echelon(matrix);
    ASSERT_EQ(LU_echelon.upper.rows(), 3); ASSERT_EQ(LU_echelon.upper.cols(), 3);

    ASSERT_EQ(LU_Result.lower(0,0), LU_echelon.lower(0,0));   ASSERT_EQ(LU_Result.lower(0,1), LU_echelon.lower(0,1));   ASSERT_EQ(LU_Result.lower(0,2), LU_echelon.lower(0,2));
    ASSERT_EQ(LU_Result.lower(1,0), LU_echelon.lower(1,0));   ASSERT_EQ(LU_Result.lower(1,1), LU_echelon.lower(1,1));  ASSERT_EQ(LU_Result.lower(1,2),  LU_echelon.lower(1,2));
    ASSERT_EQ(LU_Result.lower(2,0), LU_echelon.lower(2,0));   ASSERT_EQ(LU_Result.lower(2,1), LU_echelon.lower(2,1));   ASSERT_EQ(LU_Result.lower(2,2), LU_echelon.lower(2,2));

    ASSERT_EQ(LU_Result.upper(0,0), LU_echelon.upper(0,0));   ASSERT_EQ(LU_Result.upper(0,1), LU_echelon.upper(0,1));   ASSERT_EQ(LU_Result.upper(0,2), LU_echelon.upper(0,2));
    ASSERT_EQ(LU_Result.upper(1,0), LU_echelon.upper(1,0));   ASSERT_EQ(LU_Result.upper(1,1), LU_echelon.upper(1,1));  ASSERT_EQ(LU_Result.upper(1,2),  LU_echelon.upper(1,2));
    ASSERT_EQ(LU_Result.upper(2,0), LU_echelon.upper(2,0));   ASSERT_EQ(LU_Result.upper(2,1), LU_echelon.upper(2,1));   ASSERT_EQ(LU_Result.upper(2,2), LU_echelon.upper(2,2));
}

TEST_F(MatrixLUFactorization_StrangTests, Chapter_1_5_problem_4c)
{
    const auto data = std::vector<int>{1,1,1,
                                       1,4,4,
                                       1,4,8};

    const auto matrix = Matrix<int>(data, 3, 3);

    const auto LU_Result  = factorizeLU(matrix);
    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 1);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 1);  ASSERT_EQ(LU_Result.lower(2,1),  1);   ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 1);   ASSERT_EQ(LU_Result.upper(0,1), 1);   ASSERT_EQ(LU_Result.upper(0,2), 1);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), 3);   ASSERT_EQ(LU_Result.upper(1,2), 3);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), 4);

    // Ensure L*U reconstructs the initial matrix
    const auto result = LU_Result.lower.multiply(LU_Result.upper);

    const double epsilon = 1e-9;
    ASSERT_NEAR(result(0,0), matrix(0,0), epsilon); ASSERT_NEAR(result(0,1), matrix(0,1), epsilon); ASSERT_NEAR(result(0,2), matrix(0,2), epsilon);
    ASSERT_NEAR(result(1,0), matrix(1,0), epsilon); ASSERT_NEAR(result(1,1), matrix(1,1), epsilon); ASSERT_NEAR(result(1,2), matrix(1,2), epsilon);
    ASSERT_NEAR(result(2,0), matrix(2,0), epsilon); ASSERT_NEAR(result(2,1), matrix(2,1), epsilon); ASSERT_NEAR(result(2,2), matrix(2,2), epsilon);

    // Test LU_echelon is outputting the same result (since this is non-singular matrix)
    const auto LU_echelon = factorizeLU_echelon(matrix);
    ASSERT_EQ(LU_echelon.upper.rows(), 3); ASSERT_EQ(LU_echelon.upper.cols(), 3);

    ASSERT_EQ(LU_Result.lower(0,0), LU_echelon.lower(0,0));   ASSERT_EQ(LU_Result.lower(0,1), LU_echelon.lower(0,1));   ASSERT_EQ(LU_Result.lower(0,2), LU_echelon.lower(0,2));
    ASSERT_EQ(LU_Result.lower(1,0), LU_echelon.lower(1,0));   ASSERT_EQ(LU_Result.lower(1,1), LU_echelon.lower(1,1));  ASSERT_EQ(LU_Result.lower(1,2),  LU_echelon.lower(1,2));
    ASSERT_EQ(LU_Result.lower(2,0), LU_echelon.lower(2,0));   ASSERT_EQ(LU_Result.lower(2,1), LU_echelon.lower(2,1));   ASSERT_EQ(LU_Result.lower(2,2), LU_echelon.lower(2,2));

    ASSERT_EQ(LU_Result.upper(0,0), LU_echelon.upper(0,0));   ASSERT_EQ(LU_Result.upper(0,1), LU_echelon.upper(0,1));   ASSERT_EQ(LU_Result.upper(0,2), LU_echelon.upper(0,2));
    ASSERT_EQ(LU_Result.upper(1,0), LU_echelon.upper(1,0));   ASSERT_EQ(LU_Result.upper(1,1), LU_echelon.upper(1,1));  ASSERT_EQ(LU_Result.upper(1,2),  LU_echelon.upper(1,2));
    ASSERT_EQ(LU_Result.upper(2,0), LU_echelon.upper(2,0));   ASSERT_EQ(LU_Result.upper(2,1), LU_echelon.upper(2,1));   ASSERT_EQ(LU_Result.upper(2,2), LU_echelon.upper(2,2));
}

TEST_F(MatrixLUFactorization_StrangTests, Chapter_1_5_problem_5)
{
    const auto data = std::vector<int>{2,3,3,
                                       0,5,7,
                                       6,9,8};

    const auto matrix = Matrix<int>(data, 3, 3);

    const auto LU_Result  = factorizeLU(matrix);
    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 0);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 3);  ASSERT_EQ(LU_Result.lower(2,1),  0);   ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 2);   ASSERT_EQ(LU_Result.upper(0,1), 3);   ASSERT_EQ(LU_Result.upper(0,2), 3);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), 5);   ASSERT_EQ(LU_Result.upper(1,2), 7);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), -1);

    // Ensure L*U reconstructs the initial matrix
    const auto result = LU_Result.lower.multiply(LU_Result.upper);

    const double epsilon = 1e-9;
    ASSERT_NEAR(result(0,0), matrix(0,0), epsilon); ASSERT_NEAR(result(0,1), matrix(0,1), epsilon); ASSERT_NEAR(result(0,2), matrix(0,2), epsilon);
    ASSERT_NEAR(result(1,0), matrix(1,0), epsilon); ASSERT_NEAR(result(1,1), matrix(1,1), epsilon); ASSERT_NEAR(result(1,2), matrix(1,2), epsilon);
    ASSERT_NEAR(result(2,0), matrix(2,0), epsilon); ASSERT_NEAR(result(2,1), matrix(2,1), epsilon); ASSERT_NEAR(result(2,2), matrix(2,2), epsilon);

    // Test LU_echelon is outputting the same result (since this is non-singular matrix)
    const auto LU_echelon = factorizeLU_echelon(matrix);
    ASSERT_EQ(LU_echelon.upper.rows(), 3); ASSERT_EQ(LU_echelon.upper.cols(), 3);

    ASSERT_EQ(LU_Result.lower(0,0), LU_echelon.lower(0,0));   ASSERT_EQ(LU_Result.lower(0,1), LU_echelon.lower(0,1));   ASSERT_EQ(LU_Result.lower(0,2), LU_echelon.lower(0,2));
    ASSERT_EQ(LU_Result.lower(1,0), LU_echelon.lower(1,0));   ASSERT_EQ(LU_Result.lower(1,1), LU_echelon.lower(1,1));  ASSERT_EQ(LU_Result.lower(1,2),  LU_echelon.lower(1,2));
    ASSERT_EQ(LU_Result.lower(2,0), LU_echelon.lower(2,0));   ASSERT_EQ(LU_Result.lower(2,1), LU_echelon.lower(2,1));   ASSERT_EQ(LU_Result.lower(2,2), LU_echelon.lower(2,2));

    ASSERT_EQ(LU_Result.upper(0,0), LU_echelon.upper(0,0));   ASSERT_EQ(LU_Result.upper(0,1), LU_echelon.upper(0,1));   ASSERT_EQ(LU_Result.upper(0,2), LU_echelon.upper(0,2));
    ASSERT_EQ(LU_Result.upper(1,0), LU_echelon.upper(1,0));   ASSERT_EQ(LU_Result.upper(1,1), LU_echelon.upper(1,1));  ASSERT_EQ(LU_Result.upper(1,2),  LU_echelon.upper(1,2));
    ASSERT_EQ(LU_Result.upper(2,0), LU_echelon.upper(2,0));   ASSERT_EQ(LU_Result.upper(2,1), LU_echelon.upper(2,1));   ASSERT_EQ(LU_Result.upper(2,2), LU_echelon.upper(2,2));
}

TEST_F(MatrixLUFactorization_StrangTests, Chapter_1_5_problem_21)
{
    const auto data = std::vector<int>{1,1,1,
                                       1,2,3,
                                       1,3,6};

    const auto matrix = Matrix<int>(data, 3, 3);

    const auto LU_Result  = factorizeLU(matrix);
    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 1);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 1);  ASSERT_EQ(LU_Result.lower(2,1),  2);   ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 1);   ASSERT_EQ(LU_Result.upper(0,1), 1);   ASSERT_EQ(LU_Result.upper(0,2), 1);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), 1);   ASSERT_EQ(LU_Result.upper(1,2), 2);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), 1);

    // Ensure L*U reconstructs the initial matrix
    const auto result = LU_Result.lower.multiply(LU_Result.upper);

    const double epsilon = 1e-9;
    ASSERT_NEAR(result(0,0), matrix(0,0), epsilon); ASSERT_NEAR(result(0,1), matrix(0,1), epsilon); ASSERT_NEAR(result(0,2), matrix(0,2), epsilon);
    ASSERT_NEAR(result(1,0), matrix(1,0), epsilon); ASSERT_NEAR(result(1,1), matrix(1,1), epsilon); ASSERT_NEAR(result(1,2), matrix(1,2), epsilon);
    ASSERT_NEAR(result(2,0), matrix(2,0), epsilon); ASSERT_NEAR(result(2,1), matrix(2,1), epsilon); ASSERT_NEAR(result(2,2), matrix(2,2), epsilon);

    // Test LU_echelon is outputting the same result (since this is non-singular matrix)
    const auto LU_echelon = factorizeLU_echelon(matrix);
    ASSERT_EQ(LU_echelon.upper.rows(), 3); ASSERT_EQ(LU_echelon.upper.cols(), 3);

    ASSERT_EQ(LU_Result.lower(0,0), LU_echelon.lower(0,0));   ASSERT_EQ(LU_Result.lower(0,1), LU_echelon.lower(0,1));   ASSERT_EQ(LU_Result.lower(0,2), LU_echelon.lower(0,2));
    ASSERT_EQ(LU_Result.lower(1,0), LU_echelon.lower(1,0));   ASSERT_EQ(LU_Result.lower(1,1), LU_echelon.lower(1,1));  ASSERT_EQ(LU_Result.lower(1,2),  LU_echelon.lower(1,2));
    ASSERT_EQ(LU_Result.lower(2,0), LU_echelon.lower(2,0));   ASSERT_EQ(LU_Result.lower(2,1), LU_echelon.lower(2,1));   ASSERT_EQ(LU_Result.lower(2,2), LU_echelon.lower(2,2));

    ASSERT_EQ(LU_Result.upper(0,0), LU_echelon.upper(0,0));   ASSERT_EQ(LU_Result.upper(0,1), LU_echelon.upper(0,1));   ASSERT_EQ(LU_Result.upper(0,2), LU_echelon.upper(0,2));
    ASSERT_EQ(LU_Result.upper(1,0), LU_echelon.upper(1,0));   ASSERT_EQ(LU_Result.upper(1,1), LU_echelon.upper(1,1));  ASSERT_EQ(LU_Result.upper(1,2),  LU_echelon.upper(1,2));
    ASSERT_EQ(LU_Result.upper(2,0), LU_echelon.upper(2,0));   ASSERT_EQ(LU_Result.upper(2,1), LU_echelon.upper(2,1));   ASSERT_EQ(LU_Result.upper(2,2), LU_echelon.upper(2,2));
}

TEST_F(MatrixLUFactorization_StrangTests, Chapter_1_5_problem_23)
{
    const auto data = std::vector<int>{1,1,1,
                                       2,4,5,
                                       0,4,0};

    const auto matrix = Matrix<int>(data, 3, 3);

    const auto LU_Result  = factorizeLU(matrix);
    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 2);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 0);  ASSERT_EQ(LU_Result.lower(2,1),  2);   ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 1);   ASSERT_EQ(LU_Result.upper(0,1), 1);   ASSERT_EQ(LU_Result.upper(0,2), 1);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), 2);   ASSERT_EQ(LU_Result.upper(1,2), 3);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), -6);

    // Ensure L*U reconstructs the initial matrix
    const auto result = LU_Result.lower.multiply(LU_Result.upper);

    const double epsilon = 1e-9;
    ASSERT_NEAR(result(0,0), matrix(0,0), epsilon); ASSERT_NEAR(result(0,1), matrix(0,1), epsilon); ASSERT_NEAR(result(0,2), matrix(0,2), epsilon);
    ASSERT_NEAR(result(1,0), matrix(1,0), epsilon); ASSERT_NEAR(result(1,1), matrix(1,1), epsilon); ASSERT_NEAR(result(1,2), matrix(1,2), epsilon);
    ASSERT_NEAR(result(2,0), matrix(2,0), epsilon); ASSERT_NEAR(result(2,1), matrix(2,1), epsilon); ASSERT_NEAR(result(2,2), matrix(2,2), epsilon);

    // Test LU_echelon is outputting the same result (since this is non-singular matrix)
    const auto LU_echelon = factorizeLU_echelon(matrix);
    ASSERT_EQ(LU_echelon.upper.rows(), 3); ASSERT_EQ(LU_echelon.upper.cols(), 3);

    ASSERT_EQ(LU_Result.lower(0,0), LU_echelon.lower(0,0));   ASSERT_EQ(LU_Result.lower(0,1), LU_echelon.lower(0,1));   ASSERT_EQ(LU_Result.lower(0,2), LU_echelon.lower(0,2));
    ASSERT_EQ(LU_Result.lower(1,0), LU_echelon.lower(1,0));   ASSERT_EQ(LU_Result.lower(1,1), LU_echelon.lower(1,1));  ASSERT_EQ(LU_Result.lower(1,2),  LU_echelon.lower(1,2));
    ASSERT_EQ(LU_Result.lower(2,0), LU_echelon.lower(2,0));   ASSERT_EQ(LU_Result.lower(2,1), LU_echelon.lower(2,1));   ASSERT_EQ(LU_Result.lower(2,2), LU_echelon.lower(2,2));

    ASSERT_EQ(LU_Result.upper(0,0), LU_echelon.upper(0,0));   ASSERT_EQ(LU_Result.upper(0,1), LU_echelon.upper(0,1));   ASSERT_EQ(LU_Result.upper(0,2), LU_echelon.upper(0,2));
    ASSERT_EQ(LU_Result.upper(1,0), LU_echelon.upper(1,0));   ASSERT_EQ(LU_Result.upper(1,1), LU_echelon.upper(1,1));  ASSERT_EQ(LU_Result.upper(1,2),  LU_echelon.upper(1,2));
    ASSERT_EQ(LU_Result.upper(2,0), LU_echelon.upper(2,0));   ASSERT_EQ(LU_Result.upper(2,1), LU_echelon.upper(2,1));   ASSERT_EQ(LU_Result.upper(2,2), LU_echelon.upper(2,2));
}

TEST_F(MatrixLUFactorization_StrangTests, Chapter_1_5_problem_24)
{
    const auto data = std::vector<int>{1,0,1,
                                       2,2,2,
                                       3,4,5};

    const auto matrix = Matrix<int>(data, 3, 3);

    const auto LU_Result  = factorizeLU(matrix);
    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 2);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 3);  ASSERT_EQ(LU_Result.lower(2,1),  2);   ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 1);   ASSERT_EQ(LU_Result.upper(0,1), 0);   ASSERT_EQ(LU_Result.upper(0,2), 1);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), 2);   ASSERT_EQ(LU_Result.upper(1,2), 0);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), 2);

    // Ensure L*U reconstructs the initial matrix
    const auto result = LU_Result.lower.multiply(LU_Result.upper);

    const double epsilon = 1e-9;
    ASSERT_NEAR(result(0,0), matrix(0,0), epsilon); ASSERT_NEAR(result(0,1), matrix(0,1), epsilon); ASSERT_NEAR(result(0,2), matrix(0,2), epsilon);
    ASSERT_NEAR(result(1,0), matrix(1,0), epsilon); ASSERT_NEAR(result(1,1), matrix(1,1), epsilon); ASSERT_NEAR(result(1,2), matrix(1,2), epsilon);
    ASSERT_NEAR(result(2,0), matrix(2,0), epsilon); ASSERT_NEAR(result(2,1), matrix(2,1), epsilon); ASSERT_NEAR(result(2,2), matrix(2,2), epsilon);

    // Test LU_echelon is outputting the same result (since this is non-singular matrix)
    const auto LU_echelon = factorizeLU_echelon(matrix);
    ASSERT_EQ(LU_echelon.upper.rows(), 3); ASSERT_EQ(LU_echelon.upper.cols(), 3);

    ASSERT_EQ(LU_Result.lower(0,0), LU_echelon.lower(0,0));   ASSERT_EQ(LU_Result.lower(0,1), LU_echelon.lower(0,1));   ASSERT_EQ(LU_Result.lower(0,2), LU_echelon.lower(0,2));
    ASSERT_EQ(LU_Result.lower(1,0), LU_echelon.lower(1,0));   ASSERT_EQ(LU_Result.lower(1,1), LU_echelon.lower(1,1));  ASSERT_EQ(LU_Result.lower(1,2),  LU_echelon.lower(1,2));
    ASSERT_EQ(LU_Result.lower(2,0), LU_echelon.lower(2,0));   ASSERT_EQ(LU_Result.lower(2,1), LU_echelon.lower(2,1));   ASSERT_EQ(LU_Result.lower(2,2), LU_echelon.lower(2,2));

    ASSERT_EQ(LU_Result.upper(0,0), LU_echelon.upper(0,0));   ASSERT_EQ(LU_Result.upper(0,1), LU_echelon.upper(0,1));   ASSERT_EQ(LU_Result.upper(0,2), LU_echelon.upper(0,2));
    ASSERT_EQ(LU_Result.upper(1,0), LU_echelon.upper(1,0));   ASSERT_EQ(LU_Result.upper(1,1), LU_echelon.upper(1,1));  ASSERT_EQ(LU_Result.upper(1,2),  LU_echelon.upper(1,2));
    ASSERT_EQ(LU_Result.upper(2,0), LU_echelon.upper(2,0));   ASSERT_EQ(LU_Result.upper(2,1), LU_echelon.upper(2,1));   ASSERT_EQ(LU_Result.upper(2,2), LU_echelon.upper(2,2));
}

TEST_F(MatrixLUFactorization_StrangTests, Chapter_1_5_problem_27)
{
    const auto data = std::vector<int>{2,4,8,
                                       0,3,9,
                                       0,0,7};

    const auto matrix = Matrix<int>(data, 3, 3);

    const auto LU_Result  = factorizeLU(matrix);
    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 0);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 0);  ASSERT_EQ(LU_Result.lower(2,1),  0);   ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 2);   ASSERT_EQ(LU_Result.upper(0,1), 4);   ASSERT_EQ(LU_Result.upper(0,2), 8);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), 3);   ASSERT_EQ(LU_Result.upper(1,2), 9);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), 7);

    // Ensure L*U reconstructs the initial matrix
    const auto result = LU_Result.lower.multiply(LU_Result.upper);

    const double epsilon = 1e-9;
    ASSERT_NEAR(result(0,0), matrix(0,0), epsilon); ASSERT_NEAR(result(0,1), matrix(0,1), epsilon); ASSERT_NEAR(result(0,2), matrix(0,2), epsilon);
    ASSERT_NEAR(result(1,0), matrix(1,0), epsilon); ASSERT_NEAR(result(1,1), matrix(1,1), epsilon); ASSERT_NEAR(result(1,2), matrix(1,2), epsilon);
    ASSERT_NEAR(result(2,0), matrix(2,0), epsilon); ASSERT_NEAR(result(2,1), matrix(2,1), epsilon); ASSERT_NEAR(result(2,2), matrix(2,2), epsilon);

    // Test LU_echelon is outputting the same result (since this is non-singular matrix)
    const auto LU_echelon = factorizeLU_echelon(matrix);
    ASSERT_EQ(LU_echelon.upper.rows(), 3); ASSERT_EQ(LU_echelon.upper.cols(), 3);

    ASSERT_EQ(LU_Result.lower(0,0), LU_echelon.lower(0,0));   ASSERT_EQ(LU_Result.lower(0,1), LU_echelon.lower(0,1));   ASSERT_EQ(LU_Result.lower(0,2), LU_echelon.lower(0,2));
    ASSERT_EQ(LU_Result.lower(1,0), LU_echelon.lower(1,0));   ASSERT_EQ(LU_Result.lower(1,1), LU_echelon.lower(1,1));  ASSERT_EQ(LU_Result.lower(1,2),  LU_echelon.lower(1,2));
    ASSERT_EQ(LU_Result.lower(2,0), LU_echelon.lower(2,0));   ASSERT_EQ(LU_Result.lower(2,1), LU_echelon.lower(2,1));   ASSERT_EQ(LU_Result.lower(2,2), LU_echelon.lower(2,2));

    ASSERT_EQ(LU_Result.upper(0,0), LU_echelon.upper(0,0));   ASSERT_EQ(LU_Result.upper(0,1), LU_echelon.upper(0,1));   ASSERT_EQ(LU_Result.upper(0,2), LU_echelon.upper(0,2));
    ASSERT_EQ(LU_Result.upper(1,0), LU_echelon.upper(1,0));   ASSERT_EQ(LU_Result.upper(1,1), LU_echelon.upper(1,1));  ASSERT_EQ(LU_Result.upper(1,2),  LU_echelon.upper(1,2));
    ASSERT_EQ(LU_Result.upper(2,0), LU_echelon.upper(2,0));   ASSERT_EQ(LU_Result.upper(2,1), LU_echelon.upper(2,1));   ASSERT_EQ(LU_Result.upper(2,2), LU_echelon.upper(2,2));
}

TEST_F(MatrixLUFactorization_StrangTests, Chapter_1_5_problem_28b)
{
    const auto data = std::vector<int>{1,4,0,
                                       4,12,4,
                                       0,4,0};

    const auto matrix = Matrix<int>(data, 3, 3);

    const auto LU_Result  = factorizeLU(matrix);
    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 4);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 0);  ASSERT_EQ(LU_Result.lower(2,1),  -1);   ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 1);   ASSERT_EQ(LU_Result.upper(0,1), 4);   ASSERT_EQ(LU_Result.upper(0,2), 0);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), -4);   ASSERT_EQ(LU_Result.upper(1,2), 4);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), 4);

    // Ensure L*U reconstructs the initial matrix
    const auto result = LU_Result.lower.multiply(LU_Result.upper);

    const double epsilon = 1e-9;
    ASSERT_NEAR(result(0,0), matrix(0,0), epsilon); ASSERT_NEAR(result(0,1), matrix(0,1), epsilon); ASSERT_NEAR(result(0,2), matrix(0,2), epsilon);
    ASSERT_NEAR(result(1,0), matrix(1,0), epsilon); ASSERT_NEAR(result(1,1), matrix(1,1), epsilon); ASSERT_NEAR(result(1,2), matrix(1,2), epsilon);
    ASSERT_NEAR(result(2,0), matrix(2,0), epsilon); ASSERT_NEAR(result(2,1), matrix(2,1), epsilon); ASSERT_NEAR(result(2,2), matrix(2,2), epsilon);

    // Test LU_echelon is outputting the same result (since this is non-singular matrix)
    const auto LU_echelon = factorizeLU_echelon(matrix);
    ASSERT_EQ(LU_echelon.upper.rows(), 3); ASSERT_EQ(LU_echelon.upper.cols(), 3);

    ASSERT_EQ(LU_Result.lower(0,0), LU_echelon.lower(0,0));   ASSERT_EQ(LU_Result.lower(0,1), LU_echelon.lower(0,1));   ASSERT_EQ(LU_Result.lower(0,2), LU_echelon.lower(0,2));
    ASSERT_EQ(LU_Result.lower(1,0), LU_echelon.lower(1,0));   ASSERT_EQ(LU_Result.lower(1,1), LU_echelon.lower(1,1));  ASSERT_EQ(LU_Result.lower(1,2),  LU_echelon.lower(1,2));
    ASSERT_EQ(LU_Result.lower(2,0), LU_echelon.lower(2,0));   ASSERT_EQ(LU_Result.lower(2,1), LU_echelon.lower(2,1));   ASSERT_EQ(LU_Result.lower(2,2), LU_echelon.lower(2,2));

    ASSERT_EQ(LU_Result.upper(0,0), LU_echelon.upper(0,0));   ASSERT_EQ(LU_Result.upper(0,1), LU_echelon.upper(0,1));   ASSERT_EQ(LU_Result.upper(0,2), LU_echelon.upper(0,2));
    ASSERT_EQ(LU_Result.upper(1,0), LU_echelon.upper(1,0));   ASSERT_EQ(LU_Result.upper(1,1), LU_echelon.upper(1,1));  ASSERT_EQ(LU_Result.upper(1,2),  LU_echelon.upper(1,2));
    ASSERT_EQ(LU_Result.upper(2,0), LU_echelon.upper(2,0));   ASSERT_EQ(LU_Result.upper(2,1), LU_echelon.upper(2,1));   ASSERT_EQ(LU_Result.upper(2,2), LU_echelon.upper(2,2));
}

TEST_F(MatrixLUFactorization_StrangTests, Chapter_1_5_problem_31a)
{
    const auto data = std::vector<int>{1,1,0,
                                       1,2,1,
                                       0,1,2};

    const auto matrix = Matrix<int>(data, 3, 3);

    const auto LU_Result  = factorizeLU(matrix);
    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 1);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 0);  ASSERT_EQ(LU_Result.lower(2,1),  1);   ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 1);   ASSERT_EQ(LU_Result.upper(0,1), 1);   ASSERT_EQ(LU_Result.upper(0,2), 0);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), 1);   ASSERT_EQ(LU_Result.upper(1,2), 1);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), 1);

    // Ensure L*U reconstructs the initial matrix
    const auto result = LU_Result.lower.multiply(LU_Result.upper);

    const double epsilon = 1e-9;
    ASSERT_NEAR(result(0,0), matrix(0,0), epsilon); ASSERT_NEAR(result(0,1), matrix(0,1), epsilon); ASSERT_NEAR(result(0,2), matrix(0,2), epsilon);
    ASSERT_NEAR(result(1,0), matrix(1,0), epsilon); ASSERT_NEAR(result(1,1), matrix(1,1), epsilon); ASSERT_NEAR(result(1,2), matrix(1,2), epsilon);
    ASSERT_NEAR(result(2,0), matrix(2,0), epsilon); ASSERT_NEAR(result(2,1), matrix(2,1), epsilon); ASSERT_NEAR(result(2,2), matrix(2,2), epsilon);

    // Test LU_echelon is outputting the same result (since this is non-singular matrix)
    const auto LU_echelon = factorizeLU_echelon(matrix);
    ASSERT_EQ(LU_echelon.upper.rows(), 3); ASSERT_EQ(LU_echelon.upper.cols(), 3);

    ASSERT_EQ(LU_Result.lower(0,0), LU_echelon.lower(0,0));   ASSERT_EQ(LU_Result.lower(0,1), LU_echelon.lower(0,1));   ASSERT_EQ(LU_Result.lower(0,2), LU_echelon.lower(0,2));
    ASSERT_EQ(LU_Result.lower(1,0), LU_echelon.lower(1,0));   ASSERT_EQ(LU_Result.lower(1,1), LU_echelon.lower(1,1));  ASSERT_EQ(LU_Result.lower(1,2),  LU_echelon.lower(1,2));
    ASSERT_EQ(LU_Result.lower(2,0), LU_echelon.lower(2,0));   ASSERT_EQ(LU_Result.lower(2,1), LU_echelon.lower(2,1));   ASSERT_EQ(LU_Result.lower(2,2), LU_echelon.lower(2,2));

    ASSERT_EQ(LU_Result.upper(0,0), LU_echelon.upper(0,0));   ASSERT_EQ(LU_Result.upper(0,1), LU_echelon.upper(0,1));   ASSERT_EQ(LU_Result.upper(0,2), LU_echelon.upper(0,2));
    ASSERT_EQ(LU_Result.upper(1,0), LU_echelon.upper(1,0));   ASSERT_EQ(LU_Result.upper(1,1), LU_echelon.upper(1,1));  ASSERT_EQ(LU_Result.upper(1,2),  LU_echelon.upper(1,2));
    ASSERT_EQ(LU_Result.upper(2,0), LU_echelon.upper(2,0));   ASSERT_EQ(LU_Result.upper(2,1), LU_echelon.upper(2,1));   ASSERT_EQ(LU_Result.upper(2,2), LU_echelon.upper(2,2));
}

TEST_F(MatrixLUFactorization_StrangTests, Chapter_1_5_problem_33)
{
    const auto data = std::vector<int>{1,1,1,
                                       1,2,2,
                                       1,2,3};

    const auto matrix = Matrix<int>(data, 3, 3);

    const auto LU_Result  = factorizeLU(matrix);
    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 1);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 1);  ASSERT_EQ(LU_Result.lower(2,1),  1);   ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 1);   ASSERT_EQ(LU_Result.upper(0,1), 1);   ASSERT_EQ(LU_Result.upper(0,2), 1);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), 1);   ASSERT_EQ(LU_Result.upper(1,2), 1);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), 1);

    // Ensure L*U reconstructs the initial matrix
    const auto result = LU_Result.lower.multiply(LU_Result.upper);

    const double epsilon = 1e-9;
    ASSERT_NEAR(result(0,0), matrix(0,0), epsilon); ASSERT_NEAR(result(0,1), matrix(0,1), epsilon); ASSERT_NEAR(result(0,2), matrix(0,2), epsilon);
    ASSERT_NEAR(result(1,0), matrix(1,0), epsilon); ASSERT_NEAR(result(1,1), matrix(1,1), epsilon); ASSERT_NEAR(result(1,2), matrix(1,2), epsilon);
    ASSERT_NEAR(result(2,0), matrix(2,0), epsilon); ASSERT_NEAR(result(2,1), matrix(2,1), epsilon); ASSERT_NEAR(result(2,2), matrix(2,2), epsilon);

    // Test LU_echelon is outputting the same result (since this is non-singular matrix)
    const auto LU_echelon = factorizeLU_echelon(matrix);
    ASSERT_EQ(LU_echelon.upper.rows(), 3); ASSERT_EQ(LU_echelon.upper.cols(), 3);

    ASSERT_EQ(LU_Result.lower(0,0), LU_echelon.lower(0,0));   ASSERT_EQ(LU_Result.lower(0,1), LU_echelon.lower(0,1));   ASSERT_EQ(LU_Result.lower(0,2), LU_echelon.lower(0,2));
    ASSERT_EQ(LU_Result.lower(1,0), LU_echelon.lower(1,0));   ASSERT_EQ(LU_Result.lower(1,1), LU_echelon.lower(1,1));  ASSERT_EQ(LU_Result.lower(1,2),  LU_echelon.lower(1,2));
    ASSERT_EQ(LU_Result.lower(2,0), LU_echelon.lower(2,0));   ASSERT_EQ(LU_Result.lower(2,1), LU_echelon.lower(2,1));   ASSERT_EQ(LU_Result.lower(2,2), LU_echelon.lower(2,2));

    ASSERT_EQ(LU_Result.upper(0,0), LU_echelon.upper(0,0));   ASSERT_EQ(LU_Result.upper(0,1), LU_echelon.upper(0,1));   ASSERT_EQ(LU_Result.upper(0,2), LU_echelon.upper(0,2));
    ASSERT_EQ(LU_Result.upper(1,0), LU_echelon.upper(1,0));   ASSERT_EQ(LU_Result.upper(1,1), LU_echelon.upper(1,1));  ASSERT_EQ(LU_Result.upper(1,2),  LU_echelon.upper(1,2));
    ASSERT_EQ(LU_Result.upper(2,0), LU_echelon.upper(2,0));   ASSERT_EQ(LU_Result.upper(2,1), LU_echelon.upper(2,1));   ASSERT_EQ(LU_Result.upper(2,2), LU_echelon.upper(2,2));
}

TEST_F(MatrixLUFactorization_StrangTests, Chapter_1_review_problem_5a)
{
    const auto data = std::vector<int>{1,0,1,
                                       1,1,0,
                                       1,1,1};

    const auto matrix = Matrix<int>(data, 3,3);

    const auto LU_Result  = factorizeLU(matrix);
    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 1);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 1);  ASSERT_EQ(LU_Result.lower(2,1),  1);   ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 1);   ASSERT_EQ(LU_Result.upper(0,1), 0);   ASSERT_EQ(LU_Result.upper(0,2), 1);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), 1);   ASSERT_EQ(LU_Result.upper(1,2), -1);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), 1);

    // Ensure L*U reconstructs the initial matrix
    const auto result = LU_Result.lower.multiply(LU_Result.upper);

    const double epsilon = 1e-9;
    ASSERT_NEAR(result(0,0), matrix(0,0), epsilon); ASSERT_NEAR(result(0,1), matrix(0,1), epsilon); ASSERT_NEAR(result(0,2), matrix(0,2), epsilon);
    ASSERT_NEAR(result(1,0), matrix(1,0), epsilon); ASSERT_NEAR(result(1,1), matrix(1,1), epsilon); ASSERT_NEAR(result(1,2), matrix(1,2), epsilon);
    ASSERT_NEAR(result(2,0), matrix(2,0), epsilon); ASSERT_NEAR(result(2,1), matrix(2,1), epsilon); ASSERT_NEAR(result(2,2), matrix(2,2), epsilon);

    // Test LU_echelon is outputting the same result (since this is non-singular matrix)
    const auto LU_echelon = factorizeLU_echelon(matrix);
    ASSERT_EQ(LU_echelon.upper.rows(), 3); ASSERT_EQ(LU_echelon.upper.cols(), 3);

    ASSERT_EQ(LU_Result.lower(0,0), LU_echelon.lower(0,0));   ASSERT_EQ(LU_Result.lower(0,1), LU_echelon.lower(0,1));   ASSERT_EQ(LU_Result.lower(0,2), LU_echelon.lower(0,2));
    ASSERT_EQ(LU_Result.lower(1,0), LU_echelon.lower(1,0));   ASSERT_EQ(LU_Result.lower(1,1), LU_echelon.lower(1,1));  ASSERT_EQ(LU_Result.lower(1,2),  LU_echelon.lower(1,2));
    ASSERT_EQ(LU_Result.lower(2,0), LU_echelon.lower(2,0));   ASSERT_EQ(LU_Result.lower(2,1), LU_echelon.lower(2,1));   ASSERT_EQ(LU_Result.lower(2,2), LU_echelon.lower(2,2));

    ASSERT_EQ(LU_Result.upper(0,0), LU_echelon.upper(0,0));   ASSERT_EQ(LU_Result.upper(0,1), LU_echelon.upper(0,1));   ASSERT_EQ(LU_Result.upper(0,2), LU_echelon.upper(0,2));
    ASSERT_EQ(LU_Result.upper(1,0), LU_echelon.upper(1,0));   ASSERT_EQ(LU_Result.upper(1,1), LU_echelon.upper(1,1));  ASSERT_EQ(LU_Result.upper(1,2),  LU_echelon.upper(1,2));
    ASSERT_EQ(LU_Result.upper(2,0), LU_echelon.upper(2,0));   ASSERT_EQ(LU_Result.upper(2,1), LU_echelon.upper(2,1));   ASSERT_EQ(LU_Result.upper(2,2), LU_echelon.upper(2,2));
}

TEST_F(MatrixLUFactorization_StrangTests, Chapter_1_review_problem_5b_permutation)
{
    const auto data = std::vector<int>{0,1,1,
                                       1,0,1,
                                       1,1,0};

    const auto matrix = Matrix<int>(data, 3,3);

    const auto LU_Result  = factorizeLU(matrix);
    ASSERT_FALSE(LU_Result.permutation == std::nullopt);    // P_12

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 0);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 1);  ASSERT_EQ(LU_Result.lower(2,1),  1);   ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 1);   ASSERT_EQ(LU_Result.upper(0,1), 0);   ASSERT_EQ(LU_Result.upper(0,2), 1);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), 1);   ASSERT_EQ(LU_Result.upper(1,2), 1);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), -2);

    // Ensure P*A = L*U reconstructs the initial matrix
    const auto LU = LU_Result.lower.multiply(LU_Result.upper);
    const auto PA = LU_Result.permutation->multiply(matrix);

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
}

TEST_F(MatrixLUFactorization_StrangTests, Chapter_1_review_problem_17)
{
    const auto data = std::vector<int>{1,2,0,
                                       2,6,4,
                                       0,4,11};

    const auto matrix = Matrix<int>(data, 3,3);

    const auto LU_Result  = factorizeLU(matrix);
    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 2);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 0);  ASSERT_EQ(LU_Result.lower(2,1),  2);   ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 1);   ASSERT_EQ(LU_Result.upper(0,1), 2);   ASSERT_EQ(LU_Result.upper(0,2), 0);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), 2);   ASSERT_EQ(LU_Result.upper(1,2), 4);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), 3);

    // Ensure L*U reconstructs the initial matrix
    const auto result = LU_Result.lower.multiply(LU_Result.upper);

    const double epsilon = 1e-9;
    ASSERT_NEAR(result(0,0), matrix(0,0), epsilon); ASSERT_NEAR(result(0,1), matrix(0,1), epsilon); ASSERT_NEAR(result(0,2), matrix(0,2), epsilon);
    ASSERT_NEAR(result(1,0), matrix(1,0), epsilon); ASSERT_NEAR(result(1,1), matrix(1,1), epsilon); ASSERT_NEAR(result(1,2), matrix(1,2), epsilon);
    ASSERT_NEAR(result(2,0), matrix(2,0), epsilon); ASSERT_NEAR(result(2,1), matrix(2,1), epsilon); ASSERT_NEAR(result(2,2), matrix(2,2), epsilon);

    // Test LU_echelon is outputting the same result (since this is non-singular matrix)
    const auto LU_echelon = factorizeLU_echelon(matrix);
    ASSERT_EQ(LU_echelon.upper.rows(), 3); ASSERT_EQ(LU_echelon.upper.cols(), 3);

    ASSERT_EQ(LU_Result.lower(0,0), LU_echelon.lower(0,0));   ASSERT_EQ(LU_Result.lower(0,1), LU_echelon.lower(0,1));   ASSERT_EQ(LU_Result.lower(0,2), LU_echelon.lower(0,2));
    ASSERT_EQ(LU_Result.lower(1,0), LU_echelon.lower(1,0));   ASSERT_EQ(LU_Result.lower(1,1), LU_echelon.lower(1,1));  ASSERT_EQ(LU_Result.lower(1,2),  LU_echelon.lower(1,2));
    ASSERT_EQ(LU_Result.lower(2,0), LU_echelon.lower(2,0));   ASSERT_EQ(LU_Result.lower(2,1), LU_echelon.lower(2,1));   ASSERT_EQ(LU_Result.lower(2,2), LU_echelon.lower(2,2));

    ASSERT_EQ(LU_Result.upper(0,0), LU_echelon.upper(0,0));   ASSERT_EQ(LU_Result.upper(0,1), LU_echelon.upper(0,1));   ASSERT_EQ(LU_Result.upper(0,2), LU_echelon.upper(0,2));
    ASSERT_EQ(LU_Result.upper(1,0), LU_echelon.upper(1,0));   ASSERT_EQ(LU_Result.upper(1,1), LU_echelon.upper(1,1));  ASSERT_EQ(LU_Result.upper(1,2),  LU_echelon.upper(1,2));
    ASSERT_EQ(LU_Result.upper(2,0), LU_echelon.upper(2,0));   ASSERT_EQ(LU_Result.upper(2,1), LU_echelon.upper(2,1));   ASSERT_EQ(LU_Result.upper(2,2), LU_echelon.upper(2,2));
}