//
// Created by dorian on 20.01.2024.
//
//
// Created by dorian on 16.12.2023.
// stoicadorian@gmail.com
//


#include "gtest/gtest.h"
#include "Vector.hpp"
#include <complex>

using namespace LinearAlgebra::Vector;
using namespace std::complex_literals;

class ComplexVectorTests : public ::testing::Test
{

protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

    float fepsilon = 1e-5;
    double epsilon = 1e-9;
};

TEST_F(ComplexVectorTests, Addition_ComplexIntVector_IntVector)
{
    const auto intVec = Vector<int>({1,2,3});
    const auto complexIntVec = Vector<std::complex<int>>({{1,1}, {2,2}, {3,3}});

    const auto intVecPlusComplexIntVec = intVec + complexIntVec;
    ASSERT_EQ(intVecPlusComplexIntVec[0], std::complex<int>(2,1));
    ASSERT_EQ(intVecPlusComplexIntVec[1], std::complex<int>(4,2));
    ASSERT_EQ(intVecPlusComplexIntVec[2], std::complex<int>(6,3));

    const auto complexIntVecPlusIntVec = complexIntVec + intVec;
    ASSERT_EQ(complexIntVecPlusIntVec[0], std::complex<int>(2,1));
    ASSERT_EQ(complexIntVecPlusIntVec[1], std::complex<int>(4,2));
    ASSERT_EQ(complexIntVecPlusIntVec[2], std::complex<int>(6,3));
}

TEST_F(ComplexVectorTests, Addition_ComplexIntVector_FloatVector)
{
    const auto floatVec = Vector<float>({1.1f,2.2f,3.3f});
    const auto complexIntVec = Vector<std::complex<int>>({{1,1}, {2,2}, {3,3}});

    const auto floatVecPlusComplexIntVec = floatVec + complexIntVec;
    ASSERT_NEAR(floatVecPlusComplexIntVec[0].real(), 2.1f, fepsilon);   ASSERT_NEAR(floatVecPlusComplexIntVec[0].imag(), 1.0f, fepsilon);
    ASSERT_NEAR(floatVecPlusComplexIntVec[1].real(), 4.2f, fepsilon);   ASSERT_NEAR(floatVecPlusComplexIntVec[1].imag(), 2.0f, fepsilon);
    ASSERT_NEAR(floatVecPlusComplexIntVec[2].real(), 6.3f, fepsilon);   ASSERT_NEAR(floatVecPlusComplexIntVec[2].imag(), 3.0f, fepsilon);

    const auto complexIntVecPlusFloatVec = complexIntVec + floatVec;
    ASSERT_NEAR(complexIntVecPlusFloatVec[0].real(), 2.1f, fepsilon);   ASSERT_NEAR(complexIntVecPlusFloatVec[0].imag(), 1.0f, fepsilon);
    ASSERT_NEAR(complexIntVecPlusFloatVec[1].real(), 4.2f, fepsilon);   ASSERT_NEAR(complexIntVecPlusFloatVec[1].imag(), 2.0f, fepsilon);
    ASSERT_NEAR(complexIntVecPlusFloatVec[2].real(), 6.3f, fepsilon);   ASSERT_NEAR(complexIntVecPlusFloatVec[2].imag(), 3.0f, fepsilon);
}

TEST_F(ComplexVectorTests, Addition_ComplexIntVector_DoubleVector)
{
    const auto doubleVec = Vector<double>({1.1,2.2,3.3});
    const auto complexIntVec = Vector<std::complex<int>>({{1,1}, {2,2}, {3,3}});

    const auto doubleVecPlusComplexIntVec = doubleVec + complexIntVec;
    ASSERT_NEAR(doubleVecPlusComplexIntVec[0].real(), 2.1, epsilon);   ASSERT_NEAR(doubleVecPlusComplexIntVec[0].imag(), 1.0, epsilon);
    ASSERT_NEAR(doubleVecPlusComplexIntVec[1].real(), 4.2, epsilon);   ASSERT_NEAR(doubleVecPlusComplexIntVec[1].imag(), 2.0, epsilon);
    ASSERT_NEAR(doubleVecPlusComplexIntVec[2].real(), 6.3, epsilon);   ASSERT_NEAR(doubleVecPlusComplexIntVec[2].imag(), 3.0, epsilon);

    const auto complexIntVecPlusDoubleVec = complexIntVec + doubleVec;
    ASSERT_NEAR(complexIntVecPlusDoubleVec[0].real(), 2.1, epsilon);   ASSERT_NEAR(complexIntVecPlusDoubleVec[0].imag(), 1.0, epsilon);
    ASSERT_NEAR(complexIntVecPlusDoubleVec[1].real(), 4.2, epsilon);   ASSERT_NEAR(complexIntVecPlusDoubleVec[1].imag(), 2.0, epsilon);
    ASSERT_NEAR(complexIntVecPlusDoubleVec[2].real(), 6.3, epsilon);   ASSERT_NEAR(complexIntVecPlusDoubleVec[2].imag(), 3.0, epsilon);
}

TEST_F(ComplexVectorTests, Addition_ComplexIntVector_LongDoubleVector)
{
    const auto doubleVec = Vector<long double>({1.1,2.2,3.3});
    const auto complexIntVec = Vector<std::complex<int>>({{1,1}, {2,2}, {3,3}});

    const auto doubleVecPlusComplexIntVec = doubleVec + complexIntVec;
    ASSERT_NEAR(doubleVecPlusComplexIntVec[0].real(), 2.1, epsilon);   ASSERT_NEAR(doubleVecPlusComplexIntVec[0].imag(), 1.0, epsilon);
    ASSERT_NEAR(doubleVecPlusComplexIntVec[1].real(), 4.2, epsilon);   ASSERT_NEAR(doubleVecPlusComplexIntVec[1].imag(), 2.0, epsilon);
    ASSERT_NEAR(doubleVecPlusComplexIntVec[2].real(), 6.3, epsilon);   ASSERT_NEAR(doubleVecPlusComplexIntVec[2].imag(), 3.0, epsilon);

    const auto complexIntVecPlusDoubleVec = complexIntVec + doubleVec;
    ASSERT_NEAR(complexIntVecPlusDoubleVec[0].real(), 2.1, epsilon);   ASSERT_NEAR(complexIntVecPlusDoubleVec[0].imag(), 1.0, epsilon);
    ASSERT_NEAR(complexIntVecPlusDoubleVec[1].real(), 4.2, epsilon);   ASSERT_NEAR(complexIntVecPlusDoubleVec[1].imag(), 2.0, epsilon);
    ASSERT_NEAR(complexIntVecPlusDoubleVec[2].real(), 6.3, epsilon);   ASSERT_NEAR(complexIntVecPlusDoubleVec[2].imag(), 3.0, epsilon);
}

TEST_F(ComplexVectorTests, Addition_ComplexIntVector_ComplexIntVector)
{
    const auto complexIntVec = Vector<std::complex<int>>({{1,1}, {2,2}, {3,3}});

    const auto res = complexIntVec + complexIntVec;
    ASSERT_EQ(res[0], std::complex<int>(2,2));
    ASSERT_EQ(res[1], std::complex<int>(4,4));
    ASSERT_EQ(res[2], std::complex<int>(6,6));
}

TEST_F(ComplexVectorTests, Addition_ComplexIntVector_ComplexFloatVector)
{
    const auto complexIntVec = Vector<std::complex<int>>({{1,1}, {2,2}, {3,3}});
    const auto complexFloatVec = Vector<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.4f}});

    const auto res = complexIntVec + complexFloatVec;
    ASSERT_NEAR(res[0].real(), 2.1f, fepsilon);   ASSERT_NEAR(res[0].imag(), 2.1f, fepsilon);
    ASSERT_NEAR(res[1].real(), 4.2f, fepsilon);   ASSERT_NEAR(res[1].imag(), 4.2f, fepsilon);
    ASSERT_NEAR(res[2].real(), 6.3f, fepsilon);   ASSERT_NEAR(res[2].imag(), 6.4f, fepsilon);

    const auto res2 = complexFloatVec + complexIntVec;
    ASSERT_NEAR(res2[0].real(), 2.1f, fepsilon);   ASSERT_NEAR(res2[0].imag(), 2.1f, fepsilon);
    ASSERT_NEAR(res2[1].real(), 4.2f, fepsilon);   ASSERT_NEAR(res2[1].imag(), 4.2f, fepsilon);
    ASSERT_NEAR(res2[2].real(), 6.3f, fepsilon);   ASSERT_NEAR(res2[2].imag(), 6.4f, fepsilon);
}

TEST_F(ComplexVectorTests, Addition_ComplexIntVector_ComplexDoubleVector)
{
    const auto complexIntVec = Vector<std::complex<int>>({{1,1}, {2,2}, {3,3}});
    const auto complexDoubleVec = Vector<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.4}});

    const auto res = complexIntVec + complexDoubleVec;
    ASSERT_NEAR(res[0].real(), 2.1, epsilon);   ASSERT_NEAR(res[0].imag(), 2.1, epsilon);
    ASSERT_NEAR(res[1].real(), 4.2, epsilon);   ASSERT_NEAR(res[1].imag(), 4.2, epsilon);
    ASSERT_NEAR(res[2].real(), 6.3, epsilon);   ASSERT_NEAR(res[2].imag(), 6.4, epsilon);

    const auto res2 = complexDoubleVec + complexIntVec;
    ASSERT_NEAR(res2[0].real(), 2.1, epsilon);   ASSERT_NEAR(res2[0].imag(), 2.1, epsilon);
    ASSERT_NEAR(res2[1].real(), 4.2, epsilon);   ASSERT_NEAR(res2[1].imag(), 4.2, epsilon);
    ASSERT_NEAR(res2[2].real(), 6.3, epsilon);   ASSERT_NEAR(res2[2].imag(), 6.4, epsilon);
}

TEST_F(ComplexVectorTests, Addition_ComplexIntVector_ComplexLongDoubleVector)
{
    const auto complexIntVec = Vector<std::complex<int>>({{1,1}, {2,2}, {3,3}});
    const auto complexDoubleVec = Vector<std::complex<long double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.4}});

    const auto res = complexIntVec + complexDoubleVec;
    ASSERT_NEAR(res[0].real(), 2.1, epsilon);   ASSERT_NEAR(res[0].imag(), 2.1, epsilon);
    ASSERT_NEAR(res[1].real(), 4.2, epsilon);   ASSERT_NEAR(res[1].imag(), 4.2, epsilon);
    ASSERT_NEAR(res[2].real(), 6.3, epsilon);   ASSERT_NEAR(res[2].imag(), 6.4, epsilon);

    const auto res2 = complexDoubleVec + complexIntVec;
    ASSERT_NEAR(res2[0].real(), 2.1, epsilon);   ASSERT_NEAR(res2[0].imag(), 2.1, epsilon);
    ASSERT_NEAR(res2[1].real(), 4.2, epsilon);   ASSERT_NEAR(res2[1].imag(), 4.2, epsilon);
    ASSERT_NEAR(res2[2].real(), 6.3, epsilon);   ASSERT_NEAR(res2[2].imag(), 6.4, epsilon);
}

TEST_F(ComplexVectorTests, Addition_ComplexFloatVector_IntVector)
{
    const auto intVec = Vector<int>({1,2,3});
    const auto complexFloatVec = Vector<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}});

    const auto complexFloatVecPlusIntVec = complexFloatVec + intVec;
    ASSERT_NEAR(complexFloatVecPlusIntVec[0].real(), 2.1f, fepsilon);   ASSERT_NEAR(complexFloatVecPlusIntVec[0].imag(), 1.1f, fepsilon);
    ASSERT_NEAR(complexFloatVecPlusIntVec[1].real(), 4.2f, fepsilon);   ASSERT_NEAR(complexFloatVecPlusIntVec[1].imag(), 2.2f, fepsilon);
    ASSERT_NEAR(complexFloatVecPlusIntVec[2].real(), 6.3f, fepsilon);   ASSERT_NEAR(complexFloatVecPlusIntVec[2].imag(), 3.3f, fepsilon);

    const auto intVecPlusComplexFloatVec = intVec + complexFloatVec;
    ASSERT_NEAR(intVecPlusComplexFloatVec[0].real(), 2.1f, fepsilon);   ASSERT_NEAR(intVecPlusComplexFloatVec[0].imag(), 1.1f, fepsilon);
    ASSERT_NEAR(intVecPlusComplexFloatVec[1].real(), 4.2f, fepsilon);   ASSERT_NEAR(intVecPlusComplexFloatVec[1].imag(), 2.2f, fepsilon);
    ASSERT_NEAR(intVecPlusComplexFloatVec[2].real(), 6.3f, fepsilon);   ASSERT_NEAR(intVecPlusComplexFloatVec[2].imag(), 3.3f, fepsilon);
}

TEST_F(ComplexVectorTests, Addition_ComplexFloatVector_FloatVector)
{
    const auto floatVec = Vector<float>({1.1f,2.2f,3.3f});
    const auto complexFloatVec = Vector<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}});

    const auto complexFloatVecPlusFloatVec = complexFloatVec + floatVec;
    ASSERT_NEAR(complexFloatVecPlusFloatVec[0].real(), 2.2f, fepsilon);   ASSERT_NEAR(complexFloatVecPlusFloatVec[0].imag(), 1.1f, fepsilon);
    ASSERT_NEAR(complexFloatVecPlusFloatVec[1].real(), 4.4f, fepsilon);   ASSERT_NEAR(complexFloatVecPlusFloatVec[1].imag(), 2.2f, fepsilon);
    ASSERT_NEAR(complexFloatVecPlusFloatVec[2].real(), 6.6f, fepsilon);   ASSERT_NEAR(complexFloatVecPlusFloatVec[2].imag(), 3.3f, fepsilon);

    const auto floatVecPlusComplexFloatVec = floatVec + complexFloatVec;
    ASSERT_NEAR(floatVecPlusComplexFloatVec[0].real(), 2.2f, fepsilon);   ASSERT_NEAR(floatVecPlusComplexFloatVec[0].imag(), 1.1f, fepsilon);
    ASSERT_NEAR(floatVecPlusComplexFloatVec[1].real(), 4.4f, fepsilon);   ASSERT_NEAR(floatVecPlusComplexFloatVec[1].imag(), 2.2f, fepsilon);
    ASSERT_NEAR(floatVecPlusComplexFloatVec[2].real(), 6.6f, fepsilon);   ASSERT_NEAR(floatVecPlusComplexFloatVec[2].imag(), 3.3f, fepsilon);
}

TEST_F(ComplexVectorTests, Addition_ComplexFloatVector_DoubleVector)
{
    const auto doubleVec = Vector<double>({1.1,2.2,3.3});
    const auto complexFloatVec = Vector<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}});

    const auto complexFloatVecPlusDoubleVec = complexFloatVec + doubleVec;
    ASSERT_NEAR(complexFloatVecPlusDoubleVec[0].real(), 2.2, fepsilon);   ASSERT_NEAR(complexFloatVecPlusDoubleVec[0].imag(), 1.1, fepsilon);
    ASSERT_NEAR(complexFloatVecPlusDoubleVec[1].real(), 4.4, fepsilon);   ASSERT_NEAR(complexFloatVecPlusDoubleVec[1].imag(), 2.2, fepsilon);
    ASSERT_NEAR(complexFloatVecPlusDoubleVec[2].real(), 6.6, fepsilon);   ASSERT_NEAR(complexFloatVecPlusDoubleVec[2].imag(), 3.3, fepsilon);

    const auto doubleVecPlusComplexFloatVec = doubleVec + complexFloatVec;
    ASSERT_NEAR(doubleVecPlusComplexFloatVec[0].real(), 2.2, fepsilon);   ASSERT_NEAR(doubleVecPlusComplexFloatVec[0].imag(), 1.1, fepsilon);
    ASSERT_NEAR(doubleVecPlusComplexFloatVec[1].real(), 4.4, fepsilon);   ASSERT_NEAR(doubleVecPlusComplexFloatVec[1].imag(), 2.2, fepsilon);
    ASSERT_NEAR(doubleVecPlusComplexFloatVec[2].real(), 6.6, fepsilon);   ASSERT_NEAR(doubleVecPlusComplexFloatVec[2].imag(), 3.3, fepsilon);
}

TEST_F(ComplexVectorTests, Addition_ComplexFloatVector_LongDoubleVector)
{
    const auto doubleVec = Vector<long double>({1.1,2.2,3.3});
    const auto complexFloatVec = Vector<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}});

    const auto complexFloatVecPlusDoubleVec = complexFloatVec + doubleVec;
    ASSERT_NEAR(complexFloatVecPlusDoubleVec[0].real(), 2.2, fepsilon);   ASSERT_NEAR(complexFloatVecPlusDoubleVec[0].imag(), 1.1, fepsilon);
    ASSERT_NEAR(complexFloatVecPlusDoubleVec[1].real(), 4.4, fepsilon);   ASSERT_NEAR(complexFloatVecPlusDoubleVec[1].imag(), 2.2, fepsilon);
    ASSERT_NEAR(complexFloatVecPlusDoubleVec[2].real(), 6.6, fepsilon);   ASSERT_NEAR(complexFloatVecPlusDoubleVec[2].imag(), 3.3, fepsilon);

    const auto doubleVecPlusComplexFloatVec = doubleVec + complexFloatVec;
    ASSERT_NEAR(doubleVecPlusComplexFloatVec[0].real(), 2.2, fepsilon);   ASSERT_NEAR(doubleVecPlusComplexFloatVec[0].imag(), 1.1, fepsilon);
    ASSERT_NEAR(doubleVecPlusComplexFloatVec[1].real(), 4.4, fepsilon);   ASSERT_NEAR(doubleVecPlusComplexFloatVec[1].imag(), 2.2, fepsilon);
    ASSERT_NEAR(doubleVecPlusComplexFloatVec[2].real(), 6.6, fepsilon);   ASSERT_NEAR(doubleVecPlusComplexFloatVec[2].imag(), 3.3, fepsilon);
}

TEST_F(ComplexVectorTests, Addition_ComplexFloatVector_ComplexFloatVector)
{
    const auto complexFloatVec = Vector<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}});

    const auto res = complexFloatVec + complexFloatVec;
    ASSERT_NEAR(res[0].real(), 2.2f, fepsilon);   ASSERT_NEAR(res[0].imag(), 2.2f, fepsilon);
    ASSERT_NEAR(res[1].real(), 4.4f, fepsilon);   ASSERT_NEAR(res[1].imag(), 4.4f, fepsilon);
    ASSERT_NEAR(res[2].real(), 6.6f, fepsilon);   ASSERT_NEAR(res[2].imag(), 6.6f, fepsilon);
}

TEST_F(ComplexVectorTests, Addition_ComplexFloatVector_ComplexDoubleVector)
{
    const auto complexFloatVec = Vector<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}});
    const auto complexDoubleVec = Vector<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.4}});

    const auto res = complexFloatVec + complexDoubleVec;
    ASSERT_NEAR(res[0].real(), 2.2, fepsilon);   ASSERT_NEAR(res[0].imag(), 2.2, fepsilon);
    ASSERT_NEAR(res[1].real(), 4.4, fepsilon);   ASSERT_NEAR(res[1].imag(), 4.4, fepsilon);
    ASSERT_NEAR(res[2].real(), 6.6, fepsilon);   ASSERT_NEAR(res[2].imag(), 6.7, fepsilon);

    const auto res2 = complexDoubleVec + complexFloatVec;
    ASSERT_NEAR(res2[0].real(), 2.2, fepsilon);   ASSERT_NEAR(res2[0].imag(), 2.2, fepsilon);
    ASSERT_NEAR(res2[1].real(), 4.4, fepsilon);   ASSERT_NEAR(res2[1].imag(), 4.4, fepsilon);
    ASSERT_NEAR(res2[2].real(), 6.6, fepsilon);   ASSERT_NEAR(res2[2].imag(), 6.7, fepsilon);
}

TEST_F(ComplexVectorTests, Addition_ComplexFloatVector_ComplexLongDoubleVector)
{
    const auto complexFloatVec = Vector<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}});
    const auto complexDoubleVec = Vector<std::complex<long double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.4}});

    const auto res = complexFloatVec + complexDoubleVec;
    ASSERT_NEAR(res[0].real(), 2.2, fepsilon);   ASSERT_NEAR(res[0].imag(), 2.2, fepsilon);
    ASSERT_NEAR(res[1].real(), 4.4, fepsilon);   ASSERT_NEAR(res[1].imag(), 4.4, fepsilon);
    ASSERT_NEAR(res[2].real(), 6.6, fepsilon);   ASSERT_NEAR(res[2].imag(), 6.7, fepsilon);

    const auto res2 = complexDoubleVec + complexFloatVec;
    ASSERT_NEAR(res2[0].real(), 2.2, fepsilon);   ASSERT_NEAR(res2[0].imag(), 2.2, fepsilon);
    ASSERT_NEAR(res2[1].real(), 4.4, fepsilon);   ASSERT_NEAR(res2[1].imag(), 4.4, fepsilon);
    ASSERT_NEAR(res2[2].real(), 6.6, fepsilon);   ASSERT_NEAR(res2[2].imag(), 6.7, fepsilon);
}

TEST_F(ComplexVectorTests, Addition_ComplexDoubleVector_IntVector)
{
    const auto intVec = Vector<int>({1,2,3});
    const auto complexDoubleVec = Vector<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.3}});

    const auto complexDoubleVecPlusIntVec = complexDoubleVec + intVec;
    ASSERT_NEAR(complexDoubleVecPlusIntVec[0].real(), 2.1, epsilon);   ASSERT_NEAR(complexDoubleVecPlusIntVec[0].imag(), 1.1, epsilon);
    ASSERT_NEAR(complexDoubleVecPlusIntVec[1].real(), 4.2, epsilon);   ASSERT_NEAR(complexDoubleVecPlusIntVec[1].imag(), 2.2, epsilon);
    ASSERT_NEAR(complexDoubleVecPlusIntVec[2].real(), 6.3, epsilon);   ASSERT_NEAR(complexDoubleVecPlusIntVec[2].imag(), 3.3, epsilon);

    const auto intVecPlusComplexDoubleVec = intVec + complexDoubleVec;
    ASSERT_NEAR(intVecPlusComplexDoubleVec[0].real(), 2.1, epsilon);   ASSERT_NEAR(intVecPlusComplexDoubleVec[0].imag(), 1.1, epsilon);
    ASSERT_NEAR(intVecPlusComplexDoubleVec[1].real(), 4.2, epsilon);   ASSERT_NEAR(intVecPlusComplexDoubleVec[1].imag(), 2.2, epsilon);
    ASSERT_NEAR(intVecPlusComplexDoubleVec[2].real(), 6.3, epsilon);   ASSERT_NEAR(intVecPlusComplexDoubleVec[2].imag(), 3.3, epsilon);
}

TEST_F(ComplexVectorTests, Addition_ComplexDoubleVector_FloatVector)
{
    const auto floatVec = Vector<float>({1.1f,2.2f,3.3f});
    const auto complexDoubleVec = Vector<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.3}});

    const auto complexDoubleVecPlusFloatVec = complexDoubleVec + floatVec;
    ASSERT_NEAR(complexDoubleVecPlusFloatVec[0].real(), 2.2, fepsilon);   ASSERT_NEAR(complexDoubleVecPlusFloatVec[0].imag(), 1.1, fepsilon);
    ASSERT_NEAR(complexDoubleVecPlusFloatVec[1].real(), 4.4, fepsilon);   ASSERT_NEAR(complexDoubleVecPlusFloatVec[1].imag(), 2.2, fepsilon);
    ASSERT_NEAR(complexDoubleVecPlusFloatVec[2].real(), 6.6, fepsilon);   ASSERT_NEAR(complexDoubleVecPlusFloatVec[2].imag(), 3.3, fepsilon);

    const auto floatVecPlusComplexDoubleVec = floatVec + complexDoubleVec;
    ASSERT_NEAR(floatVecPlusComplexDoubleVec[0].real(), 2.2, fepsilon);   ASSERT_NEAR(floatVecPlusComplexDoubleVec[0].imag(), 1.1, fepsilon);
    ASSERT_NEAR(floatVecPlusComplexDoubleVec[1].real(), 4.4, fepsilon);   ASSERT_NEAR(floatVecPlusComplexDoubleVec[1].imag(), 2.2, fepsilon);
    ASSERT_NEAR(floatVecPlusComplexDoubleVec[2].real(), 6.6, fepsilon);   ASSERT_NEAR(floatVecPlusComplexDoubleVec[2].imag(), 3.3, fepsilon);
}

TEST_F(ComplexVectorTests, Addition_ComplexDoubleVector_DoubleVector)
{
    const auto doubleVec = Vector<double>({1.1,2.2,3.3});
    const auto complexDoubleVec = Vector<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.3}});

    const auto complexDoubleVecPlusDoubleVec = complexDoubleVec + doubleVec;
    ASSERT_NEAR(complexDoubleVecPlusDoubleVec[0].real(), 2.2, epsilon);   ASSERT_NEAR(complexDoubleVecPlusDoubleVec[0].imag(), 1.1, epsilon);
    ASSERT_NEAR(complexDoubleVecPlusDoubleVec[1].real(), 4.4, epsilon);   ASSERT_NEAR(complexDoubleVecPlusDoubleVec[1].imag(), 2.2, epsilon);
    ASSERT_NEAR(complexDoubleVecPlusDoubleVec[2].real(), 6.6, epsilon);   ASSERT_NEAR(complexDoubleVecPlusDoubleVec[2].imag(), 3.3, epsilon);

    const auto doubleVecPlusComplexDoubleVec = doubleVec + complexDoubleVec;
    ASSERT_NEAR(doubleVecPlusComplexDoubleVec[0].real(), 2.2, epsilon);   ASSERT_NEAR(doubleVecPlusComplexDoubleVec[0].imag(), 1.1, epsilon);
    ASSERT_NEAR(doubleVecPlusComplexDoubleVec[1].real(), 4.4, epsilon);   ASSERT_NEAR(doubleVecPlusComplexDoubleVec[1].imag(), 2.2, epsilon);
    ASSERT_NEAR(doubleVecPlusComplexDoubleVec[2].real(), 6.6, epsilon);   ASSERT_NEAR(doubleVecPlusComplexDoubleVec[2].imag(), 3.3, epsilon);
}

TEST_F(ComplexVectorTests, Addition_ComplexDoubleVector_LongDoubleVector)
{
    const auto doubleVec = Vector<long double>({1.1,2.2,3.3});
    const auto complexDoubleVec = Vector<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.3}});

    const auto complexDoubleVecPlusDoubleVec = complexDoubleVec + doubleVec;
    ASSERT_NEAR(complexDoubleVecPlusDoubleVec[0].real(), 2.2, epsilon);   ASSERT_NEAR(complexDoubleVecPlusDoubleVec[0].imag(), 1.1, epsilon);
    ASSERT_NEAR(complexDoubleVecPlusDoubleVec[1].real(), 4.4, epsilon);   ASSERT_NEAR(complexDoubleVecPlusDoubleVec[1].imag(), 2.2, epsilon);
    ASSERT_NEAR(complexDoubleVecPlusDoubleVec[2].real(), 6.6, epsilon);   ASSERT_NEAR(complexDoubleVecPlusDoubleVec[2].imag(), 3.3, epsilon);

    const auto doubleVecPlusComplexDoubleVec = doubleVec + complexDoubleVec;
    ASSERT_NEAR(doubleVecPlusComplexDoubleVec[0].real(), 2.2, epsilon);   ASSERT_NEAR(doubleVecPlusComplexDoubleVec[0].imag(), 1.1, epsilon);
    ASSERT_NEAR(doubleVecPlusComplexDoubleVec[1].real(), 4.4, epsilon);   ASSERT_NEAR(doubleVecPlusComplexDoubleVec[1].imag(), 2.2, epsilon);
    ASSERT_NEAR(doubleVecPlusComplexDoubleVec[2].real(), 6.6, epsilon);   ASSERT_NEAR(doubleVecPlusComplexDoubleVec[2].imag(), 3.3, epsilon);
}

TEST_F(ComplexVectorTests, Addition_ComplexDoubleVector_ComplexDoubleVector)
{
    const auto complexDoubleVec = Vector<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.3}});

    const auto res = complexDoubleVec + complexDoubleVec;
    ASSERT_NEAR(res[0].real(), 2.2, epsilon);   ASSERT_NEAR(res[0].imag(), 2.2, epsilon);
    ASSERT_NEAR(res[1].real(), 4.4, epsilon);   ASSERT_NEAR(res[1].imag(), 4.4, epsilon);
    ASSERT_NEAR(res[2].real(), 6.6, epsilon);   ASSERT_NEAR(res[2].imag(), 6.6, epsilon);
}

TEST_F(ComplexVectorTests, Addition_ComplexDoubleVector_ComplexLongDoubleVector)
{
    const auto complexDoubleVec = Vector<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.3}});
    const auto complexLongDoubleVec = Vector<std::complex<long double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.4}});

    const auto res = complexDoubleVec + complexLongDoubleVec;
    ASSERT_NEAR(res[0].real(), 2.2, epsilon);   ASSERT_NEAR(res[0].imag(), 2.2, epsilon);
    ASSERT_NEAR(res[1].real(), 4.4, epsilon);   ASSERT_NEAR(res[1].imag(), 4.4, epsilon);
    ASSERT_NEAR(res[2].real(), 6.6, epsilon);   ASSERT_NEAR(res[2].imag(), 6.7, epsilon);

    const auto res2 = complexLongDoubleVec + complexDoubleVec;
    ASSERT_NEAR(res2[0].real(), 2.2, epsilon);   ASSERT_NEAR(res2[0].imag(), 2.2, epsilon);
    ASSERT_NEAR(res2[1].real(), 4.4, epsilon);   ASSERT_NEAR(res2[1].imag(), 4.4, epsilon);
    ASSERT_NEAR(res2[2].real(), 6.6, epsilon);   ASSERT_NEAR(res2[2].imag(), 6.7, epsilon);
}


///////////////////////////////////////////


TEST_F(ComplexVectorTests, Subtraction_ComplexIntVector_IntVector)
{
    const auto intVec = Vector<int>({1,2,3});
    const auto complexIntVec = Vector<std::complex<int>>({{1,1}, {2,2}, {3,3}});

    const auto intVecMinusComplexIntVec = intVec - complexIntVec;
    ASSERT_EQ(intVecMinusComplexIntVec[0], std::complex<int>(0,-1));
    ASSERT_EQ(intVecMinusComplexIntVec[1], std::complex<int>(0,-2));
    ASSERT_EQ(intVecMinusComplexIntVec[2], std::complex<int>(0,-3));

    const auto complexIntVecMinusIntVec = complexIntVec - intVec;
    ASSERT_EQ(complexIntVecMinusIntVec[0], std::complex<int>(0,1));
    ASSERT_EQ(complexIntVecMinusIntVec[1], std::complex<int>(0,2));
    ASSERT_EQ(complexIntVecMinusIntVec[2], std::complex<int>(0,3));
}

TEST_F(ComplexVectorTests, Subtraction_ComplexIntVector_FloatVector)
{
    const auto floatVec = Vector<float>({1.1f,2.2f,3.3f});
    const auto complexIntVec = Vector<std::complex<int>>({{1,1}, {2,2}, {3,3}});

    const auto floatVecMinusComplexIntVec = floatVec - complexIntVec;
    ASSERT_NEAR(floatVecMinusComplexIntVec[0].real(), 0.1f, fepsilon);   ASSERT_NEAR(floatVecMinusComplexIntVec[0].imag(), -1.0f, fepsilon);
    ASSERT_NEAR(floatVecMinusComplexIntVec[1].real(), 0.2f, fepsilon);   ASSERT_NEAR(floatVecMinusComplexIntVec[1].imag(), -2.0f, fepsilon);
    ASSERT_NEAR(floatVecMinusComplexIntVec[2].real(), 0.3f, fepsilon);   ASSERT_NEAR(floatVecMinusComplexIntVec[2].imag(), -3.0f, fepsilon);

    const auto complexIntVecMinusFloatVec = complexIntVec - floatVec;
    ASSERT_NEAR(complexIntVecMinusFloatVec[0].real(), -0.1f, fepsilon);   ASSERT_NEAR(complexIntVecMinusFloatVec[0].imag(), 1.0f, fepsilon);
    ASSERT_NEAR(complexIntVecMinusFloatVec[1].real(), -0.2f, fepsilon);   ASSERT_NEAR(complexIntVecMinusFloatVec[1].imag(), 2.0f, fepsilon);
    ASSERT_NEAR(complexIntVecMinusFloatVec[2].real(), -0.3f, fepsilon);   ASSERT_NEAR(complexIntVecMinusFloatVec[2].imag(), 3.0f, fepsilon);
}

TEST_F(ComplexVectorTests, Subtraction_ComplexIntVector_DoubleVector)
{
    const auto doubleVec = Vector<double>({1.1,2.2,3.3});
    const auto complexIntVec = Vector<std::complex<int>>({{1,1}, {2,2}, {3,3}});

    const auto doubleVecMinusComplexIntVec = doubleVec - complexIntVec;
    ASSERT_NEAR(doubleVecMinusComplexIntVec[0].real(), 0.1, epsilon);   ASSERT_NEAR(doubleVecMinusComplexIntVec[0].imag(), -1.0, epsilon);
    ASSERT_NEAR(doubleVecMinusComplexIntVec[1].real(), 0.2, epsilon);   ASSERT_NEAR(doubleVecMinusComplexIntVec[1].imag(), -2.0, epsilon);
    ASSERT_NEAR(doubleVecMinusComplexIntVec[2].real(), 0.3, epsilon);   ASSERT_NEAR(doubleVecMinusComplexIntVec[2].imag(), -3.0, epsilon);

    const auto complexIntVecMinusDoubleVec = complexIntVec - doubleVec;
    ASSERT_NEAR(complexIntVecMinusDoubleVec[0].real(), -0.1, epsilon);   ASSERT_NEAR(complexIntVecMinusDoubleVec[0].imag(), 1.0, epsilon);
    ASSERT_NEAR(complexIntVecMinusDoubleVec[1].real(), -0.2, epsilon);   ASSERT_NEAR(complexIntVecMinusDoubleVec[1].imag(), 2.0, epsilon);
    ASSERT_NEAR(complexIntVecMinusDoubleVec[2].real(), -0.3, epsilon);   ASSERT_NEAR(complexIntVecMinusDoubleVec[2].imag(), 3.0, epsilon);
}

TEST_F(ComplexVectorTests, Subtraction_ComplexIntVector_LongDoubleVector)
{
    const auto doubleVec = Vector<long double>({1.1,2.2,3.3});
    const auto complexIntVec = Vector<std::complex<int>>({{1,1}, {2,2}, {3,3}});

    const auto doubleVecMinusComplexIntVec = doubleVec - complexIntVec;
    ASSERT_NEAR(doubleVecMinusComplexIntVec[0].real(), 0.1, epsilon);   ASSERT_NEAR(doubleVecMinusComplexIntVec[0].imag(), -1.0, epsilon);
    ASSERT_NEAR(doubleVecMinusComplexIntVec[1].real(), 0.2, epsilon);   ASSERT_NEAR(doubleVecMinusComplexIntVec[1].imag(), -2.0, epsilon);
    ASSERT_NEAR(doubleVecMinusComplexIntVec[2].real(), 0.3, epsilon);   ASSERT_NEAR(doubleVecMinusComplexIntVec[2].imag(), -3.0, epsilon);

    const auto complexIntVecMinusDoubleVec = complexIntVec - doubleVec;
    ASSERT_NEAR(complexIntVecMinusDoubleVec[0].real(), -0.1, epsilon);   ASSERT_NEAR(complexIntVecMinusDoubleVec[0].imag(), 1.0, epsilon);
    ASSERT_NEAR(complexIntVecMinusDoubleVec[1].real(), -0.2, epsilon);   ASSERT_NEAR(complexIntVecMinusDoubleVec[1].imag(), 2.0, epsilon);
    ASSERT_NEAR(complexIntVecMinusDoubleVec[2].real(), -0.3, epsilon);   ASSERT_NEAR(complexIntVecMinusDoubleVec[2].imag(), 3.0, epsilon);
}

TEST_F(ComplexVectorTests, Subtraction_ComplexIntVector_ComplexIntVector)
{
    const auto complexIntVec = Vector<std::complex<int>>({{1,1}, {2,2}, {3,3}});

    const auto res = complexIntVec - complexIntVec;
    ASSERT_EQ(res[0], std::complex<int>(0,0));
    ASSERT_EQ(res[1], std::complex<int>(0,0));
    ASSERT_EQ(res[2], std::complex<int>(0,0));
}

TEST_F(ComplexVectorTests, Subtraction_ComplexIntVector_ComplexFloatVector)
{
    const auto complexIntVec = Vector<std::complex<int>>({{1,1}, {2,2}, {3,3}});
    const auto complexFloatVec = Vector<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.4f}});

    const auto res = complexIntVec - complexFloatVec;
    ASSERT_NEAR(res[0].real(), -0.1f, fepsilon);   ASSERT_NEAR(res[0].imag(), -0.1f, fepsilon);
    ASSERT_NEAR(res[1].real(), -0.2f, fepsilon);   ASSERT_NEAR(res[1].imag(), -0.2f, fepsilon);
    ASSERT_NEAR(res[2].real(), -0.3f, fepsilon);   ASSERT_NEAR(res[2].imag(), -0.4f, fepsilon);

    const auto res2 = complexFloatVec - complexIntVec;
    ASSERT_NEAR(res2[0].real(), 0.1f, fepsilon);   ASSERT_NEAR(res2[0].imag(), 0.1f, fepsilon);
    ASSERT_NEAR(res2[1].real(), 0.2f, fepsilon);   ASSERT_NEAR(res2[1].imag(), 0.2f, fepsilon);
    ASSERT_NEAR(res2[2].real(), 0.3f, fepsilon);   ASSERT_NEAR(res2[2].imag(), 0.4f, fepsilon);
}

TEST_F(ComplexVectorTests, Subtraction_ComplexIntVector_ComplexDoubleVector)
{
    const auto complexIntVec = Vector<std::complex<int>>({{1,1}, {2,2}, {3,3}});
    const auto complexDoubleVec = Vector<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.4}});

    const auto res = complexIntVec - complexDoubleVec;
    ASSERT_NEAR(res[0].real(), -0.1, epsilon);   ASSERT_NEAR(res[0].imag(), -0.1, epsilon);
    ASSERT_NEAR(res[1].real(), -0.2, epsilon);   ASSERT_NEAR(res[1].imag(), -0.2, epsilon);
    ASSERT_NEAR(res[2].real(), -0.3, epsilon);   ASSERT_NEAR(res[2].imag(), -0.4, epsilon);

    const auto res2 = complexDoubleVec - complexIntVec;
    ASSERT_NEAR(res2[0].real(), 0.1, epsilon);   ASSERT_NEAR(res2[0].imag(), 0.1, epsilon);
    ASSERT_NEAR(res2[1].real(), 0.2, epsilon);   ASSERT_NEAR(res2[1].imag(), 0.2, epsilon);
    ASSERT_NEAR(res2[2].real(), 0.3, epsilon);   ASSERT_NEAR(res2[2].imag(), 0.4, epsilon);
}

TEST_F(ComplexVectorTests, Subtraction_ComplexIntVector_ComplexLongDoubleVector)
{
    const auto complexIntVec = Vector<std::complex<int>>({{1,1}, {2,2}, {3,3}});
    const auto complexDoubleVec = Vector<std::complex<long double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.4}});

    const auto res = complexIntVec - complexDoubleVec;
    ASSERT_NEAR(res[0].real(), -0.1, epsilon);   ASSERT_NEAR(res[0].imag(), -0.1, epsilon);
    ASSERT_NEAR(res[1].real(), -0.2, epsilon);   ASSERT_NEAR(res[1].imag(), -0.2, epsilon);
    ASSERT_NEAR(res[2].real(), -0.3, epsilon);   ASSERT_NEAR(res[2].imag(), -0.4, epsilon);

    const auto res2 = complexDoubleVec - complexIntVec;
    ASSERT_NEAR(res2[0].real(), 0.1, epsilon);   ASSERT_NEAR(res2[0].imag(), 0.1, epsilon);
    ASSERT_NEAR(res2[1].real(), 0.2, epsilon);   ASSERT_NEAR(res2[1].imag(), 0.2, epsilon);
    ASSERT_NEAR(res2[2].real(), 0.3, epsilon);   ASSERT_NEAR(res2[2].imag(), 0.4, epsilon);
}

TEST_F(ComplexVectorTests, Subtraction_ComplexFloatVector_IntVector)
{
    const auto intVec = Vector<int>({1,2,3});
    const auto complexFloatVec = Vector<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}});

    const auto complexFloatVecMinusIntVec = complexFloatVec - intVec;
    ASSERT_NEAR(complexFloatVecMinusIntVec[0].real(), 0.1f, fepsilon);   ASSERT_NEAR(complexFloatVecMinusIntVec[0].imag(), 1.1f, fepsilon);
    ASSERT_NEAR(complexFloatVecMinusIntVec[1].real(), 0.2f, fepsilon);   ASSERT_NEAR(complexFloatVecMinusIntVec[1].imag(), 2.2f, fepsilon);
    ASSERT_NEAR(complexFloatVecMinusIntVec[2].real(), 0.3f, fepsilon);   ASSERT_NEAR(complexFloatVecMinusIntVec[2].imag(), 3.3f, fepsilon);

    const auto intVecMinusComplexFloatVec = intVec - complexFloatVec;
    ASSERT_NEAR(intVecMinusComplexFloatVec[0].real(), -0.1f, fepsilon);   ASSERT_NEAR(intVecMinusComplexFloatVec[0].imag(), -1.1f, fepsilon);
    ASSERT_NEAR(intVecMinusComplexFloatVec[1].real(), -0.2f, fepsilon);   ASSERT_NEAR(intVecMinusComplexFloatVec[1].imag(), -2.2f, fepsilon);
    ASSERT_NEAR(intVecMinusComplexFloatVec[2].real(), -0.3f, fepsilon);   ASSERT_NEAR(intVecMinusComplexFloatVec[2].imag(), -3.3f, fepsilon);
}

TEST_F(ComplexVectorTests, Subtraction_ComplexFloatVector_FloatVector)
{
    const auto floatVec = Vector<float>({1.1f,2.2f,3.3f});
    const auto complexFloatVec = Vector<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}});

    const auto complexFloatVecMinusFloatVec = complexFloatVec - floatVec;
    ASSERT_NEAR(complexFloatVecMinusFloatVec[0].real(), 0.0f, fepsilon);   ASSERT_NEAR(complexFloatVecMinusFloatVec[0].imag(), 1.1f, fepsilon);
    ASSERT_NEAR(complexFloatVecMinusFloatVec[1].real(), 0.0f, fepsilon);   ASSERT_NEAR(complexFloatVecMinusFloatVec[1].imag(), 2.2f, fepsilon);
    ASSERT_NEAR(complexFloatVecMinusFloatVec[2].real(), 0.0f, fepsilon);   ASSERT_NEAR(complexFloatVecMinusFloatVec[2].imag(), 3.3f, fepsilon);

    const auto floatVecMinusComplexFloatVec = floatVec - complexFloatVec;
    ASSERT_NEAR(floatVecMinusComplexFloatVec[0].real(), 0.0f, fepsilon);   ASSERT_NEAR(floatVecMinusComplexFloatVec[0].imag(), -1.1f, fepsilon);
    ASSERT_NEAR(floatVecMinusComplexFloatVec[1].real(), 0.0f, fepsilon);   ASSERT_NEAR(floatVecMinusComplexFloatVec[1].imag(), -2.2f, fepsilon);
    ASSERT_NEAR(floatVecMinusComplexFloatVec[2].real(), 0.0f, fepsilon);   ASSERT_NEAR(floatVecMinusComplexFloatVec[2].imag(), -3.3f, fepsilon);
}

TEST_F(ComplexVectorTests, Subtraction_ComplexFloatVector_DoubleVector)
{
    const auto doubleVec = Vector<double>({1.1,2.2,3.3});
    const auto complexFloatVec = Vector<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}});

    const auto complexFloatVecMinusDoubleVec = complexFloatVec - doubleVec;
    ASSERT_NEAR(complexFloatVecMinusDoubleVec[0].real(), 0.0, fepsilon);   ASSERT_NEAR(complexFloatVecMinusDoubleVec[0].imag(), 1.1, fepsilon);
    ASSERT_NEAR(complexFloatVecMinusDoubleVec[1].real(), 0.0, fepsilon);   ASSERT_NEAR(complexFloatVecMinusDoubleVec[1].imag(), 2.2, fepsilon);
    ASSERT_NEAR(complexFloatVecMinusDoubleVec[2].real(), 0.0, fepsilon);   ASSERT_NEAR(complexFloatVecMinusDoubleVec[2].imag(), 3.3, fepsilon);

    const auto doubleVecMinusComplexFloatVec = doubleVec - complexFloatVec;
    ASSERT_NEAR(doubleVecMinusComplexFloatVec[0].real(), 0.0, fepsilon);   ASSERT_NEAR(doubleVecMinusComplexFloatVec[0].imag(), -1.1, fepsilon);
    ASSERT_NEAR(doubleVecMinusComplexFloatVec[1].real(), 0.0, fepsilon);   ASSERT_NEAR(doubleVecMinusComplexFloatVec[1].imag(), -2.2, fepsilon);
    ASSERT_NEAR(doubleVecMinusComplexFloatVec[2].real(), 0.0, fepsilon);   ASSERT_NEAR(doubleVecMinusComplexFloatVec[2].imag(), -3.3, fepsilon);
}

TEST_F(ComplexVectorTests, Subtraction_ComplexFloatVector_LongDoubleVector)
{
    const auto doubleVec = Vector<long double>({1.1,2.2,3.3});
    const auto complexFloatVec = Vector<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}});

    const auto complexFloatVecMinusDoubleVec = complexFloatVec - doubleVec;
    ASSERT_NEAR(complexFloatVecMinusDoubleVec[0].real(), 0.0, fepsilon);   ASSERT_NEAR(complexFloatVecMinusDoubleVec[0].imag(), 1.1, fepsilon);
    ASSERT_NEAR(complexFloatVecMinusDoubleVec[1].real(), 0.0, fepsilon);   ASSERT_NEAR(complexFloatVecMinusDoubleVec[1].imag(), 2.2, fepsilon);
    ASSERT_NEAR(complexFloatVecMinusDoubleVec[2].real(), 0.0, fepsilon);   ASSERT_NEAR(complexFloatVecMinusDoubleVec[2].imag(), 3.3, fepsilon);

    const auto doubleVecMinusComplexFloatVec = doubleVec - complexFloatVec;
    ASSERT_NEAR(doubleVecMinusComplexFloatVec[0].real(), 0.0, fepsilon);   ASSERT_NEAR(doubleVecMinusComplexFloatVec[0].imag(), -1.1, fepsilon);
    ASSERT_NEAR(doubleVecMinusComplexFloatVec[1].real(), 0.0, fepsilon);   ASSERT_NEAR(doubleVecMinusComplexFloatVec[1].imag(), -2.2, fepsilon);
    ASSERT_NEAR(doubleVecMinusComplexFloatVec[2].real(), 0.0, fepsilon);   ASSERT_NEAR(doubleVecMinusComplexFloatVec[2].imag(), -3.3, fepsilon);
}

TEST_F(ComplexVectorTests, Subtraction_ComplexFloatVector_ComplexFloatVector)
{
    const auto complexFloatVec = Vector<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}});

    const auto res = complexFloatVec - complexFloatVec;
    ASSERT_NEAR(res[0].real(), 0.0f, fepsilon);   ASSERT_NEAR(res[0].imag(), 0.0f, fepsilon);
    ASSERT_NEAR(res[1].real(), 0.0f, fepsilon);   ASSERT_NEAR(res[1].imag(), 0.0f, fepsilon);
    ASSERT_NEAR(res[2].real(), 0.0f, fepsilon);   ASSERT_NEAR(res[2].imag(), 0.0f, fepsilon);
}

TEST_F(ComplexVectorTests, Subtraction_ComplexFloatVector_ComplexDoubleVector)
{
    const auto complexFloatVec = Vector<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}});
    const auto complexDoubleVec = Vector<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.4}});

    const auto res = complexFloatVec - complexDoubleVec;
    ASSERT_NEAR(res[0].real(), 0.0, fepsilon);   ASSERT_NEAR(res[0].imag(), 0.0, fepsilon);
    ASSERT_NEAR(res[1].real(), 0.0, fepsilon);   ASSERT_NEAR(res[1].imag(), 0.0, fepsilon);
    ASSERT_NEAR(res[2].real(), 0.0, fepsilon);   ASSERT_NEAR(res[2].imag(), -0.1, fepsilon);

    const auto res2 = complexDoubleVec - complexFloatVec;
    ASSERT_NEAR(res2[0].real(), 0.0, fepsilon);   ASSERT_NEAR(res2[0].imag(), 0.0, fepsilon);
    ASSERT_NEAR(res2[1].real(), 0.0, fepsilon);   ASSERT_NEAR(res2[1].imag(), 0.0, fepsilon);
    ASSERT_NEAR(res2[2].real(), 0.0, fepsilon);   ASSERT_NEAR(res2[2].imag(), 0.1, fepsilon);
}

TEST_F(ComplexVectorTests, Subtraction_ComplexFloatVector_ComplexLongDoubleVector)
{
    const auto complexFloatVec = Vector<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}});
    const auto complexDoubleVec = Vector<std::complex<long double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.4}});

    const auto res = complexFloatVec - complexDoubleVec;
    ASSERT_NEAR(res[0].real(), 0.0, fepsilon);   ASSERT_NEAR(res[0].imag(), 0.0, fepsilon);
    ASSERT_NEAR(res[1].real(), 0.0, fepsilon);   ASSERT_NEAR(res[1].imag(), 0.0, fepsilon);
    ASSERT_NEAR(res[2].real(), 0.0, fepsilon);   ASSERT_NEAR(res[2].imag(), -0.1, fepsilon);

    const auto res2 = complexDoubleVec - complexFloatVec;
    ASSERT_NEAR(res2[0].real(), 0.0, fepsilon);   ASSERT_NEAR(res2[0].imag(), 0.0, fepsilon);
    ASSERT_NEAR(res2[1].real(), 0.0, fepsilon);   ASSERT_NEAR(res2[1].imag(), 0.0, fepsilon);
    ASSERT_NEAR(res2[2].real(), 0.0, fepsilon);   ASSERT_NEAR(res2[2].imag(), 0.1, fepsilon);
}

TEST_F(ComplexVectorTests, Subtraction_ComplexDoubleVector_IntVector)
{
    const auto intVec = Vector<int>({1,2,3});
    const auto complexDoubleVec = Vector<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.3}});

    const auto complexDoubleVecMinusIntVec = complexDoubleVec - intVec;
    ASSERT_NEAR(complexDoubleVecMinusIntVec[0].real(), 0.1, epsilon);   ASSERT_NEAR(complexDoubleVecMinusIntVec[0].imag(), 1.1, epsilon);
    ASSERT_NEAR(complexDoubleVecMinusIntVec[1].real(), 0.2, epsilon);   ASSERT_NEAR(complexDoubleVecMinusIntVec[1].imag(), 2.2, epsilon);
    ASSERT_NEAR(complexDoubleVecMinusIntVec[2].real(), 0.3, epsilon);   ASSERT_NEAR(complexDoubleVecMinusIntVec[2].imag(), 3.3, epsilon);

    const auto intVecMinusComplexDoubleVec = intVec - complexDoubleVec;
    ASSERT_NEAR(intVecMinusComplexDoubleVec[0].real(), -0.1, epsilon);   ASSERT_NEAR(intVecMinusComplexDoubleVec[0].imag(), -1.1, epsilon);
    ASSERT_NEAR(intVecMinusComplexDoubleVec[1].real(), -0.2, epsilon);   ASSERT_NEAR(intVecMinusComplexDoubleVec[1].imag(), -2.2, epsilon);
    ASSERT_NEAR(intVecMinusComplexDoubleVec[2].real(), -0.3, epsilon);   ASSERT_NEAR(intVecMinusComplexDoubleVec[2].imag(), -3.3, epsilon);
}

TEST_F(ComplexVectorTests, Subtraction_ComplexDoubleVector_FloatVector)
{
    const auto floatVec = Vector<float>({1.1f,2.2f,3.3f});
    const auto complexDoubleVec = Vector<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.3}});

    const auto complexDoubleVecMinusFloatVec = complexDoubleVec - floatVec;
    ASSERT_NEAR(complexDoubleVecMinusFloatVec[0].real(), 0.0, fepsilon);   ASSERT_NEAR(complexDoubleVecMinusFloatVec[0].imag(), 1.1, fepsilon);
    ASSERT_NEAR(complexDoubleVecMinusFloatVec[1].real(), 0.0, fepsilon);   ASSERT_NEAR(complexDoubleVecMinusFloatVec[1].imag(), 2.2, fepsilon);
    ASSERT_NEAR(complexDoubleVecMinusFloatVec[2].real(), 0.0, fepsilon);   ASSERT_NEAR(complexDoubleVecMinusFloatVec[2].imag(), 3.3, fepsilon);

    const auto floatVecMinusComplexDoubleVec = floatVec - complexDoubleVec;
    ASSERT_NEAR(floatVecMinusComplexDoubleVec[0].real(), 0.0, fepsilon);   ASSERT_NEAR(floatVecMinusComplexDoubleVec[0].imag(), -1.1, fepsilon);
    ASSERT_NEAR(floatVecMinusComplexDoubleVec[1].real(), 0.0, fepsilon);   ASSERT_NEAR(floatVecMinusComplexDoubleVec[1].imag(), -2.2, fepsilon);
    ASSERT_NEAR(floatVecMinusComplexDoubleVec[2].real(), 0.0, fepsilon);   ASSERT_NEAR(floatVecMinusComplexDoubleVec[2].imag(), -3.3, fepsilon);
}

TEST_F(ComplexVectorTests, Subtraction_ComplexDoubleVector_DoubleVector)
{
    const auto doubleVec = Vector<double>({1.1,2.2,3.3});
    const auto complexDoubleVec = Vector<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.3}});

    const auto complexDoubleVecMinusDoubleVec = complexDoubleVec - doubleVec;
    ASSERT_NEAR(complexDoubleVecMinusDoubleVec[0].real(), 0.0, epsilon);   ASSERT_NEAR(complexDoubleVecMinusDoubleVec[0].imag(), 1.1, epsilon);
    ASSERT_NEAR(complexDoubleVecMinusDoubleVec[1].real(), 0.0, epsilon);   ASSERT_NEAR(complexDoubleVecMinusDoubleVec[1].imag(), 2.2, epsilon);
    ASSERT_NEAR(complexDoubleVecMinusDoubleVec[2].real(), 0.0, epsilon);   ASSERT_NEAR(complexDoubleVecMinusDoubleVec[2].imag(), 3.3, epsilon);

    const auto doubleVecMinusComplexDoubleVec = doubleVec - complexDoubleVec;
    ASSERT_NEAR(doubleVecMinusComplexDoubleVec[0].real(), 0.0, epsilon);   ASSERT_NEAR(doubleVecMinusComplexDoubleVec[0].imag(), -1.1, epsilon);
    ASSERT_NEAR(doubleVecMinusComplexDoubleVec[1].real(), 0.0, epsilon);   ASSERT_NEAR(doubleVecMinusComplexDoubleVec[1].imag(), -2.2, epsilon);
    ASSERT_NEAR(doubleVecMinusComplexDoubleVec[2].real(), 0.0, epsilon);   ASSERT_NEAR(doubleVecMinusComplexDoubleVec[2].imag(), -3.3, epsilon);
}

TEST_F(ComplexVectorTests, Subtraction_ComplexDoubleVector_LongDoubleVector)
{
    const auto doubleVec = Vector<long double>({1.1,2.2,3.3});
    const auto complexDoubleVec = Vector<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.3}});

    const auto complexDoubleVecMinusDoubleVec = complexDoubleVec - doubleVec;
    ASSERT_NEAR(complexDoubleVecMinusDoubleVec[0].real(), 0.0, epsilon);   ASSERT_NEAR(complexDoubleVecMinusDoubleVec[0].imag(), 1.1, epsilon);
    ASSERT_NEAR(complexDoubleVecMinusDoubleVec[1].real(), 0.0, epsilon);   ASSERT_NEAR(complexDoubleVecMinusDoubleVec[1].imag(), 2.2, epsilon);
    ASSERT_NEAR(complexDoubleVecMinusDoubleVec[2].real(), 0.0, epsilon);   ASSERT_NEAR(complexDoubleVecMinusDoubleVec[2].imag(), 3.3, epsilon);

    const auto doubleVecMinusComplexDoubleVec = doubleVec - complexDoubleVec;
    ASSERT_NEAR(doubleVecMinusComplexDoubleVec[0].real(), 0.0, epsilon);   ASSERT_NEAR(doubleVecMinusComplexDoubleVec[0].imag(), -1.1, epsilon);
    ASSERT_NEAR(doubleVecMinusComplexDoubleVec[1].real(), 0.0, epsilon);   ASSERT_NEAR(doubleVecMinusComplexDoubleVec[1].imag(), -2.2, epsilon);
    ASSERT_NEAR(doubleVecMinusComplexDoubleVec[2].real(), 0.0, epsilon);   ASSERT_NEAR(doubleVecMinusComplexDoubleVec[2].imag(), -3.3, epsilon);
}

TEST_F(ComplexVectorTests, Subtraction_ComplexDoubleVector_ComplexDoubleVector)
{
    const auto complexDoubleVec = Vector<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.3}});

    const auto res = complexDoubleVec - complexDoubleVec;
    ASSERT_NEAR(res[0].real(), 0.0, epsilon);   ASSERT_NEAR(res[0].imag(), 0.0, epsilon);
    ASSERT_NEAR(res[1].real(), 0.0, epsilon);   ASSERT_NEAR(res[1].imag(), 0.0, epsilon);
    ASSERT_NEAR(res[2].real(), 0.0, epsilon);   ASSERT_NEAR(res[2].imag(), 0.0, epsilon);
}

TEST_F(ComplexVectorTests, Subtraction_ComplexDoubleVector_ComplexLongDoubleVector)
{
    const auto complexDoubleVec = Vector<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.3}});
    const auto complexLongDoubleVec = Vector<std::complex<long double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.4}});

    const auto res = complexDoubleVec - complexLongDoubleVec;
    ASSERT_NEAR(res[0].real(), 0.0, epsilon);   ASSERT_NEAR(res[0].imag(), 0.0, epsilon);
    ASSERT_NEAR(res[1].real(), 0.0, epsilon);   ASSERT_NEAR(res[1].imag(), 0.0, epsilon);
    ASSERT_NEAR(res[2].real(), 0.0, epsilon);   ASSERT_NEAR(res[2].imag(), -0.1, epsilon);

    const auto res2 = complexLongDoubleVec - complexDoubleVec;
    ASSERT_NEAR(res2[0].real(), 0.0, epsilon);   ASSERT_NEAR(res2[0].imag(), 0.0, epsilon);
    ASSERT_NEAR(res2[1].real(), 0.0, epsilon);   ASSERT_NEAR(res2[1].imag(), 0.0, epsilon);
    ASSERT_NEAR(res2[2].real(), 0.0, epsilon);   ASSERT_NEAR(res2[2].imag(), 0.1, epsilon);
}

///// in-place ops for complex vectors
TEST_F(ComplexVectorTests, InPlace_ComplexVectorAddition)
{
    auto complexIntVec = Vector<std::complex<int>>({{1,1}, {2,2}, {3,3}});
    auto complexFloatVec = Vector<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}});
    auto complexDoubleVec = Vector<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.3}});
    auto complexLongDoubleVec = Vector<std::complex<long double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.4}});

    complexIntVec += complexIntVec;
    ASSERT_EQ(complexIntVec[0], std::complex<int>(2,2));
    ASSERT_EQ(complexIntVec[1], std::complex<int>(4,4));
    ASSERT_EQ(complexIntVec[2], std::complex<int>(6,6));

    complexFloatVec += complexFloatVec;
    ASSERT_NEAR(complexFloatVec[0].real(), 2.2f, fepsilon);   ASSERT_NEAR(complexFloatVec[0].imag(), 2.2f, fepsilon);
    ASSERT_NEAR(complexFloatVec[1].real(), 4.4f, fepsilon);   ASSERT_NEAR(complexFloatVec[1].imag(), 4.4f, fepsilon);
    ASSERT_NEAR(complexFloatVec[2].real(), 6.6f, fepsilon);   ASSERT_NEAR(complexFloatVec[2].imag(), 6.6f, fepsilon);

    complexDoubleVec += complexDoubleVec;
    ASSERT_NEAR(complexDoubleVec[0].real(), 2.2, epsilon);   ASSERT_NEAR(complexDoubleVec[0].imag(), 2.2, epsilon);
    ASSERT_NEAR(complexDoubleVec[1].real(), 4.4, epsilon);   ASSERT_NEAR(complexDoubleVec[1].imag(), 4.4, epsilon);
    ASSERT_NEAR(complexDoubleVec[2].real(), 6.6, epsilon);   ASSERT_NEAR(complexDoubleVec[2].imag(), 6.6, epsilon);

    complexLongDoubleVec += complexLongDoubleVec;
    ASSERT_NEAR(complexLongDoubleVec[0].real(), 2.2, epsilon);   ASSERT_NEAR(complexLongDoubleVec[0].imag(), 2.2, epsilon);
    ASSERT_NEAR(complexLongDoubleVec[1].real(), 4.4, epsilon);   ASSERT_NEAR(complexLongDoubleVec[1].imag(), 4.4, epsilon);
    ASSERT_NEAR(complexLongDoubleVec[2].real(), 6.6, epsilon);   ASSERT_NEAR(complexLongDoubleVec[2].imag(), 6.8, epsilon);
}

TEST_F(ComplexVectorTests, InPlace_ComplexVectorSubtraction)
{
    auto complexIntVec = Vector<std::complex<int>>({{1,1}, {2,2}, {3,3}});
    auto complexFloatVec = Vector<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}});
    auto complexDoubleVec = Vector<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.3}});
    auto complexLongDoubleVec = Vector<std::complex<long double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.4}});

    complexIntVec -= complexIntVec;
    ASSERT_EQ(complexIntVec[0], std::complex<int>(0,0));
    ASSERT_EQ(complexIntVec[1], std::complex<int>(0,0));
    ASSERT_EQ(complexIntVec[2], std::complex<int>(0,0));

    complexFloatVec -= complexFloatVec;
    ASSERT_NEAR(complexFloatVec[0].real(), 0.0f, fepsilon);   ASSERT_NEAR(complexFloatVec[0].imag(), 0.0f, fepsilon);
    ASSERT_NEAR(complexFloatVec[1].real(), 0.0f, fepsilon);   ASSERT_NEAR(complexFloatVec[1].imag(), 0.0f, fepsilon);
    ASSERT_NEAR(complexFloatVec[2].real(), 0.0f, fepsilon);   ASSERT_NEAR(complexFloatVec[2].imag(), 0.0f, fepsilon);

    complexDoubleVec -= complexDoubleVec;
    ASSERT_NEAR(complexDoubleVec[0].real(), 0.0, epsilon);   ASSERT_NEAR(complexDoubleVec[0].imag(), 0.0, epsilon);
    ASSERT_NEAR(complexDoubleVec[1].real(), 0.0, epsilon);   ASSERT_NEAR(complexDoubleVec[1].imag(), 0.0, epsilon);
    ASSERT_NEAR(complexDoubleVec[2].real(), 0.0, epsilon);   ASSERT_NEAR(complexDoubleVec[2].imag(), 0.0, epsilon);

    complexLongDoubleVec -= complexLongDoubleVec;
    ASSERT_NEAR(complexLongDoubleVec[0].real(), 0.0, epsilon);   ASSERT_NEAR(complexLongDoubleVec[0].imag(), 0.0, epsilon);
    ASSERT_NEAR(complexLongDoubleVec[1].real(), 0.0, epsilon);   ASSERT_NEAR(complexLongDoubleVec[1].imag(), 0.0, epsilon);
    ASSERT_NEAR(complexLongDoubleVec[2].real(), 0.0, epsilon);   ASSERT_NEAR(complexLongDoubleVec[2].imag(), 0.0, epsilon);
}

TEST_F(ComplexVectorTests, DotProducts_Complex_Real)
{
    const auto intVec = Vector<int>({1,2,3});
    const auto floatVec = Vector<float>({1.1f,2.2f,3.3f});
    const auto doubleVec = Vector<double>({1.11,2.22,3.33});
    const auto longDoubleVec = Vector<long double>({1.12,2.23,3.34});

    const auto complexIntVec = Vector<std::complex<int>>({{1,1}, {2,2}, {3,3}});
    const auto complexFloatVec = Vector<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}});
    const auto complexDoubleVec = Vector<std::complex<double>>({{1.12,1.14}, {2.42,2.62}, {3.36,3.83}});
    const auto complexLongDoubleVec = Vector<std::complex<long double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.4}});

    //int dot complex<int>
    {
        auto dotProd = intVec.dot(complexIntVec);
        ASSERT_EQ(dotProd, std::complex<int>(14,14));

        dotProd = complexIntVec.dot(intVec);
        ASSERT_EQ(dotProd, std::complex<int>(14, -14));
    }

    //int dot complex<float>
    {
        auto dotProd = intVec.dot(complexFloatVec);
        ASSERT_NEAR(dotProd.real(), 15.4f, fepsilon);   ASSERT_NEAR(dotProd.imag(), 15.4f, fepsilon);

        dotProd = complexFloatVec.dot(intVec);
        ASSERT_NEAR(dotProd.real(), 15.4f, fepsilon);   ASSERT_NEAR(dotProd.imag(), -15.4f, fepsilon);
    }

    //int dot complex<double>
    {
        auto dotProd = intVec.dot(complexDoubleVec);
        ASSERT_NEAR(dotProd.real(), 16.04, epsilon);   ASSERT_NEAR(dotProd.imag(), 17.87, epsilon);

        dotProd = complexDoubleVec.dot(intVec);
        ASSERT_NEAR(dotProd.real(), 16.04, epsilon);   ASSERT_NEAR(dotProd.imag(), -17.87, epsilon);
    }

    //int dot complex<double>
    {
        auto dotProd = intVec.dot(complexLongDoubleVec);
        ASSERT_NEAR(dotProd.real(), 15.4, epsilon);   ASSERT_NEAR(dotProd.imag(), 15.7, epsilon);

        dotProd = complexLongDoubleVec.dot(intVec);
        ASSERT_NEAR(dotProd.real(), 15.4, epsilon);   ASSERT_NEAR(dotProd.imag(), -15.7, epsilon);
    }

    //float dot complex<int>
    {
        auto dotProd = floatVec.dot(complexIntVec);
        ASSERT_NEAR(dotProd.real(), 15.4f, fepsilon);   ASSERT_NEAR(dotProd.imag(), 15.4f, fepsilon);
        dotProd = complexIntVec.dot(floatVec);
        ASSERT_NEAR(dotProd.real(), 15.4f, fepsilon);   ASSERT_NEAR(dotProd.imag(), -15.4f, fepsilon);
    }

    //float dot complex<float>
    {
        auto dotProd = floatVec.dot(complexFloatVec);
        ASSERT_NEAR(dotProd.real(), 16.94f, fepsilon);   ASSERT_NEAR(dotProd.imag(), 16.94f, fepsilon);
        dotProd = complexFloatVec.dot(floatVec);
        ASSERT_NEAR(dotProd.real(), 16.94f, fepsilon);   ASSERT_NEAR(dotProd.imag(), -16.94f, fepsilon);
    }

    //float dot complex<double>
    {
        auto dotProd = floatVec.dot(complexDoubleVec);
        ASSERT_NEAR(dotProd.real(), 17.644, fepsilon);   ASSERT_NEAR(dotProd.imag(), 19.657, fepsilon);
        dotProd = complexDoubleVec.dot(floatVec);
        ASSERT_NEAR(dotProd.real(), 17.644, fepsilon);   ASSERT_NEAR(dotProd.imag(), -19.657, fepsilon);
    }

    //float dot complex<long double>
    {
        auto dotProd = floatVec.dot(complexLongDoubleVec);
        ASSERT_NEAR(dotProd.real(), 16.940, fepsilon);   ASSERT_NEAR(dotProd.imag(), 17.27, fepsilon);
        dotProd = complexLongDoubleVec.dot(floatVec);
        ASSERT_NEAR(dotProd.real(), 16.940, fepsilon);   ASSERT_NEAR(dotProd.imag(), -17.27, fepsilon);
    }

    //double dot complex<int>
    {
        auto dotProd = doubleVec.dot(complexIntVec);
        ASSERT_NEAR(dotProd.real(), 15.54, epsilon);   ASSERT_NEAR(dotProd.imag(), 15.54, epsilon);
        dotProd = complexIntVec.dot(doubleVec);
        ASSERT_NEAR(dotProd.real(), 15.54, epsilon);   ASSERT_NEAR(dotProd.imag(), -15.54, epsilon);
    }

    //double dot complex<float>
    {
        auto dotProd = doubleVec.dot(complexFloatVec);
        ASSERT_NEAR(dotProd.real(), 17.094, fepsilon);   ASSERT_NEAR(dotProd.imag(), 17.094, fepsilon);
        dotProd = complexFloatVec.dot(doubleVec);
        ASSERT_NEAR(dotProd.real(), 17.094f, fepsilon);   ASSERT_NEAR(dotProd.imag(), -17.094, fepsilon);
    }

    //double dot complex<double>
    {
        auto dotProd = doubleVec.dot(complexDoubleVec);
        ASSERT_NEAR(dotProd.real(), 17.8044, epsilon);   ASSERT_NEAR(dotProd.imag(), 19.8357, epsilon);
        dotProd = complexDoubleVec.dot(doubleVec);
        ASSERT_NEAR(dotProd.real(), 17.8044, epsilon);   ASSERT_NEAR(dotProd.imag(), -19.8357, epsilon);
    }

    //double dot complex<long double>
    {
        auto dotProd = doubleVec.dot(complexLongDoubleVec);
        ASSERT_NEAR(dotProd.real(), 17.094, epsilon);   ASSERT_NEAR(dotProd.imag(), 17.427, fepsilon);
        dotProd = complexLongDoubleVec.dot(doubleVec);
        ASSERT_NEAR(dotProd.real(), 17.094, epsilon);   ASSERT_NEAR(dotProd.imag(), -17.427, fepsilon);
    }

    //long double dot complex<int>
    {
        auto dotProd = longDoubleVec.dot(complexIntVec);
        ASSERT_NEAR(dotProd.real(), 15.6, epsilon);   ASSERT_NEAR(dotProd.imag(), 15.6, epsilon);
        dotProd = complexIntVec.dot(longDoubleVec);
        ASSERT_NEAR(dotProd.real(), 15.6, epsilon);   ASSERT_NEAR(dotProd.imag(), -15.6, epsilon);
    }

    //long double dot complex<float>
    {
        auto dotProd = longDoubleVec.dot(complexFloatVec);
        ASSERT_NEAR(dotProd.real(), 17.16, fepsilon);   ASSERT_NEAR(dotProd.imag(), 17.16, fepsilon);
        dotProd = complexFloatVec.dot(longDoubleVec);
        ASSERT_NEAR(dotProd.real(), 17.16, fepsilon);   ASSERT_NEAR(dotProd.imag(), -17.16, fepsilon);
    }

    //long double dot complex<double>
    {
        auto dotProd = longDoubleVec.dot(complexDoubleVec);
        ASSERT_NEAR(dotProd.real(), 17.8734, epsilon);   ASSERT_NEAR(dotProd.imag(), 19.9116, epsilon);
        dotProd = complexDoubleVec.dot(longDoubleVec);
        ASSERT_NEAR(dotProd.real(), 17.8734, epsilon);   ASSERT_NEAR(dotProd.imag(), -19.9116, epsilon);
    }

    //long double dot complex<long double>
    {
        auto dotProd = longDoubleVec.dot(complexLongDoubleVec);
        ASSERT_NEAR(dotProd.real(), 17.16, epsilon);   ASSERT_NEAR(dotProd.imag(), 17.494, fepsilon);
        dotProd = complexLongDoubleVec.dot(longDoubleVec);
        ASSERT_NEAR(dotProd.real(), 17.16, epsilon);   ASSERT_NEAR(dotProd.imag(), -17.494, fepsilon);
    }
}

TEST_F(ComplexVectorTests, DotProducts_Complex_Complex)
{
    const auto complexIntVec = Vector<std::complex<int>>({{1,1}, {2,2}, {3,3}});
    const auto complexFloatVec = Vector<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}});
    const auto complexDoubleVec = Vector<std::complex<double>>({{1.12,1.14}, {2.42,2.62}, {3.36,3.83}});
    const auto complexLongDoubleVec = Vector<std::complex<long double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.4}});

    //complex<int>-complex<int>
    {
        auto dotProd = complexIntVec.dot(complexIntVec);
        ASSERT_EQ(dotProd, std::complex<int>(28, 0));
    }

    //complex<int> dot complex<float>
    {
        auto dotProd = complexIntVec.dot(complexFloatVec);
        ASSERT_NEAR(dotProd.real(), 30.8f, fepsilon);   ASSERT_NEAR(dotProd.imag(), 0.0f, fepsilon);
        dotProd = complexFloatVec.dot(complexIntVec);
        ASSERT_NEAR(dotProd.real(), 30.8f, fepsilon);   ASSERT_NEAR(dotProd.imag(), 0.0f, fepsilon);
    }

    //complex<int> dot complex<double>
    {
        auto dotProd = complexIntVec.dot(complexDoubleVec);
        ASSERT_NEAR(dotProd.real(), 33.91, epsilon);   ASSERT_NEAR(dotProd.imag(), 1.83, epsilon);
        dotProd = complexDoubleVec.dot(complexIntVec);
        ASSERT_NEAR(dotProd.real(), 33.91, epsilon);   ASSERT_NEAR(dotProd.imag(), -1.83, epsilon);
    }

    //complex<int> dot complex<long double>
    {
        auto dotProd = complexIntVec.dot(complexLongDoubleVec);
        ASSERT_NEAR(dotProd.real(), 31.1, epsilon);   ASSERT_NEAR(dotProd.imag(), 0.3, epsilon);
        dotProd = complexLongDoubleVec.dot(complexIntVec);
        ASSERT_NEAR(dotProd.real(), 31.1, epsilon);   ASSERT_NEAR(dotProd.imag(), -0.3, epsilon);
    }

    //complex<float> dot complex<float>
    {
        auto dotProd = complexFloatVec.dot(complexFloatVec);
        ASSERT_NEAR(dotProd.real(), 33.88f, fepsilon);   ASSERT_NEAR(dotProd.imag(), 0.0f, fepsilon);
    }

    //complex<float> dot complex<double>
    {
        auto dotProd = complexFloatVec.dot(complexDoubleVec);
        ASSERT_NEAR(dotProd.real(), 37.3010, fepsilon);   ASSERT_NEAR(dotProd.imag(), 2.013, fepsilon);

        dotProd = complexDoubleVec.dot(complexFloatVec);
        ASSERT_NEAR(dotProd.real(), 37.3010, fepsilon);   ASSERT_NEAR(dotProd.imag(), -2.013, fepsilon);
    }

    //complex<float> dot complex<long double>
    {
        auto dotProd = complexFloatVec.dot(complexLongDoubleVec);
        ASSERT_NEAR(dotProd.real(), 34.21, fepsilon);   ASSERT_NEAR(dotProd.imag(), 0.33, fepsilon);

        dotProd = complexLongDoubleVec.dot(complexFloatVec);
        ASSERT_NEAR(dotProd.real(), 34.21, fepsilon);   ASSERT_NEAR(dotProd.imag(), -0.33, fepsilon);
    }

    //complex<double> dot complex<double>
    {
        auto dotProd = complexDoubleVec.dot(complexDoubleVec);
        ASSERT_NEAR(dotProd.real(), 41.2333, epsilon);   ASSERT_NEAR(dotProd.imag(), 0.0, epsilon);
    }

    //complex<double> dot complex<long double>
    {
        auto dotProd = complexDoubleVec.dot(complexLongDoubleVec);
        ASSERT_NEAR(dotProd.real(), 37.684, epsilon);   ASSERT_NEAR(dotProd.imag(), -1.677, epsilon);

        dotProd = complexLongDoubleVec.dot(complexDoubleVec);
        ASSERT_NEAR(dotProd.real(), 37.684, epsilon);   ASSERT_NEAR(dotProd.imag(), 1.677, epsilon);
    }

    //complex<long double> dot complex<long double>
    {
        auto dotProd = complexLongDoubleVec.dot(complexLongDoubleVec);
        ASSERT_NEAR(dotProd.real(), 34.550, epsilon);   ASSERT_NEAR(dotProd.imag(), 0.0, epsilon);
    }
}

TEST_F(ComplexVectorTests,  Norm)
{
    const auto complexIntVec = Vector<std::complex<int>>({{1,1}, {2,2}, {3,3}});
    const auto complexFloatVec = Vector<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {3.3f,3.3f}});
    const auto complexDoubleVec = Vector<std::complex<double>>({{1.12,1.14}, {2.42,2.62}, {3.36,3.83}});
    const auto complexLongDoubleVec = Vector<std::complex<long double>>({{1.1,1.1}, {2.2,2.2}, {3.3,3.4}});

    ASSERT_NEAR(complexIntVec.norm(), 5.291502622129181, epsilon);
    ASSERT_NEAR(complexFloatVec.norm(), 5.8206528843421, fepsilon);
    ASSERT_NEAR(complexDoubleVec.norm(), 6.421316064483978, epsilon);
    ASSERT_NEAR(complexLongDoubleVec.norm(), 5.877924803874238, epsilon);
}