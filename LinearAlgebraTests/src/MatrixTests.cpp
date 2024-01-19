//
// Created by dorian on 07.11.2023.
// stoicadorian@gmail.com
//
#include "gtest/gtest.h"
#include "Matrix.hpp"
#include "MatrixToolbox.hpp"

using namespace LinearAlgebra::Matrix;
using namespace LinearAlgebra::Vector;

class MatrixTests : public ::testing::Test
{

protected:
    virtual void SetUp()
    {
        dummyIntData    = std::vector<int>{     1, 2, 3,
                                                4, 5, 6,
                                                7, 8, 9};

        dummyFloatData  = std::vector<float>{   1.f, 3.f, 8.f,
                                                2.f, 7.f, 6.f,
                                                0.f, -1.f, 7.f};

        dummyDoubleData = std::vector<double>{  1.0, 2.0, 3.0,
                                                4.0, 5.0, 6.0,
                                                9.0, 8.0, 7.0};
    }

    virtual void TearDown()
    {
    }

    std::vector<int>    dummyIntData;
    std::vector<double> dummyDoubleData;
    std::vector<float>  dummyFloatData;
};


TEST_F(MatrixTests, SimpleConstructor)
{
    ASSERT_NO_THROW(Matrix<int>(3,4));
    ASSERT_NO_THROW(Matrix<double>(4,5));
}

TEST_F(MatrixTests, STLVectorConstructor)
{
    dummyIntData    = std::vector<int>{     1, 2, 3,
                                            4, 5, 6,
                                            7, 8, 9,
                                            4, 7, 2};

    ASSERT_NO_THROW(Matrix<int>(dummyIntData, 3,4));
    ASSERT_NO_THROW(Matrix<float>(dummyFloatData, 3, 3));
    ASSERT_NO_THROW(Matrix<double>(dummyDoubleData, 3, 3));

    EXPECT_ANY_THROW(Matrix<int>(dummyIntData, 3, 3));
    EXPECT_ANY_THROW(Matrix<float>(dummyFloatData, 2, 2));
    EXPECT_ANY_THROW(Matrix<double>(dummyDoubleData, 2, 4));
}

TEST_F(MatrixTests, CopyConstructor)
{
    const auto testMat = Matrix<float>(dummyFloatData, 3, 3);
    const auto otherMat(testMat);

    ASSERT_EQ(otherMat.rows(), 3);
    ASSERT_EQ(otherMat.cols(), 3);
    ASSERT_EQ(otherMat(0,0), 1.f);  ASSERT_EQ(otherMat(0,1), 3.f);   ASSERT_EQ(otherMat(0,2), 8.f);
    ASSERT_EQ(otherMat(1,0), 2.f);  ASSERT_EQ(otherMat(1,1), 7.f);   ASSERT_EQ(otherMat(1,2), 6.f);
    ASSERT_EQ(otherMat(2,0), 0.f);  ASSERT_EQ(otherMat(2,1), -1.f);  ASSERT_EQ(otherMat(2,2), 7.f);
}

TEST_F(MatrixTests, MoveConstructor)
{
    auto testMat = Matrix<float>(dummyFloatData, 3, 3);
    const auto otherMat(std::move(testMat));

    ASSERT_EQ(otherMat.rows(), 3);
    ASSERT_EQ(otherMat.cols(), 3);
    ASSERT_EQ(otherMat(0,0), 1.f);  ASSERT_EQ(otherMat(0,1), 3.f);   ASSERT_EQ(otherMat(0,2), 8.f);
    ASSERT_EQ(otherMat(1,0), 2.f);  ASSERT_EQ(otherMat(1,1), 7.f);   ASSERT_EQ(otherMat(1,2), 6.f);
    ASSERT_EQ(otherMat(2,0), 0.f);  ASSERT_EQ(otherMat(2,1), -1.f);  ASSERT_EQ(otherMat(2,2), 7.f);

    ASSERT_EQ(testMat.rows(), 0);
    ASSERT_EQ(testMat.cols(), 0);
}

TEST_F(MatrixTests, CopyAssignment)
{
    auto otherMat = Matrix<float>(2, 2);

    const auto testMat = Matrix<float>(dummyFloatData, 3, 3);

    otherMat = testMat;

    ASSERT_EQ(otherMat.rows(), 3);
    ASSERT_EQ(otherMat.cols(), 3);
    ASSERT_EQ(otherMat(0,0), 1.f);  ASSERT_EQ(otherMat(0,1), 3.f);   ASSERT_EQ(otherMat(0,2), 8.f);
    ASSERT_EQ(otherMat(1,0), 2.f);  ASSERT_EQ(otherMat(1,1), 7.f);   ASSERT_EQ(otherMat(1,2), 6.f);
    ASSERT_EQ(otherMat(2,0), 0.f);  ASSERT_EQ(otherMat(2,1), -1.f);  ASSERT_EQ(otherMat(2,2), 7.f);
}

TEST_F(MatrixTests, MoveAssignment)
{
    auto otherMat = Matrix<float>(2, 2);

    auto testMat = Matrix<float>(dummyFloatData, 3, 3);
    otherMat = std::move(testMat);

    ASSERT_EQ(otherMat.rows(), 3);
    ASSERT_EQ(otherMat.cols(), 3);
    ASSERT_EQ(otherMat(0,0), 1.f);  ASSERT_EQ(otherMat(0,1), 3.f);   ASSERT_EQ(otherMat(0,2), 8.f);
    ASSERT_EQ(otherMat(1,0), 2.f);  ASSERT_EQ(otherMat(1,1), 7.f);   ASSERT_EQ(otherMat(1,2), 6.f);
    ASSERT_EQ(otherMat(2,0), 0.f);  ASSERT_EQ(otherMat(2,1), -1.f);  ASSERT_EQ(otherMat(2,2), 7.f);

    ASSERT_EQ(testMat.rows(), 0);
    ASSERT_EQ(testMat.cols(), 0);
}

TEST_F(MatrixTests, GetRowsAndCols)
{
    dummyIntData    = std::vector<int>{     1, 2, 3,
                                            4, 5, 6,
                                            7, 8, 9,
                                            4, 2, 7};

    const auto testMat = Matrix<int>(dummyIntData, 3, 4);
    ASSERT_EQ(testMat.rows(), 3);
    ASSERT_EQ(testMat.cols(), 4);

    const auto testMat_2 = Matrix<int>(dummyIntData, 4, 3);
    ASSERT_EQ(testMat_2.rows(), 4);
    ASSERT_EQ(testMat_2.cols(), 3);
}

TEST_F(MatrixTests, GetIndividualValues)
{
    const auto testMat = Matrix<double>(dummyDoubleData, 3, 3);

    ASSERT_EQ(testMat(0,0), 1.0);   ASSERT_EQ(testMat(0,1), 2.0);   ASSERT_EQ(testMat(0,2), 3.0);
    ASSERT_EQ(testMat(1,0), 4.0);   ASSERT_EQ(testMat(1,1), 5.0);   ASSERT_EQ(testMat(1,2), 6.0);
    ASSERT_EQ(testMat(2,0), 9.0);   ASSERT_EQ(testMat(2,1), 8.0);   ASSERT_EQ(testMat(2,2), 7.0);

    EXPECT_ANY_THROW(testMat(5,5));
}

TEST_F(MatrixTests, SetIndividualValues)
{
    auto testMat = Matrix<int>(3,3);
    testMat(0,0) = 1;   testMat(0,1) = 11;  testMat(0,2) = 21;
    testMat(1,0) = 2;   testMat(1,1) = 3;   testMat(1,2) = 4;
    testMat(2,0) = 8;   testMat(2,1) = 14;  testMat(2,2) = 12;

    ASSERT_THROW(testMat(4,2) = 12, std::invalid_argument);

    ASSERT_EQ(testMat(0,0), 1);     ASSERT_EQ(testMat(0,1), 11);    ASSERT_EQ(testMat(0,2), 21);
    ASSERT_EQ(testMat(1,0), 2);     ASSERT_EQ(testMat(1,1), 3);     ASSERT_EQ(testMat(1,2), 4);
    ASSERT_EQ(testMat(2,0), 8);     ASSERT_EQ(testMat(2,1), 14);    ASSERT_EQ(testMat(2,2), 12);
}

TEST_F(MatrixTests, Transpose_2_5)
{
    dummyIntData = std::vector<int> {1, 2, 3, 4, 5,
                                     6, 7, 8, 9, 0};

    const auto testMat = Matrix<int>(dummyIntData, 2, 5);
    const auto transposed = transpose(testMat);

    ASSERT_EQ(transposed.rows(), 5);
    ASSERT_EQ(transposed.cols(), 2);

    auto row = getRow(transposed, 0);
    ASSERT_EQ(row[0], 1);   ASSERT_EQ(row[1], 6);

    row = getRow(transposed, 1);
    ASSERT_EQ(row[0], 2);   ASSERT_EQ(row[1], 7);

    row = getRow(transposed, 2);
    ASSERT_EQ(row[0], 3);   ASSERT_EQ(row[1], 8);

    row = getRow(transposed, 3);
    ASSERT_EQ(row[0], 4);   ASSERT_EQ(row[1], 9);

    row = getRow(transposed, 4);
    ASSERT_EQ(row[0], 5);   ASSERT_EQ(row[1], 0);

    ASSERT_EQ(transposed(0,0), 1); ASSERT_EQ(transposed(0,1), 6);
    ASSERT_EQ(transposed(1,0), 2); ASSERT_EQ(transposed(1,1), 7);
    ASSERT_EQ(transposed(2,0), 3); ASSERT_EQ(transposed(2,1), 8);
    ASSERT_EQ(transposed(3,0), 4); ASSERT_EQ(transposed(3,1), 9);
    ASSERT_EQ(transposed(4,0), 5); ASSERT_EQ(transposed(4,1), 0);
}

TEST_F(MatrixTests, Transpose_5_2)
{
    dummyIntData = std::vector<int> {1, 2,
                                     3, 4,
                                     5, 6,
                                     7, 8,
                                     9, 0};

    const auto testMat = Matrix<int>(dummyIntData, 5, 2);
    const auto transposed = transpose(testMat);

    ASSERT_EQ(transposed.rows(), 2);
    ASSERT_EQ(transposed.cols(), 5);

    auto row = getRow(transposed, 0);
    ASSERT_EQ(row[0], 1);   ASSERT_EQ(row[1], 3); ASSERT_EQ(row[2], 5);   ASSERT_EQ(row[3], 7);ASSERT_EQ(row[4], 9);

    row = getRow(transposed, 1);
    ASSERT_EQ(row[0], 2);   ASSERT_EQ(row[1], 4); ASSERT_EQ(row[2], 6);   ASSERT_EQ(row[3], 8);ASSERT_EQ(row[4], 0);

    ASSERT_EQ(transposed(0,0), 1); ASSERT_EQ(transposed(0,1), 3);
    ASSERT_EQ(transposed(0,2), 5); ASSERT_EQ(transposed(0,3), 7);
    ASSERT_EQ(transposed(0,4), 9); ASSERT_EQ(transposed(1,0), 2);
    ASSERT_EQ(transposed(1,1), 4); ASSERT_EQ(transposed(1,2), 6);
    ASSERT_EQ(transposed(1,3), 8); ASSERT_EQ(transposed(1,4), 0);
}


TEST_F(MatrixTests, GetRow)
{
    dummyIntData = std::vector<int> {1, 2, 3, 4, 5,
                                     6, 7, 8, 9, 0};

    auto testMat = Matrix<int>(dummyIntData, 2, 5);

    ASSERT_THROW(getRow(testMat, 2), std::invalid_argument);

    auto row = getRow(testMat, 1);
    ASSERT_EQ(row.dim(), 5);
    ASSERT_EQ(row[0], 6); ASSERT_EQ(row[1], 7); ASSERT_EQ(row[2], 8); ASSERT_EQ(row[3], 9); ASSERT_EQ(row[4], 0);
}

TEST_F(MatrixTests, SetRowFromSTLVector)
{
    auto testMat = Matrix<double>(2,4);

    ASSERT_THROW(setRow(testMat, {1., 2., 3., 4.}, 5), std::invalid_argument);
    ASSERT_THROW(setRow(testMat, {1., 2.}, 0), std::invalid_argument);

    setRow(testMat, {0., 1., -2., 6.}, 0);
    setRow(testMat, {1., 2., -4., -5.}, 1);

    ASSERT_EQ(testMat(0,0), 0.); ASSERT_EQ(testMat(0,1), 1.); ASSERT_EQ(testMat(0,2), -2.); ASSERT_EQ(testMat(0,3), 6.);
    ASSERT_EQ(testMat(1,0), 1.); ASSERT_EQ(testMat(1,1), 2.); ASSERT_EQ(testMat(1,2), -4.); ASSERT_EQ(testMat(1,3), -5.);
}

TEST_F(MatrixTests, SetRow)
{
    auto testMat = Matrix<double>(2,4);

    ASSERT_THROW(setRow(testMat, Vector<double>({1., 2., 3., 4.}), 5), std::invalid_argument);
    ASSERT_THROW(setRow(testMat, Vector<double>({1., 2.}), 0), std::invalid_argument);

    setRow(testMat, Vector<double>({0., 1., -2., 6.}), 0);
    setRow(testMat, Vector<double>({1., 2., -4., -5.}), 1);

    ASSERT_EQ(testMat(0,0), 0.); ASSERT_EQ(testMat(0,1), 1.); ASSERT_EQ(testMat(0,2), -2.); ASSERT_EQ(testMat(0,3), 6.);
    ASSERT_EQ(testMat(1,0), 1.); ASSERT_EQ(testMat(1,1), 2.); ASSERT_EQ(testMat(1,2), -4.); ASSERT_EQ(testMat(1,3), -5.);
}

TEST_F(MatrixTests, SwapRows)
{
    auto mat = Matrix<double>({1.23, 4.56, 7.89, 8.91,
                                            -1.,  -2.,  -3.,  -4.,
                                            9.87, 8.76, 7.65, 6.54,
                                            5.43, 4.32, 3.21, 2.1,
                                            0.12, 0.34, 0.56, 0.78,
                                            },
                                            5, 4);


    double eps = 1e-9;
    ASSERT_NEAR(mat(0,0), 1.23, eps); ASSERT_NEAR(mat(1,0), -1, eps);

    //swap first 2 rows
    swapRows(mat, 0, 1);
    ASSERT_NEAR(mat(0,0), -1., eps);    ASSERT_NEAR(mat(0,1), -2, eps);     ASSERT_NEAR(mat(0,2), -3., eps);    ASSERT_NEAR(mat(0,3), -4, eps);
    ASSERT_NEAR(mat(1,0), 1.23, eps);   ASSERT_NEAR(mat(1,1), 4.56, eps);   ASSERT_NEAR(mat(1,2), 7.89, eps);   ASSERT_NEAR(mat(1,3), 8.91, eps);

    // swap rows 3 and 4
    swapRows(mat, 2, 3);
    ASSERT_NEAR(mat(2,0), 5.43, eps);   ASSERT_NEAR(mat(2,1), 4.32, eps);   ASSERT_NEAR(mat(2,2), 3.21, eps);   ASSERT_NEAR(mat(2,3), 2.1, eps);
    ASSERT_NEAR(mat(3,0), 9.87, eps);   ASSERT_NEAR(mat(3,1), 8.76, eps);   ASSERT_NEAR(mat(3,2), 7.65, eps);   ASSERT_NEAR(mat(3,3), 6.54, eps);

    // swap first and last rows (first row is the second in the original mat due to the previous swap)
    swapRows(mat, 4, 0);
    ASSERT_NEAR(mat(0,0), 0.12, eps);   ASSERT_NEAR(mat(0,1), 0.34, eps);   ASSERT_NEAR(mat(0,2), 0.56, eps);   ASSERT_NEAR(mat(0,3), 0.78, eps);
    ASSERT_NEAR(mat(4,0), -1.,  eps);   ASSERT_NEAR(mat(4,1), -2.,  eps);   ASSERT_NEAR(mat(4,2), -3.,  eps);   ASSERT_NEAR(mat(4,3), -4.,  eps);
}