//
// Created by dorian on 03.01.2024.
// stoicadorian@gmail.com
//
#include "gtest/gtest.h"
#include "Matrix.hpp"
#include "MatrixHelpers.hpp"

using namespace LinearAlgebra::Matrix;
using namespace LinearAlgebra::Vector;

class MatrixInverseTests_HilbertTests : public ::testing::Test
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


TEST_F(MatrixInverseTests_HilbertTests, Inverse_Hilbert_3x3)
{
    const auto mat  = hilbert_matrix(3);
    const auto inverse= mat.inverse().value();

    const double epsilon = 1e-9;
    ASSERT_EQ(inverse.rows(), 3); ASSERT_EQ(inverse.cols(), 3);
    ASSERT_NEAR(inverse(0,0), 9, epsilon);      ASSERT_NEAR(inverse(0,1), -36, epsilon);    ASSERT_NEAR(inverse(0,2), 30, epsilon);
    ASSERT_NEAR(inverse(1,0), -36, epsilon);    ASSERT_NEAR(inverse(1,1), 192, epsilon);    ASSERT_NEAR(inverse(1,2), -180, epsilon);
    ASSERT_NEAR(inverse(2,0), 30, epsilon);     ASSERT_NEAR(inverse(2,1), -180, epsilon);   ASSERT_NEAR(inverse(2,2), 180, epsilon);

    const auto mat_times_mat_inverse = mat.multiply(inverse);
    ASSERT_NEAR(mat_times_mat_inverse(0,0), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,2), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(1,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,1), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,2), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(2,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,2), 1, epsilon);

    const auto mat_inverse_times_mat = inverse.multiply(mat);
    ASSERT_NEAR(mat_inverse_times_mat(0,0), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,2), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(1,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,1), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,2), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(2,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,2), 1, epsilon);
}

TEST_F(MatrixInverseTests_HilbertTests, Inverse_Hilbert_4x4)
{
    const auto mat  = hilbert_matrix(4);
    const auto inverse= mat.inverse().value();

    const double epsilon = 1e-9;
    ASSERT_EQ(inverse.rows(), 4); ASSERT_EQ(inverse.cols(), 4);
    ASSERT_NEAR(inverse(0,0), 16, epsilon); ASSERT_NEAR(inverse(0,1), -120, epsilon);       ASSERT_NEAR(inverse(0,2), 240, epsilon);      ASSERT_NEAR(inverse(0,3), -140, epsilon);
    ASSERT_NEAR(inverse(1,0), -120, epsilon);   ASSERT_NEAR(inverse(1,1), 1200, epsilon);   ASSERT_NEAR(inverse(1,2), -2700, epsilon);    ASSERT_NEAR(inverse(1,3), 1680, epsilon);
    ASSERT_NEAR(inverse(2,0), 240, epsilon);    ASSERT_NEAR(inverse(2,1), -2700, epsilon);  ASSERT_NEAR(inverse(2,2), 6480, epsilon);     ASSERT_NEAR(inverse(2,3), -4200, epsilon);
    ASSERT_NEAR(inverse(3,0), -140, epsilon);   ASSERT_NEAR(inverse(3,1), 1680, epsilon);   ASSERT_NEAR(inverse(3,2), -4200, epsilon);    ASSERT_NEAR(inverse(3,3), 2800, epsilon);

    const auto mat_times_mat_inverse = mat.multiply(inverse);
    ASSERT_NEAR(mat_times_mat_inverse(0,0), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,2), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,3), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(1,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,1), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,2), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,3), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(2,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,2), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,3), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(3,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(3,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(3,2), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(3,3), 1, epsilon);

    const auto mat_inverse_times_mat = inverse.multiply(mat);
    ASSERT_NEAR(mat_inverse_times_mat(0,0), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,2), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,3), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(1,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,1), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,2), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,3), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(2,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,2), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,3), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(3,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(3,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(3,2), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(3,3), 1, epsilon);
}

TEST_F(MatrixInverseTests_HilbertTests, Inverse_Hilbert_5x5)
{
    const auto mat  = hilbert_matrix(5);
    const auto inverse= mat.inverse().value();

    const double epsilon = 1e-6;    //only 1e-6 !!
    ASSERT_EQ(inverse.rows(), 5); ASSERT_EQ(inverse.cols(), 5);
    ASSERT_NEAR(inverse(0,0), 25, epsilon);     ASSERT_NEAR(inverse(0,1), -300, epsilon);   ASSERT_NEAR(inverse(0,2), 1050, epsilon);       ASSERT_NEAR(inverse(0,3), -1400, epsilon);      ASSERT_NEAR(inverse(0,4), 630, epsilon);
    ASSERT_NEAR(inverse(1,0), -300, epsilon);   ASSERT_NEAR(inverse(1,1), 4800, epsilon);   ASSERT_NEAR(inverse(1,2), -18900, epsilon);     ASSERT_NEAR(inverse(1,3), 26880, epsilon);      ASSERT_NEAR(inverse(1,4), -12600, epsilon);
    ASSERT_NEAR(inverse(2,0), 1050, epsilon);   ASSERT_NEAR(inverse(2,1), -18900, epsilon); ASSERT_NEAR(inverse(2,2), 79380, epsilon);      ASSERT_NEAR(inverse(2,3), -117600, epsilon);    ASSERT_NEAR(inverse(2,4), 56700, epsilon);
    ASSERT_NEAR(inverse(3,0), -1400, epsilon);  ASSERT_NEAR(inverse(3,1), 26880, epsilon);  ASSERT_NEAR(inverse(3,2), -117600, epsilon);    ASSERT_NEAR(inverse(3,3), 179200, epsilon);     ASSERT_NEAR(inverse(3,4), -88200, epsilon);
    ASSERT_NEAR(inverse(4,0), 630, epsilon);    ASSERT_NEAR(inverse(4,1), -12600, epsilon); ASSERT_NEAR(inverse(4,2), 56700, epsilon);      ASSERT_NEAR(inverse(4,3), -88200, epsilon);     ASSERT_NEAR(inverse(4,4), 44100, epsilon);

    const auto mat_times_mat_inverse = mat.multiply(inverse);
    ASSERT_NEAR(mat_times_mat_inverse(0,0), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,2), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,3), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(0,4), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(1,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,1), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,2), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,3), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(1,4), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(2,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,2), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,3), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(2,4), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(3,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(3,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(3,2), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(3,3), 1, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(3,4), 0, epsilon);
    ASSERT_NEAR(mat_times_mat_inverse(4,0), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(4,1), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(4,2), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(4,3), 0, epsilon);    ASSERT_NEAR(mat_times_mat_inverse(4,4), 1, epsilon);

    const auto mat_inverse_times_mat = inverse.multiply(mat);
    ASSERT_NEAR(mat_inverse_times_mat(0,0), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,2), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,3), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(0,4), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(1,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,1), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,2), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,3), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(1,4), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(2,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,2), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,3), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(2,4), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(3,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(3,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(3,2), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(3,3), 1, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(3,4), 0, epsilon);
    ASSERT_NEAR(mat_inverse_times_mat(4,0), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(4,1), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(4,2), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(4,3), 0, epsilon);    ASSERT_NEAR(mat_inverse_times_mat(4,4), 1, epsilon);
}
