//
// Created by dorian on 06.01.2024
// stoicadorian@gmail.com
//
#include "gtest/gtest.h"
#include "Matrix.hpp"
#include "MatrixHelpers.hpp"

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

    const auto LU_echelon = factorizeLU_echelon(mat);

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

    const auto LU_Result = factorizeLU_echelon(mat);

    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 4);
    ASSERT_EQ(LU_Result.upper(0,0), 1);   ASSERT_EQ(LU_Result.upper(0,1), 2);   ASSERT_EQ(LU_Result.upper(0,2), 3);   ASSERT_EQ(LU_Result.upper(0,3), 5);
    ASSERT_EQ(LU_Result.upper(1,0), 0);   ASSERT_EQ(LU_Result.upper(1,1), 0);   ASSERT_EQ(LU_Result.upper(1,2), 2);   ASSERT_EQ(LU_Result.upper(1,3), 2);
    ASSERT_EQ(LU_Result.upper(2,0), 0);   ASSERT_EQ(LU_Result.upper(2,1), 0);   ASSERT_EQ(LU_Result.upper(2,2), 0);   ASSERT_EQ(LU_Result.upper(2,3), 0);
}

TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Chapter_2_2_Problem_2_a)
{
    const auto data = std::vector<int>{1,2,0,1,
                                       0,1,1,0,
                                       1,2,0,1};

    const auto mat = Matrix<int>(data, 3, 4);

    const auto LU_echelon = factorizeLU_echelon(mat);

    ASSERT_EQ(LU_echelon.upper.rows(), mat.rows());      ASSERT_EQ(LU_echelon.upper.cols(), mat.cols());

    ASSERT_EQ(LU_echelon.upper(0,0), 1);     ASSERT_EQ(LU_echelon.upper(0,1), 2);     ASSERT_EQ(LU_echelon.upper(0,2), 0);     ASSERT_EQ(LU_echelon.upper(0,3), 1);
    ASSERT_EQ(LU_echelon.upper(1,0), 0);     ASSERT_EQ(LU_echelon.upper(1,1), 1);     ASSERT_EQ(LU_echelon.upper(1,2), 1);     ASSERT_EQ(LU_echelon.upper(1,3), 0);
    ASSERT_EQ(LU_echelon.upper(2,0), 0);     ASSERT_EQ(LU_echelon.upper(2,1), 0);     ASSERT_EQ(LU_echelon.upper(2,2), 0);     ASSERT_EQ(LU_echelon.upper(2,3), 0);
}

TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Strang_Chapter_2_2_Problem_2_b)
{
    const auto data = std::vector<int>{1,2,3,
                                       4,5,6,
                                       7,8,9};

    const auto mat = Matrix<int>(data, 3, 3);

    const auto LU_echelon = factorizeLU_echelon(mat);

    ASSERT_EQ(LU_echelon.upper.rows(), mat.rows());      ASSERT_EQ(LU_echelon.upper.cols(), mat.cols());

    ASSERT_EQ(LU_echelon.upper(0,0), 1);     ASSERT_EQ(LU_echelon.upper(0,1), 2);     ASSERT_EQ(LU_echelon.upper(0,2), 3);
    ASSERT_EQ(LU_echelon.upper(1,0), 0);     ASSERT_EQ(LU_echelon.upper(1,1), -3);     ASSERT_EQ(LU_echelon.upper(1,2), -6);
    ASSERT_EQ(LU_echelon.upper(2,0), 0);     ASSERT_EQ(LU_echelon.upper(2,1), 0);     ASSERT_EQ(LU_echelon.upper(2,2), 0);
}

TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Chapter_2_2_Problem_3)
{
    const auto data = std::vector<int>{0,1,0,3,
                                       0,2,0,6};

    const auto mat = Matrix<int>(data, 2, 4);
    const auto LU_Result = factorizeLU_echelon(mat);

    ASSERT_EQ(LU_Result.lower(0,0), 1);     ASSERT_EQ(LU_Result.lower(0,1), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 2);     ASSERT_EQ(LU_Result.lower(1,1), 1);

    ASSERT_EQ(LU_Result.upper(0,0), 0);     ASSERT_EQ(LU_Result.upper(0,1), 1);     ASSERT_EQ(LU_Result.upper(0,2), 0);     ASSERT_EQ(LU_Result.upper(0,3), 3);
    ASSERT_EQ(LU_Result.upper(1,0), 0);     ASSERT_EQ(LU_Result.upper(1,1), 0);     ASSERT_EQ(LU_Result.upper(1,2), 0);     ASSERT_EQ(LU_Result.upper(1,3), 0);
}

TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Chapter_2_2_Problem_4)
{
    const auto data = std::vector<int>{0,0,
                                       1,2,
                                       0,0,
                                       3,6};

    const auto mat = Matrix<int>(data, 4, 2);
    const auto LU_Result = factorizeLU_echelon(mat);

    const auto permutation = LU_Result.permutation.value();
    ASSERT_EQ(permutation(0,0),0); ASSERT_EQ(permutation(0,1),1); ASSERT_EQ(permutation(0,2),0); ASSERT_EQ(permutation(0,3),0);
    ASSERT_EQ(permutation(1,0),1); ASSERT_EQ(permutation(1,1),0); ASSERT_EQ(permutation(1,2),0); ASSERT_EQ(permutation(1,3),0);
    ASSERT_EQ(permutation(2,0),0); ASSERT_EQ(permutation(2,1),0); ASSERT_EQ(permutation(2,2),1); ASSERT_EQ(permutation(2,3),0);
    ASSERT_EQ(permutation(3,0),0); ASSERT_EQ(permutation(3,1),0); ASSERT_EQ(permutation(3,2),0); ASSERT_EQ(permutation(3,3),1);


    ASSERT_EQ(LU_Result.lower(0,0),1); ASSERT_EQ(LU_Result.lower(0,1),0); ASSERT_EQ(LU_Result.lower(0,2),0); ASSERT_EQ(LU_Result.lower(0,3),0);
    ASSERT_EQ(LU_Result.lower(1,0),0); ASSERT_EQ(LU_Result.lower(1,1),1); ASSERT_EQ(LU_Result.lower(1,2),0); ASSERT_EQ(LU_Result.lower(1,3),0);
    ASSERT_EQ(LU_Result.lower(2,0),0); ASSERT_EQ(LU_Result.lower(2,1),0); ASSERT_EQ(LU_Result.lower(2,2),1); ASSERT_EQ(LU_Result.lower(2,3),0);
    ASSERT_EQ(LU_Result.lower(3,0),3); ASSERT_EQ(LU_Result.lower(3,1),0); ASSERT_EQ(LU_Result.lower(3,2),0); ASSERT_EQ(LU_Result.lower(3,3),1);

    ASSERT_EQ(LU_Result.upper(0,0), 1);     ASSERT_EQ(LU_Result.upper(0,1), 2);
    ASSERT_EQ(LU_Result.upper(1,0), 0);     ASSERT_EQ(LU_Result.upper(1,1), 0);
    ASSERT_EQ(LU_Result.upper(2,0), 0);     ASSERT_EQ(LU_Result.upper(2,1), 0);
    ASSERT_EQ(LU_Result.upper(3,0), 0);     ASSERT_EQ(LU_Result.upper(3,1), 0);
}

TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Chapter_2_2_Problem_5a)
{
    const auto data = std::vector<int>{1,2,2,
                                       2,4,5};

    const auto mat = Matrix<int>(data, 2, 3);
    const auto LU_Result = factorizeLU_echelon(mat);

    ASSERT_EQ(LU_Result.lower(0,0), 1);     ASSERT_EQ(LU_Result.lower(0,1), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 2);     ASSERT_EQ(LU_Result.lower(1,1), 1);

    ASSERT_EQ(LU_Result.upper(0,0), 1);     ASSERT_EQ(LU_Result.upper(0,1), 2);     ASSERT_EQ(LU_Result.upper(0,2), 2);
    ASSERT_EQ(LU_Result.upper(1,0), 0);     ASSERT_EQ(LU_Result.upper(1,1), 0);     ASSERT_EQ(LU_Result.upper(1,2), 1);
}

TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Chapter_2_2_Problem_5b)
{
    const auto data = std::vector<int>{1,2,2,
                                       2,4,4};

    const auto mat = Matrix<int>(data, 2, 3);
    const auto LU_Result = factorizeLU_echelon(mat);

    ASSERT_EQ(LU_Result.lower(0,0), 1);     ASSERT_EQ(LU_Result.lower(0,1), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 2);     ASSERT_EQ(LU_Result.lower(1,1), 1);

    ASSERT_EQ(LU_Result.upper(0,0), 1);     ASSERT_EQ(LU_Result.upper(0,1), 2);     ASSERT_EQ(LU_Result.upper(0,2), 2);
    ASSERT_EQ(LU_Result.upper(1,0), 0);     ASSERT_EQ(LU_Result.upper(1,1), 0);     ASSERT_EQ(LU_Result.upper(1,2), 0);
}

TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Chapter_2_2_Problem_6)
{
    const auto data = std::vector<int>{1,0,
                                       0,1,
                                       2,3};

    const auto mat = Matrix<int>(data, 3, 2);
    const auto LU_Result = factorizeLU_echelon(mat);

    ASSERT_EQ(LU_Result.lower(0,0), 1);     ASSERT_EQ(LU_Result.lower(0,1), 0);     ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 0);     ASSERT_EQ(LU_Result.lower(1,1), 1);     ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 2);     ASSERT_EQ(LU_Result.lower(2,1), 3);     ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper(0,0), 1);     ASSERT_EQ(LU_Result.upper(0,1), 0);
    ASSERT_EQ(LU_Result.upper(1,0), 0);     ASSERT_EQ(LU_Result.upper(1,1), 1);
    ASSERT_EQ(LU_Result.upper(2,0), 0);     ASSERT_EQ(LU_Result.upper(2,1), 0);
}

TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Chapter_2_2_Problem_7)
{
    const auto data = std::vector<int>{1,1,2,
                                       2,3,-1,
                                       3,4,1};

    const auto mat = Matrix<int>(data, 3, 3);
    const auto LU_Result = factorizeLU_echelon(mat);

    ASSERT_EQ(LU_Result.lower(0,0), 1);     ASSERT_EQ(LU_Result.lower(0,1), 0);     ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 2);     ASSERT_EQ(LU_Result.lower(1,1), 1);     ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 3);     ASSERT_EQ(LU_Result.lower(2,1), 1);     ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper(0,0), 1);     ASSERT_EQ(LU_Result.upper(0,1), 1);     ASSERT_EQ(LU_Result.upper(0,2), 2);
    ASSERT_EQ(LU_Result.upper(1,0), 0);     ASSERT_EQ(LU_Result.upper(1,1), 1);     ASSERT_EQ(LU_Result.upper(1,2), -5);
    ASSERT_EQ(LU_Result.upper(2,0), 0);     ASSERT_EQ(LU_Result.upper(2,1), 0);     ASSERT_EQ(LU_Result.upper(2,2), 0);
}

TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Chapter_2_2_Problem_8)
{
    const auto data = std::vector<int>{1,2,0,3,
                                       2,4,0,7};

    const auto mat = Matrix<int>(data, 2, 4);
    const auto LU_Result = factorizeLU_echelon(mat);

    ASSERT_EQ(LU_Result.lower(0,0), 1);     ASSERT_EQ(LU_Result.lower(0,1), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 2);     ASSERT_EQ(LU_Result.lower(1,1), 1);

    ASSERT_EQ(LU_Result.upper(0,0), 1);     ASSERT_EQ(LU_Result.upper(0,1), 2);     ASSERT_EQ(LU_Result.upper(0,2), 0);     ASSERT_EQ(LU_Result.upper(0,3), 3);
    ASSERT_EQ(LU_Result.upper(1,0), 0);     ASSERT_EQ(LU_Result.upper(1,1), 0);     ASSERT_EQ(LU_Result.upper(1,2), 0);     ASSERT_EQ(LU_Result.upper(1,3), 1);
}

TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Chapter_2_2_Problem_9)
{
    const auto data = std::vector<int>{1,2,3,4,
                                       0,0,1,2,
                                       0,0,0,0};

    const auto mat = Matrix<int>(data, 3, 4);
    const auto LU_Result = factorizeLU_echelon(mat);

    ASSERT_EQ(LU_Result.lower(0,0), 1);     ASSERT_EQ(LU_Result.lower(0,1), 0);     ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 0);     ASSERT_EQ(LU_Result.lower(1,1), 1);     ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 0);     ASSERT_EQ(LU_Result.lower(2,1), 0);     ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper(0,0), 1);     ASSERT_EQ(LU_Result.upper(0,1), 2);     ASSERT_EQ(LU_Result.upper(0,2), 3);     ASSERT_EQ(LU_Result.upper(0,3), 4);
    ASSERT_EQ(LU_Result.upper(1,0), 0);     ASSERT_EQ(LU_Result.upper(1,1), 0);     ASSERT_EQ(LU_Result.upper(1,2), 1);     ASSERT_EQ(LU_Result.upper(1,3), 2);
    ASSERT_EQ(LU_Result.upper(2,0), 0);     ASSERT_EQ(LU_Result.upper(2,1), 0);     ASSERT_EQ(LU_Result.upper(2,2), 0);     ASSERT_EQ(LU_Result.upper(2,3), 0);
}

TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Chapter_2_2_Problem_13a)
{
    const auto data = std::vector<int>{1,1,1,1,
                                       1,1,1,1,
                                       1,1,1,1};

    const auto mat = Matrix<int>(data, 3, 4);
    const auto LU_Result = factorizeLU_echelon(mat);

    ASSERT_EQ(LU_Result.lower(0,0), 1);     ASSERT_EQ(LU_Result.lower(0,1), 0);     ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 1);     ASSERT_EQ(LU_Result.lower(1,1), 1);     ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 1);     ASSERT_EQ(LU_Result.lower(2,1), 0);     ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper(0,0), 1);     ASSERT_EQ(LU_Result.upper(0,1), 1);     ASSERT_EQ(LU_Result.upper(0,2), 1);     ASSERT_EQ(LU_Result.upper(0,3), 1);
    ASSERT_EQ(LU_Result.upper(1,0), 0);     ASSERT_EQ(LU_Result.upper(1,1), 0);     ASSERT_EQ(LU_Result.upper(1,2), 0);     ASSERT_EQ(LU_Result.upper(1,3), 0);
    ASSERT_EQ(LU_Result.upper(2,0), 0);     ASSERT_EQ(LU_Result.upper(2,1), 0);     ASSERT_EQ(LU_Result.upper(2,2), 0);     ASSERT_EQ(LU_Result.upper(2,3), 0);
}

TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Chapter_2_2_Problem_13b)
{
    //a_ij = (-1)^(i+j)
    const auto data = std::vector<int>{1,-1,1,-1,
                                       -1,1,-1,1,
                                       1,-1,1,-1,
                                       -1,1,-1,1};

    const auto mat = Matrix<int>(data, 4, 4);
    const auto LU_Result = factorizeLU_echelon(mat);

    ASSERT_EQ(LU_Result.lower(0,0), 1);     ASSERT_EQ(LU_Result.lower(0,1), 0);     ASSERT_EQ(LU_Result.lower(0,2), 0);     ASSERT_EQ(LU_Result.lower(0,3), 0);
    ASSERT_EQ(LU_Result.lower(1,0), -1);     ASSERT_EQ(LU_Result.lower(1,1), 1);     ASSERT_EQ(LU_Result.lower(1,2), 0);     ASSERT_EQ(LU_Result.lower(1,3), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 1);     ASSERT_EQ(LU_Result.lower(2,1), 0);     ASSERT_EQ(LU_Result.lower(2,2), 1);     ASSERT_EQ(LU_Result.lower(2,3), 0);
    ASSERT_EQ(LU_Result.lower(3,0), -1);     ASSERT_EQ(LU_Result.lower(3,1), 0);     ASSERT_EQ(LU_Result.lower(3,2), 0);     ASSERT_EQ(LU_Result.lower(3,3), 1);

    ASSERT_EQ(LU_Result.upper(0,0), 1);     ASSERT_EQ(LU_Result.upper(0,1), -1);     ASSERT_EQ(LU_Result.upper(0,2), 1);     ASSERT_EQ(LU_Result.upper(0,3), -1);
    ASSERT_EQ(LU_Result.upper(1,0), 0);     ASSERT_EQ(LU_Result.upper(1,1), 0);     ASSERT_EQ(LU_Result.upper(1,2), 0);     ASSERT_EQ(LU_Result.upper(1,3), 0);
    ASSERT_EQ(LU_Result.upper(2,0), 0);     ASSERT_EQ(LU_Result.upper(2,1), 0);     ASSERT_EQ(LU_Result.upper(2,2), 0);     ASSERT_EQ(LU_Result.upper(2,3), 0);
    ASSERT_EQ(LU_Result.upper(3,0), 0);     ASSERT_EQ(LU_Result.upper(3,1), 0);     ASSERT_EQ(LU_Result.upper(3,2), 0);     ASSERT_EQ(LU_Result.upper(3,3), 0);
}

TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Chapter_2_2_Problem_13c)
{
    //a_ij = (-1)^(j)
    const auto data = std::vector<int>{-1,1,-1,1,
                                       -1,1,-1,1,
                                       -1,1,-1,1};

    const auto mat = Matrix<int>(data, 3, 4);
    const auto LU_Result = factorizeLU_echelon(mat);

    ASSERT_EQ(LU_Result.lower(0,0), 1);     ASSERT_EQ(LU_Result.lower(0,1), 0);     ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 1);     ASSERT_EQ(LU_Result.lower(1,1), 1);     ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 1);     ASSERT_EQ(LU_Result.lower(2,1), 0);     ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper(0,0), -1);     ASSERT_EQ(LU_Result.upper(0,1), 1);     ASSERT_EQ(LU_Result.upper(0,2), -1);     ASSERT_EQ(LU_Result.upper(0,3), 1);
    ASSERT_EQ(LU_Result.upper(1,0), 0);     ASSERT_EQ(LU_Result.upper(1,1), 0);     ASSERT_EQ(LU_Result.upper(1,2), 0);     ASSERT_EQ(LU_Result.upper(1,3), 0);
    ASSERT_EQ(LU_Result.upper(2,0), 0);     ASSERT_EQ(LU_Result.upper(2,1), 0);     ASSERT_EQ(LU_Result.upper(2,2), 0);     ASSERT_EQ(LU_Result.upper(2,3), 0);
}

TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Chapter_2_2_Problem_13d)
{
    //a_ij = (-1)^(i*j)
    const auto data = std::vector<int>{-1,1,-1,1,
                                       1,1,1,1,
                                       -1,1,-1,1,
                                       1,1,1,1};

    const auto mat = Matrix<int>(data, 4, 4);
    const auto LU_Result = factorizeLU_echelon(mat);

    ASSERT_EQ(LU_Result.lower(0,0), 1);     ASSERT_EQ(LU_Result.lower(0,1), 0);     ASSERT_EQ(LU_Result.lower(0,2), 0);     ASSERT_EQ(LU_Result.lower(0,3), 0);
    ASSERT_EQ(LU_Result.lower(1,0), -1);     ASSERT_EQ(LU_Result.lower(1,1), 1);     ASSERT_EQ(LU_Result.lower(1,2), 0);     ASSERT_EQ(LU_Result.lower(1,3), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 1);     ASSERT_EQ(LU_Result.lower(2,1), 0);     ASSERT_EQ(LU_Result.lower(2,2), 1);     ASSERT_EQ(LU_Result.lower(2,3), 0);
    ASSERT_EQ(LU_Result.lower(3,0), -1);     ASSERT_EQ(LU_Result.lower(3,1), 1);     ASSERT_EQ(LU_Result.lower(3,2), 0);     ASSERT_EQ(LU_Result.lower(3,3), 1);

    ASSERT_EQ(LU_Result.upper(0,0), -1);     ASSERT_EQ(LU_Result.upper(0,1), 1);     ASSERT_EQ(LU_Result.upper(0,2), -1);     ASSERT_EQ(LU_Result.upper(0,3), 1);
    ASSERT_EQ(LU_Result.upper(1,0), 0);     ASSERT_EQ(LU_Result.upper(1,1), 2);     ASSERT_EQ(LU_Result.upper(1,2), 0);     ASSERT_EQ(LU_Result.upper(1,3), 2);
    ASSERT_EQ(LU_Result.upper(2,0), 0);     ASSERT_EQ(LU_Result.upper(2,1), 0);     ASSERT_EQ(LU_Result.upper(2,2), 0);     ASSERT_EQ(LU_Result.upper(2,3), 0);
    ASSERT_EQ(LU_Result.upper(3,0), 0);     ASSERT_EQ(LU_Result.upper(3,1), 0);     ASSERT_EQ(LU_Result.upper(3,2), 0);     ASSERT_EQ(LU_Result.upper(3,3), 0);

    const auto LU = LU_Result.lower.multiply(LU_Result.upper);

    ASSERT_EQ(LU(0,0), mat(0,0));     ASSERT_EQ(LU(0,1), mat(0,1));     ASSERT_EQ(LU(0,2), mat(0,2));     ASSERT_EQ(LU(0,3), mat(0,3));
    ASSERT_EQ(LU(1,0), mat(1,0));     ASSERT_EQ(LU(1,1), mat(1,1));     ASSERT_EQ(LU(1,2), mat(1,2));     ASSERT_EQ(LU(1,3), mat(1,3));
    ASSERT_EQ(LU(2,0), mat(2,0));     ASSERT_EQ(LU(2,1), mat(2,1));     ASSERT_EQ(LU(2,2), mat(2,2));     ASSERT_EQ(LU(2,3), mat(2,3));
    ASSERT_EQ(LU(3,0), mat(3,0));     ASSERT_EQ(LU(3,1), mat(3,1));     ASSERT_EQ(LU(3,2), mat(3,2));     ASSERT_EQ(LU(3,3), mat(3,3));
}


TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Chapter_2_2_Problem_14a_3x3)
{
    const auto data = std::vector<int>{0,0,0,
                                       0,0,3,
                                       2,4,6};

    const auto mat = Matrix<int>(data, 3, 3);
    const auto LU_Result = factorizeLU_echelon(mat);
    const auto permutation = LU_Result.permutation.value();

    ASSERT_EQ(permutation(0,0), 0);     ASSERT_EQ(permutation(0,1), 0);     ASSERT_EQ(permutation(0,2), 1);
    ASSERT_EQ(permutation(1,0), 0);    ASSERT_EQ(permutation(1,1), 1);     ASSERT_EQ(permutation(1,2), 0);
    ASSERT_EQ(permutation(2,0), 1);     ASSERT_EQ(permutation(2,1), 0);     ASSERT_EQ(permutation(2,2), 0);

    ASSERT_EQ(LU_Result.lower(0,0), 1);     ASSERT_EQ(LU_Result.lower(0,1), 0);     ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 0);    ASSERT_EQ(LU_Result.lower(1,1), 1);     ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 0);     ASSERT_EQ(LU_Result.lower(2,1), 0);     ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper(0,0), 2);     ASSERT_EQ(LU_Result.upper(0,1), 4);     ASSERT_EQ(LU_Result.upper(0,2), 6);
    ASSERT_EQ(LU_Result.upper(1,0), 0);     ASSERT_EQ(LU_Result.upper(1,1), 0);     ASSERT_EQ(LU_Result.upper(1,2), 3);
    ASSERT_EQ(LU_Result.upper(2,0), 0);     ASSERT_EQ(LU_Result.upper(2,1), 0);     ASSERT_EQ(LU_Result.upper(2,2), 0);
}

TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Chapter_2_2_Problem_14b_3x6)
{
    const auto data = std::vector<int>{0,0,0,0,0,0,
                                       0,0,3,0,0,3,
                                       2,4,6,2,4,6};

    const auto mat = Matrix<int>(data, 3, 6);
    const auto LU_Result = factorizeLU_echelon(mat);
    const auto permutation = LU_Result.permutation.value();

    ASSERT_EQ(permutation(0,0), 0);     ASSERT_EQ(permutation(0,1), 0);     ASSERT_EQ(permutation(0,2), 1);
    ASSERT_EQ(permutation(1,0), 0);    ASSERT_EQ(permutation(1,1), 1);     ASSERT_EQ(permutation(1,2), 0);
    ASSERT_EQ(permutation(2,0), 1);     ASSERT_EQ(permutation(2,1), 0);     ASSERT_EQ(permutation(2,2), 0);

    ASSERT_EQ(LU_Result.lower(0,0), 1);     ASSERT_EQ(LU_Result.lower(0,1), 0);     ASSERT_EQ(LU_Result.lower(0,2), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 0);    ASSERT_EQ(LU_Result.lower(1,1), 1);     ASSERT_EQ(LU_Result.lower(1,2), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 0);     ASSERT_EQ(LU_Result.lower(2,1), 0);     ASSERT_EQ(LU_Result.lower(2,2), 1);

    ASSERT_EQ(LU_Result.upper(0,0), 2);     ASSERT_EQ(LU_Result.upper(0,1), 4);     ASSERT_EQ(LU_Result.upper(0,2), 6);     ASSERT_EQ(LU_Result.upper(0,3), 2);     ASSERT_EQ(LU_Result.upper(0,4), 4);     ASSERT_EQ(LU_Result.upper(0,5), 6);
    ASSERT_EQ(LU_Result.upper(1,0), 0);     ASSERT_EQ(LU_Result.upper(1,1), 0);     ASSERT_EQ(LU_Result.upper(1,2), 3);     ASSERT_EQ(LU_Result.upper(1,3), 0);     ASSERT_EQ(LU_Result.upper(1,4), 0);     ASSERT_EQ(LU_Result.upper(1,5), 3);
    ASSERT_EQ(LU_Result.upper(2,0), 0);     ASSERT_EQ(LU_Result.upper(2,1), 0);     ASSERT_EQ(LU_Result.upper(2,2), 0);     ASSERT_EQ(LU_Result.upper(2,3), 0);     ASSERT_EQ(LU_Result.upper(2,4), 0);     ASSERT_EQ(LU_Result.upper(2,5), 0);
}

TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Chapter_2_2_Problem_14c_6x6_multiple_permutations)
{
    const auto data = std::vector<int>{0,0,0,0,0,0,
                                       0,0,3,0,0,3,
                                       2,4,6,2,4,6,
                                       0,0,0,0,0,0,
                                       0,0,3,0,0,0,
                                       2,4,6,0,0,0};

    const auto mat = Matrix<int>(data, 6, 6);
    const auto LU_Result = factorizeLU_echelon(mat);
    const auto permutation = LU_Result.permutation.value();

    ASSERT_EQ(permutation(0,0), 0);     ASSERT_EQ(permutation(0,1), 0);     ASSERT_EQ(permutation(0,2), 1);     ASSERT_EQ(permutation(0,3), 0);     ASSERT_EQ(permutation(0,4), 0);     ASSERT_EQ(permutation(0,5), 0);
    ASSERT_EQ(permutation(1,0), 0);     ASSERT_EQ(permutation(1,1), 1);     ASSERT_EQ(permutation(1,2), 0);     ASSERT_EQ(permutation(1,3), 0);     ASSERT_EQ(permutation(1,4), 0);     ASSERT_EQ(permutation(1,5), 0);
    ASSERT_EQ(permutation(2,0), 0);     ASSERT_EQ(permutation(2,1), 0);     ASSERT_EQ(permutation(2,2), 0);     ASSERT_EQ(permutation(2,3), 0);     ASSERT_EQ(permutation(2,4), 0);     ASSERT_EQ(permutation(2,5), 1);
    ASSERT_EQ(permutation(3,0), 0);     ASSERT_EQ(permutation(3,1), 0);     ASSERT_EQ(permutation(3,2), 0);     ASSERT_EQ(permutation(3,3), 0);     ASSERT_EQ(permutation(3,4), 1);     ASSERT_EQ(permutation(3,5), 0);
    ASSERT_EQ(permutation(4,0), 0);     ASSERT_EQ(permutation(4,1), 0);     ASSERT_EQ(permutation(4,2), 0);     ASSERT_EQ(permutation(4,3), 1);     ASSERT_EQ(permutation(4,4), 0);     ASSERT_EQ(permutation(4,5), 0);
    ASSERT_EQ(permutation(5,0), 1);     ASSERT_EQ(permutation(5,1), 0);     ASSERT_EQ(permutation(5,2), 0);     ASSERT_EQ(permutation(5,3), 0);     ASSERT_EQ(permutation(5,4), 0);     ASSERT_EQ(permutation(5,5), 0);

    ASSERT_EQ(LU_Result.lower(0,0), 1);     ASSERT_EQ(LU_Result.lower(0,1), 0);     ASSERT_EQ(LU_Result.lower(0,2), 0);     ASSERT_EQ(LU_Result.lower(0,3), 0);     ASSERT_EQ(LU_Result.lower(0,4), 0);     ASSERT_EQ(LU_Result.lower(0,5), 0);
    ASSERT_EQ(LU_Result.lower(1,0), 0);     ASSERT_EQ(LU_Result.lower(1,1), 1);     ASSERT_EQ(LU_Result.lower(1,2), 0);     ASSERT_EQ(LU_Result.lower(1,3), 0);     ASSERT_EQ(LU_Result.lower(1,4), 0);     ASSERT_EQ(LU_Result.lower(1,5), 0);
    ASSERT_EQ(LU_Result.lower(2,0), 1);     ASSERT_EQ(LU_Result.lower(2,1), 0);     ASSERT_EQ(LU_Result.lower(2,2), 1);     ASSERT_EQ(LU_Result.lower(2,3), 0);     ASSERT_EQ(LU_Result.lower(2,4), 0);     ASSERT_EQ(LU_Result.lower(2,5), 0);
    ASSERT_EQ(LU_Result.lower(3,0), 0);     ASSERT_EQ(LU_Result.lower(3,1), 1);     ASSERT_EQ(LU_Result.lower(3,2), 0);     ASSERT_EQ(LU_Result.lower(3,3), 1);     ASSERT_EQ(LU_Result.lower(3,4), 0);     ASSERT_EQ(LU_Result.lower(3,5), 0);
    ASSERT_EQ(LU_Result.lower(4,0), 0);     ASSERT_EQ(LU_Result.lower(4,1), 0);     ASSERT_EQ(LU_Result.lower(4,2), 0);     ASSERT_EQ(LU_Result.lower(4,3), 0);     ASSERT_EQ(LU_Result.lower(4,4), 1);     ASSERT_EQ(LU_Result.lower(4,5), 0);
    ASSERT_EQ(LU_Result.lower(5,0), 0);     ASSERT_EQ(LU_Result.lower(5,1), 0);     ASSERT_EQ(LU_Result.lower(5,2), 0);     ASSERT_EQ(LU_Result.lower(5,3), 0);     ASSERT_EQ(LU_Result.lower(5,4), 0);     ASSERT_EQ(LU_Result.lower(5,5), 1);

    ASSERT_EQ(LU_Result.upper(0,0), 2);     ASSERT_EQ(LU_Result.upper(0,1), 4);     ASSERT_EQ(LU_Result.upper(0,2), 6);     ASSERT_EQ(LU_Result.upper(0,3), 2);     ASSERT_EQ(LU_Result.upper(0,4), 4);     ASSERT_EQ(LU_Result.upper(0,5), 6);
    ASSERT_EQ(LU_Result.upper(1,0), 0);     ASSERT_EQ(LU_Result.upper(1,1), 0);     ASSERT_EQ(LU_Result.upper(1,2), 3);     ASSERT_EQ(LU_Result.upper(1,3), 0);     ASSERT_EQ(LU_Result.upper(1,4), 0);     ASSERT_EQ(LU_Result.upper(1,5), 3);
    ASSERT_EQ(LU_Result.upper(2,0), 0);     ASSERT_EQ(LU_Result.upper(2,1), 0);     ASSERT_EQ(LU_Result.upper(2,2), 0);     ASSERT_EQ(LU_Result.upper(2,3), -2);     ASSERT_EQ(LU_Result.upper(2,4), -4);     ASSERT_EQ(LU_Result.upper(2,5), -6);
    ASSERT_EQ(LU_Result.upper(3,0), 0);     ASSERT_EQ(LU_Result.upper(3,1), 0);     ASSERT_EQ(LU_Result.upper(3,2), 0);     ASSERT_EQ(LU_Result.upper(3,3), 0);     ASSERT_EQ(LU_Result.upper(3,4), 0);     ASSERT_EQ(LU_Result.upper(3,5), -3);
    ASSERT_EQ(LU_Result.upper(4,0), 0);     ASSERT_EQ(LU_Result.upper(4,1), 0);     ASSERT_EQ(LU_Result.upper(4,2), 0);     ASSERT_EQ(LU_Result.upper(4,3), 0);     ASSERT_EQ(LU_Result.upper(4,4), 0);     ASSERT_EQ(LU_Result.upper(4,5), 0);
    ASSERT_EQ(LU_Result.upper(5,0), 0);     ASSERT_EQ(LU_Result.upper(5,1), 0);     ASSERT_EQ(LU_Result.upper(5,2), 0);     ASSERT_EQ(LU_Result.upper(5,3), 0);     ASSERT_EQ(LU_Result.upper(5,4), 0);     ASSERT_EQ(LU_Result.upper(5,5), 0);

    // Test PA = LU
    const auto LU = LU_Result.lower.multiply(LU_Result.upper);
    const auto PA = LU_Result.permutation.value().multiply(mat);

    ASSERT_EQ(LU(0,0), PA(0,0));     ASSERT_EQ(LU(0,1), PA(0,1));     ASSERT_EQ(LU(0,2), PA(0,2));     ASSERT_EQ(LU(0,3), PA(0,3));     ASSERT_EQ(LU(0,4), PA(0,4));     ASSERT_EQ(LU(0,5), PA(0,5));
    ASSERT_EQ(LU(1,0), PA(1,0));     ASSERT_EQ(LU(1,1), PA(1,1));     ASSERT_EQ(LU(1,2), PA(1,2));     ASSERT_EQ(LU(1,3), PA(1,3));     ASSERT_EQ(LU(1,4), PA(1,4));     ASSERT_EQ(LU(1,5), PA(1,5));
    ASSERT_EQ(LU(2,0), PA(2,0));     ASSERT_EQ(LU(2,1), PA(2,1));     ASSERT_EQ(LU(2,2), PA(2,2));     ASSERT_EQ(LU(2,3), PA(2,3));     ASSERT_EQ(LU(2,4), PA(2,4));     ASSERT_EQ(LU(2,5), PA(2,5));
    ASSERT_EQ(LU(3,0), PA(3,0));     ASSERT_EQ(LU(3,1), PA(3,1));     ASSERT_EQ(LU(3,2), PA(3,2));     ASSERT_EQ(LU(3,3), PA(3,3));     ASSERT_EQ(LU(3,4), PA(3,4));     ASSERT_EQ(LU(3,5), PA(3,5));
    ASSERT_EQ(LU(4,0), PA(4,0));     ASSERT_EQ(LU(4,1), PA(4,1));     ASSERT_EQ(LU(4,2), PA(4,2));     ASSERT_EQ(LU(4,3), PA(4,3));     ASSERT_EQ(LU(4,4), PA(4,4));     ASSERT_EQ(LU(4,5), PA(4,5));
    ASSERT_EQ(LU(5,0), PA(5,0));     ASSERT_EQ(LU(5,1), PA(5,1));     ASSERT_EQ(LU(5,2), PA(5,2));     ASSERT_EQ(LU(5,3), PA(5,3));     ASSERT_EQ(LU(5,4), PA(5,4));     ASSERT_EQ(LU(5,5), PA(5,5));
}

TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Chapter_2_2_Problem_22)
{
    const auto data = std::vector<int>{8,3,16,
                                       16,8,32};

    const auto mat = Matrix<int>(data, 2, 3);
    const auto LU_Result = factorizeLU_echelon(mat);

    ASSERT_EQ(LU_Result.upper(0,0), 8);     ASSERT_EQ(LU_Result.upper(0,1), 3);     ASSERT_EQ(LU_Result.upper(0,2), 16);
    ASSERT_EQ(LU_Result.upper(1,0), 0);     ASSERT_EQ(LU_Result.upper(1,1), 2);     ASSERT_EQ(LU_Result.upper(1,2), 0);
}

TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Chapter_2_2_Problem_30)
{
    const auto data = std::vector<int>{2,4,6,4,
                                       2,5,7,6,
                                       2,3,5,2};

    const auto mat = Matrix<int>(data, 3, 4);
    const auto LU = factorizeLU_echelon(mat);

    ASSERT_EQ(LU.lower(0,0), 1);     ASSERT_EQ(LU.lower(0,1), 0);     ASSERT_EQ(LU.lower(0,2), 0);
    ASSERT_EQ(LU.lower(1,0), 1);     ASSERT_EQ(LU.lower(1,1), 1);     ASSERT_EQ(LU.lower(1,2), 0);
    ASSERT_EQ(LU.lower(2,0), 1);     ASSERT_EQ(LU.lower(2,1), -1);     ASSERT_EQ(LU.lower(2,2), 1);

    ASSERT_EQ(LU.upper(0,0), 2);     ASSERT_EQ(LU.upper(0,1), 4);     ASSERT_EQ(LU.upper(0,2), 6);     ASSERT_EQ(LU.upper(0,3), 4);
    ASSERT_EQ(LU.upper(1,0), 0);     ASSERT_EQ(LU.upper(1,1), 1);     ASSERT_EQ(LU.upper(1,2), 1);     ASSERT_EQ(LU.upper(1,3), 2);
    ASSERT_EQ(LU.upper(2,0), 0);     ASSERT_EQ(LU.upper(2,1), 0);     ASSERT_EQ(LU.upper(2,2), 0);     ASSERT_EQ(LU.upper(2,3), 0);
}

TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Chapter_2_2_Problem_33a)
{
    const auto data = std::vector<int>{1,3,3,
                                       2,6,9,
                                       -1,-3,3};

    const auto mat = Matrix<int>(data, 3, 3);
    const auto LU = factorizeLU_echelon(mat);

    ASSERT_EQ(LU.lower(0,0), 1);     ASSERT_EQ(LU.lower(0,1), 0);     ASSERT_EQ(LU.lower(0,2), 0);
    ASSERT_EQ(LU.lower(1,0), 2);     ASSERT_EQ(LU.lower(1,1), 1);     ASSERT_EQ(LU.lower(1,2), 0);
    ASSERT_EQ(LU.lower(2,0), -1);     ASSERT_EQ(LU.lower(2,1), 2);     ASSERT_EQ(LU.lower(2,2), 1);

    ASSERT_EQ(LU.upper(0,0), 1);     ASSERT_EQ(LU.upper(0,1), 3);     ASSERT_EQ(LU.upper(0,2), 3);
    ASSERT_EQ(LU.upper(1,0), 0);     ASSERT_EQ(LU.upper(1,1), 0);     ASSERT_EQ(LU.upper(1,2), 3);
    ASSERT_EQ(LU.upper(2,0), 0);     ASSERT_EQ(LU.upper(2,1), 0);     ASSERT_EQ(LU.upper(2,2), 0);
}

TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Chapter_2_2_Problem_33b)
{
    const auto data = std::vector<int>{1,3,1,2,
                                       2,6,4,8,
                                       0,0,2,4};

    const auto mat = Matrix<int>(data, 3, 4);
    const auto LU = factorizeLU_echelon(mat);

    ASSERT_EQ(LU.lower(0,0), 1);     ASSERT_EQ(LU.lower(0,1), 0);     ASSERT_EQ(LU.lower(0,2), 0);
    ASSERT_EQ(LU.lower(1,0), 2);     ASSERT_EQ(LU.lower(1,1), 1);     ASSERT_EQ(LU.lower(1,2), 0);
    ASSERT_EQ(LU.lower(2,0), 0);     ASSERT_EQ(LU.lower(2,1), 1);     ASSERT_EQ(LU.lower(2,2), 1);

    ASSERT_EQ(LU.upper(0,0), 1);     ASSERT_EQ(LU.upper(0,1), 3);     ASSERT_EQ(LU.upper(0,2), 1);     ASSERT_EQ(LU.upper(0,3), 2);
    ASSERT_EQ(LU.upper(1,0), 0);     ASSERT_EQ(LU.upper(1,1), 0);     ASSERT_EQ(LU.upper(1,2), 2);     ASSERT_EQ(LU.upper(1,3), 4);
    ASSERT_EQ(LU.upper(2,0), 0);     ASSERT_EQ(LU.upper(2,1), 0);     ASSERT_EQ(LU.upper(2,2), 0);     ASSERT_EQ(LU.upper(2,3), 0);
}

TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Chapter_2_2_Problem_34)
{
    const auto data = std::vector<int>{1,2,-2,
                                       2,5,-4,
                                       4,9,-8};

    const auto mat = Matrix<int>(data, 3, 3);
    const auto LU = factorizeLU_echelon(mat);

    ASSERT_EQ(LU.lower(0,0), 1);     ASSERT_EQ(LU.lower(0,1), 0);     ASSERT_EQ(LU.lower(0,2), 0);
    ASSERT_EQ(LU.lower(1,0), 2);     ASSERT_EQ(LU.lower(1,1), 1);     ASSERT_EQ(LU.lower(1,2), 0);
    ASSERT_EQ(LU.lower(2,0), 4);     ASSERT_EQ(LU.lower(2,1), 1);     ASSERT_EQ(LU.lower(2,2), 1);

    ASSERT_EQ(LU.upper(0,0), 1);     ASSERT_EQ(LU.upper(0,1), 2);     ASSERT_EQ(LU.upper(0,2), -2);
    ASSERT_EQ(LU.upper(1,0), 0);     ASSERT_EQ(LU.upper(1,1), 1);     ASSERT_EQ(LU.upper(1,2), 0);
    ASSERT_EQ(LU.upper(2,0), 0);     ASSERT_EQ(LU.upper(2,1), 0);     ASSERT_EQ(LU.upper(2,2), 0);
}

TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Chapter_2_2_Problem_35a)
{
    const auto data = std::vector<int>{1,2,
                                       2,4,
                                       2,5,
                                       3,9};

    const auto mat = Matrix<int>(data, 4, 2);
    const auto LU = factorizeLU_echelon(mat);

    const auto permutation = LU.permutation.value();
    ASSERT_EQ(permutation(0,0), 1);     ASSERT_EQ(permutation(0,1), 0);     ASSERT_EQ(permutation(0,2), 0);      ASSERT_EQ(permutation(0,3), 0);
    ASSERT_EQ(permutation(1,0), 0);     ASSERT_EQ(permutation(1,1), 0);     ASSERT_EQ(permutation(1,2), 1);      ASSERT_EQ(permutation(1,3), 0);
    ASSERT_EQ(permutation(2,0), 0);     ASSERT_EQ(permutation(2,1), 1);     ASSERT_EQ(permutation(2,2), 0);      ASSERT_EQ(permutation(2,3), 0);
    ASSERT_EQ(permutation(3,0), 0);     ASSERT_EQ(permutation(3,1), 0);     ASSERT_EQ(permutation(3,2), 0);      ASSERT_EQ(permutation(3,3), 1);

    ASSERT_EQ(LU.lower(0,0), 1);     ASSERT_EQ(LU.lower(0,1), 0);     ASSERT_EQ(LU.lower(0,2), 0);      ASSERT_EQ(LU.lower(0,3), 0);
    ASSERT_EQ(LU.lower(1,0), 2);     ASSERT_EQ(LU.lower(1,1), 1);     ASSERT_EQ(LU.lower(1,2), 0);      ASSERT_EQ(LU.lower(1,3), 0);
    ASSERT_EQ(LU.lower(2,0), 2);     ASSERT_EQ(LU.lower(2,1), 0);     ASSERT_EQ(LU.lower(2,2), 1);      ASSERT_EQ(LU.lower(2,3), 0);
    ASSERT_EQ(LU.lower(3,0), 3);     ASSERT_EQ(LU.lower(3,1), 3);     ASSERT_EQ(LU.lower(3,2), 0);      ASSERT_EQ(LU.lower(3,3), 1);

    ASSERT_EQ(LU.upper(0,0), 1);     ASSERT_EQ(LU.upper(0,1), 2);
    ASSERT_EQ(LU.upper(1,0), 0);     ASSERT_EQ(LU.upper(1,1), 1);
    ASSERT_EQ(LU.upper(2,0), 0);     ASSERT_EQ(LU.upper(2,1), 0);
    ASSERT_EQ(LU.upper(3,0), 0);     ASSERT_EQ(LU.upper(3,1), 0);

    // Test PA = LU
    const auto LtimesU = LU.lower.multiply(LU.upper);
    const auto PA = LU.permutation.value().multiply(mat);

    ASSERT_EQ(LtimesU(0,0), PA(0,0));     ASSERT_EQ(LtimesU(0,1), PA(0,1));
    ASSERT_EQ(LtimesU(1,0), PA(1,0));     ASSERT_EQ(LtimesU(1,1), PA(1,1));
    ASSERT_EQ(LtimesU(2,0), PA(2,0));     ASSERT_EQ(LtimesU(2,1), PA(2,1));
    ASSERT_EQ(LtimesU(3,0), PA(3,0));     ASSERT_EQ(LtimesU(3,1), PA(3,1));
}

TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Chapter_2_2_Problem_35b)
{
    const auto data = std::vector<int>{1,2,3,
                                       2,4,6,
                                       2,5,7,
                                       3,9,12};

    const auto mat = Matrix<int>(data, 4, 3);
    const auto LU = factorizeLU_echelon(mat);

    const auto permutation = LU.permutation.value();
    ASSERT_EQ(permutation(0,0), 1);     ASSERT_EQ(permutation(0,1), 0);     ASSERT_EQ(permutation(0,2), 0);      ASSERT_EQ(permutation(0,3), 0);
    ASSERT_EQ(permutation(1,0), 0);     ASSERT_EQ(permutation(1,1), 0);     ASSERT_EQ(permutation(1,2), 1);      ASSERT_EQ(permutation(1,3), 0);
    ASSERT_EQ(permutation(2,0), 0);     ASSERT_EQ(permutation(2,1), 1);     ASSERT_EQ(permutation(2,2), 0);      ASSERT_EQ(permutation(2,3), 0);
    ASSERT_EQ(permutation(3,0), 0);     ASSERT_EQ(permutation(3,1), 0);     ASSERT_EQ(permutation(3,2), 0);      ASSERT_EQ(permutation(3,3), 1);

    ASSERT_EQ(LU.lower(0,0), 1);     ASSERT_EQ(LU.lower(0,1), 0);     ASSERT_EQ(LU.lower(0,2), 0);      ASSERT_EQ(LU.lower(0,3), 0);
    ASSERT_EQ(LU.lower(1,0), 2);     ASSERT_EQ(LU.lower(1,1), 1);     ASSERT_EQ(LU.lower(1,2), 0);      ASSERT_EQ(LU.lower(1,3), 0);
    ASSERT_EQ(LU.lower(2,0), 2);     ASSERT_EQ(LU.lower(2,1), 0);     ASSERT_EQ(LU.lower(2,2), 1);      ASSERT_EQ(LU.lower(2,3), 0);
    ASSERT_EQ(LU.lower(3,0), 3);     ASSERT_EQ(LU.lower(3,1), 3);     ASSERT_EQ(LU.lower(3,2), 0);      ASSERT_EQ(LU.lower(3,3), 1);

    ASSERT_EQ(LU.upper(0,0), 1);     ASSERT_EQ(LU.upper(0,1), 2);       ASSERT_EQ(LU.upper(0,2), 3);
    ASSERT_EQ(LU.upper(1,0), 0);     ASSERT_EQ(LU.upper(1,1), 1);       ASSERT_EQ(LU.upper(1,2), 1);
    ASSERT_EQ(LU.upper(2,0), 0);     ASSERT_EQ(LU.upper(2,1), 0);       ASSERT_EQ(LU.upper(2,2), 0);
    ASSERT_EQ(LU.upper(3,0), 0);     ASSERT_EQ(LU.upper(3,1), 0);       ASSERT_EQ(LU.upper(3,2), 0);

    // Test PA = LU
    const auto LtimesU = LU.lower.multiply(LU.upper);
    const auto PA = LU.permutation.value().multiply(mat);

    ASSERT_EQ(LtimesU(0,0), PA(0,0));     ASSERT_EQ(LtimesU(0,1), PA(0,1));     ASSERT_EQ(LtimesU(0,2), PA(0,2));
    ASSERT_EQ(LtimesU(1,0), PA(1,0));     ASSERT_EQ(LtimesU(1,1), PA(1,1));     ASSERT_EQ(LtimesU(1,2), PA(1,2));
    ASSERT_EQ(LtimesU(2,0), PA(2,0));     ASSERT_EQ(LtimesU(2,1), PA(2,1));     ASSERT_EQ(LtimesU(2,2), PA(2,2));
    ASSERT_EQ(LtimesU(3,0), PA(3,0));     ASSERT_EQ(LtimesU(3,1), PA(3,1));     ASSERT_EQ(LtimesU(3,2), PA(3,2));
}

TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Chapter_2_2_Problem_36a)
{
    const auto data = std::vector<int>{1,2,1,
                                       2,6,3,
                                       0,2,5};

    const auto mat = Matrix<int>(data, 3, 3);
    const auto LU = factorizeLU_echelon(mat);

    ASSERT_EQ(LU.lower(0,0), 1);     ASSERT_EQ(LU.lower(0,1), 0);     ASSERT_EQ(LU.lower(0,2), 0);
    ASSERT_EQ(LU.lower(1,0), 2);     ASSERT_EQ(LU.lower(1,1), 1);     ASSERT_EQ(LU.lower(1,2), 0);
    ASSERT_EQ(LU.lower(2,0), 0);     ASSERT_EQ(LU.lower(2,1), 1);     ASSERT_EQ(LU.lower(2,2), 1);

    ASSERT_EQ(LU.upper(0,0), 1);     ASSERT_EQ(LU.upper(0,1), 2);       ASSERT_EQ(LU.upper(0,2), 1);
    ASSERT_EQ(LU.upper(1,0), 0);     ASSERT_EQ(LU.upper(1,1), 2);       ASSERT_EQ(LU.upper(1,2), 1);
    ASSERT_EQ(LU.upper(2,0), 0);     ASSERT_EQ(LU.upper(2,1), 0);       ASSERT_EQ(LU.upper(2,2), 4);
}

TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Chapter_2_2_Problem_36b)
{
    const auto data = std::vector<int>{1,1,1,
                                       1,2,4,
                                       2,4,8};

    const auto mat = Matrix<int>(data, 3, 3);
    const auto LU = factorizeLU_echelon(mat);

    ASSERT_EQ(LU.lower(0,0), 1);     ASSERT_EQ(LU.lower(0,1), 0);     ASSERT_EQ(LU.lower(0,2), 0);
    ASSERT_EQ(LU.lower(1,0), 1);     ASSERT_EQ(LU.lower(1,1), 1);     ASSERT_EQ(LU.lower(1,2), 0);
    ASSERT_EQ(LU.lower(2,0), 2);     ASSERT_EQ(LU.lower(2,1), 2);     ASSERT_EQ(LU.lower(2,2), 1);

    ASSERT_EQ(LU.upper(0,0), 1);     ASSERT_EQ(LU.upper(0,1), 1);       ASSERT_EQ(LU.upper(0,2), 1);
    ASSERT_EQ(LU.upper(1,0), 0);     ASSERT_EQ(LU.upper(1,1), 1);       ASSERT_EQ(LU.upper(1,2), 3);
    ASSERT_EQ(LU.upper(2,0), 0);     ASSERT_EQ(LU.upper(2,1), 0);       ASSERT_EQ(LU.upper(2,2), 0);
}

TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Chapter_2_2_Problem_48)
{
    const auto data = std::vector<int>{1,0,2,3,
                                       1,3,2,0,
                                       2,0,4,9};

    const auto mat = Matrix<int>(data, 3, 4);
    const auto LU = factorizeLU_echelon(mat);

    ASSERT_EQ(LU.lower(0,0), 1);     ASSERT_EQ(LU.lower(0,1), 0);     ASSERT_EQ(LU.lower(0,2), 0);
    ASSERT_EQ(LU.lower(1,0), 1);     ASSERT_EQ(LU.lower(1,1), 1);     ASSERT_EQ(LU.lower(1,2), 0);
    ASSERT_EQ(LU.lower(2,0), 2);     ASSERT_EQ(LU.lower(2,1), 0);     ASSERT_EQ(LU.lower(2,2), 1);

    ASSERT_EQ(LU.upper(0,0), 1);     ASSERT_EQ(LU.upper(0,1), 0);       ASSERT_EQ(LU.upper(0,2), 2);        ASSERT_EQ(LU.upper(0,3), 3);
    ASSERT_EQ(LU.upper(1,0), 0);     ASSERT_EQ(LU.upper(1,1), 3);       ASSERT_EQ(LU.upper(1,2), 0);        ASSERT_EQ(LU.upper(1,3), -3);
    ASSERT_EQ(LU.upper(2,0), 0);     ASSERT_EQ(LU.upper(2,1), 0);       ASSERT_EQ(LU.upper(2,2), 0);        ASSERT_EQ(LU.upper(2,3), 3);
}

TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Chapter_2_2_Problem_52a)
{
    const auto data = std::vector<int>{1,2,2,4,6,
                                       1,2,3,6,9,
                                       0,0,1,2,3};

    const auto mat = Matrix<int>(data, 3, 5);
    const auto LU = factorizeLU_echelon(mat);

    ASSERT_EQ(LU.lower(0,0), 1);     ASSERT_EQ(LU.lower(0,1), 0);     ASSERT_EQ(LU.lower(0,2), 0);
    ASSERT_EQ(LU.lower(1,0), 1);     ASSERT_EQ(LU.lower(1,1), 1);     ASSERT_EQ(LU.lower(1,2), 0);
    ASSERT_EQ(LU.lower(2,0), 0);     ASSERT_EQ(LU.lower(2,1), 1);     ASSERT_EQ(LU.lower(2,2), 1);

    ASSERT_EQ(LU.upper(0,0), 1);     ASSERT_EQ(LU.upper(0,1), 2);       ASSERT_EQ(LU.upper(0,2), 2);        ASSERT_EQ(LU.upper(0,3), 4);        ASSERT_EQ(LU.upper(0,4), 6);
    ASSERT_EQ(LU.upper(1,0), 0);     ASSERT_EQ(LU.upper(1,1), 0);       ASSERT_EQ(LU.upper(1,2), 1);        ASSERT_EQ(LU.upper(1,3), 2);       ASSERT_EQ(LU.upper(1,4), 3);
    ASSERT_EQ(LU.upper(2,0), 0);     ASSERT_EQ(LU.upper(2,1), 0);       ASSERT_EQ(LU.upper(2,2), 0);        ASSERT_EQ(LU.upper(2,3), 0);        ASSERT_EQ(LU.upper(2,4), 0);
}

TEST_F(MatrixLU_EchelonTests, LU_Echelon_Strang_Chapter_2_2_Problem_52b)
{
    const auto data = std::vector<int>{2,4,2,
                                       0,4,4,
                                       0,8,8};

    const auto mat = Matrix<int>(data, 3, 3);
    const auto LU = factorizeLU_echelon(mat);

    ASSERT_EQ(LU.lower(0,0), 1);     ASSERT_EQ(LU.lower(0,1), 0);     ASSERT_EQ(LU.lower(0,2), 0);
    ASSERT_EQ(LU.lower(1,0), 0);     ASSERT_EQ(LU.lower(1,1), 1);     ASSERT_EQ(LU.lower(1,2), 0);
    ASSERT_EQ(LU.lower(2,0), 0);     ASSERT_EQ(LU.lower(2,1), 2);     ASSERT_EQ(LU.lower(2,2), 1);

    ASSERT_EQ(LU.upper(0,0), 2);     ASSERT_EQ(LU.upper(0,1), 4);       ASSERT_EQ(LU.upper(0,2), 2);
    ASSERT_EQ(LU.upper(1,0), 0);     ASSERT_EQ(LU.upper(1,1), 4);       ASSERT_EQ(LU.upper(1,2), 4);
    ASSERT_EQ(LU.upper(2,0), 0);     ASSERT_EQ(LU.upper(2,1), 0);       ASSERT_EQ(LU.upper(2,2), 0);
}