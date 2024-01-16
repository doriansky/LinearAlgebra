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