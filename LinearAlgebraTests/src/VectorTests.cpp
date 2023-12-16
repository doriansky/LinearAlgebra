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

TEST_F(VectorTests, DotProduct_Int_Int)
{
    const auto testVec  = Vector<int>({1, 4, 5});
    const auto otherVec = Vector<int>({3, -2, 0});

    const int dot = testVec.dot(otherVec);
    ASSERT_EQ(dot, -5);
    ASSERT_EQ(dot, otherVec.dot(testVec));
}

TEST_F(VectorTests, DotProduct_Int_Float_And_Float_Int)
{
    const auto intVec  = Vector<int>({1, 4, 5});
    const auto floatVec = Vector<float>({0.5f, -2.5f, 0.f});

    const float dot = intVec.dot(floatVec);
    ASSERT_EQ(dot, -9.5f);
    ASSERT_EQ(dot, floatVec.dot(intVec));
}

TEST_F(VectorTests, DotProduct_Int_Double_And_Double_Int)
{
    const auto intVec  = Vector<int>({1, 4, 5});
    const auto doubleVec = Vector<double>({0.24, 1.34, 0.123});

    const double dot = intVec.dot(doubleVec);
    ASSERT_NEAR(dot, 6.215, 1e-9);
    ASSERT_EQ(dot, doubleVec.dot(intVec));
}

TEST_F(VectorTests, DotProduct_Double_Float_And_Float_Double)
{
    const auto floatVec  = Vector<float>({1.56f, 4.65f, 5.82f});
    const auto doubleVec = Vector<double>({0.24, 1.34, 0.123});

    const double dot = floatVec.dot(doubleVec);
    ASSERT_NEAR(dot, 7.32126, 1e-6);
    ASSERT_EQ(dot, doubleVec.dot(floatVec));
}