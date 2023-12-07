//
// Created by dorian on 07.11.2023.
// stoicadorian@gmail.com
//
#include "gtest/gtest.h"
#include "Matrix.hpp"

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

TEST_F(MatrixTests, MatrixAddition)
{
    const auto testMat = Matrix<double>(dummyDoubleData, 3, 3);
    const auto otherMat(testMat);

    const auto result = testMat + otherMat;

    ASSERT_EQ(result(0,0), 2.0);    ASSERT_EQ(result(0,1), 4.0);    ASSERT_EQ(result(0,2), 6.0);
    ASSERT_EQ(result(1,0), 8.0);    ASSERT_EQ(result(1,1), 10.0);   ASSERT_EQ(result(1,2), 12.0);
    ASSERT_EQ(result(2,0), 18.0);   ASSERT_EQ(result(2,1), 16.0);   ASSERT_EQ(result(2,2), 14.0);
}

TEST_F(MatrixTests, MatrixSubtraction)
{
    const auto testMat = Matrix<double>(dummyDoubleData, 3, 3);
    const auto otherMat(testMat);

    const auto result = testMat - otherMat;

    ASSERT_EQ(result(0,0), 0.0);    ASSERT_EQ(result(0,1), 0.0);    ASSERT_EQ(result(0,2), 0.0);
    ASSERT_EQ(result(1,0), 0.0);    ASSERT_EQ(result(1,1), 0.0);    ASSERT_EQ(result(1,2), 0.0);
    ASSERT_EQ(result(2,0), 0.0);    ASSERT_EQ(result(2,1), 0.0);    ASSERT_EQ(result(2,2), 0.0);
}

TEST_F(MatrixTests, ElementWiseMatrixMultiplication)
{
    const auto testMat = Matrix<double>(dummyDoubleData, 3, 3);

    const auto result = testMat * testMat;

    ASSERT_EQ(result(0,0), 1.0);    ASSERT_EQ(result(0,1), 4.0);    ASSERT_EQ(result(0,2), 9.0);
    ASSERT_EQ(result(1,0), 16.0);   ASSERT_EQ(result(1,1), 25.0);   ASSERT_EQ(result(1,2), 36.0);
    ASSERT_EQ(result(2,0), 81.0);   ASSERT_EQ(result(2,1), 64.0);   ASSERT_EQ(result(2,2), 49.0);
}

TEST_F(MatrixTests, ElementWiseMatrixDivision)
{
    const auto testMat = Matrix<double>(dummyDoubleData, 3, 3);

    const auto result = testMat / testMat;

    ASSERT_EQ(result(0,0), 1.0);    ASSERT_EQ(result(0,1), 1.0);    ASSERT_EQ(result(0,2), 1.0);
    ASSERT_EQ(result(1,0), 1.0);    ASSERT_EQ(result(1,1), 1.0);    ASSERT_EQ(result(1,2), 1.0);
    ASSERT_EQ(result(2,0), 1.0);    ASSERT_EQ(result(2,1), 1.0);    ASSERT_EQ(result(2,2), 1.0);

    auto divizorWithZeros = testMat;  divizorWithZeros(0,2) = 0;

    ASSERT_THROW(testMat/divizorWithZeros, std::invalid_argument);
}

TEST_F(MatrixTests, InPlaceMatrixAddition)
{
    const auto testMat = Matrix<double>(dummyDoubleData, 3, 3);
    auto result(testMat);

    result += testMat;

    ASSERT_EQ(result(0,0), 2.0);    ASSERT_EQ(result(0,1), 4.0);    ASSERT_EQ(result(0,2), 6.0);
    ASSERT_EQ(result(1,0), 8.0);    ASSERT_EQ(result(1,1), 10.0);   ASSERT_EQ(result(1,2), 12.0);
    ASSERT_EQ(result(2,0), 18.0);   ASSERT_EQ(result(2,1), 16.0);   ASSERT_EQ(result(2,2), 14.0);
}

TEST_F(MatrixTests, InPlaceMatrixSubtraction)
{
    const auto testMat = Matrix<double>(dummyDoubleData, 3, 3);
    auto result(testMat);

    result -= testMat;

    ASSERT_EQ(result(0,0), 0.0);    ASSERT_EQ(result(0,1), 0.0);    ASSERT_EQ(result(0,2), 0.0);
    ASSERT_EQ(result(1,0), 0.0);    ASSERT_EQ(result(1,1), 0.0);    ASSERT_EQ(result(1,2), 0.0);
    ASSERT_EQ(result(2,0), 0.0);    ASSERT_EQ(result(2,1), 0.0);    ASSERT_EQ(result(2,2), 0.0);
}

TEST_F(MatrixTests, InPlaceElementWiseMatrixMultiplication)
{
    auto result = Matrix<double>(dummyDoubleData, 3, 3);

    result *= result;

    ASSERT_EQ(result(0,0), 1.0);    ASSERT_EQ(result(0,1), 4.0);    ASSERT_EQ(result(0,2), 9.0);
    ASSERT_EQ(result(1,0), 16.0);   ASSERT_EQ(result(1,1), 25.0);   ASSERT_EQ(result(1,2), 36.0);
    ASSERT_EQ(result(2,0), 81.0);   ASSERT_EQ(result(2,1), 64.0);   ASSERT_EQ(result(2,2), 49.0);
}

TEST_F(MatrixTests, InPlaceElementWiseMatrixDivision)
{
    auto result = Matrix<double>(dummyDoubleData, 3, 3);

    result /= result;

    ASSERT_EQ(result(0,0), 1.0);    ASSERT_EQ(result(0,1), 1.0);    ASSERT_EQ(result(0,2), 1.0);
    ASSERT_EQ(result(1,0), 1.0);    ASSERT_EQ(result(1,1), 1.0);    ASSERT_EQ(result(1,2), 1.0);
    ASSERT_EQ(result(2,0), 1.0);    ASSERT_EQ(result(2,1), 1.0);    ASSERT_EQ(result(2,2), 1.0);

    auto divizorWithZeros = result;  divizorWithZeros(0,2) = 0;

    ASSERT_THROW(result/=divizorWithZeros, std::invalid_argument);
}

TEST_F(MatrixTests, AdditionBroadcaster)
{
    const auto testMatrix = Matrix<int>(dummyIntData, 3, 3);

    const auto result = testMatrix + 5;

    //Also let's test the non-member operator
    const auto sameResult = 5 + testMatrix;

    ASSERT_EQ(result(0,0), 6);  ASSERT_EQ(result(0,1), 7);  ASSERT_EQ(result(0,2), 8);
    ASSERT_EQ(result(1,0), 9);  ASSERT_EQ(result(1,1), 10); ASSERT_EQ(result(1,2), 11);
    ASSERT_EQ(result(2,0), 12); ASSERT_EQ(result(2,1), 13); ASSERT_EQ(result(2,2), 14);

    ASSERT_EQ(sameResult(0,0), 6);  ASSERT_EQ(sameResult(0,1), 7);  ASSERT_EQ(sameResult(0,2), 8);
    ASSERT_EQ(sameResult(1,0), 9);  ASSERT_EQ(sameResult(1,1), 10); ASSERT_EQ(sameResult(1,2), 11);
    ASSERT_EQ(sameResult(2,0), 12); ASSERT_EQ(sameResult(2,1), 13); ASSERT_EQ(sameResult(2,2), 14);
}

TEST_F(MatrixTests, SubtractionBroadcaster)
{
    const auto testMatrix = Matrix<int>(dummyIntData, 3, 3);

    const auto result = testMatrix - 5;

    ASSERT_EQ(result(0,0), -4);  ASSERT_EQ(result(0,1), -3);  ASSERT_EQ(result(0,2), -2);
    ASSERT_EQ(result(1,0), -1);  ASSERT_EQ(result(1,1),  0);  ASSERT_EQ(result(1,2),  1);
    ASSERT_EQ(result(2,0),  2);  ASSERT_EQ(result(2,1), 3);   ASSERT_EQ(result(2,2),  4);
}

TEST_F(MatrixTests, MultiplicationBroadcaster)
{
    const auto testMatrix = Matrix<int>(dummyIntData, 3, 3);

    const auto result = testMatrix * 5;

    //Also let's test the non-member operator
    const auto sameResult = 5 * testMatrix;

    ASSERT_EQ(result(0,0), 5);      ASSERT_EQ(result(0,1), 10);     ASSERT_EQ(result(0,2), 15);
    ASSERT_EQ(result(1,0), 20);     ASSERT_EQ(result(1,1), 25);     ASSERT_EQ(result(1,2), 30);
    ASSERT_EQ(result(2,0), 35);     ASSERT_EQ(result(2,1), 40);     ASSERT_EQ(result(2,2), 45);

    ASSERT_EQ(sameResult(0,0), 5);  ASSERT_EQ(sameResult(0,1), 10); ASSERT_EQ(sameResult(0,2), 15);
    ASSERT_EQ(sameResult(1,0), 20); ASSERT_EQ(sameResult(1,1), 25); ASSERT_EQ(sameResult(1,2), 30);
    ASSERT_EQ(sameResult(2,0), 35); ASSERT_EQ(sameResult(2,1), 40); ASSERT_EQ(sameResult(2,2), 45);
}

TEST_F(MatrixTests, DivisionBroadcaster)
{
    dummyIntData = std::vector<int>{3, 6, 9,
                                    12, 15, 18,
                                    21, 24, 27};

    const auto testMatrix = Matrix<int>(dummyIntData, 3, 3);

    const auto result = testMatrix / 3;

    ASSERT_EQ(result(0,0), 1);  ASSERT_EQ(result(0,1), 2);  ASSERT_EQ(result(0,2), 3);
    ASSERT_EQ(result(1,0), 4);  ASSERT_EQ(result(1,1), 5);  ASSERT_EQ(result(1,2), 6);
    ASSERT_EQ(result(2,0), 7);  ASSERT_EQ(result(2,1), 8);  ASSERT_EQ(result(2,2), 9);

    ASSERT_THROW(testMatrix/0, std::invalid_argument);
}

TEST_F(MatrixTests, InPlaceAdditionBroadcaster)
{
    auto result = Matrix<int>(dummyIntData, 3, 3);

    result += 5;

    ASSERT_EQ(result(0,0), 6);  ASSERT_EQ(result(0,1), 7);  ASSERT_EQ(result(0,2), 8);
    ASSERT_EQ(result(1,0), 9);  ASSERT_EQ(result(1,1), 10); ASSERT_EQ(result(1,2), 11);
    ASSERT_EQ(result(2,0), 12); ASSERT_EQ(result(2,1), 13); ASSERT_EQ(result(2,2), 14);
}

TEST_F(MatrixTests, InPlaceSubtractionBroadcaster)
{
    auto result = Matrix<int>(dummyIntData, 3, 3);

    result -= 5;

    ASSERT_EQ(result(0,0), -4);  ASSERT_EQ(result(0,1), -3);  ASSERT_EQ(result(0,2), -2);
    ASSERT_EQ(result(1,0), -1);  ASSERT_EQ(result(1,1),  0);  ASSERT_EQ(result(1,2),  1);
    ASSERT_EQ(result(2,0),  2);  ASSERT_EQ(result(2,1), 3);   ASSERT_EQ(result(2,2),  4);
}

TEST_F(MatrixTests, InPlaceMultiplicationBroadcaster)
{
    auto result = Matrix<int>(dummyIntData, 3, 3);

    result *= 5;

    ASSERT_EQ(result(0,0), 5);      ASSERT_EQ(result(0,1), 10);     ASSERT_EQ(result(0,2), 15);
    ASSERT_EQ(result(1,0), 20);     ASSERT_EQ(result(1,1), 25);     ASSERT_EQ(result(1,2), 30);
    ASSERT_EQ(result(2,0), 35);     ASSERT_EQ(result(2,1), 40);     ASSERT_EQ(result(2,2), 45);
}

TEST_F(MatrixTests, InPlaceDivisionBroadcaster)
{
    dummyIntData = std::vector<int>{3, 6, 9,
                                    12, 15, 18,
                                    21, 24, 27};

    auto result = Matrix<int>(dummyIntData, 3, 3);

    result /= 3;

    ASSERT_EQ(result(0,0), 1);  ASSERT_EQ(result(0,1), 2);  ASSERT_EQ(result(0,2), 3);
    ASSERT_EQ(result(1,0), 4);  ASSERT_EQ(result(1,1), 5);  ASSERT_EQ(result(1,2), 6);
    ASSERT_EQ(result(2,0), 7);  ASSERT_EQ(result(2,1), 8);  ASSERT_EQ(result(2,2), 9);

    ASSERT_THROW(result/0, std::invalid_argument);
}

TEST_F(MatrixTests, Transpose_2_5)
{
    dummyIntData = std::vector<int> {1, 2, 3, 4, 5,
                                     6, 7, 8, 9, 0};

    const auto testMat = Matrix<int>(dummyIntData, 2, 5);
    const auto transposed = testMat.transpose();

    ASSERT_EQ(transposed.rows(), 5);
    ASSERT_EQ(transposed.cols(), 2);

    auto row = transposed.getRow(0);
    ASSERT_EQ(row[0], 1);   ASSERT_EQ(row[1], 6);

    row = transposed.getRow(1);
    ASSERT_EQ(row[0], 2);   ASSERT_EQ(row[1], 7);

    row = transposed.getRow(2);
    ASSERT_EQ(row[0], 3);   ASSERT_EQ(row[1], 8);

    row = transposed.getRow(3);
    ASSERT_EQ(row[0], 4);   ASSERT_EQ(row[1], 9);

    row = transposed.getRow(4);
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
    const auto transposed = testMat.transpose();

    ASSERT_EQ(transposed.rows(), 2);
    ASSERT_EQ(transposed.cols(), 5);

    auto row = transposed.getRow(0);
    ASSERT_EQ(row[0], 1);   ASSERT_EQ(row[1], 3); ASSERT_EQ(row[2], 5);   ASSERT_EQ(row[3], 7);ASSERT_EQ(row[4], 9);

    row = transposed.getRow(1);
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

    ASSERT_THROW(testMat.getRow(2), std::invalid_argument);

    auto row = testMat.getRow(1);
    ASSERT_EQ(row.dim(), 5);
    ASSERT_EQ(row[0], 6); ASSERT_EQ(row[1], 7); ASSERT_EQ(row[2], 8); ASSERT_EQ(row[3], 9); ASSERT_EQ(row[4], 0);
}

TEST_F(MatrixTests, SetRowFromSTLVector)
{
    auto testMat = Matrix<double>(2,4);

    ASSERT_THROW(testMat.setRow({1., 2., 3., 4.}, 5), std::invalid_argument);
    ASSERT_THROW(testMat.setRow({1., 2.}, 0), std::invalid_argument);

    testMat.setRow({0., 1., -2., 6.}, 0);
    testMat.setRow({1., 2., -4., -5.}, 1);

    ASSERT_EQ(testMat(0,0), 0.); ASSERT_EQ(testMat(0,1), 1.); ASSERT_EQ(testMat(0,2), -2.); ASSERT_EQ(testMat(0,3), 6.);
    ASSERT_EQ(testMat(1,0), 1.); ASSERT_EQ(testMat(1,1), 2.); ASSERT_EQ(testMat(1,2), -4.); ASSERT_EQ(testMat(1,3), -5.);
}

TEST_F(MatrixTests, SetRow)
{
    auto testMat = Matrix<double>(2,4);

    ASSERT_THROW(testMat.setRow(Vector<double>({1., 2., 3., 4.}), 5), std::invalid_argument);
    ASSERT_THROW(testMat.setRow(Vector<double>({1., 2.}), 0), std::invalid_argument);

    testMat.setRow(Vector<double>({0., 1., -2., 6.}), 0);
    testMat.setRow(Vector<double>({1., 2., -4., -5.}), 1);

    ASSERT_EQ(testMat(0,0), 0.); ASSERT_EQ(testMat(0,1), 1.); ASSERT_EQ(testMat(0,2), -2.); ASSERT_EQ(testMat(0,3), 6.);
    ASSERT_EQ(testMat(1,0), 1.); ASSERT_EQ(testMat(1,1), 2.); ASSERT_EQ(testMat(1,2), -4.); ASSERT_EQ(testMat(1,3), -5.);
}

TEST_F(MatrixTests, Multiply_Test1)
{
    auto data_A = std::vector<int>{1, 2, 3, 4, 5,
                                              6, 7, 8, 9, 10};
    auto data_B = std::vector<int>{  1, 2,
                                                3, 4,
                                                5, 6,
                                                7, 8,
                                                9, 10};

    const auto mat_A    = Matrix<int>(data_A, 2, 5);
    const auto mat_B    = Matrix<int>(data_B, 5, 2);

    const auto resultAB = mat_A.multiply(mat_B);
    ASSERT_EQ(resultAB.rows(), 2);
    ASSERT_EQ(resultAB.cols(), 2);

    ASSERT_EQ(resultAB(0,0), 95);   ASSERT_EQ(resultAB(0,1), 110);
    ASSERT_EQ(resultAB(1,0), 220);  ASSERT_EQ(resultAB(1,1), 260);

    const auto resultBA = mat_B.multiply(mat_A);
    ASSERT_EQ(resultBA.rows(), 5);
    ASSERT_EQ(resultBA.cols(), 5);

    ASSERT_EQ(resultBA(0,0), 13);   ASSERT_EQ(resultBA(0,1), 16);   ASSERT_EQ(resultBA(0,2), 19);   ASSERT_EQ(resultBA(0,3), 22);   ASSERT_EQ(resultBA(0,4), 25);
    ASSERT_EQ(resultBA(1,0), 27);   ASSERT_EQ(resultBA(1,1), 34);   ASSERT_EQ(resultBA(1,2), 41);   ASSERT_EQ(resultBA(1,3), 48);   ASSERT_EQ(resultBA(1,4), 55);
    ASSERT_EQ(resultBA(2,0), 41);   ASSERT_EQ(resultBA(2,1), 52);   ASSERT_EQ(resultBA(2,2), 63);   ASSERT_EQ(resultBA(2,3), 74);   ASSERT_EQ(resultBA(2,4), 85);
    ASSERT_EQ(resultBA(3,0), 55);   ASSERT_EQ(resultBA(3,1), 70);   ASSERT_EQ(resultBA(3,2), 85);   ASSERT_EQ(resultBA(3,3), 100);  ASSERT_EQ(resultBA(3,4), 115);
    ASSERT_EQ(resultBA(4,0), 69);   ASSERT_EQ(resultBA(4,1), 88);   ASSERT_EQ(resultBA(4,2), 107);  ASSERT_EQ(resultBA(4,3), 126);  ASSERT_EQ(resultBA(4,4), 145);
}

TEST_F(MatrixTests, LUFactorization_1)
{
    const auto data = std::vector<int> {1,2,3,
                                         2,3,1,
                                        -2,3,-2};
    const auto matrix = Matrix<int>(data, 3, 3);

    const auto [lower, upper] = matrix.LU();

    ASSERT_EQ(lower.rows(), 3); ASSERT_EQ(lower.cols(), 3);
    ASSERT_EQ(lower(0,0), 1);   ASSERT_EQ(lower(0,1), 0);   ASSERT_EQ(lower(0,2), 0);
    ASSERT_EQ(lower(1,0), 2);   ASSERT_EQ(lower(1,1), 1);   ASSERT_EQ(lower(1,2), 0);
    ASSERT_EQ(lower(2,0), -2);  ASSERT_EQ(lower(2,1), -7);   ASSERT_EQ(lower(2,2), 1);

    ASSERT_EQ(upper.rows(), 3); ASSERT_EQ(upper.cols(), 3);
    ASSERT_EQ(upper(0,0), 1);   ASSERT_EQ(upper(0,1), 2);   ASSERT_EQ(upper(0,2), 3);
    ASSERT_EQ(upper(1,0), 0);   ASSERT_EQ(upper(1,1), -1);  ASSERT_EQ(upper(1,2), -5);
    ASSERT_EQ(upper(2,0), 0);   ASSERT_EQ(upper(2,1), 0);   ASSERT_EQ(upper(2,2), -31);
}

TEST_F(MatrixTests, LUFactorization_2)
{
    const auto data = std::vector<int> {1,2,0,2,
                                        1,3,2,1,
                                        2,3,4,0};

    const auto matrix = Matrix<int>(data, 3, 4);

    const auto [lower, upper] = matrix.LU();

    ASSERT_EQ(lower.rows(), 3); ASSERT_EQ(lower.cols(), 3);
    ASSERT_EQ(lower(0,0), 1);   ASSERT_EQ(lower(0,1), 0);   ASSERT_EQ(lower(0,2), 0);
    ASSERT_EQ(lower(1,0), 1);   ASSERT_EQ(lower(1,1), 1);   ASSERT_EQ(lower(1,2), 0);
    ASSERT_EQ(lower(2,0), 2);   ASSERT_EQ(lower(2,1), -1);  ASSERT_EQ(lower(2,2), 1);

    ASSERT_EQ(upper.rows(), 3); ASSERT_EQ(upper.cols(), 4);
    ASSERT_EQ(upper(0,0), 1);   ASSERT_EQ(upper(0,1), 2);   ASSERT_EQ(upper(0,2), 0);   ASSERT_EQ(upper(0,3), 2);
    ASSERT_EQ(upper(1,0), 0);   ASSERT_EQ(upper(1,1), 1);   ASSERT_EQ(upper(1,2), 2);   ASSERT_EQ(upper(1,3), -1);
    ASSERT_EQ(upper(2,0), 0);   ASSERT_EQ(upper(2,1), 0);   ASSERT_EQ(upper(2,2), 6);   ASSERT_EQ(upper(2,3), -5);
}


TEST_F(MatrixTests, LUFactorization_3)
{
    const double epsilon = 1e-9;
    const auto data = std::vector<double> {11./10,    12./10,     13./10,
                                                             4,         5,          2,
                                                             23./10,    32./10,     3};

    const auto matrix = Matrix<double>(data, 3, 3);

    const auto [lower, upper] = matrix.LU();

    ASSERT_EQ(lower.rows(), 3); ASSERT_EQ(lower.cols(), 3);
    ASSERT_NEAR(lower(0,0), 1, epsilon);           ASSERT_NEAR(lower(0,1), 0, epsilon);       ASSERT_NEAR(lower(0,2), 0, epsilon);
    ASSERT_NEAR(lower(1,0), 40./11, epsilon);       ASSERT_NEAR(lower(1,1), 1, epsilon);       ASSERT_NEAR(lower(1,2), 0, epsilon);
    ASSERT_NEAR(lower(2,0), 23./11, epsilon);       ASSERT_NEAR(lower(2,1), 38./35, epsilon);   ASSERT_NEAR(lower(2,2), 1, epsilon);

    ASSERT_EQ(upper.rows(), 3); ASSERT_EQ(upper.cols(), 3);
    ASSERT_NEAR(upper(0,0), 11./10, epsilon);   ASSERT_NEAR(upper(0,1), 6./5, epsilon);     ASSERT_NEAR(upper(0,2), 13./10, epsilon);
    ASSERT_NEAR(upper(1,0), 0, epsilon);       ASSERT_NEAR(upper(1,1), 7./11, epsilon);    ASSERT_NEAR(upper(1,2), -30./11, epsilon);
    ASSERT_NEAR(upper(2,0), 0, epsilon);       ASSERT_NEAR(upper(2,1), 0, epsilon);       ASSERT_NEAR(upper(2,2), 227./70, epsilon);
}