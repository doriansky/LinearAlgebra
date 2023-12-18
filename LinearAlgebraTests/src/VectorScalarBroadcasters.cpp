//
// Created by dorian on 16.12.2023.
// stoicadorian@gmail.com
//

#include "gtest/gtest.h"
#include "Vector.hpp"

using namespace LinearAlgebra::Vector;

class VectorBroadcastersTests : public ::testing::Test
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

TEST_F(VectorBroadcastersTests, AdditionBroadcaster_Int_Int)
{
    const auto testVector = Vector<int>(dummyIntData);

    const auto result = testVector + 5;

    //Also let's test the non-member operator
    const auto sameResult = 5 + testVector;

    ASSERT_EQ(result[0], 6);  ASSERT_EQ(result[1], 7);  ASSERT_EQ(result[2], 8);
    ASSERT_EQ(result[3], 9);  ASSERT_EQ(result[4], 10); ASSERT_EQ(result[5], 11);
    ASSERT_EQ(result[6], 12); ASSERT_EQ(result[7], 13); ASSERT_EQ(result[8], 14);

    ASSERT_EQ(sameResult[0], 6);  ASSERT_EQ(sameResult[1], 7);  ASSERT_EQ(sameResult[2], 8);
    ASSERT_EQ(sameResult[3], 9);  ASSERT_EQ(sameResult[4], 10); ASSERT_EQ(sameResult[5], 11);
    ASSERT_EQ(sameResult[6], 12); ASSERT_EQ(sameResult[7], 13); ASSERT_EQ(sameResult[8], 14);
}

TEST_F(VectorBroadcastersTests, AdditionBroadcaster_Int_Float)
{
    const auto testVector = Vector<int>(dummyIntData);
    const float value = 5.1f;
    const auto result = testVector + value;

    //Also let's test the non-member operator
    const auto sameResult = value + testVector;

    const float eps = 1e-5;
    ASSERT_NEAR(result[0], 6.1f, eps);  ASSERT_NEAR(result[1], 7.1f, eps);  ASSERT_NEAR(result[2], 8.1f, eps);
    ASSERT_NEAR(result[3], 9.1f, eps);  ASSERT_NEAR(result[4], 10.1f, eps); ASSERT_NEAR(result[5], 11.1f, eps);
    ASSERT_NEAR(result[6], 12.1f, eps); ASSERT_NEAR(result[7], 13.1f, eps); ASSERT_NEAR(result[8], 14.1f, eps);

    ASSERT_NEAR(sameResult[0], 6.1f, eps);  ASSERT_NEAR(sameResult[1], 7.1f, eps);  ASSERT_NEAR(sameResult[2], 8.1f, eps);
    ASSERT_NEAR(sameResult[3], 9.1f, eps);  ASSERT_NEAR(sameResult[4], 10.1f, eps); ASSERT_NEAR(sameResult[5], 11.1f, eps);
    ASSERT_NEAR(sameResult[6], 12.1f, eps); ASSERT_NEAR(sameResult[7], 13.1f, eps); ASSERT_NEAR(sameResult[8], 14.1f, eps);
}

TEST_F(VectorBroadcastersTests, AdditionBroadcaster_Int_Double)
{
    const auto testVector = Vector<int>(dummyIntData);
    const double value = 5.1;
    const auto result = testVector + value;

    //Also let's test the non-member operator
    const auto sameResult = value + testVector;

    const double eps = 1e-8;
    ASSERT_NEAR(result[0], 6.1, eps);  ASSERT_NEAR(result[1], 7.1, eps);  ASSERT_NEAR(result[2], 8.1, eps);
    ASSERT_NEAR(result[3], 9.1, eps);  ASSERT_NEAR(result[4], 10.1, eps); ASSERT_NEAR(result[5], 11.1, eps);
    ASSERT_NEAR(result[6], 12.1, eps); ASSERT_NEAR(result[7], 13.1, eps); ASSERT_NEAR(result[8], 14.1, eps);

    ASSERT_NEAR(sameResult[0], 6.1, eps);  ASSERT_NEAR(sameResult[1], 7.1, eps);  ASSERT_NEAR(sameResult[2], 8.1, eps);
    ASSERT_NEAR(sameResult[3], 9.1, eps);  ASSERT_NEAR(sameResult[4], 10.1, eps); ASSERT_NEAR(sameResult[5], 11.1, eps);
    ASSERT_NEAR(sameResult[6], 12.1, eps); ASSERT_NEAR(sameResult[7], 13.1, eps); ASSERT_NEAR(sameResult[8], 14.1, eps);
}

TEST_F(VectorBroadcastersTests, AdditionBroadcaster_Float_Int)
{
    const auto testVector = Vector<float>(dummyFloatData);
    const int value = 5;
    const auto result = testVector + value;

    //Also let's test the non-member operator
    const auto sameResult = value + testVector;

    const float eps = 1e-5f;
    ASSERT_NEAR(result[0], 6.1f, eps);  ASSERT_NEAR(result[1], 8.1f, eps);  ASSERT_NEAR(result[2], 13.1f, eps);
    ASSERT_NEAR(result[3], 7.2f, eps);  ASSERT_NEAR(result[4], 12.3f, eps); ASSERT_NEAR(result[5], 11.4f, eps);
    ASSERT_NEAR(result[6], 5.2f, eps); ASSERT_NEAR(result[7], 3.5f, eps);   ASSERT_NEAR(result[8], 12.2f, eps);

    ASSERT_NEAR(sameResult[0], 6.1f, eps);  ASSERT_NEAR(sameResult[1], 8.1f, eps);  ASSERT_NEAR(sameResult[2], 13.1f, eps);
    ASSERT_NEAR(sameResult[3], 7.2f, eps);  ASSERT_NEAR(sameResult[4], 12.3f, eps); ASSERT_NEAR(sameResult[5], 11.4f, eps);
    ASSERT_NEAR(sameResult[6], 5.2f, eps); ASSERT_NEAR(sameResult[7], 3.5f, eps);   ASSERT_NEAR(sameResult[8], 12.2f, eps);
}

TEST_F(VectorBroadcastersTests, AdditionBroadcaster_Float_Float)
{
    const auto testVector = Vector<float>(dummyFloatData);
    const float value = 5.1f;
    const auto result = testVector + value;

    //Also let's test the non-member operator
    const auto sameResult = value + testVector;

    const float eps = 1e-5f;
    ASSERT_NEAR(result[0], 6.2f, eps);  ASSERT_NEAR(result[1], 8.2f, eps);  ASSERT_NEAR(result[2], 13.2f, eps);
    ASSERT_NEAR(result[3], 7.3f, eps);  ASSERT_NEAR(result[4], 12.4f, eps); ASSERT_NEAR(result[5], 11.5f, eps);
    ASSERT_NEAR(result[6], 5.3f, eps); ASSERT_NEAR(result[7], 3.6f, eps);   ASSERT_NEAR(result[8], 12.3f, eps);

    ASSERT_NEAR(sameResult[0], 6.2f, eps);  ASSERT_NEAR(sameResult[1], 8.2f, eps);  ASSERT_NEAR(sameResult[2], 13.2f, eps);
    ASSERT_NEAR(sameResult[3], 7.3f, eps);  ASSERT_NEAR(sameResult[4], 12.4f, eps); ASSERT_NEAR(sameResult[5], 11.5f, eps);
    ASSERT_NEAR(sameResult[6], 5.3f, eps); ASSERT_NEAR(sameResult[7], 3.6f, eps);   ASSERT_NEAR(sameResult[8], 12.3f, eps);
}

TEST_F(VectorBroadcastersTests, AdditionBroadcaster_Float_Double)
{
    const auto testVector = Vector<float>(dummyFloatData);
    const double value = 5.1;
    const auto result = testVector + value;

    //Also let's test the non-member operator
    const auto sameResult = value + testVector;

    const float eps = 1e-5f;
    ASSERT_NEAR(result[0], 6.2f, eps);  ASSERT_NEAR(result[1], 8.2f, eps);  ASSERT_NEAR(result[2], 13.2f, eps);
    ASSERT_NEAR(result[3], 7.3f, eps);  ASSERT_NEAR(result[4], 12.4f, eps); ASSERT_NEAR(result[5], 11.5f, eps);
    ASSERT_NEAR(result[6], 5.3f, eps); ASSERT_NEAR(result[7], 3.6f, eps);   ASSERT_NEAR(result[8], 12.3f, eps);

    ASSERT_NEAR(sameResult[0], 6.2f, eps);  ASSERT_NEAR(sameResult[1], 8.2f, eps);  ASSERT_NEAR(sameResult[2], 13.2f, eps);
    ASSERT_NEAR(sameResult[3], 7.3f, eps);  ASSERT_NEAR(sameResult[4], 12.4f, eps); ASSERT_NEAR(sameResult[5], 11.5f, eps);
    ASSERT_NEAR(sameResult[6], 5.3f, eps); ASSERT_NEAR(sameResult[7], 3.6f, eps);   ASSERT_NEAR(sameResult[8], 12.3f, eps);
}

TEST_F(VectorBroadcastersTests, AdditionBroadcaster_Double_Int)
{
    const auto testVector = Vector<double>(dummyDoubleData);
    const int value = 5;
    const auto result = testVector + value;

    //Also let's test the non-member operator
    const auto sameResult = value + testVector;

    const double eps = 1e-9;

    ASSERT_NEAR(result[0], 6.1, eps);  ASSERT_NEAR(result[1], 7.2, eps);    ASSERT_NEAR(result[2],  8.7, eps);
    ASSERT_NEAR(result[3], 9.4, eps);  ASSERT_NEAR(result[4], 10.2, eps);   ASSERT_NEAR(result[5], 11.7, eps);
    ASSERT_NEAR(result[6], 14.3, eps); ASSERT_NEAR(result[7], 13.7, eps);   ASSERT_NEAR(result[8], 12.4, eps);

    ASSERT_NEAR(sameResult[0], 6.1, eps);  ASSERT_NEAR(sameResult[1], 7.2, eps);    ASSERT_NEAR(sameResult[2],  8.7, eps);
    ASSERT_NEAR(sameResult[3], 9.4, eps);  ASSERT_NEAR(sameResult[4], 10.2, eps);   ASSERT_NEAR(sameResult[5], 11.7, eps);
    ASSERT_NEAR(sameResult[6], 14.3, eps); ASSERT_NEAR(sameResult[7], 13.7, eps);   ASSERT_NEAR(sameResult[8], 12.4, eps);
}

TEST_F(VectorBroadcastersTests, AdditionBroadcaster_Double_Float)
{
    const auto testVector = Vector<double>(dummyDoubleData);
    const float value = 5.1f;
    const auto result = testVector + value;

    //Also let's test the non-member operator
    const auto sameResult = value + testVector;

    const double eps = 1e-7;

    ASSERT_NEAR(result[0], 6.2, eps);  ASSERT_NEAR(result[1], 7.3, eps);    ASSERT_NEAR(result[2],  8.8, eps);
    ASSERT_NEAR(result[3], 9.5, eps);  ASSERT_NEAR(result[4], 10.3, eps);   ASSERT_NEAR(result[5], 11.8, eps);
    ASSERT_NEAR(result[6], 14.4, eps); ASSERT_NEAR(result[7], 13.8, eps);   ASSERT_NEAR(result[8], 12.5, eps);

    ASSERT_NEAR(sameResult[0], 6.2, eps);  ASSERT_NEAR(sameResult[1], 7.3, eps);    ASSERT_NEAR(sameResult[2],  8.8, eps);
    ASSERT_NEAR(sameResult[3], 9.5, eps);  ASSERT_NEAR(sameResult[4], 10.3, eps);   ASSERT_NEAR(sameResult[5], 11.8, eps);
    ASSERT_NEAR(sameResult[6], 14.4, eps); ASSERT_NEAR(sameResult[7], 13.8, eps);   ASSERT_NEAR(sameResult[8], 12.5, eps);
}

TEST_F(VectorBroadcastersTests, AdditionBroadcaster_Double_Double)
{
    const auto testVector = Vector<double>(dummyDoubleData);
    const double value = 5.1;
    const auto result = testVector + value;

    //Also let's test the non-member operator
    const auto sameResult = value + testVector;

    const double eps = 1e-8;

    ASSERT_NEAR(result[0], 6.2, eps);  ASSERT_NEAR(result[1], 7.3, eps);    ASSERT_NEAR(result[2],  8.8, eps);
    ASSERT_NEAR(result[3], 9.5, eps);  ASSERT_NEAR(result[4], 10.3, eps);   ASSERT_NEAR(result[5], 11.8, eps);
    ASSERT_NEAR(result[6], 14.4, eps); ASSERT_NEAR(result[7], 13.8, eps);   ASSERT_NEAR(result[8], 12.5, eps);

    ASSERT_NEAR(sameResult[0], 6.2, eps);  ASSERT_NEAR(sameResult[1], 7.3, eps);    ASSERT_NEAR(sameResult[2],  8.8, eps);
    ASSERT_NEAR(sameResult[3], 9.5, eps);  ASSERT_NEAR(sameResult[4], 10.3, eps);   ASSERT_NEAR(sameResult[5], 11.8, eps);
    ASSERT_NEAR(sameResult[6], 14.4, eps); ASSERT_NEAR(sameResult[7], 13.8, eps);   ASSERT_NEAR(sameResult[8], 12.5, eps);
}


TEST_F(VectorBroadcastersTests, SubtractionBroadcaster_Int_Int)
{
    const auto testVector = Vector<int>(dummyIntData);

    const auto result = testVector - 5;

    ASSERT_EQ(result[0], -4);  ASSERT_EQ(result[1], -3);  ASSERT_EQ(result[2], -2);
    ASSERT_EQ(result[3], -1);  ASSERT_EQ(result[4],  0);  ASSERT_EQ(result[5],  1);
    ASSERT_EQ(result[6],  2);  ASSERT_EQ(result[7], 3);   ASSERT_EQ(result[8],  4);
}


TEST_F(VectorBroadcastersTests, SubtractionBroadcaster_Int_Float)
{
    const auto testVector = Vector<int>(dummyIntData);
    const float value = 4.9f;
    const auto result = testVector - value;

    const float eps = 1e-5;
    ASSERT_NEAR(result[0], -3.9f,eps);      ASSERT_NEAR(result[1], -2.9f, eps);  ASSERT_NEAR(result[2], -1.9f, eps);
    ASSERT_NEAR(result[3], -0.9f,eps);      ASSERT_NEAR(result[4],  0.1f, eps);  ASSERT_NEAR(result[5],  1.1f, eps);
    ASSERT_NEAR(result[6],  2.1f, eps);     ASSERT_NEAR(result[7], 3.1f, eps);   ASSERT_NEAR(result[8],  4.1f, eps);
}

TEST_F(VectorBroadcastersTests, SubtractionBroadcaster_Int_Double)
{
    const auto testVector = Vector<int>(dummyIntData);
    const double value = 4.9;
    const auto result = testVector - value;

    const double eps = 1e-9;
    ASSERT_NEAR(result[0], -3.9, eps);      ASSERT_NEAR(result[1], -2.9, eps);  ASSERT_NEAR(result[2], -1.9, eps);
    ASSERT_NEAR(result[3], -0.9, eps);      ASSERT_NEAR(result[4],  0.1, eps);  ASSERT_NEAR(result[5],  1.1, eps);
    ASSERT_NEAR(result[6],  2.1, eps);      ASSERT_NEAR(result[7], 3.1, eps);   ASSERT_NEAR(result[8],  4.1, eps);
}


TEST_F(VectorBroadcastersTests, SubtractionBroadcaster_Float_Int)
{
    const auto testVector = Vector<float>(dummyFloatData);
    const int value = 1;
    const auto result = testVector - value;

    const float eps = 1e-5;
    ASSERT_NEAR(result[0], 0.1f, eps);      ASSERT_NEAR(result[1], 2.1f, eps);      ASSERT_NEAR(result[2], 7.1f, eps);
    ASSERT_NEAR(result[3], 1.2f, eps);      ASSERT_NEAR(result[4],  6.3f, eps);     ASSERT_NEAR(result[5],  5.4f, eps);
    ASSERT_NEAR(result[6],  -0.8f, eps);    ASSERT_NEAR(result[7], -2.5f, eps);     ASSERT_NEAR(result[8],  6.2f, eps);
}

TEST_F(VectorBroadcastersTests, SubtractionBroadcaster_Float_Float)
{
    const auto testVector = Vector<float>(dummyFloatData);
    const float value = 0.9f;
    const auto result = testVector - value;

    const float eps = 1e-5;
    ASSERT_NEAR(result[0], 0.2f, eps);      ASSERT_NEAR(result[1], 2.2f, eps);      ASSERT_NEAR(result[2], 7.2f, eps);
    ASSERT_NEAR(result[3], 1.3f, eps);      ASSERT_NEAR(result[4],  6.4f, eps);     ASSERT_NEAR(result[5],  5.5f, eps);
    ASSERT_NEAR(result[6],  -0.7f, eps);    ASSERT_NEAR(result[7], -2.4f, eps);     ASSERT_NEAR(result[8],  6.3f, eps);
}

TEST_F(VectorBroadcastersTests, SubtractionBroadcaster_Float_Double)
{
    const auto testVector = Vector<float>(dummyFloatData);
    const double value = 0.8;
    const auto result = testVector - value;

    const double eps = 1e-6;
    ASSERT_NEAR(result[0], 0.3f, eps);      ASSERT_NEAR(result[1], 2.3f, eps);      ASSERT_NEAR(result[2], 7.3f, eps);
    ASSERT_NEAR(result[3], 1.4f, eps);      ASSERT_NEAR(result[4],  6.5f, eps);     ASSERT_NEAR(result[5],  5.6f, eps);
    ASSERT_NEAR(result[6],  -0.6f, eps);    ASSERT_NEAR(result[7], -2.3f, eps);     ASSERT_NEAR(result[8],  6.4f, eps);
}

TEST_F(VectorBroadcastersTests, SubtractionBroadcaster_Double_Int)
{
    const auto testVector = Vector<double>(dummyDoubleData);
    const int value = 1;
    const auto result = testVector - value;

    const double eps = 1e-9;
    ASSERT_NEAR(result[0], 0.1, eps);      ASSERT_NEAR(result[1], 1.2, eps);      ASSERT_NEAR(result[2], 2.7, eps);
    ASSERT_NEAR(result[3], 3.4, eps);      ASSERT_NEAR(result[4],  4.2, eps);     ASSERT_NEAR(result[5],  5.7, eps);
    ASSERT_NEAR(result[6],  8.3, eps);     ASSERT_NEAR(result[7], 7.7, eps);      ASSERT_NEAR(result[8],  6.4, eps);
}

TEST_F(VectorBroadcastersTests, SubtractionBroadcaster_Double_Float)
{
    const auto testVector = Vector<double>(dummyDoubleData);
    const float value = 0.9f;
    const auto result = testVector - value;

    const double eps = 1e-6;
    ASSERT_NEAR(result[0], 0.2, eps);      ASSERT_NEAR(result[1], 1.3, eps);      ASSERT_NEAR(result[2], 2.8, eps);
    ASSERT_NEAR(result[3], 3.5, eps);      ASSERT_NEAR(result[4],  4.3, eps);     ASSERT_NEAR(result[5],  5.8, eps);
    ASSERT_NEAR(result[6],  8.4, eps);     ASSERT_NEAR(result[7], 7.8, eps);      ASSERT_NEAR(result[8],  6.5, eps);
}

TEST_F(VectorBroadcastersTests, SubtractionBroadcaster_Double_Double)
{
    const auto testVector = Vector<double>(dummyDoubleData);
    const double value = 0.8;
    const auto result = testVector - value;

    const double eps = 1e-9;
    ASSERT_NEAR(result[0], 0.3, eps);      ASSERT_NEAR(result[1], 1.4, eps);      ASSERT_NEAR(result[2], 2.9, eps);
    ASSERT_NEAR(result[3], 3.6, eps);      ASSERT_NEAR(result[4],  4.4, eps);     ASSERT_NEAR(result[5],  5.9, eps);
    ASSERT_NEAR(result[6],  8.5, eps);     ASSERT_NEAR(result[7], 7.9, eps);      ASSERT_NEAR(result[8],  6.6, eps);
}


TEST_F(VectorBroadcastersTests, MultiplicationBroadcaster_Int_Int)
{
    const auto testVector = Vector<int>(dummyIntData);

    const auto result = testVector * 5;

    //Also let's test the non-member operator
    const auto sameResult = 5 * testVector;

    ASSERT_EQ(result[0], 5);      ASSERT_EQ(result[1], 10);     ASSERT_EQ(result[2], 15);
    ASSERT_EQ(result[3], 20);     ASSERT_EQ(result[4], 25);     ASSERT_EQ(result[5], 30);
    ASSERT_EQ(result[6], 35);     ASSERT_EQ(result[7], 40);     ASSERT_EQ(result[8], 45);

    ASSERT_EQ(sameResult[0], 5);      ASSERT_EQ(sameResult[1], 10);     ASSERT_EQ(sameResult[2], 15);
    ASSERT_EQ(sameResult[3], 20);     ASSERT_EQ(sameResult[4], 25);     ASSERT_EQ(sameResult[5], 30);
    ASSERT_EQ(sameResult[6], 35);     ASSERT_EQ(sameResult[7], 40);     ASSERT_EQ(sameResult[8], 45);
}

TEST_F(VectorBroadcastersTests, MultiplicationBroadcaster_Int_Float)
{
    const auto testVector = Vector<int>(dummyIntData);
    const float value = 5.0f;
    const auto result = testVector * value;

    //Also let's test the non-member operator
    const auto sameResult = value * testVector;

    const float eps = 1e-5;
    ASSERT_NEAR(result[0], 5.f, eps);      ASSERT_NEAR(result[1], 10.f, eps);     ASSERT_NEAR(result[2], 15.f, eps);
    ASSERT_NEAR(result[3], 20.f, eps);     ASSERT_NEAR(result[4], 25.f, eps);     ASSERT_NEAR(result[5], 30.f, eps);
    ASSERT_NEAR(result[6], 35.f, eps);     ASSERT_NEAR(result[7], 40.f, eps);     ASSERT_NEAR(result[8], 45.f, eps);

    ASSERT_NEAR(sameResult[0], 5.f, eps);      ASSERT_NEAR(sameResult[1], 10.f, eps);     ASSERT_NEAR(sameResult[2], 15.f, eps);
    ASSERT_NEAR(sameResult[3], 20.f, eps);     ASSERT_NEAR(sameResult[4], 25.f, eps);     ASSERT_NEAR(sameResult[5], 30.f, eps);
    ASSERT_NEAR(sameResult[6], 35.f, eps);     ASSERT_NEAR(sameResult[7], 40.f, eps);     ASSERT_NEAR(sameResult[8], 45.f, eps);
}

TEST_F(VectorBroadcastersTests, MultiplicationBroadcaster_Int_Double)
{
    const auto testVector = Vector<int>(dummyIntData);
    const double value = 5.0;
    const auto result = testVector * value;

    //Also let's test the non-member operator
    const auto sameResult = value * testVector;

    const double eps = 1e-9;
    ASSERT_NEAR(result[0], 5., eps);      ASSERT_NEAR(result[1], 10., eps);     ASSERT_NEAR(result[2], 15., eps);
    ASSERT_NEAR(result[3], 20., eps);     ASSERT_NEAR(result[4], 25., eps);     ASSERT_NEAR(result[5], 30., eps);
    ASSERT_NEAR(result[6], 35., eps);     ASSERT_NEAR(result[7], 40., eps);     ASSERT_NEAR(result[8], 45., eps);

    ASSERT_NEAR(sameResult[0], 5., eps);      ASSERT_NEAR(sameResult[1], 10., eps);     ASSERT_NEAR(sameResult[2], 15., eps);
    ASSERT_NEAR(sameResult[3], 20., eps);     ASSERT_NEAR(sameResult[4], 25., eps);     ASSERT_NEAR(sameResult[5], 30., eps);
    ASSERT_NEAR(sameResult[6], 35., eps);     ASSERT_NEAR(sameResult[7], 40., eps);     ASSERT_NEAR(sameResult[8], 45., eps);
}

TEST_F(VectorBroadcastersTests, MultiplicationBroadcaster_Float_Int)
{
    const auto testVector = Vector<float>(dummyFloatData);
    const int value = 2;
    const auto result = testVector * value;

    //Also let's test the non-member operator
    const auto sameResult = value * testVector;

    const float eps = 1e-5;

    ASSERT_NEAR(result[0], 2.2f, eps);      ASSERT_NEAR(result[1], 6.2f, eps);     ASSERT_NEAR(result[2], 16.2f, eps);
    ASSERT_NEAR(result[3], 4.4f, eps);     ASSERT_NEAR(result[4], 14.6f, eps);     ASSERT_NEAR(result[5], 12.8f, eps);
    ASSERT_NEAR(result[6], 0.4f, eps);     ASSERT_NEAR(result[7], -3.0f, eps);     ASSERT_NEAR(result[8], 14.4f, eps);

    ASSERT_NEAR(sameResult[0], 2.2f, eps);      ASSERT_NEAR(sameResult[1], 6.2f, eps);     ASSERT_NEAR(sameResult[2], 16.2f, eps);
    ASSERT_NEAR(sameResult[3], 4.4f, eps);     ASSERT_NEAR(sameResult[4], 14.6f, eps);     ASSERT_NEAR(sameResult[5], 12.8f, eps);
    ASSERT_NEAR(sameResult[6], 0.4f, eps);     ASSERT_NEAR(sameResult[7], -3.0f, eps);     ASSERT_NEAR(sameResult[8], 14.4f, eps);
}

TEST_F(VectorBroadcastersTests, MultiplicationBroadcaster_Float_Float)
{
    const auto testVector = Vector<float>(dummyFloatData);
    const float value = 2.5f;
    const auto result = testVector * value;

    //Also let's test the non-member operator
    const auto sameResult = value * testVector;

    const float eps = 1e-5;

    ASSERT_NEAR(result[0], 2.75f, eps);     ASSERT_NEAR(result[1], 7.75f, eps);         ASSERT_NEAR(result[2], 20.25f, eps);
    ASSERT_NEAR(result[3], 5.5f, eps);      ASSERT_NEAR(result[4], 18.25f, eps);        ASSERT_NEAR(result[5], 16.f, eps);
    ASSERT_NEAR(result[6], 0.5f, eps);      ASSERT_NEAR(result[7], -3.75f, eps);        ASSERT_NEAR(result[8], 18.f, eps);

    ASSERT_NEAR(sameResult[0], 2.75f, eps);     ASSERT_NEAR(sameResult[1], 7.75f, eps);         ASSERT_NEAR(sameResult[2], 20.25f, eps);
    ASSERT_NEAR(sameResult[3], 5.5f, eps);      ASSERT_NEAR(sameResult[4], 18.25f, eps);        ASSERT_NEAR(sameResult[5], 16.f, eps);
    ASSERT_NEAR(sameResult[6], 0.5f, eps);      ASSERT_NEAR(sameResult[7], -3.75f, eps);        ASSERT_NEAR(sameResult[8], 18.f, eps);
}

TEST_F(VectorBroadcastersTests, MultiplicationBroadcaster_Float_Double)
{
    const auto testVector = Vector<float>(dummyFloatData);
    const double value = 2.5;
    const auto result = testVector * value;

    //Also let's test the non-member operator
    const auto sameResult = value * testVector;

    const double eps = 1e-6;

    ASSERT_NEAR(result[0], 2.75, eps);      ASSERT_NEAR(result[1], 7.75, eps);      ASSERT_NEAR(result[2], 20.25, eps);
    ASSERT_NEAR(result[3], 5.5, eps);       ASSERT_NEAR(result[4], 18.25, eps);     ASSERT_NEAR(result[5], 16., eps);
    ASSERT_NEAR(result[6], 0.5, eps);       ASSERT_NEAR(result[7], -3.75, eps);     ASSERT_NEAR(result[8], 18., eps);

    ASSERT_NEAR(sameResult[0], 2.75, eps);      ASSERT_NEAR(sameResult[1], 7.75, eps);      ASSERT_NEAR(sameResult[2], 20.25, eps);
    ASSERT_NEAR(sameResult[3], 5.5, eps);       ASSERT_NEAR(sameResult[4], 18.25, eps);     ASSERT_NEAR(sameResult[5], 16., eps);
    ASSERT_NEAR(sameResult[6], 0.5, eps);       ASSERT_NEAR(sameResult[7], -3.75, eps);     ASSERT_NEAR(sameResult[8], 18., eps);
}

TEST_F(VectorBroadcastersTests, MultiplicationBroadcaster_Double_Int)
{
    const auto testVector = Vector<double>(dummyDoubleData);
    const int value = 2;
    const auto result = testVector * value;

    //Also let's test the non-member operator
    const auto sameResult = value * testVector;

    const double eps = 1e-9;

    ASSERT_NEAR(result[0], 2.2, eps);       ASSERT_NEAR(result[1], 4.4, eps);       ASSERT_NEAR(result[2], 7.4, eps);
    ASSERT_NEAR(result[3], 8.8, eps);       ASSERT_NEAR(result[4], 10.4, eps);      ASSERT_NEAR(result[5], 13.4, eps);
    ASSERT_NEAR(result[6], 18.6, eps);      ASSERT_NEAR(result[7], 17.4, eps);      ASSERT_NEAR(result[8], 14.8, eps);

    ASSERT_NEAR(sameResult[0], 2.2, eps);       ASSERT_NEAR(sameResult[1], 4.4, eps);       ASSERT_NEAR(sameResult[2], 7.4, eps);
    ASSERT_NEAR(sameResult[3], 8.8, eps);       ASSERT_NEAR(sameResult[4], 10.4, eps);      ASSERT_NEAR(sameResult[5], 13.4, eps);
    ASSERT_NEAR(sameResult[6], 18.6, eps);      ASSERT_NEAR(sameResult[7], 17.4, eps);      ASSERT_NEAR(sameResult[8], 14.8, eps);
}

TEST_F(VectorBroadcastersTests, MultiplicationBroadcaster_Double_Float)
{
    const auto testVector = Vector<double>(dummyDoubleData);
    const float value = 2.5f;
    const auto result = testVector * value;

    //Also let's test the non-member operator
    const auto sameResult = value * testVector;

    const double eps = 1e-7;

    ASSERT_NEAR(result[0], 2.75, eps);      ASSERT_NEAR(result[1], 5.5, eps);       ASSERT_NEAR(result[2], 9.25, eps);
    ASSERT_NEAR(result[3], 11, eps);        ASSERT_NEAR(result[4], 13, eps);        ASSERT_NEAR(result[5], 16.75, eps);
    ASSERT_NEAR(result[6], 23.25, eps);     ASSERT_NEAR(result[7], 21.75, eps);     ASSERT_NEAR(result[8], 18.5, eps);

    ASSERT_NEAR(sameResult[0], 2.75, eps);      ASSERT_NEAR(sameResult[1], 5.5, eps);       ASSERT_NEAR(sameResult[2], 9.25, eps);
    ASSERT_NEAR(sameResult[3], 11, eps);        ASSERT_NEAR(sameResult[4], 13, eps);        ASSERT_NEAR(sameResult[5], 16.75, eps);
    ASSERT_NEAR(sameResult[6], 23.25, eps);     ASSERT_NEAR(sameResult[7], 21.75, eps);     ASSERT_NEAR(sameResult[8], 18.5, eps);
}

TEST_F(VectorBroadcastersTests, MultiplicationBroadcaster_Double_Double)
{
    const auto testVector = Vector<double>(dummyDoubleData);
    const double value = 2.5;
    const auto result = testVector * value;

    //Also let's test the non-member operator
    const auto sameResult = value * testVector;

    const double eps = 1e-9;

    ASSERT_NEAR(result[0], 2.75, eps);      ASSERT_NEAR(result[1], 5.5, eps);       ASSERT_NEAR(result[2], 9.25, eps);
    ASSERT_NEAR(result[3], 11, eps);        ASSERT_NEAR(result[4], 13, eps);        ASSERT_NEAR(result[5], 16.75, eps);
    ASSERT_NEAR(result[6], 23.25, eps);     ASSERT_NEAR(result[7], 21.75, eps);     ASSERT_NEAR(result[8], 18.5, eps);

    ASSERT_NEAR(sameResult[0], 2.75, eps);      ASSERT_NEAR(sameResult[1], 5.5, eps);       ASSERT_NEAR(sameResult[2], 9.25, eps);
    ASSERT_NEAR(sameResult[3], 11, eps);        ASSERT_NEAR(sameResult[4], 13, eps);        ASSERT_NEAR(sameResult[5], 16.75, eps);
    ASSERT_NEAR(sameResult[6], 23.25, eps);     ASSERT_NEAR(sameResult[7], 21.75, eps);     ASSERT_NEAR(sameResult[8], 18.5, eps);
}

TEST_F(VectorBroadcastersTests, DivisionBroadcaster_Int_Int)
{
    dummyIntData = std::vector<int>{3, 6, 9,
                                12, 15, 18,
                                21, 24, 27};

    const auto testVector = Vector<int>(dummyIntData);

    const auto result = testVector / 3;

    ASSERT_EQ(result[0], 1);  ASSERT_EQ(result[1], 2);  ASSERT_EQ(result[2], 3);
    ASSERT_EQ(result[3], 4);  ASSERT_EQ(result[4], 5);  ASSERT_EQ(result[5], 6);
    ASSERT_EQ(result[6], 7);  ASSERT_EQ(result[7], 8);  ASSERT_EQ(result[8], 9);

    ASSERT_THROW(testVector/0, std::invalid_argument);

    const auto castedResult = testVector / 2;
    ASSERT_EQ(castedResult[0], 1);   ASSERT_EQ(castedResult[1], 3);   ASSERT_EQ(castedResult[2], 4);
    ASSERT_EQ(castedResult[3], 6);   ASSERT_EQ(castedResult[4], 7);   ASSERT_EQ(castedResult[5], 9);
    ASSERT_EQ(castedResult[6], 10);  ASSERT_EQ(castedResult[7], 12);  ASSERT_EQ(castedResult[8], 13);
}

TEST_F(VectorBroadcastersTests, DivisionBroadcaster_Int_Float)
{
    const auto testVector = Vector<int>(dummyIntData);

    const auto result = testVector / 2.5f;

    const float eps = 1e-6;

    ASSERT_NEAR(result[0], 0.4f, eps);      ASSERT_NEAR(result[1], 0.8f, eps);      ASSERT_NEAR(result[2], 1.2f, eps);
    ASSERT_NEAR(result[3], 1.6f, eps);      ASSERT_NEAR(result[4], 2.f, eps);       ASSERT_NEAR(result[5], 2.4f, eps);
    ASSERT_NEAR(result[6], 2.8f, eps);      ASSERT_NEAR(result[7], 3.2f, eps);      ASSERT_NEAR(result[8], 3.6f, eps);
}

TEST_F(VectorBroadcastersTests, DivisionBroadcaster_Int_Double)
{
    const auto testVector = Vector<int>(dummyIntData);

    const auto result = testVector / 2.4;

    const double eps = 1e-9;

    ASSERT_NEAR(result[0], 0.416666666666667, eps);     ASSERT_NEAR(result[1], 0.833333333333333, eps);     ASSERT_NEAR(result[2], 1.25, eps);
    ASSERT_NEAR(result[3], 1.66666666666667, eps);      ASSERT_NEAR(result[4], 2.08333333333333, eps);      ASSERT_NEAR(result[5], 2.5, eps);
    ASSERT_NEAR(result[6], 2.91666666666667, eps);      ASSERT_NEAR(result[7], 3.33333333333333, eps);      ASSERT_NEAR(result[8], 3.75, eps);
}

TEST_F(VectorBroadcastersTests, DivisionBroadcaster_Float_Int)
{
    const auto testVector = Vector<float>(dummyFloatData);

    const auto result = testVector / 2;

    const float eps = 1e-6;

    ASSERT_NEAR(result[0], 0.55f, eps);      ASSERT_NEAR(result[1], 1.55f, eps);      ASSERT_NEAR(result[2], 4.05f, eps);
    ASSERT_NEAR(result[3], 1.1f, eps);      ASSERT_NEAR(result[4], 3.65f, eps);       ASSERT_NEAR(result[5], 3.2f, eps);
    ASSERT_NEAR(result[6], 0.1f, eps);      ASSERT_NEAR(result[7], -0.75f, eps);      ASSERT_NEAR(result[8], 3.6f, eps);
}

TEST_F(VectorBroadcastersTests, DivisionBroadcaster_Float_Float)
{
    const auto testVector = Vector<float>(dummyFloatData);

    const auto result = testVector / 2.5f;

    const float eps = 1e-6;

    ASSERT_NEAR(result[0], 0.44f, eps);      ASSERT_NEAR(result[1], 1.24f, eps);        ASSERT_NEAR(result[2], 3.24f, eps);
    ASSERT_NEAR(result[3], 0.88f, eps);      ASSERT_NEAR(result[4], 2.92f, eps);        ASSERT_NEAR(result[5], 2.56f, eps);
    ASSERT_NEAR(result[6], 0.08f, eps);      ASSERT_NEAR(result[7], -0.6f, eps);        ASSERT_NEAR(result[8], 2.88f, eps);
}

TEST_F(VectorBroadcastersTests, DivisionBroadcaster_Float_Double)
{
    const auto testVector = Vector<float>(dummyFloatData);

    const auto result = testVector / 2.5;

    const double eps = 1e-6;

    ASSERT_NEAR(result[0], 0.44, eps);      ASSERT_NEAR(result[1], 1.24, eps);        ASSERT_NEAR(result[2], 3.24, eps);
    ASSERT_NEAR(result[3], 0.88, eps);      ASSERT_NEAR(result[4], 2.92, eps);        ASSERT_NEAR(result[5], 2.56, eps);
    ASSERT_NEAR(result[6], 0.08, eps);      ASSERT_NEAR(result[7], -0.6, eps);        ASSERT_NEAR(result[8], 2.88, eps);
}

TEST_F(VectorBroadcastersTests, DivisionBroadcaster_Double_Int)
{
    const auto testVector = Vector<double>(dummyDoubleData);

    const auto result = testVector / 2;

    const double eps = 1e-9;

    ASSERT_NEAR(result[0], 0.55, eps);      ASSERT_NEAR(result[1], 1.1, eps);       ASSERT_NEAR(result[2], 1.85, eps);
    ASSERT_NEAR(result[3], 2.2, eps);       ASSERT_NEAR(result[4], 2.6, eps);       ASSERT_NEAR(result[5], 3.35, eps);
    ASSERT_NEAR(result[6], 4.65, eps);      ASSERT_NEAR(result[7], 4.35, eps);      ASSERT_NEAR(result[8], 3.7, eps);
}

TEST_F(VectorBroadcastersTests, DivisionBroadcaster_Double_Float)
{
    const auto testVector = Vector<double>(dummyDoubleData);

    const auto result = testVector / 2.5f;

    const double eps = 1e-9;

    ASSERT_NEAR(result[0], 0.44, eps);      ASSERT_NEAR(result[1], 0.88, eps);      ASSERT_NEAR(result[2], 1.48, eps);
    ASSERT_NEAR(result[3], 1.76, eps);      ASSERT_NEAR(result[4], 2.08, eps);      ASSERT_NEAR(result[5], 2.68, eps);
    ASSERT_NEAR(result[6], 3.72, eps);      ASSERT_NEAR(result[7], 3.48, eps);      ASSERT_NEAR(result[8], 2.96, eps);
}

TEST_F(VectorBroadcastersTests, DivisionBroadcaster_Double_Double)
{
    const auto testVector = Vector<double>(dummyDoubleData);

    const auto result = testVector / 2.31;

    const double eps = 1e-9;

    ASSERT_NEAR(result[0], 0.476190476190476, eps);     ASSERT_NEAR(result[1], 0.952380952380952, eps);     ASSERT_NEAR(result[2], 1.6017316017316, eps);
    ASSERT_NEAR(result[3], 1.90476190476191, eps);      ASSERT_NEAR(result[4], 2.25108225108225, eps);      ASSERT_NEAR(result[5], 2.9004329004329, eps);
    ASSERT_NEAR(result[6], 4.02597402597403, eps);      ASSERT_NEAR(result[7], 3.76623376623377, eps);      ASSERT_NEAR(result[8], 3.2034632034632, eps);
}

TEST_F(VectorBroadcastersTests, InPlaceAdditionBroadcaster)
{
auto result = Vector<int>(dummyIntData);

result += 5;

ASSERT_EQ(result[0], 6);  ASSERT_EQ(result[1], 7);  ASSERT_EQ(result[2], 8);
ASSERT_EQ(result[3], 9);  ASSERT_EQ(result[4], 10); ASSERT_EQ(result[5], 11);
ASSERT_EQ(result[6], 12); ASSERT_EQ(result[7], 13); ASSERT_EQ(result[8], 14);
}

TEST_F(VectorBroadcastersTests, InPlaceSubtractionBroadcaster)
{
auto result = Vector<int>(dummyIntData);

result -= 5;

ASSERT_EQ(result[0], -4);  ASSERT_EQ(result[1], -3);  ASSERT_EQ(result[2], -2);
ASSERT_EQ(result[3], -1);  ASSERT_EQ(result[4],  0);  ASSERT_EQ(result[5],  1);
ASSERT_EQ(result[6],  2);  ASSERT_EQ(result[7], 3);   ASSERT_EQ(result[8],  4);
}

TEST_F(VectorBroadcastersTests, InPlaceMultiplicationBroadcaster)
{
auto result = Vector<int>(dummyIntData);

result *= 5;

ASSERT_EQ(result[0], 5);      ASSERT_EQ(result[1], 10);     ASSERT_EQ(result[2], 15);
ASSERT_EQ(result[3], 20);     ASSERT_EQ(result[4], 25);     ASSERT_EQ(result[5], 30);
ASSERT_EQ(result[6], 35);     ASSERT_EQ(result[7], 40);     ASSERT_EQ(result[8], 45);
}

TEST_F(VectorBroadcastersTests, InPlaceDivisionBroadcaster)
{
dummyIntData = std::vector<int>{3, 6, 9,
                                12, 15, 18,
                                21, 24, 27};
auto result = Vector<int>(dummyIntData);

result /= 3;

ASSERT_EQ(result[0], 1);  ASSERT_EQ(result[1], 2);  ASSERT_EQ(result[2], 3);
ASSERT_EQ(result[3], 4);  ASSERT_EQ(result[4], 5);  ASSERT_EQ(result[5], 6);
ASSERT_EQ(result[6], 7);  ASSERT_EQ(result[7], 8);  ASSERT_EQ(result[8], 9);

ASSERT_THROW(result/0, std::invalid_argument);
}