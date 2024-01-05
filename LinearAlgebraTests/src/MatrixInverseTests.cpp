//
// Created by dorian on 03.01.2024.
// stoicadorian@gmail.com
//
#include "gtest/gtest.h"
#include "Matrix.hpp"
#include "MatrixHelpers.hpp"

using namespace LinearAlgebra::Matrix;
using namespace LinearAlgebra::Vector;

class MatrixInverseTests : public ::testing::Test
{

protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

    std::vector<int>    dummyIntData;
    std::vector<double> dummyDoubleData;
    std::vector<float>  dummyFloatData;
};


TEST_F(MatrixInverseTests, Inverse_Strang_Chapter_1_6_example)
{
    const auto data = std::vector<int>{2,1,1,
                                             4,-6,0,
                                             -2,7,2};

    const auto mat  = Matrix<int>(data, 3,3);
    const auto inverse= mat.inverse().value();

    const double epsilon = 1e-9;
    ASSERT_EQ(inverse.rows(), 3); ASSERT_EQ(inverse.cols(), 3);
    ASSERT_NEAR(inverse(0,0), 12./16, epsilon);     ASSERT_NEAR(inverse(0,1), -5./16, epsilon);     ASSERT_NEAR(inverse(0,2), -6./16, epsilon);
    ASSERT_NEAR(inverse(1,0), 4./8, epsilon);       ASSERT_NEAR(inverse(1,1), -3./8, epsilon);      ASSERT_NEAR(inverse(1,2), -2./8, epsilon);
    ASSERT_NEAR(inverse(2,0), -1, epsilon);         ASSERT_NEAR(inverse(2,1), 1, epsilon);          ASSERT_NEAR(inverse(2,2), 1, epsilon);

    const auto mat_times_mat_inverse = mat.multiply(inverse);
    ASSERT_NEAR(mat_times_mat_inverse(0,0), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,2), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(1,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,1), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,2), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(2,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,2), 1, epsilon);

    const auto mat_inverse_times_mat = inverse.multiply(mat);
    ASSERT_NEAR(mat_inverse_times_mat(0,0), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,2), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(1,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,1), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,2), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(2,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,2), 1, epsilon);
}

TEST_F(MatrixInverseTests, Inverse_Strang_Chapter_1_6_Problem_1_a_row_swap)
{
    const auto data = std::vector<int>{0,2,
                                       3,0};

    const auto mat      = Matrix<int>(data, 2, 2);
    const auto inverse= mat.inverse().value();

    const double epsilon = 1e-9;

    ASSERT_EQ(inverse.rows(), 2); ASSERT_EQ(inverse.cols(), 2);
    ASSERT_NEAR(inverse(0,0), 0, epsilon);      ASSERT_NEAR(inverse(0,1), 1./3, epsilon);
    ASSERT_NEAR(inverse(1,0), 1./2, epsilon);   ASSERT_NEAR(inverse(1,1), 0, epsilon);

    const auto mat_times_mat_inverse = mat.multiply(inverse);
    ASSERT_NEAR(mat_times_mat_inverse(0,0), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,1), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(1,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,1), 1, epsilon);

    const auto mat_inverse_times_mat = inverse.multiply(mat);
    ASSERT_NEAR(mat_inverse_times_mat(0,0), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,1), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(1,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,1), 1, epsilon);
}

TEST_F(MatrixInverseTests, Inverse_Strang_Chapter_1_6_Problem_1_b)
{
    const auto data = std::vector<int>{2,0,
                                       4,2};

    const auto mat      = Matrix<int>(data, 2, 2);
    const auto inverse= mat.inverse().value();

    const double epsilon = 1e-9;

    ASSERT_EQ(inverse.rows(), 2); ASSERT_EQ(inverse.cols(), 2);
    ASSERT_NEAR(inverse(0,0), 1./2, epsilon);   ASSERT_NEAR(inverse(0,1), 0, epsilon);
    ASSERT_NEAR(inverse(1,0), -1, epsilon);     ASSERT_NEAR(inverse(1,1), 1./2, epsilon);

    const auto mat_times_mat_inverse = mat.multiply(inverse);
    ASSERT_NEAR(mat_times_mat_inverse(0,0), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,1), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(1,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,1), 1, epsilon);

    const auto mat_inverse_times_mat = inverse.multiply(mat);
    ASSERT_NEAR(mat_inverse_times_mat(0,0), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,1), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(1,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,1), 1, epsilon);
}

TEST_F(MatrixInverseTests, Inverse_Strang_Chapter_1_6_Problem_2_a_inverse_of_permutation)
{
    const auto data = std::vector<int>{0,0,1,
                                       0,1,0,
                                       1,0,0};

    const auto mat  = Matrix<int>(data, 3,3);
    const auto inverse= mat.inverse().value();

    const double epsilon = 1e-9;
    ASSERT_EQ(inverse.rows(), 3); ASSERT_EQ(inverse.cols(), 3);

    // The inverse of a permutation matrix is its inverse.
    ASSERT_NEAR(inverse(0,0), 0, epsilon);  ASSERT_NEAR(inverse(0,1), 0, epsilon);  ASSERT_NEAR(inverse(0,2), 1, epsilon);
    ASSERT_NEAR(inverse(1,0), 0, epsilon);  ASSERT_NEAR(inverse(1,1), 1, epsilon);  ASSERT_NEAR(inverse(1,2), 0, epsilon);
    ASSERT_NEAR(inverse(2,0), 1, epsilon);  ASSERT_NEAR(inverse(2,1), 0, epsilon);  ASSERT_NEAR(inverse(2,2), 0, epsilon);

    const auto mat_times_mat_inverse = mat.multiply(inverse);
    ASSERT_NEAR(mat_times_mat_inverse(0,0), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,2), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(1,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,1), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,2), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(2,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,2), 1, epsilon);

    const auto mat_inverse_times_mat = inverse.multiply(mat);
    ASSERT_NEAR(mat_inverse_times_mat(0,0), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,2), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(1,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,1), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,2), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(2,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,2), 1, epsilon);
}

TEST_F(MatrixInverseTests, Inverse_Strang_Chapter_1_6_Problem_2_b_inverse_of_permutation)
{
    const auto data = std::vector<int>{0,0,1,
                                       1,0,0,
                                       0,1,0};

    const auto mat  = Matrix<int>(data, 3,3);
    const auto inverse= mat.inverse().value();

    const double epsilon = 1e-9;
    ASSERT_EQ(inverse.rows(), 3); ASSERT_EQ(inverse.cols(), 3);

    // The inverse of a permutation matrix is its inverse.
    ASSERT_NEAR(inverse(0,0), 0, epsilon);  ASSERT_NEAR(inverse(0,1), 1, epsilon);  ASSERT_NEAR(inverse(0,2), 0, epsilon);
    ASSERT_NEAR(inverse(1,0), 0, epsilon);  ASSERT_NEAR(inverse(1,1), 0, epsilon);  ASSERT_NEAR(inverse(1,2), 1, epsilon);
    ASSERT_NEAR(inverse(2,0), 1, epsilon);  ASSERT_NEAR(inverse(2,1), 0, epsilon);  ASSERT_NEAR(inverse(2,2), 0, epsilon);

    const auto mat_times_mat_inverse = mat.multiply(inverse);
    ASSERT_NEAR(mat_times_mat_inverse(0,0), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,2), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(1,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,1), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,2), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(2,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,2), 1, epsilon);

    const auto mat_inverse_times_mat = inverse.multiply(mat);
    ASSERT_NEAR(mat_inverse_times_mat(0,0), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,2), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(1,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,1), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,2), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(2,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,2), 1, epsilon);
}

TEST_F(MatrixInverseTests, Inverse_Strang_Chapter_1_6_Problem_6_a)
{
    const auto data = std::vector<int>{1,0,0,
                                       1,1,1,
                                       0,0,1};

    const auto mat  = Matrix<int>(data, 3,3);
    const auto inverse= mat.inverse().value();

    const double epsilon = 1e-9;
    ASSERT_EQ(inverse.rows(), 3); ASSERT_EQ(inverse.cols(), 3);

    ASSERT_NEAR(inverse(0,0), 1, epsilon);      ASSERT_NEAR(inverse(0,1), 0, epsilon);  ASSERT_NEAR(inverse(0,2), 0, epsilon);
    ASSERT_NEAR(inverse(1,0), -1, epsilon);     ASSERT_NEAR(inverse(1,1), 1, epsilon);  ASSERT_NEAR(inverse(1,2), -1, epsilon);
    ASSERT_NEAR(inverse(2,0), 0, epsilon);      ASSERT_NEAR(inverse(2,1), 0, epsilon);  ASSERT_NEAR(inverse(2,2), 1, epsilon);

    const auto mat_times_mat_inverse = mat.multiply(inverse);
    ASSERT_NEAR(mat_times_mat_inverse(0,0), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,2), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(1,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,1), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,2), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(2,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,2), 1, epsilon);

    const auto mat_inverse_times_mat = inverse.multiply(mat);
    ASSERT_NEAR(mat_inverse_times_mat(0,0), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,2), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(1,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,1), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,2), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(2,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,2), 1, epsilon);
}

TEST_F(MatrixInverseTests, Inverse_Strang_Chapter_1_6_Problem_6_b)
{
    const auto data = std::vector<int>{2,-1,0,
                                       -1,2,-1,
                                       0,-1,2};

    const auto mat  = Matrix<int>(data, 3,3);
    const auto inverse= mat.inverse().value();

    const double epsilon = 1e-9;
    ASSERT_EQ(inverse.rows(), 3); ASSERT_EQ(inverse.cols(), 3);

    ASSERT_NEAR(inverse(0,0), 3./4, epsilon);   ASSERT_NEAR(inverse(0,1), 1./2, epsilon);   ASSERT_NEAR(inverse(0,2), 1./4, epsilon);
    ASSERT_NEAR(inverse(1,0), 1./2, epsilon);   ASSERT_NEAR(inverse(1,1), 1, epsilon);      ASSERT_NEAR(inverse(1,2), 1./2, epsilon);
    ASSERT_NEAR(inverse(2,0), 1./4, epsilon);   ASSERT_NEAR(inverse(2,1), 1./2, epsilon);   ASSERT_NEAR(inverse(2,2), 3./4, epsilon);

    const auto mat_times_mat_inverse = mat.multiply(inverse);
    ASSERT_NEAR(mat_times_mat_inverse(0,0), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,2), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(1,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,1), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,2), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(2,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,2), 1, epsilon);

    const auto mat_inverse_times_mat = inverse.multiply(mat);
    ASSERT_NEAR(mat_inverse_times_mat(0,0), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,2), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(1,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,1), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,2), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(2,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,2), 1, epsilon);
}

TEST_F(MatrixInverseTests, Inverse_Strang_Chapter_1_6_Problem_6_c)
{
    const auto data = std::vector<int>{0,0,1,
                                       0,1,1,
                                       1,1,1};

    const auto mat  = Matrix<int>(data, 3,3);
    const auto inverse= mat.inverse().value();

    const double epsilon = 1e-9;
    ASSERT_EQ(inverse.rows(), 3); ASSERT_EQ(inverse.cols(), 3);

    ASSERT_NEAR(inverse(0,0), 0, epsilon);  ASSERT_NEAR(inverse(0,1), -1, epsilon); ASSERT_NEAR(inverse(0,2), 1, epsilon);
    ASSERT_NEAR(inverse(1,0), -1, epsilon); ASSERT_NEAR(inverse(1,1), 1, epsilon);  ASSERT_NEAR(inverse(1,2), 0, epsilon);
    ASSERT_NEAR(inverse(2,0), 1, epsilon);  ASSERT_NEAR(inverse(2,1), 0, epsilon);  ASSERT_NEAR(inverse(2,2), 0, epsilon);

    const auto mat_times_mat_inverse = mat.multiply(inverse);
    ASSERT_NEAR(mat_times_mat_inverse(0,0), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,2), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(1,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,1), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,2), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(2,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,2), 1, epsilon);

    const auto mat_inverse_times_mat = inverse.multiply(mat);
    ASSERT_NEAR(mat_inverse_times_mat(0,0), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,2), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(1,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,1), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,2), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(2,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,2), 1, epsilon);
}

TEST_F(MatrixInverseTests, Inverse_Strang_Chapter_1_6_Problem_10_a)
{
    const auto data = std::vector<int>{0,0,0,1,
                                       0,0,2,0,
                                       0,3,0,0,
                                       4,0,0,0};

    const auto mat  = Matrix<int>(data, 4,4);
    const auto inverse= mat.inverse().value();

    const double epsilon = 1e-9;
    ASSERT_EQ(inverse.rows(), 4); ASSERT_EQ(inverse.cols(), 4);

    ASSERT_NEAR(inverse(0,0), 0, epsilon);  ASSERT_NEAR(inverse(0,1), 0, epsilon);      ASSERT_NEAR(inverse(0,2), 0, epsilon);      ASSERT_NEAR(inverse(0,3), 1./4, epsilon);
    ASSERT_NEAR(inverse(1,0), 0, epsilon);  ASSERT_NEAR(inverse(1,1), 0, epsilon);      ASSERT_NEAR(inverse(1,2), 1./3, epsilon);   ASSERT_NEAR(inverse(1,3), 0, epsilon);
    ASSERT_NEAR(inverse(2,0), 0, epsilon);  ASSERT_NEAR(inverse(2,1), 1./2, epsilon);   ASSERT_NEAR(inverse(2,2), 0, epsilon);      ASSERT_NEAR(inverse(2,3), 0, epsilon);
    ASSERT_NEAR(inverse(3,0), 1, epsilon);  ASSERT_NEAR(inverse(3,1), 0, epsilon);      ASSERT_NEAR(inverse(3,2), 0, epsilon);      ASSERT_NEAR(inverse(3,3), 0, epsilon);

    const auto mat_times_mat_inverse = mat.multiply(inverse);
    ASSERT_NEAR(mat_times_mat_inverse(0,0), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,2), 0, epsilon);  ASSERT_NEAR(mat_times_mat_inverse(0,3), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(1,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,1), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,2), 0, epsilon);  ASSERT_NEAR(mat_times_mat_inverse(1,3), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(2,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,2), 1, epsilon);  ASSERT_NEAR(mat_times_mat_inverse(2,3), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(3,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(3,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(3,2), 0, epsilon);  ASSERT_NEAR(mat_times_mat_inverse(3,3), 1, epsilon);

    const auto mat_inverse_times_mat = inverse.multiply(mat);
    ASSERT_NEAR(mat_inverse_times_mat(0,0), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,2), 0, epsilon);  ASSERT_NEAR(mat_inverse_times_mat(0,3), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(1,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,1), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,2), 0, epsilon);  ASSERT_NEAR(mat_inverse_times_mat(1,3), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(2,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,2), 1, epsilon);  ASSERT_NEAR(mat_inverse_times_mat(2,3), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(3,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(3,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(3,2), 0, epsilon);  ASSERT_NEAR(mat_inverse_times_mat(3,3), 1, epsilon);
}

TEST_F(MatrixInverseTests, Inverse_Strang_Chapter_1_6_Problem_10_b)
{
    const auto data = std::vector<double>{1,0,0,0,
                                       -1./2,   1,      0,      0,
                                       0,       -2./3,  1,      0,
                                       0,       0,      -3./4,  1};

    const auto mat  = Matrix<double>(data, 4,4);
    const auto inverse= mat.inverse().value();

    const double epsilon = 1e-9;
    ASSERT_EQ(inverse.rows(), 4); ASSERT_EQ(inverse.cols(), 4);

    ASSERT_NEAR(inverse(0,0), 1, epsilon);      ASSERT_NEAR(inverse(0,1), 0, epsilon);      ASSERT_NEAR(inverse(0,2), 0, epsilon);      ASSERT_NEAR(inverse(0,3), 0, epsilon);
    ASSERT_NEAR(inverse(1,0), 1./2, epsilon);   ASSERT_NEAR(inverse(1,1), 1, epsilon);      ASSERT_NEAR(inverse(1,2), 0, epsilon);      ASSERT_NEAR(inverse(1,3), 0, epsilon);
    ASSERT_NEAR(inverse(2,0), 1./3, epsilon);   ASSERT_NEAR(inverse(2,1), 2./3, epsilon);   ASSERT_NEAR(inverse(2,2), 1, epsilon);      ASSERT_NEAR(inverse(2,3), 0, epsilon);
    ASSERT_NEAR(inverse(3,0), 1./4, epsilon);   ASSERT_NEAR(inverse(3,1), 1./2, epsilon);   ASSERT_NEAR(inverse(3,2), 3./4, epsilon);   ASSERT_NEAR(inverse(3,3), 1, epsilon);

    const auto mat_times_mat_inverse = mat.multiply(inverse);
    ASSERT_NEAR(mat_times_mat_inverse(0,0), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,2), 0, epsilon);  ASSERT_NEAR(mat_times_mat_inverse(0,3), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(1,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,1), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,2), 0, epsilon);  ASSERT_NEAR(mat_times_mat_inverse(1,3), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(2,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,2), 1, epsilon);  ASSERT_NEAR(mat_times_mat_inverse(2,3), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(3,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(3,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(3,2), 0, epsilon);  ASSERT_NEAR(mat_times_mat_inverse(3,3), 1, epsilon);

    const auto mat_inverse_times_mat = inverse.multiply(mat);
    ASSERT_NEAR(mat_inverse_times_mat(0,0), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,2), 0, epsilon);  ASSERT_NEAR(mat_inverse_times_mat(0,3), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(1,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,1), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,2), 0, epsilon);  ASSERT_NEAR(mat_inverse_times_mat(1,3), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(2,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,2), 1, epsilon);  ASSERT_NEAR(mat_inverse_times_mat(2,3), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(3,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(3,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(3,2), 0, epsilon);  ASSERT_NEAR(mat_inverse_times_mat(3,3), 1, epsilon);
}

TEST_F(MatrixInverseTests, Inverse_Strang_Chapter_1_6_Problem_20)
{
    const auto data = std::vector<double>{1,       0,      0,      0,
                                          1./4,    1,      0,      0,
                                          1./3,    1./3,   1,      0,
                                          1./2,    1./2,   1./2,   1};

    const auto mat  = Matrix<double>(data, 4,4);
    const auto inverse= mat.inverse().value();

    const double epsilon = 1e-9;
    ASSERT_EQ(inverse.rows(), 4); ASSERT_EQ(inverse.cols(), 4);

    ASSERT_NEAR(inverse(0,0), 1, epsilon);          ASSERT_NEAR(inverse(0,1), 0, epsilon);          ASSERT_NEAR(inverse(0,2), 0, epsilon);      ASSERT_NEAR(inverse(0,3), 0, epsilon);
    ASSERT_NEAR(inverse(1,0), -1./4, epsilon);      ASSERT_NEAR(inverse(1,1), 1, epsilon);          ASSERT_NEAR(inverse(1,2), 0, epsilon);      ASSERT_NEAR(inverse(1,3), 0, epsilon);
    ASSERT_NEAR(inverse(2,0), -1./4, epsilon);      ASSERT_NEAR(inverse(2,1), -1./3, epsilon);      ASSERT_NEAR(inverse(2,2), 1, epsilon);      ASSERT_NEAR(inverse(2,3), 0, epsilon);
    ASSERT_NEAR(inverse(3,0), -1./4, epsilon);      ASSERT_NEAR(inverse(3,1), -1./3, epsilon);      ASSERT_NEAR(inverse(3,2), -1./2, epsilon);  ASSERT_NEAR(inverse(3,3), 1, epsilon);

    const auto mat_times_mat_inverse = mat.multiply(inverse);
    ASSERT_NEAR(mat_times_mat_inverse(0,0), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,2), 0, epsilon);  ASSERT_NEAR(mat_times_mat_inverse(0,3), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(1,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,1), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,2), 0, epsilon);  ASSERT_NEAR(mat_times_mat_inverse(1,3), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(2,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,2), 1, epsilon);  ASSERT_NEAR(mat_times_mat_inverse(2,3), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(3,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(3,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(3,2), 0, epsilon);  ASSERT_NEAR(mat_times_mat_inverse(3,3), 1, epsilon);

    const auto mat_inverse_times_mat = inverse.multiply(mat);
    ASSERT_NEAR(mat_inverse_times_mat(0,0), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,2), 0, epsilon);  ASSERT_NEAR(mat_inverse_times_mat(0,3), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(1,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,1), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,2), 0, epsilon);  ASSERT_NEAR(mat_inverse_times_mat(1,3), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(2,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,2), 1, epsilon);  ASSERT_NEAR(mat_inverse_times_mat(2,3), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(3,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(3,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(3,2), 0, epsilon);  ASSERT_NEAR(mat_inverse_times_mat(3,3), 1, epsilon);
}

TEST_F(MatrixInverseTests, Inverse_Strang_Chapter_1_6_Problem_22_a)
{
    const auto data = std::vector<int>{0,3,
                                       4,6};

    const auto mat      = Matrix<int>(data, 2, 2);
    const auto inverse= mat.inverse().value();

    const double epsilon = 1e-9;

    ASSERT_EQ(inverse.rows(), 2); ASSERT_EQ(inverse.cols(), 2);
    ASSERT_NEAR(inverse(0,0), -1./2, epsilon);   ASSERT_NEAR(inverse(0,1), 1./4, epsilon);
    ASSERT_NEAR(inverse(1,0), 1./3, epsilon);     ASSERT_NEAR(inverse(1,1), 0, epsilon);

    const auto mat_times_mat_inverse = mat.multiply(inverse);
    ASSERT_NEAR(mat_times_mat_inverse(0,0), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,1), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(1,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,1), 1, epsilon);

    const auto mat_inverse_times_mat = inverse.multiply(mat);
    ASSERT_NEAR(mat_inverse_times_mat(0,0), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,1), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(1,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,1), 1, epsilon);
}

TEST_F(MatrixInverseTests, Inverse_Strang_Chapter_1_6_Problem_22_b)
{
    const auto data = std::vector<int>{3,4,
                                       5,7};

    const auto mat      = Matrix<int>(data, 2, 2);
    const auto inverse= mat.inverse().value();

    const double epsilon = 1e-9;

    ASSERT_EQ(inverse.rows(), 2); ASSERT_EQ(inverse.cols(), 2);
    ASSERT_NEAR(inverse(0,0), 7, epsilon);   ASSERT_NEAR(inverse(0,1), -4, epsilon);
    ASSERT_NEAR(inverse(1,0), -5, epsilon);     ASSERT_NEAR(inverse(1,1), 3, epsilon);

    const auto mat_times_mat_inverse = mat.multiply(inverse);
    ASSERT_NEAR(mat_times_mat_inverse(0,0), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,1), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(1,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,1), 1, epsilon);

    const auto mat_inverse_times_mat = inverse.multiply(mat);
    ASSERT_NEAR(mat_inverse_times_mat(0,0), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,1), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(1,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,1), 1, epsilon);
}

TEST_F(MatrixInverseTests, Inverse_Strang_Chapter_1_6_Problem_23)
{
    const auto data = std::vector<int>{10,20,
                                       20,50};

    const auto mat      = Matrix<int>(data, 2, 2);
    const auto inverse= mat.inverse().value();

    const double epsilon = 1e-9;

    ASSERT_EQ(inverse.rows(), 2); ASSERT_EQ(inverse.cols(), 2);
    ASSERT_NEAR(inverse(0,0), 1./2, epsilon);   ASSERT_NEAR(inverse(0,1), -1./5, epsilon);
    ASSERT_NEAR(inverse(1,0), -1./5, epsilon);     ASSERT_NEAR(inverse(1,1), 1./10, epsilon);

    const auto mat_times_mat_inverse = mat.multiply(inverse);
    ASSERT_NEAR(mat_times_mat_inverse(0,0), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,1), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(1,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,1), 1, epsilon);

    const auto mat_inverse_times_mat = inverse.multiply(mat);
    ASSERT_NEAR(mat_inverse_times_mat(0,0), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,1), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(1,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,1), 1, epsilon);
}

TEST_F(MatrixInverseTests, Inverse_Strang_Chapter_1_6_Problem_32)
{
    const auto data = std::vector<double>{4,    -1,   -1,     -1,
                                                           -1,    4,    -1,     -1,
                                                           -1,    -1,   4,      -1,
                                                           -1,    -1,   -1,     4};

    const auto mat  = Matrix<double>(data, 4,4);
    const auto inverse= mat.inverse().value();

    const double epsilon = 1e-9;
    ASSERT_EQ(inverse.rows(), 4); ASSERT_EQ(inverse.cols(), 4);

    ASSERT_NEAR(inverse(0,0), 2./5, epsilon);      ASSERT_NEAR(inverse(0,1), 1./5, epsilon);    ASSERT_NEAR(inverse(0,2), 1./5, epsilon);   ASSERT_NEAR(inverse(0,3), 1./5, epsilon);
    ASSERT_NEAR(inverse(1,0), 1./5, epsilon);      ASSERT_NEAR(inverse(1,1), 2./5, epsilon);    ASSERT_NEAR(inverse(1,2), 1./5, epsilon);   ASSERT_NEAR(inverse(1,3), 1./5, epsilon);
    ASSERT_NEAR(inverse(2,0), 1./5, epsilon);      ASSERT_NEAR(inverse(2,1), 1./5, epsilon);    ASSERT_NEAR(inverse(2,2), 2./5, epsilon);   ASSERT_NEAR(inverse(2,3), 1./5, epsilon);
    ASSERT_NEAR(inverse(3,0), 1./5, epsilon);      ASSERT_NEAR(inverse(3,1), 1./5, epsilon);    ASSERT_NEAR(inverse(3,2), 1./5, epsilon);   ASSERT_NEAR(inverse(3,3), 2./5, epsilon);

    const auto mat_times_mat_inverse = mat.multiply(inverse);
    ASSERT_NEAR(mat_times_mat_inverse(0,0), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,2), 0, epsilon);  ASSERT_NEAR(mat_times_mat_inverse(0,3), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(1,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,1), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,2), 0, epsilon);  ASSERT_NEAR(mat_times_mat_inverse(1,3), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(2,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,2), 1, epsilon);  ASSERT_NEAR(mat_times_mat_inverse(2,3), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(3,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(3,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(3,2), 0, epsilon);  ASSERT_NEAR(mat_times_mat_inverse(3,3), 1, epsilon);

    const auto mat_inverse_times_mat = inverse.multiply(mat);
    ASSERT_NEAR(mat_inverse_times_mat(0,0), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,2), 0, epsilon);  ASSERT_NEAR(mat_inverse_times_mat(0,3), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(1,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,1), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,2), 0, epsilon);  ASSERT_NEAR(mat_inverse_times_mat(1,3), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(2,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,2), 1, epsilon);  ASSERT_NEAR(mat_inverse_times_mat(2,3), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(3,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(3,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(3,2), 0, epsilon);  ASSERT_NEAR(mat_inverse_times_mat(3,3), 1, epsilon);
}

TEST_F(MatrixInverseTests, Inverse_Strang_Chapter_1_6_Problem_35_a)
{
    const auto data = std::vector<int>{1,3,
                                       2,7};

    const auto mat      = Matrix<int>(data, 2, 2);
    const auto inverse= mat.inverse().value();

    const double epsilon = 1e-9;

    ASSERT_EQ(inverse.rows(), 2); ASSERT_EQ(inverse.cols(), 2);
    ASSERT_NEAR(inverse(0,0), 7, epsilon);   ASSERT_NEAR(inverse(0,1), -3, epsilon);
    ASSERT_NEAR(inverse(1,0), -2, epsilon);     ASSERT_NEAR(inverse(1,1), 1, epsilon);

    const auto mat_times_mat_inverse = mat.multiply(inverse);
    ASSERT_NEAR(mat_times_mat_inverse(0,0), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,1), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(1,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,1), 1, epsilon);

    const auto mat_inverse_times_mat = inverse.multiply(mat);
    ASSERT_NEAR(mat_inverse_times_mat(0,0), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,1), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(1,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,1), 1, epsilon);
}

TEST_F(MatrixInverseTests, Inverse_Strang_Chapter_1_6_Problem_35_b)
{
    const auto data = std::vector<int>{1,4,
                                       3,9};

    const auto mat      = Matrix<int>(data, 2, 2);
    const auto inverse= mat.inverse().value();

    const double epsilon = 1e-9;

    ASSERT_EQ(inverse.rows(), 2); ASSERT_EQ(inverse.cols(), 2);
    ASSERT_NEAR(inverse(0,0), -3, epsilon);   ASSERT_NEAR(inverse(0,1), 4./3, epsilon);
    ASSERT_NEAR(inverse(1,0), 1, epsilon);     ASSERT_NEAR(inverse(1,1), -1./3, epsilon);

    const auto mat_times_mat_inverse = mat.multiply(inverse);
    ASSERT_NEAR(mat_times_mat_inverse(0,0), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,1), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(1,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,1), 1, epsilon);

    const auto mat_inverse_times_mat = inverse.multiply(mat);
    ASSERT_NEAR(mat_inverse_times_mat(0,0), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,1), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(1,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,1), 1, epsilon);
}

TEST_F(MatrixInverseTests, Inverse_Strang_Chapter_1_6_Problem_36)
{
    const auto data = std::vector<int>{2,1,0,
                                       1,2,1,
                                       0,1,2};

    const auto mat  = Matrix<int>(data, 3,3);
    const auto inverse= mat.inverse().value();

    const double epsilon = 1e-9;
    ASSERT_EQ(inverse.rows(), 3); ASSERT_EQ(inverse.cols(), 3);

    ASSERT_NEAR(inverse(0,0), 3./4, epsilon);  ASSERT_NEAR(inverse(0,1), -1./2, epsilon);   ASSERT_NEAR(inverse(0,2), 1./4, epsilon);
    ASSERT_NEAR(inverse(1,0), -1./2, epsilon); ASSERT_NEAR(inverse(1,1), 1, epsilon);       ASSERT_NEAR(inverse(1,2), -1./2, epsilon);
    ASSERT_NEAR(inverse(2,0), 1./4, epsilon);  ASSERT_NEAR(inverse(2,1), -1./2, epsilon);   ASSERT_NEAR(inverse(2,2), 3./4, epsilon);

    const auto mat_times_mat_inverse = mat.multiply(inverse);
    ASSERT_NEAR(mat_times_mat_inverse(0,0), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,2), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(1,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,1), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,2), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(2,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,2), 1, epsilon);

    const auto mat_inverse_times_mat = inverse.multiply(mat);
    ASSERT_NEAR(mat_inverse_times_mat(0,0), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,2), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(1,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,1), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,2), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(2,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,2), 1, epsilon);
}

TEST_F(MatrixInverseTests, Inverse_Strang_Chapter_1_6_Problem_38_a)
{
    const auto data = std::vector<int>{1,0,0,
                                       2,1,3,
                                       0,0,1};

    const auto mat  = Matrix<int>(data, 3,3);
    const auto inverse= mat.inverse().value();

    const double epsilon = 1e-9;
    ASSERT_EQ(inverse.rows(), 3); ASSERT_EQ(inverse.cols(), 3);

    ASSERT_NEAR(inverse(0,0), 1, epsilon);  ASSERT_NEAR(inverse(0,1), 0, epsilon);      ASSERT_NEAR(inverse(0,2), 0, epsilon);
    ASSERT_NEAR(inverse(1,0), -2, epsilon); ASSERT_NEAR(inverse(1,1), 1, epsilon);      ASSERT_NEAR(inverse(1,2), -3, epsilon);
    ASSERT_NEAR(inverse(2,0), 0, epsilon);  ASSERT_NEAR(inverse(2,1), 0, epsilon);      ASSERT_NEAR(inverse(2,2), 1, epsilon);

    const auto mat_times_mat_inverse = mat.multiply(inverse);
    ASSERT_NEAR(mat_times_mat_inverse(0,0), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,2), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(1,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,1), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,2), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(2,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,2), 1, epsilon);

    const auto mat_inverse_times_mat = inverse.multiply(mat);
    ASSERT_NEAR(mat_inverse_times_mat(0,0), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,2), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(1,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,1), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,2), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(2,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,2), 1, epsilon);
}

TEST_F(MatrixInverseTests, Inverse_Strang_Chapter_1_6_Problem_38_b)
{
    const auto data = std::vector<int>{1,1,1,
                                       1,2,2,
                                       1,2,3};

    const auto mat  = Matrix<int>(data, 3,3);
    const auto inverse= mat.inverse().value();

    const double epsilon = 1e-9;
    ASSERT_EQ(inverse.rows(), 3); ASSERT_EQ(inverse.cols(), 3);

    ASSERT_NEAR(inverse(0,0), 2, epsilon);  ASSERT_NEAR(inverse(0,1), -1, epsilon);      ASSERT_NEAR(inverse(0,2), 0, epsilon);
    ASSERT_NEAR(inverse(1,0), -1, epsilon); ASSERT_NEAR(inverse(1,1), 2, epsilon);      ASSERT_NEAR(inverse(1,2), -1, epsilon);
    ASSERT_NEAR(inverse(2,0), 0, epsilon);  ASSERT_NEAR(inverse(2,1), -1, epsilon);      ASSERT_NEAR(inverse(2,2), 1, epsilon);

    const auto mat_times_mat_inverse = mat.multiply(inverse);
    ASSERT_NEAR(mat_times_mat_inverse(0,0), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,2), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(1,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,1), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,2), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(2,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,2), 1, epsilon);

    const auto mat_inverse_times_mat = inverse.multiply(mat);
    ASSERT_NEAR(mat_inverse_times_mat(0,0), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,2), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(1,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,1), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,2), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(2,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,2), 1, epsilon);
}

TEST_F(MatrixInverseTests, Inverse_Strang_Chapter_1_6_Problem_39)
{
    const auto data = std::vector<int>{0,2,
                                       2,2};

    const auto mat      = Matrix<int>(data, 2, 2);
    const auto inverse= mat.inverse().value();

    const double epsilon = 1e-9;

    ASSERT_EQ(inverse.rows(), 2); ASSERT_EQ(inverse.cols(), 2);
    ASSERT_NEAR(inverse(0,0), -1./2, epsilon);    ASSERT_NEAR(inverse(0,1), 1./2, epsilon);
    ASSERT_NEAR(inverse(1,0), 1./2, epsilon);     ASSERT_NEAR(inverse(1,1), 0, epsilon);

    const auto mat_times_mat_inverse = mat.multiply(inverse);
    ASSERT_NEAR(mat_times_mat_inverse(0,0), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,1), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(1,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,1), 1, epsilon);

    const auto mat_inverse_times_mat = inverse.multiply(mat);
    ASSERT_NEAR(mat_inverse_times_mat(0,0), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,1), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(1,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,1), 1, epsilon);
}

TEST_F(MatrixInverseTests, Inverse_Strang_Chapter_1_6_Problem_43)
{
    const auto data = std::vector<double>{1,    -1,   1,     -1,
                                          0,    1,    -1,     1,
                                          0,    0,     1,     -1,
                                          0,    0,     0,     1};

    const auto mat  = Matrix<double>(data, 4,4);
    const auto inverse= mat.inverse().value();

    const double epsilon = 1e-9;
    ASSERT_EQ(inverse.rows(), 4); ASSERT_EQ(inverse.cols(), 4);

    ASSERT_NEAR(inverse(0,0), 1, epsilon);      ASSERT_NEAR(inverse(0,1), 1, epsilon);    ASSERT_NEAR(inverse(0,2), 0, epsilon);   ASSERT_NEAR(inverse(0,3), 0, epsilon);
    ASSERT_NEAR(inverse(1,0), 0, epsilon);      ASSERT_NEAR(inverse(1,1), 1, epsilon);    ASSERT_NEAR(inverse(1,2), 1, epsilon);   ASSERT_NEAR(inverse(1,3), 0, epsilon);
    ASSERT_NEAR(inverse(2,0), 0, epsilon);      ASSERT_NEAR(inverse(2,1), 0, epsilon);    ASSERT_NEAR(inverse(2,2), 1, epsilon);   ASSERT_NEAR(inverse(2,3), 1, epsilon);
    ASSERT_NEAR(inverse(3,0), 0, epsilon);      ASSERT_NEAR(inverse(3,1), 0, epsilon);    ASSERT_NEAR(inverse(3,2), 0, epsilon);   ASSERT_NEAR(inverse(3,3), 1, epsilon);

    const auto mat_times_mat_inverse = mat.multiply(inverse);
    ASSERT_NEAR(mat_times_mat_inverse(0,0), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,2), 0, epsilon);  ASSERT_NEAR(mat_times_mat_inverse(0,3), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(1,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,1), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,2), 0, epsilon);  ASSERT_NEAR(mat_times_mat_inverse(1,3), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(2,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,2), 1, epsilon);  ASSERT_NEAR(mat_times_mat_inverse(2,3), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(3,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(3,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(3,2), 0, epsilon);  ASSERT_NEAR(mat_times_mat_inverse(3,3), 1, epsilon);

    const auto mat_inverse_times_mat = inverse.multiply(mat);
    ASSERT_NEAR(mat_inverse_times_mat(0,0), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,2), 0, epsilon);  ASSERT_NEAR(mat_inverse_times_mat(0,3), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(1,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,1), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,2), 0, epsilon);  ASSERT_NEAR(mat_inverse_times_mat(1,3), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(2,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,2), 1, epsilon);  ASSERT_NEAR(mat_inverse_times_mat(2,3), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(3,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(3,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(3,2), 0, epsilon);  ASSERT_NEAR(mat_inverse_times_mat(3,3), 1, epsilon);
}

TEST_F(MatrixInverseTests, Inverse_Strang_Chapter_1_6_Problem_71)
{
    const auto data = std::vector<double>{1,        0,     0,      0,
                                          -1./2,    1,      0,      0,
                                          0,        -2./3,  1,      0,
                                          0,        0,      -3./4,  1};

    const auto mat  = Matrix<double>(data, 4,4);
    const auto inverse= mat.inverse().value();

    const double epsilon = 1e-9;
    ASSERT_EQ(inverse.rows(), 4); ASSERT_EQ(inverse.cols(), 4);

    ASSERT_NEAR(inverse(0,0), 1, epsilon);          ASSERT_NEAR(inverse(0,1), 0, epsilon);      ASSERT_NEAR(inverse(0,2), 0, epsilon);      ASSERT_NEAR(inverse(0,3), 0, epsilon);
    ASSERT_NEAR(inverse(1,0), 1./2, epsilon);       ASSERT_NEAR(inverse(1,1), 1, epsilon);      ASSERT_NEAR(inverse(1,2), 0, epsilon);      ASSERT_NEAR(inverse(1,3), 0, epsilon);
    ASSERT_NEAR(inverse(2,0), 1./3, epsilon);       ASSERT_NEAR(inverse(2,1), 2./3, epsilon);   ASSERT_NEAR(inverse(2,2), 1, epsilon);      ASSERT_NEAR(inverse(2,3), 0, epsilon);
    ASSERT_NEAR(inverse(3,0), 1./4, epsilon);       ASSERT_NEAR(inverse(3,1), 2./4, epsilon);   ASSERT_NEAR(inverse(3,2), 3./4, epsilon);   ASSERT_NEAR(inverse(3,3), 1, epsilon);

    const auto mat_times_mat_inverse = mat.multiply(inverse);
    ASSERT_NEAR(mat_times_mat_inverse(0,0), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,2), 0, epsilon);  ASSERT_NEAR(mat_times_mat_inverse(0,3), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(1,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,1), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,2), 0, epsilon);  ASSERT_NEAR(mat_times_mat_inverse(1,3), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(2,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,2), 1, epsilon);  ASSERT_NEAR(mat_times_mat_inverse(2,3), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(3,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(3,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(3,2), 0, epsilon);  ASSERT_NEAR(mat_times_mat_inverse(3,3), 1, epsilon);

    const auto mat_inverse_times_mat = inverse.multiply(mat);
    ASSERT_NEAR(mat_inverse_times_mat(0,0), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,2), 0, epsilon);  ASSERT_NEAR(mat_inverse_times_mat(0,3), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(1,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,1), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,2), 0, epsilon);  ASSERT_NEAR(mat_inverse_times_mat(1,3), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(2,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,2), 1, epsilon);  ASSERT_NEAR(mat_inverse_times_mat(2,3), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(3,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(3,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(3,2), 0, epsilon);  ASSERT_NEAR(mat_inverse_times_mat(3,3), 1, epsilon);
}

TEST_F(MatrixInverseTests, Inverse_Singular_Mat)
{
    const auto data = std::vector<int>{1,2,3,
                                       4,5,6,
                                       5,7,9};

    const auto mat  = Matrix<int>(data, 3,3);
    const auto inverse= mat.inverse();

    ASSERT_TRUE(inverse == std::nullopt);
}
