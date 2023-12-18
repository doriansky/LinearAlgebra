//
// Created by dorian on 16.12.2023.
// stoicadorian@gmail.com
//


#include "gtest/gtest.h"
#include "Vector.hpp"

using namespace LinearAlgebra::Vector;

class VectorArithmeticTests : public ::testing::Test
{

protected:
    virtual void SetUp()
    {
        dummyIntData = std::vector<int>{1, 2, 3,
                                        4, 5, 6,
                                        7, 8, 9};

        dummyFloatData = std::vector<float>{1.1f, 3.1f, 8.1f,
                                            2.2f, 7.3f, 6.4f,
                                            0.2f, -1.5f, 7.2f};
        dummyDoubleData = std::vector<double>{1.1, 2.2, 3.7,
                                              4.4, 5.2, 6.7,
                                              9.3, 8.7, 7.4};
    }

    virtual void TearDown()
    {
    }

    std::vector<int>    dummyIntData;
    std::vector<double> dummyDoubleData;
    std::vector<float>  dummyFloatData;
};

TEST_F(VectorArithmeticTests, VectorAddition_IntPlusInt)
{
    const auto testVec = Vector<int>(dummyIntData);
    const auto otherVec(testVec);

    const auto result = testVec + otherVec;

    ASSERT_EQ(result[0], 2);    ASSERT_EQ(result[1], 4);    ASSERT_EQ(result[2], 6);
    ASSERT_EQ(result[3], 8);    ASSERT_EQ(result[4], 10);   ASSERT_EQ(result[5], 12);
    ASSERT_EQ(result[6], 14);   ASSERT_EQ(result[7], 16);   ASSERT_EQ(result[8], 18);
}

TEST_F(VectorArithmeticTests, VectorAddition_FloatPlusFloat)
{
    const auto testVec = Vector<float>(dummyFloatData);
    const auto otherVec(testVec);

    const auto result = testVec + otherVec;

    ASSERT_EQ(result[0], 2.2f);    ASSERT_EQ(result[1], 6.2f);    ASSERT_EQ(result[2], 16.2f);
    ASSERT_EQ(result[3], 4.4f);    ASSERT_EQ(result[4], 14.6f);   ASSERT_EQ(result[5], 12.8f);
    ASSERT_EQ(result[6], 0.4f);   ASSERT_EQ(result[7], -3.f);   ASSERT_EQ(result[8], 14.4f);
}

TEST_F(VectorArithmeticTests, VectorAddition_DoublePlusDouble)
{
    const auto testVec = Vector<double>(dummyDoubleData);
    const auto otherVec(testVec);

    const auto result = testVec + otherVec;

    ASSERT_EQ(result[0], 2.2);    ASSERT_EQ(result[1], 4.4);    ASSERT_EQ(result[2], 7.4);
    ASSERT_EQ(result[3], 8.8);    ASSERT_EQ(result[4], 10.4);   ASSERT_EQ(result[5], 13.4);
    ASSERT_EQ(result[6], 18.6);   ASSERT_EQ(result[7], 17.4);   ASSERT_EQ(result[8], 14.8);
}

TEST_F(VectorArithmeticTests, VectorAddition_IntPlusFloat)
{
    const auto intVec = Vector<int>(dummyIntData);
    const auto floatVec  = Vector<float>(dummyFloatData);

    const auto result = intVec + floatVec;

    ASSERT_EQ(result[0], 2.1f);    ASSERT_EQ(result[1], 5.1f);    ASSERT_EQ(result[2], 11.1f);
    ASSERT_EQ(result[3], 6.2f);    ASSERT_EQ(result[4], 12.3f);   ASSERT_EQ(result[5], 12.4f);
    ASSERT_EQ(result[6], 7.2f);   ASSERT_EQ(result[7], 6.5f);   ASSERT_EQ(result[8], 16.2f);
}

TEST_F(VectorArithmeticTests, VectorAddition_IntPlusDouble)
{
    const auto intVec = Vector<int>(dummyIntData);
    const auto doubleVec  = Vector<double>(dummyDoubleData);

    const auto result = intVec + doubleVec;

    ASSERT_EQ(result[0], 2.1);    ASSERT_EQ(result[1], 4.2);    ASSERT_EQ(result[2], 6.7);
    ASSERT_EQ(result[3], 8.4);    ASSERT_EQ(result[4], 10.2);   ASSERT_EQ(result[5], 12.7);
    ASSERT_EQ(result[6], 16.3);   ASSERT_EQ(result[7], 16.7);   ASSERT_EQ(result[8], 16.4);
}

TEST_F(VectorArithmeticTests, VectorAddition_FloatPlusInt)
{
    const auto intVec = Vector<int>(dummyIntData);
    const auto floatVec  = Vector<float>(dummyFloatData);

    const auto result = floatVec + intVec;

    ASSERT_EQ(result[0], 2.1f);    ASSERT_EQ(result[1], 5.1f);    ASSERT_EQ(result[2], 11.1f);
    ASSERT_EQ(result[3], 6.2f);    ASSERT_EQ(result[4], 12.3f);   ASSERT_EQ(result[5], 12.4f);
    ASSERT_EQ(result[6], 7.2f);   ASSERT_EQ(result[7], 6.5f);   ASSERT_EQ(result[8], 16.2f);
}

TEST_F(VectorArithmeticTests, VectorAddition_FloatPlusDouble)
{
    const auto doubleVec = Vector<double>(dummyDoubleData);
    const auto floatVec  = Vector<float>(dummyFloatData);

    const auto result = floatVec + doubleVec;
    const double eps = 1e-6;

    ASSERT_NEAR(result[0], 2.2, eps);       ASSERT_NEAR(result[1], 5.3, eps);    ASSERT_NEAR(result[2], 11.8, eps);
    ASSERT_NEAR(result[3], 6.6, eps);       ASSERT_NEAR(result[4], 12.5, eps);   ASSERT_NEAR(result[5], 13.1, eps);
    ASSERT_NEAR(result[6], 9.5, eps);       ASSERT_NEAR(result[7], 7.2, eps);   ASSERT_NEAR(result[8], 14.6, eps);
}

TEST_F(VectorArithmeticTests, VectorAddition_DoublePlusInt)
{
    auto intVec = Vector<int>(dummyIntData);
    const auto doubleVec  = Vector<double>(dummyDoubleData);

    const auto result = doubleVec + intVec;

    ASSERT_EQ(result[0], 2.1);    ASSERT_EQ(result[1], 4.2);    ASSERT_EQ(result[2], 6.7);
    ASSERT_EQ(result[3], 8.4);    ASSERT_EQ(result[4], 10.2);   ASSERT_EQ(result[5], 12.7);
    ASSERT_EQ(result[6], 16.3);   ASSERT_EQ(result[7], 16.7);   ASSERT_EQ(result[8], 16.4);
}

TEST_F(VectorArithmeticTests, VectorAddition_DoublePlusFloat)
{
    const auto doubleVec = Vector<double>(dummyDoubleData);
    const auto floatVec  = Vector<float>(dummyFloatData);

    const auto result = doubleVec + floatVec;
    const double eps = 1e-6;

    ASSERT_NEAR(result[0], 2.2, eps);       ASSERT_NEAR(result[1], 5.3, eps);    ASSERT_NEAR(result[2], 11.8, eps);
    ASSERT_NEAR(result[3], 6.6, eps);       ASSERT_NEAR(result[4], 12.5, eps);   ASSERT_NEAR(result[5], 13.1, eps);
    ASSERT_NEAR(result[6], 9.5, eps);       ASSERT_NEAR(result[7], 7.2, eps);   ASSERT_NEAR(result[8], 14.6, eps);
}

TEST_F(VectorArithmeticTests, VectorSubtractionIntMinusInt)
{
    const auto testVec = Vector<int>(dummyIntData);
    const auto otherVec(testVec);

    const auto result = testVec - otherVec;

    ASSERT_EQ(result[0], 0);    ASSERT_EQ(result[1], 0);    ASSERT_EQ(result[2], 0);
    ASSERT_EQ(result[3], 0);    ASSERT_EQ(result[4], 0);    ASSERT_EQ(result[5], 0);
    ASSERT_EQ(result[6], 0);    ASSERT_EQ(result[7], 0);    ASSERT_EQ(result[8], 0);
}

TEST_F(VectorArithmeticTests, VectorSubtractionFloatMinusFloat)
{
    const auto testVec = Vector<float>(dummyFloatData);
    const auto otherVec(testVec);

    const auto result = testVec - otherVec;

    ASSERT_EQ(result[0], 0.f);    ASSERT_EQ(result[1], 0.f);    ASSERT_EQ(result[2], 0.f);
    ASSERT_EQ(result[3], 0.f);    ASSERT_EQ(result[4], 0.f);    ASSERT_EQ(result[5], 0.f);
    ASSERT_EQ(result[6], 0.f);    ASSERT_EQ(result[7], 0.f);    ASSERT_EQ(result[8], 0.f);
}

TEST_F(VectorArithmeticTests, VectorSubtractionDoubleMinusDouble)
{
    const auto testVec = Vector<double>(dummyDoubleData);
    const auto otherVec(testVec);

    const auto result = testVec - otherVec;

    ASSERT_EQ(result[0], 0.0);    ASSERT_EQ(result[1], 0.0);    ASSERT_EQ(result[2], 0.0);
    ASSERT_EQ(result[3], 0.0);    ASSERT_EQ(result[4], 0.0);    ASSERT_EQ(result[5], 0.0);
    ASSERT_EQ(result[6], 0.0);    ASSERT_EQ(result[7], 0.0);    ASSERT_EQ(result[8], 0.0);
}

TEST_F(VectorArithmeticTests, VectorSubtractionIntMinusFloat)
{
    const auto intVec = Vector<int>(dummyIntData);
    const auto floatVec = Vector<float>(dummyFloatData);

    const auto result = intVec - floatVec;

    const float eps = 1e-6f;
    ASSERT_NEAR(result[0], -0.1f, eps);     ASSERT_NEAR(result[1], -1.1f, eps);     ASSERT_NEAR(result[2], -5.1f, eps);
    ASSERT_NEAR(result[3], 1.8f, eps);      ASSERT_NEAR(result[4], -2.3f, eps);     ASSERT_NEAR(result[5], -0.4f, eps);
    ASSERT_NEAR(result[6], 6.8f, eps);      ASSERT_NEAR(result[7], 9.5f, eps);      ASSERT_NEAR(result[8], 1.8f, eps);
}

TEST_F(VectorArithmeticTests, VectorSubtractionIntMinusDouble)
{
    const auto intVec = Vector<int>(dummyIntData);
    const auto doubleVec = Vector<double>(dummyDoubleData);

    const auto result = intVec - doubleVec;

    const double eps = 1e-9;
    ASSERT_NEAR(result[0], -0.1, eps);    ASSERT_NEAR(result[1], -0.2, eps);    ASSERT_NEAR(result[2], -0.7, eps);
    ASSERT_NEAR(result[3], -0.4, eps);    ASSERT_NEAR(result[4], -0.2, eps);    ASSERT_NEAR(result[5], -0.7, eps);
    ASSERT_NEAR(result[6], -2.3, eps);    ASSERT_NEAR(result[7], -0.7, eps);    ASSERT_NEAR(result[8], 1.6, eps);
}

TEST_F(VectorArithmeticTests, VectorSubtractionFloatMinusInt)
{
    const auto intVec = Vector<int>(dummyIntData);
    const auto floatVec = Vector<float>(dummyFloatData);

    const auto result = floatVec - intVec;
    const float eps = 1e-6f;

    ASSERT_NEAR(result[0], 0.1f, eps);     ASSERT_NEAR(result[1], 1.1f, eps);     ASSERT_NEAR(result[2], 5.1f, eps);
    ASSERT_NEAR(result[3], -1.8f, eps);      ASSERT_NEAR(result[4], 2.3f, eps);     ASSERT_NEAR(result[5], 0.4f, eps);
    ASSERT_NEAR(result[6], -6.8f, eps);      ASSERT_NEAR(result[7], -9.5f, eps);      ASSERT_NEAR(result[8], -1.8f, eps);
}

TEST_F(VectorArithmeticTests, VectorSubtractionFloatMinusDouble)
{
    const auto doubleVec = Vector<double>(dummyDoubleData);
    const auto floatVec = Vector<float>(dummyFloatData);

    const auto result = floatVec - doubleVec;
    const float eps = 1e-6f;

    ASSERT_NEAR(result[0], 0.0f, eps);      ASSERT_NEAR(result[1], 0.9f, eps);      ASSERT_NEAR(result[2], 4.4f, eps);
    ASSERT_NEAR(result[3], -2.2f, eps);     ASSERT_NEAR(result[4], 2.1f, eps);      ASSERT_NEAR(result[5], -0.3f, eps);
    ASSERT_NEAR(result[6], -9.1f, eps);     ASSERT_NEAR(result[7], -10.2f, eps);     ASSERT_NEAR(result[8], -0.2f, eps);
}

TEST_F(VectorArithmeticTests, VectorSubtractionDoubleMinusInt)
{
    const auto doubleVec = Vector<double>(dummyDoubleData);
    const auto intVec = Vector<int>(dummyIntData);

    const auto result = doubleVec - intVec;
    const double eps = 1e-9;
    ASSERT_NEAR(result[0], 0.1, eps);    ASSERT_NEAR(result[1], 0.2, eps);    ASSERT_NEAR(result[2], 0.7, eps);
    ASSERT_NEAR(result[3], 0.4, eps);    ASSERT_NEAR(result[4], 0.2, eps);    ASSERT_NEAR(result[5], 0.7, eps);
    ASSERT_NEAR(result[6], 2.3, eps);    ASSERT_NEAR(result[7], 0.7, eps);    ASSERT_NEAR(result[8], -1.6, eps);
}

TEST_F(VectorArithmeticTests, VectorSubtractionDoubleMinusFloat)
{
    const auto doubleVec = Vector<double>(dummyDoubleData);
    const auto floatVec = Vector<float>(dummyFloatData);

    const auto result = doubleVec - floatVec;

    const float eps = 1e-6;

    ASSERT_NEAR(result[0], 0.0, eps);       ASSERT_NEAR(result[1], -0.9, eps);      ASSERT_NEAR(result[2], -4.4, eps);
    ASSERT_NEAR(result[3], 2.2, eps);       ASSERT_NEAR(result[4], -2.1, eps);      ASSERT_NEAR(result[5], 0.3, eps);
    ASSERT_NEAR(result[6], 9.1, eps);       ASSERT_NEAR(result[7], 10.2, eps);      ASSERT_NEAR(result[8], 0.2, eps);
}

TEST_F(VectorArithmeticTests, ElementWiseVectorMultiplication_IntTimesInt)
{
    const auto testVec = Vector<int>(dummyIntData);

    const auto result = testVec * testVec;

    ASSERT_EQ(result[0], 1);    ASSERT_EQ(result[1], 4);    ASSERT_EQ(result[2], 9);
    ASSERT_EQ(result[3], 16);   ASSERT_EQ(result[4], 25);   ASSERT_EQ(result[5], 36);
    ASSERT_EQ(result[6], 49);   ASSERT_EQ(result[7], 64);   ASSERT_EQ(result[8], 81);
}

TEST_F(VectorArithmeticTests, ElementWiseVectorMultiplication_FloatTimesFloat)
{
    const auto testVec = Vector<float>(dummyFloatData);

    const auto result = testVec * testVec;
    const auto eps = 1e-5f;
    ASSERT_NEAR(result[0], 1.21f, eps);     ASSERT_NEAR(result[1], 9.61f, eps);     ASSERT_NEAR(result[2], 65.61f, eps);
    ASSERT_NEAR(result[3], 4.84f, eps);     ASSERT_NEAR(result[4], 53.29f, eps);    ASSERT_NEAR(result[5], 40.96f, eps);
    ASSERT_NEAR(result[6], 0.04f, eps);     ASSERT_NEAR(result[7], 2.25f, eps);     ASSERT_NEAR(result[8], 51.84f, eps);
}

TEST_F(VectorArithmeticTests, ElementWiseVectorMultiplication_DoubleTimesDouble)
{
    const auto testVec = Vector<double>(dummyDoubleData);

    const auto result = testVec * testVec;

    const auto eps = 1e-9;
    ASSERT_NEAR(result[0], 1.21, eps);    ASSERT_NEAR(result[1], 4.84, eps);    ASSERT_NEAR(result[2], 13.69, eps);
    ASSERT_NEAR(result[3], 19.36, eps);   ASSERT_NEAR(result[4], 27.04, eps);   ASSERT_NEAR(result[5], 44.89, eps);
    ASSERT_NEAR(result[6], 86.49, eps);   ASSERT_NEAR(result[7], 75.69, eps);   ASSERT_NEAR(result[8], 54.76, eps);
}

TEST_F(VectorArithmeticTests, ElementWiseVectorMultiplication_IntTimesFloat)
{
    const auto intVec = Vector<int>(dummyIntData);
    const auto floatVec = Vector<float>(dummyFloatData);

    const auto result = intVec * floatVec;
    const auto eps = 1e-5f;
    ASSERT_NEAR(result[0], 1.1f, eps);     ASSERT_NEAR(result[1], 6.2f, eps);     ASSERT_NEAR(result[2], 24.3f, eps);
    ASSERT_NEAR(result[3], 8.8f, eps);     ASSERT_NEAR(result[4], 36.5f, eps);    ASSERT_NEAR(result[5], 38.4f, eps);
    ASSERT_NEAR(result[6], 1.4f, eps);     ASSERT_NEAR(result[7], -12.f, eps);     ASSERT_NEAR(result[8], 64.8f, eps);
}

TEST_F(VectorArithmeticTests, ElementWiseVectorMultiplication_IntTimesDouble)
{
    const auto intVec = Vector<int>(dummyIntData);
    const auto doubleVec = Vector<double>(dummyDoubleData);

    const auto result = intVec * doubleVec;
    const auto eps = 1e-9;
    ASSERT_NEAR(result[0], 1.1, eps);       ASSERT_NEAR(result[1], 4.4, eps);       ASSERT_NEAR(result[2], 11.1, eps);
    ASSERT_NEAR(result[3], 17.6, eps);      ASSERT_NEAR(result[4], 26, eps);        ASSERT_NEAR(result[5], 40.2, eps);
    ASSERT_NEAR(result[6], 65.1, eps);      ASSERT_NEAR(result[7], 69.6, eps);
}

TEST_F(VectorArithmeticTests, ElementWiseVectorMultiplication_FloatTimesInt)
{
    const auto intVec = Vector<int>(dummyIntData);
    const auto floatVec = Vector<float>(dummyFloatData);

    const auto result = floatVec * intVec;
    const auto eps = 1e-5f;
    ASSERT_NEAR(result[0], 1.1f, eps);     ASSERT_NEAR(result[1], 6.2f, eps);     ASSERT_NEAR(result[2], 24.3f, eps);
    ASSERT_NEAR(result[3], 8.8f, eps);     ASSERT_NEAR(result[4], 36.5f, eps);    ASSERT_NEAR(result[5], 38.4f, eps);
    ASSERT_NEAR(result[6], 1.4f, eps);     ASSERT_NEAR(result[7], -12.f, eps);     ASSERT_NEAR(result[8], 64.8f, eps);
}

TEST_F(VectorArithmeticTests, ElementWiseVectorMultiplication_FloatTimesDouble)
{
    const auto doubleVec = Vector<double>(dummyDoubleData);
    const auto floatVec = Vector<float>(dummyFloatData);

    const auto result = floatVec * doubleVec;
    const auto eps = 1e-5f;
    ASSERT_NEAR(result[0], 1.21, eps);     ASSERT_NEAR(result[1], 6.82, eps);     ASSERT_NEAR(result[2], 29.97, eps);
    ASSERT_NEAR(result[3], 9.68, eps);     ASSERT_NEAR(result[4], 37.96, eps);    ASSERT_NEAR(result[5], 42.88, eps);
    ASSERT_NEAR(result[6], 1.86, eps);     ASSERT_NEAR(result[7], -13.05, eps);     ASSERT_NEAR(result[8], 53.28, eps);
}

TEST_F(VectorArithmeticTests, ElementWiseVectorMultiplication_DoubleTimesInt)
{
    const auto intVec = Vector<int>(dummyIntData);
    const auto doubleVec = Vector<double>(dummyDoubleData);

    const auto result = doubleVec * intVec;
    const auto eps = 1e-9;
    ASSERT_NEAR(result[0], 1.1, eps);       ASSERT_NEAR(result[1], 4.4, eps);       ASSERT_NEAR(result[2], 11.1, eps);
    ASSERT_NEAR(result[3], 17.6, eps);      ASSERT_NEAR(result[4], 26, eps);        ASSERT_NEAR(result[5], 40.2, eps);
    ASSERT_NEAR(result[6], 65.1, eps);      ASSERT_NEAR(result[7], 69.6, eps);
}

TEST_F(VectorArithmeticTests, ElementWiseVectorMultiplication_DoubleTimesFloat)
{
    const auto doubleVec = Vector<double>(dummyDoubleData);
    const auto floatVec = Vector<float>(dummyFloatData);

    const auto result = doubleVec * floatVec;
    const auto eps = 1e-5f;
    ASSERT_NEAR(result[0], 1.21, eps);     ASSERT_NEAR(result[1], 6.82, eps);     ASSERT_NEAR(result[2], 29.97, eps);
    ASSERT_NEAR(result[3], 9.68, eps);     ASSERT_NEAR(result[4], 37.96, eps);    ASSERT_NEAR(result[5], 42.88, eps);
    ASSERT_NEAR(result[6], 1.86, eps);     ASSERT_NEAR(result[7], -13.05, eps);     ASSERT_NEAR(result[8], 53.28, eps);
}

TEST_F(VectorArithmeticTests, ElementWiseVectorDivision_Int_Int)
{
    const auto testVec = Vector<int>(dummyIntData);

    const auto result = testVec / testVec;

    ASSERT_EQ(result[0], 1);    ASSERT_EQ(result[1], 1);    ASSERT_EQ(result[2], 1);
    ASSERT_EQ(result[3], 1);    ASSERT_EQ(result[4], 1);    ASSERT_EQ(result[5], 1);
    ASSERT_EQ(result[6], 1);    ASSERT_EQ(result[7], 1);    ASSERT_EQ(result[8], 1);

    auto divizorWithZeros = testVec;  divizorWithZeros[0] = 0;

    ASSERT_THROW(testVec/divizorWithZeros, std::invalid_argument);
}

TEST_F(VectorArithmeticTests, ElementWiseVectorDivision_Float_Float)
{
    const auto testVec = Vector<float>(dummyFloatData);

    const auto result = testVec / testVec;

    ASSERT_EQ(result[0], 1.f);    ASSERT_EQ(result[1], 1.f);    ASSERT_EQ(result[2], 1.f);
    ASSERT_EQ(result[3], 1.f);    ASSERT_EQ(result[4], 1.f);    ASSERT_EQ(result[5], 1.f);
    ASSERT_EQ(result[6], 1.f);    ASSERT_EQ(result[7], 1.f);    ASSERT_EQ(result[8], 1.f);

    auto divizorWithZeros = testVec;  divizorWithZeros[0] = 0.f;

    ASSERT_THROW(testVec/divizorWithZeros, std::invalid_argument);
}

TEST_F(VectorArithmeticTests, ElementWiseVectorDivision_Double_Double)
{
    const auto testVec = Vector<double>(dummyDoubleData);

    const auto result = testVec / testVec;

    ASSERT_EQ(result[0], 1.);    ASSERT_EQ(result[1], 1.);    ASSERT_EQ(result[2], 1.);
    ASSERT_EQ(result[3], 1.);    ASSERT_EQ(result[4], 1.);    ASSERT_EQ(result[5], 1.);
    ASSERT_EQ(result[6], 1.);    ASSERT_EQ(result[7], 1.);    ASSERT_EQ(result[8], 1.);

    auto divizorWithZeros = testVec;  divizorWithZeros[0] = 0.0;

    ASSERT_THROW(testVec/divizorWithZeros, std::invalid_argument);
}

TEST_F(VectorArithmeticTests, ElementWiseVectorDivision_Int_Float)
{
    const auto intVec = Vector<int>(dummyIntData);
    const auto floatVec = Vector<float>(dummyFloatData);

    const auto result = intVec / floatVec;
    const float eps = 1e-5f;
    ASSERT_NEAR(result[0], 0.909090909090909f, eps);    ASSERT_NEAR(result[1], 0.645161290322581f, eps);    ASSERT_NEAR(result[2], 0.37037037037037f, eps);
    ASSERT_NEAR(result[3], 1.81818181818182f, eps);     ASSERT_NEAR(result[4], 0.684931506849315f, eps);    ASSERT_NEAR(result[5], 0.9375f, eps);
    ASSERT_NEAR(result[6], 35.f, eps);                  ASSERT_NEAR(result[7], -5.33333333333333f, eps);    ASSERT_NEAR(result[8], 1.25f, eps);
}

TEST_F(VectorArithmeticTests, ElementWiseVectorDivision_Int_Double)
{
    const auto intVec = Vector<int>(dummyIntData);
    const auto doubleVec = Vector<double>(dummyDoubleData);

    const auto result = intVec/ doubleVec;
    const float eps = 1e-9;
    ASSERT_NEAR(result[0], 0.909090909090909, eps);    ASSERT_NEAR(result[1], 0.909090909090909, eps);    ASSERT_NEAR(result[2], 0.810810810810811, eps);
    ASSERT_NEAR(result[3], 0.909090909090909, eps);    ASSERT_NEAR(result[4], 0.961538461538461, eps);    ASSERT_NEAR(result[5], 0.895522388059701, eps);
    ASSERT_NEAR(result[6], 0.752688172043011, eps);    ASSERT_NEAR(result[7], 0.919540229885058, eps);    ASSERT_NEAR(result[8], 1.21621621621622, eps);
}

TEST_F(VectorArithmeticTests, ElementWiseVectorDivision_Float_Int)
{
    const auto intVec = Vector<int>(dummyIntData);
    const auto floatVec = Vector<float>(dummyFloatData);

    const auto result = floatVec/ intVec;
    const float eps = 1e-5f;
    ASSERT_NEAR(result[0], 1.1f, eps);                  ASSERT_NEAR(result[1], 1.55f, eps);         ASSERT_NEAR(result[2], 2.7f, eps);
        ASSERT_NEAR(result[3], 0.55f, eps);             ASSERT_NEAR(result[4], 1.46f, eps);         ASSERT_NEAR(result[5], 1.06666666666667f, eps);
    ASSERT_NEAR(result[6], 0.0285714285714286f, eps);   ASSERT_NEAR(result[7], -0.1875f, eps);      ASSERT_NEAR(result[8], 0.8f, eps);
}

TEST_F(VectorArithmeticTests, ElementWiseVectorDivision_Float_Double)
{
    const auto doubleVec = Vector<double>(dummyDoubleData);
    const auto floatVec = Vector<float>(dummyFloatData);

    const auto result = floatVec/ doubleVec;
    const float eps = 1e-5f;
    ASSERT_NEAR(result[0], 1.0, eps);    ASSERT_NEAR(result[1], 1.40909090909091, eps);    ASSERT_NEAR(result[2], 2.18918918918919, eps);
    ASSERT_NEAR(result[3], 0.5, eps);    ASSERT_NEAR(result[4], 1.40384615384615, eps);    ASSERT_NEAR(result[5], 0.955223880597015, eps);
    ASSERT_NEAR(result[6], 0.021505376344086, eps);    ASSERT_NEAR(result[7], -0.172413793103448, eps);    ASSERT_NEAR(result[8], 0.972972972972973, eps);
}

TEST_F(VectorArithmeticTests, ElementWiseVectorDivision_Double_Int)
{
    const auto doubleVec = Vector<double>(dummyDoubleData);
    const auto intVec = Vector<int>(dummyIntData);

    const auto result = doubleVec / intVec;
    const float eps = 1e-9;
    ASSERT_NEAR(result[0], 1.1, eps);                   ASSERT_NEAR(result[1], 1.1, eps);       ASSERT_NEAR(result[2], 1.23333333333333, eps);
    ASSERT_NEAR(result[3], 1.1, eps);                   ASSERT_NEAR(result[4], 1.04, eps);      ASSERT_NEAR(result[5], 1.11666666666667, eps);
    ASSERT_NEAR(result[6], 1.32857142857143, eps);      ASSERT_NEAR(result[7], 1.0875, eps);    ASSERT_NEAR(result[8], 0.822222222222222, eps);
}

TEST_F(VectorArithmeticTests, ElementWiseVectorDivision_Double_Float)
{
    const auto doubleVec = Vector<double>(dummyDoubleData);
    const auto floatVec = Vector<float>(dummyFloatData);

    const auto result = doubleVec / floatVec;
    const float eps = 1e-5f;
    ASSERT_NEAR(result[0], 1., eps);        ASSERT_NEAR(result[1], 0.709677419354839, eps);     ASSERT_NEAR(result[2], 0.45679012345679, eps);
    ASSERT_NEAR(result[3], 2., eps);        ASSERT_NEAR(result[4], 0.712328767123288, eps);     ASSERT_NEAR(result[5], 1.046875, eps);
    ASSERT_NEAR(result[6], 46.5, eps);      ASSERT_NEAR(result[7], -5.8f, eps);                 ASSERT_NEAR(result[8], 1.02777777777778, eps);
}

TEST_F(VectorArithmeticTests, InPlaceVectorAddition)
{
    auto testVec = Vector<double>(dummyDoubleData);

    testVec += testVec;

    ASSERT_EQ(testVec[0], 2.2);    ASSERT_EQ(testVec[1], 4.4);    ASSERT_EQ(testVec[2], 7.4);
    ASSERT_EQ(testVec[3], 8.8);    ASSERT_EQ(testVec[4], 10.4);   ASSERT_EQ(testVec[5], 13.4);
    ASSERT_EQ(testVec[6], 18.6);   ASSERT_EQ(testVec[7], 17.4);   ASSERT_EQ(testVec[8], 14.8);
}

TEST_F(VectorArithmeticTests, InPlaceVectorSubtraction)
{
    auto testVec = Vector<double>(dummyDoubleData);

    testVec -= testVec;

    ASSERT_EQ(testVec[0], 0.0);    ASSERT_EQ(testVec[1], 0.0);    ASSERT_EQ(testVec[2], 0.0);
    ASSERT_EQ(testVec[3], 0.0);    ASSERT_EQ(testVec[4], 0.0);    ASSERT_EQ(testVec[5], 0.0);
    ASSERT_EQ(testVec[6], 0.0);    ASSERT_EQ(testVec[7], 0.0);    ASSERT_EQ(testVec[8], 0.0);
}

TEST_F(VectorArithmeticTests, InPlaceElementWiseVectorMultiplication)
{
    auto result = Vector<double>(dummyDoubleData);

    result *= result;
    const double eps = 1e-9;
    ASSERT_NEAR(result[0], 1.21, eps);    ASSERT_NEAR(result[1], 4.84, eps);    ASSERT_NEAR(result[2], 13.69, eps);
    ASSERT_NEAR(result[3], 19.36, eps);   ASSERT_NEAR(result[4], 27.04, eps);   ASSERT_NEAR(result[5], 44.89, eps);
    ASSERT_NEAR(result[6], 86.49, eps);   ASSERT_NEAR(result[7], 75.69, eps);   ASSERT_NEAR(result[8], 54.76, eps);
}

TEST_F(VectorArithmeticTests, InPlaceElementWiseVectorDivision)
{
    auto result = Vector<double>(dummyDoubleData);

    result /= result;

    ASSERT_EQ(result[0], 1.0);    ASSERT_EQ(result[1],1.0);    ASSERT_EQ(result[2], 1.0);
    ASSERT_EQ(result[3], 1.0);   ASSERT_EQ(result[4], 1.0);   ASSERT_EQ(result[5], 1.0);
    ASSERT_EQ(result[6], 1.0);   ASSERT_EQ(result[7], 1.0);   ASSERT_EQ(result[8], 1.0);

    auto divizorWithZeros = result;  divizorWithZeros[2] = 0;

    ASSERT_THROW(result/=divizorWithZeros, std::invalid_argument);
}