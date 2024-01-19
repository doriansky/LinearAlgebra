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