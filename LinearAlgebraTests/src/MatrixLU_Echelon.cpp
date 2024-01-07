//
// Created by dorian on 06.01.2024
// stoicadorian@gmail.com
//
#include "gtest/gtest.h"
#include "Matrix.hpp"

using namespace LinearAlgebra::Matrix;
using namespace LinearAlgebra::Vector;

class MatrixLU_EchelonTests : public ::testing::Test
{

protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};


TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Chapter_2_2_Example)
{
    const auto data = std::vector<int>{1,3,3,2,
                                       2,6,9,7,
                                       -1,-3,3,4};

    const auto mat = Matrix<int>(data, 3, 4);

    const auto LU_echelon = mat.factorizeLU_echelon();

    ASSERT_TRUE(LU_echelon.permutation == std::nullopt);

    ASSERT_EQ(LU_echelon.lower.rows(), mat.rows()); ASSERT_EQ(LU_echelon.lower.cols(), mat.rows());
    ASSERT_EQ(LU_echelon.lower(0,0), 1);   ASSERT_EQ(LU_echelon.lower(0,1), 0);   ASSERT_EQ(LU_echelon.lower(0,2), 0);
    ASSERT_EQ(LU_echelon.lower(1,0), 2);   ASSERT_EQ(LU_echelon.lower(1,1), 1);   ASSERT_EQ(LU_echelon.lower(1,2), 0);
    ASSERT_EQ(LU_echelon.lower(2,0), -1);   ASSERT_EQ(LU_echelon.lower(2,1), 2);  ASSERT_EQ(LU_echelon.lower(2,2), 1);


    ASSERT_EQ(LU_echelon.upper.rows(), mat.rows()); ASSERT_EQ(LU_echelon.upper.cols(), mat.cols());
    ASSERT_EQ(LU_echelon.upper(0,0), 1);   ASSERT_EQ(LU_echelon.upper(0,1), 3);   ASSERT_EQ(LU_echelon.upper(0,2), 3);   ASSERT_EQ(LU_echelon.upper(0,3), 2);
    ASSERT_EQ(LU_echelon.upper(1,0), 0);   ASSERT_EQ(LU_echelon.upper(1,1), 0);   ASSERT_EQ(LU_echelon.upper(1,2), 3);   ASSERT_EQ(LU_echelon.upper(1,3), 3);
    ASSERT_EQ(LU_echelon.upper(2,0), 0);   ASSERT_EQ(LU_echelon.upper(2,1), 0);   ASSERT_EQ(LU_echelon.upper(2,2), 0);   ASSERT_EQ(LU_echelon.upper(2,3), 0);

    // Ensure L*U reconstructs the initial matrix
    const auto result = LU_echelon.lower.multiply(LU_echelon.upper);

    const double epsilon = 1e-9;
    ASSERT_NEAR(result(0,0), mat(0,0), epsilon); ASSERT_NEAR(result(0,1), mat(0,1), epsilon); ASSERT_NEAR(result(0,2), mat(0,2), epsilon);  ASSERT_NEAR(result(0,3), mat(0,3), epsilon);
    ASSERT_NEAR(result(1,0), mat(1,0), epsilon); ASSERT_NEAR(result(1,1), mat(1,1), epsilon); ASSERT_NEAR(result(1,2), mat(1,2), epsilon);  ASSERT_NEAR(result(1,3), mat(1,3), epsilon);
    ASSERT_NEAR(result(2,0), mat(2,0), epsilon); ASSERT_NEAR(result(2,1), mat(2,1), epsilon); ASSERT_NEAR(result(2,2), mat(2,2), epsilon);  ASSERT_NEAR(result(2,3), mat(2,3), epsilon);
}


TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Chapter_2_2_Another_Example)
{
    const auto data = std::vector<int>{1,2,3,5,
                                       2,4,8,12,
                                       3,6,7,13};

    const auto mat = Matrix<int>(data, 3, 4);

    const auto LU_Result = mat.factorizeLU_echelon();

    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 4);
    ASSERT_EQ(LU_Result.upper(0,0), 1);   ASSERT_EQ(LU_Result.upper(0,1), 2);   ASSERT_EQ(LU_Result.upper(0,2), 3);   ASSERT_EQ(LU_Result.upper(0,3), 5);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), 0);   ASSERT_EQ(LU_Result.upper(1,2), 2);   ASSERT_EQ(LU_Result.upper(1,3), 2);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), 0);   ASSERT_EQ(LU_Result.upper(2,3), 0);
}

TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Chapter_2_2_Problem_3)
{
    const auto data = std::vector<int>{0,1,0,3,
                                       0,2,0,6};

    const auto mat = Matrix<int>(data, 2, 4);
    const auto LU_Result = mat.factorizeLU_echelon();

    ASSERT_EQ(LU_Result.lower(0,0), 1);     ASSERT_EQ(LU_Result.lower(0,1), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 2);     ASSERT_EQ(LU_Result.lower(1,1), 1);

    ASSERT_EQ(LU_Result.upper(0,0), 0);     ASSERT_EQ(LU_Result.upper(0,1), 1);     ASSERT_EQ(LU_Result.upper(0,2), 0);     ASSERT_EQ(LU_Result.upper(0,3), 3);
    ASSERT_EQ(LU_Result.upper(1,0), 0);     ASSERT_EQ(LU_Result.upper(1,1), 0);     ASSERT_EQ(LU_Result.upper(1,2), 0);     ASSERT_EQ(LU_Result.upper(1,3), 0);
}