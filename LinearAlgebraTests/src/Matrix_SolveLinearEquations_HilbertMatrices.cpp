//
// Created by dorian on 29.12.2023.
// stoicadorian@gmail.com
//

#include "gtest/gtest.h"
#include "Matrix.hpp"
#include "MatrixHelpers.hpp"

using namespace LinearAlgebra::Matrix;
using namespace LinearAlgebra::Vector;

#include "gtest/gtest.h"
#include "Matrix.hpp"
#include "MatrixHelpers.hpp"


class Matrix_SolveSystemLinearEquations_HilbertMatrices : public ::testing::Test
{

protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(Matrix_SolveSystemLinearEquations_HilbertMatrices, Hilbert_5x5)
{
    const auto mat = hilbert_matrix(5);

    const auto b = Vector<int>({1,2,3,4,5});

    const auto solution = mat.solve(b);

    ASSERT_TRUE(solution.dim() == 5);
    const double epsilon = 1e-7; //only 1e-7 precision !
    ASSERT_NEAR(solution[0], 125, epsilon);
    ASSERT_NEAR(solution[1], -2880, epsilon);
    ASSERT_NEAR(solution[2], 14490, epsilon);
    ASSERT_NEAR(solution[3], -24640, epsilon);
    ASSERT_NEAR(solution[4], 13230, epsilon);

    //Multiply the matrix with solution and ensure the result is b
    const auto same_b = mat*solution;

    ASSERT_NEAR(same_b[0], b[0], epsilon);
    ASSERT_NEAR(same_b[1], b[1], epsilon);
    ASSERT_NEAR(same_b[2], b[2], epsilon);
    ASSERT_NEAR(same_b[3], b[3], epsilon);
    ASSERT_NEAR(same_b[4], b[4], epsilon);
}

TEST_F(Matrix_SolveSystemLinearEquations_HilbertMatrices, Hilbert_5x5_test_2)
{
    const auto mat = hilbert_matrix(5);

    const auto b = Vector<double>({0.123,  1.234,  2.345,  3.456,  4.567});

    const auto solution = mat.solve(b);

    ASSERT_TRUE(solution.dim() == 5);
    const double epsilon = 1e-7; //only 1e-7 precision !
    ASSERT_NEAR(solution[0], 26787./200,    epsilon);
    ASSERT_NEAR(solution[1], -77028./25,    epsilon);
    ASSERT_NEAR(solution[2], 309519./20,    epsilon);
    ASSERT_NEAR(solution[3], -656712./25,   epsilon);
    ASSERT_NEAR(solution[4], 1407609./100,  epsilon);

    //Multiply the matrix with solution and ensure the result is b
    const auto same_b = mat*solution;

    ASSERT_NEAR(same_b[0], b[0], epsilon);
    ASSERT_NEAR(same_b[1], b[1], epsilon);
    ASSERT_NEAR(same_b[2], b[2], epsilon);
    ASSERT_NEAR(same_b[3], b[3], epsilon);
    ASSERT_NEAR(same_b[4], b[4], epsilon);
}

TEST_F(Matrix_SolveSystemLinearEquations_HilbertMatrices, Hilbert_7x7)
{
    const auto mat = hilbert_matrix(7);

    const auto b = Vector<int>({1,2,3,4,5,6,7});

    const auto solution = mat.solve(b);

    ASSERT_TRUE(solution.dim() == 7);

    const double epsilon = 1e-2; //only 1e-2 precision !

    ASSERT_NEAR(solution[0], 343, epsilon);
    ASSERT_NEAR(solution[1], -16128, epsilon);
    ASSERT_NEAR(solution[2], 177660, epsilon);
    ASSERT_NEAR(solution[3], -772800, epsilon);
    ASSERT_NEAR(solution[4], 1559250, epsilon);
    ASSERT_NEAR(solution[5], -1463616, epsilon);
    ASSERT_NEAR(solution[6], 516516, epsilon);

    //Multiply the matrix with solution and ensure the result is b
    const auto same_b = mat*solution;

    ASSERT_NEAR(same_b[0], b[0], epsilon);
    ASSERT_NEAR(same_b[1], b[1], epsilon);
    ASSERT_NEAR(same_b[2], b[2], epsilon);
    ASSERT_NEAR(same_b[3], b[3], epsilon);
    ASSERT_NEAR(same_b[4], b[4], epsilon);
    ASSERT_NEAR(same_b[5], b[5], epsilon);
    ASSERT_NEAR(same_b[6], b[6], epsilon);

    ASSERT_NEAR(mat.determinant(), 4.8358026e-25, 1e-25);
}

TEST_F(Matrix_SolveSystemLinearEquations_HilbertMatrices, Hilbert_7x7_test_2)
{
    const auto mat = hilbert_matrix(7);

    const auto b = Vector<double>({0.123,  1.234,  2.345,  3.456,  4.567,  5.678,  6.789});

    const auto solution = mat.solve(b);

    ASSERT_TRUE(solution.dim() == 7);

    const double epsilon = 1e-2; //only 1e-2 precision !

    ASSERT_NEAR(solution[0], 374157./1000, epsilon);
    ASSERT_NEAR(solution[1], -439656./25, epsilon);
    ASSERT_NEAR(solution[2], 9682281./50, epsilon);
    ASSERT_NEAR(solution[3], -4209912./5, epsilon);
    ASSERT_NEAR(solution[4], 33961851./20, epsilon);
    ASSERT_NEAR(solution[5], -199151568./125, epsilon);
    ASSERT_NEAR(solution[6], 28099071./50, epsilon);

    //Multiply the matrix with solution and ensure the result is b
    const auto same_b = mat*solution;

    ASSERT_NEAR(same_b[0], b[0], epsilon);
    ASSERT_NEAR(same_b[1], b[1], epsilon);
    ASSERT_NEAR(same_b[2], b[2], epsilon);
    ASSERT_NEAR(same_b[3], b[3], epsilon);
    ASSERT_NEAR(same_b[4], b[4], epsilon);
    ASSERT_NEAR(same_b[5], b[5], epsilon);
    ASSERT_NEAR(same_b[6], b[6], epsilon);
}