//
// Created by dorian on 16.12.2023.
// stoicadorian@gmail.com
//

#include "gtest/gtest.h"
#include "Vector.hpp"

using namespace LinearAlgebra::Vector;

class VectorComplexBroadcastersTests : public ::testing::Test
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

TEST_F(VectorComplexBroadcastersTests, Addition_BroadcastComplexScalars_To_IntVector)
{
    const auto intVector = Vector<int>({1,2,3});

    const auto intComplexScalar = std::complex<int>{1,1};
    const auto floatComplexScalar = std::complex<float>{1.1f,1.1f};
    const auto doubleComplexScalar = std::complex<double>{1.1,1.1};
    const auto longDoubleComplexScalar = std::complex<double>{1.1,1.1};

    {
        const auto res = intVector + intComplexScalar;
        ASSERT_EQ(res[0], std::complex<int>(2,1));
        ASSERT_EQ(res[1], std::complex<int>(3,1));
        ASSERT_EQ(res[2], std::complex<int>(4,1));

        const auto resFloat = intVector + floatComplexScalar;
        ASSERT_NEAR(resFloat[0].real(), 2.1f, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 1.1f, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 3.1f, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 1.1f, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 4.1f, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 1.1f, fepsilon);

        const auto resDouble = intVector + doubleComplexScalar;
        ASSERT_NEAR(resDouble[0].real(), 2.1, epsilon);   ASSERT_NEAR(resDouble[0].imag(), 1.1, epsilon);
        ASSERT_NEAR(resDouble[1].real(), 3.1, epsilon);   ASSERT_NEAR(resDouble[1].imag(), 1.1, epsilon);
        ASSERT_NEAR(resDouble[2].real(), 4.1, epsilon);   ASSERT_NEAR(resDouble[2].imag(), 1.1, epsilon);

        const auto resLongDouble = intVector + longDoubleComplexScalar;
        ASSERT_NEAR(resLongDouble[0].real(), 2.1, epsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 1.1, epsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 3.1, epsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 1.1, epsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 4.1, epsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 1.1, epsilon);
    }

    {
        const auto res = intComplexScalar + intVector;
        ASSERT_EQ(res[0], std::complex<int>(2,1));
        ASSERT_EQ(res[1], std::complex<int>(3,1));
        ASSERT_EQ(res[2], std::complex<int>(4,1));

        const auto resFloat = floatComplexScalar + intVector;
        ASSERT_NEAR(resFloat[0].real(), 2.1f, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 1.1f, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 3.1f, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 1.1f, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 4.1f, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 1.1f, fepsilon);

        const auto resDouble = doubleComplexScalar + intVector;
        ASSERT_NEAR(resDouble[0].real(), 2.1, epsilon);   ASSERT_NEAR(resDouble[0].imag(), 1.1, epsilon);
        ASSERT_NEAR(resDouble[1].real(), 3.1, epsilon);   ASSERT_NEAR(resDouble[1].imag(), 1.1, epsilon);
        ASSERT_NEAR(resDouble[2].real(), 4.1, epsilon);   ASSERT_NEAR(resDouble[2].imag(), 1.1, epsilon);

        const auto resLongDouble = longDoubleComplexScalar + intVector;
        ASSERT_NEAR(resLongDouble[0].real(), 2.1, epsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 1.1, epsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 3.1, epsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 1.1, epsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 4.1, epsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 1.1, epsilon);
    }
}

TEST_F(VectorComplexBroadcastersTests, Addition_BroadcastScalars_To_ComplexIntVector)
{
    const auto complexIntVector = Vector<std::complex<int>>({{1,1},{2,2},{3,3}});

    const int intScalar = 1;
    const float floatScalar = 1.1f;
    const double doubleScalar = 1.1;
    const long double longScalar = 1.12;

    const auto intComplexScalar = std::complex<int>{1,1};
    const auto floatComplexScalar = std::complex<float>{1.1f,1.1f};
    const auto doubleComplexScalar = std::complex<double>{1.1,1.1};
    const auto longDoubleComplexScalar = std::complex<double>{1.1,1.12};

    {
        const auto res = complexIntVector + intScalar;
        ASSERT_EQ(res[0], std::complex<int>(2,1));
        ASSERT_EQ(res[1], std::complex<int>(3,2));
        ASSERT_EQ(res[2], std::complex<int>(4,3));

        const auto resFloat = complexIntVector + floatScalar;
        ASSERT_NEAR(resFloat[0].real(), 2.1f, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 1.0f, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 3.1f, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 2.0f, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 4.1f, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 3.0f, fepsilon);

        const auto resDouble = complexIntVector + doubleScalar;
        ASSERT_NEAR(resDouble[0].real(), 2.1, epsilon);   ASSERT_NEAR(resDouble[0].imag(), 1.0, epsilon);
        ASSERT_NEAR(resDouble[1].real(), 3.1, epsilon);   ASSERT_NEAR(resDouble[1].imag(), 2.0, epsilon);
        ASSERT_NEAR(resDouble[2].real(), 4.1, epsilon);   ASSERT_NEAR(resDouble[2].imag(), 3.0, epsilon);

        const auto resLongDouble = complexIntVector + longScalar;
        ASSERT_NEAR(resLongDouble[0].real(), 2.12, epsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 1.0, epsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 3.12, epsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 2.0, epsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 4.12, epsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 3.0, epsilon);
    }

    {
        const auto res = complexIntVector + intComplexScalar;
        ASSERT_EQ(res[0], std::complex<int>(2,2));
        ASSERT_EQ(res[1], std::complex<int>(3,3));
        ASSERT_EQ(res[2], std::complex<int>(4,4));

        const auto resFloat = complexIntVector + floatComplexScalar;
        ASSERT_NEAR(resFloat[0].real(), 2.1f, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 2.1f, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 3.1f, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 3.1f, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 4.1f, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 4.1f, fepsilon);

        const auto resDouble = complexIntVector + doubleComplexScalar;
        ASSERT_NEAR(resDouble[0].real(), 2.1, epsilon);   ASSERT_NEAR(resDouble[0].imag(), 2.1, epsilon);
        ASSERT_NEAR(resDouble[1].real(), 3.1, epsilon);   ASSERT_NEAR(resDouble[1].imag(), 3.1, epsilon);
        ASSERT_NEAR(resDouble[2].real(), 4.1, epsilon);   ASSERT_NEAR(resDouble[2].imag(), 4.1, epsilon);

        const auto resLongDouble = complexIntVector + longDoubleComplexScalar;
        ASSERT_NEAR(resLongDouble[0].real(), 2.1, epsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 2.12, epsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 3.1, epsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 3.12, epsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 4.1, epsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 4.12, epsilon);
    }

    // non-member op
    {
        const auto res = intScalar + complexIntVector;
        ASSERT_EQ(res[0], std::complex<int>(2,1));
        ASSERT_EQ(res[1], std::complex<int>(3,2));
        ASSERT_EQ(res[2], std::complex<int>(4,3));

        const auto resFloat = floatScalar + complexIntVector;
        ASSERT_NEAR(resFloat[0].real(), 2.1f, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 1.0f, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 3.1f, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 2.0f, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 4.1f, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 3.0f, fepsilon);

        const auto resDouble = doubleScalar + complexIntVector;
        ASSERT_NEAR(resDouble[0].real(), 2.1, epsilon);   ASSERT_NEAR(resDouble[0].imag(), 1.0, epsilon);
        ASSERT_NEAR(resDouble[1].real(), 3.1, epsilon);   ASSERT_NEAR(resDouble[1].imag(), 2.0, epsilon);
        ASSERT_NEAR(resDouble[2].real(), 4.1, epsilon);   ASSERT_NEAR(resDouble[2].imag(), 3.0, epsilon);

        const auto resLongDouble = longScalar + complexIntVector;
        ASSERT_NEAR(resLongDouble[0].real(), 2.12, epsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 1.0, epsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 3.12, epsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 2.0, epsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 4.12, epsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 3.0, epsilon);
    }

    {
        const auto res = intComplexScalar + complexIntVector;
        ASSERT_EQ(res[0], std::complex<int>(2,2));
        ASSERT_EQ(res[1], std::complex<int>(3,3));
        ASSERT_EQ(res[2], std::complex<int>(4,4));

        const auto resFloat = floatComplexScalar + complexIntVector;
        ASSERT_NEAR(resFloat[0].real(), 2.1f, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 2.1f, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 3.1f, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 3.1f, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 4.1f, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 4.1f, fepsilon);

        const auto resDouble = doubleComplexScalar + complexIntVector;
        ASSERT_NEAR(resDouble[0].real(), 2.1, epsilon);   ASSERT_NEAR(resDouble[0].imag(), 2.1, epsilon);
        ASSERT_NEAR(resDouble[1].real(), 3.1, epsilon);   ASSERT_NEAR(resDouble[1].imag(), 3.1, epsilon);
        ASSERT_NEAR(resDouble[2].real(), 4.1, epsilon);   ASSERT_NEAR(resDouble[2].imag(), 4.1, epsilon);

        const auto resLongDouble = longDoubleComplexScalar + complexIntVector;
        ASSERT_NEAR(resLongDouble[0].real(), 2.1, epsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 2.12, epsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 3.1, epsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 3.12, epsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 4.1, epsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 4.12, epsilon);
    }
}

TEST_F(VectorComplexBroadcastersTests, Addition_BroadcastComplexScalars_To_FloatVector)
{
    const auto floatVector = Vector<float>({1.1f,2.2f,3.3f});

    const auto intComplexScalar = std::complex<int>{1,1};
    const auto floatComplexScalar = std::complex<float>{1.1f,1.1f};
    const auto doubleComplexScalar = std::complex<double>{1.1,1.1};
    const auto longDoubleComplexScalar = std::complex<double>{1.1,1.1};

    {
        const auto res = floatVector + intComplexScalar;
        ASSERT_NEAR(res[0].real(), 2.1f, fepsilon);   ASSERT_NEAR(res[0].imag(), 1.0f, fepsilon);
        ASSERT_NEAR(res[1].real(), 3.2f, fepsilon);   ASSERT_NEAR(res[1].imag(), 1.0f, fepsilon);
        ASSERT_NEAR(res[2].real(), 4.3f, fepsilon);   ASSERT_NEAR(res[2].imag(), 1.0f, fepsilon);

        const auto resFloat = floatVector + floatComplexScalar;
        ASSERT_NEAR(resFloat[0].real(), 2.2f, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 1.1f, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 3.3f, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 1.1f, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 4.4f, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 1.1f, fepsilon);

        const auto resDouble = floatVector + doubleComplexScalar;
        ASSERT_NEAR(resDouble[0].real(), 2.2, fepsilon);   ASSERT_NEAR(resDouble[0].imag(), 1.1, fepsilon);
        ASSERT_NEAR(resDouble[1].real(), 3.3, fepsilon);   ASSERT_NEAR(resDouble[1].imag(), 1.1, fepsilon);
        ASSERT_NEAR(resDouble[2].real(), 4.4, fepsilon);   ASSERT_NEAR(resDouble[2].imag(), 1.1, fepsilon);

        const auto resLongDouble = floatVector + longDoubleComplexScalar;
        ASSERT_NEAR(resLongDouble[0].real(), 2.2, fepsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 1.1, fepsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 3.3, fepsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 1.1, fepsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 4.4, fepsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 1.1, fepsilon);
    }

    {
        const auto res = intComplexScalar + floatVector;
        ASSERT_NEAR(res[0].real(), 2.1f, fepsilon);   ASSERT_NEAR(res[0].imag(), 1.0f, fepsilon);
        ASSERT_NEAR(res[1].real(), 3.2f, fepsilon);   ASSERT_NEAR(res[1].imag(), 1.0f, fepsilon);
        ASSERT_NEAR(res[2].real(), 4.3f, fepsilon);   ASSERT_NEAR(res[2].imag(), 1.0f, fepsilon);

        const auto resFloat = floatComplexScalar + floatVector;
        ASSERT_NEAR(resFloat[0].real(), 2.2f, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 1.1f, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 3.3f, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 1.1f, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 4.4f, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 1.1f, fepsilon);

        const auto resDouble = doubleComplexScalar + floatVector;
        ASSERT_NEAR(resDouble[0].real(), 2.2, fepsilon);   ASSERT_NEAR(resDouble[0].imag(), 1.1, fepsilon);
        ASSERT_NEAR(resDouble[1].real(), 3.3, fepsilon);   ASSERT_NEAR(resDouble[1].imag(), 1.1, fepsilon);
        ASSERT_NEAR(resDouble[2].real(), 4.4, fepsilon);   ASSERT_NEAR(resDouble[2].imag(), 1.1, fepsilon);

        const auto resLongDouble = longDoubleComplexScalar + floatVector;
        ASSERT_NEAR(resLongDouble[0].real(), 2.2, fepsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 1.1, fepsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 3.3, fepsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 1.1, fepsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 4.4, fepsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 1.1, fepsilon);
    }
}

TEST_F(VectorComplexBroadcastersTests, Addition_BroadcastScalars_To_ComplexFloatVector)
{
    const auto complexFloatVector = Vector<std::complex<float>>({{1.1f,1.2f},{2.3f,2.4f},{3.5f,3.6f}});

    const int intScalar = 1;
    const float floatScalar = 1.1f;
    const double doubleScalar = 1.1;
    const long double longScalar = 1.12;

    const auto intComplexScalar = std::complex<int>{1,1};
    const auto floatComplexScalar = std::complex<float>{1.1f,1.1f};
    const auto doubleComplexScalar = std::complex<double>{1.1,1.1};
    const auto longDoubleComplexScalar = std::complex<double>{1.1,1.12};

    {
        const auto res = complexFloatVector + intScalar;
        ASSERT_NEAR(res[0].real(), 2.1f, fepsilon);   ASSERT_NEAR(res[0].imag(), 1.2f, fepsilon);
        ASSERT_NEAR(res[1].real(), 3.3f, fepsilon);   ASSERT_NEAR(res[1].imag(), 2.4f, fepsilon);
        ASSERT_NEAR(res[2].real(), 4.5f, fepsilon);   ASSERT_NEAR(res[2].imag(), 3.6f, fepsilon);

        const auto resFloat = complexFloatVector + floatScalar;
        ASSERT_NEAR(resFloat[0].real(), 2.2f, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 1.2f, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 3.4f, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 2.4f, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 4.6f, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 3.6f, fepsilon);

        const auto resDouble = complexFloatVector + doubleScalar;
        ASSERT_NEAR(resDouble[0].real(), 2.2, fepsilon);   ASSERT_NEAR(resDouble[0].imag(), 1.2, fepsilon);
        ASSERT_NEAR(resDouble[1].real(), 3.4, fepsilon);   ASSERT_NEAR(resDouble[1].imag(), 2.4, fepsilon);
        ASSERT_NEAR(resDouble[2].real(), 4.6, fepsilon);   ASSERT_NEAR(resDouble[2].imag(), 3.6, fepsilon);

        const auto resLongDouble = complexFloatVector + longScalar;
        ASSERT_NEAR(resLongDouble[0].real(), 2.22, fepsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 1.2, fepsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 3.42, fepsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 2.4, fepsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 4.62, fepsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 3.6, fepsilon);
    }

    {
        const auto res = complexFloatVector + intComplexScalar;
        ASSERT_NEAR(res[0].real(), 2.1f, fepsilon);   ASSERT_NEAR(res[0].imag(), 2.2f, fepsilon);
        ASSERT_NEAR(res[1].real(), 3.3f, fepsilon);   ASSERT_NEAR(res[1].imag(), 3.4f, fepsilon);
        ASSERT_NEAR(res[2].real(), 4.5f, fepsilon);   ASSERT_NEAR(res[2].imag(), 4.6f, fepsilon);


        const auto resFloat = complexFloatVector + floatComplexScalar;
        ASSERT_NEAR(resFloat[0].real(), 2.2f, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 2.3f, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 3.4f, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 3.5f, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 4.6f, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 4.7f, fepsilon);

        const auto resDouble = complexFloatVector + doubleComplexScalar;
        ASSERT_NEAR(resDouble[0].real(), 2.2, fepsilon);   ASSERT_NEAR(resDouble[0].imag(), 2.3, fepsilon);
        ASSERT_NEAR(resDouble[1].real(), 3.4, fepsilon);   ASSERT_NEAR(resDouble[1].imag(), 3.5, fepsilon);
        ASSERT_NEAR(resDouble[2].real(), 4.6, fepsilon);   ASSERT_NEAR(resDouble[2].imag(), 4.7, fepsilon);

        const auto resLongDouble = complexFloatVector + longDoubleComplexScalar;
        ASSERT_NEAR(resLongDouble[0].real(), 2.2, fepsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 2.32, fepsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 3.4, fepsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 3.52, fepsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 4.6, fepsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 4.72, fepsilon);
    }

    // non-member op
    {
        const auto res = intScalar + complexFloatVector;
        ASSERT_NEAR(res[0].real(), 2.1f, fepsilon);   ASSERT_NEAR(res[0].imag(), 1.2f, fepsilon);
        ASSERT_NEAR(res[1].real(), 3.3f, fepsilon);   ASSERT_NEAR(res[1].imag(), 2.4f, fepsilon);
        ASSERT_NEAR(res[2].real(), 4.5f, fepsilon);   ASSERT_NEAR(res[2].imag(), 3.6f, fepsilon);

        const auto resFloat = floatScalar + complexFloatVector;
        ASSERT_NEAR(resFloat[0].real(), 2.2f, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 1.2f, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 3.4f, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 2.4f, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 4.6f, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 3.6f, fepsilon);

        const auto resDouble = doubleScalar + complexFloatVector;
        ASSERT_NEAR(resDouble[0].real(), 2.2, fepsilon);   ASSERT_NEAR(resDouble[0].imag(), 1.2, fepsilon);
        ASSERT_NEAR(resDouble[1].real(), 3.4, fepsilon);   ASSERT_NEAR(resDouble[1].imag(), 2.4, fepsilon);
        ASSERT_NEAR(resDouble[2].real(), 4.6, fepsilon);   ASSERT_NEAR(resDouble[2].imag(), 3.6, fepsilon);

        const auto resLongDouble = longScalar + complexFloatVector;
        ASSERT_NEAR(resLongDouble[0].real(), 2.22, fepsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 1.2, fepsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 3.42, fepsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 2.4, fepsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 4.62, fepsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 3.6, fepsilon);
    }

    {
        const auto res = intComplexScalar + complexFloatVector;
        ASSERT_NEAR(res[0].real(), 2.1f, fepsilon);   ASSERT_NEAR(res[0].imag(), 2.2f, fepsilon);
        ASSERT_NEAR(res[1].real(), 3.3f, fepsilon);   ASSERT_NEAR(res[1].imag(), 3.4f, fepsilon);
        ASSERT_NEAR(res[2].real(), 4.5f, fepsilon);   ASSERT_NEAR(res[2].imag(), 4.6f, fepsilon);

        const auto resFloat = floatComplexScalar + complexFloatVector;
        ASSERT_NEAR(resFloat[0].real(), 2.2f, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 2.3f, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 3.4f, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 3.5f, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 4.6f, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 4.7f, fepsilon);

        const auto resDouble = doubleComplexScalar + complexFloatVector;
        ASSERT_NEAR(resDouble[0].real(), 2.2, fepsilon);   ASSERT_NEAR(resDouble[0].imag(), 2.3, fepsilon);
        ASSERT_NEAR(resDouble[1].real(), 3.4, fepsilon);   ASSERT_NEAR(resDouble[1].imag(), 3.5, fepsilon);
        ASSERT_NEAR(resDouble[2].real(), 4.6, fepsilon);   ASSERT_NEAR(resDouble[2].imag(), 4.7, fepsilon);

        const auto resLongDouble = longDoubleComplexScalar + complexFloatVector;
        ASSERT_NEAR(resLongDouble[0].real(), 2.2, fepsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 2.32, fepsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 3.4, fepsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 3.52, fepsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 4.6, fepsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 4.72, fepsilon);
    }
}


TEST_F(VectorComplexBroadcastersTests, Addition_BroadcastComplexScalars_To_DoubleVector)
{
    const auto doubleVector = Vector<double>({1.1,2.2,3.3});

    const auto intComplexScalar = std::complex<int>{1,1};
    const auto floatComplexScalar = std::complex<float>{1.1f,1.1f};
    const auto doubleComplexScalar = std::complex<double>{1.1,1.1};
    const auto longDoubleComplexScalar = std::complex<double>{1.1,1.1};

    {
        const auto res = doubleVector + intComplexScalar;
        ASSERT_NEAR(res[0].real(), 2.1, epsilon);   ASSERT_NEAR(res[0].imag(), 1.0, epsilon);
        ASSERT_NEAR(res[1].real(), 3.2, epsilon);   ASSERT_NEAR(res[1].imag(), 1.0, epsilon);
        ASSERT_NEAR(res[2].real(), 4.3, epsilon);   ASSERT_NEAR(res[2].imag(), 1.0, epsilon);

        const auto resFloat = doubleVector + floatComplexScalar;
        ASSERT_NEAR(resFloat[0].real(), 2.2, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 1.1, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 3.3, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 1.1, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 4.4, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 1.1, fepsilon);

        const auto resDouble = doubleVector + doubleComplexScalar;
        ASSERT_NEAR(resDouble[0].real(), 2.2, epsilon);   ASSERT_NEAR(resDouble[0].imag(), 1.1, epsilon);
        ASSERT_NEAR(resDouble[1].real(), 3.3, epsilon);   ASSERT_NEAR(resDouble[1].imag(), 1.1, epsilon);
        ASSERT_NEAR(resDouble[2].real(), 4.4, epsilon);   ASSERT_NEAR(resDouble[2].imag(), 1.1, epsilon);

        const auto resLongDouble = doubleVector + longDoubleComplexScalar;
        ASSERT_NEAR(resLongDouble[0].real(), 2.2, epsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 1.1, epsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 3.3, epsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 1.1, epsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 4.4, epsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 1.1, epsilon);
    }

    {
        const auto res = intComplexScalar + doubleVector;
        ASSERT_NEAR(res[0].real(), 2.1, epsilon);   ASSERT_NEAR(res[0].imag(), 1.0, epsilon);
        ASSERT_NEAR(res[1].real(), 3.2, epsilon);   ASSERT_NEAR(res[1].imag(), 1.0, epsilon);
        ASSERT_NEAR(res[2].real(), 4.3, epsilon);   ASSERT_NEAR(res[2].imag(), 1.0, epsilon);

        const auto resFloat = floatComplexScalar + doubleVector;
        ASSERT_NEAR(resFloat[0].real(), 2.2, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 1.1f, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 3.3, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 1.1f, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 4.4, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 1.1f, fepsilon);

        const auto resDouble = doubleComplexScalar + doubleVector;
        ASSERT_NEAR(resDouble[0].real(), 2.2, epsilon);   ASSERT_NEAR(resDouble[0].imag(), 1.1, epsilon);
        ASSERT_NEAR(resDouble[1].real(), 3.3, epsilon);   ASSERT_NEAR(resDouble[1].imag(), 1.1, epsilon);
        ASSERT_NEAR(resDouble[2].real(), 4.4, epsilon);   ASSERT_NEAR(resDouble[2].imag(), 1.1, epsilon);

        const auto resLongDouble = longDoubleComplexScalar + doubleVector;
        ASSERT_NEAR(resLongDouble[0].real(), 2.2, epsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 1.1, epsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 3.3, epsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 1.1, epsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 4.4, epsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 1.1, epsilon);
    }
}

TEST_F(VectorComplexBroadcastersTests, Addition_BroadcastScalars_To_ComplexDoubleVector)
{
    const auto complexDoubleVector = Vector<std::complex<double>>({{1.1,1.2},{2.3,2.4},{3.5,3.6}});

    const int intScalar = 1;
    const float floatScalar = 1.1f;
    const double doubleScalar = 1.1;
    const long double longScalar = 1.12;

    const auto intComplexScalar = std::complex<int>{1,1};
    const auto floatComplexScalar = std::complex<float>{1.1f,1.1f};
    const auto doubleComplexScalar = std::complex<double>{1.1,1.1};
    const auto longDoubleComplexScalar = std::complex<double>{1.1,1.12};

    {
        const auto res = complexDoubleVector + intScalar;
        ASSERT_NEAR(res[0].real(), 2.1, epsilon);   ASSERT_NEAR(res[0].imag(), 1.2, epsilon);
        ASSERT_NEAR(res[1].real(), 3.3, epsilon);   ASSERT_NEAR(res[1].imag(), 2.4, epsilon);
        ASSERT_NEAR(res[2].real(), 4.5, epsilon);   ASSERT_NEAR(res[2].imag(), 3.6, epsilon);

        const auto resFloat = complexDoubleVector + floatScalar;
        ASSERT_NEAR(resFloat[0].real(), 2.2, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 1.2, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 3.4, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 2.4, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 4.6, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 3.6, fepsilon);

        const auto resDouble = complexDoubleVector + doubleScalar;
        ASSERT_NEAR(resDouble[0].real(), 2.2, epsilon);   ASSERT_NEAR(resDouble[0].imag(), 1.2, epsilon);
        ASSERT_NEAR(resDouble[1].real(), 3.4, epsilon);   ASSERT_NEAR(resDouble[1].imag(), 2.4, epsilon);
        ASSERT_NEAR(resDouble[2].real(), 4.6, epsilon);   ASSERT_NEAR(resDouble[2].imag(), 3.6, epsilon);

        const auto resLongDouble = complexDoubleVector + longScalar;
        ASSERT_NEAR(resLongDouble[0].real(), 2.22, epsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 1.2, epsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 3.42, epsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 2.4, epsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 4.62, epsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 3.6, epsilon);
    }

    {
        const auto res = complexDoubleVector + intComplexScalar;
        ASSERT_NEAR(res[0].real(), 2.1, epsilon);   ASSERT_NEAR(res[0].imag(), 2.2f, fepsilon);
        ASSERT_NEAR(res[1].real(), 3.3, epsilon);   ASSERT_NEAR(res[1].imag(), 3.4f, fepsilon);
        ASSERT_NEAR(res[2].real(), 4.5, epsilon);   ASSERT_NEAR(res[2].imag(), 4.6f, fepsilon);


        const auto resFloat = complexDoubleVector + floatComplexScalar;
        ASSERT_NEAR(resFloat[0].real(), 2.2, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 2.3, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 3.4, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 3.5, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 4.6, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 4.7, fepsilon);

        const auto resDouble = complexDoubleVector + doubleComplexScalar;
        ASSERT_NEAR(resDouble[0].real(), 2.2, epsilon);   ASSERT_NEAR(resDouble[0].imag(), 2.3, epsilon);
        ASSERT_NEAR(resDouble[1].real(), 3.4, epsilon);   ASSERT_NEAR(resDouble[1].imag(), 3.5, epsilon);
        ASSERT_NEAR(resDouble[2].real(), 4.6, epsilon);   ASSERT_NEAR(resDouble[2].imag(), 4.7, epsilon);

        const auto resLongDouble = complexDoubleVector + longDoubleComplexScalar;
        ASSERT_NEAR(resLongDouble[0].real(), 2.2, epsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 2.32, epsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 3.4, epsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 3.52, epsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 4.6, epsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 4.72, epsilon);
    }

    // non-member op
    {
        const auto res = intScalar + complexDoubleVector;
        ASSERT_NEAR(res[0].real(), 2.1, epsilon);   ASSERT_NEAR(res[0].imag(), 1.2f, fepsilon);
        ASSERT_NEAR(res[1].real(), 3.3, epsilon);   ASSERT_NEAR(res[1].imag(), 2.4f, fepsilon);
        ASSERT_NEAR(res[2].real(), 4.5, epsilon);   ASSERT_NEAR(res[2].imag(), 3.6f, fepsilon);

        const auto resFloat = floatScalar + complexDoubleVector;
        ASSERT_NEAR(resFloat[0].real(), 2.2, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 1.2, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 3.4, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 2.4, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 4.6, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 3.6, fepsilon);

        const auto resDouble = doubleScalar + complexDoubleVector;
        ASSERT_NEAR(resDouble[0].real(), 2.2, epsilon);   ASSERT_NEAR(resDouble[0].imag(), 1.2, epsilon);
        ASSERT_NEAR(resDouble[1].real(), 3.4, epsilon);   ASSERT_NEAR(resDouble[1].imag(), 2.4, epsilon);
        ASSERT_NEAR(resDouble[2].real(), 4.6, epsilon);   ASSERT_NEAR(resDouble[2].imag(), 3.6, epsilon);

        const auto resLongDouble = longScalar + complexDoubleVector;
        ASSERT_NEAR(resLongDouble[0].real(), 2.22, epsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 1.2, epsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 3.42, epsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 2.4, epsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 4.62, epsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 3.6, epsilon);
    }

    {
        const auto res = intComplexScalar + complexDoubleVector;
        ASSERT_NEAR(res[0].real(), 2.1, epsilon);   ASSERT_NEAR(res[0].imag(), 2.2, epsilon);
        ASSERT_NEAR(res[1].real(), 3.3, epsilon);   ASSERT_NEAR(res[1].imag(), 3.4, epsilon);
        ASSERT_NEAR(res[2].real(), 4.5, epsilon);   ASSERT_NEAR(res[2].imag(), 4.6, epsilon);

        const auto resFloat = floatComplexScalar + complexDoubleVector;
        ASSERT_NEAR(resFloat[0].real(), 2.2, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 2.3, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 3.4, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 3.5, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 4.6, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 4.7, fepsilon);

        const auto resDouble = doubleComplexScalar + complexDoubleVector;
        ASSERT_NEAR(resDouble[0].real(), 2.2, epsilon);   ASSERT_NEAR(resDouble[0].imag(), 2.3, epsilon);
        ASSERT_NEAR(resDouble[1].real(), 3.4, epsilon);   ASSERT_NEAR(resDouble[1].imag(), 3.5, epsilon);
        ASSERT_NEAR(resDouble[2].real(), 4.6, epsilon);   ASSERT_NEAR(resDouble[2].imag(), 4.7, epsilon);

        const auto resLongDouble = longDoubleComplexScalar + complexDoubleVector;
        ASSERT_NEAR(resLongDouble[0].real(), 2.2, epsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 2.32, epsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 3.4, epsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 3.52, epsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 4.6, epsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 4.72, epsilon);
    }
}

TEST_F(VectorComplexBroadcastersTests, Addition_BroadcastComplexScalars_To_LongDoubleVector)
{
    const auto doubleVector = Vector<long double>({1.1,2.2,3.3});

    const auto intComplexScalar = std::complex<int>{1,1};
    const auto floatComplexScalar = std::complex<float>{1.1f,1.1f};
    const auto doubleComplexScalar = std::complex<double>{1.1,1.1};
    const auto longDoubleComplexScalar = std::complex<double>{1.1,1.1};

    {
        const auto res = doubleVector + intComplexScalar;
        ASSERT_NEAR(res[0].real(), 2.1, epsilon);   ASSERT_NEAR(res[0].imag(), 1.0, epsilon);
        ASSERT_NEAR(res[1].real(), 3.2, epsilon);   ASSERT_NEAR(res[1].imag(), 1.0, epsilon);
        ASSERT_NEAR(res[2].real(), 4.3, epsilon);   ASSERT_NEAR(res[2].imag(), 1.0, epsilon);

        const auto resFloat = doubleVector + floatComplexScalar;
        ASSERT_NEAR(resFloat[0].real(), 2.2, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 1.1, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 3.3, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 1.1, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 4.4, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 1.1, fepsilon);

        const auto resDouble = doubleVector + doubleComplexScalar;
        ASSERT_NEAR(resDouble[0].real(), 2.2, epsilon);   ASSERT_NEAR(resDouble[0].imag(), 1.1, epsilon);
        ASSERT_NEAR(resDouble[1].real(), 3.3, epsilon);   ASSERT_NEAR(resDouble[1].imag(), 1.1, epsilon);
        ASSERT_NEAR(resDouble[2].real(), 4.4, epsilon);   ASSERT_NEAR(resDouble[2].imag(), 1.1, epsilon);

        const auto resLongDouble = doubleVector + longDoubleComplexScalar;
        ASSERT_NEAR(resLongDouble[0].real(), 2.2, epsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 1.1, epsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 3.3, epsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 1.1, epsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 4.4, epsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 1.1, epsilon);
    }

    {
        const auto res = intComplexScalar + doubleVector;
        ASSERT_NEAR(res[0].real(), 2.1, epsilon);   ASSERT_NEAR(res[0].imag(), 1.0, epsilon);
        ASSERT_NEAR(res[1].real(), 3.2, epsilon);   ASSERT_NEAR(res[1].imag(), 1.0, epsilon);
        ASSERT_NEAR(res[2].real(), 4.3, epsilon);   ASSERT_NEAR(res[2].imag(), 1.0, epsilon);

        const auto resFloat = floatComplexScalar + doubleVector;
        ASSERT_NEAR(resFloat[0].real(), 2.2, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 1.1f, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 3.3, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 1.1f, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 4.4, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 1.1f, fepsilon);

        const auto resDouble = doubleComplexScalar + doubleVector;
        ASSERT_NEAR(resDouble[0].real(), 2.2, epsilon);   ASSERT_NEAR(resDouble[0].imag(), 1.1, epsilon);
        ASSERT_NEAR(resDouble[1].real(), 3.3, epsilon);   ASSERT_NEAR(resDouble[1].imag(), 1.1, epsilon);
        ASSERT_NEAR(resDouble[2].real(), 4.4, epsilon);   ASSERT_NEAR(resDouble[2].imag(), 1.1, epsilon);

        const auto resLongDouble = longDoubleComplexScalar + doubleVector;
        ASSERT_NEAR(resLongDouble[0].real(), 2.2, epsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 1.1, epsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 3.3, epsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 1.1, epsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 4.4, epsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 1.1, epsilon);
    }
}

TEST_F(VectorComplexBroadcastersTests, Addition_BroadcastScalars_To_ComplexLongDoubleVector)
{
    const auto complexDoubleVector = Vector<std::complex<long double>>({{1.1,1.2},{2.3,2.4},{3.5,3.6}});

    const int intScalar = 1;
    const float floatScalar = 1.1f;
    const double doubleScalar = 1.1;
    const long double longScalar = 1.12;

    const auto intComplexScalar = std::complex<int>{1,1};
    const auto floatComplexScalar = std::complex<float>{1.1f,1.1f};
    const auto doubleComplexScalar = std::complex<double>{1.1,1.1};
    const auto longDoubleComplexScalar = std::complex<double>{1.1,1.12};

    {
        const auto res = complexDoubleVector + intScalar;
        ASSERT_NEAR(res[0].real(), 2.1, epsilon);   ASSERT_NEAR(res[0].imag(), 1.2, epsilon);
        ASSERT_NEAR(res[1].real(), 3.3, epsilon);   ASSERT_NEAR(res[1].imag(), 2.4, epsilon);
        ASSERT_NEAR(res[2].real(), 4.5, epsilon);   ASSERT_NEAR(res[2].imag(), 3.6, epsilon);

        const auto resFloat = complexDoubleVector + floatScalar;
        ASSERT_NEAR(resFloat[0].real(), 2.2, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 1.2, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 3.4, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 2.4, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 4.6, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 3.6, fepsilon);

        const auto resDouble = complexDoubleVector + doubleScalar;
        ASSERT_NEAR(resDouble[0].real(), 2.2, epsilon);   ASSERT_NEAR(resDouble[0].imag(), 1.2, epsilon);
        ASSERT_NEAR(resDouble[1].real(), 3.4, epsilon);   ASSERT_NEAR(resDouble[1].imag(), 2.4, epsilon);
        ASSERT_NEAR(resDouble[2].real(), 4.6, epsilon);   ASSERT_NEAR(resDouble[2].imag(), 3.6, epsilon);

        const auto resLongDouble = complexDoubleVector + longScalar;
        ASSERT_NEAR(resLongDouble[0].real(), 2.22, epsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 1.2, epsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 3.42, epsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 2.4, epsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 4.62, epsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 3.6, epsilon);
    }

    {
        const auto res = complexDoubleVector + intComplexScalar;
        ASSERT_NEAR(res[0].real(), 2.1, epsilon);   ASSERT_NEAR(res[0].imag(), 2.2f, fepsilon);
        ASSERT_NEAR(res[1].real(), 3.3, epsilon);   ASSERT_NEAR(res[1].imag(), 3.4f, fepsilon);
        ASSERT_NEAR(res[2].real(), 4.5, epsilon);   ASSERT_NEAR(res[2].imag(), 4.6f, fepsilon);


        const auto resFloat = complexDoubleVector + floatComplexScalar;
        ASSERT_NEAR(resFloat[0].real(), 2.2, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 2.3, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 3.4, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 3.5, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 4.6, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 4.7, fepsilon);

        const auto resDouble = complexDoubleVector + doubleComplexScalar;
        ASSERT_NEAR(resDouble[0].real(), 2.2, epsilon);   ASSERT_NEAR(resDouble[0].imag(), 2.3, epsilon);
        ASSERT_NEAR(resDouble[1].real(), 3.4, epsilon);   ASSERT_NEAR(resDouble[1].imag(), 3.5, epsilon);
        ASSERT_NEAR(resDouble[2].real(), 4.6, epsilon);   ASSERT_NEAR(resDouble[2].imag(), 4.7, epsilon);

        const auto resLongDouble = complexDoubleVector + longDoubleComplexScalar;
        ASSERT_NEAR(resLongDouble[0].real(), 2.2, epsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 2.32, epsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 3.4, epsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 3.52, epsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 4.6, epsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 4.72, epsilon);
    }

    // non-member op
    {
        const auto res = intScalar + complexDoubleVector;
        ASSERT_NEAR(res[0].real(), 2.1, epsilon);   ASSERT_NEAR(res[0].imag(), 1.2f, fepsilon);
        ASSERT_NEAR(res[1].real(), 3.3, epsilon);   ASSERT_NEAR(res[1].imag(), 2.4f, fepsilon);
        ASSERT_NEAR(res[2].real(), 4.5, epsilon);   ASSERT_NEAR(res[2].imag(), 3.6f, fepsilon);

        const auto resFloat = floatScalar + complexDoubleVector;
        ASSERT_NEAR(resFloat[0].real(), 2.2, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 1.2, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 3.4, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 2.4, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 4.6, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 3.6, fepsilon);

        const auto resDouble = doubleScalar + complexDoubleVector;
        ASSERT_NEAR(resDouble[0].real(), 2.2, epsilon);   ASSERT_NEAR(resDouble[0].imag(), 1.2, epsilon);
        ASSERT_NEAR(resDouble[1].real(), 3.4, epsilon);   ASSERT_NEAR(resDouble[1].imag(), 2.4, epsilon);
        ASSERT_NEAR(resDouble[2].real(), 4.6, epsilon);   ASSERT_NEAR(resDouble[2].imag(), 3.6, epsilon);

        const auto resLongDouble = longScalar + complexDoubleVector;
        ASSERT_NEAR(resLongDouble[0].real(), 2.22, epsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 1.2, epsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 3.42, epsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 2.4, epsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 4.62, epsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 3.6, epsilon);
    }

    {
        const auto res = intComplexScalar + complexDoubleVector;
        ASSERT_NEAR(res[0].real(), 2.1, epsilon);   ASSERT_NEAR(res[0].imag(), 2.2, epsilon);
        ASSERT_NEAR(res[1].real(), 3.3, epsilon);   ASSERT_NEAR(res[1].imag(), 3.4, epsilon);
        ASSERT_NEAR(res[2].real(), 4.5, epsilon);   ASSERT_NEAR(res[2].imag(), 4.6, epsilon);

        const auto resFloat = floatComplexScalar + complexDoubleVector;
        ASSERT_NEAR(resFloat[0].real(), 2.2, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 2.3, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 3.4, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 3.5, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 4.6, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 4.7, fepsilon);

        const auto resDouble = doubleComplexScalar + complexDoubleVector;
        ASSERT_NEAR(resDouble[0].real(), 2.2, epsilon);   ASSERT_NEAR(resDouble[0].imag(), 2.3, epsilon);
        ASSERT_NEAR(resDouble[1].real(), 3.4, epsilon);   ASSERT_NEAR(resDouble[1].imag(), 3.5, epsilon);
        ASSERT_NEAR(resDouble[2].real(), 4.6, epsilon);   ASSERT_NEAR(resDouble[2].imag(), 4.7, epsilon);

        const auto resLongDouble = longDoubleComplexScalar + complexDoubleVector;
        ASSERT_NEAR(resLongDouble[0].real(), 2.2, epsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 2.32, epsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 3.4, epsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 3.52, epsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 4.6, epsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 4.72, epsilon);
    }
}

TEST_F(VectorComplexBroadcastersTests, Addition_InPlace_Broadcaster)
{
    auto complexIntVector = Vector<std::complex<int>>({{1, 1},{2 ,2},{3, 3}});
    auto complexFloatVector = Vector<std::complex<float>>({{1.1f, 1.2f},{2.3f, 2.4f},{3.5f, 3.6f}});
    auto complexDoubleVector = Vector<std::complex<double>>({{1.1,1.2},{2.3,2.4},{3.5,3.6}});
    auto complexLongDoubleVector = Vector<std::complex<long double>>({{1.1,1.2},{2.3,2.4},{3.5,3.6}});

    const auto intComplexScalar = std::complex<int>{1,1};
    const auto floatComplexScalar = std::complex<float>{1.1f,1.1f};
    const auto doubleComplexScalar = std::complex<double>{1.1,1.1};
    const auto longDoubleComplexScalar = std::complex<double>{1.1,1.12};

    complexIntVector += intComplexScalar;
    ASSERT_EQ(complexIntVector[0], std::complex<int>(2,2));
    ASSERT_EQ(complexIntVector[1], std::complex<int>(3,3));
    ASSERT_EQ(complexIntVector[2], std::complex<int>(4,4));

    complexFloatVector += floatComplexScalar;
    ASSERT_NEAR(complexFloatVector[0].real(), 2.2f, fepsilon);   ASSERT_NEAR(complexFloatVector[0].imag(), 2.3f, fepsilon);
    ASSERT_NEAR(complexFloatVector[1].real(), 3.4f, fepsilon);   ASSERT_NEAR(complexFloatVector[1].imag(), 3.5f, fepsilon);
    ASSERT_NEAR(complexFloatVector[2].real(), 4.6f, fepsilon);   ASSERT_NEAR(complexFloatVector[2].imag(), 4.7f, fepsilon);

    complexDoubleVector += doubleComplexScalar;
    ASSERT_NEAR(complexDoubleVector[0].real(), 2.2, epsilon);   ASSERT_NEAR(complexDoubleVector[0].imag(), 2.3, epsilon);
    ASSERT_NEAR(complexDoubleVector[1].real(), 3.4, epsilon);   ASSERT_NEAR(complexDoubleVector[1].imag(), 3.5, epsilon);
    ASSERT_NEAR(complexDoubleVector[2].real(), 4.6, epsilon);   ASSERT_NEAR(complexDoubleVector[2].imag(), 4.7, epsilon);

    complexLongDoubleVector += longDoubleComplexScalar;
    ASSERT_NEAR(complexLongDoubleVector[0].real(), 2.2, epsilon);   ASSERT_NEAR(complexLongDoubleVector[0].imag(), 2.32, epsilon);
    ASSERT_NEAR(complexLongDoubleVector[1].real(), 3.4, epsilon);   ASSERT_NEAR(complexLongDoubleVector[1].imag(), 3.52, epsilon);
    ASSERT_NEAR(complexLongDoubleVector[2].real(), 4.6, epsilon);   ASSERT_NEAR(complexLongDoubleVector[2].imag(), 4.72, epsilon);
}

TEST_F(VectorComplexBroadcastersTests, Subtraction_BroadcastComplexScalars_To_IntVector)
{
    const auto intVector = Vector<int>({1,2,3});

    const auto intComplexScalar = std::complex<int>{1,1};
    const auto floatComplexScalar = std::complex<float>{1.1f,1.1f};
    const auto doubleComplexScalar = std::complex<double>{1.1,1.1};
    const auto longDoubleComplexScalar = std::complex<double>{1.1,1.1};

    {
        const auto res = intVector - intComplexScalar;
        ASSERT_EQ(res[0], std::complex<int>(0,-1));
        ASSERT_EQ(res[1], std::complex<int>(1,-1));
        ASSERT_EQ(res[2], std::complex<int>(2,-1));

        const auto resFloat = intVector - floatComplexScalar;
        ASSERT_NEAR(resFloat[0].real(), -0.1f, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), -1.1f, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 0.9f, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), -1.1f, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 1.9f, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), -1.1f, fepsilon);

        const auto resDouble = intVector - doubleComplexScalar;
        ASSERT_NEAR(resDouble[0].real(), -0.1, epsilon);   ASSERT_NEAR(resDouble[0].imag(), -1.1, epsilon);
        ASSERT_NEAR(resDouble[1].real(), 0.9, epsilon);   ASSERT_NEAR(resDouble[1].imag(), -1.1, epsilon);
        ASSERT_NEAR(resDouble[2].real(), 1.9, epsilon);   ASSERT_NEAR(resDouble[2].imag(), -1.1, epsilon);

        const auto resLongDouble = intVector - longDoubleComplexScalar;
        ASSERT_NEAR(resLongDouble[0].real(), -0.1, epsilon);   ASSERT_NEAR(resLongDouble[0].imag(), -1.1, epsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 0.9, epsilon);   ASSERT_NEAR(resLongDouble[1].imag(), -1.1, epsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 1.9, epsilon);   ASSERT_NEAR(resLongDouble[2].imag(), -1.1, epsilon);
    }
}

TEST_F(VectorComplexBroadcastersTests, Subtraction_BroadcastScalars_To_ComplexIntVector)
{
    const auto complexIntVector = Vector<std::complex<int>>({{1,1},{2,2},{3,3}});

    const int intScalar = 1;
    const float floatScalar = 1.1f;
    const double doubleScalar = 1.1;
    const long double longScalar = 1.12;

    const auto intComplexScalar = std::complex<int>{1,1};
    const auto floatComplexScalar = std::complex<float>{1.1f,1.1f};
    const auto doubleComplexScalar = std::complex<double>{1.1,1.1};
    const auto longDoubleComplexScalar = std::complex<double>{1.1,1.12};

    {
        const auto res = complexIntVector - intScalar;
        ASSERT_EQ(res[0], std::complex<int>(0,1));
        ASSERT_EQ(res[1], std::complex<int>(1,2));
        ASSERT_EQ(res[2], std::complex<int>(2,3));

        const auto resFloat = complexIntVector - floatScalar;
        ASSERT_NEAR(resFloat[0].real(), -0.1f, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 1.0f, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 0.9f, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 2.0f, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 1.9f, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 3.0f, fepsilon);

        const auto resDouble = complexIntVector - doubleScalar;
        ASSERT_NEAR(resDouble[0].real(), -0.1, epsilon);   ASSERT_NEAR(resDouble[0].imag(), 1.0, epsilon);
        ASSERT_NEAR(resDouble[1].real(), 0.9, epsilon);   ASSERT_NEAR(resDouble[1].imag(), 2.0, epsilon);
        ASSERT_NEAR(resDouble[2].real(), 1.9, epsilon);   ASSERT_NEAR(resDouble[2].imag(), 3.0, epsilon);

        const auto resLongDouble = complexIntVector - longScalar;
        ASSERT_NEAR(resLongDouble[0].real(), -0.12, epsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 1.0, epsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 0.88, epsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 2.0, epsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 1.88, epsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 3.0, epsilon);
    }

    {
        const auto res = complexIntVector + intComplexScalar;
        ASSERT_EQ(res[0], std::complex<int>(2,2));
        ASSERT_EQ(res[1], std::complex<int>(3,3));
        ASSERT_EQ(res[2], std::complex<int>(4,4));

        const auto resFloat = complexIntVector + floatComplexScalar;
        ASSERT_NEAR(resFloat[0].real(), 2.1f, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 2.1f, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 3.1f, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 3.1f, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 4.1f, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 4.1f, fepsilon);

        const auto resDouble = complexIntVector + doubleComplexScalar;
        ASSERT_NEAR(resDouble[0].real(), 2.1, epsilon);   ASSERT_NEAR(resDouble[0].imag(), 2.1, epsilon);
        ASSERT_NEAR(resDouble[1].real(), 3.1, epsilon);   ASSERT_NEAR(resDouble[1].imag(), 3.1, epsilon);
        ASSERT_NEAR(resDouble[2].real(), 4.1, epsilon);   ASSERT_NEAR(resDouble[2].imag(), 4.1, epsilon);

        const auto resLongDouble = complexIntVector + longDoubleComplexScalar;
        ASSERT_NEAR(resLongDouble[0].real(), 2.1, epsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 2.12, epsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 3.1, epsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 3.12, epsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 4.1, epsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 4.12, epsilon);
    }
}

TEST_F(VectorComplexBroadcastersTests, Subtraction_BroadcastComplexScalars_To_FloatVector)
{
    const auto floatVector = Vector<float>({1.1f,2.2f,3.3f});

    const auto intComplexScalar = std::complex<int>{1,1};
    const auto floatComplexScalar = std::complex<float>{1.1f,1.1f};
    const auto doubleComplexScalar = std::complex<double>{1.1,1.1};
    const auto longDoubleComplexScalar = std::complex<double>{1.1,1.1};

    {
        const auto res = floatVector - intComplexScalar;
        ASSERT_NEAR(res[0].real(), 0.1f, fepsilon);   ASSERT_NEAR(res[0].imag(), -1.0f, fepsilon);
        ASSERT_NEAR(res[1].real(), 1.2f, fepsilon);   ASSERT_NEAR(res[1].imag(), -1.0f, fepsilon);
        ASSERT_NEAR(res[2].real(), 2.3f, fepsilon);   ASSERT_NEAR(res[2].imag(), -1.0f, fepsilon);

        const auto resFloat = floatVector - floatComplexScalar;
        ASSERT_NEAR(resFloat[0].real(), 0.0f, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), -1.1f, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 1.1f, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), -1.1f, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 2.2f, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), -1.1f, fepsilon);

        const auto resDouble = floatVector - doubleComplexScalar;
        ASSERT_NEAR(resDouble[0].real(), 0.0, fepsilon);   ASSERT_NEAR(resDouble[0].imag(), -1.1, fepsilon);
        ASSERT_NEAR(resDouble[1].real(), 1.1, fepsilon);   ASSERT_NEAR(resDouble[1].imag(), -1.1, fepsilon);
        ASSERT_NEAR(resDouble[2].real(), 2.2, fepsilon);   ASSERT_NEAR(resDouble[2].imag(), -1.1, fepsilon);

        const auto resLongDouble = floatVector - longDoubleComplexScalar;
        ASSERT_NEAR(resLongDouble[0].real(), 0.0, fepsilon);   ASSERT_NEAR(resLongDouble[0].imag(), -1.1, fepsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 1.1, fepsilon);   ASSERT_NEAR(resLongDouble[1].imag(), -1.1, fepsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 2.2, fepsilon);   ASSERT_NEAR(resLongDouble[2].imag(), -1.1, fepsilon);
    }
}

TEST_F(VectorComplexBroadcastersTests, Subtraction_BroadcastScalars_To_ComplexFloatVector)
{
    const auto complexFloatVector = Vector<std::complex<float>>({{1.1f,1.2f},{2.3f,2.4f},{3.5f,3.6f}});

    const int intScalar = 1;
    const float floatScalar = 1.1f;
    const double doubleScalar = 1.1;
    const long double longScalar = 1.12;

    const auto intComplexScalar = std::complex<int>{1,1};
    const auto floatComplexScalar = std::complex<float>{1.1f,1.1f};
    const auto doubleComplexScalar = std::complex<double>{1.1,1.1};
    const auto longDoubleComplexScalar = std::complex<double>{1.1,1.12};

    {
        const auto res = complexFloatVector - intScalar;
        ASSERT_NEAR(res[0].real(), 0.1f, fepsilon);   ASSERT_NEAR(res[0].imag(), 1.2f, fepsilon);
        ASSERT_NEAR(res[1].real(), 1.3f, fepsilon);   ASSERT_NEAR(res[1].imag(), 2.4f, fepsilon);
        ASSERT_NEAR(res[2].real(), 2.5f, fepsilon);   ASSERT_NEAR(res[2].imag(), 3.6f, fepsilon);

        const auto resFloat = complexFloatVector - floatScalar;
        ASSERT_NEAR(resFloat[0].real(), 0.0f, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 1.2f, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 1.2f, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 2.4f, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 2.4f, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 3.6f, fepsilon);

        const auto resDouble = complexFloatVector - doubleScalar;
        ASSERT_NEAR(resDouble[0].real(), 0.0, fepsilon);   ASSERT_NEAR(resDouble[0].imag(), 1.2, fepsilon);
        ASSERT_NEAR(resDouble[1].real(), 1.2, fepsilon);   ASSERT_NEAR(resDouble[1].imag(), 2.4, fepsilon);
        ASSERT_NEAR(resDouble[2].real(), 2.4, fepsilon);   ASSERT_NEAR(resDouble[2].imag(), 3.6, fepsilon);

        const auto resLongDouble = complexFloatVector - longScalar;
        ASSERT_NEAR(resLongDouble[0].real(), -0.02, fepsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 1.2, fepsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 1.18, fepsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 2.4, fepsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 2.38, fepsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 3.6, fepsilon);
    }

    {
        const auto res = complexFloatVector - intComplexScalar;
        ASSERT_NEAR(res[0].real(), 0.1f, fepsilon);   ASSERT_NEAR(res[0].imag(), 0.2f, fepsilon);
        ASSERT_NEAR(res[1].real(), 1.3f, fepsilon);   ASSERT_NEAR(res[1].imag(), 1.4f, fepsilon);
        ASSERT_NEAR(res[2].real(), 2.5f, fepsilon);   ASSERT_NEAR(res[2].imag(), 2.6f, fepsilon);


        const auto resFloat = complexFloatVector - floatComplexScalar;
        ASSERT_NEAR(resFloat[0].real(), 0.0f, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 0.1f, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 1.2f, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 1.3f, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 2.4f, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 2.5f, fepsilon);

        const auto resDouble = complexFloatVector - doubleComplexScalar;
        ASSERT_NEAR(resDouble[0].real(), 0.0, fepsilon);   ASSERT_NEAR(resDouble[0].imag(), 0.1, fepsilon);
        ASSERT_NEAR(resDouble[1].real(), 1.2, fepsilon);   ASSERT_NEAR(resDouble[1].imag(), 1.3, fepsilon);
        ASSERT_NEAR(resDouble[2].real(), 2.4, fepsilon);   ASSERT_NEAR(resDouble[2].imag(), 2.5, fepsilon);

        const auto resLongDouble = complexFloatVector - longDoubleComplexScalar;
        ASSERT_NEAR(resLongDouble[0].real(), 0.0, fepsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 0.08, fepsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 1.2, fepsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 1.28, fepsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 2.4, fepsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 2.48, fepsilon);
    }
}


TEST_F(VectorComplexBroadcastersTests, Subtraction_BroadcastComplexScalars_To_DoubleVector)
{
    const auto doubleVector = Vector<double>({1.1,2.2,3.3});

    const auto intComplexScalar = std::complex<int>{1,1};
    const auto floatComplexScalar = std::complex<float>{1.1f,1.1f};
    const auto doubleComplexScalar = std::complex<double>{1.1,1.1};
    const auto longDoubleComplexScalar = std::complex<double>{1.1,1.1};

    {
        const auto res = doubleVector - intComplexScalar;
        ASSERT_NEAR(res[0].real(), 0.1, epsilon);   ASSERT_NEAR(res[0].imag(), -1.0, epsilon);
        ASSERT_NEAR(res[1].real(), 1.2, epsilon);   ASSERT_NEAR(res[1].imag(), -1.0, epsilon);
        ASSERT_NEAR(res[2].real(), 2.3, epsilon);   ASSERT_NEAR(res[2].imag(), -1.0, epsilon);

        const auto resFloat = doubleVector - floatComplexScalar;
        ASSERT_NEAR(resFloat[0].real(), 0.0, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), -1.1, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 1.1, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), -1.1, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 2.2, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), -1.1, fepsilon);

        const auto resDouble = doubleVector - doubleComplexScalar;
        ASSERT_NEAR(resDouble[0].real(), 0.0, epsilon);   ASSERT_NEAR(resDouble[0].imag(), -1.1, epsilon);
        ASSERT_NEAR(resDouble[1].real(), 1.1, epsilon);   ASSERT_NEAR(resDouble[1].imag(), -1.1, epsilon);
        ASSERT_NEAR(resDouble[2].real(), 2.2, epsilon);   ASSERT_NEAR(resDouble[2].imag(), -1.1, epsilon);

        const auto resLongDouble = doubleVector - longDoubleComplexScalar;
        ASSERT_NEAR(resLongDouble[0].real(), 0.0, epsilon);   ASSERT_NEAR(resLongDouble[0].imag(), -1.1, epsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 1.1, epsilon);   ASSERT_NEAR(resLongDouble[1].imag(), -1.1, epsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 2.2, epsilon);   ASSERT_NEAR(resLongDouble[2].imag(), -1.1, epsilon);
    }
}

TEST_F(VectorComplexBroadcastersTests, Subtraction_BroadcastScalars_To_ComplexDoubleVector)
{
    const auto complexDoubleVector = Vector<std::complex<double>>({{1.1,1.2},{2.3,2.4},{3.5,3.6}});

    const int intScalar = 1;
    const float floatScalar = 1.1f;
    const double doubleScalar = 1.1;
    const long double longScalar = 1.12;

    const auto intComplexScalar = std::complex<int>{1,1};
    const auto floatComplexScalar = std::complex<float>{1.1f,1.1f};
    const auto doubleComplexScalar = std::complex<double>{1.1,1.1};
    const auto longDoubleComplexScalar = std::complex<double>{1.1,1.12};

    {
        const auto res = complexDoubleVector - intScalar;
        ASSERT_NEAR(res[0].real(), 0.1, epsilon);   ASSERT_NEAR(res[0].imag(), 1.2, epsilon);
        ASSERT_NEAR(res[1].real(), 1.3, epsilon);   ASSERT_NEAR(res[1].imag(), 2.4, epsilon);
        ASSERT_NEAR(res[2].real(), 2.5, epsilon);   ASSERT_NEAR(res[2].imag(), 3.6, epsilon);

        const auto resFloat = complexDoubleVector - floatScalar;
        ASSERT_NEAR(resFloat[0].real(), 0.0, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 1.2, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 1.2, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 2.4, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 2.4, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 3.6, fepsilon);

        const auto resDouble = complexDoubleVector - doubleScalar;
        ASSERT_NEAR(resDouble[0].real(), 0.0, epsilon);   ASSERT_NEAR(resDouble[0].imag(), 1.2, epsilon);
        ASSERT_NEAR(resDouble[1].real(), 1.2, epsilon);   ASSERT_NEAR(resDouble[1].imag(), 2.4, epsilon);
        ASSERT_NEAR(resDouble[2].real(), 2.4, epsilon);   ASSERT_NEAR(resDouble[2].imag(), 3.6, epsilon);

        const auto resLongDouble = complexDoubleVector - longScalar;
        ASSERT_NEAR(resLongDouble[0].real(), -0.02, epsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 1.2, epsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 1.18, epsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 2.4, epsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 2.38, epsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 3.6, epsilon);
    }

    {
        const auto res = complexDoubleVector - intComplexScalar;
        ASSERT_NEAR(res[0].real(), 0.1, epsilon);   ASSERT_NEAR(res[0].imag(), 0.2f, fepsilon);
        ASSERT_NEAR(res[1].real(), 1.3, epsilon);   ASSERT_NEAR(res[1].imag(), 1.4f, fepsilon);
        ASSERT_NEAR(res[2].real(), 2.5, epsilon);   ASSERT_NEAR(res[2].imag(), 2.6f, fepsilon);


        const auto resFloat = complexDoubleVector - floatComplexScalar;
        ASSERT_NEAR(resFloat[0].real(), 0.0, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 0.1, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 1.2, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 1.3, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 2.4, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 2.5, fepsilon);

        const auto resDouble = complexDoubleVector - doubleComplexScalar;
        ASSERT_NEAR(resDouble[0].real(), 0.0, epsilon);   ASSERT_NEAR(resDouble[0].imag(), 0.1, epsilon);
        ASSERT_NEAR(resDouble[1].real(), 1.2, epsilon);   ASSERT_NEAR(resDouble[1].imag(), 1.3, epsilon);
        ASSERT_NEAR(resDouble[2].real(), 2.4, epsilon);   ASSERT_NEAR(resDouble[2].imag(), 2.5, epsilon);

        const auto resLongDouble = complexDoubleVector - longDoubleComplexScalar;
        ASSERT_NEAR(resLongDouble[0].real(), 0.0, epsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 0.08, epsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 1.2, epsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 1.28, epsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 2.4, epsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 2.48, epsilon);
    }
}

TEST_F(VectorComplexBroadcastersTests, Subtraction_BroadcastComplexScalars_To_LongDoubleVector)
{
    const auto doubleVector = Vector<long double>({1.1,2.2,3.3});

    const auto intComplexScalar = std::complex<int>{1,1};
    const auto floatComplexScalar = std::complex<float>{1.1f,1.1f};
    const auto doubleComplexScalar = std::complex<double>{1.1,1.1};
    const auto longDoubleComplexScalar = std::complex<double>{1.1,1.1};

    {
        const auto res = doubleVector - intComplexScalar;
        ASSERT_NEAR(res[0].real(), 0.1, epsilon);   ASSERT_NEAR(res[0].imag(), -1.0, epsilon);
        ASSERT_NEAR(res[1].real(), 1.2, epsilon);   ASSERT_NEAR(res[1].imag(), -1.0, epsilon);
        ASSERT_NEAR(res[2].real(), 2.3, epsilon);   ASSERT_NEAR(res[2].imag(), -1.0, epsilon);

        const auto resFloat = doubleVector - floatComplexScalar;
        ASSERT_NEAR(resFloat[0].real(), 0.0, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), -1.1, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 1.1, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), -1.1, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 2.2, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), -1.1, fepsilon);

        const auto resDouble = doubleVector - doubleComplexScalar;
        ASSERT_NEAR(resDouble[0].real(), 0.0, epsilon);   ASSERT_NEAR(resDouble[0].imag(), -1.1, epsilon);
        ASSERT_NEAR(resDouble[1].real(), 1.1, epsilon);   ASSERT_NEAR(resDouble[1].imag(), -1.1, epsilon);
        ASSERT_NEAR(resDouble[2].real(), 2.2, epsilon);   ASSERT_NEAR(resDouble[2].imag(), -1.1, epsilon);

        const auto resLongDouble = doubleVector - longDoubleComplexScalar;
        ASSERT_NEAR(resLongDouble[0].real(), 0.0, epsilon);   ASSERT_NEAR(resLongDouble[0].imag(), -1.1, epsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 1.1, epsilon);   ASSERT_NEAR(resLongDouble[1].imag(), -1.1, epsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 2.2, epsilon);   ASSERT_NEAR(resLongDouble[2].imag(), -1.1, epsilon);
    }
}

TEST_F(VectorComplexBroadcastersTests, Subtraction_BroadcastScalars_To_ComplexLongDoubleVector)
{
    const auto complexDoubleVector = Vector<std::complex<long double>>({{1.1,1.2},{2.3,2.4},{3.5,3.6}});

    const int intScalar = 1;
    const float floatScalar = 1.1f;
    const double doubleScalar = 1.1;
    const long double longScalar = 1.12;

    const auto intComplexScalar = std::complex<int>{1,1};
    const auto floatComplexScalar = std::complex<float>{1.1f,1.1f};
    const auto doubleComplexScalar = std::complex<double>{1.1,1.1};
    const auto longDoubleComplexScalar = std::complex<double>{1.1,1.12};

    {
        const auto res = complexDoubleVector - intScalar;
        ASSERT_NEAR(res[0].real(), 0.1, epsilon);   ASSERT_NEAR(res[0].imag(), 1.2, epsilon);
        ASSERT_NEAR(res[1].real(), 1.3, epsilon);   ASSERT_NEAR(res[1].imag(), 2.4, epsilon);
        ASSERT_NEAR(res[2].real(), 2.5, epsilon);   ASSERT_NEAR(res[2].imag(), 3.6, epsilon);

        const auto resFloat = complexDoubleVector - floatScalar;
        ASSERT_NEAR(resFloat[0].real(), 0.0, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 1.2, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 1.2, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 2.4, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 2.4, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 3.6, fepsilon);

        const auto resDouble = complexDoubleVector - doubleScalar;
        ASSERT_NEAR(resDouble[0].real(), 0.0, epsilon);   ASSERT_NEAR(resDouble[0].imag(), 1.2, epsilon);
        ASSERT_NEAR(resDouble[1].real(), 1.2, epsilon);   ASSERT_NEAR(resDouble[1].imag(), 2.4, epsilon);
        ASSERT_NEAR(resDouble[2].real(), 2.4, epsilon);   ASSERT_NEAR(resDouble[2].imag(), 3.6, epsilon);

        const auto resLongDouble = complexDoubleVector - longScalar;
        ASSERT_NEAR(resLongDouble[0].real(), -0.02, epsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 1.2, epsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 1.18, epsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 2.4, epsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 2.38, epsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 3.6, epsilon);
    }

    {
        const auto res = complexDoubleVector - intComplexScalar;
        ASSERT_NEAR(res[0].real(), 0.1, epsilon);   ASSERT_NEAR(res[0].imag(), 0.2f, fepsilon);
        ASSERT_NEAR(res[1].real(), 1.3, epsilon);   ASSERT_NEAR(res[1].imag(), 1.4f, fepsilon);
        ASSERT_NEAR(res[2].real(), 2.5, epsilon);   ASSERT_NEAR(res[2].imag(), 2.6f, fepsilon);


        const auto resFloat = complexDoubleVector - floatComplexScalar;
        ASSERT_NEAR(resFloat[0].real(), 0.0, fepsilon);   ASSERT_NEAR(resFloat[0].imag(), 0.1, fepsilon);
        ASSERT_NEAR(resFloat[1].real(), 1.2, fepsilon);   ASSERT_NEAR(resFloat[1].imag(), 1.3, fepsilon);
        ASSERT_NEAR(resFloat[2].real(), 2.4, fepsilon);   ASSERT_NEAR(resFloat[2].imag(), 2.5, fepsilon);

        const auto resDouble = complexDoubleVector - doubleComplexScalar;
        ASSERT_NEAR(resDouble[0].real(), 0.0, epsilon);   ASSERT_NEAR(resDouble[0].imag(), 0.1, epsilon);
        ASSERT_NEAR(resDouble[1].real(), 1.2, epsilon);   ASSERT_NEAR(resDouble[1].imag(), 1.3, epsilon);
        ASSERT_NEAR(resDouble[2].real(), 2.4, epsilon);   ASSERT_NEAR(resDouble[2].imag(), 2.5, epsilon);

        const auto resLongDouble = complexDoubleVector - longDoubleComplexScalar;
        ASSERT_NEAR(resLongDouble[0].real(), 0.0, epsilon);   ASSERT_NEAR(resLongDouble[0].imag(), 0.08, epsilon);
        ASSERT_NEAR(resLongDouble[1].real(), 1.2, epsilon);   ASSERT_NEAR(resLongDouble[1].imag(), 1.28, epsilon);
        ASSERT_NEAR(resLongDouble[2].real(), 2.4, epsilon);   ASSERT_NEAR(resLongDouble[2].imag(), 2.48, epsilon);
    }
}

TEST_F(VectorComplexBroadcastersTests, Subtraction_InPlace_Broadcaster)
{
    auto complexIntVector = Vector<std::complex<int>>({{1, 1},{2 ,2},{3, 3}});
    auto complexFloatVector = Vector<std::complex<float>>({{1.1f, 1.2f},{2.3f, 2.4f},{3.5f, 3.6f}});
    auto complexDoubleVector = Vector<std::complex<double>>({{1.1,1.2},{2.3,2.4},{3.5,3.6}});
    auto complexLongDoubleVector = Vector<std::complex<long double>>({{1.1,1.2},{2.3,2.4},{3.5,3.6}});

    const auto intComplexScalar = std::complex<int>{1,1};
    const auto floatComplexScalar = std::complex<float>{1.1f,1.1f};
    const auto doubleComplexScalar = std::complex<double>{1.1,1.1};
    const auto longDoubleComplexScalar = std::complex<double>{1.1,1.12};

    complexIntVector -= intComplexScalar;
    ASSERT_EQ(complexIntVector[0], std::complex<int>(0,0));
    ASSERT_EQ(complexIntVector[1], std::complex<int>(1,1));
    ASSERT_EQ(complexIntVector[2], std::complex<int>(2,2));

    complexFloatVector -= floatComplexScalar;
    ASSERT_NEAR(complexFloatVector[0].real(), 0.0f, fepsilon);   ASSERT_NEAR(complexFloatVector[0].imag(), 0.1f, fepsilon);
    ASSERT_NEAR(complexFloatVector[1].real(), 1.2f, fepsilon);   ASSERT_NEAR(complexFloatVector[1].imag(), 1.3f, fepsilon);
    ASSERT_NEAR(complexFloatVector[2].real(), 2.4f, fepsilon);   ASSERT_NEAR(complexFloatVector[2].imag(), 2.5f, fepsilon);

    complexDoubleVector -= doubleComplexScalar;
    ASSERT_NEAR(complexDoubleVector[0].real(), 0.0, epsilon);   ASSERT_NEAR(complexDoubleVector[0].imag(), 0.1, epsilon);
    ASSERT_NEAR(complexDoubleVector[1].real(), 1.2, epsilon);   ASSERT_NEAR(complexDoubleVector[1].imag(), 1.3, epsilon);
    ASSERT_NEAR(complexDoubleVector[2].real(), 2.4, epsilon);   ASSERT_NEAR(complexDoubleVector[2].imag(), 2.5, epsilon);

    complexLongDoubleVector -= longDoubleComplexScalar;
    ASSERT_NEAR(complexLongDoubleVector[0].real(), 0.0, epsilon);   ASSERT_NEAR(complexLongDoubleVector[0].imag(), 0.08, epsilon);
    ASSERT_NEAR(complexLongDoubleVector[1].real(), 1.2, epsilon);   ASSERT_NEAR(complexLongDoubleVector[1].imag(), 1.28, epsilon);
    ASSERT_NEAR(complexLongDoubleVector[2].real(), 2.4, epsilon);   ASSERT_NEAR(complexLongDoubleVector[2].imag(), 2.48, epsilon);
}
