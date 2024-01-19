//
// Created by dorian on 16.12.2023.
// stoicadorian@gmail.com
//
#include "gtest/gtest.h"
#include "Matrix.hpp"

using namespace LinearAlgebra::Matrix;

class MatrixArithmeticTests : public ::testing::Test
{

protected:
    virtual void SetUp()
    {
        dummyIntData    = std::vector<int>{     1, 2, 3,
                                                4, 5, 6,
                                                7, 8, 9};

        dummyFloatData  = std::vector<float>{   1.f, 3.f, 8.f,
                                                2.f, 7.f, 6.1f,
                                                0.f, -1.f, 7.f};

        dummyDoubleData = std::vector<double>{  1.0, 2.0, 3.0,
                                                4.0, 5.0, 6.0,
                                                9.1, 8.0, 7.0};
    }

    virtual void TearDown()
    {
    }

    std::vector<int>    dummyIntData;
    std::vector<double> dummyDoubleData;
    std::vector<float>  dummyFloatData;
};

TEST_F(MatrixArithmeticTests, MatrixAddition_SameType)
{
    const auto intMat = Matrix<int>(dummyIntData, 3, 3);
    const auto floatMat = Matrix<float>(dummyFloatData, 3, 3);
    const auto doubleMat = Matrix<double>(dummyDoubleData, 3, 3);

    const auto intResult = intMat + intMat;

    ASSERT_EQ(intResult(0,0), 2);    ASSERT_EQ(intResult(0,1), 4);    ASSERT_EQ(intResult(0,2), 6);
    ASSERT_EQ(intResult(1,0), 8);    ASSERT_EQ(intResult(1,1), 10);   ASSERT_EQ(intResult(1,2), 12);
    ASSERT_EQ(intResult(2,0), 14);   ASSERT_EQ(intResult(2,1), 16);   ASSERT_EQ(intResult(2,2), 18);

    const auto floatResult = floatMat + floatMat;

    ASSERT_EQ(floatResult(0,0), 2.f);    ASSERT_EQ(floatResult(0,1), 6.f);    ASSERT_EQ(floatResult(0,2), 16.f);
    ASSERT_EQ(floatResult(1,0), 4.f);    ASSERT_EQ(floatResult(1,1), 14.f);   ASSERT_EQ(floatResult(1,2), 12.2f);
    ASSERT_EQ(floatResult(2,0), 0.f);    ASSERT_EQ(floatResult(2,1), -2.f);   ASSERT_EQ(floatResult(2,2), 14.f);

    const auto doubleResult = doubleMat + doubleMat;

    ASSERT_EQ(doubleResult(0,0), 2.0);    ASSERT_EQ(doubleResult(0,1), 4.0);    ASSERT_EQ(doubleResult(0,2), 6.0);
    ASSERT_EQ(doubleResult(1,0), 8.0);    ASSERT_EQ(doubleResult(1,1), 10.0);   ASSERT_EQ(doubleResult(1,2), 12.0);
    ASSERT_EQ(doubleResult(2,0), 18.2);   ASSERT_EQ(doubleResult(2,1), 16.0);   ASSERT_EQ(doubleResult(2,2), 14.0);
}

TEST_F(MatrixArithmeticTests, MatrixAddition_Int_Plus_Float_And_Float_Plus_Int)
{
    const auto intMat = Matrix<int>(dummyIntData, 3, 3);
    const auto floatMaT= Matrix<float>(dummyFloatData, 3, 3);

    const auto result = intMat + floatMaT;
    const auto sameResult = floatMaT + intMat;

    ASSERT_EQ(result(0,0), 2.f);    ASSERT_EQ(result(0,1), 5.f);    ASSERT_EQ(result(0,2), 11.f);
    ASSERT_EQ(result(1,0), 6.f);    ASSERT_EQ(result(1,1), 12.f);   ASSERT_EQ(result(1,2), 12.1f);
    ASSERT_EQ(result(2,0), 7.f);    ASSERT_EQ(result(2,1), 7.f);    ASSERT_EQ(result(2,2), 16.f);

    ASSERT_EQ(sameResult(0,0), 2.f);    ASSERT_EQ(sameResult(0,1), 5.f);    ASSERT_EQ(sameResult(0,2), 11.f);
    ASSERT_EQ(sameResult(1,0), 6.f);    ASSERT_EQ(sameResult(1,1), 12.f);   ASSERT_EQ(sameResult(1,2), 12.1f);
    ASSERT_EQ(sameResult(2,0), 7.f);    ASSERT_EQ(sameResult(2,1), 7.f);    ASSERT_EQ(sameResult(2,2), 16.f);
}

TEST_F(MatrixArithmeticTests, MatrixAddition_Int_Plus_Double_And_Double_Plus_Int)
{
    const auto intMat = Matrix<int>(dummyIntData, 3, 3);
    const auto doubleMat= Matrix<double>(dummyDoubleData, 3, 3);

    const auto result = intMat + doubleMat;
    const auto sameResult = doubleMat + intMat;

    ASSERT_EQ(result(0,0), 2.0);    ASSERT_EQ(result(0,1), 4.0);    ASSERT_EQ(result(0,2), 6.0);
    ASSERT_EQ(result(1,0), 8.0);    ASSERT_EQ(result(1,1), 10.0);   ASSERT_EQ(result(1,2), 12.0);
    ASSERT_EQ(result(2,0), 16.1);   ASSERT_EQ(result(2,1), 16.0);   ASSERT_EQ(result(2,2), 16.0);

    ASSERT_EQ(sameResult(0,0), 2.0);    ASSERT_EQ(sameResult(0,1), 4.0);    ASSERT_EQ(sameResult(0,2), 6.0);
    ASSERT_EQ(sameResult(1,0), 8.0);    ASSERT_EQ(sameResult(1,1), 10.0);   ASSERT_EQ(sameResult(1,2), 12.0);
    ASSERT_EQ(sameResult(2,0), 16.1);   ASSERT_EQ(sameResult(2,1), 16.0);   ASSERT_EQ(sameResult(2,2), 16.0);
}

TEST_F(MatrixArithmeticTests, MatrixAddition_Double_Plus_Float_And_Float_Plus_Double)
{
    const auto doubleMat = Matrix<double>(dummyDoubleData, 3, 3);
    const auto floatMat = Matrix<float>(dummyFloatData, 3, 3);

    const auto result = doubleMat + floatMat;
    const auto sameResult = floatMat + doubleMat;

    const double eps = 1e-6;
    ASSERT_NEAR(result(0,0), 2.0, eps);    ASSERT_NEAR(result(0,1), 5.0, eps);    ASSERT_NEAR(result(0,2), 11.0, eps);
    ASSERT_NEAR(result(1,0), 6.0, eps);    ASSERT_NEAR(result(1,1), 12.0, eps);   ASSERT_NEAR(result(1,2), 12.1, eps);
    ASSERT_NEAR(result(2,0), 9.1, eps);    ASSERT_NEAR(result(2,1), 7.0, eps);    ASSERT_NEAR(result(2,2), 14.0, eps);

    ASSERT_NEAR(sameResult(0,0), 2.0, eps);    ASSERT_NEAR(sameResult(0,1), 5.0, eps);    ASSERT_NEAR(sameResult(0,2), 11.0, eps);
    ASSERT_NEAR(sameResult(1,0), 6.0, eps);    ASSERT_NEAR(sameResult(1,1), 12.0, eps);   ASSERT_NEAR(sameResult(1,2), 12.1, eps);
    ASSERT_NEAR(sameResult(2,0), 9.1, eps);    ASSERT_NEAR(sameResult(2,1), 7.0, eps);    ASSERT_NEAR(sameResult(2,2), 14.0, eps);
}

TEST_F(MatrixArithmeticTests, MatrixSubtraction_SameType)
{
    const auto intMat = Matrix<int>(dummyIntData, 3, 3);
    const auto floatMat = Matrix<float>(dummyFloatData, 3, 3);
    const auto doubleMat = Matrix<double>(dummyDoubleData, 3, 3);

    const auto intResult = intMat - intMat;

    ASSERT_EQ(intResult(0,0), 0);    ASSERT_EQ(intResult(0,1), 0);   ASSERT_EQ(intResult(0,2), 0);
    ASSERT_EQ(intResult(1,0), 0);    ASSERT_EQ(intResult(1,1), 0);   ASSERT_EQ(intResult(1,2), 0);
    ASSERT_EQ(intResult(2,0), 0);    ASSERT_EQ(intResult(2,1), 0);   ASSERT_EQ(intResult(2,2), 0);

    const auto floatResult = floatMat - floatMat;

    ASSERT_EQ(floatResult(0,0), 0.f);    ASSERT_EQ(floatResult(0,1), 0.f);   ASSERT_EQ(floatResult(0,2), 0.f);
    ASSERT_EQ(floatResult(1,0), 0.f);    ASSERT_EQ(floatResult(1,1), 0.f);   ASSERT_EQ(floatResult(1,2), 0.f);
    ASSERT_EQ(floatResult(2,0), 0.f);    ASSERT_EQ(floatResult(2,1), 0.f);   ASSERT_EQ(floatResult(2,2), 0.f);

    const auto doubleResult = doubleMat - doubleMat;

    ASSERT_EQ(doubleResult(0,0), 0.0);    ASSERT_EQ(doubleResult(0,1), 0.0);   ASSERT_EQ(doubleResult(0,2), 0.0);
    ASSERT_EQ(doubleResult(1,0), 0.0);    ASSERT_EQ(doubleResult(1,1), 0.0);   ASSERT_EQ(doubleResult(1,2), 0.0);
    ASSERT_EQ(doubleResult(2,0), 0.0);    ASSERT_EQ(doubleResult(2,1), 0.0);   ASSERT_EQ(doubleResult(2,2), 0.0);
}

TEST_F(MatrixArithmeticTests, MatrixSubtraction_Int_Minus_Float_And_Float_Minus_Int)
{
    const auto intMat = Matrix<int>(dummyIntData, 3, 3);
    const auto floatMat = Matrix<float>(dummyFloatData, 3, 3);

    const auto intMinusFloatResult = intMat - floatMat;

    const float eps = 1e-5;

    ASSERT_NEAR(intMinusFloatResult(0,0), 0.f, eps);    ASSERT_NEAR(intMinusFloatResult(0,1), -1.f, eps);   ASSERT_NEAR(intMinusFloatResult(0,2), -5.f, eps);
    ASSERT_NEAR(intMinusFloatResult(1,0), 2.f, eps);    ASSERT_NEAR(intMinusFloatResult(1,1), -2.f, eps);   ASSERT_NEAR(intMinusFloatResult(1,2), -0.1f, eps);
    ASSERT_NEAR(intMinusFloatResult(2,0), 7.f, eps);    ASSERT_NEAR(intMinusFloatResult(2,1), 9.f, eps);    ASSERT_NEAR(intMinusFloatResult(2,2), 2.f, eps);

    const auto floatMinusIntResult = floatMat - intMat;

    ASSERT_NEAR(floatMinusIntResult(0,0), 0.f, eps);     ASSERT_NEAR(floatMinusIntResult(0,1), 1.f, eps);    ASSERT_NEAR(floatMinusIntResult(0,2), 5.f, eps);
    ASSERT_NEAR(floatMinusIntResult(1,0), -2.f, eps);    ASSERT_NEAR(floatMinusIntResult(1,1), 2.f, eps);    ASSERT_NEAR(floatMinusIntResult(1,2), 0.1f, eps);
    ASSERT_NEAR(floatMinusIntResult(2,0), -7.f, eps);    ASSERT_NEAR(floatMinusIntResult(2,1), -9.f, eps);   ASSERT_NEAR(floatMinusIntResult(2,2), -2.f, eps);
}

TEST_F(MatrixArithmeticTests, MatrixSubtraction_Int_Minus_Double_And_Double_Minus_Int)
{
    const auto intMat = Matrix<int>(dummyIntData, 3, 3);
    const auto doubleMat = Matrix<double>(dummyDoubleData, 3, 3);

    const auto intMinusDoubleResult = intMat - doubleMat;
    const double eps = 1e-9;

    ASSERT_NEAR(intMinusDoubleResult(0,0), 0.0, eps);       ASSERT_NEAR(intMinusDoubleResult(0,1), 0.0, eps);   ASSERT_NEAR(intMinusDoubleResult(0,2), 0.0, eps);
    ASSERT_NEAR(intMinusDoubleResult(1,0), 0.0, eps);       ASSERT_NEAR(intMinusDoubleResult(1,1), 0.0, eps);   ASSERT_NEAR(intMinusDoubleResult(1,2), 0.0, eps);
    ASSERT_NEAR(intMinusDoubleResult(2,0), -2.1, eps);      ASSERT_NEAR(intMinusDoubleResult(2,1), 0.0, eps);   ASSERT_NEAR(intMinusDoubleResult(2,2), 2.0, eps);

    const auto doubleMinusIntResult = doubleMat - intMat;

    ASSERT_NEAR(doubleMinusIntResult(0,0), 0.0, eps);    ASSERT_NEAR(doubleMinusIntResult(0,1), 0.0, eps);    ASSERT_NEAR(doubleMinusIntResult(0,2), 0.0, eps);
    ASSERT_NEAR(doubleMinusIntResult(1,0), 0.0, eps);    ASSERT_NEAR(doubleMinusIntResult(1,1), 0.0, eps);    ASSERT_NEAR(doubleMinusIntResult(1,2), 0.0, eps);
    ASSERT_NEAR(doubleMinusIntResult(2,0), 2.1, eps);    ASSERT_NEAR(doubleMinusIntResult(2,1), 0.0, eps);   ASSERT_NEAR(doubleMinusIntResult(2,2),  -2.0, eps);
}


TEST_F(MatrixArithmeticTests, MatrixSubtraction_Float_Minus_Double_And_Double_Minus_Float)
{
    const auto floatMat = Matrix<float>(dummyFloatData, 3, 3);
    const auto doubleMat = Matrix<double>(dummyDoubleData, 3, 3);

    const auto floatMinusDoubleResult = floatMat - doubleMat;
    const double eps = 1e-5;

    ASSERT_NEAR(floatMinusDoubleResult(0,0), 0.0, eps);     ASSERT_NEAR(floatMinusDoubleResult(0,1), 1.0, eps);     ASSERT_NEAR(floatMinusDoubleResult(0,2), 5.0, eps);
    ASSERT_NEAR(floatMinusDoubleResult(1,0), -2.0, eps);    ASSERT_NEAR(floatMinusDoubleResult(1,1), 2.0, eps);     ASSERT_NEAR(floatMinusDoubleResult(1,2), 0.1, eps);
    ASSERT_NEAR(floatMinusDoubleResult(2,0), -9.1, eps);    ASSERT_NEAR(floatMinusDoubleResult(2,1), -9.0, eps);    ASSERT_NEAR(floatMinusDoubleResult(2,2), 0.0, eps);

    const auto doubleMinusFloatResult = doubleMat - floatMat;

    ASSERT_NEAR(doubleMinusFloatResult(0,0), 0.0, eps);    ASSERT_NEAR(doubleMinusFloatResult(0,1), -1.0, eps);    ASSERT_NEAR(doubleMinusFloatResult(0,2), -5.0, eps);
    ASSERT_NEAR(doubleMinusFloatResult(1,0), 2.0, eps);    ASSERT_NEAR(doubleMinusFloatResult(1,1), -2.0, eps);    ASSERT_NEAR(doubleMinusFloatResult(1,2), -0.1, eps);
    ASSERT_NEAR(doubleMinusFloatResult(2,0), 9.1, eps);    ASSERT_NEAR(doubleMinusFloatResult(2,1), 9.0, eps);   ASSERT_NEAR(doubleMinusFloatResult(2,2),  0.0, eps);
}

TEST_F(MatrixArithmeticTests, InPlaceMatrixAddition)
{
    const auto testMat = Matrix<double>(dummyDoubleData, 3, 3);
    auto result(testMat);

    result += testMat;

    ASSERT_EQ(result(0,0), 2.0);    ASSERT_EQ(result(0,1), 4.0);    ASSERT_EQ(result(0,2), 6.0);
    ASSERT_EQ(result(1,0), 8.0);    ASSERT_EQ(result(1,1), 10.0);   ASSERT_EQ(result(1,2), 12.0);
    ASSERT_EQ(result(2,0), 18.2);   ASSERT_EQ(result(2,1), 16.0);   ASSERT_EQ(result(2,2), 14.0);
}

TEST_F(MatrixArithmeticTests, InPlaceMatrixSubtraction)
{
    const auto testMat = Matrix<double>(dummyDoubleData, 3, 3);
    auto result(testMat);

    result -= testMat;

    ASSERT_EQ(result(0,0), 0.0);    ASSERT_EQ(result(0,1), 0.0);    ASSERT_EQ(result(0,2), 0.0);
    ASSERT_EQ(result(1,0), 0.0);    ASSERT_EQ(result(1,1), 0.0);    ASSERT_EQ(result(1,2), 0.0);
    ASSERT_EQ(result(2,0), 0.0);    ASSERT_EQ(result(2,1), 0.0);    ASSERT_EQ(result(2,2), 0.0);
}