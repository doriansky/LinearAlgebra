//
// Created by dorian on 31.01.2024.
//

#include "gtest/gtest.h"
#include "Matrix.hpp"

using namespace LinearAlgebra::Matrix;

class MatrixMultiplicationComplexTests : public ::testing::Test
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

TEST_F(MatrixMultiplicationComplexTests, IntMat_ComplexIntMat)
{
    const auto intMat = Matrix<int>({1,2,3,
                                     4,5,6,
                                     7,8,9},
                                    3, 3);
    const auto complexIntMat = Matrix<std::complex<int>>({{1,1}, {2,2}, {3,3},
                                                          {4,4}, {2,2}, {5,5},
                                                          {6,4}, {7,5}, {3,4}},
                                                                  3,3);

    const auto res = intMat * complexIntMat;
    ASSERT_EQ(res(0,0), std::complex<int>(27, 21)); ASSERT_EQ(res(0,1), std::complex<int>(27, 21)); ASSERT_EQ(res(0,2), std::complex<int>(22, 25));
    ASSERT_EQ(res(1,0), std::complex<int>(60, 48)); ASSERT_EQ(res(1,1), std::complex<int>(60, 48)); ASSERT_EQ(res(1,2), std::complex<int>(55, 61));
    ASSERT_EQ(res(2,0), std::complex<int>(93, 75)); ASSERT_EQ(res(2,1), std::complex<int>(93, 75)); ASSERT_EQ(res(2,2), std::complex<int>(88, 97));

    const auto res2 = complexIntMat * intMat;
    ASSERT_EQ(res2(0,0), std::complex<int>(30, 30)); ASSERT_EQ(res2(0,1), std::complex<int>(36, 36)); ASSERT_EQ(res2(0,2), std::complex<int>(42, 42));
    ASSERT_EQ(res2(1,0), std::complex<int>(47, 47)); ASSERT_EQ(res2(1,1), std::complex<int>(58, 58)); ASSERT_EQ(res2(1,2), std::complex<int>(69, 69));
    ASSERT_EQ(res2(2,0), std::complex<int>(55, 52)); ASSERT_EQ(res2(2,1), std::complex<int>(71, 65)); ASSERT_EQ(res2(2,2), std::complex<int>(87, 78));
}

TEST_F(MatrixMultiplicationComplexTests, IntMat_ComplexFloatMat)
{
    const auto intMat = Matrix<int>({1,2,3,
                                     4,5,6,
                                     7,8,9},
                                    3, 3);
    const auto complexFloatMat = Matrix<std::complex<float>>({{0.1f,1.1f}, {2.2f,0.2f}, {3.1f,0.3f},
                                                          {4.4f,4.2f}, {0.2f,2.1f}, {0.5f,5.1f},
                                                          {6.1f,0.4f}, {0.7f,5.1f}, {3.1f,0.4f}},
                                                         3,3);

    const auto res = intMat * complexFloatMat;
    ASSERT_NEAR(res(0,0).real(), 27.2f, fepsilon);  ASSERT_NEAR(res(0,0).imag(), 10.7f, fepsilon);
    ASSERT_NEAR(res(1,0).real(), 59.f, fepsilon);   ASSERT_NEAR(res(1,0).imag(), 27.8f, fepsilon);
    ASSERT_NEAR(res(2,0).real(), 90.8f, fepsilon);  ASSERT_NEAR(res(2,0).imag(), 44.9f, fepsilon);

    ASSERT_NEAR(res(0,1).real(), 4.7f, fepsilon);   ASSERT_NEAR(res(0,1).imag(), 19.7f, fepsilon);
    ASSERT_NEAR(res(1,1).real(), 14.f, fepsilon);   ASSERT_NEAR(res(1,1).imag(), 41.9f, fepsilon);
    ASSERT_NEAR(res(2,1).real(), 23.3f, fepsilon);  ASSERT_NEAR(res(2,1).imag(), 64.1f, fepsilon);

    ASSERT_NEAR(res(0,2).real(), 13.4f, fepsilon);  ASSERT_NEAR(res(0,2).imag(), 11.7f, fepsilon);
    ASSERT_NEAR(res(1,2).real(), 33.5f, fepsilon);  ASSERT_NEAR(res(1,2).imag(), 29.1f, fepsilon);
    ASSERT_NEAR(res(2,2).real(), 53.6f, fepsilon);  ASSERT_NEAR(res(2,2).imag(), 46.5f, fepsilon);

    const auto res2 = complexFloatMat * intMat;
    ASSERT_NEAR(res2(0,0).real(), 30.6f, fepsilon); ASSERT_NEAR(res2(0,0).imag(), 4.f, fepsilon);
    ASSERT_NEAR(res2(1,0).real(), 8.7f, fepsilon);  ASSERT_NEAR(res2(1,0).imag(), 48.3f, fepsilon);
    ASSERT_NEAR(res2(2,0).real(), 30.6f, fepsilon); ASSERT_NEAR(res2(2,0).imag(), 23.6f, fepsilon);

    ASSERT_NEAR(res2(0,1).real(), 36.f, fepsilon);  ASSERT_NEAR(res2(0,1).imag(), 5.6f, fepsilon);
    ASSERT_NEAR(res2(1,1).real(), 13.8f, fepsilon);  ASSERT_NEAR(res2(1,1).imag(), 59.7f, fepsilon);
    ASSERT_NEAR(res2(2,1).real(), 40.5f, fepsilon);  ASSERT_NEAR(res2(2,1).imag(), 29.5f, fepsilon);

    ASSERT_NEAR(res2(0,2).real(), 41.4f, fepsilon);  ASSERT_NEAR(res2(0,2).imag(), 7.2f, fepsilon);
    ASSERT_NEAR(res2(1,2).real(), 18.9f, fepsilon);  ASSERT_NEAR(res2(1,2).imag(), 71.1f, fepsilon);
    ASSERT_NEAR(res2(2,2).real(), 50.4f, fepsilon);  ASSERT_NEAR(res2(2,2).imag(), 35.4f, fepsilon);
}

TEST_F(MatrixMultiplicationComplexTests, IntMat_ComplexDoubletMat)
{
    const auto intMat = Matrix<int>({1,2,3,
                                     4,5,6,
                                     7,8,9},
                                    3, 3);
    const auto complexDoubleMat = Matrix<std::complex<double>>({{0.1,1.1}, {2.2,0.2}, {3.1,0.3},
                                                              {4.4,4.2}, {0.2,2.1}, {0.5,5.1},
                                                              {6.1,0.4}, {0.7,5.1}, {3.1,0.4}},
                                                             3,3);

    const auto res = intMat * complexDoubleMat;
    ASSERT_NEAR(res(0,0).real(), 27.2, epsilon);  ASSERT_NEAR(res(0,0).imag(), 10.7, epsilon);
    ASSERT_NEAR(res(1,0).real(), 59., epsilon);   ASSERT_NEAR(res(1,0).imag(), 27.8, epsilon);
    ASSERT_NEAR(res(2,0).real(), 90.8, epsilon);  ASSERT_NEAR(res(2,0).imag(), 44.9, epsilon);

    ASSERT_NEAR(res(0,1).real(), 4.7, epsilon);   ASSERT_NEAR(res(0,1).imag(), 19.7, epsilon);
    ASSERT_NEAR(res(1,1).real(), 14., epsilon);   ASSERT_NEAR(res(1,1).imag(), 41.9, epsilon);
    ASSERT_NEAR(res(2,1).real(), 23.3, epsilon);  ASSERT_NEAR(res(2,1).imag(), 64.1, epsilon);

    ASSERT_NEAR(res(0,2).real(), 13.4, epsilon);  ASSERT_NEAR(res(0,2).imag(), 11.7, epsilon);
    ASSERT_NEAR(res(1,2).real(), 33.5, epsilon);  ASSERT_NEAR(res(1,2).imag(), 29.1, epsilon);
    ASSERT_NEAR(res(2,2).real(), 53.6, epsilon);  ASSERT_NEAR(res(2,2).imag(), 46.5, epsilon);

    const auto res2 = complexDoubleMat * intMat;
    ASSERT_NEAR(res2(0,0).real(), 30.6, epsilon); ASSERT_NEAR(res2(0,0).imag(), 4., epsilon);
    ASSERT_NEAR(res2(1,0).real(), 8.7, epsilon);  ASSERT_NEAR(res2(1,0).imag(), 48.3, epsilon);
    ASSERT_NEAR(res2(2,0).real(), 30.6, epsilon); ASSERT_NEAR(res2(2,0).imag(), 23.6, epsilon);

    ASSERT_NEAR(res2(0,1).real(), 36., epsilon);  ASSERT_NEAR(res2(0,1).imag(), 5.6, epsilon);
    ASSERT_NEAR(res2(1,1).real(), 13.8, epsilon);  ASSERT_NEAR(res2(1,1).imag(), 59.7, epsilon);
    ASSERT_NEAR(res2(2,1).real(), 40.5, epsilon);  ASSERT_NEAR(res2(2,1).imag(), 29.5, epsilon);

    ASSERT_NEAR(res2(0,2).real(), 41.4, epsilon);  ASSERT_NEAR(res2(0,2).imag(), 7.2, epsilon);
    ASSERT_NEAR(res2(1,2).real(), 18.9, epsilon);  ASSERT_NEAR(res2(1,2).imag(), 71.1, epsilon);
    ASSERT_NEAR(res2(2,2).real(), 50.4, epsilon);  ASSERT_NEAR(res2(2,2).imag(), 35.4, epsilon);
}

TEST_F(MatrixMultiplicationComplexTests, IntMat_ComplexLongDoubletMat)
{
    const auto intMat = Matrix<int>({1,2,3,
                                     4,5,6,
                                     7,8,9},
                                    3, 3);
    const auto complexDoubleMat = Matrix<std::complex<long double>>({{0.1,1.1}, {2.2,0.2}, {3.1,0.3},
                                                                {4.4,4.2}, {0.2,2.1}, {0.5,5.1},
                                                                {6.1,0.4}, {0.7,5.1}, {3.1,0.4}},
                                                               3,3);

    const auto res = intMat * complexDoubleMat;
    ASSERT_NEAR(res(0,0).real(), 27.2, epsilon);  ASSERT_NEAR(res(0,0).imag(), 10.7, epsilon);
    ASSERT_NEAR(res(1,0).real(), 59., epsilon);   ASSERT_NEAR(res(1,0).imag(), 27.8, epsilon);
    ASSERT_NEAR(res(2,0).real(), 90.8, epsilon);  ASSERT_NEAR(res(2,0).imag(), 44.9, epsilon);

    ASSERT_NEAR(res(0,1).real(), 4.7, epsilon);   ASSERT_NEAR(res(0,1).imag(), 19.7, epsilon);
    ASSERT_NEAR(res(1,1).real(), 14., epsilon);   ASSERT_NEAR(res(1,1).imag(), 41.9, epsilon);
    ASSERT_NEAR(res(2,1).real(), 23.3, epsilon);  ASSERT_NEAR(res(2,1).imag(), 64.1, epsilon);

    ASSERT_NEAR(res(0,2).real(), 13.4, epsilon);  ASSERT_NEAR(res(0,2).imag(), 11.7, epsilon);
    ASSERT_NEAR(res(1,2).real(), 33.5, epsilon);  ASSERT_NEAR(res(1,2).imag(), 29.1, epsilon);
    ASSERT_NEAR(res(2,2).real(), 53.6, epsilon);  ASSERT_NEAR(res(2,2).imag(), 46.5, epsilon);

    const auto res2 = complexDoubleMat * intMat;
    ASSERT_NEAR(res2(0,0).real(), 30.6, epsilon); ASSERT_NEAR(res2(0,0).imag(), 4., epsilon);
    ASSERT_NEAR(res2(1,0).real(), 8.7, epsilon);  ASSERT_NEAR(res2(1,0).imag(), 48.3, epsilon);
    ASSERT_NEAR(res2(2,0).real(), 30.6, epsilon); ASSERT_NEAR(res2(2,0).imag(), 23.6, epsilon);

    ASSERT_NEAR(res2(0,1).real(), 36., epsilon);  ASSERT_NEAR(res2(0,1).imag(), 5.6, epsilon);
    ASSERT_NEAR(res2(1,1).real(), 13.8, epsilon);  ASSERT_NEAR(res2(1,1).imag(), 59.7, epsilon);
    ASSERT_NEAR(res2(2,1).real(), 40.5, epsilon);  ASSERT_NEAR(res2(2,1).imag(), 29.5, epsilon);

    ASSERT_NEAR(res2(0,2).real(), 41.4, epsilon);  ASSERT_NEAR(res2(0,2).imag(), 7.2, epsilon);
    ASSERT_NEAR(res2(1,2).real(), 18.9, epsilon);  ASSERT_NEAR(res2(1,2).imag(), 71.1, epsilon);
    ASSERT_NEAR(res2(2,2).real(), 50.4, epsilon);  ASSERT_NEAR(res2(2,2).imag(), 35.4, epsilon);
}

TEST_F(MatrixMultiplicationComplexTests, FloatMat_ComplexIntMat)
{
    const auto floatMat = Matrix<float>({1.1f,2.2f,
                                         4.4f,5.5f,
                                         7.7f,8.3f},
                                        3, 2);

    const auto complexIntMat = Matrix<std::complex<int>>({{1,1}, {2,2}, {5,3},
                                                          {4,4}, {2,2}, {5,5}},
                                                         2,3);

    const auto res = floatMat * complexIntMat;
    ASSERT_NEAR(res(0,0).real(), 9.9f, fepsilon);  ASSERT_NEAR(res(0,0).imag(), 9.9f, fepsilon);
    ASSERT_NEAR(res(1,0).real(), 26.4f, fepsilon);   ASSERT_NEAR(res(1,0).imag(), 26.4f, fepsilon);
    ASSERT_NEAR(res(2,0).real(), 40.9f, fepsilon);  ASSERT_NEAR(res(2,0).imag(), 40.9f, fepsilon);

    ASSERT_NEAR(res(0,1).real(), 6.6f, fepsilon);   ASSERT_NEAR(res(0,1).imag(), 6.6f, fepsilon);
    ASSERT_NEAR(res(1,1).real(), 19.8f, fepsilon);   ASSERT_NEAR(res(1,1).imag(), 19.8f, fepsilon);
    ASSERT_NEAR(res(2,1).real(), 32.0f, fepsilon);  ASSERT_NEAR(res(2,1).imag(), 32.0f, fepsilon);

    ASSERT_NEAR(res(0,2).real(), 16.5f, fepsilon);  ASSERT_NEAR(res(0,2).imag(), 14.3f, fepsilon);
    ASSERT_NEAR(res(1,2).real(), 49.5f, fepsilon);  ASSERT_NEAR(res(1,2).imag(), 40.7f, fepsilon);
    ASSERT_NEAR(res(2,2).real(), 80.0f, fepsilon);  ASSERT_NEAR(res(2,2).imag(), 64.6f, fepsilon);

    const auto res2 = complexIntMat * floatMat;
    ASSERT_NEAR(res2(0,0).real(), 48.4f, fepsilon);  ASSERT_NEAR(res2(0,0).imag(), 33.f, fepsilon);
    ASSERT_NEAR(res2(1,0).real(), 51.7f, fepsilon);   ASSERT_NEAR(res2(1,0).imag(), 51.7f, fepsilon);

    ASSERT_NEAR(res2(0,1).real(), 54.7f, fepsilon);   ASSERT_NEAR(res2(0,1).imag(), 38.1f, fepsilon);
    ASSERT_NEAR(res2(1,1).real(), 61.3f, fepsilon);   ASSERT_NEAR(res2(1,1).imag(), 61.3f, fepsilon);
}

TEST_F(MatrixMultiplicationComplexTests, FloatMat_ComplexFloatMat)
{
    const auto floatMat = Matrix<float>({1.1f,2.2f,
                                         4.4f,5.5f,
                                         7.7f,8.3f},
                                        3, 2);

    const auto complexFloatMat = Matrix<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {5.2f,3.0f},
                                                          {4.1f,4.2f}, {2.4f,2.5f}, {5.1f,5.3f}},
                                                         2,3);

    const auto res = floatMat * complexFloatMat;
    ASSERT_NEAR(res(0,0).real(), 10.23f, fepsilon);  ASSERT_NEAR(res(0,0).imag(), 10.45f, fepsilon);
    ASSERT_NEAR(res(1,0).real(), 27.39f, fepsilon);   ASSERT_NEAR(res(1,0).imag(), 27.94f, fepsilon);
    ASSERT_NEAR(res(2,0).real(), 42.5f, fepsilon);  ASSERT_NEAR(res(2,0).imag(), 43.33f, fepsilon);

    ASSERT_NEAR(res(0,1).real(), 7.7f, fepsilon);   ASSERT_NEAR(res(0,1).imag(), 7.92f, fepsilon);
    ASSERT_NEAR(res(1,1).real(), 22.88f, fepsilon);   ASSERT_NEAR(res(1,1).imag(), 23.43f, fepsilon);
    ASSERT_NEAR(res(2,1).real(), 36.86f, fepsilon);  ASSERT_NEAR(res(2,1).imag(), 37.69f, fepsilon);

    ASSERT_NEAR(res(0,2).real(), 16.94f, fepsilon);  ASSERT_NEAR(res(0,2).imag(), 14.96f, fepsilon);
    ASSERT_NEAR(res(1,2).real(), 50.93f, fepsilon);  ASSERT_NEAR(res(1,2).imag(), 42.35f, fepsilon);
    ASSERT_NEAR(res(2,2).real(), 82.37f, fepsilon);  ASSERT_NEAR(res(2,2).imag(), 67.09f, fepsilon);

    const auto res2 = complexFloatMat * floatMat;
    ASSERT_NEAR(res2(0,0).real(), 50.93f, fepsilon);  ASSERT_NEAR(res2(0,0).imag(), 33.99f, fepsilon);
    ASSERT_NEAR(res2(1,0).real(), 54.34f, fepsilon);   ASSERT_NEAR(res2(1,0).imag(), 56.43f, fepsilon);

    ASSERT_NEAR(res2(0,1).real(), 57.68f, fepsilon);   ASSERT_NEAR(res2(0,1).imag(), 39.42f, fepsilon);
    ASSERT_NEAR(res2(1,1).real(), 64.55f, fepsilon);   ASSERT_NEAR(res2(1,1).imag(), 66.98f, fepsilon);
}

TEST_F(MatrixMultiplicationComplexTests, FloatMat_ComplexDoubleMat)
{
    const auto floatMat = Matrix<float>({1.1f,2.2f,
                                         4.4f,5.5f,
                                         7.7f,8.3f},
                                        3, 2);

    const auto complexDoubleMat = Matrix<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {5.2,3.0},
                                                              {4.1,4.2}, {2.4,2.5}, {5.1,5.3}},
                                                             2,3);

    const auto res = floatMat * complexDoubleMat;
    ASSERT_NEAR(res(0,0).real(), 10.23, fepsilon);  ASSERT_NEAR(res(0,0).imag(), 10.45, fepsilon);
    ASSERT_NEAR(res(1,0).real(), 27.39, fepsilon);   ASSERT_NEAR(res(1,0).imag(), 27.94, fepsilon);
    ASSERT_NEAR(res(2,0).real(), 42.5, fepsilon);  ASSERT_NEAR(res(2,0).imag(), 43.33, fepsilon);

    ASSERT_NEAR(res(0,1).real(), 7.7, fepsilon);   ASSERT_NEAR(res(0,1).imag(), 7.92, fepsilon);
    ASSERT_NEAR(res(1,1).real(), 22.88, fepsilon);   ASSERT_NEAR(res(1,1).imag(), 23.43, fepsilon);
    ASSERT_NEAR(res(2,1).real(), 36.86, fepsilon);  ASSERT_NEAR(res(2,1).imag(), 37.69, fepsilon);

    ASSERT_NEAR(res(0,2).real(), 16.94, fepsilon);  ASSERT_NEAR(res(0,2).imag(), 14.96, fepsilon);
    ASSERT_NEAR(res(1,2).real(), 50.93, fepsilon);  ASSERT_NEAR(res(1,2).imag(), 42.35, fepsilon);
    ASSERT_NEAR(res(2,2).real(), 82.37, fepsilon);  ASSERT_NEAR(res(2,2).imag(), 67.09, fepsilon);

    const auto res2 = complexDoubleMat * floatMat;
    ASSERT_NEAR(res2(0,0).real(), 50.93, fepsilon);  ASSERT_NEAR(res2(0,0).imag(), 33.99, fepsilon);
    ASSERT_NEAR(res2(1,0).real(), 54.34, fepsilon);   ASSERT_NEAR(res2(1,0).imag(), 56.43, fepsilon);

    ASSERT_NEAR(res2(0,1).real(), 57.68, fepsilon);   ASSERT_NEAR(res2(0,1).imag(), 39.42, fepsilon);
    ASSERT_NEAR(res2(1,1).real(), 64.55, fepsilon);   ASSERT_NEAR(res2(1,1).imag(), 66.98, fepsilon);
}

TEST_F(MatrixMultiplicationComplexTests, FloatMat_ComplexLongDoubleMat)
{
    const auto floatMat = Matrix<float>({1.1f,2.2f,
                                         4.4f,5.5f,
                                         7.7f,8.3f},
                                        3, 2);

    const auto complexDoubleMat = Matrix<std::complex<long double>>({{1.1,1.1}, {2.2,2.2}, {5.2,3.0},
                                                                {4.1,4.2}, {2.4,2.5}, {5.1,5.3}},
                                                               2,3);

    const auto res = floatMat * complexDoubleMat;
    ASSERT_NEAR(res(0,0).real(), 10.23, fepsilon);  ASSERT_NEAR(res(0,0).imag(), 10.45, fepsilon);
    ASSERT_NEAR(res(1,0).real(), 27.39, fepsilon);   ASSERT_NEAR(res(1,0).imag(), 27.94, fepsilon);
    ASSERT_NEAR(res(2,0).real(), 42.5, fepsilon);  ASSERT_NEAR(res(2,0).imag(), 43.33, fepsilon);

    ASSERT_NEAR(res(0,1).real(), 7.7, fepsilon);   ASSERT_NEAR(res(0,1).imag(), 7.92, fepsilon);
    ASSERT_NEAR(res(1,1).real(), 22.88, fepsilon);   ASSERT_NEAR(res(1,1).imag(), 23.43, fepsilon);
    ASSERT_NEAR(res(2,1).real(), 36.86, fepsilon);  ASSERT_NEAR(res(2,1).imag(), 37.69, fepsilon);

    ASSERT_NEAR(res(0,2).real(), 16.94, fepsilon);  ASSERT_NEAR(res(0,2).imag(), 14.96, fepsilon);
    ASSERT_NEAR(res(1,2).real(), 50.93, fepsilon);  ASSERT_NEAR(res(1,2).imag(), 42.35, fepsilon);
    ASSERT_NEAR(res(2,2).real(), 82.37, fepsilon);  ASSERT_NEAR(res(2,2).imag(), 67.09, fepsilon);

    const auto res2 = complexDoubleMat * floatMat;
    ASSERT_NEAR(res2(0,0).real(), 50.93, fepsilon);  ASSERT_NEAR(res2(0,0).imag(), 33.99, fepsilon);
    ASSERT_NEAR(res2(1,0).real(), 54.34, fepsilon);   ASSERT_NEAR(res2(1,0).imag(), 56.43, fepsilon);

    ASSERT_NEAR(res2(0,1).real(), 57.68, fepsilon);   ASSERT_NEAR(res2(0,1).imag(), 39.42, fepsilon);
    ASSERT_NEAR(res2(1,1).real(), 64.55, fepsilon);   ASSERT_NEAR(res2(1,1).imag(), 66.98, fepsilon);
}

TEST_F(MatrixMultiplicationComplexTests, DoubletMat_ComplexIntMat)
{
    const auto doubleMat = Matrix<double>({1.1,2.2,
                                         4.4,5.5,
                                         7.7,8.3},
                                        3, 2);

    const auto complexIntMat = Matrix<std::complex<int>>({{1,1}, {2,2}, {5,3},
                                                          {4,4}, {2,2}, {5,5}},
                                                         2,3);

    const auto res = doubleMat * complexIntMat;
    ASSERT_NEAR(res(0,0).real(), 9.9, epsilon);  ASSERT_NEAR(res(0,0).imag(), 9.9, epsilon);
    ASSERT_NEAR(res(1,0).real(), 26.4, epsilon);   ASSERT_NEAR(res(1,0).imag(), 26.4, epsilon);
    ASSERT_NEAR(res(2,0).real(), 40.9, epsilon);  ASSERT_NEAR(res(2,0).imag(), 40.9, epsilon);

    ASSERT_NEAR(res(0,1).real(), 6.6, epsilon);   ASSERT_NEAR(res(0,1).imag(), 6.6, epsilon);
    ASSERT_NEAR(res(1,1).real(), 19.8, epsilon);   ASSERT_NEAR(res(1,1).imag(), 19.8, epsilon);
    ASSERT_NEAR(res(2,1).real(), 32.0, epsilon);  ASSERT_NEAR(res(2,1).imag(), 32.0, epsilon);

    ASSERT_NEAR(res(0,2).real(), 16.5, epsilon);  ASSERT_NEAR(res(0,2).imag(), 14.3, epsilon);
    ASSERT_NEAR(res(1,2).real(), 49.5, epsilon);  ASSERT_NEAR(res(1,2).imag(), 40.7, epsilon);
    ASSERT_NEAR(res(2,2).real(), 80.0, epsilon);  ASSERT_NEAR(res(2,2).imag(), 64.6, epsilon);

    const auto res2 = complexIntMat * doubleMat;
    ASSERT_NEAR(res2(0,0).real(), 48.4, epsilon);  ASSERT_NEAR(res2(0,0).imag(), 33., epsilon);
    ASSERT_NEAR(res2(1,0).real(), 51.7, epsilon);   ASSERT_NEAR(res2(1,0).imag(), 51.7, epsilon);

    ASSERT_NEAR(res2(0,1).real(), 54.7, epsilon);   ASSERT_NEAR(res2(0,1).imag(), 38.1, epsilon);
    ASSERT_NEAR(res2(1,1).real(), 61.3, epsilon);   ASSERT_NEAR(res2(1,1).imag(), 61.3, epsilon);
}

TEST_F(MatrixMultiplicationComplexTests, DoubleMat_ComplexFloatMat)
{
    const auto doubleMat = Matrix<double>({1.1,2.2,
                                           4.4,5.5,
                                           7.7,8.3},
                                          3, 2);

    const auto complexFloatMat = Matrix<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {5.2f,3.0f},
                                                              {4.1f,4.2f}, {2.4f,2.5f}, {5.1f,5.3f}},
                                                             2,3);

    const auto res = doubleMat * complexFloatMat;
    ASSERT_NEAR(res(0,0).real(), 10.23, fepsilon);  ASSERT_NEAR(res(0,0).imag(), 10.45, fepsilon);
    ASSERT_NEAR(res(1,0).real(), 27.39, fepsilon);   ASSERT_NEAR(res(1,0).imag(), 27.94, fepsilon);
    ASSERT_NEAR(res(2,0).real(), 42.5, fepsilon);  ASSERT_NEAR(res(2,0).imag(), 43.33, fepsilon);

    ASSERT_NEAR(res(0,1).real(), 7.7, fepsilon);   ASSERT_NEAR(res(0,1).imag(), 7.92, fepsilon);
    ASSERT_NEAR(res(1,1).real(), 22.88, fepsilon);   ASSERT_NEAR(res(1,1).imag(), 23.43, fepsilon);
    ASSERT_NEAR(res(2,1).real(), 36.86, fepsilon);  ASSERT_NEAR(res(2,1).imag(), 37.69, fepsilon);

    ASSERT_NEAR(res(0,2).real(), 16.94, fepsilon);  ASSERT_NEAR(res(0,2).imag(), 14.96, fepsilon);
    ASSERT_NEAR(res(1,2).real(), 50.93, fepsilon);  ASSERT_NEAR(res(1,2).imag(), 42.35, fepsilon);
    ASSERT_NEAR(res(2,2).real(), 82.37, fepsilon);  ASSERT_NEAR(res(2,2).imag(), 67.09, fepsilon);

    const auto res2 = complexFloatMat * doubleMat;
    ASSERT_NEAR(res2(0,0).real(), 50.93, fepsilon);  ASSERT_NEAR(res2(0,0).imag(), 33.99, fepsilon);
    ASSERT_NEAR(res2(1,0).real(), 54.34, fepsilon);   ASSERT_NEAR(res2(1,0).imag(), 56.43, fepsilon);

    ASSERT_NEAR(res2(0,1).real(), 57.68, fepsilon);   ASSERT_NEAR(res2(0,1).imag(), 39.42, fepsilon);
    ASSERT_NEAR(res2(1,1).real(), 64.55, fepsilon);   ASSERT_NEAR(res2(1,1).imag(), 66.98, fepsilon);
}

TEST_F(MatrixMultiplicationComplexTests, DoubletMat_ComplexDoubleMat)
{
    const auto doubleMat = Matrix<double>({1.1,2.2,
                                           4.4,5.5,
                                           7.7,8.3},
                                          3, 2);

    const auto complexDoubleMat = Matrix<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {5.2,3.0},
                                                                {4.1,4.2}, {2.4,2.5}, {5.1,5.3}},
                                                               2,3);

    const auto res = doubleMat * complexDoubleMat;
    ASSERT_NEAR(res(0,0).real(), 10.23, epsilon);  ASSERT_NEAR(res(0,0).imag(), 10.45, epsilon);
    ASSERT_NEAR(res(1,0).real(), 27.39, epsilon);   ASSERT_NEAR(res(1,0).imag(), 27.94, epsilon);
    ASSERT_NEAR(res(2,0).real(), 42.5, epsilon);  ASSERT_NEAR(res(2,0).imag(), 43.33, epsilon);

    ASSERT_NEAR(res(0,1).real(), 7.7, epsilon);   ASSERT_NEAR(res(0,1).imag(), 7.92, epsilon);
    ASSERT_NEAR(res(1,1).real(), 22.88, epsilon);   ASSERT_NEAR(res(1,1).imag(), 23.43, epsilon);
    ASSERT_NEAR(res(2,1).real(), 36.86, epsilon);  ASSERT_NEAR(res(2,1).imag(), 37.69, epsilon);

    ASSERT_NEAR(res(0,2).real(), 16.94, epsilon);  ASSERT_NEAR(res(0,2).imag(), 14.96, epsilon);
    ASSERT_NEAR(res(1,2).real(), 50.93, epsilon);  ASSERT_NEAR(res(1,2).imag(), 42.35, epsilon);
    ASSERT_NEAR(res(2,2).real(), 82.37, epsilon);  ASSERT_NEAR(res(2,2).imag(), 67.09, epsilon);

    const auto res2 = complexDoubleMat * doubleMat;
    ASSERT_NEAR(res2(0,0).real(), 50.93, epsilon);  ASSERT_NEAR(res2(0,0).imag(), 33.99, epsilon);
    ASSERT_NEAR(res2(1,0).real(), 54.34, epsilon);   ASSERT_NEAR(res2(1,0).imag(), 56.43, epsilon);

    ASSERT_NEAR(res2(0,1).real(), 57.68, epsilon);   ASSERT_NEAR(res2(0,1).imag(), 39.42, epsilon);
    ASSERT_NEAR(res2(1,1).real(), 64.55, epsilon);   ASSERT_NEAR(res2(1,1).imag(), 66.98, epsilon);
}

TEST_F(MatrixMultiplicationComplexTests, DoubleMat_ComplexLongDoubleMat)
{
    const auto doubleMat = Matrix<double>({1.1,2.2,
                                           4.4,5.5,
                                           7.7,8.3},
                                          3, 2);

    const auto complexDoubleMat = Matrix<std::complex<long double>>({{1.1,1.1}, {2.2,2.2}, {5.2,3.0},
                                                                {4.1,4.2}, {2.4,2.5}, {5.1,5.3}},
                                                               2,3);

    const auto res = doubleMat * complexDoubleMat;
    ASSERT_NEAR(res(0,0).real(), 10.23, epsilon);  ASSERT_NEAR(res(0,0).imag(), 10.45, epsilon);
    ASSERT_NEAR(res(1,0).real(), 27.39, epsilon);   ASSERT_NEAR(res(1,0).imag(), 27.94, epsilon);
    ASSERT_NEAR(res(2,0).real(), 42.5, epsilon);  ASSERT_NEAR(res(2,0).imag(), 43.33, epsilon);

    ASSERT_NEAR(res(0,1).real(), 7.7, epsilon);   ASSERT_NEAR(res(0,1).imag(), 7.92, epsilon);
    ASSERT_NEAR(res(1,1).real(), 22.88, epsilon);   ASSERT_NEAR(res(1,1).imag(), 23.43, epsilon);
    ASSERT_NEAR(res(2,1).real(), 36.86, epsilon);  ASSERT_NEAR(res(2,1).imag(), 37.69, epsilon);

    ASSERT_NEAR(res(0,2).real(), 16.94, epsilon);  ASSERT_NEAR(res(0,2).imag(), 14.96, epsilon);
    ASSERT_NEAR(res(1,2).real(), 50.93, epsilon);  ASSERT_NEAR(res(1,2).imag(), 42.35, epsilon);
    ASSERT_NEAR(res(2,2).real(), 82.37, epsilon);  ASSERT_NEAR(res(2,2).imag(), 67.09, epsilon);

    const auto res2 = complexDoubleMat * doubleMat;
    ASSERT_NEAR(res2(0,0).real(), 50.93, epsilon);  ASSERT_NEAR(res2(0,0).imag(), 33.99, epsilon);
    ASSERT_NEAR(res2(1,0).real(), 54.34, epsilon);   ASSERT_NEAR(res2(1,0).imag(), 56.43, epsilon);

    ASSERT_NEAR(res2(0,1).real(), 57.68, epsilon);   ASSERT_NEAR(res2(0,1).imag(), 39.42, epsilon);
    ASSERT_NEAR(res2(1,1).real(), 64.55, epsilon);   ASSERT_NEAR(res2(1,1).imag(), 66.98, epsilon);
}

TEST_F(MatrixMultiplicationComplexTests, LongDoubletMat_ComplexIntMat)
{
    const auto doubleMat = Matrix<long double>({1.1,2.2,
                                           4.4,5.5,
                                           7.7,8.3},
                                          3, 2);

    const auto complexIntMat = Matrix<std::complex<int>>({{1,1}, {2,2}, {5,3},
                                                          {4,4}, {2,2}, {5,5}},
                                                         2,3);

    const auto res = doubleMat * complexIntMat;
    ASSERT_NEAR(res(0,0).real(), 9.9, epsilon);  ASSERT_NEAR(res(0,0).imag(), 9.9, epsilon);
    ASSERT_NEAR(res(1,0).real(), 26.4, epsilon);   ASSERT_NEAR(res(1,0).imag(), 26.4, epsilon);
    ASSERT_NEAR(res(2,0).real(), 40.9, epsilon);  ASSERT_NEAR(res(2,0).imag(), 40.9, epsilon);

    ASSERT_NEAR(res(0,1).real(), 6.6, epsilon);   ASSERT_NEAR(res(0,1).imag(), 6.6, epsilon);
    ASSERT_NEAR(res(1,1).real(), 19.8, epsilon);   ASSERT_NEAR(res(1,1).imag(), 19.8, epsilon);
    ASSERT_NEAR(res(2,1).real(), 32.0, epsilon);  ASSERT_NEAR(res(2,1).imag(), 32.0, epsilon);

    ASSERT_NEAR(res(0,2).real(), 16.5, epsilon);  ASSERT_NEAR(res(0,2).imag(), 14.3, epsilon);
    ASSERT_NEAR(res(1,2).real(), 49.5, epsilon);  ASSERT_NEAR(res(1,2).imag(), 40.7, epsilon);
    ASSERT_NEAR(res(2,2).real(), 80.0, epsilon);  ASSERT_NEAR(res(2,2).imag(), 64.6, epsilon);

    const auto res2 = complexIntMat * doubleMat;
    ASSERT_NEAR(res2(0,0).real(), 48.4, epsilon);  ASSERT_NEAR(res2(0,0).imag(), 33., epsilon);
    ASSERT_NEAR(res2(1,0).real(), 51.7, epsilon);   ASSERT_NEAR(res2(1,0).imag(), 51.7, epsilon);

    ASSERT_NEAR(res2(0,1).real(), 54.7, epsilon);   ASSERT_NEAR(res2(0,1).imag(), 38.1, epsilon);
    ASSERT_NEAR(res2(1,1).real(), 61.3, epsilon);   ASSERT_NEAR(res2(1,1).imag(), 61.3, epsilon);
}

TEST_F(MatrixMultiplicationComplexTests, LongDoubleMat_ComplexFloatMat)
{
    const auto doubleMat = Matrix<long double>({1.1,2.2,
                                           4.4,5.5,
                                           7.7,8.3},
                                          3, 2);

    const auto complexFloatMat = Matrix<std::complex<float>>({{1.1f,1.1f}, {2.2f,2.2f}, {5.2f,3.0f},
                                                              {4.1f,4.2f}, {2.4f,2.5f}, {5.1f,5.3f}},
                                                             2,3);

    const auto res = doubleMat * complexFloatMat;
    ASSERT_NEAR(res(0,0).real(), 10.23, fepsilon);  ASSERT_NEAR(res(0,0).imag(), 10.45, fepsilon);
    ASSERT_NEAR(res(1,0).real(), 27.39, fepsilon);   ASSERT_NEAR(res(1,0).imag(), 27.94, fepsilon);
    ASSERT_NEAR(res(2,0).real(), 42.5, fepsilon);  ASSERT_NEAR(res(2,0).imag(), 43.33, fepsilon);

    ASSERT_NEAR(res(0,1).real(), 7.7, fepsilon);   ASSERT_NEAR(res(0,1).imag(), 7.92, fepsilon);
    ASSERT_NEAR(res(1,1).real(), 22.88, fepsilon);   ASSERT_NEAR(res(1,1).imag(), 23.43, fepsilon);
    ASSERT_NEAR(res(2,1).real(), 36.86, fepsilon);  ASSERT_NEAR(res(2,1).imag(), 37.69, fepsilon);

    ASSERT_NEAR(res(0,2).real(), 16.94, fepsilon);  ASSERT_NEAR(res(0,2).imag(), 14.96, fepsilon);
    ASSERT_NEAR(res(1,2).real(), 50.93, fepsilon);  ASSERT_NEAR(res(1,2).imag(), 42.35, fepsilon);
    ASSERT_NEAR(res(2,2).real(), 82.37, fepsilon);  ASSERT_NEAR(res(2,2).imag(), 67.09, fepsilon);

    const auto res2 = complexFloatMat * doubleMat;
    ASSERT_NEAR(res2(0,0).real(), 50.93, fepsilon);  ASSERT_NEAR(res2(0,0).imag(), 33.99, fepsilon);
    ASSERT_NEAR(res2(1,0).real(), 54.34, fepsilon);   ASSERT_NEAR(res2(1,0).imag(), 56.43, fepsilon);

    ASSERT_NEAR(res2(0,1).real(), 57.68, fepsilon);   ASSERT_NEAR(res2(0,1).imag(), 39.42, fepsilon);
    ASSERT_NEAR(res2(1,1).real(), 64.55, fepsilon);   ASSERT_NEAR(res2(1,1).imag(), 66.98, fepsilon);
}

TEST_F(MatrixMultiplicationComplexTests, LongDoubletMat_ComplexDoubleMat)
{
    const auto doubleMat = Matrix<long double>({1.1,2.2,
                                           4.4,5.5,
                                           7.7,8.3},
                                          3, 2);

    const auto complexDoubleMat = Matrix<std::complex<double>>({{1.1,1.1}, {2.2,2.2}, {5.2,3.0},
                                                                {4.1,4.2}, {2.4,2.5}, {5.1,5.3}},
                                                               2,3);

    const auto res = doubleMat * complexDoubleMat;
    ASSERT_NEAR(res(0,0).real(), 10.23, epsilon);  ASSERT_NEAR(res(0,0).imag(), 10.45, epsilon);
    ASSERT_NEAR(res(1,0).real(), 27.39, epsilon);   ASSERT_NEAR(res(1,0).imag(), 27.94, epsilon);
    ASSERT_NEAR(res(2,0).real(), 42.5, epsilon);  ASSERT_NEAR(res(2,0).imag(), 43.33, epsilon);

    ASSERT_NEAR(res(0,1).real(), 7.7, epsilon);   ASSERT_NEAR(res(0,1).imag(), 7.92, epsilon);
    ASSERT_NEAR(res(1,1).real(), 22.88, epsilon);   ASSERT_NEAR(res(1,1).imag(), 23.43, epsilon);
    ASSERT_NEAR(res(2,1).real(), 36.86, epsilon);  ASSERT_NEAR(res(2,1).imag(), 37.69, epsilon);

    ASSERT_NEAR(res(0,2).real(), 16.94, epsilon);  ASSERT_NEAR(res(0,2).imag(), 14.96, epsilon);
    ASSERT_NEAR(res(1,2).real(), 50.93, epsilon);  ASSERT_NEAR(res(1,2).imag(), 42.35, epsilon);
    ASSERT_NEAR(res(2,2).real(), 82.37, epsilon);  ASSERT_NEAR(res(2,2).imag(), 67.09, epsilon);

    const auto res2 = complexDoubleMat * doubleMat;
    ASSERT_NEAR(res2(0,0).real(), 50.93, epsilon);  ASSERT_NEAR(res2(0,0).imag(), 33.99, epsilon);
    ASSERT_NEAR(res2(1,0).real(), 54.34, epsilon);   ASSERT_NEAR(res2(1,0).imag(), 56.43, epsilon);

    ASSERT_NEAR(res2(0,1).real(), 57.68, epsilon);   ASSERT_NEAR(res2(0,1).imag(), 39.42, epsilon);
    ASSERT_NEAR(res2(1,1).real(), 64.55, epsilon);   ASSERT_NEAR(res2(1,1).imag(), 66.98, epsilon);
}

TEST_F(MatrixMultiplicationComplexTests, LongDoubleMat_ComplexLongDoubleMat)
{
    const auto doubleMat = Matrix<long double>({1.1,2.2,
                                           4.4,5.5,
                                           7.7,8.3},
                                          3, 2);

    const auto complexDoubleMat = Matrix<std::complex<long double>>({{1.1,1.1}, {2.2,2.2}, {5.2,3.0},
                                                                     {4.1,4.2}, {2.4,2.5}, {5.1,5.3}},
                                                                    2,3);

    const auto res = doubleMat * complexDoubleMat;
    ASSERT_NEAR(res(0,0).real(), 10.23, epsilon);  ASSERT_NEAR(res(0,0).imag(), 10.45, epsilon);
    ASSERT_NEAR(res(1,0).real(), 27.39, epsilon);   ASSERT_NEAR(res(1,0).imag(), 27.94, epsilon);
    ASSERT_NEAR(res(2,0).real(), 42.5, epsilon);  ASSERT_NEAR(res(2,0).imag(), 43.33, epsilon);

    ASSERT_NEAR(res(0,1).real(), 7.7, epsilon);   ASSERT_NEAR(res(0,1).imag(), 7.92, epsilon);
    ASSERT_NEAR(res(1,1).real(), 22.88, epsilon);   ASSERT_NEAR(res(1,1).imag(), 23.43, epsilon);
    ASSERT_NEAR(res(2,1).real(), 36.86, epsilon);  ASSERT_NEAR(res(2,1).imag(), 37.69, epsilon);

    ASSERT_NEAR(res(0,2).real(), 16.94, epsilon);  ASSERT_NEAR(res(0,2).imag(), 14.96, epsilon);
    ASSERT_NEAR(res(1,2).real(), 50.93, epsilon);  ASSERT_NEAR(res(1,2).imag(), 42.35, epsilon);
    ASSERT_NEAR(res(2,2).real(), 82.37, epsilon);  ASSERT_NEAR(res(2,2).imag(), 67.09, epsilon);

    const auto res2 = complexDoubleMat * doubleMat;
    ASSERT_NEAR(res2(0,0).real(), 50.93, epsilon);  ASSERT_NEAR(res2(0,0).imag(), 33.99, epsilon);
    ASSERT_NEAR(res2(1,0).real(), 54.34, epsilon);   ASSERT_NEAR(res2(1,0).imag(), 56.43, epsilon);

    ASSERT_NEAR(res2(0,1).real(), 57.68, epsilon);   ASSERT_NEAR(res2(0,1).imag(), 39.42, epsilon);
    ASSERT_NEAR(res2(1,1).real(), 64.55, epsilon);   ASSERT_NEAR(res2(1,1).imag(), 66.98, epsilon);
}

TEST_F(MatrixMultiplicationComplexTests, ComplexInt_ComplexInt)
{
    const auto complexIntMat = Matrix<std::complex<int>>({{1,1}, {2,2}, {3,3},
                                                          {4,4}, {2,2}, {5,5},
                                                          {6,4}, {7,5}, {3,4}},
                                                         3,3);

    const auto res = complexIntMat * complexIntMat;
    ASSERT_EQ(res(0,0), std::complex<int>(6, 48)); ASSERT_EQ(res(0,1), std::complex<int>(6, 48)); ASSERT_EQ(res(0,2), std::complex<int>(-3, 47));
    ASSERT_EQ(res(1,0), std::complex<int>(10, 74)); ASSERT_EQ(res(1,1), std::complex<int>(10, 84)); ASSERT_EQ(res(1,2), std::complex<int>(-5, 79));
    ASSERT_EQ(res(2,0), std::complex<int>(12, 94)); ASSERT_EQ(res(2,1), std::complex<int>(9, 87)); ASSERT_EQ(res(2,2), std::complex<int>(9, 114));
}

TEST_F(MatrixMultiplicationComplexTests, ComplexInt_ComplexFloat)
{
    const auto complexIntMat = Matrix<std::complex<int>>({{1,1}, {2,2},
                                                          {4,4}, {2,2},
                                                          {6,4}, {7,5}},
                                                         3,2);

    const auto complexFloatMat = Matrix<std::complex<float>>({{1.1f, 1.2f}, {2.2f, 2.3f}, {3.6f, 3.7f},
                                                           {4.7f, 4.2f}, {1.8f, 1.5f}, {-2.1f, -6.2f}},
                                                                   2,3);

    const auto res = complexIntMat * complexFloatMat;
    ASSERT_NEAR(res(0,0).real(), 0.9f, fepsilon);  ASSERT_NEAR(res(0,0).imag(), 20.1f, fepsilon);
    ASSERT_NEAR(res(1,0).real(), 0.6f, fepsilon);   ASSERT_NEAR(res(1,0).imag(), 27.f, fepsilon);
    ASSERT_NEAR(res(2,0).real(), 13.7f, fepsilon);  ASSERT_NEAR(res(2,0).imag(), 64.5f, fepsilon);

    ASSERT_NEAR(res(0,1).real(), 0.5f, fepsilon);   ASSERT_NEAR(res(0,1).imag(), 11.1f, fepsilon);
    ASSERT_NEAR(res(1,1).real(), 0.2f, fepsilon);   ASSERT_NEAR(res(1,1).imag(), 24.6f, fepsilon);
    ASSERT_NEAR(res(2,1).real(), 9.1f, fepsilon);  ASSERT_NEAR(res(2,1).imag(), 42.1f, fepsilon);

    ASSERT_NEAR(res(0,2).real(), 8.1f, fepsilon);  ASSERT_NEAR(res(0,2).imag(), -9.3f, fepsilon);
    ASSERT_NEAR(res(1,2).real(), 7.8f, fepsilon);  ASSERT_NEAR(res(1,2).imag(), 12.6f, fepsilon);
    ASSERT_NEAR(res(2,2).real(), 23.1f, fepsilon);  ASSERT_NEAR(res(2,2).imag(), -17.3f, fepsilon);

    const auto res2 = complexFloatMat * complexIntMat;
    ASSERT_NEAR(res2(0,0).real(), 6.3f, fepsilon);  ASSERT_NEAR(res2(0,0).imag(), 56.9f, fepsilon);
    ASSERT_NEAR(res2(1,0).real(), 13.9f, fepsilon);   ASSERT_NEAR(res2(1,0).imag(), -23.5f, fepsilon);

    ASSERT_NEAR(res2(0,1).real(), 6.3f, fepsilon);   ASSERT_NEAR(res2(0,1).imag(), 57.5f, fepsilon);
    ASSERT_NEAR(res2(1,1).real(), 17.9f, fepsilon);   ASSERT_NEAR(res2(1,1).imag(), -29.5f, fepsilon);
}

TEST_F(MatrixMultiplicationComplexTests, ComplexInt_ComplexDouble)
{
    const auto complexIntMat = Matrix<std::complex<int>>({{1,3}, {4,2},
                                                          {6,4}, {2,2},
                                                          {8,4}, {3,1}},
                                                         3,2);

    const auto complexDoubleMat = Matrix<std::complex<double>>({{1.21, 1.32}, {2.4, 2.8}, {4.1, 6.2},
                                                              {4.7, -4.2}, {-1.8, 1.5}, {2.1, 6.2}},
                                                             2,3);

    const auto res = complexIntMat * complexDoubleMat;
    ASSERT_NEAR(res(0,0).real(), 24.45, epsilon);  ASSERT_NEAR(res(0,0).imag(), -2.45, epsilon);
    ASSERT_NEAR(res(1,0).real(), 19.78, epsilon);   ASSERT_NEAR(res(1,0).imag(), 13.76, epsilon);
    ASSERT_NEAR(res(2,0).real(), 22.7, epsilon);  ASSERT_NEAR(res(2,0).imag(), 7.5, epsilon);

    ASSERT_NEAR(res(0,1).real(), -16.2, epsilon);   ASSERT_NEAR(res(0,1).imag(), 12.4, epsilon);
    ASSERT_NEAR(res(1,1).real(), -3.4, epsilon);   ASSERT_NEAR(res(1,1).imag(), 25.8, epsilon);
    ASSERT_NEAR(res(2,1).real(), 1.1, epsilon);  ASSERT_NEAR(res(2,1).imag(), 34.7, epsilon);

    ASSERT_NEAR(res(0,2).real(), -18.5, epsilon);  ASSERT_NEAR(res(0,2).imag(), 47.5, epsilon);
    ASSERT_NEAR(res(1,2).real(), -8.4, epsilon);  ASSERT_NEAR(res(1,2).imag(), 70.2, epsilon);
    ASSERT_NEAR(res(2,2).real(), 8.1, epsilon);  ASSERT_NEAR(res(2,2).imag(), 86.7, epsilon);

    const auto res2 = complexDoubleMat * complexIntMat;
    ASSERT_NEAR(res2(0,0).real(), 8.45, epsilon);  ASSERT_NEAR(res2(0,0).imag(), 97.35, epsilon);
    ASSERT_NEAR(res2(1,0).real(), -7.5, epsilon);   ASSERT_NEAR(res2(1,0).imag(), 69.7, epsilon);

    ASSERT_NEAR(res2(0,1).real(), 7.5, epsilon);   ASSERT_NEAR(res2(0,1).imag(), 40.8, epsilon);
    ASSERT_NEAR(res2(1,1).real(), 20.7, epsilon);   ASSERT_NEAR(res2(1,1).imag(), 12.7, epsilon);
}

TEST_F(MatrixMultiplicationComplexTests, ComplexInt_ComplexLongDouble)
{
    const auto complexIntMat = Matrix<std::complex<int>>({{1,3}, {4,2},
                                                          {6,4}, {2,2},
                                                          {8,4}, {3,1}},
                                                         3,2);

    const auto complexDoubleMat = Matrix<std::complex<long double>>({{1.21, 1.32}, {2.4, 2.8}, {4.1, 6.2},
                                                                {4.7, -4.2}, {-1.8, 1.5}, {2.1, 6.2}},
                                                               2,3);

    const auto res = complexIntMat * complexDoubleMat;
    ASSERT_NEAR(res(0,0).real(), 24.45, epsilon);  ASSERT_NEAR(res(0,0).imag(), -2.45, epsilon);
    ASSERT_NEAR(res(1,0).real(), 19.78, epsilon);   ASSERT_NEAR(res(1,0).imag(), 13.76, epsilon);
    ASSERT_NEAR(res(2,0).real(), 22.7, epsilon);  ASSERT_NEAR(res(2,0).imag(), 7.5, epsilon);

    ASSERT_NEAR(res(0,1).real(), -16.2, epsilon);   ASSERT_NEAR(res(0,1).imag(), 12.4, epsilon);
    ASSERT_NEAR(res(1,1).real(), -3.4, epsilon);   ASSERT_NEAR(res(1,1).imag(), 25.8, epsilon);
    ASSERT_NEAR(res(2,1).real(), 1.1, epsilon);  ASSERT_NEAR(res(2,1).imag(), 34.7, epsilon);

    ASSERT_NEAR(res(0,2).real(), -18.5, epsilon);  ASSERT_NEAR(res(0,2).imag(), 47.5, epsilon);
    ASSERT_NEAR(res(1,2).real(), -8.4, epsilon);  ASSERT_NEAR(res(1,2).imag(), 70.2, epsilon);
    ASSERT_NEAR(res(2,2).real(), 8.1, epsilon);  ASSERT_NEAR(res(2,2).imag(), 86.7, epsilon);

    const auto res2 = complexDoubleMat * complexIntMat;
    ASSERT_NEAR(res2(0,0).real(), 8.45, epsilon);  ASSERT_NEAR(res2(0,0).imag(), 97.35, epsilon);
    ASSERT_NEAR(res2(1,0).real(), -7.5, epsilon);   ASSERT_NEAR(res2(1,0).imag(), 69.7, epsilon);

    ASSERT_NEAR(res2(0,1).real(), 7.5, epsilon);   ASSERT_NEAR(res2(0,1).imag(), 40.8, epsilon);
    ASSERT_NEAR(res2(1,1).real(), 20.7, epsilon);   ASSERT_NEAR(res2(1,1).imag(), 12.7, epsilon);
}

TEST_F(MatrixMultiplicationComplexTests, ComplexFloat_ComplexFloat)
{
    const auto complexFloatMat = Matrix<std::complex<float>>({{1.1f, 1.2f}, {2.2f, 2.3f}, {3.6f, 3.7f},
                                                              {4.7f, 4.2f}, {1.8f, 1.5f}, {-2.1f, -6.2f},
                                                              {2.7f, 1.2f}, {3.8f, 2.5f}, {-1.1f, -3.2f}},
                                                             3,3);

    const auto res = complexFloatMat * complexFloatMat;
    ASSERT_NEAR(res(0,0).real(), 5.73f, fepsilon);  ASSERT_NEAR(res(0,0).imag(), 37.f, fepsilon);
    ASSERT_NEAR(res(1,0).real(), 4.06f, fepsilon);   ASSERT_NEAR(res(1,0).imag(), 5.61f, fepsilon);
    ASSERT_NEAR(res(2,0).real(), 9.76f, fepsilon);  ASSERT_NEAR(res(2,0).imag(), 22.31f, fepsilon);

    ASSERT_NEAR(res(0,1).real(), 4.6f, fepsilon);   ASSERT_NEAR(res(0,1).imag(), 35.67f, fepsilon);
    ASSERT_NEAR(res(1,1).real(), 9.19f, fepsilon);   ASSERT_NEAR(res(1,1).imag(), -3.36f, fepsilon);
    ASSERT_NEAR(res(2,1).real(), 10.09f, fepsilon);  ASSERT_NEAR(res(2,1).imag(), 4.14f, fepsilon);

    ASSERT_NEAR(res(0,2).real(), 17.04f, fepsilon);  ASSERT_NEAR(res(0,2).imag(), -25.67f, fepsilon);
    ASSERT_NEAR(res(1,2).real(), -10.63f, fepsilon);  ASSERT_NEAR(res(1,2).imag(), 31.74f, fepsilon);
    ASSERT_NEAR(res(2,2).real(), 3.77f, fepsilon);  ASSERT_NEAR(res(2,2).imag(), -7.46f, fepsilon);
}

TEST_F(MatrixMultiplicationComplexTests, ComplexFloat_ComplexDouble)
{
    const auto complexFloatMat = Matrix<std::complex<float>>({{1.1f, 1.2f}, {2.2f, 2.3f}, {3.6f, 3.7f},
                                                              {4.7f, 4.2f}, {1.8f, 1.5f}, {-2.1f, -6.2f},
                                                              {2.7f, 1.2f}, {3.8f, 2.5f}, {-1.1f, -3.2f}},
                                                             3,3);

    const auto complexDoubleMat = Matrix<std::complex<double>>({{1.1, 1.2}, {2.2, 2.3}, {3.6, 3.7},
                                                              {4.7, 4.2}, {1.8, 1.5}, {-2.1, -6.2},
                                                              {2.7, 1.2}, {3.8, 2.5}, {-1.1, -3.2}},
                                                             3,3);

    auto res = complexFloatMat * complexDoubleMat;
    ASSERT_NEAR(res(0,0).real(), 5.73, fepsilon);  ASSERT_NEAR(res(0,0).imag(), 37., fepsilon);
    ASSERT_NEAR(res(1,0).real(), 4.06, fepsilon);   ASSERT_NEAR(res(1,0).imag(), 5.61, fepsilon);
    ASSERT_NEAR(res(2,0).real(), 9.76, fepsilon);  ASSERT_NEAR(res(2,0).imag(), 22.31, fepsilon);

    ASSERT_NEAR(res(0,1).real(), 4.6, fepsilon);   ASSERT_NEAR(res(0,1).imag(), 35.67, fepsilon);
    ASSERT_NEAR(res(1,1).real(), 9.19, fepsilon);   ASSERT_NEAR(res(1,1).imag(), -3.36, fepsilon);
    ASSERT_NEAR(res(2,1).real(), 10.09, fepsilon);  ASSERT_NEAR(res(2,1).imag(), 4.14, fepsilon);

    ASSERT_NEAR(res(0,2).real(), 17.04, fepsilon);  ASSERT_NEAR(res(0,2).imag(), -25.67, fepsilon);
    ASSERT_NEAR(res(1,2).real(), -10.63, fepsilon);  ASSERT_NEAR(res(1,2).imag(), 31.74, fepsilon);
    ASSERT_NEAR(res(2,2).real(), 3.77, fepsilon);  ASSERT_NEAR(res(2,2).imag(), -7.46, fepsilon);

    res = complexDoubleMat * complexFloatMat;
    ASSERT_NEAR(res(0,0).real(), 5.73, fepsilon);  ASSERT_NEAR(res(0,0).imag(), 37., fepsilon);
    ASSERT_NEAR(res(1,0).real(), 4.06, fepsilon);   ASSERT_NEAR(res(1,0).imag(), 5.61, fepsilon);
    ASSERT_NEAR(res(2,0).real(), 9.76, fepsilon);  ASSERT_NEAR(res(2,0).imag(), 22.31, fepsilon);

    ASSERT_NEAR(res(0,1).real(), 4.6, fepsilon);   ASSERT_NEAR(res(0,1).imag(), 35.67, fepsilon);
    ASSERT_NEAR(res(1,1).real(), 9.19, fepsilon);   ASSERT_NEAR(res(1,1).imag(), -3.36, fepsilon);
    ASSERT_NEAR(res(2,1).real(), 10.09, fepsilon);  ASSERT_NEAR(res(2,1).imag(), 4.14, fepsilon);

    ASSERT_NEAR(res(0,2).real(), 17.04, fepsilon);  ASSERT_NEAR(res(0,2).imag(), -25.67, fepsilon);
    ASSERT_NEAR(res(1,2).real(), -10.63, fepsilon);  ASSERT_NEAR(res(1,2).imag(), 31.74, fepsilon);
    ASSERT_NEAR(res(2,2).real(), 3.77, fepsilon);  ASSERT_NEAR(res(2,2).imag(), -7.46, fepsilon);
}