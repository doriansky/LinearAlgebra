//
// Created by dorian on 18.12.2023.
// stoicadorian@gmail.com
//

#include "gtest/gtest.h"
#include "Matrix.hpp"

using namespace LinearAlgebra::Matrix;
using namespace LinearAlgebra::Vector;

class MatrixVectorMultiplicationTests : public ::testing::Test
{

protected:
    virtual void SetUp()
    {
        const auto dummyIntData    = std::vector<int>{     1, 2, 3,
                                                4, 5, 6,
                                                7, 8, 9};

        const auto dummyFloatData  = std::vector<float>{   1.1f, 3.2f,  8.4f,
                                                           12.5f, 2.3f, 7.1f,
                                                           6.1f, 7.32f, 0.3f,
                                                           -1.2f, 7.3f, 9.32f};

        const auto dummyDoubleData = std::vector<double>{  1.12, 2.23, 3.34,
                                                4.62, 5.76, 6.78,
                                                9.12, 8.51, 7.15};

        intMat      = Matrix<int>(dummyIntData, 3, 3);
        floatMat    = Matrix<float>(dummyFloatData, 4, 3);
        doubleMat   = Matrix<double>(dummyDoubleData, 3, 3);

        intVec          = Vector<int>({-1, -2, -3});
        floatVec        = Vector<float>({1.23f, 2.34f, 3.45f});
        doubleVec       = Vector<double>({5.67, 6.78, 7.89});
    }

    virtual void TearDown()
    {
    }

    Vector<int>         intVec      = Vector<int>(3);
    Vector<float>       floatVec    = Vector<float>(4);
    Vector<double>      doubleVec   = Vector<double>(3);
    Matrix<int>         intMat      = Matrix<int>(3, 3);
    Matrix<float>       floatMat    = Matrix<float>(3, 3);
    Matrix<double>      doubleMat   = Matrix<double>(3, 3);

    float               feps        = 1e-5f;
    double              deps        = 1e-9;
};

TEST_F(MatrixVectorMultiplicationTests, Multiply_IntMatrix_IntVector)
{
    const auto result = intMat * intVec;

    ASSERT_EQ(result.dim(), 3);
    ASSERT_EQ(result[0], -14);
    ASSERT_EQ(result[1], -32);
    ASSERT_EQ(result[2], -50);
}

TEST_F(MatrixVectorMultiplicationTests, Multiply_IntMatrix_FloatVector)
{
    floatVec = Vector<float>({1.23f, 2.34f, 3.45f});

    const auto result = intMat * floatVec;

    ASSERT_EQ(result.dim(), 3);

    ASSERT_NEAR(result[0], 16.26f, feps);
    ASSERT_NEAR(result[1], 37.32f, feps);
    ASSERT_NEAR(result[2], 58.38f, feps);
}

TEST_F(MatrixVectorMultiplicationTests, Multiply_IntMatrix_DoubleVector)
{
    const auto result = intMat * doubleVec;

    ASSERT_EQ(result.dim(), 3);

    ASSERT_NEAR(result[0], 42.9, deps);
    ASSERT_NEAR(result[1], 103.92, deps);
    ASSERT_NEAR(result[2], 164.94, deps);
}

TEST_F(MatrixVectorMultiplicationTests, Multiply_FloatMatrix_IntVector)
{
    const auto result = floatMat * intVec;

    ASSERT_EQ(result.dim(), 4);

    ASSERT_NEAR(result[0], -32.7f, feps);
    ASSERT_NEAR(result[1], -38.4f, feps);
    ASSERT_NEAR(result[2], -21.64f, feps);
    ASSERT_NEAR(result[3], -41.36f, feps);
}

TEST_F(MatrixVectorMultiplicationTests, Multiply_FloatMatrix_FloatVector)
{
    const auto result = floatMat * floatVec;

    ASSERT_EQ(result.dim(), 4);

    ASSERT_NEAR(result[0], 37.821f, feps);
    ASSERT_NEAR(result[1], 45.252f, feps);
    ASSERT_NEAR(result[3], 47.76f, feps);
}

TEST_F(MatrixVectorMultiplicationTests, Multiply_FloatMatrix_DoubleVector)
{
    const auto result = floatMat * doubleVec;

    ASSERT_EQ(result.dim(), 4);

    ASSERT_NEAR(result[0], 94.209, feps);
    ASSERT_NEAR(result[1], 142.488, feps);
    ASSERT_NEAR(result[2], 86.5836, feps);
    ASSERT_NEAR(result[3], 116.2248, feps);
}

TEST_F(MatrixVectorMultiplicationTests, Multiply_DoubleMatrix_IntVector)
{
    const auto result = doubleMat * intVec;

    ASSERT_EQ(result.dim(), 3);

    ASSERT_NEAR(result[0], -15.6, deps);
    ASSERT_NEAR(result[1], -36.48, deps);
    ASSERT_NEAR(result[2], -47.59, deps);
}

TEST_F(MatrixVectorMultiplicationTests, Multiply_DoubleMatrix_FloatVector)
{
    const auto result = doubleMat * floatVec;

    ASSERT_EQ(result.dim(), 3);

    deps = 1e-6;
    ASSERT_NEAR(result[0], 18.1188, deps);
    ASSERT_NEAR(result[1], 42.552, deps);
    ASSERT_NEAR(result[2], 55.7985, deps);
}

TEST_F(MatrixVectorMultiplicationTests, Multiply_DoubleMatrix_DoubleVector)
{
    const auto result = doubleMat * doubleVec;

    ASSERT_EQ(result.dim(), 3);

    ASSERT_NEAR(result[0], 47.8224, deps);
    ASSERT_NEAR(result[1], 118.7424, deps);
    ASSERT_NEAR(result[2], 165.8217, deps);
}