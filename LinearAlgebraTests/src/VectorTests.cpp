//
// Created by dorian on 07.11.2023.
// stoicadorian@gmail.com
//
#include "gtest/gtest.h"
#include "Vector.hpp"

class VectorTests : public ::testing::Test
{

protected:
    virtual void SetUp()
    {
        dummyIntData = std::vector<int>{1, 2, 3,
                                        4, 5, 6,
                                        7, 8, 9};

        dummyFloatData = std::vector<float>{1.f, 3.f, 8.f,
                                            2.f, 7.f, 6.f,
                                            0.f, -1.f, 7.f};
        dummyDoubleData = std::vector<double>{1.0, 2.0, 3.0,
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


TEST_F(VectorTests, SimpleConstructor)
{
    ASSERT_NO_THROW(Vector<int>(3));
    ASSERT_NO_THROW(Vector<double>(4));
}

TEST_F(VectorTests, STLVectorConstructor)
{
    ASSERT_NO_THROW(const auto vec = Vector<int>(dummyIntData));
    ASSERT_NO_THROW(const auto vec = Vector<double>(dummyDoubleData));
}

TEST_F(VectorTests, CopyConstructor)
{
    const auto testVec = Vector<float>(dummyFloatData);
    const auto otherVec(testVec);

    ASSERT_EQ(otherVec.dim(), 9);

    ASSERT_EQ(otherVec[0], 1.f);  ASSERT_EQ(otherVec[1], 3.f);   ASSERT_EQ(otherVec[2], 8.f);
    ASSERT_EQ(otherVec[3], 2.f);  ASSERT_EQ(otherVec[4], 7.f);   ASSERT_EQ(otherVec[5], 6.f);
    ASSERT_EQ(otherVec[6], 0.f);  ASSERT_EQ(otherVec[7], -1.f);  ASSERT_EQ(otherVec[8], 7.f);
}

TEST_F(VectorTests, MoveConstructor)
{
    auto testVec = Vector<float>(dummyFloatData);
    const auto otherVec(std::move(testVec));

    ASSERT_EQ(otherVec[0], 1.f);  ASSERT_EQ(otherVec[1], 3.f);   ASSERT_EQ(otherVec[2], 8.f);
    ASSERT_EQ(otherVec[3], 2.f);  ASSERT_EQ(otherVec[4], 7.f);   ASSERT_EQ(otherVec[5], 6.f);
    ASSERT_EQ(otherVec[6], 0.f);  ASSERT_EQ(otherVec[7], -1.f);  ASSERT_EQ(otherVec[8], 7.f);

    ASSERT_EQ(testVec.dim(), 0);
}

TEST_F(VectorTests, CopyAssignment)
{
    auto otherVec = Vector<float>(2);

    const auto testVec = Vector<float>(dummyFloatData);

    otherVec = testVec;

    ASSERT_EQ(otherVec[0], 1.f);  ASSERT_EQ(otherVec[1], 3.f);   ASSERT_EQ(otherVec[2], 8.f);
    ASSERT_EQ(otherVec[3], 2.f);  ASSERT_EQ(otherVec[4], 7.f);   ASSERT_EQ(otherVec[5], 6.f);
    ASSERT_EQ(otherVec[6], 0.f);  ASSERT_EQ(otherVec[7], -1.f);  ASSERT_EQ(otherVec[8], 7.f);
}

TEST_F(VectorTests, MoveAssignment)
{
    auto otherVec = Vector<float>(2);

    auto testVec = Vector<float>(dummyFloatData);
    otherVec = std::move(testVec);

    ASSERT_EQ(otherVec[0], 1.f);  ASSERT_EQ(otherVec[1], 3.f);   ASSERT_EQ(otherVec[2], 8.f);
    ASSERT_EQ(otherVec[3], 2.f);  ASSERT_EQ(otherVec[4], 7.f);   ASSERT_EQ(otherVec[5], 6.f);
    ASSERT_EQ(otherVec[6], 0.f);  ASSERT_EQ(otherVec[7], -1.f);  ASSERT_EQ(otherVec[8], 7.f);

    ASSERT_EQ(testVec.dim(), 0);
}

TEST_F(VectorTests, GetIndividualValues)
{
    const auto testVec = Vector<double>(dummyDoubleData);

    ASSERT_EQ(testVec[0], 1.0);   ASSERT_EQ(testVec[1], 2.0);   ASSERT_EQ(testVec[2], 3.0);
    ASSERT_EQ(testVec[3], 4.0);   ASSERT_EQ(testVec[4], 5.0);   ASSERT_EQ(testVec[5], 6.0);
    ASSERT_EQ(testVec[6], 9.0);   ASSERT_EQ(testVec[7], 8.0);   ASSERT_EQ(testVec[8], 7.0);

    EXPECT_ANY_THROW(testVec[11]);
}

TEST_F(VectorTests, BeginAndEnd)
{
    const auto testVec = Vector<double>(dummyDoubleData);

    const auto itBegin = testVec.begin();
    const auto itEnd   = testVec.end();

    ASSERT_EQ(*itBegin,      1.0);
    ASSERT_EQ(*(itEnd -1),   7.0);
}

TEST_F(VectorTests, SetIndividualValues)
{
    auto testVec = Vector<int>(5);
    testVec[0] = 1;   testVec[1] = 11;  testVec[2] = 21;
    testVec[3] = 2;   testVec[4] = 3;

    ASSERT_THROW(testVec[6] = 12, std::invalid_argument);

    ASSERT_EQ(testVec[0], 1);     ASSERT_EQ(testVec[1], 11);    ASSERT_EQ(testVec[2], 21);
    ASSERT_EQ(testVec[3], 2);     ASSERT_EQ(testVec[4], 3);
}

TEST_F(VectorTests, VectorAddition)
{
    const auto testVec = Vector<double>(dummyDoubleData);
    const auto otherVec(testVec);

    const auto result = testVec + otherVec;

    ASSERT_EQ(result[0], 2.0);    ASSERT_EQ(result[1], 4.0);    ASSERT_EQ(result[2], 6.0);
    ASSERT_EQ(result[3], 8.0);    ASSERT_EQ(result[4], 10.0);   ASSERT_EQ(result[5], 12.0);
    ASSERT_EQ(result[6], 18.0);   ASSERT_EQ(result[7], 16.0);   ASSERT_EQ(result[8], 14.0);
}

TEST_F(VectorTests, VectorSubtraction)
{
    const auto testVec = Vector<double>(dummyDoubleData);
    const auto otherVec(testVec);

    const auto result = testVec - otherVec;

    ASSERT_EQ(result[0], 0.0);    ASSERT_EQ(result[1], 0.0);    ASSERT_EQ(result[2], 0.0);
    ASSERT_EQ(result[3], 0.0);    ASSERT_EQ(result[4], 0.0);    ASSERT_EQ(result[5], 0.0);
    ASSERT_EQ(result[6], 0.0);    ASSERT_EQ(result[7], 0.0);    ASSERT_EQ(result[8], 0.0);
}

TEST_F(VectorTests, ElementWiseVectorMultiplication)
{
    const auto testVec = Vector<double>(dummyDoubleData);

    const auto result = testVec * testVec;

    ASSERT_EQ(result[0], 1.0);    ASSERT_EQ(result[1], 4.0);    ASSERT_EQ(result[2], 9.0);
    ASSERT_EQ(result[3], 16.0);   ASSERT_EQ(result[4], 25.0);   ASSERT_EQ(result[5], 36.0);
    ASSERT_EQ(result[6], 81.0);   ASSERT_EQ(result[7], 64.0);   ASSERT_EQ(result[8], 49.0);
}

TEST_F(VectorTests, ElementWiseVectorDivision)
{
    const auto testVec = Vector<double>(dummyDoubleData);

    const auto result = testVec / testVec;

    ASSERT_EQ(result[0], 1.0);    ASSERT_EQ(result[1],1.0);    ASSERT_EQ(result[2], 1.0);
    ASSERT_EQ(result[3], 1.0);   ASSERT_EQ(result[4], 1.0);   ASSERT_EQ(result[5], 1.0);
    ASSERT_EQ(result[6], 1.0);   ASSERT_EQ(result[7], 1.0);   ASSERT_EQ(result[8], 1.0);

    auto divizorWithZeros = testVec;  divizorWithZeros[0] = 0;

    ASSERT_THROW(testVec/divizorWithZeros, std::invalid_argument);
}

TEST_F(VectorTests, InPlaceVectorAddition)
{
    const auto testVec = Vector<double>(dummyDoubleData);
    auto result(testVec);

    result += testVec;

    ASSERT_EQ(result[0], 2.0);    ASSERT_EQ(result[1], 4.0);    ASSERT_EQ(result[2], 6.0);
    ASSERT_EQ(result[3], 8.0);    ASSERT_EQ(result[4], 10.0);   ASSERT_EQ(result[5], 12.0);
    ASSERT_EQ(result[6], 18.0);   ASSERT_EQ(result[7], 16.0);   ASSERT_EQ(result[8], 14.0);
}

TEST_F(VectorTests, InPlaceVectorSubtraction)
{
    const auto testVec = Vector<double>(dummyDoubleData);
    auto result(testVec);

    result -= testVec;

    ASSERT_EQ(result[0], 0.0);    ASSERT_EQ(result[1], 0.0);    ASSERT_EQ(result[2], 0.0);
    ASSERT_EQ(result[3], 0.0);    ASSERT_EQ(result[4], 0.0);    ASSERT_EQ(result[5], 0.0);
    ASSERT_EQ(result[6], 0.0);    ASSERT_EQ(result[7], 0.0);    ASSERT_EQ(result[8], 0.0);
}

TEST_F(VectorTests, InPlaceElementWiseVectorMultiplication)
{
    auto result = Vector<double>(dummyDoubleData);

    result *= result;

    ASSERT_EQ(result[0], 1.0);    ASSERT_EQ(result[1], 4.0);    ASSERT_EQ(result[2], 9.0);
    ASSERT_EQ(result[3], 16.0);   ASSERT_EQ(result[4], 25.0);   ASSERT_EQ(result[5], 36.0);
    ASSERT_EQ(result[6], 81.0);   ASSERT_EQ(result[7], 64.0);   ASSERT_EQ(result[8], 49.0);
}

TEST_F(VectorTests, InPlaceElementWiseVectorDivision)
{
    auto result = Vector<double>(dummyDoubleData);

    result /= result;

    ASSERT_EQ(result[0], 1.0);    ASSERT_EQ(result[1],1.0);    ASSERT_EQ(result[2], 1.0);
    ASSERT_EQ(result[3], 1.0);   ASSERT_EQ(result[4], 1.0);   ASSERT_EQ(result[5], 1.0);
    ASSERT_EQ(result[6], 1.0);   ASSERT_EQ(result[7], 1.0);   ASSERT_EQ(result[8], 1.0);

    auto divizorWithZeros = result;  divizorWithZeros[2] = 0;

    ASSERT_THROW(result/=divizorWithZeros, std::invalid_argument);
}

TEST_F(VectorTests, AdditionBroadcaster)
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

TEST_F(VectorTests, SubtractionBroadcaster)
{
    const auto testVector = Vector<int>(dummyIntData);

    const auto result = testVector - 5;

    ASSERT_EQ(result[0], -4);  ASSERT_EQ(result[1], -3);  ASSERT_EQ(result[2], -2);
    ASSERT_EQ(result[3], -1);  ASSERT_EQ(result[4],  0);  ASSERT_EQ(result[5],  1);
    ASSERT_EQ(result[6],  2);  ASSERT_EQ(result[7], 3);   ASSERT_EQ(result[8],  4);
}

TEST_F(VectorTests, MultiplicationBroadcaster)
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

TEST_F(VectorTests, DivisionBroadcaster)
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
}

TEST_F(VectorTests, InPlaceAdditionBroadcaster)
{
    auto result = Vector<int>(dummyIntData);

    result += 5;

    ASSERT_EQ(result[0], 6);  ASSERT_EQ(result[1], 7);  ASSERT_EQ(result[2], 8);
    ASSERT_EQ(result[3], 9);  ASSERT_EQ(result[4], 10); ASSERT_EQ(result[5], 11);
    ASSERT_EQ(result[6], 12); ASSERT_EQ(result[7], 13); ASSERT_EQ(result[8], 14);
}

TEST_F(VectorTests, InPlaceSubtractionBroadcaster)
{
    auto result = Vector<int>(dummyIntData);

    result -= 5;

    ASSERT_EQ(result[0], -4);  ASSERT_EQ(result[1], -3);  ASSERT_EQ(result[2], -2);
    ASSERT_EQ(result[3], -1);  ASSERT_EQ(result[4],  0);  ASSERT_EQ(result[5],  1);
    ASSERT_EQ(result[6],  2);  ASSERT_EQ(result[7], 3);   ASSERT_EQ(result[8],  4);
}

TEST_F(VectorTests, InPlaceMultiplicationBroadcaster)
{
    auto result = Vector<int>(dummyIntData);

    result *= 5;

    ASSERT_EQ(result[0], 5);      ASSERT_EQ(result[1], 10);     ASSERT_EQ(result[2], 15);
    ASSERT_EQ(result[3], 20);     ASSERT_EQ(result[4], 25);     ASSERT_EQ(result[5], 30);
    ASSERT_EQ(result[6], 35);     ASSERT_EQ(result[7], 40);     ASSERT_EQ(result[8], 45);
}

TEST_F(VectorTests, InPlaceDivisionBroadcaster)
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

TEST_F(VectorTests, DotProduct)
{
    const auto testVec  = Vector<double>({1.0, 4.0, 5.0});
    const auto otherVec = Vector<double>({3.0, -2.0, 0.0});

    const double dot = testVec.dot(otherVec);
    ASSERT_EQ(dot, -5.0);
    ASSERT_EQ(dot, otherVec.dot(testVec));
}