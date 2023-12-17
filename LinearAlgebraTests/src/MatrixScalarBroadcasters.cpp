//
// Created by dorian on 17.12.2023.
// stoicadorian@gmail.com
//

#include "gtest/gtest.h"
#include "Matrix.hpp"

class MatrixBroadcastersTests : public ::testing::Test
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

        intMat      = Matrix<int>(dummyIntData, 3, 3);
        floatMat    = Matrix<float>(dummyFloatData, 3, 3);
        doubleMat   = Matrix<double>(dummyDoubleData, 3, 3);
    }

    virtual void TearDown()
    {
    }

    std::vector<int>    dummyIntData;
    std::vector<double> dummyDoubleData;
    std::vector<float>  dummyFloatData;
    Matrix<int>         intMat      = Matrix<int>(3, 3);
    Matrix<float>       floatMat    = Matrix<float>(3, 3);
    Matrix<double>      doubleMat   = Matrix<double>(3, 3);
};

TEST_F(MatrixBroadcastersTests, AdditionBroadcaster_Int_Int)
{
    const auto result = intMat + 5;

    //Also let's test the non-member operator
    const auto sameResult = 5 + intMat;

    ASSERT_EQ(result(0,0), 6);  ASSERT_EQ(result(0,1), 7);  ASSERT_EQ(result(0,2), 8);
    ASSERT_EQ(result(1,0), 9);  ASSERT_EQ(result(1,1), 10); ASSERT_EQ(result(1,2), 11);
    ASSERT_EQ(result(2,0), 12); ASSERT_EQ(result(2,1), 13); ASSERT_EQ(result(2,2), 14);

    ASSERT_EQ(sameResult(0,0), 6);  ASSERT_EQ(sameResult(0,1), 7);  ASSERT_EQ(sameResult(0,2), 8);
    ASSERT_EQ(sameResult(1,0), 9);  ASSERT_EQ(sameResult(1,1), 10); ASSERT_EQ(sameResult(1,2), 11);
    ASSERT_EQ(sameResult(2,0), 12); ASSERT_EQ(sameResult(2,1), 13); ASSERT_EQ(sameResult(2,2), 14);
}

TEST_F(MatrixBroadcastersTests, AdditionBroadcaster_Int_Float)
{
    const auto result = intMat + 5.14f;

    //Also let's test the non-member operator
    const auto sameResult = 5.14f + intMat;

    const float eps = 1e-5;
    ASSERT_NEAR(result(0,0), 6.14, eps);  ASSERT_NEAR(result(0,1), 7.14, eps);  ASSERT_NEAR(result(0,2), 8.14, eps);
    ASSERT_NEAR(result(1,0), 9.14, eps);  ASSERT_NEAR(result(1,1), 10.14, eps); ASSERT_NEAR(result(1,2), 11.14, eps);
    ASSERT_NEAR(result(2,0), 12.14, eps); ASSERT_NEAR(result(2,1), 13.14, eps); ASSERT_NEAR(result(2,2), 14.14, eps);

    ASSERT_NEAR(sameResult(0,0), 6.14, eps);  ASSERT_NEAR(sameResult(0,1), 7.14, eps);  ASSERT_NEAR(sameResult(0,2), 8.14, eps);
    ASSERT_NEAR(sameResult(1,0), 9.14, eps);  ASSERT_NEAR(sameResult(1,1), 10.14, eps); ASSERT_NEAR(sameResult(1,2), 11.14, eps);
    ASSERT_NEAR(sameResult(2,0), 12.14, eps); ASSERT_NEAR(sameResult(2,1), 13.14, eps); ASSERT_NEAR(sameResult(2,2), 14.14, eps);
}

TEST_F(MatrixBroadcastersTests, AdditionBroadcaster_Int_Double)
{
    const auto result = intMat + 5.14;

    //Also let's test the non-member operator
    const auto sameResult = 5.14 + intMat;

    const double eps = 1e-9;
    ASSERT_NEAR(result(0,0), 6.14, eps);  ASSERT_NEAR(result(0,1), 7.14, eps);  ASSERT_NEAR(result(0,2), 8.14, eps);
    ASSERT_NEAR(result(1,0), 9.14, eps);  ASSERT_NEAR(result(1,1), 10.14, eps); ASSERT_NEAR(result(1,2), 11.14, eps);
    ASSERT_NEAR(result(2,0), 12.14, eps); ASSERT_NEAR(result(2,1), 13.14, eps); ASSERT_NEAR(result(2,2), 14.14, eps);

    ASSERT_NEAR(sameResult(0,0), 6.14, eps);  ASSERT_NEAR(sameResult(0,1), 7.14, eps);  ASSERT_NEAR(sameResult(0,2), 8.14, eps);
    ASSERT_NEAR(sameResult(1,0), 9.14, eps);  ASSERT_NEAR(sameResult(1,1), 10.14, eps); ASSERT_NEAR(sameResult(1,2), 11.14, eps);
    ASSERT_NEAR(sameResult(2,0), 12.14, eps); ASSERT_NEAR(sameResult(2,1), 13.14, eps); ASSERT_NEAR(sameResult(2,2), 14.14, eps);
}

TEST_F(MatrixBroadcastersTests, AdditionBroadcaster_Float_Int)
{
    const auto result = floatMat + 3;

    //Also let's test the non-member operator
    const auto sameResult = 3 + floatMat;

    const float eps = 1e-5;
    ASSERT_NEAR(result(0,0), 4.f, eps);  ASSERT_NEAR(result(0,1), 6.f, eps);  ASSERT_NEAR(result(0,2), 11.f, eps);
    ASSERT_NEAR(result(1,0), 5.f, eps);  ASSERT_NEAR(result(1,1), 10.f, eps); ASSERT_NEAR(result(1,2), 9.1f, eps);
    ASSERT_NEAR(result(2,0), 3.f, eps); ASSERT_NEAR(result(2,1), 2.f, eps); ASSERT_NEAR(result(2,2), 10.f, eps);

    ASSERT_NEAR(sameResult(0,0), 4.f, eps);  ASSERT_NEAR(sameResult(0,1), 6.f, eps);  ASSERT_NEAR(sameResult(0,2), 11.f, eps);
    ASSERT_NEAR(sameResult(1,0), 5.f, eps);  ASSERT_NEAR(sameResult(1,1), 10.f, eps); ASSERT_NEAR(sameResult(1,2), 9.1f, eps);
    ASSERT_NEAR(sameResult(2,0), 3.f, eps); ASSERT_NEAR(sameResult(2,1), 2.f, eps); ASSERT_NEAR(sameResult(2,2), 10.f, eps);
}

TEST_F(MatrixBroadcastersTests, AdditionBroadcaster_Float_Float)
{
    const float val = 3.17f;
    const auto result = floatMat + val;

    //Also let's test the non-member operator
    const auto sameResult = val + floatMat;

    const float eps = 1e-5;
    ASSERT_NEAR(result(0,0), 4.17f, eps);  ASSERT_NEAR(result(0,1), 6.17f, eps);  ASSERT_NEAR(result(0,2), 11.17f, eps);
    ASSERT_NEAR(result(1,0), 5.17f, eps);  ASSERT_NEAR(result(1,1), 10.17f, eps); ASSERT_NEAR(result(1,2), 9.27f, eps);
    ASSERT_NEAR(result(2,0), 3.17f, eps); ASSERT_NEAR(result(2,1), 2.17f, eps); ASSERT_NEAR(result(2,2), 10.17f, eps);

    ASSERT_NEAR(sameResult(0,0), 4.17f, eps);  ASSERT_NEAR(sameResult(0,1), 6.17f, eps);  ASSERT_NEAR(sameResult(0,2), 11.17f, eps);
    ASSERT_NEAR(sameResult(1,0), 5.17f, eps);  ASSERT_NEAR(sameResult(1,1), 10.17f, eps); ASSERT_NEAR(sameResult(1,2), 9.27f, eps);
    ASSERT_NEAR(sameResult(2,0), 3.17f, eps); ASSERT_NEAR(sameResult(2,1), 2.17f, eps); ASSERT_NEAR(sameResult(2,2), 10.17f, eps);
}

TEST_F(MatrixBroadcastersTests, AdditionBroadcaster_Float_Double)
{
    const double val = 3.17;
    const auto result = floatMat + val;

    //Also let's test the non-member operator
    const auto sameResult = val + floatMat;

    const float eps = 1e-5;
    ASSERT_NEAR(result(0,0), 4.17f, eps);  ASSERT_NEAR(result(0,1), 6.17f, eps);  ASSERT_NEAR(result(0,2), 11.17f, eps);
    ASSERT_NEAR(result(1,0), 5.17f, eps);  ASSERT_NEAR(result(1,1), 10.17f, eps); ASSERT_NEAR(result(1,2), 9.27f, eps);
    ASSERT_NEAR(result(2,0), 3.17f, eps); ASSERT_NEAR(result(2,1), 2.17f, eps); ASSERT_NEAR(result(2,2), 10.17f, eps);

    ASSERT_NEAR(sameResult(0,0), 4.17f, eps);  ASSERT_NEAR(sameResult(0,1), 6.17f, eps);  ASSERT_NEAR(sameResult(0,2), 11.17f, eps);
    ASSERT_NEAR(sameResult(1,0), 5.17f, eps);  ASSERT_NEAR(sameResult(1,1), 10.17f, eps); ASSERT_NEAR(sameResult(1,2), 9.27f, eps);
    ASSERT_NEAR(sameResult(2,0), 3.17f, eps); ASSERT_NEAR(sameResult(2,1), 2.17f, eps); ASSERT_NEAR(sameResult(2,2), 10.17f, eps);
}

TEST_F(MatrixBroadcastersTests, AdditionBroadcaster_Double_Int)
{
    const int val = 2;
    const auto result = doubleMat + val;

    //Also let's test the non-member operator
    const auto sameResult = val + doubleMat;

    const double eps = 1e-9;
    ASSERT_NEAR(result(0,0), 3.0, eps);  ASSERT_NEAR(result(0,1), 4.0, eps);  ASSERT_NEAR(result(0,2), 5.0, eps);
    ASSERT_NEAR(result(1,0), 6.0, eps);  ASSERT_NEAR(result(1,1), 7.0, eps); ASSERT_NEAR(result(1,2), 8.0, eps);
    ASSERT_NEAR(result(2,0), 11.1, eps); ASSERT_NEAR(result(2,1), 10.0, eps); ASSERT_NEAR(result(2,2), 9.0, eps);

    ASSERT_NEAR(sameResult(0,0), 3.0, eps);  ASSERT_NEAR(sameResult(0,1), 4.0, eps);  ASSERT_NEAR(sameResult(0,2), 5.0, eps);
    ASSERT_NEAR(sameResult(1,0), 6.0, eps);  ASSERT_NEAR(sameResult(1,1), 7.0, eps); ASSERT_NEAR(sameResult(1,2), 8.0, eps);
    ASSERT_NEAR(sameResult(2,0), 11.1, eps); ASSERT_NEAR(sameResult(2,1), 10.0, eps); ASSERT_NEAR(sameResult(2,2), 9.0, eps);
}

TEST_F(MatrixBroadcastersTests, AdditionBroadcaster_Double_Float)
{
    const float val = 2.14f;
    const auto result = doubleMat + val;

    //Also let's test the non-member operator
    const auto sameResult = val + doubleMat;

    const double eps = 1e-6;
    ASSERT_NEAR(result(0,0), 3.14, eps);  ASSERT_NEAR(result(0,1), 4.14, eps);  ASSERT_NEAR(result(0,2), 5.14, eps);
    ASSERT_NEAR(result(1,0), 6.14, eps);  ASSERT_NEAR(result(1,1), 7.14, eps); ASSERT_NEAR(result(1,2), 8.14, eps);
    ASSERT_NEAR(result(2,0), 11.24, eps); ASSERT_NEAR(result(2,1), 10.14, eps); ASSERT_NEAR(result(2,2), 9.14, eps);

    ASSERT_NEAR(sameResult(0,0), 3.14, eps);  ASSERT_NEAR(sameResult(0,1), 4.14, eps);  ASSERT_NEAR(sameResult(0,2), 5.14, eps);
    ASSERT_NEAR(sameResult(1,0), 6.14, eps);  ASSERT_NEAR(sameResult(1,1), 7.14, eps); ASSERT_NEAR(sameResult(1,2), 8.14, eps);
    ASSERT_NEAR(sameResult(2,0), 11.24, eps); ASSERT_NEAR(sameResult(2,1), 10.14, eps); ASSERT_NEAR(sameResult(2,2), 9.14, eps);
}

TEST_F(MatrixBroadcastersTests, AdditionBroadcaster_Double_Double)
{
    const double val = 2.14;
    const auto result = doubleMat + val;

    //Also let's test the non-member operator
    const auto sameResult = val + doubleMat;

    const double eps = 1e-9;
    ASSERT_NEAR(result(0,0), 3.14, eps);  ASSERT_NEAR(result(0,1), 4.14, eps);  ASSERT_NEAR(result(0,2), 5.14, eps);
    ASSERT_NEAR(result(1,0), 6.14, eps);  ASSERT_NEAR(result(1,1), 7.14, eps); ASSERT_NEAR(result(1,2), 8.14, eps);
    ASSERT_NEAR(result(2,0), 11.24, eps); ASSERT_NEAR(result(2,1), 10.14, eps); ASSERT_NEAR(result(2,2), 9.14, eps);

    ASSERT_NEAR(sameResult(0,0), 3.14, eps);  ASSERT_NEAR(sameResult(0,1), 4.14, eps);  ASSERT_NEAR(sameResult(0,2), 5.14, eps);
    ASSERT_NEAR(sameResult(1,0), 6.14, eps);  ASSERT_NEAR(sameResult(1,1), 7.14, eps); ASSERT_NEAR(sameResult(1,2), 8.14, eps);
    ASSERT_NEAR(sameResult(2,0), 11.24, eps); ASSERT_NEAR(sameResult(2,1), 10.14, eps); ASSERT_NEAR(sameResult(2,2), 9.14, eps);
}

TEST_F(MatrixBroadcastersTests, SubtractionBroadcaster_Int_Int)
{
    const auto result = intMat - 5;

    ASSERT_EQ(result(0,0), -4);  ASSERT_EQ(result(0,1), -3);  ASSERT_EQ(result(0,2), -2);
    ASSERT_EQ(result(1,0), -1);  ASSERT_EQ(result(1,1),  0);  ASSERT_EQ(result(1,2),  1);
    ASSERT_EQ(result(2,0),  2);  ASSERT_EQ(result(2,1), 3);   ASSERT_EQ(result(2,2),  4);
}

TEST_F(MatrixBroadcastersTests, SubtractionBroadcaster_Int_Float)
{
    const auto result = intMat - 4.86f;

    const float eps = 1e-5;
    ASSERT_NEAR(result(0,0), -3.86f, eps);  ASSERT_NEAR(result(0,1), -2.86f, eps);  ASSERT_NEAR(result(0,2), -1.86f, eps);
    ASSERT_NEAR(result(1,0), -0.86f, eps);  ASSERT_NEAR(result(1,1), 0.14f, eps);   ASSERT_NEAR(result(1,2), 1.14f, eps);
    ASSERT_NEAR(result(2,0),  2.14f, eps);  ASSERT_NEAR(result(2,1), 3.14f, eps);   ASSERT_NEAR(result(2,2), 4.14f, eps);
}

TEST_F(MatrixBroadcastersTests, SubtractionBroadcaster_Int_Double)
{
    const auto result = intMat - 4.86;

    const double eps = 1e-9;
    ASSERT_NEAR(result(0,0), -3.86, eps);  ASSERT_NEAR(result(0,1), -2.86, eps);  ASSERT_NEAR(result(0,2), -1.86, eps);
    ASSERT_NEAR(result(1,0), -0.86, eps);  ASSERT_NEAR(result(1,1), 0.14, eps);   ASSERT_NEAR(result(1,2), 1.14, eps);
    ASSERT_NEAR(result(2,0),  2.14, eps);  ASSERT_NEAR(result(2,1), 3.14, eps);   ASSERT_NEAR(result(2,2), 4.14, eps);
}

TEST_F(MatrixBroadcastersTests, SubtractionBroadcaster_Float_Int)
{
    const auto result = floatMat - 3;

    const float eps = 1e-5;
    ASSERT_NEAR(result(0,0), -2.f, eps);    ASSERT_NEAR(result(0,1), 0.f, eps);     ASSERT_NEAR(result(0,2), 5.f, eps);
    ASSERT_NEAR(result(1,0), -1.f, eps);    ASSERT_NEAR(result(1,1), 4.f, eps);     ASSERT_NEAR(result(1,2), 3.1f, eps);
    ASSERT_NEAR(result(2,0),  -3.f, eps);   ASSERT_NEAR(result(2,1), -4.f, eps);    ASSERT_NEAR(result(2,2), 4.f, eps);
}

TEST_F(MatrixBroadcastersTests, SubtractionBroadcaster_Float_Float)
{
    const auto result = floatMat - 2.64f;

    const float eps = 1e-5;
    ASSERT_NEAR(result(0,0), -1.64f, eps);    ASSERT_NEAR(result(0,1), 0.36f, eps);     ASSERT_NEAR(result(0,2), 5.36f, eps);
    ASSERT_NEAR(result(1,0), -0.64f, eps);    ASSERT_NEAR(result(1,1), 4.36f, eps);     ASSERT_NEAR(result(1,2), 3.46f, eps);
    ASSERT_NEAR(result(2,0),  -2.64f, eps);   ASSERT_NEAR(result(2,1), -3.64f, eps);    ASSERT_NEAR(result(2,2), 4.36f, eps);
}

TEST_F(MatrixBroadcastersTests, SubtractionBroadcaster_Float_Double)
{
    const auto result = floatMat - 2.64;

    const double eps = 1e-7;
    ASSERT_NEAR(result(0,0), -1.64, eps);    ASSERT_NEAR(result(0,1), 0.36, eps);     ASSERT_NEAR(result(0,2), 5.36, eps);
    ASSERT_NEAR(result(1,0), -0.64, eps);    ASSERT_NEAR(result(1,1), 4.36, eps);     ASSERT_NEAR(result(1,2), 3.46, eps);
    ASSERT_NEAR(result(2,0),  -2.64, eps);   ASSERT_NEAR(result(2,1), -3.64, eps);    ASSERT_NEAR(result(2,2), 4.36, eps);
}

TEST_F(MatrixBroadcastersTests, SubtractionBroadcaster_Double_Int)
{
    const auto result = doubleMat - 3;

    const double eps = 1e-9;
    ASSERT_NEAR(result(0,0), -2., eps);     ASSERT_NEAR(result(0,1), -1.0, eps);    ASSERT_NEAR(result(0,2), 0., eps);
    ASSERT_NEAR(result(1,0), 1., eps);      ASSERT_NEAR(result(1,1), 2., eps);      ASSERT_NEAR(result(1,2), 3., eps);
    ASSERT_NEAR(result(2,0),  6.1, eps);    ASSERT_NEAR(result(2,1), 5., eps);      ASSERT_NEAR(result(2,2), 4., eps);
}

TEST_F(MatrixBroadcastersTests, SubtractionBroadcaster_Double_Float)
{
    const auto result = doubleMat - 2.64f;

    const double eps = 1e-6;
    ASSERT_NEAR(result(0,0), -1.64, eps);       ASSERT_NEAR(result(0,1), -0.64, eps);       ASSERT_NEAR(result(0,2), 0.36, eps);
    ASSERT_NEAR(result(1,0), 1.36, eps);        ASSERT_NEAR(result(1,1), 2.36, eps);        ASSERT_NEAR(result(1,2), 3.36, eps);
    ASSERT_NEAR(result(2,0),  6.46, eps);       ASSERT_NEAR(result(2,1), 5.36, eps);        ASSERT_NEAR(result(2,2), 4.36, eps);
}

TEST_F(MatrixBroadcastersTests, SubtractionBroadcaster_Double_Double)
{
    const auto result = doubleMat - 2.64;

    const double eps = 1e-9;
    ASSERT_NEAR(result(0,0), -1.64, eps);       ASSERT_NEAR(result(0,1), -0.64, eps);       ASSERT_NEAR(result(0,2), 0.36, eps);
    ASSERT_NEAR(result(1,0), 1.36, eps);        ASSERT_NEAR(result(1,1), 2.36, eps);        ASSERT_NEAR(result(1,2), 3.36, eps);
    ASSERT_NEAR(result(2,0),  6.46, eps);       ASSERT_NEAR(result(2,1), 5.36, eps);        ASSERT_NEAR(result(2,2), 4.36, eps);
}

TEST_F(MatrixBroadcastersTests, MultiplicationBroadcaster_Int_Int)
{
    const auto result = intMat * 4;

    ASSERT_EQ(result(0,0), 4);      ASSERT_EQ(result(0,1), 8);      ASSERT_EQ(result(0,2), 12);
    ASSERT_EQ(result(1,0), 16);     ASSERT_EQ(result(1,1),  20);    ASSERT_EQ(result(1,2),  24);
    ASSERT_EQ(result(2,0),  28);    ASSERT_EQ(result(2,1), 32);     ASSERT_EQ(result(2,2),  36);

    //Also let's test the non-member operator
    const auto sameResult = 4 * intMat;

    ASSERT_EQ(sameResult(0,0), 4);      ASSERT_EQ(sameResult(0,1), 8);      ASSERT_EQ(sameResult(0,2), 12);
    ASSERT_EQ(sameResult(1,0), 16);     ASSERT_EQ(sameResult(1,1),  20);    ASSERT_EQ(sameResult(1,2),  24);
    ASSERT_EQ(sameResult(2,0),  28);    ASSERT_EQ(sameResult(2,1), 32);     ASSERT_EQ(sameResult(2,2),  36);
}

TEST_F(MatrixBroadcastersTests, MultiplicationBroadcaster_Int_Float)
{
    const float val = 4.12f;
    const auto result = intMat * val;

    const float eps = 1e-5f;
    ASSERT_NEAR(result(0,0), 4.12f, eps);       ASSERT_NEAR(result(0,1), 8.24f, eps);       ASSERT_NEAR(result(0,2), 12.36f, eps);
    ASSERT_NEAR(result(1,0), 16.48f, eps);      ASSERT_NEAR(result(1,1), 20.6f, eps);       ASSERT_NEAR(result(1,2), 24.72f, eps);
    ASSERT_NEAR(result(2,0),  28.84f, eps);     ASSERT_NEAR(result(2,1), 32.96f, eps);      ASSERT_NEAR(result(2,2), 37.08f, eps);

    //Also let's test the non-member operator
    const auto sameResult = val * intMat;
    ASSERT_NEAR(sameResult(0,0), 4.12f, eps);       ASSERT_NEAR(sameResult(0,1), 8.24f, eps);       ASSERT_NEAR(sameResult(0,2), 12.36f, eps);
    ASSERT_NEAR(sameResult(1,0), 16.48f, eps);      ASSERT_NEAR(sameResult(1,1), 20.6f, eps);       ASSERT_NEAR(sameResult(1,2), 24.72f, eps);
    ASSERT_NEAR(sameResult(2,0),  28.84f, eps);     ASSERT_NEAR(sameResult(2,1), 32.96f, eps);      ASSERT_NEAR(sameResult(2,2), 37.08f, eps);
}

TEST_F(MatrixBroadcastersTests, MultiplicationBroadcaster_Int_Double)
{
    const double val = 4.12;
    const auto result = intMat * val;

    const double eps = 1e-9f;
    ASSERT_NEAR(result(0,0), 4.12, eps);       ASSERT_NEAR(result(0,1), 8.24, eps);       ASSERT_NEAR(result(0,2), 12.36, eps);
    ASSERT_NEAR(result(1,0), 16.48, eps);      ASSERT_NEAR(result(1,1), 20.6, eps);       ASSERT_NEAR(result(1,2), 24.72, eps);
    ASSERT_NEAR(result(2,0),  28.84, eps);     ASSERT_NEAR(result(2,1), 32.96, eps);      ASSERT_NEAR(result(2,2), 37.08, eps);

    //Also let's test the non-member operator
    const auto sameResult = val * intMat;
    ASSERT_NEAR(sameResult(0,0), 4.12, eps);       ASSERT_NEAR(sameResult(0,1), 8.24, eps);       ASSERT_NEAR(sameResult(0,2), 12.36, eps);
    ASSERT_NEAR(sameResult(1,0), 16.48, eps);      ASSERT_NEAR(sameResult(1,1), 20.6, eps);       ASSERT_NEAR(sameResult(1,2), 24.72, eps);
    ASSERT_NEAR(sameResult(2,0),  28.84, eps);     ASSERT_NEAR(sameResult(2,1), 32.96, eps);      ASSERT_NEAR(sameResult(2,2), 37.08, eps);
}

TEST_F(MatrixBroadcastersTests, MultiplicationBroadcaster_Float_Int)
{
    const int val = 4;
    const auto result = floatMat * val;

    const float eps = 1e-5f;
    ASSERT_NEAR(result(0,0), 4.f, eps);     ASSERT_NEAR(result(0,1), 12.f, eps);        ASSERT_NEAR(result(0,2), 32.f, eps);
    ASSERT_NEAR(result(1,0), 8.f, eps);     ASSERT_NEAR(result(1,1), 28.f, eps);        ASSERT_NEAR(result(1,2), 24.4f, eps);
    ASSERT_NEAR(result(2,0),  0.f, eps);    ASSERT_NEAR(result(2,1), -4.f, eps);        ASSERT_NEAR(result(2,2), 28.f, eps);

    //Also let's test the non-member operator
    const auto sameResult = val * floatMat;
    ASSERT_NEAR(sameResult(0,0), 4.f, eps);     ASSERT_NEAR(sameResult(0,1), 12.f, eps);        ASSERT_NEAR(sameResult(0,2), 32.f, eps);
    ASSERT_NEAR(sameResult(1,0), 8.f, eps);     ASSERT_NEAR(sameResult(1,1), 28.f, eps);        ASSERT_NEAR(sameResult(1,2), 24.4f, eps);
    ASSERT_NEAR(sameResult(2,0),  0.f, eps);    ASSERT_NEAR(sameResult(2,1), -4.f, eps);        ASSERT_NEAR(sameResult(2,2), 28.f, eps);
}

TEST_F(MatrixBroadcastersTests, MultiplicationBroadcaster_Float_Float)
{
    const float val = 4.17f;
    const auto result = floatMat * val;

    const float eps = 1e-5f;
    ASSERT_NEAR(result(0,0), 4.17f, eps);       ASSERT_NEAR(result(0,1), 12.51f, eps);        ASSERT_NEAR(result(0,2), 33.36f, eps);
    ASSERT_NEAR(result(1,0), 8.34f, eps);       ASSERT_NEAR(result(1,1), 29.19f, eps);        ASSERT_NEAR(result(1,2), 25.437f, eps);
    ASSERT_NEAR(result(2,0),  0.f, eps);        ASSERT_NEAR(result(2,1), -4.17f, eps);        ASSERT_NEAR(result(2,2), 29.19f, eps);

    //Also let's test the non-member operator
    const auto sameResult = val * floatMat;
    ASSERT_NEAR(sameResult(0,0), 4.17f, eps);       ASSERT_NEAR(sameResult(0,1), 12.51f, eps);        ASSERT_NEAR(sameResult(0,2), 33.36f, eps);
    ASSERT_NEAR(sameResult(1,0), 8.34f, eps);       ASSERT_NEAR(sameResult(1,1), 29.19f, eps);        ASSERT_NEAR(sameResult(1,2), 25.437f, eps);
    ASSERT_NEAR(sameResult(2,0),  0.f, eps);        ASSERT_NEAR(sameResult(2,1), -4.17f, eps);        ASSERT_NEAR(sameResult(2,2), 29.19f, eps);
}

TEST_F(MatrixBroadcastersTests, MultiplicationBroadcaster_Float_Double)
{
    const double val = 4.17;
    const auto result = floatMat * val;

    const double eps = 1e-6;
    ASSERT_NEAR(result(0,0), 4.17, eps);       ASSERT_NEAR(result(0,1), 12.51, eps);        ASSERT_NEAR(result(0,2), 33.36, eps);
    ASSERT_NEAR(result(1,0), 8.34, eps);       ASSERT_NEAR(result(1,1), 29.19, eps);        ASSERT_NEAR(result(1,2), 25.437, eps);
    ASSERT_NEAR(result(2,0),  0., eps);        ASSERT_NEAR(result(2,1), -4.17, eps);        ASSERT_NEAR(result(2,2), 29.19, eps);

    //Also let's test the non-member operator
    const auto sameResult = val * floatMat;
    ASSERT_NEAR(sameResult(0,0), 4.17, eps);       ASSERT_NEAR(sameResult(0,1), 12.51, eps);        ASSERT_NEAR(sameResult(0,2), 33.36, eps);
    ASSERT_NEAR(sameResult(1,0), 8.34, eps);       ASSERT_NEAR(sameResult(1,1), 29.19, eps);        ASSERT_NEAR(sameResult(1,2), 25.437, eps);
    ASSERT_NEAR(sameResult(2,0),  0., eps);        ASSERT_NEAR(sameResult(2,1), -4.17, eps);        ASSERT_NEAR(sameResult(2,2), 29.19, eps);
}

TEST_F(MatrixBroadcastersTests, MultiplicationBroadcaster_Double_Int)
{
    const int val = 4;
    const auto result = doubleMat * val;

    const double eps = 1e-9f;
    ASSERT_NEAR(result(0,0), 4., eps);      ASSERT_NEAR(result(0,1), 8., eps);      ASSERT_NEAR(result(0,2), 12., eps);
    ASSERT_NEAR(result(1,0), 16., eps);     ASSERT_NEAR(result(1,1), 20., eps);     ASSERT_NEAR(result(1,2), 24., eps);
    ASSERT_NEAR(result(2,0), 36.4, eps);    ASSERT_NEAR(result(2,1), 32., eps);     ASSERT_NEAR(result(2,2), 28., eps);

    //Also let's test the non-member operator
    const auto sameResult = val * doubleMat;
    ASSERT_NEAR(sameResult(0,0), 4., eps);      ASSERT_NEAR(sameResult(0,1), 8., eps);      ASSERT_NEAR(sameResult(0,2), 12., eps);
    ASSERT_NEAR(sameResult(1,0), 16., eps);     ASSERT_NEAR(sameResult(1,1), 20., eps);     ASSERT_NEAR(sameResult(1,2), 24., eps);
    ASSERT_NEAR(sameResult(2,0), 36.4, eps);    ASSERT_NEAR(sameResult(2,1), 32., eps);     ASSERT_NEAR(sameResult(2,2), 28., eps);
}

TEST_F(MatrixBroadcastersTests, MultiplicationBroadcaster_Double_Float)
{
    const float val = 4.17f;
    const auto result = doubleMat * val;

    const double eps = 1e-6f;
    ASSERT_NEAR(result(0,0), 4.17, eps);        ASSERT_NEAR(result(0,1), 8.34, eps);        ASSERT_NEAR(result(0,2), 12.51, eps);
    ASSERT_NEAR(result(1,0), 16.68, eps);       ASSERT_NEAR(result(1,1), 20.85, eps);       ASSERT_NEAR(result(1,2), 25.02, eps);
    ASSERT_NEAR(result(2,0),  37.947, eps);     ASSERT_NEAR(result(2,1), 33.36, eps);       ASSERT_NEAR(result(2,2), 29.19, eps);

    //Also let's test the non-member operator
    const auto sameResult = val * doubleMat;
    ASSERT_NEAR(sameResult(0,0), 4.17, eps);        ASSERT_NEAR(sameResult(0,1), 8.34, eps);        ASSERT_NEAR(sameResult(0,2), 12.51, eps);
    ASSERT_NEAR(sameResult(1,0), 16.68, eps);       ASSERT_NEAR(sameResult(1,1), 20.85, eps);       ASSERT_NEAR(sameResult(1,2), 25.02, eps);
    ASSERT_NEAR(sameResult(2,0),  37.947, eps);     ASSERT_NEAR(sameResult(2,1), 33.36, eps);       ASSERT_NEAR(sameResult(2,2), 29.19, eps);
}

TEST_F(MatrixBroadcastersTests, MultiplicationBroadcaster_Double_Double)
{
    const double val = 4.17;
    const auto result = doubleMat * val;

    const double eps = 1e-9;
    ASSERT_NEAR(result(0,0), 4.17, eps);        ASSERT_NEAR(result(0,1), 8.34, eps);        ASSERT_NEAR(result(0,2), 12.51, eps);
    ASSERT_NEAR(result(1,0), 16.68, eps);       ASSERT_NEAR(result(1,1), 20.85, eps);       ASSERT_NEAR(result(1,2), 25.02, eps);
    ASSERT_NEAR(result(2,0),  37.947, eps);     ASSERT_NEAR(result(2,1), 33.36, eps);       ASSERT_NEAR(result(2,2), 29.19, eps);

    //Also let's test the non-member operator
    const auto sameResult = val * doubleMat;
    ASSERT_NEAR(sameResult(0,0), 4.17, eps);        ASSERT_NEAR(sameResult(0,1), 8.34, eps);        ASSERT_NEAR(sameResult(0,2), 12.51, eps);
    ASSERT_NEAR(sameResult(1,0), 16.68, eps);       ASSERT_NEAR(sameResult(1,1), 20.85, eps);       ASSERT_NEAR(sameResult(1,2), 25.02, eps);
    ASSERT_NEAR(sameResult(2,0),  37.947, eps);     ASSERT_NEAR(sameResult(2,1), 33.36, eps);       ASSERT_NEAR(sameResult(2,2), 29.19, eps);
}

TEST_F(MatrixBroadcastersTests, DivisionBroadcaster_IntMatrix_WithDifferentScalarTypes)
{
    //First of all, division by zero throws
    ASSERT_THROW(intMat/0, std::invalid_argument);
    ASSERT_THROW(intMat/0.0f, std::invalid_argument);
    ASSERT_THROW(intMat/0.0, std::invalid_argument);

    // Dividing an int matrix with an integer will return an int matrix (will all values casted to int)
    const auto result = intMat / 4;

    ASSERT_EQ(result(0,0), 0);      ASSERT_EQ(result(0,1), 0);      ASSERT_EQ(result(0,2), 0);
    ASSERT_EQ(result(1,0), 1);      ASSERT_EQ(result(1,1),  1);     ASSERT_EQ(result(1,2),  1);
    ASSERT_EQ(result(2,0), 1);      ASSERT_EQ(result(2,1), 2);      ASSERT_EQ(result(2,2),  2);

    // Dividing by same "value" of float type will return a float matrix
    const auto floatResult = intMat / 4.0f;
    const float eps = 1e-5f;
    ASSERT_NEAR(floatResult(0,0), 0.25f, eps);      ASSERT_NEAR(floatResult(0,1), 0.5f, eps);       ASSERT_NEAR(floatResult(0,2), 0.75f, eps);
    ASSERT_NEAR(floatResult(1,0), 1.f, eps);        ASSERT_NEAR(floatResult(1,1), 1.25f, eps);      ASSERT_NEAR(floatResult(1,2), 1.5f, eps);
    ASSERT_NEAR(floatResult(2,0), 1.75f, eps);      ASSERT_NEAR(floatResult(2,1), 2.f, eps);        ASSERT_NEAR(floatResult(2,2), 2.25f, eps);


    // Same for double
    const auto doubleResult = intMat / 4.0;
    const double epsd = 1e-9;
    ASSERT_NEAR(doubleResult(0,0), 0.25f, epsd);      ASSERT_NEAR(doubleResult(0,1), 0.5f, epsd);       ASSERT_NEAR(doubleResult(0,2), 0.75f, epsd);
    ASSERT_NEAR(doubleResult(1,0), 1.f, epsd);        ASSERT_NEAR(doubleResult(1,1), 1.25f, epsd);      ASSERT_NEAR(doubleResult(1,2), 1.5f, epsd);
    ASSERT_NEAR(doubleResult(2,0), 1.75f, epsd);      ASSERT_NEAR(doubleResult(2,1), 2.f, epsd);        ASSERT_NEAR(doubleResult(2,2), 2.25f, epsd);
}

TEST_F(MatrixBroadcastersTests, DivisionBroadcaster_FloatMatrix_WithDifferentScalarTypes)
{
    //First of all, division by zero throws
    ASSERT_THROW(floatMat/0, std::invalid_argument);
    ASSERT_THROW(floatMat/0.0f, std::invalid_argument);
    ASSERT_THROW(floatMat/0.0, std::invalid_argument);

    const float eps = 1e-5f;

    {
        //Dividing with int
        const auto result = floatMat / 2;

        ASSERT_NEAR(result(0,0), 0.5f, eps);      ASSERT_NEAR(result(0,1), 1.5f, eps);       ASSERT_NEAR(result(0,2), 4.f, eps);
        ASSERT_NEAR(result(1,0), 1.f, eps);        ASSERT_NEAR(result(1,1), 3.5f, eps);      ASSERT_NEAR(result(1,2), 3.05f, eps);
        ASSERT_NEAR(result(2,0), 0.f, eps);      ASSERT_NEAR(result(2,1), -0.5f, eps);        ASSERT_NEAR(result(2,2), 3.5f, eps);
    }

    {
        //Dividing with float
        const auto result = floatMat / 1.23f;
        ASSERT_NEAR(result(0,0), 0.813008130081301f, eps);      ASSERT_NEAR(result(0,1), 2.4390243902439f, eps);        ASSERT_NEAR(result(0,2), 6.50406504065041f, eps);
        ASSERT_NEAR(result(1,0), 1.6260162601626f, eps);        ASSERT_NEAR(result(1,1), 5.69105691056911f, eps);       ASSERT_NEAR(result(1,2), 4.95934959349593f, eps);
        ASSERT_NEAR(result(2,0), 0.f, eps);                     ASSERT_NEAR(result(2,1), -0.813008130081301f, eps);     ASSERT_NEAR(result(2,2), 5.69105691056911f, eps);
    }

    {
        //Dividing with double
        const auto result = floatMat / 1.23;
        ASSERT_NEAR(result(0,0), 0.813008130081301, eps);      ASSERT_NEAR(result(0,1), 2.4390243902439, eps);        ASSERT_NEAR(result(0,2), 6.50406504065041, eps);
        ASSERT_NEAR(result(1,0), 1.6260162601626, eps);        ASSERT_NEAR(result(1,1), 5.69105691056911, eps);       ASSERT_NEAR(result(1,2), 4.95934959349593, eps);
        ASSERT_NEAR(result(2,0), 0., eps);                     ASSERT_NEAR(result(2,1), -0.813008130081301, eps);     ASSERT_NEAR(result(2,2), 5.69105691056911, eps);
    }
}

TEST_F(MatrixBroadcastersTests, DivisionBroadcaster_DoubleMatrix_WithDifferentScalarTypes)
{
    //First of all, division by zero throws
    ASSERT_THROW(doubleMat/0, std::invalid_argument);
    ASSERT_THROW(doubleMat/0.0f, std::invalid_argument);
    ASSERT_THROW(doubleMat/0.0, std::invalid_argument);

    const double eps = 1e-9f;

    {
        //Dividing with int
        const auto result = doubleMat / 2;

        ASSERT_NEAR(result(0,0), 0.5, eps);     ASSERT_NEAR(result(0,1), 1., eps);      ASSERT_NEAR(result(0,2), 1.5, eps);
        ASSERT_NEAR(result(1,0), 2., eps);      ASSERT_NEAR(result(1,1), 2.5, eps);     ASSERT_NEAR(result(1,2), 3., eps);
        ASSERT_NEAR(result(2,0), 4.55, eps);    ASSERT_NEAR(result(2,1), 4., eps);      ASSERT_NEAR(result(2,2), 3.5, eps);
    }

    {
        //Dividing with float
        const auto result = doubleMat / 2.34f;
        const float epsf = 1e-5f;
        ASSERT_NEAR(result(0,0), 0.427350427350427, epsf);       ASSERT_NEAR(result(0,1), 0.854700854700855, epsf);       ASSERT_NEAR(result(0,2), 1.28205128205128, epsf);
        ASSERT_NEAR(result(1,0), 1.70940170940171, epsf);        ASSERT_NEAR(result(1,1), 2.13675213675214, epsf);        ASSERT_NEAR(result(1,2), 2.56410256410256, epsf);
        ASSERT_NEAR(result(2,0), 3.88888888888889, epsf);        ASSERT_NEAR(result(2,1), 3.41880341880342, epsf);        ASSERT_NEAR(result(2,2), 2.99145299145299, epsf);
    }

    {
        //Dividing with double
        const auto result = doubleMat / 2.34;
        ASSERT_NEAR(result(0,0), 0.427350427350427, eps);       ASSERT_NEAR(result(0,1), 0.854700854700855, eps);       ASSERT_NEAR(result(0,2), 1.28205128205128, eps);
        ASSERT_NEAR(result(1,0), 1.70940170940171, eps);        ASSERT_NEAR(result(1,1), 2.13675213675214, eps);        ASSERT_NEAR(result(1,2), 2.56410256410256, eps);
        ASSERT_NEAR(result(2,0), 3.88888888888889, eps);        ASSERT_NEAR(result(2,1), 3.41880341880342, eps);        ASSERT_NEAR(result(2,2), 2.99145299145299, eps);
    }
}

TEST_F(MatrixBroadcastersTests, InPlaceAdditionBroadcaster)
{
    auto result = Matrix<int>(dummyIntData, 3, 3);

    result += 5;

    ASSERT_EQ(result(0,0), 6);  ASSERT_EQ(result(0,1), 7);  ASSERT_EQ(result(0,2), 8);
    ASSERT_EQ(result(1,0), 9);  ASSERT_EQ(result(1,1), 10); ASSERT_EQ(result(1,2), 11);
    ASSERT_EQ(result(2,0), 12); ASSERT_EQ(result(2,1), 13); ASSERT_EQ(result(2,2), 14);
}

TEST_F(MatrixBroadcastersTests, InPlaceSubtractionBroadcaster)
{
    auto result = Matrix<int>(dummyIntData, 3, 3);

    result -= 5;

    ASSERT_EQ(result(0,0), -4);  ASSERT_EQ(result(0,1), -3);  ASSERT_EQ(result(0,2), -2);
    ASSERT_EQ(result(1,0), -1);  ASSERT_EQ(result(1,1),  0);  ASSERT_EQ(result(1,2),  1);
    ASSERT_EQ(result(2,0),  2);  ASSERT_EQ(result(2,1), 3);   ASSERT_EQ(result(2,2),  4);
}

TEST_F(MatrixBroadcastersTests, InPlaceMultiplicationBroadcaster)
{
    auto result = Matrix<int>(dummyIntData, 3, 3);

    result *= 5;

    ASSERT_EQ(result(0,0), 5);      ASSERT_EQ(result(0,1), 10);     ASSERT_EQ(result(0,2), 15);
    ASSERT_EQ(result(1,0), 20);     ASSERT_EQ(result(1,1), 25);     ASSERT_EQ(result(1,2), 30);
    ASSERT_EQ(result(2,0), 35);     ASSERT_EQ(result(2,1), 40);     ASSERT_EQ(result(2,2), 45);
}

TEST_F(MatrixBroadcastersTests, InPlaceDivisionBroadcaster)
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