//
// Created by dorian on 07.01.2024
// stoicadorian@gmail.com
//
#include "gtest/gtest.h"
#include "Matrix.hpp"

using namespace LinearAlgebra::Matrix;
using namespace LinearAlgebra::Vector;

class MatrixReducedRowEchelonTests : public ::testing::Test
{

protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(MatrixReducedRowEchelonTests, RREF_example)
{
    const auto data = std::vector<int> {1,2,0,2,
                                        1,3,2,1,
                                        2,3,4,0};

    const auto mat = Matrix<int>(data, 3, 4);

    const auto rre = mat.reduced_row_echelon();

    const long double epsilon = 1e-9;
    ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), 0);     ASSERT_EQ(rre(0,2), 0);     ASSERT_NEAR(rre(0,3), 2./3, epsilon);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 1);     ASSERT_EQ(rre(1,2), 0);     ASSERT_NEAR(rre(1,3), 2./3, epsilon);
    ASSERT_EQ(rre(2,0), 0);     ASSERT_EQ(rre(2,1), 0);     ASSERT_EQ(rre(2,2), 1);     ASSERT_NEAR(rre(2,3), -5./6, epsilon);
}

TEST_F(MatrixReducedRowEchelonTests, RowReduced_Echelon_Strang_Chapter_2_2_Example)
{
    const auto data = std::vector<int>{1,3,3,2,
                                       2,6,9,7,
                                       -1,-3,3,4};

    const auto mat = Matrix<int>(data, 3, 4);

    const auto rre = mat.reduced_row_echelon();
    ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), 3);     ASSERT_EQ(rre(0,2), 0);     ASSERT_EQ(rre(0,3), -1);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 0);     ASSERT_EQ(rre(1,2), 1);     ASSERT_EQ(rre(1,3), 1);
    ASSERT_EQ(rre(2,0), 0);     ASSERT_EQ(rre(2,1), 0);     ASSERT_EQ(rre(2,2), 0);     ASSERT_EQ(rre(2,3), 0);
}


TEST_F(MatrixReducedRowEchelonTests, RowReduced_Echelon_Strang_Chapter_2_2_Another_Example)
{
    const auto data = std::vector<int>{1,2,3,5,
                                       2,4,8,12,
                                       3,6,7,13};

    const auto mat = Matrix<int>(data, 3, 4);

    const auto rre = mat.reduced_row_echelon();
    ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), 2);     ASSERT_EQ(rre(0,2), 0);     ASSERT_EQ(rre(0,3), 2);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 0);     ASSERT_EQ(rre(1,2), 1);     ASSERT_EQ(rre(1,3), 1);
    ASSERT_EQ(rre(2,0), 0);     ASSERT_EQ(rre(2,1), 0);     ASSERT_EQ(rre(2,2), 0);     ASSERT_EQ(rre(2,3), 0);
}

TEST_F(MatrixReducedRowEchelonTests, RowReduced_Echelon_Strang_Chapter_2_2_Problem_2_a)
{
    const auto data = std::vector<int>{1,2,0,1,
                                       0,1,1,0,
                                       1,2,0,1};

    const auto mat = Matrix<int>(data, 3, 4);

    const auto rre = mat.reduced_row_echelon();

    ASSERT_EQ(rre.rows(), mat.rows());      ASSERT_EQ(rre.cols(), mat.cols());

    ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), 0);     ASSERT_EQ(rre(0,2), -2);     ASSERT_EQ(rre(0,3), 1);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 1);     ASSERT_EQ(rre(1,2), 1);     ASSERT_EQ(rre(1,3), 0);
    ASSERT_EQ(rre(2,0), 0);     ASSERT_EQ(rre(2,1), 0);     ASSERT_EQ(rre(2,2), 0);     ASSERT_EQ(rre(2,3), 0);
}

TEST_F(MatrixReducedRowEchelonTests, RowReduced_Echelon_Strang_Chapter_2_2_Problem_2_b)
{
    const auto data = std::vector<int>{1,2,3,
                                       4,5,6,
                                       7,8,9};

    const auto mat = Matrix<int>(data, 3, 3);

    const auto rre = mat.reduced_row_echelon();

    ASSERT_EQ(rre.rows(), mat.rows());      ASSERT_EQ(rre.cols(), mat.cols());

    ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), 0);     ASSERT_EQ(rre(0,2), -1);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 1);     ASSERT_EQ(rre(1,2), 2);
    ASSERT_EQ(rre(2,0), 0);     ASSERT_EQ(rre(2,1), 0);     ASSERT_EQ(rre(2,2), 0);
}

TEST_F(MatrixReducedRowEchelonTests, RowReduced_Echelon_Strang_Chapter_2_2_Problem_3)
{
    const auto data = std::vector<int>{0,1,0,3,
                                       0,2,0,6};

    const auto mat = Matrix<int>(data, 2, 4);
    const auto rre = mat.reduced_row_echelon();

    ASSERT_EQ(rre(0,0), 0);     ASSERT_EQ(rre(0,1), 1);     ASSERT_EQ(rre(0,2), 0);     ASSERT_EQ(rre(0,3), 3);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 0);     ASSERT_EQ(rre(1,2), 0);     ASSERT_EQ(rre(1,3), 0);
}