//
// Created by dorian on 07.01.2024
// stoicadorian@gmail.com
//
#include "gtest/gtest.h"
#include "Matrix.hpp"
#include "MatrixHelpers.hpp"

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

    const auto rre = reduced_row_echelon(mat);

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

    const auto rre = reduced_row_echelon(mat);
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

    const auto rre = reduced_row_echelon(mat);
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

    const auto rre = reduced_row_echelon(mat);

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

    const auto rre = reduced_row_echelon(mat);

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
    const auto rre = reduced_row_echelon(mat);

    ASSERT_EQ(rre(0,0), 0);     ASSERT_EQ(rre(0,1), 1);     ASSERT_EQ(rre(0,2), 0);     ASSERT_EQ(rre(0,3), 3);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 0);     ASSERT_EQ(rre(1,2), 0);     ASSERT_EQ(rre(1,3), 0);
}

TEST_F(MatrixReducedRowEchelonTests, RowReduced_Echelon_Strang_Chapter_2_2_Problem_4)
{
    const auto data = std::vector<int>{0,0,
                                       1,2,
                                       0,0,
                                       3,6};

    const auto mat = Matrix<int>(data, 4, 2);
    const auto rre = reduced_row_echelon(mat);

    ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), 2);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 0);
    ASSERT_EQ(rre(2,0), 0);     ASSERT_EQ(rre(2,1), 0);
    ASSERT_EQ(rre(3,0), 0);     ASSERT_EQ(rre(3,1), 0);
}

TEST_F(MatrixReducedRowEchelonTests, RowReduced_Strang_Chapter_2_2_Problem_5a)
{
    const auto data = std::vector<int>{1,2,2,
                                       2,4,5};

    const auto mat = Matrix<int>(data, 2, 3);
    const auto rre = reduced_row_echelon(mat);

    ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), 2);     ASSERT_EQ(rre(0,2), 0);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 0);     ASSERT_EQ(rre(1,2), 1);
}

TEST_F(MatrixReducedRowEchelonTests, RowReduced_Strang_Chapter_2_2_Problem_5b)
{
    const auto data = std::vector<int>{1,2,2,
                                       2,4,4};

    const auto mat = Matrix<int>(data, 2, 3);
    const auto rre = reduced_row_echelon(mat);

    ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), 2);     ASSERT_EQ(rre(0,2), 2);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 0);     ASSERT_EQ(rre(1,2), 0);
}

TEST_F(MatrixReducedRowEchelonTests, RowReduced_Strang_Chapter_2_2_Problem_6)
{
    const auto data = std::vector<int>{1,0,
                                       0,1,
                                       2,3};

    const auto mat = Matrix<int>(data, 3, 2);
    const auto rre = reduced_row_echelon(mat);

    ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), 0);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 1);
    ASSERT_EQ(rre(2,0), 0);     ASSERT_EQ(rre(2,1), 0);
}

TEST_F(MatrixReducedRowEchelonTests, RowReduced_Strang_Chapter_2_2_Problem_7)
{
    const auto data = std::vector<int>{1,1,2,
                                       2,3,-1,
                                       3,4,1};

    const auto mat = Matrix<int>(data, 3, 3);
    const auto rre = reduced_row_echelon(mat);

    ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), 0);     ASSERT_EQ(rre(0,2), 7);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 1);     ASSERT_EQ(rre(1,2), -5);
    ASSERT_EQ(rre(2,0), 0);     ASSERT_EQ(rre(2,1), 0);     ASSERT_EQ(rre(2,2), 0);
}

TEST_F(MatrixReducedRowEchelonTests, RowReduced_Echelon_Strang_Chapter_2_2_Problem_8)
{
    const auto data = std::vector<int>{1,2,0,3,
                                       2,4,0,7};

    const auto mat = Matrix<int>(data, 2, 4);
    const auto rre = reduced_row_echelon(mat);

    ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), 2);     ASSERT_EQ(rre(0,2), 0);     ASSERT_EQ(rre(0,3), 0);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 0);     ASSERT_EQ(rre(1,2), 0);     ASSERT_EQ(rre(1,3), 1);
}

TEST_F(MatrixReducedRowEchelonTests, RowReduced_Echelon_Strang_Chapter_2_2_Problem_9)
{
    const auto data = std::vector<int>{1,2,3,4,
                                       0,0,1,2,
                                       0,0,0,0};

    const auto mat = Matrix<int>(data, 3, 4);
    const auto rre = reduced_row_echelon(mat);

    ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), 2);     ASSERT_EQ(rre(0,2), 0);     ASSERT_EQ(rre(0,3), -2);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 0);     ASSERT_EQ(rre(1,2), 1);     ASSERT_EQ(rre(1,3), 2);
    ASSERT_EQ(rre(2,0), 0);     ASSERT_EQ(rre(2,1), 0);     ASSERT_EQ(rre(2,2), 0);     ASSERT_EQ(rre(2,3), 0);
}

TEST_F(MatrixReducedRowEchelonTests, RowReduced_Echelon_Strang_Chapter_2_2_Problem_13a)
{
    const auto data = std::vector<int>{1,1,1,1,
                                       1,1,1,1,
                                       1,1,1,1};

    const auto mat = Matrix<int>(data, 3, 4);
    const auto rre = reduced_row_echelon(mat);

    ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), 1);     ASSERT_EQ(rre(0,2), 1);     ASSERT_EQ(rre(0,3), 1);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 0);     ASSERT_EQ(rre(1,2), 0);     ASSERT_EQ(rre(1,3), 0);
    ASSERT_EQ(rre(2,0), 0);     ASSERT_EQ(rre(2,1), 0);     ASSERT_EQ(rre(2,2), 0);     ASSERT_EQ(rre(2,3), 0);
}

TEST_F(MatrixReducedRowEchelonTests, RowReduced_Echelon_Strang_Chapter_2_2_Problem_13b)
{
    //a_ij = (-1)^(i+j)
    const auto data = std::vector<int>{1,-1,1,-1,
                                       -1,1,-1,1,
                                       1,-1,1,-1,
                                       -1,1,-1,1};

    const auto mat = Matrix<int>(data, 4, 4);
    const auto rre = reduced_row_echelon(mat);

    ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), -1);     ASSERT_EQ(rre(0,2), 1);     ASSERT_EQ(rre(0,3), -1);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 0);     ASSERT_EQ(rre(1,2), 0);     ASSERT_EQ(rre(1,3), 0);
    ASSERT_EQ(rre(2,0), 0);     ASSERT_EQ(rre(2,1), 0);     ASSERT_EQ(rre(2,2), 0);     ASSERT_EQ(rre(2,3), 0);
    ASSERT_EQ(rre(3,0), 0);     ASSERT_EQ(rre(3,1), 0);     ASSERT_EQ(rre(3,2), 0);     ASSERT_EQ(rre(3,3), 0);
}

TEST_F(MatrixReducedRowEchelonTests, RowReduced_Echelon_Strang_Chapter_2_2_Problem_13c)
{
    //a_ij = (-1)^(j)
    const auto data = std::vector<int>{-1,1,-1,1,
                                       -1,1,-1,1,
                                       -1,1,-1,1};

    const auto mat = Matrix<int>(data, 3, 4);
    const auto rre = reduced_row_echelon(mat);

    ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), -1);     ASSERT_EQ(rre(0,2), 1);     ASSERT_EQ(rre(0,3), -1);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 0);     ASSERT_EQ(rre(1,2), 0);     ASSERT_EQ(rre(1,3), 0);
    ASSERT_EQ(rre(2,0), 0);     ASSERT_EQ(rre(2,1), 0);     ASSERT_EQ(rre(2,2), 0);     ASSERT_EQ(rre(2,3), 0);
}

TEST_F(MatrixReducedRowEchelonTests, RowReduced_Echelon_Strang_Chapter_2_2_Problem_13d)
{
    //a_ij = (-1)^(i*j)
    const auto data = std::vector<int>{-1,1,-1,1,
                                       1,1,1,1,
                                       -1,1,-1,1,
                                       1,1,1,1};

    const auto mat = Matrix<int>(data, 4, 4);
    const auto rre = reduced_row_echelon(mat);

    ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), 0);     ASSERT_EQ(rre(0,2), 1);     ASSERT_EQ(rre(0,3), 0);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 1);     ASSERT_EQ(rre(1,2), 0);     ASSERT_EQ(rre(1,3), 1);
    ASSERT_EQ(rre(2,0), 0);     ASSERT_EQ(rre(2,1), 0);     ASSERT_EQ(rre(2,2), 0);     ASSERT_EQ(rre(2,3), 0);
    ASSERT_EQ(rre(3,0), 0);     ASSERT_EQ(rre(3,1), 0);     ASSERT_EQ(rre(3,2), 0);     ASSERT_EQ(rre(3,3), 0);
}

TEST_F(MatrixReducedRowEchelonTests, RowReduced_Echelon_Strang_Chapter_2_2_Problem_14a_3x3)
{
    const auto data = std::vector<int>{0,0,0,
                                       0,0,3,
                                       2,4,6};

    const auto mat = Matrix<int>(data, 3, 3);
    const auto rre = reduced_row_echelon(mat);

    ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), 2);     ASSERT_EQ(rre(0,2), 0);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 0);     ASSERT_EQ(rre(1,2), 1);
    ASSERT_EQ(rre(2,0), 0);     ASSERT_EQ(rre(2,1), 0);     ASSERT_EQ(rre(2,2), 0);
}

TEST_F(MatrixReducedRowEchelonTests, RowReduced_Echelon_Strang_Chapter_2_2_Problem_14b_3x6)
{
    const auto data = std::vector<int>{0,0,0,0,0,0,
                                       0,0,3,0,0,3,
                                       2,4,6,2,4,6};

    const auto mat = Matrix<int>(data, 3, 6);
    const auto rre = reduced_row_echelon(mat);

    ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), 2);     ASSERT_EQ(rre(0,2), 0);     ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), 2);     ASSERT_EQ(rre(0,2), 0);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 0);     ASSERT_EQ(rre(1,2), 1);     ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 0);     ASSERT_EQ(rre(1,2), 1);
    ASSERT_EQ(rre(2,0), 0);     ASSERT_EQ(rre(2,1), 0);     ASSERT_EQ(rre(2,2), 0);     ASSERT_EQ(rre(2,0), 0);     ASSERT_EQ(rre(2,1), 0);     ASSERT_EQ(rre(2,2), 0);
}

TEST_F(MatrixReducedRowEchelonTests, RowReduced_Echelon_Strang_Chapter_2_2_Problem_14c_6x6_multiple_permutations)
{
    const auto data = std::vector<int>{0,0,0,0,0,0,
                                       0,0,3,0,0,3,
                                       2,4,6,2,4,6,
                                       0,0,0,0,0,0,
                                       0,0,3,0,0,0,
                                       2,4,6,0,0,0};

    const auto mat = Matrix<int>(data, 6, 6);
    const auto rre = reduced_row_echelon(mat);

    ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), 2);     ASSERT_EQ(rre(0,2), 0);     ASSERT_EQ(rre(0,3), 0);     ASSERT_EQ(rre(0,4), 0);     ASSERT_EQ(rre(0,5), 0);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 0);     ASSERT_EQ(rre(1,2), 1);     ASSERT_EQ(rre(1,3), 0);     ASSERT_EQ(rre(1,4), 0);     ASSERT_EQ(rre(1,5), 0);
    ASSERT_EQ(rre(2,0), 0);     ASSERT_EQ(rre(2,1), 0);     ASSERT_EQ(rre(2,2), 0);     ASSERT_EQ(rre(2,3), 1);     ASSERT_EQ(rre(2,4), 2);     ASSERT_EQ(rre(2,5), 0);
    ASSERT_EQ(rre(3,0), 0);     ASSERT_EQ(rre(3,1), 0);     ASSERT_EQ(rre(3,2), 0);     ASSERT_EQ(rre(3,3), 0);     ASSERT_EQ(rre(3,4), 0);     ASSERT_EQ(rre(3,5), 1);
    ASSERT_EQ(rre(4,0), 0);     ASSERT_EQ(rre(4,1), 0);     ASSERT_EQ(rre(4,2), 0);     ASSERT_EQ(rre(4,3), 0);     ASSERT_EQ(rre(4,4), 0);     ASSERT_EQ(rre(4,5), 0);
    ASSERT_EQ(rre(5,0), 0);     ASSERT_EQ(rre(5,1), 0);     ASSERT_EQ(rre(5,2), 0);     ASSERT_EQ(rre(5,3), 0);     ASSERT_EQ(rre(5,4), 0);     ASSERT_EQ(rre(5,5), 0);
}

TEST_F(MatrixReducedRowEchelonTests, RowReduced_Echelon_Strang_Chapter_2_2_Problem_22)
{
    const auto data = std::vector<int>{8,3,16,
                                       16,8,32};

    const auto mat = Matrix<int>(data, 2, 3);
    const auto rre = reduced_row_echelon(mat);

    ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), 0);     ASSERT_EQ(rre(0,2), 2);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 1);     ASSERT_EQ(rre(1,2), 0);
}

TEST_F(MatrixReducedRowEchelonTests, RowReduced_Echelon_Strang_Chapter_2_2_Problem_30)
{
    const auto data = std::vector<int>{2,4,6,4,
                                       2,5,7,6,
                                       2,3,5,2};

    const auto mat = Matrix<int>(data, 3, 4);
    const auto rre = reduced_row_echelon(mat);

    ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), 0);     ASSERT_EQ(rre(0,2), 1);     ASSERT_EQ(rre(0,3), -2);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 1);     ASSERT_EQ(rre(1,2), 1);     ASSERT_EQ(rre(1,3), 2);
    ASSERT_EQ(rre(2,0), 0);     ASSERT_EQ(rre(2,1), 0);     ASSERT_EQ(rre(2,2), 0);     ASSERT_EQ(rre(2,3), 0);
}

TEST_F(MatrixReducedRowEchelonTests, RowReduced_Echelon_Strang_Chapter_2_2_Problem_33a)
{
    const auto data = std::vector<int>{1,3,3,
                                       2,6,9,
                                       -1,-3,3};

    const auto mat = Matrix<int>(data, 3, 3);
    const auto rre = reduced_row_echelon(mat);

    ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), 3);     ASSERT_EQ(rre(0,2), 0);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 0);     ASSERT_EQ(rre(1,2), 1);
    ASSERT_EQ(rre(2,0), 0);     ASSERT_EQ(rre(2,1), 0);     ASSERT_EQ(rre(2,2), 0);
}

TEST_F(MatrixReducedRowEchelonTests, RowReduced_Echelon_Strang_Chapter_2_2_Problem_33b)
{
    const auto data = std::vector<int>{1,3,1,2,
                                       2,6,4,8,
                                       0,0,2,4};

    const auto mat = Matrix<int>(data, 3, 4);
    const auto rre = reduced_row_echelon(mat);

    ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), 3);     ASSERT_EQ(rre(0,2), 0);     ASSERT_EQ(rre(0,3), 0);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 0);     ASSERT_EQ(rre(1,2), 1);     ASSERT_EQ(rre(1,3), 2);
    ASSERT_EQ(rre(2,0), 0);     ASSERT_EQ(rre(2,1), 0);     ASSERT_EQ(rre(2,2), 0);     ASSERT_EQ(rre(2,3), 0);
}

TEST_F(MatrixReducedRowEchelonTests, RowReduced_Echelon_Strang_Chapter_2_2_Problem_34)
{
    const auto data = std::vector<int>{1,2,-2,
                                       2,5,-4,
                                       4,9,-8};

    const auto mat = Matrix<int>(data, 3, 3);
    const auto rre = reduced_row_echelon(mat);

    ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), 0);     ASSERT_EQ(rre(0,2), -2);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 1);     ASSERT_EQ(rre(1,2), 0);
    ASSERT_EQ(rre(2,0), 0);     ASSERT_EQ(rre(2,1), 0);     ASSERT_EQ(rre(2,2), 0);
}

TEST_F(MatrixReducedRowEchelonTests, RowReduced_Echelon_Strang_Chapter_2_2_Problem_35a)
{
    const auto data = std::vector<int>{1,2,
                                       2,4,
                                       2,5,
                                       3,9};

    const auto mat = Matrix<int>(data, 4, 2);
    const auto rre = reduced_row_echelon(mat);

    ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), 0);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 1);
    ASSERT_EQ(rre(2,0), 0);     ASSERT_EQ(rre(2,1), 0);
    ASSERT_EQ(rre(3,0), 0);     ASSERT_EQ(rre(3,1), 0);
}

TEST_F(MatrixReducedRowEchelonTests, RowReduced_Echelon_Strang_Chapter_2_2_Problem_35b)
{
    const auto data = std::vector<int>{1,2,3,
                                       2,4,6,
                                       2,5,7,
                                       3,9,12};

    const auto mat = Matrix<int>(data, 4, 3);
    const auto rre = reduced_row_echelon(mat);

    ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), 0);     ASSERT_EQ(rre(0,2), 1);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 1);     ASSERT_EQ(rre(1,2), 1);
    ASSERT_EQ(rre(2,0), 0);     ASSERT_EQ(rre(2,1), 0);     ASSERT_EQ(rre(2,2), 0);
    ASSERT_EQ(rre(3,0), 0);     ASSERT_EQ(rre(3,1), 0);     ASSERT_EQ(rre(3,2), 0);
}

TEST_F(MatrixReducedRowEchelonTests, RowReduced_Echelon_Strang_Chapter_2_2_Problem_36a)
{
    const auto data = std::vector<int>{1,2,1,
                                       2,6,3,
                                       0,2,5};

    const auto mat = Matrix<int>(data, 3, 3);
    const auto rre = reduced_row_echelon(mat);

    // This is non-singular matrix, therefore rre is identity
    ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), 0);     ASSERT_EQ(rre(0,2), 0);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 1);     ASSERT_EQ(rre(1,2), 0);
    ASSERT_EQ(rre(2,0), 0);     ASSERT_EQ(rre(2,1), 0);     ASSERT_EQ(rre(2,2), 1);
}

TEST_F(MatrixReducedRowEchelonTests, RowReduced_Echelon_Strang_Chapter_2_2_Problem_36b)
{
    const auto data = std::vector<int>{1,1,1,
                                       1,2,4,
                                       2,4,8};

    const auto mat = Matrix<int>(data, 3, 3);
    const auto rre = reduced_row_echelon(mat);

    ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), 0);     ASSERT_EQ(rre(0,2), -2);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 1);     ASSERT_EQ(rre(1,2), 3);
    ASSERT_EQ(rre(2,0), 0);     ASSERT_EQ(rre(2,1), 0);     ASSERT_EQ(rre(2,2), 0);
}

TEST_F(MatrixReducedRowEchelonTests, RowReduced_Echelon_Strang_Chapter_2_2_Problem_48)
{
    const auto data = std::vector<int>{1,0,2,3,
                                       1,3,2,0,
                                       2,0,4,9};

    const auto mat = Matrix<int>(data, 3, 4);
    const auto rre = reduced_row_echelon(mat);

    ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), 0);     ASSERT_EQ(rre(0,2), 2);     ASSERT_EQ(rre(0,3), 0);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 1);     ASSERT_EQ(rre(1,2), 0);     ASSERT_EQ(rre(1,3), 0);
    ASSERT_EQ(rre(2,0), 0);     ASSERT_EQ(rre(2,1), 0);     ASSERT_EQ(rre(2,2), 0);     ASSERT_EQ(rre(2,3), 1);
}

TEST_F(MatrixReducedRowEchelonTests, RowReduced_Echelon_Strang_Chapter_2_2_Problem_52a)
{
    const auto data = std::vector<int>{1,2,2,4,6,
                                       1,2,3,6,9,
                                       0,0,1,2,3};

    const auto mat = Matrix<int>(data, 3, 5);
    const auto rre = reduced_row_echelon(mat);

    ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), 2);     ASSERT_EQ(rre(0,2), 0);     ASSERT_EQ(rre(0,3), 0);     ASSERT_EQ(rre(0,4), 0);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 0);     ASSERT_EQ(rre(1,2), 1);     ASSERT_EQ(rre(1,3), 2);     ASSERT_EQ(rre(1,4), 3);
    ASSERT_EQ(rre(2,0), 0);     ASSERT_EQ(rre(2,1), 0);     ASSERT_EQ(rre(2,2), 0);     ASSERT_EQ(rre(2,3), 0);     ASSERT_EQ(rre(2,4), 0);
}

TEST_F(MatrixReducedRowEchelonTests, RowReduced_Echelon_Strang_Chapter_2_2_Problem_52b)
{
    const auto data = std::vector<int>{2,4,2,
                                       0,4,4,
                                       0,8,8};

    const auto mat = Matrix<int>(data, 3, 3);
    const auto rre = reduced_row_echelon(mat);

    ASSERT_EQ(rre(0,0), 1);     ASSERT_EQ(rre(0,1), 0);     ASSERT_EQ(rre(0,2), -1);
    ASSERT_EQ(rre(1,0), 0);     ASSERT_EQ(rre(1,1), 1);     ASSERT_EQ(rre(1,2), 1);
    ASSERT_EQ(rre(2,0), 0);     ASSERT_EQ(rre(2,1), 0);     ASSERT_EQ(rre(2,2), 0);
}