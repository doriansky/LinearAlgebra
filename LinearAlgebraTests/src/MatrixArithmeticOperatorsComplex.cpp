//
// Created by dorian on 25.01.2024
// stoicadorian@gmail.com
//
#include "gtest/gtest.h"
#include "Matrix.hpp"

using namespace LinearAlgebra::Matrix;

class ComplexMatrixArithmeticTests : public ::testing::Test
{

protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

    float fepsilon = 1e-6;
    double epsilon = 1e-9;
};

TEST_F(ComplexMatrixArithmeticTests, MatrixAddition_SameType)
{
    const auto intMat = Matrix<int>({1,2,3}, 3, 1);
    const auto complexIntMat = Matrix<std::complex<int>>({{1,1}, {2,2}, {3,3}}, 3, 1);

    const auto intMatPlusComplexIntMat = intMat + complexIntMat;
    ASSERT_EQ(intMatPlusComplexIntMat(0,0), std::complex<int>(2,1));
    ASSERT_EQ(intMatPlusComplexIntMat(1,0), std::complex<int>(4,2));
    ASSERT_EQ(intMatPlusComplexIntMat(2,0), std::complex<int>(6,3));

    const auto complexIntMatPlusIntMat = complexIntMat + intMat;
    ASSERT_EQ(complexIntMatPlusIntMat(0,0), std::complex<int>(2,1));
    ASSERT_EQ(complexIntMatPlusIntMat(1,0), std::complex<int>(4,2));
    ASSERT_EQ(complexIntMatPlusIntMat(2,0), std::complex<int>(6,3));
}

TEST_F(ComplexMatrixArithmeticTests, Addition_ComplexIntMatrix_FloatMatrix)
{
    const auto floatMat = Matrix<float>({1.1f,2.2f,3.3f}, 3, 1);
    const auto complexIntMat = Matrix<std::complex<int>>({{1,1}, {2,2}, {3,3}}, 3, 1);

    const auto floatMatPlusComplexIntMat = floatMat + complexIntMat;
    ASSERT_NEAR(floatMatPlusComplexIntMat(0,0).real(), 2.1f, fepsilon);   ASSERT_NEAR(floatMatPlusComplexIntMat(0,0).imag(), 1.0f, fepsilon);
    ASSERT_NEAR(floatMatPlusComplexIntMat(1,0).real(), 4.2f, fepsilon);   ASSERT_NEAR(floatMatPlusComplexIntMat(1,0).imag(), 2.0f, fepsilon);
    ASSERT_NEAR(floatMatPlusComplexIntMat(2,0).real(), 6.3f, fepsilon);   ASSERT_NEAR(floatMatPlusComplexIntMat(2,0).imag(), 3.0f, fepsilon);

    const auto complexIntMatPlusFloatMat = complexIntMat + floatMat;
    ASSERT_NEAR(complexIntMatPlusFloatMat(0,0).real(), 2.1f, fepsilon);   ASSERT_NEAR(complexIntMatPlusFloatMat(0,0).imag(), 1.0f, fepsilon);
    ASSERT_NEAR(complexIntMatPlusFloatMat(1,0).real(), 4.2f, fepsilon);   ASSERT_NEAR(complexIntMatPlusFloatMat(1,0).imag(), 2.0f, fepsilon);
    ASSERT_NEAR(complexIntMatPlusFloatMat(2,0).real(), 6.3f, fepsilon);   ASSERT_NEAR(complexIntMatPlusFloatMat(2,0).imag(), 3.0f, fepsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Addition_ComplexIntMatrix_DoubleMatrix)
{
    const auto doubleMat = Matrix<double>({1.1,2.2,3.3}, 3, 1);
    const auto complexIntMat = Matrix<std::complex<int>>({{1,1}, {2,2}, {3,3}}, 3, 1);

    const auto doubleMatPlusComplexIntMat = doubleMat + complexIntMat;
    ASSERT_NEAR(doubleMatPlusComplexIntMat(0,0).real(), 2.1, epsilon);   ASSERT_NEAR(doubleMatPlusComplexIntMat(0,0).imag(), 1.0, epsilon);
    ASSERT_NEAR(doubleMatPlusComplexIntMat(1,0).real(), 4.2, epsilon);   ASSERT_NEAR(doubleMatPlusComplexIntMat(1,0).imag(), 2.0, epsilon);
    ASSERT_NEAR(doubleMatPlusComplexIntMat(2,0).real(), 6.3, epsilon);   ASSERT_NEAR(doubleMatPlusComplexIntMat(2,0).imag(), 3.0, epsilon);

    const auto complexIntMatPlusDoubleMat = complexIntMat + doubleMat;
    ASSERT_NEAR(complexIntMatPlusDoubleMat(0,0).real(), 2.1, epsilon);   ASSERT_NEAR(complexIntMatPlusDoubleMat(0,0).imag(), 1.0, epsilon);
    ASSERT_NEAR(complexIntMatPlusDoubleMat(1,0).real(), 4.2, epsilon);   ASSERT_NEAR(complexIntMatPlusDoubleMat(1,0).imag(), 2.0, epsilon);
    ASSERT_NEAR(complexIntMatPlusDoubleMat(2,0).real(), 6.3, epsilon);   ASSERT_NEAR(complexIntMatPlusDoubleMat(2,0).imag(), 3.0, epsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Addition_ComplexIntMatrix_LongDoubleMatrix)
{
    const auto doubleMat = Matrix<long double>({1.1,2.2,3.3}, 3, 1);
    const auto complexIntMat = Matrix<std::complex<int>>({{1,1}, {2,2}, {3,3}}, 3, 1);

    const auto doubleMatPlusComplexIntMat = doubleMat + complexIntMat;
    ASSERT_NEAR(doubleMatPlusComplexIntMat(0,0).real(), 2.1, epsilon);   ASSERT_NEAR(doubleMatPlusComplexIntMat(0,0).imag(), 1.0, epsilon);
    ASSERT_NEAR(doubleMatPlusComplexIntMat(1,0).real(), 4.2, epsilon);   ASSERT_NEAR(doubleMatPlusComplexIntMat(1,0).imag(), 2.0, epsilon);
    ASSERT_NEAR(doubleMatPlusComplexIntMat(2,0).real(), 6.3, epsilon);   ASSERT_NEAR(doubleMatPlusComplexIntMat(2,0).imag(), 3.0, epsilon);

    const auto complexIntMatPlusDoubleMat = complexIntMat + doubleMat;
    ASSERT_NEAR(complexIntMatPlusDoubleMat(0,0).real(), 2.1, epsilon);   ASSERT_NEAR(complexIntMatPlusDoubleMat(0,0).imag(), 1.0, epsilon);
    ASSERT_NEAR(complexIntMatPlusDoubleMat(1,0).real(), 4.2, epsilon);   ASSERT_NEAR(complexIntMatPlusDoubleMat(1,0).imag(), 2.0, epsilon);
    ASSERT_NEAR(complexIntMatPlusDoubleMat(2,0).real(), 6.3, epsilon);   ASSERT_NEAR(complexIntMatPlusDoubleMat(2,0).imag(), 3.0, epsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Addition_ComplexIntMatrix_ComplexIntMatrix)
{
    const auto complexIntMat = Matrix<std::complex<int>>({{1,2}, {2,2}, {3,3}}, 3, 1);

    const auto res = complexIntMat + complexIntMat;
    ASSERT_EQ(res(0,0), std::complex<int>(2,4));
    ASSERT_EQ(res(1,0), std::complex<int>(4,4));
    ASSERT_EQ(res(2,0), std::complex<int>(6,6));
}

TEST_F(ComplexMatrixArithmeticTests, Addition_ComplexIntMatrix_ComplexFloatMatrix)
{
    const auto complexIntMat = Matrix<std::complex<int>>({{1,1}, {2,2}, {3,3}}, 3, 1);
    const auto complexFloatMat = Matrix<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.4f}}, 3, 1);

    const auto res = complexIntMat + complexFloatMat;
    ASSERT_NEAR(res(0,0).real(), 2.1f, fepsilon);   ASSERT_NEAR(res(0,0).imag(), 2.1f, fepsilon);
    ASSERT_NEAR(res(1,0).real(), 4.2f, fepsilon);   ASSERT_NEAR(res(1,0).imag(), 4.2f, fepsilon);
    ASSERT_NEAR(res(2,0).real(), 6.3f, fepsilon);   ASSERT_NEAR(res(2,0).imag(), 6.4f, fepsilon);

    const auto res2 = complexFloatMat + complexIntMat;
    ASSERT_NEAR(res2(0,0).real(), 2.1f, fepsilon);   ASSERT_NEAR(res2(0,0).imag(), 2.1f, fepsilon);
    ASSERT_NEAR(res2(1,0).real(), 4.2f, fepsilon);   ASSERT_NEAR(res2(1,0).imag(), 4.2f, fepsilon);
    ASSERT_NEAR(res2(2,0).real(), 6.3f, fepsilon);   ASSERT_NEAR(res2(2,0).imag(), 6.4f, fepsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Addition_ComplexIntMatrix_ComplexDoubleMatrix)
{
    const auto complexIntMat = Matrix<std::complex<int>>({{1,1}, {2,2}, {3,3}}, 3, 1);
    const auto complexDoubleMat = Matrix<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.4}}, 3, 1);

    const auto res = complexIntMat + complexDoubleMat;
    ASSERT_NEAR(res(0,0).real(), 2.1, epsilon);   ASSERT_NEAR(res(0,0).imag(), 2.1, epsilon);
    ASSERT_NEAR(res(1,0).real(), 4.2, epsilon);   ASSERT_NEAR(res(1,0).imag(), 4.2, epsilon);
    ASSERT_NEAR(res(2,0).real(), 6.3, epsilon);   ASSERT_NEAR(res(2,0).imag(), 6.4, epsilon);

    const auto res2 = complexDoubleMat + complexIntMat;
    ASSERT_NEAR(res2(0,0).real(), 2.1, epsilon);   ASSERT_NEAR(res2(0,0).imag(), 2.1, epsilon);
    ASSERT_NEAR(res2(1,0).real(), 4.2, epsilon);   ASSERT_NEAR(res2(1,0).imag(), 4.2, epsilon);
    ASSERT_NEAR(res2(2,0).real(), 6.3, epsilon);   ASSERT_NEAR(res2(2,0).imag(), 6.4, epsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Addition_ComplexIntMatrix_ComplexLongDoubleMatrix)
{
    const auto complexIntMat = Matrix<std::complex<int>>({{1,1}, {2,2}, {3,3}}, 3, 1);
    const auto complexDoubleMat = Matrix<std::complex<long double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.4}}, 3, 1);

    const auto res = complexIntMat + complexDoubleMat;
    ASSERT_NEAR(res(0,0).real(), 2.1, epsilon);   ASSERT_NEAR(res(0,0).imag(), 2.1, epsilon);
    ASSERT_NEAR(res(1,0).real(), 4.2, epsilon);   ASSERT_NEAR(res(1,0).imag(), 4.2, epsilon);
    ASSERT_NEAR(res(2,0).real(), 6.3, epsilon);   ASSERT_NEAR(res(2,0).imag(), 6.4, epsilon);

    const auto res2 = complexDoubleMat + complexIntMat;
    ASSERT_NEAR(res2(0,0).real(), 2.1, epsilon);   ASSERT_NEAR(res2(0,0).imag(), 2.1, epsilon);
    ASSERT_NEAR(res2(1,0).real(), 4.2, epsilon);   ASSERT_NEAR(res2(1,0).imag(), 4.2, epsilon);
    ASSERT_NEAR(res2(2,0).real(), 6.3, epsilon);   ASSERT_NEAR(res2(2,0).imag(), 6.4, epsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Addition_ComplexFloatMatrix_IntMatrix)
{
    const auto intMat = Matrix<int>({1,2,3}, 3, 1);
    const auto complexFloatMat = Matrix<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}}, 3, 1);

    const auto complexFloatMatPlusIntMat = complexFloatMat + intMat;
    ASSERT_NEAR(complexFloatMatPlusIntMat(0,0).real(), 2.1f, fepsilon);   ASSERT_NEAR(complexFloatMatPlusIntMat(0,0).imag(), 1.1f, fepsilon);
    ASSERT_NEAR(complexFloatMatPlusIntMat(1,0).real(), 4.2f, fepsilon);   ASSERT_NEAR(complexFloatMatPlusIntMat(1,0).imag(), 2.2f, fepsilon);
    ASSERT_NEAR(complexFloatMatPlusIntMat(2,0).real(), 6.3f, fepsilon);   ASSERT_NEAR(complexFloatMatPlusIntMat(2,0).imag(), 3.3f, fepsilon);

    const auto intMatPlusComplexFloatMat = intMat + complexFloatMat;
    ASSERT_NEAR(intMatPlusComplexFloatMat(0,0).real(), 2.1f, fepsilon);   ASSERT_NEAR(intMatPlusComplexFloatMat(0,0).imag(), 1.1f, fepsilon);
    ASSERT_NEAR(intMatPlusComplexFloatMat(1,0).real(), 4.2f, fepsilon);   ASSERT_NEAR(intMatPlusComplexFloatMat(1,0).imag(), 2.2f, fepsilon);
    ASSERT_NEAR(intMatPlusComplexFloatMat(2,0).real(), 6.3f, fepsilon);   ASSERT_NEAR(intMatPlusComplexFloatMat(2,0).imag(), 3.3f, fepsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Addition_ComplexFloatMatrix_FloatMatrix)
{
    const auto floatMat = Matrix<float>({1.1f,2.2f,3.3f}, 3, 1);
    const auto complexFloatMat = Matrix<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}}, 3, 1);

    const auto complexFloatMatPlusFloatMat = complexFloatMat + floatMat;
    ASSERT_NEAR(complexFloatMatPlusFloatMat(0,0).real(), 2.2f, fepsilon);   ASSERT_NEAR(complexFloatMatPlusFloatMat(0,0).imag(), 1.1f, fepsilon);
    ASSERT_NEAR(complexFloatMatPlusFloatMat(1,0).real(), 4.4f, fepsilon);   ASSERT_NEAR(complexFloatMatPlusFloatMat(1,0).imag(), 2.2f, fepsilon);
    ASSERT_NEAR(complexFloatMatPlusFloatMat(2,0).real(), 6.6f, fepsilon);   ASSERT_NEAR(complexFloatMatPlusFloatMat(2,0).imag(), 3.3f, fepsilon);

    const auto floatMatPlusComplexFloatMat = floatMat + complexFloatMat;
    ASSERT_NEAR(floatMatPlusComplexFloatMat(0,0).real(), 2.2f, fepsilon);   ASSERT_NEAR(floatMatPlusComplexFloatMat(0,0).imag(), 1.1f, fepsilon);
    ASSERT_NEAR(floatMatPlusComplexFloatMat(1,0).real(), 4.4f, fepsilon);   ASSERT_NEAR(floatMatPlusComplexFloatMat(1,0).imag(), 2.2f, fepsilon);
    ASSERT_NEAR(floatMatPlusComplexFloatMat(2,0).real(), 6.6f, fepsilon);   ASSERT_NEAR(floatMatPlusComplexFloatMat(2,0).imag(), 3.3f, fepsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Addition_ComplexFloatMatrix_DoubleMatrix)
{
    const auto doubleMat = Matrix<double>({1.1,2.2,3.3}, 3, 1);
    const auto complexFloatMat = Matrix<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}}, 3, 1);

    const auto complexFloatMatPlusDoubleMat = complexFloatMat + doubleMat;
    ASSERT_NEAR(complexFloatMatPlusDoubleMat(0,0).real(), 2.2, fepsilon);   ASSERT_NEAR(complexFloatMatPlusDoubleMat(0,0).imag(), 1.1, fepsilon);
    ASSERT_NEAR(complexFloatMatPlusDoubleMat(1,0).real(), 4.4, fepsilon);   ASSERT_NEAR(complexFloatMatPlusDoubleMat(1,0).imag(), 2.2, fepsilon);
    ASSERT_NEAR(complexFloatMatPlusDoubleMat(2,0).real(), 6.6, fepsilon);   ASSERT_NEAR(complexFloatMatPlusDoubleMat(2,0).imag(), 3.3, fepsilon);

    const auto doubleMatPlusComplexFloatMat = doubleMat + complexFloatMat;
    ASSERT_NEAR(doubleMatPlusComplexFloatMat(0,0).real(), 2.2, fepsilon);   ASSERT_NEAR(doubleMatPlusComplexFloatMat(0,0).imag(), 1.1, fepsilon);
    ASSERT_NEAR(doubleMatPlusComplexFloatMat(1,0).real(), 4.4, fepsilon);   ASSERT_NEAR(doubleMatPlusComplexFloatMat(1,0).imag(), 2.2, fepsilon);
    ASSERT_NEAR(doubleMatPlusComplexFloatMat(2,0).real(), 6.6, fepsilon);   ASSERT_NEAR(doubleMatPlusComplexFloatMat(2,0).imag(), 3.3, fepsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Addition_ComplexFloatMatrix_LongDoubleMatrix)
{
    const auto doubleMat = Matrix<long double>({1.1,2.2,3.3}, 3, 1);
    const auto complexFloatMat = Matrix<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}}, 3, 1);

    const auto complexFloatMatPlusDoubleMat = complexFloatMat + doubleMat;
    ASSERT_NEAR(complexFloatMatPlusDoubleMat(0,0).real(), 2.2, fepsilon);   ASSERT_NEAR(complexFloatMatPlusDoubleMat(0,0).imag(), 1.1, fepsilon);
    ASSERT_NEAR(complexFloatMatPlusDoubleMat(1,0).real(), 4.4, fepsilon);   ASSERT_NEAR(complexFloatMatPlusDoubleMat(1,0).imag(), 2.2, fepsilon);
    ASSERT_NEAR(complexFloatMatPlusDoubleMat(2,0).real(), 6.6, fepsilon);   ASSERT_NEAR(complexFloatMatPlusDoubleMat(2,0).imag(), 3.3, fepsilon);

    const auto doubleMatPlusComplexFloatMat = doubleMat + complexFloatMat;
    ASSERT_NEAR(doubleMatPlusComplexFloatMat(0,0).real(), 2.2, fepsilon);   ASSERT_NEAR(doubleMatPlusComplexFloatMat(0,0).imag(), 1.1, fepsilon);
    ASSERT_NEAR(doubleMatPlusComplexFloatMat(1,0).real(), 4.4, fepsilon);   ASSERT_NEAR(doubleMatPlusComplexFloatMat(1,0).imag(), 2.2, fepsilon);
    ASSERT_NEAR(doubleMatPlusComplexFloatMat(2,0).real(), 6.6, fepsilon);   ASSERT_NEAR(doubleMatPlusComplexFloatMat(2,0).imag(), 3.3, fepsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Addition_ComplexFloatMatrix_ComplexFloatMatrix)
{
    const auto complexFloatMat = Matrix<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}}, 3, 1);

    const auto res = complexFloatMat + complexFloatMat;
    ASSERT_NEAR(res(0,0).real(), 2.2f, fepsilon);   ASSERT_NEAR(res(0,0).imag(), 2.2f, fepsilon);
    ASSERT_NEAR(res(1,0).real(), 4.4f, fepsilon);   ASSERT_NEAR(res(1,0).imag(), 4.4f, fepsilon);
    ASSERT_NEAR(res(2,0).real(), 6.6f, fepsilon);   ASSERT_NEAR(res(2,0).imag(), 6.6f, fepsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Addition_ComplexFloatMatrix_ComplexDoubleMatrix)
{
    const auto complexFloatMat = Matrix<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}}, 3, 1);
    const auto complexDoubleMat = Matrix<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.4}}, 3, 1);

    const auto res = complexFloatMat + complexDoubleMat;
    ASSERT_NEAR(res(0,0).real(), 2.2, fepsilon);   ASSERT_NEAR(res(0,0).imag(), 2.2, fepsilon);
    ASSERT_NEAR(res(1,0).real(), 4.4, fepsilon);   ASSERT_NEAR(res(1,0).imag(), 4.4, fepsilon);
    ASSERT_NEAR(res(2,0).real(), 6.6, fepsilon);   ASSERT_NEAR(res(2,0).imag(), 6.7, fepsilon);

    const auto res2 = complexDoubleMat + complexFloatMat;
    ASSERT_NEAR(res2(0,0).real(), 2.2, fepsilon);   ASSERT_NEAR(res2(0,0).imag(), 2.2, fepsilon);
    ASSERT_NEAR(res2(1,0).real(), 4.4, fepsilon);   ASSERT_NEAR(res2(1,0).imag(), 4.4, fepsilon);
    ASSERT_NEAR(res2(2,0).real(), 6.6, fepsilon);   ASSERT_NEAR(res2(2,0).imag(), 6.7, fepsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Addition_ComplexFloatMatrix_ComplexLongDoubleMatrix)
{
    const auto complexFloatMat = Matrix<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}}, 3, 1);
    const auto complexDoubleMat = Matrix<std::complex<long double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.4}}, 3, 1);

    const auto res = complexFloatMat + complexDoubleMat;
    ASSERT_NEAR(res(0,0).real(), 2.2, fepsilon);   ASSERT_NEAR(res(0,0).imag(), 2.2, fepsilon);
    ASSERT_NEAR(res(1,0).real(), 4.4, fepsilon);   ASSERT_NEAR(res(1,0).imag(), 4.4, fepsilon);
    ASSERT_NEAR(res(2,0).real(), 6.6, fepsilon);   ASSERT_NEAR(res(2,0).imag(), 6.7, fepsilon);

    const auto res2 = complexDoubleMat + complexFloatMat;
    ASSERT_NEAR(res2(0,0).real(), 2.2, fepsilon);   ASSERT_NEAR(res2(0,0).imag(), 2.2, fepsilon);
    ASSERT_NEAR(res2(1,0).real(), 4.4, fepsilon);   ASSERT_NEAR(res2(1,0).imag(), 4.4, fepsilon);
    ASSERT_NEAR(res2(2,0).real(), 6.6, fepsilon);   ASSERT_NEAR(res2(2,0).imag(), 6.7, fepsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Addition_ComplexDoubleMatrix_IntMatrix)
{
    const auto intMat = Matrix<int>({1,2,3}, 3, 1);
    const auto complexDoubleMat = Matrix<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.3}}, 3, 1);

    const auto complexDoubleMatPlusIntMat = complexDoubleMat + intMat;
    ASSERT_NEAR(complexDoubleMatPlusIntMat(0,0).real(), 2.1, epsilon);   ASSERT_NEAR(complexDoubleMatPlusIntMat(0,0).imag(), 1.1, epsilon);
    ASSERT_NEAR(complexDoubleMatPlusIntMat(1,0).real(), 4.2, epsilon);   ASSERT_NEAR(complexDoubleMatPlusIntMat(1,0).imag(), 2.2, epsilon);
    ASSERT_NEAR(complexDoubleMatPlusIntMat(2,0).real(), 6.3, epsilon);   ASSERT_NEAR(complexDoubleMatPlusIntMat(2,0).imag(), 3.3, epsilon);

    const auto intMatPlusComplexDoubleMat = intMat + complexDoubleMat;
    ASSERT_NEAR(intMatPlusComplexDoubleMat(0,0).real(), 2.1, epsilon);   ASSERT_NEAR(intMatPlusComplexDoubleMat(0,0).imag(), 1.1, epsilon);
    ASSERT_NEAR(intMatPlusComplexDoubleMat(1,0).real(), 4.2, epsilon);   ASSERT_NEAR(intMatPlusComplexDoubleMat(1,0).imag(), 2.2, epsilon);
    ASSERT_NEAR(intMatPlusComplexDoubleMat(2,0).real(), 6.3, epsilon);   ASSERT_NEAR(intMatPlusComplexDoubleMat(2,0).imag(), 3.3, epsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Addition_ComplexDoubleMatrix_FloatMatrix)
{
    const auto floatMat = Matrix<float>({1.1f,2.2f,3.3f}, 3, 1);
    const auto complexDoubleMat = Matrix<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.3}}, 3, 1);

    const auto complexDoubleMatPlusFloatMat = complexDoubleMat + floatMat;
    ASSERT_NEAR(complexDoubleMatPlusFloatMat(0,0).real(), 2.2, fepsilon);   ASSERT_NEAR(complexDoubleMatPlusFloatMat(0,0).imag(), 1.1, fepsilon);
    ASSERT_NEAR(complexDoubleMatPlusFloatMat(1,0).real(), 4.4, fepsilon);   ASSERT_NEAR(complexDoubleMatPlusFloatMat(1,0).imag(), 2.2, fepsilon);
    ASSERT_NEAR(complexDoubleMatPlusFloatMat(2,0).real(), 6.6, fepsilon);   ASSERT_NEAR(complexDoubleMatPlusFloatMat(2,0).imag(), 3.3, fepsilon);

    const auto floatMatPlusComplexDoubleMat = floatMat + complexDoubleMat;
    ASSERT_NEAR(floatMatPlusComplexDoubleMat(0,0).real(), 2.2, fepsilon);   ASSERT_NEAR(floatMatPlusComplexDoubleMat(0,0).imag(), 1.1, fepsilon);
    ASSERT_NEAR(floatMatPlusComplexDoubleMat(1,0).real(), 4.4, fepsilon);   ASSERT_NEAR(floatMatPlusComplexDoubleMat(1,0).imag(), 2.2, fepsilon);
    ASSERT_NEAR(floatMatPlusComplexDoubleMat(2,0).real(), 6.6, fepsilon);   ASSERT_NEAR(floatMatPlusComplexDoubleMat(2,0).imag(), 3.3, fepsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Addition_ComplexDoubleMatrix_DoubleMatrix)
{
    const auto doubleMat = Matrix<double>({1.1,2.2,3.3}, 3, 1);
    const auto complexDoubleMat = Matrix<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.3}}, 3, 1);

    const auto complexDoubleMatPlusDoubleMat = complexDoubleMat + doubleMat;
    ASSERT_NEAR(complexDoubleMatPlusDoubleMat(0,0).real(), 2.2, epsilon);   ASSERT_NEAR(complexDoubleMatPlusDoubleMat(0,0).imag(), 1.1, epsilon);
    ASSERT_NEAR(complexDoubleMatPlusDoubleMat(1,0).real(), 4.4, epsilon);   ASSERT_NEAR(complexDoubleMatPlusDoubleMat(1,0).imag(), 2.2, epsilon);
    ASSERT_NEAR(complexDoubleMatPlusDoubleMat(2,0).real(), 6.6, epsilon);   ASSERT_NEAR(complexDoubleMatPlusDoubleMat(2,0).imag(), 3.3, epsilon);

    const auto doubleMatPlusComplexDoubleMat = doubleMat + complexDoubleMat;
    ASSERT_NEAR(doubleMatPlusComplexDoubleMat(0,0).real(), 2.2, epsilon);   ASSERT_NEAR(doubleMatPlusComplexDoubleMat(0,0).imag(), 1.1, epsilon);
    ASSERT_NEAR(doubleMatPlusComplexDoubleMat(1,0).real(), 4.4, epsilon);   ASSERT_NEAR(doubleMatPlusComplexDoubleMat(1,0).imag(), 2.2, epsilon);
    ASSERT_NEAR(doubleMatPlusComplexDoubleMat(2,0).real(), 6.6, epsilon);   ASSERT_NEAR(doubleMatPlusComplexDoubleMat(2,0).imag(), 3.3, epsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Addition_ComplexDoubleMatrix_LongDoubleMatrix)
{
    const auto doubleMat = Matrix<long double>({1.1,2.2,3.3}, 3, 1);
    const auto complexDoubleMat = Matrix<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.3}}, 3, 1);

    const auto complexDoubleMatPlusDoubleMat = complexDoubleMat + doubleMat;
    ASSERT_NEAR(complexDoubleMatPlusDoubleMat(0,0).real(), 2.2, epsilon);   ASSERT_NEAR(complexDoubleMatPlusDoubleMat(0,0).imag(), 1.1, epsilon);
    ASSERT_NEAR(complexDoubleMatPlusDoubleMat(1,0).real(), 4.4, epsilon);   ASSERT_NEAR(complexDoubleMatPlusDoubleMat(1,0).imag(), 2.2, epsilon);
    ASSERT_NEAR(complexDoubleMatPlusDoubleMat(2,0).real(), 6.6, epsilon);   ASSERT_NEAR(complexDoubleMatPlusDoubleMat(2,0).imag(), 3.3, epsilon);

    const auto doubleMatPlusComplexDoubleMat = doubleMat + complexDoubleMat;
    ASSERT_NEAR(doubleMatPlusComplexDoubleMat(0,0).real(), 2.2, epsilon);   ASSERT_NEAR(doubleMatPlusComplexDoubleMat(0,0).imag(), 1.1, epsilon);
    ASSERT_NEAR(doubleMatPlusComplexDoubleMat(1,0).real(), 4.4, epsilon);   ASSERT_NEAR(doubleMatPlusComplexDoubleMat(1,0).imag(), 2.2, epsilon);
    ASSERT_NEAR(doubleMatPlusComplexDoubleMat(2,0).real(), 6.6, epsilon);   ASSERT_NEAR(doubleMatPlusComplexDoubleMat(2,0).imag(), 3.3, epsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Addition_ComplexDoubleMatrix_ComplexDoubleMatrix)
{
    const auto complexDoubleVec = Matrix<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.3}}, 3, 1);

    const auto res = complexDoubleVec + complexDoubleVec;
    ASSERT_NEAR(res(0,0).real(), 2.2, epsilon);   ASSERT_NEAR(res(0,0).imag(), 2.2, epsilon);
    ASSERT_NEAR(res(1,0).real(), 4.4, epsilon);   ASSERT_NEAR(res(1,0).imag(), 4.4, epsilon);
    ASSERT_NEAR(res(2,0).real(), 6.6, epsilon);   ASSERT_NEAR(res(2,0).imag(), 6.6, epsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Addition_ComplexDoubleMatrix_ComplexLongDoubleMatrix)
{
    const auto complexDoubleMat = Matrix<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.3}}, 3, 1);
    const auto complexLongDoubleMat = Matrix<std::complex<long double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.4}}, 3, 1);

    const auto res = complexDoubleMat + complexLongDoubleMat;
    ASSERT_NEAR(res(0,0).real(), 2.2, epsilon);   ASSERT_NEAR(res(0,0).imag(), 2.2, epsilon);
    ASSERT_NEAR(res(1,0).real(), 4.4, epsilon);   ASSERT_NEAR(res(1,0).imag(), 4.4, epsilon);
    ASSERT_NEAR(res(2,0).real(), 6.6, epsilon);   ASSERT_NEAR(res(2,0).imag(), 6.7, epsilon);

    const auto res2 = complexLongDoubleMat + complexDoubleMat;
    ASSERT_NEAR(res2(0,0).real(), 2.2, epsilon);   ASSERT_NEAR(res2(0,0).imag(), 2.2, epsilon);
    ASSERT_NEAR(res2(1,0).real(), 4.4, epsilon);   ASSERT_NEAR(res2(1,0).imag(), 4.4, epsilon);
    ASSERT_NEAR(res2(2,0).real(), 6.6, epsilon);   ASSERT_NEAR(res2(2,0).imag(), 6.7, epsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Subtraction_ComplexIntMatrix_IntMatrix)
{
    const auto intMat = Matrix<int>({1,2,3}, 3, 1);
    const auto complexIntMat = Matrix<std::complex<int>>({{1,1}, {2,2}, {3,3}}, 3, 1);

    const auto intMatMinusComplexIntMat = intMat - complexIntMat;
    ASSERT_EQ(intMatMinusComplexIntMat(0,0), std::complex<int>(0,-1));
    ASSERT_EQ(intMatMinusComplexIntMat(1,0), std::complex<int>(0,-2));
    ASSERT_EQ(intMatMinusComplexIntMat(2,0), std::complex<int>(0,-3));

    const auto complexIntMatMinusIntMat = complexIntMat - intMat;
    ASSERT_EQ(complexIntMatMinusIntMat(0,0), std::complex<int>(0,1));
    ASSERT_EQ(complexIntMatMinusIntMat(1,0), std::complex<int>(0,2));
    ASSERT_EQ(complexIntMatMinusIntMat(2,0), std::complex<int>(0,3));
}

TEST_F(ComplexMatrixArithmeticTests, Subtraction_ComplexIntMatrix_FloatMatrix)
{
    const auto floatMat = Matrix<float>({1.1f,2.2f,3.3f}, 3, 1);
    const auto complexIntMat = Matrix<std::complex<int>>({{1,1}, {2,2}, {3,3}}, 3, 1);

    const auto floatMatMinusComplexIntMat = floatMat - complexIntMat;
    ASSERT_NEAR(floatMatMinusComplexIntMat(0,0).real(), 0.1f, fepsilon);   ASSERT_NEAR(floatMatMinusComplexIntMat(0,0).imag(), -1.0f, fepsilon);
    ASSERT_NEAR(floatMatMinusComplexIntMat(1,0).real(), 0.2f, fepsilon);   ASSERT_NEAR(floatMatMinusComplexIntMat(1,0).imag(), -2.0f, fepsilon);
    ASSERT_NEAR(floatMatMinusComplexIntMat(2,0).real(), 0.3f, fepsilon);   ASSERT_NEAR(floatMatMinusComplexIntMat(2,0).imag(), -3.0f, fepsilon);

    const auto complexIntMatMinusFloatMat = complexIntMat - floatMat;
    ASSERT_NEAR(complexIntMatMinusFloatMat(0,0).real(), -0.1f, fepsilon);   ASSERT_NEAR(complexIntMatMinusFloatMat(0,0).imag(), 1.0f, fepsilon);
    ASSERT_NEAR(complexIntMatMinusFloatMat(1,0).real(), -0.2f, fepsilon);   ASSERT_NEAR(complexIntMatMinusFloatMat(1,0).imag(), 2.0f, fepsilon);
    ASSERT_NEAR(complexIntMatMinusFloatMat(2,0).real(), -0.3f, fepsilon);   ASSERT_NEAR(complexIntMatMinusFloatMat(2,0).imag(), 3.0f, fepsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Subtraction_ComplexIntMatrix_DoubleMatrix)
{
    const auto doubleMat = Matrix<double>({1.1,2.2,3.3}, 3, 1);
    const auto complexIntMat = Matrix<std::complex<int>>({{1,1}, {2,2}, {3,3}}, 3, 1);

    const auto doubleMatMinusComplexIntMat = doubleMat - complexIntMat;
    ASSERT_NEAR(doubleMatMinusComplexIntMat(0,0).real(), 0.1, epsilon);   ASSERT_NEAR(doubleMatMinusComplexIntMat(0,0).imag(), -1.0, epsilon);
    ASSERT_NEAR(doubleMatMinusComplexIntMat(1,0).real(), 0.2, epsilon);   ASSERT_NEAR(doubleMatMinusComplexIntMat(1,0).imag(), -2.0, epsilon);
    ASSERT_NEAR(doubleMatMinusComplexIntMat(2,0).real(), 0.3, epsilon);   ASSERT_NEAR(doubleMatMinusComplexIntMat(2,0).imag(), -3.0, epsilon);

    const auto complexIntMatMinusDoubleMat = complexIntMat - doubleMat;
    ASSERT_NEAR(complexIntMatMinusDoubleMat(0,0).real(), -0.1, epsilon);   ASSERT_NEAR(complexIntMatMinusDoubleMat(0,0).imag(), 1.0, epsilon);
    ASSERT_NEAR(complexIntMatMinusDoubleMat(1,0).real(), -0.2, epsilon);   ASSERT_NEAR(complexIntMatMinusDoubleMat(1,0).imag(), 2.0, epsilon);
    ASSERT_NEAR(complexIntMatMinusDoubleMat(2,0).real(), -0.3, epsilon);   ASSERT_NEAR(complexIntMatMinusDoubleMat(2,0).imag(), 3.0, epsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Subtraction_ComplexIntMatrix_LongDoubleMatrix)
{
    const auto doubleMat = Matrix<long double>({1.1,2.2,3.3}, 3, 1);
    const auto complexIntMat = Matrix<std::complex<int>>({{1,1}, {2,2}, {3,3}}, 3, 1);

    const auto doubleMatMinusComplexIntMat = doubleMat - complexIntMat;
    ASSERT_NEAR(doubleMatMinusComplexIntMat(0,0).real(), 0.1, epsilon);   ASSERT_NEAR(doubleMatMinusComplexIntMat(0,0).imag(), -1.0, epsilon);
    ASSERT_NEAR(doubleMatMinusComplexIntMat(1,0).real(), 0.2, epsilon);   ASSERT_NEAR(doubleMatMinusComplexIntMat(1,0).imag(), -2.0, epsilon);
    ASSERT_NEAR(doubleMatMinusComplexIntMat(2,0).real(), 0.3, epsilon);   ASSERT_NEAR(doubleMatMinusComplexIntMat(2,0).imag(), -3.0, epsilon);

    const auto complexIntMatMinusDoubleMat = complexIntMat - doubleMat;
    ASSERT_NEAR(complexIntMatMinusDoubleMat(0,0).real(), -0.1, epsilon);   ASSERT_NEAR(complexIntMatMinusDoubleMat(0,0).imag(), 1.0, epsilon);
    ASSERT_NEAR(complexIntMatMinusDoubleMat(1,0).real(), -0.2, epsilon);   ASSERT_NEAR(complexIntMatMinusDoubleMat(1,0).imag(), 2.0, epsilon);
    ASSERT_NEAR(complexIntMatMinusDoubleMat(2,0).real(), -0.3, epsilon);   ASSERT_NEAR(complexIntMatMinusDoubleMat(2,0).imag(), 3.0, epsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Subtraction_ComplexIntMatrix_ComplexIntMatrix)
{
    const auto complexIntMat = Matrix<std::complex<int>>({{1,1}, {2,2}, {3,3}}, 3, 1);

    const auto res = complexIntMat - complexIntMat;
    ASSERT_EQ(res(0,0), std::complex<int>(0,0));
    ASSERT_EQ(res(1,0), std::complex<int>(0,0));
    ASSERT_EQ(res(2,0), std::complex<int>(0,0));
}

TEST_F(ComplexMatrixArithmeticTests, Subtraction_ComplexIntMatrix_ComplexFloatMatrix)
{
    const auto complexIntMat = Matrix<std::complex<int>>({{1,1}, {2,2}, {3,3}}, 3, 1);
    const auto complexFloatMat = Matrix<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.4f}}, 3, 1);

    const auto res = complexIntMat - complexFloatMat;
    ASSERT_NEAR(res(0,0).real(), -0.1f, fepsilon);   ASSERT_NEAR(res(0,0).imag(), -0.1f, fepsilon);
    ASSERT_NEAR(res(1,0).real(), -0.2f, fepsilon);   ASSERT_NEAR(res(1,0).imag(), -0.2f, fepsilon);
    ASSERT_NEAR(res(2,0).real(), -0.3f, fepsilon);   ASSERT_NEAR(res(2,0).imag(), -0.4f, fepsilon);

    const auto res2 = complexFloatMat - complexIntMat;
    ASSERT_NEAR(res2(0,0).real(), 0.1f, fepsilon);   ASSERT_NEAR(res2(0,0).imag(), 0.1f, fepsilon);
    ASSERT_NEAR(res2(1,0).real(), 0.2f, fepsilon);   ASSERT_NEAR(res2(1,0).imag(), 0.2f, fepsilon);
    ASSERT_NEAR(res2(2,0).real(), 0.3f, fepsilon);   ASSERT_NEAR(res2(2,0).imag(), 0.4f, fepsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Subtraction_ComplexIntMatrix_ComplexDoubleMatrix)
{
    const auto complexIntMat = Matrix<std::complex<int>>({{1,1}, {2,2}, {3,3}}, 3, 1);
    const auto complexDoubleMat = Matrix<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.4}}, 3, 1);

    const auto res = complexIntMat - complexDoubleMat;
    ASSERT_NEAR(res(0,0).real(), -0.1, epsilon);   ASSERT_NEAR(res(0,0).imag(), -0.1, epsilon);
    ASSERT_NEAR(res(1,0).real(), -0.2, epsilon);   ASSERT_NEAR(res(1,0).imag(), -0.2, epsilon);
    ASSERT_NEAR(res(2,0).real(), -0.3, epsilon);   ASSERT_NEAR(res(2,0).imag(), -0.4, epsilon);

    const auto res2 = complexDoubleMat - complexIntMat;
    ASSERT_NEAR(res2(0,0).real(), 0.1, epsilon);   ASSERT_NEAR(res2(0,0).imag(), 0.1, epsilon);
    ASSERT_NEAR(res2(1,0).real(), 0.2, epsilon);   ASSERT_NEAR(res2(1,0).imag(), 0.2, epsilon);
    ASSERT_NEAR(res2(2,0).real(), 0.3, epsilon);   ASSERT_NEAR(res2(2,0).imag(), 0.4, epsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Subtraction_ComplexIntMatrix_ComplexLongDoubleMatrix)
{
    const auto complexIntMat = Matrix<std::complex<int>>({{1,1}, {2,2}, {3,3}}, 3, 1);
    const auto complexDoubleMat = Matrix<std::complex<long double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.4}}, 3, 1);

    const auto res = complexIntMat - complexDoubleMat;
    ASSERT_NEAR(res(0,0).real(), -0.1, epsilon);   ASSERT_NEAR(res(0,0).imag(), -0.1, epsilon);
    ASSERT_NEAR(res(1,0).real(), -0.2, epsilon);   ASSERT_NEAR(res(1,0).imag(), -0.2, epsilon);
    ASSERT_NEAR(res(2,0).real(), -0.3, epsilon);   ASSERT_NEAR(res(2,0).imag(), -0.4, epsilon);

    const auto res2 = complexDoubleMat - complexIntMat;
    ASSERT_NEAR(res2(0,0).real(), 0.1, epsilon);   ASSERT_NEAR(res2(0,0).imag(), 0.1, epsilon);
    ASSERT_NEAR(res2(1,0).real(), 0.2, epsilon);   ASSERT_NEAR(res2(1,0).imag(), 0.2, epsilon);
    ASSERT_NEAR(res2(2,0).real(), 0.3, epsilon);   ASSERT_NEAR(res2(2,0).imag(), 0.4, epsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Subtraction_ComplexFloatMatrix_IntMatrix)
{
    const auto intMat = Matrix<int>({1,2,3}, 3, 1);
    const auto complexFloatMat = Matrix<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}}, 3, 1);

    const auto complexFloatMatMinusIntMat = complexFloatMat - intMat;
    ASSERT_NEAR(complexFloatMatMinusIntMat(0,0).real(), 0.1f, fepsilon);   ASSERT_NEAR(complexFloatMatMinusIntMat(0,0).imag(), 1.1f, fepsilon);
    ASSERT_NEAR(complexFloatMatMinusIntMat(1,0).real(), 0.2f, fepsilon);   ASSERT_NEAR(complexFloatMatMinusIntMat(1,0).imag(), 2.2f, fepsilon);
    ASSERT_NEAR(complexFloatMatMinusIntMat(2,0).real(), 0.3f, fepsilon);   ASSERT_NEAR(complexFloatMatMinusIntMat(2,0).imag(), 3.3f, fepsilon);

    const auto intMatMinusComplexFloatMat = intMat - complexFloatMat;
    ASSERT_NEAR(intMatMinusComplexFloatMat(0,0).real(), -0.1f, fepsilon);   ASSERT_NEAR(intMatMinusComplexFloatMat(0,0).imag(), -1.1f, fepsilon);
    ASSERT_NEAR(intMatMinusComplexFloatMat(1,0).real(), -0.2f, fepsilon);   ASSERT_NEAR(intMatMinusComplexFloatMat(1,0).imag(), -2.2f, fepsilon);
    ASSERT_NEAR(intMatMinusComplexFloatMat(2,0).real(), -0.3f, fepsilon);   ASSERT_NEAR(intMatMinusComplexFloatMat(2,0).imag(), -3.3f, fepsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Subtraction_ComplexFloatMatrix_FloatMatrix)
{
    const auto floatMat = Matrix<float>({1.1f,2.2f,3.3f}, 3, 1);
    const auto complexFloatMat = Matrix<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}}, 3, 1);

    const auto complexFloatMatMinusFloatMat = complexFloatMat - floatMat;
    ASSERT_NEAR(complexFloatMatMinusFloatMat(0,0).real(), 0.0f, fepsilon);   ASSERT_NEAR(complexFloatMatMinusFloatMat(0,0).imag(), 1.1f, fepsilon);
    ASSERT_NEAR(complexFloatMatMinusFloatMat(1,0).real(), 0.0f, fepsilon);   ASSERT_NEAR(complexFloatMatMinusFloatMat(1,0).imag(), 2.2f, fepsilon);
    ASSERT_NEAR(complexFloatMatMinusFloatMat(2,0).real(), 0.0f, fepsilon);   ASSERT_NEAR(complexFloatMatMinusFloatMat(2,0).imag(), 3.3f, fepsilon);

    const auto floatMatMinusComplexFloatMat = floatMat - complexFloatMat;
    ASSERT_NEAR(floatMatMinusComplexFloatMat(0,0).real(), 0.0f, fepsilon);   ASSERT_NEAR(floatMatMinusComplexFloatMat(0,0).imag(), -1.1f, fepsilon);
    ASSERT_NEAR(floatMatMinusComplexFloatMat(1,0).real(), 0.0f, fepsilon);   ASSERT_NEAR(floatMatMinusComplexFloatMat(1,0).imag(), -2.2f, fepsilon);
    ASSERT_NEAR(floatMatMinusComplexFloatMat(2,0).real(), 0.0f, fepsilon);   ASSERT_NEAR(floatMatMinusComplexFloatMat(2,0).imag(), -3.3f, fepsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Subtraction_ComplexFloatMatrix_DoubleMatrix)
{
    const auto doubleMat = Matrix<double>({1.1,2.2,3.3}, 3, 1);
    const auto complexFloatMat = Matrix<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}}, 3, 1);

    const auto complexFloatMatMinusDoubleMat = complexFloatMat - doubleMat;
    ASSERT_NEAR(complexFloatMatMinusDoubleMat(0,0).real(), 0.0, fepsilon);   ASSERT_NEAR(complexFloatMatMinusDoubleMat(0,0).imag(), 1.1, fepsilon);
    ASSERT_NEAR(complexFloatMatMinusDoubleMat(1,0).real(), 0.0, fepsilon);   ASSERT_NEAR(complexFloatMatMinusDoubleMat(1,0).imag(), 2.2, fepsilon);
    ASSERT_NEAR(complexFloatMatMinusDoubleMat(2,0).real(), 0.0, fepsilon);   ASSERT_NEAR(complexFloatMatMinusDoubleMat(2,0).imag(), 3.3, fepsilon);

    const auto doubleMatMinusComplexFloatMat = doubleMat - complexFloatMat;
    ASSERT_NEAR(doubleMatMinusComplexFloatMat(0,0).real(), 0.0, fepsilon);   ASSERT_NEAR(doubleMatMinusComplexFloatMat(0,0).imag(), -1.1, fepsilon);
    ASSERT_NEAR(doubleMatMinusComplexFloatMat(1,0).real(), 0.0, fepsilon);   ASSERT_NEAR(doubleMatMinusComplexFloatMat(1,0).imag(), -2.2, fepsilon);
    ASSERT_NEAR(doubleMatMinusComplexFloatMat(2,0).real(), 0.0, fepsilon);   ASSERT_NEAR(doubleMatMinusComplexFloatMat(2,0).imag(), -3.3, fepsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Subtraction_ComplexFloatMatrix_LongDoubleMatrix)
{
    const auto doubleMat = Matrix<long double>({1.1,2.2,3.3}, 3, 1);
    const auto complexFloatMat = Matrix<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}}, 3, 1);

    const auto complexFloatMatMinusDoubleMat = complexFloatMat - doubleMat;
    ASSERT_NEAR(complexFloatMatMinusDoubleMat(0,0).real(), 0.0, fepsilon);   ASSERT_NEAR(complexFloatMatMinusDoubleMat(0,0).imag(), 1.1, fepsilon);
    ASSERT_NEAR(complexFloatMatMinusDoubleMat(1,0).real(), 0.0, fepsilon);   ASSERT_NEAR(complexFloatMatMinusDoubleMat(1,0).imag(), 2.2, fepsilon);
    ASSERT_NEAR(complexFloatMatMinusDoubleMat(2,0).real(), 0.0, fepsilon);   ASSERT_NEAR(complexFloatMatMinusDoubleMat(2,0).imag(), 3.3, fepsilon);

    const auto doubleMatMinusComplexFloatMat = doubleMat - complexFloatMat;
    ASSERT_NEAR(doubleMatMinusComplexFloatMat(0,0).real(), 0.0, fepsilon);   ASSERT_NEAR(doubleMatMinusComplexFloatMat(0,0).imag(), -1.1, fepsilon);
    ASSERT_NEAR(doubleMatMinusComplexFloatMat(1,0).real(), 0.0, fepsilon);   ASSERT_NEAR(doubleMatMinusComplexFloatMat(1,0).imag(), -2.2, fepsilon);
    ASSERT_NEAR(doubleMatMinusComplexFloatMat(2,0).real(), 0.0, fepsilon);   ASSERT_NEAR(doubleMatMinusComplexFloatMat(2,0).imag(), -3.3, fepsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Subtraction_ComplexFloatMatrix_ComplexFloatMatrix)
{
    const auto complexFloatMat = Matrix<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}}, 3, 1);

    const auto res = complexFloatMat - complexFloatMat;
    ASSERT_NEAR(res(0,0).real(), 0.0f, fepsilon);   ASSERT_NEAR(res(0,0).imag(), 0.0f, fepsilon);
    ASSERT_NEAR(res(1,0).real(), 0.0f, fepsilon);   ASSERT_NEAR(res(1,0).imag(), 0.0f, fepsilon);
    ASSERT_NEAR(res(2,0).real(), 0.0f, fepsilon);   ASSERT_NEAR(res(2,0).imag(), 0.0f, fepsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Subtraction_ComplexFloatMatrix_ComplexDoubleMatrix)
{
    const auto complexFloatMat = Matrix<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}}, 3, 1);
    const auto complexDoubleMat = Matrix<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.4}}, 3, 1);

    const auto res = complexFloatMat - complexDoubleMat;
    ASSERT_NEAR(res(0,0).real(), 0.0, fepsilon);   ASSERT_NEAR(res(0,0).imag(), 0.0, fepsilon);
    ASSERT_NEAR(res(1,0).real(), 0.0, fepsilon);   ASSERT_NEAR(res(1,0).imag(), 0.0, fepsilon);
    ASSERT_NEAR(res(2,0).real(), 0.0, fepsilon);   ASSERT_NEAR(res(2,0).imag(), -0.1, fepsilon);

    const auto res2 = complexDoubleMat - complexFloatMat;
    ASSERT_NEAR(res2(0,0).real(), 0.0, fepsilon);   ASSERT_NEAR(res2(0,0).imag(), 0.0, fepsilon);
    ASSERT_NEAR(res2(1,0).real(), 0.0, fepsilon);   ASSERT_NEAR(res2(1,0).imag(), 0.0, fepsilon);
    ASSERT_NEAR(res2(2,0).real(), 0.0, fepsilon);   ASSERT_NEAR(res2(2,0).imag(), 0.1, fepsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Subtraction_ComplexFloatMatrix_ComplexLongDoubleMatrix)
{
    const auto complexFloatMat = Matrix<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}}, 3, 1);
    const auto complexDoubleMat = Matrix<std::complex<long double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.4}}, 3, 1);

    const auto res = complexFloatMat - complexDoubleMat;
    ASSERT_NEAR(res(0,0).real(), 0.0, fepsilon);   ASSERT_NEAR(res(0,0).imag(), 0.0, fepsilon);
    ASSERT_NEAR(res(1,0).real(), 0.0, fepsilon);   ASSERT_NEAR(res(1,0).imag(), 0.0, fepsilon);
    ASSERT_NEAR(res(2,0).real(), 0.0, fepsilon);   ASSERT_NEAR(res(2,0).imag(), -0.1, fepsilon);

    const auto res2 = complexDoubleMat - complexFloatMat;
    ASSERT_NEAR(res2(0,0).real(), 0.0, fepsilon);   ASSERT_NEAR(res2(0,0).imag(), 0.0, fepsilon);
    ASSERT_NEAR(res2(1,0).real(), 0.0, fepsilon);   ASSERT_NEAR(res2(1,0).imag(), 0.0, fepsilon);
    ASSERT_NEAR(res2(2,0).real(), 0.0, fepsilon);   ASSERT_NEAR(res2(2,0).imag(), 0.1, fepsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Subtraction_ComplexDoubleMatrix_IntMatrix)
{
    const auto intMat = Matrix<int>({1,2,3}, 3, 1);
    const auto complexDoubleMat = Matrix<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.3}}, 3, 1);

    const auto complexDoubleMatMinusIntMat = complexDoubleMat - intMat;
    ASSERT_NEAR(complexDoubleMatMinusIntMat(0,0).real(), 0.1, epsilon);   ASSERT_NEAR(complexDoubleMatMinusIntMat(0,0).imag(), 1.1, epsilon);
    ASSERT_NEAR(complexDoubleMatMinusIntMat(1,0).real(), 0.2, epsilon);   ASSERT_NEAR(complexDoubleMatMinusIntMat(1,0).imag(), 2.2, epsilon);
    ASSERT_NEAR(complexDoubleMatMinusIntMat(2,0).real(), 0.3, epsilon);   ASSERT_NEAR(complexDoubleMatMinusIntMat(2,0).imag(), 3.3, epsilon);

    const auto intMatMinusComplexDoubleMat = intMat - complexDoubleMat;
    ASSERT_NEAR(intMatMinusComplexDoubleMat(0,0).real(), -0.1, epsilon);   ASSERT_NEAR(intMatMinusComplexDoubleMat(0,0).imag(), -1.1, epsilon);
    ASSERT_NEAR(intMatMinusComplexDoubleMat(1,0).real(), -0.2, epsilon);   ASSERT_NEAR(intMatMinusComplexDoubleMat(1,0).imag(), -2.2, epsilon);
    ASSERT_NEAR(intMatMinusComplexDoubleMat(2,0).real(), -0.3, epsilon);   ASSERT_NEAR(intMatMinusComplexDoubleMat(2,0).imag(), -3.3, epsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Subtraction_ComplexDoubleMatrix_FloatMatrix)
{
    const auto floatMat = Matrix<float>({1.1f,2.2f,3.3f}, 3, 1);
    const auto complexDoubleMat = Matrix<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.3}}, 3, 1);

    const auto complexDoubleMatMinusFloatMat = complexDoubleMat - floatMat;
    ASSERT_NEAR(complexDoubleMatMinusFloatMat(0,0).real(), 0.0, fepsilon);   ASSERT_NEAR(complexDoubleMatMinusFloatMat(0,0).imag(), 1.1, fepsilon);
    ASSERT_NEAR(complexDoubleMatMinusFloatMat(1,0).real(), 0.0, fepsilon);   ASSERT_NEAR(complexDoubleMatMinusFloatMat(1,0).imag(), 2.2, fepsilon);
    ASSERT_NEAR(complexDoubleMatMinusFloatMat(2,0).real(), 0.0, fepsilon);   ASSERT_NEAR(complexDoubleMatMinusFloatMat(2,0).imag(), 3.3, fepsilon);

    const auto floatMatMinusComplexDoubleMat = floatMat - complexDoubleMat;
    ASSERT_NEAR(floatMatMinusComplexDoubleMat(0,0).real(), 0.0, fepsilon);   ASSERT_NEAR(floatMatMinusComplexDoubleMat(0,0).imag(), -1.1, fepsilon);
    ASSERT_NEAR(floatMatMinusComplexDoubleMat(1,0).real(), 0.0, fepsilon);   ASSERT_NEAR(floatMatMinusComplexDoubleMat(1,0).imag(), -2.2, fepsilon);
    ASSERT_NEAR(floatMatMinusComplexDoubleMat(2,0).real(), 0.0, fepsilon);   ASSERT_NEAR(floatMatMinusComplexDoubleMat(2,0).imag(), -3.3, fepsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Subtraction_ComplexDoubleMatrix_DoubleMatrix)
{
    const auto doubleMat = Matrix<double>({1.1,2.2,3.3}, 3, 1);
    const auto complexDoubleMat = Matrix<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.3}}, 3, 1);

    const auto complexDoubleMatMinusDoubleMat = complexDoubleMat - doubleMat;
    ASSERT_NEAR(complexDoubleMatMinusDoubleMat(0,0).real(), 0.0, epsilon);   ASSERT_NEAR(complexDoubleMatMinusDoubleMat(0,0).imag(), 1.1, epsilon);
    ASSERT_NEAR(complexDoubleMatMinusDoubleMat(1,0).real(), 0.0, epsilon);   ASSERT_NEAR(complexDoubleMatMinusDoubleMat(1,0).imag(), 2.2, epsilon);
    ASSERT_NEAR(complexDoubleMatMinusDoubleMat(2,0).real(), 0.0, epsilon);   ASSERT_NEAR(complexDoubleMatMinusDoubleMat(2,0).imag(), 3.3, epsilon);

    const auto doubleMatMinusComplexDoubleMat = doubleMat - complexDoubleMat;
    ASSERT_NEAR(doubleMatMinusComplexDoubleMat(0,0).real(), 0.0, epsilon);   ASSERT_NEAR(doubleMatMinusComplexDoubleMat(0,0).imag(), -1.1, epsilon);
    ASSERT_NEAR(doubleMatMinusComplexDoubleMat(1,0).real(), 0.0, epsilon);   ASSERT_NEAR(doubleMatMinusComplexDoubleMat(1,0).imag(), -2.2, epsilon);
    ASSERT_NEAR(doubleMatMinusComplexDoubleMat(2,0).real(), 0.0, epsilon);   ASSERT_NEAR(doubleMatMinusComplexDoubleMat(2,0).imag(), -3.3, epsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Subtraction_ComplexDoubleMatrix_LongDoubleMatrix)
{
    const auto doubleMat = Matrix<long double>({1.1,2.2,3.3}, 3, 1);
    const auto complexDoubleMat = Matrix<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.3}}, 3, 1);

    const auto complexDoubleMatMinusDoubleMat = complexDoubleMat - doubleMat;
    ASSERT_NEAR(complexDoubleMatMinusDoubleMat(0,0).real(), 0.0, epsilon);   ASSERT_NEAR(complexDoubleMatMinusDoubleMat(0,0).imag(), 1.1, epsilon);
    ASSERT_NEAR(complexDoubleMatMinusDoubleMat(1,0).real(), 0.0, epsilon);   ASSERT_NEAR(complexDoubleMatMinusDoubleMat(1,0).imag(), 2.2, epsilon);
    ASSERT_NEAR(complexDoubleMatMinusDoubleMat(2,0).real(), 0.0, epsilon);   ASSERT_NEAR(complexDoubleMatMinusDoubleMat(2,0).imag(), 3.3, epsilon);

    const auto doubleMatMinusComplexDoubleMat = doubleMat - complexDoubleMat;
    ASSERT_NEAR(doubleMatMinusComplexDoubleMat(0,0).real(), 0.0, epsilon);   ASSERT_NEAR(doubleMatMinusComplexDoubleMat(0,0).imag(), -1.1, epsilon);
    ASSERT_NEAR(doubleMatMinusComplexDoubleMat(1,0).real(), 0.0, epsilon);   ASSERT_NEAR(doubleMatMinusComplexDoubleMat(1,0).imag(), -2.2, epsilon);
    ASSERT_NEAR(doubleMatMinusComplexDoubleMat(2,0).real(), 0.0, epsilon);   ASSERT_NEAR(doubleMatMinusComplexDoubleMat(2,0).imag(), -3.3, epsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Subtraction_ComplexDoubleVector_ComplexDoubleVector)
{
    const auto complexDoubleMat = Matrix<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.3}}, 3, 1);

    const auto res = complexDoubleMat - complexDoubleMat;
    ASSERT_NEAR(res(0,0).real(), 0.0, epsilon);   ASSERT_NEAR(res(0,0).imag(), 0.0, epsilon);
    ASSERT_NEAR(res(0,0).real(), 0.0, epsilon);   ASSERT_NEAR(res(0,0).imag(), 0.0, epsilon);
    ASSERT_NEAR(res(0,0).real(), 0.0, epsilon);   ASSERT_NEAR(res(0,0).imag(), 0.0, epsilon);
}

TEST_F(ComplexMatrixArithmeticTests, Subtraction_ComplexDoubleVector_ComplexLongDoubleVector)
{
    const auto complexDoubleMat = Matrix<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.3}}, 3, 1);
    const auto complexLongDoubleMat = Matrix<std::complex<long double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.4}}, 3, 1);

    const auto res = complexDoubleMat - complexLongDoubleMat;
    ASSERT_NEAR(res(0,0).real(), 0.0, epsilon);   ASSERT_NEAR(res(0,0).imag(), 0.0, epsilon);
    ASSERT_NEAR(res(1,0).real(), 0.0, epsilon);   ASSERT_NEAR(res(1,0).imag(), 0.0, epsilon);
    ASSERT_NEAR(res(2,0).real(), 0.0, epsilon);   ASSERT_NEAR(res(2,0).imag(), -0.1, epsilon);

    const auto res2 = complexLongDoubleMat - complexDoubleMat;
    ASSERT_NEAR(res2(0,0).real(), 0.0, epsilon);   ASSERT_NEAR(res2(0,0).imag(), 0.0, epsilon);
    ASSERT_NEAR(res2(1,0).real(), 0.0, epsilon);   ASSERT_NEAR(res2(1,0).imag(), 0.0, epsilon);
    ASSERT_NEAR(res2(2,0).real(), 0.0, epsilon);   ASSERT_NEAR(res2(2,0).imag(), 0.1, epsilon);
}

///// in-place ops for complex matrices
TEST_F(ComplexMatrixArithmeticTests, InPlace_ComplexMatrixAddition)
{
    auto complexIntMat = Matrix<std::complex<int>>({{1,1}, {2,2}, {3,3}}, 3, 1);
    auto complexFloatMat = Matrix<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}}, 3, 1);
    auto complexDoubleMat = Matrix<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.3}}, 3, 1);
    auto complexLongDoubleMat = Matrix<std::complex<long double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.4}}, 3, 1);

    complexIntMat += complexIntMat;
    ASSERT_EQ(complexIntMat(0,0), std::complex<int>(2,2));
    ASSERT_EQ(complexIntMat(1,0), std::complex<int>(4,4));
    ASSERT_EQ(complexIntMat(2,0), std::complex<int>(6,6));

    complexFloatMat += complexFloatMat;
    ASSERT_NEAR(complexFloatMat(0,0).real(), 2.2f, fepsilon);   ASSERT_NEAR(complexFloatMat(0,0).imag(), 2.2f, fepsilon);
    ASSERT_NEAR(complexFloatMat(1,0).real(), 4.4f, fepsilon);   ASSERT_NEAR(complexFloatMat(1,0).imag(), 4.4f, fepsilon);
    ASSERT_NEAR(complexFloatMat(2,0).real(), 6.6f, fepsilon);   ASSERT_NEAR(complexFloatMat(2,0).imag(), 6.6f, fepsilon);

    complexDoubleMat += complexDoubleMat;
    ASSERT_NEAR(complexDoubleMat(0,0).real(), 2.2, epsilon);   ASSERT_NEAR(complexDoubleMat(0,0).imag(), 2.2, epsilon);
    ASSERT_NEAR(complexDoubleMat(1,0).real(), 4.4, epsilon);   ASSERT_NEAR(complexDoubleMat(1,0).imag(), 4.4, epsilon);
    ASSERT_NEAR(complexDoubleMat(2,0).real(), 6.6, epsilon);   ASSERT_NEAR(complexDoubleMat(2,0).imag(), 6.6, epsilon);

    complexLongDoubleMat += complexLongDoubleMat;
    ASSERT_NEAR(complexLongDoubleMat(0,0).real(), 2.2, epsilon);   ASSERT_NEAR(complexLongDoubleMat(0,0).imag(), 2.2, epsilon);
    ASSERT_NEAR(complexLongDoubleMat(1,0).real(), 4.4, epsilon);   ASSERT_NEAR(complexLongDoubleMat(1,0).imag(), 4.4, epsilon);
    ASSERT_NEAR(complexLongDoubleMat(2,0).real(), 6.6, epsilon);   ASSERT_NEAR(complexLongDoubleMat(2,0).imag(), 6.8, epsilon);
}

TEST_F(ComplexMatrixArithmeticTests, InPlace_ComplexMatrixSubtraction)
{
    auto complexIntMat = Matrix<std::complex<int>>({{1,1}, {2,2}, {3,3}}, 3, 1);
    auto complexFloatMat = Matrix<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}}, 3, 1);
    auto complexDoubleMat = Matrix<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.3}}, 3, 1);
    auto complexLongDoubleMat = Matrix<std::complex<long double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.4}}, 3, 1);

    complexIntMat -= complexIntMat;
    ASSERT_EQ(complexIntMat(0,0), std::complex<int>(0,0));
    ASSERT_EQ(complexIntMat(1,0), std::complex<int>(0,0));
    ASSERT_EQ(complexIntMat(2,0), std::complex<int>(0,0));

    complexFloatMat -= complexFloatMat;
    ASSERT_NEAR(complexFloatMat(0,0).real(), 0.0f, fepsilon);   ASSERT_NEAR(complexFloatMat(0,0).imag(), 0.0f, fepsilon);
    ASSERT_NEAR(complexFloatMat(1,0).real(), 0.0f, fepsilon);   ASSERT_NEAR(complexFloatMat(1,0).imag(), 0.0f, fepsilon);
    ASSERT_NEAR(complexFloatMat(2,0).real(), 0.0f, fepsilon);   ASSERT_NEAR(complexFloatMat(2,0).imag(), 0.0f, fepsilon);

    complexDoubleMat -= complexDoubleMat;
    ASSERT_NEAR(complexDoubleMat(0,0).real(), 0.0, epsilon);   ASSERT_NEAR(complexDoubleMat(0,0).imag(), 0.0, epsilon);
    ASSERT_NEAR(complexDoubleMat(1,0).real(), 0.0, epsilon);   ASSERT_NEAR(complexDoubleMat(1,0).imag(), 0.0, epsilon);
    ASSERT_NEAR(complexDoubleMat(2,0).real(), 0.0, epsilon);   ASSERT_NEAR(complexDoubleMat(2,0).imag(), 0.0, epsilon);

    complexLongDoubleMat -= complexLongDoubleMat;
    ASSERT_NEAR(complexLongDoubleMat(0,0).real(), 0.0, epsilon);   ASSERT_NEAR(complexLongDoubleMat(0,0).imag(), 0.0, epsilon);
    ASSERT_NEAR(complexLongDoubleMat(1,0).real(), 0.0, epsilon);   ASSERT_NEAR(complexLongDoubleMat(1,0).imag(), 0.0, epsilon);
    ASSERT_NEAR(complexLongDoubleMat(2,0).real(), 0.0, epsilon);   ASSERT_NEAR(complexLongDoubleMat(2,0).imag(), 0.0, epsilon);
}