//
// Created by dorian on 29.12.2023.
// stoicadorian@gmail.com
//
#include "gtest/gtest.h"
#include "Matrix.hpp"
#include "MatrixHelpers.hpp"

using namespace LinearAlgebra::Matrix;
using namespace LinearAlgebra::Vector;

class MatrixHelpersTests : public ::testing::Test
{

protected:
    virtual void SetUp()
    {
        dummyIntData    = std::vector<int>{     1, 2, 3,
                                                4, 5, 6,
                                                7, 8, 9};

        dummyFloatData  = std::vector<float>{   1.f, 3.f, 8.f,
                                                2.f, 7.f, 6.f,
                                                0.f, -1.f, 7.f};

        dummyDoubleData = std::vector<double>{  1.0, 2.0, 3.0,
                                                4.0, 5.0, 6.0,
                                                9.0, 8.0, 7.0};
    }

    virtual void TearDown()
    {
    }

    std::vector<int>    dummyIntData;
    std::vector<double> dummyDoubleData;
    std::vector<float>  dummyFloatData;
};


TEST_F(MatrixHelpersTests, Test_isLowerTriangular_Int)
{
    const auto m = Matrix<int>(dummyIntData, 3,3);
    ASSERT_FALSE(isLowerTriangular(m));

    const auto lower = Matrix<int>({1, 0 ,0,
                                                  2,1,0,
                                                  3,1,1},
                                     3,3);

    ASSERT_TRUE(isLowerTriangular(lower));
}

TEST_F(MatrixHelpersTests, Test_isLowerTriangular_Float)
{
    const auto m = Matrix<float>(dummyFloatData, 3,3);
    ASSERT_FALSE(isLowerTriangular(m));

    auto lower = Matrix<float>({1e-3f,    0,        0,
                                                      2e-5f,    1e-5f,  0,
                                                      3e-6f,    1e-2f,  1.142f},
                                   3,3);

    ASSERT_TRUE(isLowerTriangular(lower));

    lower(1,2) = 0.0001;
    ASSERT_FALSE(isLowerTriangular(lower));
}

TEST_F(MatrixHelpersTests, Test_isLowerTriangular_Double)
{
    const auto m = Matrix<double>(dummyDoubleData, 3,3);
    ASSERT_FALSE(isLowerTriangular(m));

    auto lower = Matrix<float>({1e-5,    0 ,     0,
                                            2e-7,    1e-8f,  0,
                                            3e-8,    1e-4f,  1.1422123},
                               3,3);

    ASSERT_TRUE(isLowerTriangular(lower));

    lower(1,2) = 0.0001;
    ASSERT_FALSE(isLowerTriangular(lower));
}

TEST_F(MatrixHelpersTests, Test_isUpperTriangular_Int)
{
    const auto m = Matrix<int>(dummyIntData, 3,3);
    ASSERT_FALSE(isUpperTriangular(m));

    const auto upper = Matrix<int>({1,1,1,
                                    0,1,2,
                                    0,0,1},
                                   3,3);

    ASSERT_TRUE(isUpperTriangular(upper));
}

TEST_F(MatrixHelpersTests, Test_isUpperTriangular_Float)
{
    const auto m = Matrix<float>(dummyFloatData, 3,3);
    ASSERT_FALSE(isUpperTriangular(m));

    auto upper = Matrix<float>({1e-4f,  1e-5f,  1e-3f,
                                                0,  1e-5f,  2e-5f,
                                                0,  0,      1e-6f},
                                   3,3);

    ASSERT_TRUE(isUpperTriangular(upper));

    upper(1,0) = 1e-5f;
    ASSERT_FALSE(isUpperTriangular(upper));
}

TEST_F(MatrixHelpersTests, Test_isUpperTriangular_Double)
{
    const auto m = Matrix<double>(dummyDoubleData, 3,3);
    ASSERT_FALSE(isUpperTriangular(m));

    auto upper = Matrix<double>({1e-6,  1e-7,  1e-5,
                                0,  1e-8,  2e-6,
                                0,  0,      1e-8},
                               3,3);

    ASSERT_TRUE(isUpperTriangular(upper));

    upper(1,0) = 1e-7;
    ASSERT_FALSE(isUpperTriangular(upper));
}