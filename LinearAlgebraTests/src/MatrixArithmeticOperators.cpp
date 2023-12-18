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

TEST_F(MatrixArithmeticTests, ElementWiseMatrixMultiplication_SameType)
{
    const auto intMat = Matrix<int>(dummyIntData, 3, 3);
    const auto floatMat = Matrix<float>(dummyFloatData, 3, 3);
    const auto doubleMat = Matrix<double>(dummyDoubleData, 3, 3);

    const auto intResult = intMat * intMat;

    ASSERT_EQ(intResult(0,0), 1);    ASSERT_EQ(intResult(0,1), 4);    ASSERT_EQ(intResult(0,2), 9);
    ASSERT_EQ(intResult(1,0), 16);    ASSERT_EQ(intResult(1,1), 25);   ASSERT_EQ(intResult(1,2), 36);
    ASSERT_EQ(intResult(2,0), 49);   ASSERT_EQ(intResult(2,1), 64);   ASSERT_EQ(intResult(2,2), 81);

    const auto floatResult = floatMat * floatMat;

    const float eps = 1e-5f;

    ASSERT_NEAR(floatResult(0,0), 1.f, eps);     ASSERT_NEAR(floatResult(0,1), 9.f, eps);       ASSERT_NEAR(floatResult(0,2), 64.f    , eps);
    ASSERT_NEAR(floatResult(1,0), 4.f, eps);     ASSERT_NEAR(floatResult(1,1), 49.f, eps);      ASSERT_NEAR(floatResult(1,2), 37.21f, eps);
    ASSERT_NEAR(floatResult(2,0), 0.f, eps);     ASSERT_NEAR(floatResult(2,1), 1.f, eps);       ASSERT_NEAR(floatResult(2,2), 49.f, eps);

    const auto doubleResult = doubleMat * doubleMat;
    const double deps = 1e-9;

    ASSERT_NEAR(doubleResult(0,0), 1.0, deps);      ASSERT_NEAR(doubleResult(0,1), 4.0, deps);      ASSERT_NEAR(doubleResult(0,2), 9.0, deps);
    ASSERT_NEAR(doubleResult(1,0), 16.0,deps);      ASSERT_NEAR(doubleResult(1,1), 25.0, deps);     ASSERT_NEAR(doubleResult(1,2), 36.0, deps);
    ASSERT_NEAR(doubleResult(2,0), 82.81, deps);    ASSERT_NEAR(doubleResult(2,1), 64.0, deps);     ASSERT_NEAR(doubleResult(2,2), 49.0, deps);
}

TEST_F(MatrixArithmeticTests, ElementWiseMatrixMultiplication_Int_Float_And_Float_Int)
{
    const auto intMat = Matrix<int>(dummyIntData, 3, 3);
    const auto floatMat = Matrix<float>(dummyFloatData, 3, 3);

    const auto intFloatResult = intMat * floatMat;
    const auto floatIntResult = floatMat * intMat;

    const float eps = 1e-5f;

    ASSERT_NEAR(intFloatResult(0,0), 1.f, eps);     ASSERT_NEAR(intFloatResult(0,1), 6.f, eps);         ASSERT_NEAR(intFloatResult(0,2), 24.f, eps);
    ASSERT_NEAR(intFloatResult(1,0), 8.f, eps);     ASSERT_NEAR(intFloatResult(1,1), 35.f, eps);        ASSERT_NEAR(intFloatResult(1,2), 36.6f, eps);
    ASSERT_NEAR(intFloatResult(2,0), 0.f, eps);     ASSERT_NEAR(intFloatResult(2,1), -8.f, eps);        ASSERT_NEAR(intFloatResult(2,2), 63.f, eps);

    ASSERT_NEAR(floatIntResult(0,0), 1.f, eps);     ASSERT_NEAR(floatIntResult(0,1), 6.f, eps);         ASSERT_NEAR(floatIntResult(0,2), 24.f, eps);
    ASSERT_NEAR(floatIntResult(1,0), 8.f, eps);     ASSERT_NEAR(floatIntResult(1,1), 35.f, eps);        ASSERT_NEAR(floatIntResult(1,2), 36.6f, eps);
    ASSERT_NEAR(floatIntResult(2,0), 0.f, eps);     ASSERT_NEAR(floatIntResult(2,1), -8.f, eps);        ASSERT_NEAR(floatIntResult(2,2), 63.f, eps);
}

TEST_F(MatrixArithmeticTests, ElementWiseMatrixMultiplication_Int_Double_And_Double_Int)
{
    const auto intMat = Matrix<int>(dummyIntData, 3, 3);
    const auto doubleMat = Matrix<double>(dummyDoubleData, 3, 3);

    const auto intDoubleResult = intMat * doubleMat;
    const auto doubleIntResult = doubleMat * intMat;

    const double eps = 1e-9;

    ASSERT_NEAR(intDoubleResult(0,0), 1.0, eps);     ASSERT_NEAR(intDoubleResult(0,1), 4.0, eps);     ASSERT_NEAR(intDoubleResult(0,2), 9.0, eps);
    ASSERT_NEAR(intDoubleResult(1,0), 16.0, eps);    ASSERT_NEAR(intDoubleResult(1,1), 25.0, eps);    ASSERT_NEAR(intDoubleResult(1,2), 36.0, eps);
    ASSERT_NEAR(intDoubleResult(2,0), 63.7, eps);    ASSERT_NEAR(intDoubleResult(2,1), 64, eps);      ASSERT_NEAR(intDoubleResult(2,2), 63.0, eps);

    ASSERT_NEAR(doubleIntResult(0,0), 1.0, eps);     ASSERT_NEAR(doubleIntResult(0,1), 4.0, eps);     ASSERT_NEAR(doubleIntResult(0,2), 9.0, eps);
    ASSERT_NEAR(doubleIntResult(1,0), 16.0, eps);    ASSERT_NEAR(doubleIntResult(1,1), 25.0, eps);    ASSERT_NEAR(doubleIntResult(1,2), 36.0, eps);
    ASSERT_NEAR(doubleIntResult(2,0), 63.7, eps);    ASSERT_NEAR(doubleIntResult(2,1), 64, eps);      ASSERT_NEAR(doubleIntResult(2,2), 63.0, eps);
}

TEST_F(MatrixArithmeticTests, ElementWiseMatrixMultiplication_Float_Double_And_Double_Float)
{
    const auto floatMat = Matrix<float>(dummyFloatData, 3, 3);
    const auto doubleMat = Matrix<double>(dummyDoubleData, 3, 3);

    const auto floatDoubleResult = floatMat * doubleMat;
    const auto doubleFloatResult = doubleMat * floatMat;

    const double eps = 1e-5;

    ASSERT_NEAR(floatDoubleResult(0,0), 1.0, eps);     ASSERT_NEAR(floatDoubleResult(0,1), 6.0, eps);     ASSERT_NEAR(floatDoubleResult(0,2), 24.0, eps);
    ASSERT_NEAR(floatDoubleResult(1,0), 8.0, eps);     ASSERT_NEAR(floatDoubleResult(1,1), 35.0, eps);    ASSERT_NEAR(floatDoubleResult(1,2), 36.6, eps);
    ASSERT_NEAR(floatDoubleResult(2,0), 0, eps);       ASSERT_NEAR(floatDoubleResult(2,1), -8, eps);      ASSERT_NEAR(floatDoubleResult(2,2), 49.0, eps);

    ASSERT_NEAR(doubleFloatResult(0,0), 1.0, eps);     ASSERT_NEAR(doubleFloatResult(0,1), 6.0, eps);     ASSERT_NEAR(doubleFloatResult(0,2), 24.0, eps);
    ASSERT_NEAR(doubleFloatResult(1,0), 8.0, eps);     ASSERT_NEAR(doubleFloatResult(1,1), 35.0, eps);    ASSERT_NEAR(doubleFloatResult(1,2), 36.6, eps);
    ASSERT_NEAR(doubleFloatResult(2,0), 0, eps);       ASSERT_NEAR(doubleFloatResult(2,1), -8, eps);      ASSERT_NEAR(doubleFloatResult(2,2), 49.0, eps);
}

TEST_F(MatrixArithmeticTests, ElementWiseMatrixDivision_SameType)
{
    const auto intMat = Matrix<int>(dummyIntData, 3, 3);
    auto floatMat = Matrix<float>(dummyFloatData, 3, 3);
    floatMat(2,0) = 3.14f;
    const auto doubleMat = Matrix<double>(dummyDoubleData, 3, 3);

    const auto intResult = intMat / intMat;

    ASSERT_EQ(intResult(0,0), 1);    ASSERT_EQ(intResult(0,1), 1);    ASSERT_EQ(intResult(0,2), 1);
    ASSERT_EQ(intResult(1,0), 1);    ASSERT_EQ(intResult(1,1), 1);    ASSERT_EQ(intResult(1,2), 1);
    ASSERT_EQ(intResult(2,0), 1);    ASSERT_EQ(intResult(2,1), 1);    ASSERT_EQ(intResult(2,2), 1);

    const auto floatResult = floatMat / floatMat;

    const float eps = 1e-5f;

    ASSERT_NEAR(floatResult(0,0), 1.f, eps);     ASSERT_NEAR(floatResult(0,1), 1.f, eps);       ASSERT_NEAR(floatResult(0,2), 1.f, eps);
    ASSERT_NEAR(floatResult(1,0), 1.f, eps);     ASSERT_NEAR(floatResult(1,1), 1.f, eps);       ASSERT_NEAR(floatResult(1,2), 1.f, eps);
    ASSERT_NEAR(floatResult(2,0), 1.f, eps);     ASSERT_NEAR(floatResult(2,1), 1.f, eps);       ASSERT_NEAR(floatResult(2,2), 1.f, eps);

    const auto doubleResult = doubleMat / doubleMat;
    const double deps = 1e-9;

    ASSERT_NEAR(doubleResult(0,0), 1.0, deps);      ASSERT_NEAR(doubleResult(0,1), 1.0, deps);      ASSERT_NEAR(doubleResult(0,2), 1.0, deps);
    ASSERT_NEAR(doubleResult(1,0), 1.0, deps);      ASSERT_NEAR(doubleResult(1,1), 1.0, deps);      ASSERT_NEAR(doubleResult(1,2), 1.0, deps);
    ASSERT_NEAR(doubleResult(2,0), 1.0, deps);      ASSERT_NEAR(doubleResult(2,1), 1.0, deps);      ASSERT_NEAR(doubleResult(2,2), 1.0, deps);

    auto divizorWithZerosInt = intMat;  divizorWithZerosInt(0,2) = 0;

    ASSERT_THROW(intMat/divizorWithZerosInt, std::invalid_argument);

    auto divizorWithZerosFloat = floatMat;  divizorWithZerosFloat(0,2) = 0;

    ASSERT_THROW(floatMat/divizorWithZerosFloat, std::invalid_argument);

    auto divizorWithZerosDouble = doubleMat;  divizorWithZerosDouble(0,2) = 0;

    ASSERT_THROW(doubleMat/divizorWithZerosDouble, std::invalid_argument);
}

TEST_F(MatrixArithmeticTests, ElementWiseMatrixDivision_Int_Float_And_Float_Int)
{
    const auto intMat = Matrix<int>(dummyIntData, 3, 3);
    auto floatMat = Matrix<float>(dummyFloatData, 3, 3);
    floatMat(2,0) = 3.1415f;

    const auto intFloatResult = intMat / floatMat;
    const auto floatIntResult = floatMat / intMat;

    const float eps = 1e-5f;

    ASSERT_NEAR(intFloatResult(0,0), 1.f, eps);                                                                 ASSERT_NEAR(intFloatResult(0,2), 0.375f, eps);
    ASSERT_NEAR(intFloatResult(1,0), 2.f, eps);             ASSERT_NEAR(intFloatResult(1,1), 0.71428571f, eps); ASSERT_NEAR(intFloatResult(1,2), 0.98360656f, eps);
    ASSERT_NEAR(intFloatResult(2,0), 2.22823492f, eps);     ASSERT_NEAR(intFloatResult(2,1), -8.f, eps);        ASSERT_NEAR(intFloatResult(2,2), 1.28571429f, eps);

    ASSERT_NEAR(floatIntResult(0,0), 1.f, eps);             ASSERT_NEAR(floatIntResult(0,1), 1.5f, eps);
    ASSERT_NEAR(floatIntResult(1,0), 0.5f, eps);            ASSERT_NEAR(floatIntResult(1,1), 1.4f, eps);
    ASSERT_NEAR(floatIntResult(2,0), 0.44878571f, eps);     ASSERT_NEAR(floatIntResult(2,1), -0.125f, eps);         ASSERT_NEAR(floatIntResult(2,2), 0.777777f, eps);
}

TEST_F(MatrixArithmeticTests, ElementWiseMatrixDivision_Int_Double_And_Double_Int)
{
    const auto intMat = Matrix<int>(dummyIntData, 3, 3);
    const auto doubleMat = Matrix<double>(dummyDoubleData, 3, 3);

    const auto intDoubleResult = intMat / doubleMat;
    const auto doubleIntResult = doubleMat / intMat;

    const double eps = 1e-8;

    ASSERT_NEAR(intDoubleResult(0,0), 1.0, eps);            ASSERT_NEAR(intDoubleResult(0,1), 1.0, eps);        ASSERT_NEAR(intDoubleResult(0,2), 1.0, eps);
    ASSERT_NEAR(intDoubleResult(1,0), 1.0, eps);            ASSERT_NEAR(intDoubleResult(1,1), 1.0, eps);        ASSERT_NEAR(intDoubleResult(1,2), 1.0, eps);
    ASSERT_NEAR(intDoubleResult(2,0), 0.76923077, eps);     ASSERT_NEAR(intDoubleResult(2,1), 1, eps);          ASSERT_NEAR(intDoubleResult(2,2), 1.28571429, eps);

    ASSERT_NEAR(doubleIntResult(0,0), 1.0, eps);        ASSERT_NEAR(doubleIntResult(0,1), 1.0, eps);        ASSERT_NEAR(doubleIntResult(0,2), 1.0, eps);
    ASSERT_NEAR(doubleIntResult(1,0), 1.0, eps);        ASSERT_NEAR(doubleIntResult(1,1),  1.0, eps);       ASSERT_NEAR(doubleIntResult(1,2),  1.0, eps);
    ASSERT_NEAR(doubleIntResult(2,0), 1.3, eps);        ASSERT_NEAR(doubleIntResult(2,1), 1, eps);          ASSERT_NEAR(doubleIntResult(2,2), 0.77777778, eps);
}

TEST_F(MatrixArithmeticTests, ElementWiseMatrixDivision_Float_Double_And_Double_Float)
{
    auto floatMat = Matrix<float>(dummyFloatData, 3, 3);
    floatMat(2,0) = 3.1415f;
    const auto doubleMat = Matrix<double>(dummyDoubleData, 3, 3);

    const auto floatDoubleResult = floatMat / doubleMat;
    const auto doubleFloatResult = doubleMat / floatMat;

    const double eps = 1e-5;

    ASSERT_NEAR(floatDoubleResult(0,0), 1.0, eps);          ASSERT_NEAR(floatDoubleResult(0,1), 1.5, eps);
    ASSERT_NEAR(floatDoubleResult(1,0), 0.5, eps);          ASSERT_NEAR(floatDoubleResult(1,1), 1.4, eps);
    ASSERT_NEAR(floatDoubleResult(2,0), 0.34521978, eps);   ASSERT_NEAR(floatDoubleResult(2,1), -0.125, eps);      ASSERT_NEAR(floatDoubleResult(2,2), 1.0, eps);

    ASSERT_NEAR(doubleFloatResult(0,0), 1.0, eps);                                                                      ASSERT_NEAR(doubleFloatResult(0,2), 0.375, eps);
    ASSERT_NEAR(doubleFloatResult(1,0), 2.0, eps);              ASSERT_NEAR(doubleFloatResult(1,1), 0.71428571, eps);   ASSERT_NEAR(doubleFloatResult(1,2), 0.98360656, eps);
    ASSERT_NEAR(doubleFloatResult(2,0), 2.8967054, eps);        ASSERT_NEAR(doubleFloatResult(2,1), -8, eps);           ASSERT_NEAR(doubleFloatResult(2,2), 1.0, eps);
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

TEST_F(MatrixArithmeticTests, InPlaceElementWiseMatrixMultiplication)
{
    auto result = Matrix<double>(dummyDoubleData, 3, 3);

    result *= result;

    ASSERT_EQ(result(0,0), 1.0);    ASSERT_EQ(result(0,1), 4.0);    ASSERT_EQ(result(0,2), 9.0);
    ASSERT_EQ(result(1,0), 16.0);   ASSERT_EQ(result(1,1), 25.0);   ASSERT_EQ(result(1,2), 36.0);
    ASSERT_NEAR(result(2,0), 82.81, 1e-9);   ASSERT_EQ(result(2,1), 64.0);   ASSERT_EQ(result(2,2), 49.0);
}

TEST_F(MatrixArithmeticTests, InPlaceElementWiseMatrixDivision)
{
    auto result = Matrix<double>(dummyDoubleData, 3, 3);

    result /= result;

    ASSERT_EQ(result(0,0), 1.0);    ASSERT_EQ(result(0,1), 1.0);    ASSERT_EQ(result(0,2), 1.0);
    ASSERT_EQ(result(1,0), 1.0);    ASSERT_EQ(result(1,1), 1.0);    ASSERT_EQ(result(1,2), 1.0);
    ASSERT_EQ(result(2,0), 1.0);    ASSERT_EQ(result(2,1), 1.0);    ASSERT_EQ(result(2,2), 1.0);

    auto divizorWithZeros = result;  divizorWithZeros(0,2) = 0;

    ASSERT_THROW(result/=divizorWithZeros, std::invalid_argument);
}