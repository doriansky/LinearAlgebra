//
// Created by dorian on 18.12.2023.
// stoicadorian@gmail.com
//
#include "gtest/gtest.h"
#include "Matrix.hpp"
#include "MatrixToolbox.hpp"

using namespace LinearAlgebra::Matrix;
using namespace LinearAlgebra::Vector;

class MatrixLUFactorizationTests : public ::testing::Test
{

protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};


TEST_F(MatrixLUFactorizationTests, LUFactorization_3x3)
{
    const auto data = std::vector<int> {1,2,3,
                                        2,3,1,
                                        -2,3,-2};
    const auto matrix = Matrix<int>(data, 3, 3);

    const auto LU_Result = factorizeLU(matrix);

    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 2);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), -2);  ASSERT_EQ(LU_Result.lower(2,1), -7);  ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_EQ(LU_Result.upper(0,0), 1);   ASSERT_EQ(LU_Result.upper(0,1), 2);   ASSERT_EQ(LU_Result.upper(0,2), 3);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), -1);  ASSERT_EQ(LU_Result.upper(1,2), -5);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), -31);

    // Ensure L*U reconstructs the initial matrix
    const auto result = LU_Result.lower * LU_Result.upper;

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

TEST_F(MatrixLUFactorizationTests, LUFactorization_3x4)
{
    const auto data = std::vector<int> {1,2,0,2,
                                        1,3,2,1,
                                        2,3,4,0};

    const auto matrix = Matrix<int>(data, 3, 4);

    const auto LU_Result = factorizeLU(matrix);

    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_EQ(LU_Result.lower(0,0), 1);   ASSERT_EQ(LU_Result.lower(0,1), 0);   ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 1);   ASSERT_EQ(LU_Result.lower(1,1), 1);   ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 2);   ASSERT_EQ(LU_Result.lower(2,1), -1);  ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 4);
    ASSERT_EQ(LU_Result.upper(0,0), 1);   ASSERT_EQ(LU_Result.upper(0,1), 2);   ASSERT_EQ(LU_Result.upper(0,2), 0);   ASSERT_EQ(LU_Result.upper(0,3), 2);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), 1);   ASSERT_EQ(LU_Result.upper(1,2), 2);   ASSERT_EQ(LU_Result.upper(1,3), -1);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), 6);   ASSERT_EQ(LU_Result.upper(2,3), -5);

    // Ensure L*U reconstructs the initial matrix
    const auto result = LU_Result.lower * LU_Result.upper;

    const double epsilon = 1e-9;
    ASSERT_NEAR(result(0,0), matrix(0,0), epsilon); ASSERT_NEAR(result(0,1), matrix(0,1), epsilon); ASSERT_NEAR(result(0,2), matrix(0,2), epsilon);
    ASSERT_NEAR(result(1,0), matrix(1,0), epsilon); ASSERT_NEAR(result(1,1), matrix(1,1), epsilon); ASSERT_NEAR(result(1,2), matrix(1,2), epsilon);
    ASSERT_NEAR(result(2,0), matrix(2,0), epsilon); ASSERT_NEAR(result(2,1), matrix(2,1), epsilon); ASSERT_NEAR(result(2,2), matrix(2,2), epsilon);

    // Test LU_echelon is outputting the same result (since this is non-singular matrix)
    const auto LU_echelon = factorizeLU_echelon(matrix);
    ASSERT_EQ(LU_echelon.upper.rows(), 3); ASSERT_EQ(LU_echelon.upper.cols(), 4);

    ASSERT_EQ(LU_Result.lower(0,0), LU_echelon.lower(0,0));   ASSERT_EQ(LU_Result.lower(0,1), LU_echelon.lower(0,1));   ASSERT_EQ(LU_Result.lower(0,2), LU_echelon.lower(0,2));
    ASSERT_EQ(LU_Result.lower(1,0), LU_echelon.lower(1,0));   ASSERT_EQ(LU_Result.lower(1,1), LU_echelon.lower(1,1));   ASSERT_EQ(LU_Result.lower(1,2),  LU_echelon.lower(1,2));
    ASSERT_EQ(LU_Result.lower(2,0), LU_echelon.lower(2,0));   ASSERT_EQ(LU_Result.lower(2,1), LU_echelon.lower(2,1));   ASSERT_EQ(LU_Result.lower(2,2), LU_echelon.lower(2,2));

    ASSERT_EQ(LU_Result.upper(0,0), LU_echelon.upper(0,0));   ASSERT_EQ(LU_Result.upper(0,1), LU_echelon.upper(0,1));   ASSERT_EQ(LU_Result.upper(0,2), LU_echelon.upper(0,2));     ASSERT_EQ(LU_Result.upper(0,3), LU_echelon.upper(0,3));
    ASSERT_EQ(LU_Result.upper(1,0), LU_echelon.upper(1,0));   ASSERT_EQ(LU_Result.upper(1,1), LU_echelon.upper(1,1));   ASSERT_EQ(LU_Result.upper(1,2),  LU_echelon.upper(1,2));    ASSERT_EQ(LU_Result.upper(1,3), LU_echelon.upper(1,3));
    ASSERT_EQ(LU_Result.upper(2,0), LU_echelon.upper(2,0));   ASSERT_EQ(LU_Result.upper(2,1), LU_echelon.upper(2,1));   ASSERT_EQ(LU_Result.upper(2,2), LU_echelon.upper(2,2));     ASSERT_EQ(LU_Result.upper(2,3), LU_echelon.upper(2,3));
}


TEST_F(MatrixLUFactorizationTests, LUFactorization_3x3_double)
{
    const double epsilon = 1e-9;
    const auto data = std::vector<double> {11./10,    12./10,     13./10,
                                           4,         5,          2,
                                           23./10,    32./10,     3};

    const auto matrix = Matrix<double>(data, 3, 3);

    const auto LU_Result = factorizeLU(matrix);

    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_NEAR(LU_Result.lower(0,0), 1, epsilon);          ASSERT_NEAR(LU_Result.lower(0,1), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(0,2), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(1,0), 40./11, epsilon);     ASSERT_NEAR(LU_Result.lower(1,1), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(1,2), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(2,0), 23./11, epsilon);     ASSERT_NEAR(LU_Result.lower(2,1), 38./35, epsilon); ASSERT_NEAR(LU_Result.lower(2,2), 1, epsilon);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_NEAR(LU_Result.upper(0,0), 11./10, epsilon);     ASSERT_NEAR(LU_Result.upper(0,1), 6./5, epsilon);       ASSERT_NEAR(LU_Result.upper(0,2), 13./10, epsilon);
    ASSERT_NEAR(LU_Result.upper(1,0), 0, epsilon);          ASSERT_NEAR(LU_Result.upper(1,1), 7./11, epsilon);      ASSERT_NEAR(LU_Result.upper(1,2), -30./11, epsilon);
    ASSERT_NEAR(LU_Result.upper(2,0), 0, epsilon);          ASSERT_NEAR(LU_Result.upper(2,1), 0, epsilon);          ASSERT_NEAR(LU_Result.upper(2,2), 227./70, epsilon);

    // Ensure L*U reconstructs the initial matrix
    const auto result = LU_Result.lower * LU_Result.upper;

    ASSERT_NEAR(result(0,0), matrix(0,0), epsilon); ASSERT_NEAR(result(0,1), matrix(0,1), epsilon); ASSERT_NEAR(result(0,2), matrix(0,2), epsilon);
    ASSERT_NEAR(result(1,0), matrix(1,0), epsilon); ASSERT_NEAR(result(1,1), matrix(1,1), epsilon); ASSERT_NEAR(result(1,2), matrix(1,2), epsilon);
    ASSERT_NEAR(result(2,0), matrix(2,0), epsilon); ASSERT_NEAR(result(2,1), matrix(2,1), epsilon); ASSERT_NEAR(result(2,2), matrix(2,2), epsilon);

    ASSERT_NEAR(determinant(matrix), 2.27, epsilon);

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

TEST_F(MatrixLUFactorizationTests, LUFactorization_3x3_double_2)
{
    const double epsilon = 1e-9;
    const auto data = std::vector<double> {1.23, 4.56, 7.89,
                                                            1.45, 6.32, 7.44,
                                                            5.43, 6.88, 1.43};

    const auto matrix = Matrix<double>(data, 3, 3);

    const auto LU_Result = factorizeLU(matrix);

    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_NEAR(LU_Result.lower(0,0), 1, epsilon);                        ASSERT_NEAR(LU_Result.lower(0,1), 0, epsilon);                    ASSERT_NEAR(LU_Result.lower(0,2), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(1,0), 1.178861788617886, epsilon);        ASSERT_NEAR(LU_Result.lower(1,1), 1, epsilon);                    ASSERT_NEAR(LU_Result.lower(1,2), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(2,0), 4.414634146341463, epsilon);        ASSERT_NEAR(LU_Result.lower(2,1), -14.03099173553719, epsilon);   ASSERT_NEAR(LU_Result.lower(2,2), 1, epsilon);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_NEAR(LU_Result.upper(0,0), 1.23, epsilon);       ASSERT_NEAR(LU_Result.upper(0,1), 4.56, epsilon);                 ASSERT_NEAR(LU_Result.upper(0,2), 7.89, epsilon);
    ASSERT_NEAR(LU_Result.upper(1,0), 0, epsilon);          ASSERT_NEAR(LU_Result.upper(1,1), 0.944390243902439, epsilon);    ASSERT_NEAR(LU_Result.upper(1,2), -1.861219512195122, epsilon);
    ASSERT_NEAR(LU_Result.upper(2,0), 0, epsilon);          ASSERT_NEAR(LU_Result.upper(2,1), 0, epsilon);                    ASSERT_NEAR(LU_Result.upper(2,2), -59.516219008264463, epsilon);


    // L*U should reconstruct the original matrix.
    const auto result = LU_Result.lower * LU_Result.upper;
    ASSERT_NEAR(result(0,0), matrix(0,0), epsilon); ASSERT_NEAR(result(0,1), matrix(0,1), epsilon); ASSERT_NEAR(result(0,2), matrix(0,2), epsilon);
    ASSERT_NEAR(result(1,0), matrix(1,0), epsilon); ASSERT_NEAR(result(1,1), matrix(1,1), epsilon); ASSERT_NEAR(result(1,2), matrix(1,2), epsilon);
    ASSERT_NEAR(result(2,0), matrix(2,0), epsilon); ASSERT_NEAR(result(2,1), matrix(2,1), epsilon); ASSERT_NEAR(result(2,2), matrix(2,2), epsilon);

    ASSERT_NEAR(determinant(matrix), -1728351./25000, epsilon);

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

TEST_F(MatrixLUFactorizationTests, LUFactorization_5x5)
{
    const double epsilon = 1e-9;
    const auto data = std::vector<double> {4,6,10,9,7,
                                           7,8,2,2,1,
                                           7,6,7,8,10,
                                           7,7,9,10,8,
                                           9,9,1,10,6};

    const auto matrix = Matrix<double>(data, 5, 5);

    const auto LU_Result = factorizeLU(matrix);

    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.lower.rows(), 5); ASSERT_EQ(LU_Result.lower.cols(), 5);
    ASSERT_NEAR(LU_Result.lower(0,0), 1, epsilon);    ASSERT_NEAR(LU_Result.lower(0,1), 0, epsilon);    ASSERT_NEAR(LU_Result.lower(0,2), 0, epsilon);            ASSERT_NEAR(LU_Result.lower(0,3), 0, epsilon);            ASSERT_NEAR(LU_Result.lower(0,4), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(1,0), 1.75, epsilon); ASSERT_NEAR(LU_Result.lower(1,1), 1, epsilon);    ASSERT_NEAR(LU_Result.lower(1,2), 0, epsilon);            ASSERT_NEAR(LU_Result.lower(1,3), 0, epsilon);            ASSERT_NEAR(LU_Result.lower(1,4), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(2,0), 1.75, epsilon); ASSERT_NEAR(LU_Result.lower(2,1), 1.8, epsilon);  ASSERT_NEAR(LU_Result.lower(2,2), 1, epsilon);            ASSERT_NEAR(LU_Result.lower(2,3), 0, epsilon);            ASSERT_NEAR(LU_Result.lower(2,4), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(3,0), 1.75, epsilon); ASSERT_NEAR(LU_Result.lower(3,1), 1.4, epsilon);  ASSERT_NEAR(LU_Result.lower(3,2), 0.7586206896, epsilon); ASSERT_NEAR(LU_Result.lower(3,3), 1, epsilon);            ASSERT_NEAR(LU_Result.lower(3,4), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(4,0), 2.25, epsilon); ASSERT_NEAR(LU_Result.lower(4,1), 1.8, epsilon);  ASSERT_NEAR(LU_Result.lower(4,2), 0.367816091, epsilon);  ASSERT_NEAR(LU_Result.lower(4,3), 13.6666666666, epsilon);   ASSERT_NEAR(LU_Result.lower(4,4), 1, epsilon);

    ASSERT_EQ(LU_Result.upper.rows(), 5); ASSERT_EQ(LU_Result.upper.cols(), 5);
    ASSERT_NEAR(LU_Result.upper(0,0), 4, epsilon);  ASSERT_NEAR(LU_Result.upper(0,1), 6, epsilon);      ASSERT_NEAR(LU_Result.upper(0,2), 10, epsilon);       ASSERT_NEAR(LU_Result.upper(0,3), 9, epsilon);            ASSERT_NEAR(LU_Result.upper(0,4), 7, epsilon);
    ASSERT_NEAR(LU_Result.upper(1,0), 0, epsilon);  ASSERT_NEAR(LU_Result.upper(1,1), -2.5, epsilon);   ASSERT_NEAR(LU_Result.upper(1,2), -15.5, epsilon);    ASSERT_NEAR(LU_Result.upper(1,3), -13.75, epsilon);       ASSERT_NEAR(LU_Result.upper(1,4), -11.25, epsilon);
    ASSERT_NEAR(LU_Result.upper(2,0), 0, epsilon);  ASSERT_NEAR(LU_Result.upper(2,1), 0, epsilon);      ASSERT_NEAR(LU_Result.upper(2,2), 17.4, epsilon);     ASSERT_NEAR(LU_Result.upper(2,3), 17, epsilon);           ASSERT_NEAR(LU_Result.upper(2,4), 18, epsilon);
    ASSERT_NEAR(LU_Result.upper(3,0), 0, epsilon);  ASSERT_NEAR(LU_Result.upper(3,1), 0, epsilon);      ASSERT_NEAR(LU_Result.upper(3,2), 0, epsilon);        ASSERT_NEAR(LU_Result.upper(3,3), 0.6034482758, epsilon); ASSERT_NEAR(LU_Result.upper(3,4), -2.155172413, epsilon);
    ASSERT_NEAR(LU_Result.upper(4,0), 0, epsilon);  ASSERT_NEAR(LU_Result.upper(4,1), 0, epsilon);      ASSERT_NEAR(LU_Result.upper(4,2), 0, epsilon);        ASSERT_NEAR(LU_Result.upper(4,3), 0, epsilon);            ASSERT_NEAR(LU_Result.upper(4,4), 33.333333333, epsilon);


    // L*U should reconstruct the original matrix.
    const auto result = LU_Result.lower * LU_Result.upper;
    ASSERT_NEAR(result(0,0), matrix(0,0), epsilon); ASSERT_NEAR(result(0,1), matrix(0,1), epsilon); ASSERT_NEAR(result(0,2), matrix(0,2), epsilon); ASSERT_NEAR(result(0,3), matrix(0,3), epsilon); ASSERT_NEAR(result(0,4), matrix(0,4), epsilon);
    ASSERT_NEAR(result(1,0), matrix(1,0), epsilon); ASSERT_NEAR(result(1,1), matrix(1,1), epsilon); ASSERT_NEAR(result(1,2), matrix(1,2), epsilon); ASSERT_NEAR(result(1,3), matrix(1,3), epsilon); ASSERT_NEAR(result(1,4), matrix(1,4), epsilon);
    ASSERT_NEAR(result(2,0), matrix(2,0), epsilon); ASSERT_NEAR(result(2,1), matrix(2,1), epsilon); ASSERT_NEAR(result(2,2), matrix(2,2), epsilon); ASSERT_NEAR(result(2,3), matrix(2,3), epsilon); ASSERT_NEAR(result(2,4), matrix(2,4), epsilon);
    ASSERT_NEAR(result(3,0), matrix(3,0), epsilon); ASSERT_NEAR(result(3,1), matrix(3,1), epsilon); ASSERT_NEAR(result(3,2), matrix(3,2), epsilon); ASSERT_NEAR(result(3,3), matrix(3,3), epsilon); ASSERT_NEAR(result(3,4), matrix(3,4), epsilon);
    ASSERT_NEAR(result(4,0), matrix(4,0), epsilon); ASSERT_NEAR(result(4,1), matrix(4,1), epsilon); ASSERT_NEAR(result(4,2), matrix(4,2), epsilon); ASSERT_NEAR(result(4,3), matrix(4,3), epsilon); ASSERT_NEAR(result(4,4), matrix(4,4), epsilon);

    ASSERT_NEAR(determinant(matrix), -3500, epsilon);

    // Test LU_echelon is outputting the same result (since this is non-singular matrix)
    const auto LU_echelon = factorizeLU_echelon(matrix);
    ASSERT_EQ(LU_echelon.upper.rows(), 5); ASSERT_EQ(LU_echelon.upper.cols(), 5);

    ASSERT_EQ(LU_Result.lower(0,0), LU_echelon.lower(0,0));   ASSERT_EQ(LU_Result.lower(0,1), LU_echelon.lower(0,1));   ASSERT_EQ(LU_Result.lower(0,2), LU_echelon.lower(0,2));     ASSERT_EQ(LU_Result.lower(0,3), LU_echelon.lower(0,3));   ASSERT_EQ(LU_Result.lower(0,4), LU_echelon.lower(0,4));
    ASSERT_EQ(LU_Result.lower(1,0), LU_echelon.lower(1,0));   ASSERT_EQ(LU_Result.lower(1,1), LU_echelon.lower(1,1));   ASSERT_EQ(LU_Result.lower(1,2),  LU_echelon.lower(1,2));    ASSERT_EQ(LU_Result.lower(1,3), LU_echelon.lower(1,3));   ASSERT_EQ(LU_Result.lower(1,4), LU_echelon.lower(1,4));
    ASSERT_EQ(LU_Result.lower(2,0), LU_echelon.lower(2,0));   ASSERT_EQ(LU_Result.lower(2,1), LU_echelon.lower(2,1));   ASSERT_EQ(LU_Result.lower(2,2), LU_echelon.lower(2,2));     ASSERT_EQ(LU_Result.lower(2,3), LU_echelon.lower(2,3));   ASSERT_EQ(LU_Result.lower(2,4), LU_echelon.lower(2,4));
    ASSERT_EQ(LU_Result.lower(3,0), LU_echelon.lower(3,0));   ASSERT_EQ(LU_Result.lower(3,1), LU_echelon.lower(3,1));   ASSERT_EQ(LU_Result.lower(3,2), LU_echelon.lower(3,2));     ASSERT_EQ(LU_Result.lower(3,3), LU_echelon.lower(3,3));   ASSERT_EQ(LU_Result.lower(3,4), LU_echelon.lower(3,4));
    ASSERT_EQ(LU_Result.lower(4,0), LU_echelon.lower(4,0));   ASSERT_EQ(LU_Result.lower(4,1), LU_echelon.lower(4,1));   ASSERT_EQ(LU_Result.lower(4,2), LU_echelon.lower(4,2));     ASSERT_EQ(LU_Result.lower(4,3), LU_echelon.lower(4,3));   ASSERT_EQ(LU_Result.lower(4,4), LU_echelon.lower(4,4));

    ASSERT_EQ(LU_Result.upper(0,0), LU_echelon.upper(0,0));   ASSERT_EQ(LU_Result.upper(0,1), LU_echelon.upper(0,1));   ASSERT_EQ(LU_Result.upper(0,2), LU_echelon.upper(0,2));     ASSERT_EQ(LU_Result.upper(0,3), LU_echelon.upper(0,3));   ASSERT_EQ(LU_Result.upper(0,4), LU_echelon.upper(0,4));
    ASSERT_EQ(LU_Result.upper(1,0), LU_echelon.upper(1,0));   ASSERT_EQ(LU_Result.upper(1,1), LU_echelon.upper(1,1));   ASSERT_EQ(LU_Result.upper(1,2),  LU_echelon.upper(1,2));    ASSERT_EQ(LU_Result.upper(1,3), LU_echelon.upper(1,3));   ASSERT_EQ(LU_Result.upper(1,4), LU_echelon.upper(1,4));
    ASSERT_EQ(LU_Result.upper(2,0), LU_echelon.upper(2,0));   ASSERT_EQ(LU_Result.upper(2,1), LU_echelon.upper(2,1));   ASSERT_EQ(LU_Result.upper(2,2), LU_echelon.upper(2,2));     ASSERT_EQ(LU_Result.upper(2,3), LU_echelon.upper(2,3));   ASSERT_EQ(LU_Result.upper(2,4), LU_echelon.upper(2,4));
    ASSERT_EQ(LU_Result.upper(3,0), LU_echelon.upper(3,0));   ASSERT_EQ(LU_Result.upper(3,1), LU_echelon.upper(3,1));   ASSERT_EQ(LU_Result.upper(3,2), LU_echelon.upper(3,2));     ASSERT_EQ(LU_Result.upper(3,3), LU_echelon.upper(3,3));   ASSERT_EQ(LU_Result.upper(3,4), LU_echelon.upper(3,4));
    ASSERT_EQ(LU_Result.upper(4,0), LU_echelon.upper(4,0));   ASSERT_EQ(LU_Result.upper(4,1), LU_echelon.upper(4,1));   ASSERT_EQ(LU_Result.upper(4,2), LU_echelon.upper(4,2));     ASSERT_EQ(LU_Result.upper(4,3), LU_echelon.upper(4,3));   ASSERT_EQ(LU_Result.upper(4,4), LU_echelon.upper(4,4));
}

TEST_F(MatrixLUFactorizationTests, LUFactorization_4x4_Tridiagonal_Strang_1_7_1)
{
    const auto data = std::vector<int>{2,   -1,     0,      0,
                                       -1,   2,     -1,     0,
                                       0,    -1,    2,      -1,
                                       0,    0,     -1,     2};

    const auto mat = Matrix<int>(data, 4, 4);

    const auto LU = factorizeLU(mat);

    ASSERT_TRUE(LU.permutation == std::nullopt);

    const long double epsilon = 1e-9;

    ASSERT_EQ(LU.lower.rows(), 4); ASSERT_EQ(LU.lower.cols(), 4);

    ASSERT_NEAR(LU.lower(0,0), 1, epsilon);     ASSERT_NEAR(LU.lower(0,1), 0, epsilon);     ASSERT_NEAR(LU.lower(0,2), 0, epsilon);         ASSERT_NEAR(LU.lower(0,3), 0, epsilon);
    ASSERT_NEAR(LU.lower(1,0), -1./2, epsilon);  ASSERT_NEAR(LU.lower(1,1), 1, epsilon);    ASSERT_NEAR(LU.lower(1,2), 0, epsilon);         ASSERT_NEAR(LU.lower(1,3), 0, epsilon);
    ASSERT_NEAR(LU.lower(2,0), 0, epsilon);     ASSERT_NEAR(LU.lower(2,1), -2./3, epsilon); ASSERT_NEAR(LU.lower(2,2), 1, epsilon);         ASSERT_NEAR(LU.lower(2,3), 0, epsilon);
    ASSERT_NEAR(LU.lower(3,0), 0, epsilon);     ASSERT_NEAR(LU.lower(3,1), 0, epsilon);     ASSERT_NEAR(LU.lower(3,2), -3./4, epsilon);     ASSERT_NEAR(LU.lower(3,3), 1, epsilon);


    ASSERT_EQ(LU.upper.rows(), 4); ASSERT_EQ(LU.upper.cols(), 4);
    ASSERT_NEAR(LU.upper(0,0), 2, epsilon);  ASSERT_NEAR(LU.upper(0,1), -1, epsilon);       ASSERT_NEAR(LU.upper(0,2), 0, epsilon);     ASSERT_NEAR(LU.upper(0,3), 0, epsilon);
    ASSERT_NEAR(LU.upper(1,0), 0, epsilon);  ASSERT_NEAR(LU.upper(1,1), 3./2, epsilon);     ASSERT_NEAR(LU.upper(1,2), -1, epsilon);    ASSERT_NEAR(LU.upper(1,3), 0, epsilon);
    ASSERT_NEAR(LU.upper(2,0), 0, epsilon);  ASSERT_NEAR(LU.upper(2,1), 0, epsilon);        ASSERT_NEAR(LU.upper(2,2), 4./3, epsilon);  ASSERT_NEAR(LU.upper(2,3), -1, epsilon);
    ASSERT_NEAR(LU.upper(3,0), 0, epsilon);  ASSERT_NEAR(LU.upper(3,1), 0, epsilon);        ASSERT_NEAR(LU.upper(3,2), 0, epsilon);     ASSERT_NEAR(LU.upper(3,3), 5./4, epsilon);


    // L*U should reconstruct the original matrix.
    const auto result = LU.lower * LU.upper;
    ASSERT_NEAR(result(0,0), mat(0,0), epsilon); ASSERT_NEAR(result(0,1), mat(0,1), epsilon); ASSERT_NEAR(result(0,2), mat(0,2), epsilon); ASSERT_NEAR(result(0,3), mat(0,3), epsilon);
    ASSERT_NEAR(result(1,0), mat(1,0), epsilon); ASSERT_NEAR(result(1,1), mat(1,1), epsilon); ASSERT_NEAR(result(1,2), mat(1,2), epsilon); ASSERT_NEAR(result(1,3), mat(1,3), epsilon);
    ASSERT_NEAR(result(2,0), mat(2,0), epsilon); ASSERT_NEAR(result(2,1), mat(2,1), epsilon); ASSERT_NEAR(result(2,2), mat(2,2), epsilon); ASSERT_NEAR(result(2,3), mat(2,3), epsilon);
    ASSERT_NEAR(result(3,0), mat(3,0), epsilon); ASSERT_NEAR(result(3,1), mat(3,1), epsilon); ASSERT_NEAR(result(3,2), mat(3,2), epsilon); ASSERT_NEAR(result(3,3), mat(3,3), epsilon);

    ASSERT_NEAR(determinant(mat), 5, 1e-9);

    // Test LU_echelon is outputting the same result (since this is non-singular matrix)
    const auto LU_echelon = factorizeLU_echelon(mat);
    ASSERT_EQ(LU_echelon.upper.rows(), 4); ASSERT_EQ(LU_echelon.upper.cols(), 4);

    ASSERT_EQ(LU.lower(0,0), LU_echelon.lower(0,0));   ASSERT_EQ(LU.lower(0,1), LU_echelon.lower(0,1));   ASSERT_EQ(LU.lower(0,2), LU_echelon.lower(0,2));     ASSERT_EQ(LU.lower(0,3), LU_echelon.lower(0,3));
    ASSERT_EQ(LU.lower(1,0), LU_echelon.lower(1,0));   ASSERT_EQ(LU.lower(1,1), LU_echelon.lower(1,1));   ASSERT_EQ(LU.lower(1,2),  LU_echelon.lower(1,2));    ASSERT_EQ(LU.lower(1,3), LU_echelon.lower(1,3));
    ASSERT_EQ(LU.lower(2,0), LU_echelon.lower(2,0));   ASSERT_EQ(LU.lower(2,1), LU_echelon.lower(2,1));   ASSERT_EQ(LU.lower(2,2), LU_echelon.lower(2,2));     ASSERT_EQ(LU.lower(2,3), LU_echelon.lower(2,3));
    ASSERT_EQ(LU.lower(3,0), LU_echelon.lower(3,0));   ASSERT_EQ(LU.lower(3,1), LU_echelon.lower(3,1));   ASSERT_EQ(LU.lower(3,2), LU_echelon.lower(3,2));     ASSERT_EQ(LU.lower(3,3), LU_echelon.lower(3,3));

    ASSERT_EQ(LU.upper(0,0), LU_echelon.upper(0,0));   ASSERT_EQ(LU.upper(0,1), LU_echelon.upper(0,1));   ASSERT_EQ(LU.upper(0,2), LU_echelon.upper(0,2));     ASSERT_EQ(LU.upper(0,3), LU_echelon.upper(0,3));
    ASSERT_EQ(LU.upper(1,0), LU_echelon.upper(1,0));   ASSERT_EQ(LU.upper(1,1), LU_echelon.upper(1,1));   ASSERT_EQ(LU.upper(1,2),  LU_echelon.upper(1,2));    ASSERT_EQ(LU.upper(1,3), LU_echelon.upper(1,3));
    ASSERT_EQ(LU.upper(2,0), LU_echelon.upper(2,0));   ASSERT_EQ(LU.upper(2,1), LU_echelon.upper(2,1));   ASSERT_EQ(LU.upper(2,2), LU_echelon.upper(2,2));     ASSERT_EQ(LU.upper(2,3), LU_echelon.upper(2,3));
    ASSERT_EQ(LU.upper(3,0), LU_echelon.upper(3,0));   ASSERT_EQ(LU.upper(3,1), LU_echelon.upper(3,1));   ASSERT_EQ(LU.upper(3,2), LU_echelon.upper(3,2));     ASSERT_EQ(LU.upper(3,3), LU_echelon.upper(3,3));
}

TEST_F(MatrixLUFactorizationTests, LUFactorization_5x5_Tridiagonal)
{
    const auto data = std::vector<int>{2,   -1,     0,      0,      0,
                                                      -1,   2,     -1,     0,      0,
                                                      0,    -1,    2,      -1,     0,
                                                      0,    0,     -1,     2,      -1,
                                                      0,    0,     0,     -1,      2};

    const auto mat = Matrix<int>(data, 5, 5);

    const auto LU = factorizeLU(mat);

    ASSERT_TRUE(LU.permutation == std::nullopt);

    const long double epsilon = 1e-9;

    ASSERT_EQ(LU.lower.rows(), 5); ASSERT_EQ(LU.lower.cols(), 5);

    ASSERT_NEAR(LU.lower(0,0), 1, epsilon);     ASSERT_NEAR(LU.lower(0,1), 0, epsilon);     ASSERT_NEAR(LU.lower(0,2), 0, epsilon);         ASSERT_NEAR(LU.lower(0,3), 0, epsilon);     ASSERT_NEAR(LU.lower(0,4), 0, epsilon);
    ASSERT_NEAR(LU.lower(1,0), -1./2, epsilon);  ASSERT_NEAR(LU.lower(1,1), 1, epsilon);    ASSERT_NEAR(LU.lower(1,2), 0, epsilon);         ASSERT_NEAR(LU.lower(1,3), 0, epsilon);     ASSERT_NEAR(LU.lower(1,4), 0, epsilon);
    ASSERT_NEAR(LU.lower(2,0), 0, epsilon);     ASSERT_NEAR(LU.lower(2,1), -2./3, epsilon); ASSERT_NEAR(LU.lower(2,2), 1, epsilon);         ASSERT_NEAR(LU.lower(2,3), 0, epsilon);     ASSERT_NEAR(LU.lower(2,4), 0, epsilon);
    ASSERT_NEAR(LU.lower(3,0), 0, epsilon);     ASSERT_NEAR(LU.lower(3,1), 0, epsilon);     ASSERT_NEAR(LU.lower(3,2), -3./4, epsilon);     ASSERT_NEAR(LU.lower(3,3), 1, epsilon);     ASSERT_NEAR(LU.lower(3,4), 0, epsilon);
    ASSERT_NEAR(LU.lower(4,0), 0, epsilon);     ASSERT_NEAR(LU.lower(4,1), 0, epsilon);     ASSERT_NEAR(LU.lower(4,2), 0, epsilon);         ASSERT_NEAR(LU.lower(4,3), -4./5, epsilon);  ASSERT_NEAR(LU.lower(4,4), 1, epsilon);

    ASSERT_EQ(LU.upper.rows(), 5); ASSERT_EQ(LU.upper.cols(), 5);
    ASSERT_NEAR(LU.upper(0,0), 2, epsilon);  ASSERT_NEAR(LU.upper(0,1), -1, epsilon);       ASSERT_NEAR(LU.upper(0,2), 0, epsilon);     ASSERT_NEAR(LU.upper(0,3), 0, epsilon);         ASSERT_NEAR(LU.upper(0,4), 0, epsilon);
    ASSERT_NEAR(LU.upper(1,0), 0, epsilon);  ASSERT_NEAR(LU.upper(1,1), 3./2, epsilon);     ASSERT_NEAR(LU.upper(1,2), -1, epsilon);    ASSERT_NEAR(LU.upper(1,3), 0, epsilon);         ASSERT_NEAR(LU.upper(1,4), 0, epsilon);
    ASSERT_NEAR(LU.upper(2,0), 0, epsilon);  ASSERT_NEAR(LU.upper(2,1), 0, epsilon);        ASSERT_NEAR(LU.upper(2,2), 4./3, epsilon);  ASSERT_NEAR(LU.upper(2,3), -1, epsilon);        ASSERT_NEAR(LU.upper(2,4), 0, epsilon);
    ASSERT_NEAR(LU.upper(3,0), 0, epsilon);  ASSERT_NEAR(LU.upper(3,1), 0, epsilon);        ASSERT_NEAR(LU.upper(3,2), 0, epsilon);     ASSERT_NEAR(LU.upper(3,3), 5./4, epsilon);      ASSERT_NEAR(LU.upper(3,4), -1, epsilon);
    ASSERT_NEAR(LU.upper(4,0), 0, epsilon);  ASSERT_NEAR(LU.upper(4,1), 0, epsilon);        ASSERT_NEAR(LU.upper(4,2), 0, epsilon);     ASSERT_NEAR(LU.upper(4,3), 0, epsilon);         ASSERT_NEAR(LU.upper(4,4), 6./5, epsilon);


    // L*U should reconstruct the original matrix.
    const auto result = LU.lower * LU.upper;
    ASSERT_NEAR(result(0,0), mat(0,0), epsilon); ASSERT_NEAR(result(0,1), mat(0,1), epsilon); ASSERT_NEAR(result(0,2), mat(0,2), epsilon); ASSERT_NEAR(result(0,3), mat(0,3), epsilon); ASSERT_NEAR(result(0,4), mat(0,4), epsilon);
    ASSERT_NEAR(result(1,0), mat(1,0), epsilon); ASSERT_NEAR(result(1,1), mat(1,1), epsilon); ASSERT_NEAR(result(1,2), mat(1,2), epsilon); ASSERT_NEAR(result(1,3), mat(1,3), epsilon); ASSERT_NEAR(result(1,4), mat(1,4), epsilon);
    ASSERT_NEAR(result(2,0), mat(2,0), epsilon); ASSERT_NEAR(result(2,1), mat(2,1), epsilon); ASSERT_NEAR(result(2,2), mat(2,2), epsilon); ASSERT_NEAR(result(2,3), mat(2,3), epsilon); ASSERT_NEAR(result(2,4), mat(2,4), epsilon);
    ASSERT_NEAR(result(3,0), mat(3,0), epsilon); ASSERT_NEAR(result(3,1), mat(3,1), epsilon); ASSERT_NEAR(result(3,2), mat(3,2), epsilon); ASSERT_NEAR(result(3,3), mat(3,3), epsilon); ASSERT_NEAR(result(3,4), mat(3,4), epsilon);
    ASSERT_NEAR(result(4,0), mat(4,0), epsilon); ASSERT_NEAR(result(4,1), mat(4,1), epsilon); ASSERT_NEAR(result(4,2), mat(4,2), epsilon); ASSERT_NEAR(result(4,3), mat(4,3), epsilon); ASSERT_NEAR(result(4,4), mat(4,4), epsilon);

    ASSERT_NEAR(determinant(mat), 6, 1e-9);

    // Test LU_echelon is outputting the same result (since this is non-singular matrix)
    const auto LU_echelon = factorizeLU_echelon(mat);
    ASSERT_EQ(LU_echelon.upper.rows(), 5); ASSERT_EQ(LU_echelon.upper.cols(), 5);

    ASSERT_EQ(LU.lower(0,0), LU_echelon.lower(0,0));   ASSERT_EQ(LU.lower(0,1), LU_echelon.lower(0,1));   ASSERT_EQ(LU.lower(0,2), LU_echelon.lower(0,2));     ASSERT_EQ(LU.lower(0,3), LU_echelon.lower(0,3));   ASSERT_EQ(LU.lower(0,4), LU_echelon.lower(0,4));
    ASSERT_EQ(LU.lower(1,0), LU_echelon.lower(1,0));   ASSERT_EQ(LU.lower(1,1), LU_echelon.lower(1,1));   ASSERT_EQ(LU.lower(1,2),  LU_echelon.lower(1,2));    ASSERT_EQ(LU.lower(1,3), LU_echelon.lower(1,3));   ASSERT_EQ(LU.lower(1,4), LU_echelon.lower(1,4));
    ASSERT_EQ(LU.lower(2,0), LU_echelon.lower(2,0));   ASSERT_EQ(LU.lower(2,1), LU_echelon.lower(2,1));   ASSERT_EQ(LU.lower(2,2), LU_echelon.lower(2,2));     ASSERT_EQ(LU.lower(2,3), LU_echelon.lower(2,3));   ASSERT_EQ(LU.lower(2,4), LU_echelon.lower(2,4));
    ASSERT_EQ(LU.lower(3,0), LU_echelon.lower(3,0));   ASSERT_EQ(LU.lower(3,1), LU_echelon.lower(3,1));   ASSERT_EQ(LU.lower(3,2), LU_echelon.lower(3,2));     ASSERT_EQ(LU.lower(3,3), LU_echelon.lower(3,3));   ASSERT_EQ(LU.lower(3,4), LU_echelon.lower(3,4));
    ASSERT_EQ(LU.lower(4,0), LU_echelon.lower(4,0));   ASSERT_EQ(LU.lower(4,1), LU_echelon.lower(4,1));   ASSERT_EQ(LU.lower(4,2), LU_echelon.lower(4,2));     ASSERT_EQ(LU.lower(4,3), LU_echelon.lower(4,3));   ASSERT_EQ(LU.lower(4,4), LU_echelon.lower(4,4));

    ASSERT_EQ(LU.upper(0,0), LU_echelon.upper(0,0));   ASSERT_EQ(LU.upper(0,1), LU_echelon.upper(0,1));   ASSERT_EQ(LU.upper(0,2), LU_echelon.upper(0,2));     ASSERT_EQ(LU.upper(0,3), LU_echelon.upper(0,3));   ASSERT_EQ(LU.upper(0,4), LU_echelon.upper(0,4));
    ASSERT_EQ(LU.upper(1,0), LU_echelon.upper(1,0));   ASSERT_EQ(LU.upper(1,1), LU_echelon.upper(1,1));   ASSERT_EQ(LU.upper(1,2),  LU_echelon.upper(1,2));    ASSERT_EQ(LU.upper(1,3), LU_echelon.upper(1,3));   ASSERT_EQ(LU.upper(1,4), LU_echelon.upper(1,4));
    ASSERT_EQ(LU.upper(2,0), LU_echelon.upper(2,0));   ASSERT_EQ(LU.upper(2,1), LU_echelon.upper(2,1));   ASSERT_EQ(LU.upper(2,2), LU_echelon.upper(2,2));     ASSERT_EQ(LU.upper(2,3), LU_echelon.upper(2,3));   ASSERT_EQ(LU.upper(2,4), LU_echelon.upper(2,4));
    ASSERT_EQ(LU.upper(3,0), LU_echelon.upper(3,0));   ASSERT_EQ(LU.upper(3,1), LU_echelon.upper(3,1));   ASSERT_EQ(LU.upper(3,2), LU_echelon.upper(3,2));     ASSERT_EQ(LU.upper(3,3), LU_echelon.upper(3,3));   ASSERT_EQ(LU.upper(3,4), LU_echelon.upper(3,4));
    ASSERT_EQ(LU.upper(4,0), LU_echelon.upper(4,0));   ASSERT_EQ(LU.upper(4,1), LU_echelon.upper(4,1));   ASSERT_EQ(LU.upper(4,2), LU_echelon.upper(4,2));     ASSERT_EQ(LU.upper(4,3), LU_echelon.upper(4,3));   ASSERT_EQ(LU.upper(4,4), LU_echelon.upper(4,4));
}

TEST_F(MatrixLUFactorizationTests, LUFactorization_5x5_Tridiagonal_Strang_1_7_2)
{
    const auto data = std::vector<int>{1,   -1,     0,      0,      0,
                                       -1,   2,     -1,     0,      0,
                                       0,    -1,    2,      -1,     0,
                                       0,    0,     -1,     2,      -1,
                                       0,    0,     0,     -1,      2};

    const auto mat = Matrix<int>(data, 5, 5);

    const auto LU = factorizeLU(mat);

    ASSERT_TRUE(LU.permutation == std::nullopt);

    const long double epsilon = 1e-9;

    ASSERT_EQ(LU.lower.rows(), 5); ASSERT_EQ(LU.lower.cols(), 5);

    ASSERT_NEAR(LU.lower(0,0), 1, epsilon);     ASSERT_NEAR(LU.lower(0,1), 0, epsilon);     ASSERT_NEAR(LU.lower(0,2), 0, epsilon);         ASSERT_NEAR(LU.lower(0,3), 0, epsilon);     ASSERT_NEAR(LU.lower(0,4), 0, epsilon);
    ASSERT_NEAR(LU.lower(1,0), -1, epsilon);    ASSERT_NEAR(LU.lower(1,1), 1, epsilon);     ASSERT_NEAR(LU.lower(1,2), 0, epsilon);         ASSERT_NEAR(LU.lower(1,3), 0, epsilon);     ASSERT_NEAR(LU.lower(1,4), 0, epsilon);
    ASSERT_NEAR(LU.lower(2,0), 0, epsilon);     ASSERT_NEAR(LU.lower(2,1), -1, epsilon);    ASSERT_NEAR(LU.lower(2,2), 1, epsilon);         ASSERT_NEAR(LU.lower(2,3), 0, epsilon);     ASSERT_NEAR(LU.lower(2,4), 0, epsilon);
    ASSERT_NEAR(LU.lower(3,0), 0, epsilon);     ASSERT_NEAR(LU.lower(3,1), 0, epsilon);     ASSERT_NEAR(LU.lower(3,2), -1, epsilon);        ASSERT_NEAR(LU.lower(3,3), 1, epsilon);     ASSERT_NEAR(LU.lower(3,4), 0, epsilon);
    ASSERT_NEAR(LU.lower(4,0), 0, epsilon);     ASSERT_NEAR(LU.lower(4,1), 0, epsilon);     ASSERT_NEAR(LU.lower(4,2), 0, epsilon);         ASSERT_NEAR(LU.lower(4,3), -1, epsilon);    ASSERT_NEAR(LU.lower(4,4), 1, epsilon);

    ASSERT_EQ(LU.upper.rows(), 5); ASSERT_EQ(LU.upper.cols(), 5);
    ASSERT_NEAR(LU.upper(0,0), 1, epsilon);  ASSERT_NEAR(LU.upper(0,1), -1, epsilon);       ASSERT_NEAR(LU.upper(0,2), 0, epsilon);     ASSERT_NEAR(LU.upper(0,3), 0, epsilon);         ASSERT_NEAR(LU.upper(0,4), 0, epsilon);
    ASSERT_NEAR(LU.upper(1,0), 0, epsilon);  ASSERT_NEAR(LU.upper(1,1), 1, epsilon);        ASSERT_NEAR(LU.upper(1,2), -1, epsilon);    ASSERT_NEAR(LU.upper(1,3), 0, epsilon);         ASSERT_NEAR(LU.upper(1,4), 0, epsilon);
    ASSERT_NEAR(LU.upper(2,0), 0, epsilon);  ASSERT_NEAR(LU.upper(2,1), 0, epsilon);        ASSERT_NEAR(LU.upper(2,2), 1, epsilon);     ASSERT_NEAR(LU.upper(2,3), -1, epsilon);        ASSERT_NEAR(LU.upper(2,4), 0, epsilon);
    ASSERT_NEAR(LU.upper(3,0), 0, epsilon);  ASSERT_NEAR(LU.upper(3,1), 0, epsilon);        ASSERT_NEAR(LU.upper(3,2), 0, epsilon);     ASSERT_NEAR(LU.upper(3,3), 1, epsilon);         ASSERT_NEAR(LU.upper(3,4), -1, epsilon);
    ASSERT_NEAR(LU.upper(4,0), 0, epsilon);  ASSERT_NEAR(LU.upper(4,1), 0, epsilon);        ASSERT_NEAR(LU.upper(4,2), 0, epsilon);     ASSERT_NEAR(LU.upper(4,3), 0, epsilon);         ASSERT_NEAR(LU.upper(4,4), 1, epsilon);


    // L*U should reconstruct the original matrix.
    const auto result = LU.lower * LU.upper;
    ASSERT_NEAR(result(0,0), mat(0,0), epsilon); ASSERT_NEAR(result(0,1), mat(0,1), epsilon); ASSERT_NEAR(result(0,2), mat(0,2), epsilon); ASSERT_NEAR(result(0,3), mat(0,3), epsilon); ASSERT_NEAR(result(0,4), mat(0,4), epsilon);
    ASSERT_NEAR(result(1,0), mat(1,0), epsilon); ASSERT_NEAR(result(1,1), mat(1,1), epsilon); ASSERT_NEAR(result(1,2), mat(1,2), epsilon); ASSERT_NEAR(result(1,3), mat(1,3), epsilon); ASSERT_NEAR(result(1,4), mat(1,4), epsilon);
    ASSERT_NEAR(result(2,0), mat(2,0), epsilon); ASSERT_NEAR(result(2,1), mat(2,1), epsilon); ASSERT_NEAR(result(2,2), mat(2,2), epsilon); ASSERT_NEAR(result(2,3), mat(2,3), epsilon); ASSERT_NEAR(result(2,4), mat(2,4), epsilon);
    ASSERT_NEAR(result(3,0), mat(3,0), epsilon); ASSERT_NEAR(result(3,1), mat(3,1), epsilon); ASSERT_NEAR(result(3,2), mat(3,2), epsilon); ASSERT_NEAR(result(3,3), mat(3,3), epsilon); ASSERT_NEAR(result(3,4), mat(3,4), epsilon);
    ASSERT_NEAR(result(4,0), mat(4,0), epsilon); ASSERT_NEAR(result(4,1), mat(4,1), epsilon); ASSERT_NEAR(result(4,2), mat(4,2), epsilon); ASSERT_NEAR(result(4,3), mat(4,3), epsilon); ASSERT_NEAR(result(4,4), mat(4,4), epsilon);

    ASSERT_NEAR(determinant(mat), 1, 1e-9);

    // Test LU_echelon is outputting the same result (since this is non-singular matrix)
    const auto LU_echelon = factorizeLU_echelon(mat);
    ASSERT_EQ(LU_echelon.upper.rows(), 5); ASSERT_EQ(LU_echelon.upper.cols(), 5);

    ASSERT_EQ(LU.lower(0,0), LU_echelon.lower(0,0));   ASSERT_EQ(LU.lower(0,1), LU_echelon.lower(0,1));   ASSERT_EQ(LU.lower(0,2), LU_echelon.lower(0,2));     ASSERT_EQ(LU.lower(0,3), LU_echelon.lower(0,3));   ASSERT_EQ(LU.lower(0,4), LU_echelon.lower(0,4));
    ASSERT_EQ(LU.lower(1,0), LU_echelon.lower(1,0));   ASSERT_EQ(LU.lower(1,1), LU_echelon.lower(1,1));   ASSERT_EQ(LU.lower(1,2),  LU_echelon.lower(1,2));    ASSERT_EQ(LU.lower(1,3), LU_echelon.lower(1,3));   ASSERT_EQ(LU.lower(1,4), LU_echelon.lower(1,4));
    ASSERT_EQ(LU.lower(2,0), LU_echelon.lower(2,0));   ASSERT_EQ(LU.lower(2,1), LU_echelon.lower(2,1));   ASSERT_EQ(LU.lower(2,2), LU_echelon.lower(2,2));     ASSERT_EQ(LU.lower(2,3), LU_echelon.lower(2,3));   ASSERT_EQ(LU.lower(2,4), LU_echelon.lower(2,4));
    ASSERT_EQ(LU.lower(3,0), LU_echelon.lower(3,0));   ASSERT_EQ(LU.lower(3,1), LU_echelon.lower(3,1));   ASSERT_EQ(LU.lower(3,2), LU_echelon.lower(3,2));     ASSERT_EQ(LU.lower(3,3), LU_echelon.lower(3,3));   ASSERT_EQ(LU.lower(3,4), LU_echelon.lower(3,4));
    ASSERT_EQ(LU.lower(4,0), LU_echelon.lower(4,0));   ASSERT_EQ(LU.lower(4,1), LU_echelon.lower(4,1));   ASSERT_EQ(LU.lower(4,2), LU_echelon.lower(4,2));     ASSERT_EQ(LU.lower(4,3), LU_echelon.lower(4,3));   ASSERT_EQ(LU.lower(4,4), LU_echelon.lower(4,4));

    ASSERT_EQ(LU.upper(0,0), LU_echelon.upper(0,0));   ASSERT_EQ(LU.upper(0,1), LU_echelon.upper(0,1));   ASSERT_EQ(LU.upper(0,2), LU_echelon.upper(0,2));     ASSERT_EQ(LU.upper(0,3), LU_echelon.upper(0,3));   ASSERT_EQ(LU.upper(0,4), LU_echelon.upper(0,4));
    ASSERT_EQ(LU.upper(1,0), LU_echelon.upper(1,0));   ASSERT_EQ(LU.upper(1,1), LU_echelon.upper(1,1));   ASSERT_EQ(LU.upper(1,2),  LU_echelon.upper(1,2));    ASSERT_EQ(LU.upper(1,3), LU_echelon.upper(1,3));   ASSERT_EQ(LU.upper(1,4), LU_echelon.upper(1,4));
    ASSERT_EQ(LU.upper(2,0), LU_echelon.upper(2,0));   ASSERT_EQ(LU.upper(2,1), LU_echelon.upper(2,1));   ASSERT_EQ(LU.upper(2,2), LU_echelon.upper(2,2));     ASSERT_EQ(LU.upper(2,3), LU_echelon.upper(2,3));   ASSERT_EQ(LU.upper(2,4), LU_echelon.upper(2,4));
    ASSERT_EQ(LU.upper(3,0), LU_echelon.upper(3,0));   ASSERT_EQ(LU.upper(3,1), LU_echelon.upper(3,1));   ASSERT_EQ(LU.upper(3,2), LU_echelon.upper(3,2));     ASSERT_EQ(LU.upper(3,3), LU_echelon.upper(3,3));   ASSERT_EQ(LU.upper(3,4), LU_echelon.upper(3,4));
    ASSERT_EQ(LU.upper(4,0), LU_echelon.upper(4,0));   ASSERT_EQ(LU.upper(4,1), LU_echelon.upper(4,1));   ASSERT_EQ(LU.upper(4,2), LU_echelon.upper(4,2));     ASSERT_EQ(LU.upper(4,3), LU_echelon.upper(4,3));   ASSERT_EQ(LU.upper(4,4), LU_echelon.upper(4,4));
}