//
// Created by dorian on 15.01.2024.
// stoicadorian@gmail.com
//
#include "gtest/gtest.h"
#include "Matrix.hpp"
#include <cmath>

using namespace LinearAlgebra::Matrix;
using namespace LinearAlgebra::Vector;

class Matrix_SolveLLSQ_tests : public ::testing::Test
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


TEST_F(Matrix_SolveLLSQ_tests, Solve_LLSQ_example)
{
    const auto data = std::vector<int>{1,2,
                                       1,3,
                                       0,0};

    const auto mat = Matrix<int>(data, 3,2);
    const auto b = Vector<int>({4,5,6});

    ASSERT_TRUE(mat.solve(b) == std::nullopt);
    const auto llsq_result = mat.fit_LLSQ(b).value();
    ASSERT_TRUE(llsq_result.bestEstimate.dim() ==  2);

    ASSERT_EQ(llsq_result.bestEstimate[0], 2);
    ASSERT_EQ(llsq_result.bestEstimate[1], 1);

    ASSERT_EQ(llsq_result.error, 6);
}

TEST_F(Matrix_SolveLLSQ_tests, Solve_LLSQ_example_2)
{
    const auto data = std::vector<int>{1,-1,
                                       1,1,
                                       1,2};

    const auto mat = Matrix<int>(data, 3,2);
    const auto b = Vector<int>({1,1,3});

    ASSERT_TRUE(mat.solve(b) == std::nullopt);
    const auto llsq_result = mat.fit_LLSQ(b).value();
    ASSERT_TRUE(llsq_result.bestEstimate.dim() ==  2);

    ASSERT_NEAR(llsq_result.bestEstimate[0], 9./7, epsilon);
    ASSERT_NEAR(llsq_result.bestEstimate[1], 4./7, epsilon);

    ASSERT_NEAR(llsq_result.error, std::sqrt(56)/7, epsilon);
}

// This is a dummy test involving projecting the vector (10,5) to the line (3,4).
TEST_F(Matrix_SolveLLSQ_tests, Solve_LLSQ_Strang_3_3_1)
{
    const auto data = std::vector<int>{3, 4};

    const auto mat = Matrix<int>(data, 2, 1);
    const auto b = Vector<int>({10, 5});

    ASSERT_TRUE(mat.solve(b) == std::nullopt);
    const auto llsq_result = mat.fit_LLSQ(b).value();
    ASSERT_TRUE(llsq_result.bestEstimate.dim() ==  1);

    ASSERT_NEAR(llsq_result.bestEstimate[0], 2, epsilon);
}

TEST_F(Matrix_SolveLLSQ_tests, Solve_LLSQ_Strang_3_3_3)
{
    const auto data = std::vector<int>{1,0,
                                       0,1,
                                       1,1};

    const auto mat = Matrix<int>(data, 3, 2);
    const auto b = Vector<int>({1,1,0});

    ASSERT_TRUE(mat.solve(b) == std::nullopt);
    const auto llsq_result = mat.fit_LLSQ(b).value();
    ASSERT_TRUE(llsq_result.bestEstimate.dim() ==  2);

    ASSERT_NEAR(llsq_result.bestEstimate[0], 1./3, epsilon);
    ASSERT_NEAR(llsq_result.bestEstimate[1], 1./3, epsilon);

    ASSERT_NEAR(llsq_result.error, 2*std::sqrt(3)/3, epsilon);
}

TEST_F(Matrix_SolveLLSQ_tests, Solve_LLSQ_Strang_3_3_5)
{
    const auto data = std::vector<int>{1,-1,
                                       1,0,
                                       1,1};

    const auto mat = Matrix<int>(data, 3, 2);
    const auto b = Vector<int>({4,5,9});

    ASSERT_TRUE(mat.solve(b) == std::nullopt);
    const auto llsq_result = mat.fit_LLSQ(b).value();
    ASSERT_TRUE(llsq_result.bestEstimate.dim() ==  2);

    ASSERT_NEAR(llsq_result.bestEstimate[0], 6, epsilon);
    ASSERT_NEAR(llsq_result.bestEstimate[1], 5./2, epsilon);
}

TEST_F(Matrix_SolveLLSQ_tests, Solve_LLSQ_Strang_3_3_13)
{
    const auto data = std::vector<int>{1,-2,
                                       1,-1,
                                       1,0,
                                       1,2};

    const auto mat = Matrix<int>(data, 4, 2);
    const auto b = Vector<int>({4,3,1,0});

    ASSERT_TRUE(mat.solve(b) == std::nullopt);
    const auto llsq_result = mat.fit_LLSQ(b).value();
    ASSERT_TRUE(llsq_result.bestEstimate.dim() ==  2);

    ASSERT_NEAR(llsq_result.bestEstimate[0], 61./35, epsilon);
    ASSERT_NEAR(llsq_result.bestEstimate[1], -36./35, epsilon);
}