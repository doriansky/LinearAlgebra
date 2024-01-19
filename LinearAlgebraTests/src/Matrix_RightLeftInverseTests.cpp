//
// Created by dorian on 15.01.2024.
// stoicadorian@gmail.com
//
#include "gtest/gtest.h"
#include "Matrix.hpp"
#include "MatrixToolbox.hpp"

using namespace LinearAlgebra::Matrix;
using namespace LinearAlgebra::Vector;

class MatrixRightLeftInverseTests : public ::testing::Test
{

protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

    const long double epsilon = 1e-9;
};


TEST_F(MatrixRightLeftInverseTests, RightInverse_2x3_rank_2)
{
    const auto data = std::vector<int>{4,0,0,
                                                   0,5,0};

    const auto mat = Matrix<int>(data, 2, 3);
    const auto l_inv = left_inverse(mat);
    const auto r_inv = right_inverse(mat).value();

    ASSERT_EQ(l_inv, std::nullopt);
    ASSERT_EQ(r_inv.rows(), 3);
    ASSERT_EQ(r_inv.cols(), 2);

    ASSERT_NEAR(r_inv(0,0), 1./4, epsilon);     ASSERT_EQ(r_inv(0,1), 0);
    ASSERT_EQ(r_inv(1,0), 0);                   ASSERT_NEAR(r_inv(1,1), 1./5, epsilon);
    ASSERT_EQ(r_inv(2,0), 0);                   ASSERT_EQ(r_inv(2,1), 0);

    const auto id = mat * r_inv;
    ASSERT_EQ(id.rows(), mat.rows());
    ASSERT_EQ(id.cols(), mat.rows());
    ASSERT_NEAR(id(0,0), 1, epsilon);  ASSERT_EQ(id(0,1), 0);
    ASSERT_EQ(id(1,0), 0);  ASSERT_NEAR(id(1,1), 1, epsilon);
}

TEST_F(MatrixRightLeftInverseTests, LeftInverse_4x3_rank_3)
{
    const auto data = std::vector<int>{1,2,3,
                                       4,5,6,
                                       7,8,10,
                                       10,11,12};

    const auto mat = Matrix<int>(data, 4, 3);
    const auto r_inv = right_inverse(mat);
    const auto l_inv = left_inverse(mat).value();

    ASSERT_EQ(r_inv, std::nullopt);
    ASSERT_EQ(l_inv.rows(), 3);
    ASSERT_EQ(l_inv.cols(), 4);

    const auto id = l_inv * mat;
    ASSERT_EQ(id.rows(), 3);    ASSERT_EQ(id.cols(), 3);

    ASSERT_NEAR(id(0,0), 1, epsilon);   ASSERT_NEAR(id(0,1), 0, epsilon);   ASSERT_NEAR(id(0,2), 0, epsilon);
    ASSERT_NEAR(id(1,0), 0, epsilon);   ASSERT_NEAR(id(1,1), 1, epsilon);   ASSERT_NEAR(id(1,2), 0, epsilon);
    ASSERT_NEAR(id(2,0), 0, epsilon);   ASSERT_NEAR(id(2,1), 0, epsilon);   ASSERT_NEAR(id(2,2), 1, epsilon);
}

TEST_F(MatrixRightLeftInverseTests, SquareInvertible)
{
    const auto data = std::vector<int> {1,2,3,
                                        2,3,1,
                                        -2,3,-2};
    const auto matrix = Matrix<int>(data, 3, 3);

    const auto inv = inverse(matrix).value();
    const auto leftInv = left_inverse(matrix).value();
    const auto rightInv = right_inverse(matrix).value();

    ASSERT_NEAR(inv(0,0), leftInv(0,0), epsilon);   ASSERT_NEAR(inv(0,1), leftInv(0,1), epsilon);   ASSERT_NEAR(inv(0,2), leftInv(0,2), epsilon);
    ASSERT_NEAR(inv(1,0), leftInv(1,0), epsilon);   ASSERT_NEAR(inv(1,1), leftInv(1,1), epsilon);   ASSERT_NEAR(inv(1,2), leftInv(1,2), epsilon);
    ASSERT_NEAR(inv(2,0), leftInv(2,0), epsilon);   ASSERT_NEAR(inv(2,1), leftInv(2,1), epsilon);   ASSERT_NEAR(inv(2,2), leftInv(2,2), epsilon);

    ASSERT_NEAR(inv(0,0), rightInv(0,0), epsilon);   ASSERT_NEAR(inv(0,1), rightInv(0,1), epsilon);   ASSERT_NEAR(inv(0,2), rightInv(0,2), epsilon);
    ASSERT_NEAR(inv(1,0), rightInv(1,0), epsilon);   ASSERT_NEAR(inv(1,1), rightInv(1,1), epsilon);   ASSERT_NEAR(inv(1,2), rightInv(1,2), epsilon);
    ASSERT_NEAR(inv(2,0), rightInv(2,0), epsilon);   ASSERT_NEAR(inv(2,1), rightInv(2,1), epsilon);   ASSERT_NEAR(inv(2,2), rightInv(2,2), epsilon);
}