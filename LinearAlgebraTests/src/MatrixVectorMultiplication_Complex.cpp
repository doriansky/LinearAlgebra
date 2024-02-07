//
// Created by dorian on 07.02.2024.
// stoicadorian@gmail.com
//

#include "gtest/gtest.h"
#include "Matrix.hpp"

using namespace LinearAlgebra::Matrix;
using namespace LinearAlgebra::Vector;

class MatrixVectorMultiplication_Complex : public ::testing::Test
{

protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

    float               fepsilon        = 1e-5f;
    double              epsilon         = 1e-9;
};

TEST_F(MatrixVectorMultiplication_Complex, Multiply_IntMatrix_ComplexIntVector)
{
    const auto mat = Matrix<int>({1,2,3,
                                  4,5,6,
                                  7,8,9},
                                 3,3);

    const auto vec = Vector<std::complex<int>>({{1,2}, {3,4}, {5,6}});

    const auto res = mat * vec;
    ASSERT_EQ(res[0], std::complex<int>(22, 28));
    ASSERT_EQ(res[1], std::complex<int>(49, 64));
    ASSERT_EQ(res[2], std::complex<int>(76, 100));
}

TEST_F(MatrixVectorMultiplication_Complex, Multiply_IntMatrix_ComplexFloatVector)
{
    const auto mat = Matrix<int>({1,2,3,
                                  4,5,6,
                                  7,8,9},
                                 3,3);

    const auto vec = Vector<std::complex<float>>({{1.1f,2.2f}, {3.3f,4.4f}, {5.5f,6.8f}});

    const auto res = mat * vec;
    ASSERT_NEAR(res[0].real(), 24.2f, fepsilon);    ASSERT_NEAR(res[0].imag(), 31.4f, fepsilon);
    ASSERT_NEAR(res[1].real(), 53.9f, fepsilon);    ASSERT_NEAR(res[1].imag(), 71.6f, fepsilon);
    ASSERT_NEAR(res[2].real(), 83.6f, fepsilon);    ASSERT_NEAR(res[2].imag(), 111.8f, fepsilon);
}

TEST_F(MatrixVectorMultiplication_Complex, Multiply_IntMatrix_ComplexDoubleVector)
{
    const auto mat = Matrix<int>({1,2,3,
                                  4,5,6,
                                  7,8,9},
                                 3,3);

    const auto vec = Vector<std::complex<double>>({{1.1,2.2}, {3.3,4.4}, {5.5,6.9}});

    const auto res = mat * vec;
    ASSERT_NEAR(res[0].real(), 24.2, epsilon);    ASSERT_NEAR(res[0].imag(), 31.7, epsilon);
    ASSERT_NEAR(res[1].real(), 53.9, epsilon);    ASSERT_NEAR(res[1].imag(), 72.2, epsilon);
    ASSERT_NEAR(res[2].real(), 83.6, epsilon);    ASSERT_NEAR(res[2].imag(), 112.7, epsilon);
}

TEST_F(MatrixVectorMultiplication_Complex, Multiply_FloatMatrix_ComplexIntVector)
{
    const auto mat = Matrix<float>({1.1f,2.2f,3.4f,
                                  4.5f,5.6f,6.12f,
                                  7.8f,8.9f,9.36f},
                                 3,3);

    const auto vec = Vector<std::complex<int>>({{1,2}, {3,4}, {5,6}});

    const auto res = mat * vec;
    ASSERT_NEAR(res[0].real(), 24.7f, fepsilon);    ASSERT_NEAR(res[0].imag(), 31.4f, fepsilon);
    ASSERT_NEAR(res[1].real(), 51.9f, fepsilon);    ASSERT_NEAR(res[1].imag(), 68.12f, fepsilon);
    ASSERT_NEAR(res[2].real(), 81.3f, fepsilon);    ASSERT_NEAR(res[2].imag(), 107.36f, fepsilon);
}


TEST_F(MatrixVectorMultiplication_Complex, Multiply_FloatMatrix_ComplexFloatVector)
{
    const auto mat = Matrix<float>({1.1f,2.2f,3.4f,
                                    4.5f,5.6f,6.12f,
                                    7.8f,8.9f,9.36f},
                                   3,3);

    const auto vec = Vector<std::complex<float>>({{1.1f,2.2f}, {3.3f,4.4f}, {5.5f,6.8f}});

    const auto res = mat * vec;
    ASSERT_NEAR(res[0].real(), 27.17f, fepsilon);    ASSERT_NEAR(res[0].imag(), 35.22f, fepsilon);
    ASSERT_NEAR(res[1].real(), 57.09f, fepsilon);    ASSERT_NEAR(res[1].imag(), 76.156f, fepsilon);
    ASSERT_NEAR(res[2].real(), 89.43f, fepsilon);    ASSERT_NEAR(res[2].imag(), 119.968f, fepsilon);
}

TEST_F(MatrixVectorMultiplication_Complex, Multiply_FloatMatrix_ComplexDoubletVector)
{
    const auto mat = Matrix<float>({1.1f,2.2f,3.4f,
                                    4.5f,5.6f,6.12f,
                                    7.8f,8.9f,9.36f},
                                   3,3);

    const auto vec = Vector<std::complex<double>>({{1.1,2.2}, {3.3,4.4}, {5.5,6.28}});

    const auto res = mat * vec;
    ASSERT_NEAR(res[0].real(), 27.17, fepsilon);    ASSERT_NEAR(res[0].imag(), 33.452, fepsilon);
    ASSERT_NEAR(res[1].real(), 57.09, fepsilon);    ASSERT_NEAR(res[1].imag(), 72.9736, fepsilon);
    ASSERT_NEAR(res[2].real(), 89.43, fepsilon);    ASSERT_NEAR(res[2].imag(), 115.1008, fepsilon);
}

TEST_F(MatrixVectorMultiplication_Complex, Multiply_DoubleMatrix_ComplexIntVector)
{
    const auto mat = Matrix<double>({1.1,2.2,3.4,
                                    4.5,5.6,6.12,
                                    7.8,8.9,9.36},
                                   3,3);

    const auto vec = Vector<std::complex<int>>({{1,2}, {3,4}, {5,6}});

    const auto res = mat * vec;
    ASSERT_NEAR(res[0].real(), 24.7, epsilon);    ASSERT_NEAR(res[0].imag(), 31.4, epsilon);
    ASSERT_NEAR(res[1].real(), 51.9, epsilon);    ASSERT_NEAR(res[1].imag(), 68.12, epsilon);
    ASSERT_NEAR(res[2].real(), 81.3, epsilon);    ASSERT_NEAR(res[2].imag(), 107.36, epsilon);
}


TEST_F(MatrixVectorMultiplication_Complex, Multiply_DoubleMatrix_ComplexFloatVector)
{
    const auto mat = Matrix<double>({1.1,2.2,3.4,
                                     4.5,5.6,6.12,
                                     7.8,8.9,9.36},
                                    3,3);

    const auto vec = Vector<std::complex<float>>({{1.1f,2.2f}, {3.3f,4.4f}, {5.5f,6.8f}});

    const auto res = mat * vec;
    ASSERT_NEAR(res[0].real(), 27.17, fepsilon);    ASSERT_NEAR(res[0].imag(), 35.22, fepsilon);
    ASSERT_NEAR(res[1].real(), 57.09, fepsilon);    ASSERT_NEAR(res[1].imag(), 76.156, fepsilon);
    ASSERT_NEAR(res[2].real(), 89.43, fepsilon);    ASSERT_NEAR(res[2].imag(), 119.968, fepsilon);
}

TEST_F(MatrixVectorMultiplication_Complex, Multiply_DoubleMatrix_ComplexDoubletVector)
{
    const auto mat = Matrix<double>({1.1,2.2,3.4,
                                     4.5,5.6,6.12,
                                     7.8,8.9,9.36},
                                    3,3);

    const auto vec = Vector<std::complex<double>>({{1.1,2.2}, {3.3,4.4}, {5.5,6.28}});

    const auto res = mat * vec;
    ASSERT_NEAR(res[0].real(), 27.17, epsilon);    ASSERT_NEAR(res[0].imag(), 33.452, epsilon);
    ASSERT_NEAR(res[1].real(), 57.09, epsilon);    ASSERT_NEAR(res[1].imag(), 72.9736, epsilon);
    ASSERT_NEAR(res[2].real(), 89.43, epsilon);    ASSERT_NEAR(res[2].imag(), 115.1008, epsilon);
}

TEST_F(MatrixVectorMultiplication_Complex, Multiply_ComplexIntMatrix_IntVector)
{
    const auto mat = Matrix<std::complex<int>>({{1,2}, {3,4}, {5,6},
                                                {7,8}, {9,2}, {1,4},
                                                {3,4}, {5,7}, {3,1}},
                                               3,3);

    const auto vec = Vector<int>({1,5,8});

    const auto res = mat * vec;
    ASSERT_EQ(res[0], std::complex<int>(56,70));
    ASSERT_EQ(res[1], std::complex<int>(60, 50));
    ASSERT_EQ(res[2], std::complex<int>(52, 47));
}

TEST_F(MatrixVectorMultiplication_Complex, Multiply_ComplexIntMatrix_FloatVector)
{
    const auto mat = Matrix<std::complex<int>>({{1,2}, {3,4}, {5,6},
                                                {7,8}, {9,2}, {1,4},
                                                {3,4}, {5,7}, {3,1}},
                                               3,3);

    const auto vec = Vector<float>({1.3f,5.2f,8.5f});

    const auto res = mat * vec;
    ASSERT_NEAR(res[0].real(), 59.4f, fepsilon);    ASSERT_NEAR(res[0].imag(), 74.4f, fepsilon);
    ASSERT_NEAR(res[1].real(), 64.4f, fepsilon);    ASSERT_NEAR(res[1].imag(), 54.8f, fepsilon);
    ASSERT_NEAR(res[2].real(), 55.4f, fepsilon);    ASSERT_NEAR(res[2].imag(), 50.1f, fepsilon);
}

TEST_F(MatrixVectorMultiplication_Complex, Multiply_ComplexIntMatrix_DoubleVector)
{
    const auto mat = Matrix<std::complex<int>>({{1,2}, {3,4}, {5,6},
                                                {7,8}, {9,2}, {1,4},
                                                {3,4}, {5,7}, {3,1}},
                                               3,3);

    const auto vec = Vector<double>({1.3,5.2,8.5});

    const auto res = mat * vec;
    ASSERT_NEAR(res[0].real(), 59.4, epsilon);    ASSERT_NEAR(res[0].imag(), 74.4, epsilon);
    ASSERT_NEAR(res[1].real(), 64.4, epsilon);    ASSERT_NEAR(res[1].imag(), 54.8, epsilon);
    ASSERT_NEAR(res[2].real(), 55.4, epsilon);    ASSERT_NEAR(res[2].imag(), 50.1, epsilon);
}


TEST_F(MatrixVectorMultiplication_Complex, Multiply_ComplexIntMatrix_ComplexIntVector)
{
    const auto mat = Matrix<std::complex<int>>({{1,2}, {3,4}, {5,6},
                                  {7,8}, {9,2}, {1,4},
                                  {3,4}, {5,7}, {3,1}},
                                 3,3);

    const auto vec = Vector<std::complex<int>>({{1,2}, {3,4}, {5,6}});

    const auto res = mat * vec;
    ASSERT_EQ(res[0], std::complex<int>(-21, 88));
    ASSERT_EQ(res[1], std::complex<int>(-9, 90));
    ASSERT_EQ(res[2], std::complex<int>(-9, 74));
}

TEST_F(MatrixVectorMultiplication_Complex, Multiply_ComplexIntMatrix_ComplexFloatVector)
{
    const auto mat = Matrix<std::complex<int>>({{1,2}, {3,4}, {5,6},
                                                {7,8}, {9,2}, {1,4},
                                                {3,4}, {5,7}, {3,1}},
                                               3,3);

    const auto vec = Vector<std::complex<float>>({{1.3f,2.4f}, {3.5f,4.6f}, {5.8f,6.2f}});

    const auto res = mat * vec;
    ASSERT_NEAR(res[0].real(), -19.6f, fepsilon);    ASSERT_NEAR(res[0].imag(), 98.6f, fepsilon);
    ASSERT_NEAR(res[1].real(), -6.8f, fepsilon);    ASSERT_NEAR(res[1].imag(), 105.f, fepsilon);
    ASSERT_NEAR(res[2].real(), -9.2f, fepsilon);    ASSERT_NEAR(res[2].imag(), 84.3f, fepsilon);
}

TEST_F(MatrixVectorMultiplication_Complex, Multiply_ComplexIntMatrix_ComplexDoubleVector)
{
    const auto mat = Matrix<std::complex<int>>({{1,2}, {3,4}, {5,6},
                                                {7,8}, {9,2}, {1,4},
                                                {3,4}, {5,7}, {3,1}},
                                               3,3);

    const auto vec = Vector<std::complex<double>>({{1.3,2.4}, {3.5,4.6}, {5.8,6.2}});

    const auto res = mat * vec;
    ASSERT_NEAR(res[0].real(), -19.6, epsilon);    ASSERT_NEAR(res[0].imag(), 98.6, epsilon);
    ASSERT_NEAR(res[1].real(), -6.8, epsilon);    ASSERT_NEAR(res[1].imag(), 105., epsilon);
    ASSERT_NEAR(res[2].real(), -9.2, epsilon);    ASSERT_NEAR(res[2].imag(), 84.3, epsilon);
}

TEST_F(MatrixVectorMultiplication_Complex, Multiply_ComplexFloatMatrix_IntVector)
{
    const auto mat = Matrix<std::complex<float>>({{1.23f,2.12f}, {3.45f,4.75f}, {5.24f,6.86f},
                                                {7.32f,8.62f}, {9.84f,2.63f}, {1.87f,4.13f},
                                                {3.64f,4.17f}, {5.27f,7.17f}, {3.94f,1.93f}},
                                               3,3);

    const auto vec = Vector<int>({1, 5, 8});

    const auto res = mat * vec;
    ASSERT_NEAR(res[0].real(), 60.4f, fepsilon);    ASSERT_NEAR(res[0].imag(), 80.75f, fepsilon);
    ASSERT_NEAR(res[1].real(), 71.48f, fepsilon);    ASSERT_NEAR(res[1].imag(), 54.81f, fepsilon);
    ASSERT_NEAR(res[2].real(), 61.51f, fepsilon);    ASSERT_NEAR(res[2].imag(), 55.46f, fepsilon);
}


TEST_F(MatrixVectorMultiplication_Complex, Multiply_ComplexFloatMatrix_FloatVector)
{
    const auto mat = Matrix<std::complex<float>>({{1.23f,2.12f}, {3.45f,4.75f}, {5.24f,6.86f},
                                                  {7.32f,8.62f}, {9.84f,2.63f}, {1.87f,4.13f},
                                                  {3.64f,4.17f}, {5.27f,7.17f}, {3.94f,1.93f}},
                                                 3,3);

    const auto vec = Vector<float>({1.4f, 5.7f, 8.3f});

    const auto res = mat * vec;
    ASSERT_NEAR(res[0].real(), 64.879f, fepsilon);    ASSERT_NEAR(res[0].imag(), 86.981f, fepsilon);
    ASSERT_NEAR(res[1].real(), 81.857f, fepsilon);    ASSERT_NEAR(res[1].imag(), 61.338f, fepsilon);
    ASSERT_NEAR(res[2].real(), 67.837f, fepsilon);    ASSERT_NEAR(res[2].imag(), 62.726f, fepsilon);
}

TEST_F(MatrixVectorMultiplication_Complex, Multiply_ComplexFloatMatrix_DoubleVector)
{
    const auto mat = Matrix<std::complex<float>>({{1.23f,2.12f}, {3.45f,4.75f}, {5.24f,6.86f},
                                                  {7.32f,8.62f}, {9.84f,2.63f}, {1.87f,4.13f},
                                                  {3.64f,4.17f}, {5.27f,7.17f}, {3.94f,1.93f}},
                                                 3,3);

    const auto vec = Vector<double>({1.4, 5.7, 8.3});

    const auto res = mat * vec;
    ASSERT_NEAR(res[0].real(), 64.879, fepsilon);    ASSERT_NEAR(res[0].imag(), 86.981, fepsilon);
    ASSERT_NEAR(res[1].real(), 81.857, fepsilon);    ASSERT_NEAR(res[1].imag(), 61.338, fepsilon);
    ASSERT_NEAR(res[2].real(), 67.837, fepsilon);    ASSERT_NEAR(res[2].imag(), 62.726, fepsilon);
}

TEST_F(MatrixVectorMultiplication_Complex, Multiply_ComplexFloatMatrix_ComplexIntVector)
{
    const auto mat = Matrix<std::complex<float>>({{1.23f,2.12f}, {3.45f,4.75f}, {5.24f,6.86f},
                                                  {7.32f,8.62f}, {9.84f,2.63f}, {1.87f,4.13f},
                                                  {3.64f,4.17f}, {5.27f,7.17f}, {3.94f,1.93f}},
                                                 3,3);

    const auto vec = Vector<std::complex<int>>({{1,2}, {5,3}, {8,4}});

    const auto res = mat * vec;
    ASSERT_NEAR(res[0].real(), 14.47f, fepsilon);    ASSERT_NEAR(res[0].imag(), 114.52f, fepsilon);
    ASSERT_NEAR(res[1].real(), 29.83f, fepsilon);    ASSERT_NEAR(res[1].imag(), 106.45f, fepsilon);
    ASSERT_NEAR(res[2].real(), 23.94f, fepsilon);    ASSERT_NEAR(res[2].imag(), 94.31f, fepsilon);
}


TEST_F(MatrixVectorMultiplication_Complex, Multiply_ComplexFloatMatrix_ComplexFloatVector)
{
    const auto mat = Matrix<std::complex<float>>({{1.23f,2.12f}, {3.45f,4.75f}, {5.24f,6.86f},
                                                  {7.32f,8.62f}, {9.84f,2.63f}, {1.87f,4.13f},
                                                  {3.64f,4.17f}, {5.27f,7.17f}, {3.94f,1.93f}},
                                                 3,3);

    const auto vec = Vector<std::complex<float>>({{1.2f,-2.4f}, {-5.6f,3.7f}, {-8.1f,-4.3f}});

    const auto res = mat * vec;
    ASSERT_NEAR(res[0].real(), -43.277f, fepsilon);    ASSERT_NEAR(res[0].imag(), -92.341f, fepsilon);
    ASSERT_NEAR(res[1].real(), -32.751f, fepsilon);    ASSERT_NEAR(res[1].imag(), -27.038f, fepsilon);
    ASSERT_NEAR(res[2].real(), -65.28f, fepsilon);    ASSERT_NEAR(res[2].imag(), -56.96f, fepsilon);
}

TEST_F(MatrixVectorMultiplication_Complex, Multiply_ComplexFloatMatrix_ComplexDoubleVector)
{
    const auto mat = Matrix<std::complex<float>>({{1.23f,2.12f}, {3.45f,4.75f}, {5.24f,6.86f},
                                                  {7.32f,8.62f}, {9.84f,2.63f}, {1.87f,4.13f},
                                                  {3.64f,4.17f}, {5.27f,7.17f}, {3.94f,1.93f}},
                                                 3,3);

    const auto vec = Vector<std::complex<double>>({{1.2,-2.4}, {-5.6,3.7}, {-8.1,-4.3}});

    const auto res = mat * vec;
    ASSERT_NEAR(res[0].real(), -43.277, fepsilon);    ASSERT_NEAR(res[0].imag(), -92.341, fepsilon);
    ASSERT_NEAR(res[1].real(), -32.751, fepsilon);    ASSERT_NEAR(res[1].imag(), -27.038, fepsilon);
    ASSERT_NEAR(res[2].real(), -65.28, fepsilon);    ASSERT_NEAR(res[2].imag(), -56.96, fepsilon);
}

TEST_F(MatrixVectorMultiplication_Complex, Multiply_ComplexDoubleMatrix_IntVector)
{
    const auto mat = Matrix<std::complex<double>>({{1.23,2.12}, {3.45,4.75}, {5.24,6.86},
                                                  {7.32,8.62}, {9.84,2.63}, {1.87,4.13},
                                                  {3.64,4.17}, {5.27,7.17}, {3.94,1.93}},
                                                 3,3);

    const auto vec = Vector<int>({1, 5, 8});

    const auto res = mat * vec;
    ASSERT_NEAR(res[0].real(), 60.4, epsilon);    ASSERT_NEAR(res[0].imag(), 80.75, epsilon);
    ASSERT_NEAR(res[1].real(), 71.48, epsilon);    ASSERT_NEAR(res[1].imag(), 54.81, epsilon);
    ASSERT_NEAR(res[2].real(), 61.51, epsilon);    ASSERT_NEAR(res[2].imag(), 55.46, epsilon);
}


TEST_F(MatrixVectorMultiplication_Complex, Multiply_ComplexDoubleMatrix_FloatVector)
{
    const auto mat = Matrix<std::complex<double>>({{1.23,2.12}, {3.45,4.75}, {5.24,6.86},
                                                   {7.32,8.62}, {9.84,2.63}, {1.87,4.13},
                                                   {3.64,4.17}, {5.27,7.17}, {3.94,1.93}},
                                                  3,3);


    const auto vec = Vector<float>({1.4f, 5.7f, 8.3f});

    const auto res = mat * vec;
    ASSERT_NEAR(res[0].real(), 64.879, fepsilon);    ASSERT_NEAR(res[0].imag(), 86.981, fepsilon);
    ASSERT_NEAR(res[1].real(), 81.857, fepsilon);    ASSERT_NEAR(res[1].imag(), 61.338, fepsilon);
    ASSERT_NEAR(res[2].real(), 67.837, fepsilon);    ASSERT_NEAR(res[2].imag(), 62.726, fepsilon);
}

TEST_F(MatrixVectorMultiplication_Complex, Multiply_ComplexDoubleMatrix_DoubleVector)
{
    const auto mat = Matrix<std::complex<double>>({{1.23,2.12}, {3.45,4.75}, {5.24,6.86},
                                                   {7.32,8.62}, {9.84,2.63}, {1.87,4.13},
                                                   {3.64,4.17}, {5.27,7.17}, {3.94,1.93}},
                                                  3,3);


    const auto vec = Vector<double>({1.4, 5.7, 8.3});

    const auto res = mat * vec;
    ASSERT_NEAR(res[0].real(), 64.879, epsilon);    ASSERT_NEAR(res[0].imag(), 86.981, epsilon);
    ASSERT_NEAR(res[1].real(), 81.857, epsilon);    ASSERT_NEAR(res[1].imag(), 61.338, epsilon);
    ASSERT_NEAR(res[2].real(), 67.837, epsilon);    ASSERT_NEAR(res[2].imag(), 62.726, epsilon);
}

TEST_F(MatrixVectorMultiplication_Complex, Multiply_ComplexDoubleMatrix_ComplexIntVector)
{
    const auto mat = Matrix<std::complex<double>>({{1.23,2.12}, {3.45,4.75}, {5.24,6.86},
                                                   {7.32,8.62}, {9.84,2.63}, {1.87,4.13},
                                                   {3.64,4.17}, {5.27,7.17}, {3.94,1.93}},
                                                  3,3);

    const auto vec = Vector<std::complex<int>>({{1,2}, {5,3}, {8,4}});

    const auto res = mat * vec;
    ASSERT_NEAR(res[0].real(), 14.47, epsilon);    ASSERT_NEAR(res[0].imag(), 114.52, epsilon);
    ASSERT_NEAR(res[1].real(), 29.83, epsilon);    ASSERT_NEAR(res[1].imag(), 106.45, epsilon);
    ASSERT_NEAR(res[2].real(), 23.94, epsilon);    ASSERT_NEAR(res[2].imag(), 94.31, epsilon);
}


TEST_F(MatrixVectorMultiplication_Complex, Multiply_ComplexDoubleMatrix_ComplexFloatVector)
{
    const auto mat = Matrix<std::complex<double>>({{1.23,2.12}, {3.45,4.75}, {5.24,6.86},
                                                   {7.32,8.62}, {9.84,2.63}, {1.87,4.13},
                                                   {3.64,4.17}, {5.27,7.17}, {3.94,1.93}},
                                                  3,3);

    const auto vec = Vector<std::complex<float>>({{1.2f,-2.4f}, {-5.6f,3.7f}, {-8.1f,-4.3f}});

    const auto res = mat * vec;
    ASSERT_NEAR(res[0].real(), -43.277, fepsilon);    ASSERT_NEAR(res[0].imag(), -92.341, fepsilon);
    ASSERT_NEAR(res[1].real(), -32.751, fepsilon);    ASSERT_NEAR(res[1].imag(), -27.038, fepsilon);
    ASSERT_NEAR(res[2].real(), -65.28, fepsilon);    ASSERT_NEAR(res[2].imag(), -56.96, fepsilon);
}

TEST_F(MatrixVectorMultiplication_Complex, Multiply_ComplexDoubleMatrix_ComplexDoubleVector)
{
    const auto mat = Matrix<std::complex<double>>({{1.23,2.12}, {3.45,4.75}, {5.24,6.86},
                                                   {7.32,8.62}, {9.84,2.63}, {1.87,4.13},
                                                   {3.64,4.17}, {5.27,7.17}, {3.94,1.93}},
                                                  3,3);


    const auto vec = Vector<std::complex<double>>({{1.2,-2.4}, {-5.6,3.7}, {-8.1,-4.3}});

    const auto res = mat * vec;
    ASSERT_NEAR(res[0].real(), -43.277, epsilon);    ASSERT_NEAR(res[0].imag(), -92.341, epsilon);
    ASSERT_NEAR(res[1].real(), -32.751, epsilon);    ASSERT_NEAR(res[1].imag(), -27.038, epsilon);
    ASSERT_NEAR(res[2].real(), -65.28, epsilon);    ASSERT_NEAR(res[2].imag(), -56.96, epsilon);
}