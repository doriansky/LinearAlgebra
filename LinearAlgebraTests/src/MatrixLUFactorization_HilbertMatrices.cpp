//
// Created by dorian on 29.12.2023.
// stoicadorian@gmail.com
//
#include "gtest/gtest.h"
#include "Matrix.hpp"
#include "MatrixToolbox.hpp"

using namespace LinearAlgebra::Matrix;
using namespace LinearAlgebra::Vector;

//Test LU decomposition with various Hilbert matrices

class MatrixLUFactorization_HilbertMatrices : public ::testing::Test
{

protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(MatrixLUFactorization_HilbertMatrices, LUFactorization_Hilbert_3x3)
{
    const auto hilbert_mat = hilbert_matrix(3);
    const auto LU_Result = factorizeLU(hilbert_mat);

    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    const double epsilon = 1e-9;
    ASSERT_EQ(LU_Result.lower.rows(), 3); ASSERT_EQ(LU_Result.lower.cols(), 3);
    ASSERT_NEAR(LU_Result.lower(0,0), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(0,1), 0, epsilon);   ASSERT_NEAR(LU_Result.lower(0,2), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(1,0), 1./2, epsilon);   ASSERT_NEAR(LU_Result.lower(1,1), 1, epsilon);   ASSERT_NEAR(LU_Result.lower(1,2), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(2,0), 1./3, epsilon);   ASSERT_NEAR(LU_Result.lower(2,1), 1, epsilon);   ASSERT_NEAR(LU_Result.lower(2,2), 1, epsilon);


    ASSERT_EQ(LU_Result.upper.rows(), 3); ASSERT_EQ(LU_Result.upper.cols(), 3);
    ASSERT_NEAR(LU_Result.upper(0,0), 1, epsilon);   ASSERT_NEAR(LU_Result.upper(0,1), 1./2, epsilon);      ASSERT_NEAR(LU_Result.upper(0,2), 1./3, epsilon);
    ASSERT_NEAR(LU_Result.upper(1,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(1,1), 1./12, epsilon);     ASSERT_NEAR(LU_Result.upper(1,2), 1./12, epsilon);
    ASSERT_NEAR(LU_Result.upper(2,0), 0, epsilon);   ASSERT_NEAR(LU_Result.upper(2,1), 0, epsilon);         ASSERT_NEAR(LU_Result.upper(2,2), 1./180, epsilon);

    // Test LU_echelon is outputting the same result (since this is non-singular matrix)
    const auto LU_echelon = factorizeLU_echelon(hilbert_mat);
    ASSERT_EQ(LU_echelon.upper.rows(), 3); ASSERT_EQ(LU_echelon.upper.cols(), 3);

    ASSERT_EQ(LU_Result.lower(0,0), LU_echelon.lower(0,0));   ASSERT_EQ(LU_Result.lower(0,1), LU_echelon.lower(0,1));   ASSERT_EQ(LU_Result.lower(0,2), LU_echelon.lower(0,2));
    ASSERT_EQ(LU_Result.lower(1,0), LU_echelon.lower(1,0));   ASSERT_EQ(LU_Result.lower(1,1), LU_echelon.lower(1,1));  ASSERT_EQ(LU_Result.lower(1,2),  LU_echelon.lower(1,2));
    ASSERT_EQ(LU_Result.lower(2,0), LU_echelon.lower(2,0));   ASSERT_EQ(LU_Result.lower(2,1), LU_echelon.lower(2,1));   ASSERT_EQ(LU_Result.lower(2,2), LU_echelon.lower(2,2));

    ASSERT_EQ(LU_Result.upper(0,0), LU_echelon.upper(0,0));   ASSERT_EQ(LU_Result.upper(0,1), LU_echelon.upper(0,1));   ASSERT_EQ(LU_Result.upper(0,2), LU_echelon.upper(0,2));
    ASSERT_EQ(LU_Result.upper(1,0), LU_echelon.upper(1,0));   ASSERT_EQ(LU_Result.upper(1,1), LU_echelon.upper(1,1));  ASSERT_EQ(LU_Result.upper(1,2),  LU_echelon.upper(1,2));
    ASSERT_EQ(LU_Result.upper(2,0), LU_echelon.upper(2,0));   ASSERT_EQ(LU_Result.upper(2,1), LU_echelon.upper(2,1));   ASSERT_EQ(LU_Result.upper(2,2), LU_echelon.upper(2,2));
}

TEST_F(MatrixLUFactorization_HilbertMatrices, LUFactorization_Hilbert_5x5)
{
    const auto hilbert_mat = hilbert_matrix(5);
    const auto LU_Result = factorizeLU(hilbert_mat);

    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    const double epsilon = 1e-9;
    ASSERT_EQ(LU_Result.lower.rows(), 5); ASSERT_EQ(LU_Result.lower.cols(), 5);
    ASSERT_NEAR(LU_Result.lower(0,0), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(0,1), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(0,2), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(0,3), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(0,4), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(1,0), 1./2, epsilon);   ASSERT_NEAR(LU_Result.lower(1,1), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(1,2), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(1,3), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(1,4), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(2,0), 1./3, epsilon);   ASSERT_NEAR(LU_Result.lower(2,1), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(2,2), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(2,3), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(2,4), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(3,0), 1./4, epsilon);   ASSERT_NEAR(LU_Result.lower(3,1), 9./10, epsilon);  ASSERT_NEAR(LU_Result.lower(3,2), 3./2, epsilon);   ASSERT_NEAR(LU_Result.lower(3,3), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(3,4), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(4,0), 1./5, epsilon);   ASSERT_NEAR(LU_Result.lower(4,1), 4./5, epsilon);   ASSERT_NEAR(LU_Result.lower(4,2), 12./7, epsilon);  ASSERT_NEAR(LU_Result.lower(4,3), 2, epsilon);      ASSERT_NEAR(LU_Result.lower(4,4), 1, epsilon);


    ASSERT_EQ(LU_Result.upper.rows(), 5); ASSERT_EQ(LU_Result.upper.cols(), 5);
    ASSERT_NEAR(LU_Result.upper(0,0), 1, epsilon);  ASSERT_NEAR(LU_Result.upper(0,1), 1./2, epsilon);   ASSERT_NEAR(LU_Result.upper(0,2), 1./3, epsilon);       ASSERT_NEAR(LU_Result.upper(0,3), 1./4, epsilon);       ASSERT_NEAR(LU_Result.upper(0,4), 1./5, epsilon);
    ASSERT_NEAR(LU_Result.upper(1,0), 0, epsilon);  ASSERT_NEAR(LU_Result.upper(1,1), 1./12, epsilon);  ASSERT_NEAR(LU_Result.upper(1,2), 1./12, epsilon);      ASSERT_NEAR(LU_Result.upper(1,3), 3./40, epsilon);      ASSERT_NEAR(LU_Result.upper(1,4), 1./15, epsilon);
    ASSERT_NEAR(LU_Result.upper(2,0), 0, epsilon);  ASSERT_NEAR(LU_Result.upper(2,1), 0, epsilon);      ASSERT_NEAR(LU_Result.upper(2,2), 1./180, epsilon);     ASSERT_NEAR(LU_Result.upper(2,3), 1./120, epsilon);     ASSERT_NEAR(LU_Result.upper(2,4), 1./105, epsilon);
    ASSERT_NEAR(LU_Result.upper(3,0), 0, epsilon);  ASSERT_NEAR(LU_Result.upper(3,1), 0, epsilon);      ASSERT_NEAR(LU_Result.upper(3,2), 0, epsilon);          ASSERT_NEAR(LU_Result.upper(3,3), 1./2800, epsilon);    ASSERT_NEAR(LU_Result.upper(3,4), 1./1400, epsilon);
    ASSERT_NEAR(LU_Result.upper(4,0), 0, epsilon);  ASSERT_NEAR(LU_Result.upper(4,1), 0, epsilon);      ASSERT_NEAR(LU_Result.upper(4,2), 0, epsilon);          ASSERT_NEAR(LU_Result.upper(4,3), 0, epsilon);          ASSERT_NEAR(LU_Result.upper(4,4), 1./44100, epsilon);

    // Test LU_echelon is outputting the same result (since this is non-singular matrix)
    const auto LU_echelon = factorizeLU_echelon(hilbert_mat);
    ASSERT_EQ(LU_echelon.upper.rows(), 5); ASSERT_EQ(LU_echelon.upper.cols(), 5);

    ASSERT_EQ(LU_Result.lower(0,0), LU_echelon.lower(0,0));   ASSERT_EQ(LU_Result.lower(0,1), LU_echelon.lower(0,1));   ASSERT_EQ(LU_Result.lower(0,2), LU_echelon.lower(0,2));     ASSERT_EQ(LU_Result.lower(0,3), LU_echelon.lower(0,3));   ASSERT_EQ(LU_Result.lower(0,4), LU_echelon.lower(0,4));
    ASSERT_EQ(LU_Result.lower(1,0), LU_echelon.lower(1,0));   ASSERT_EQ(LU_Result.lower(1,1), LU_echelon.lower(1,1));   ASSERT_EQ(LU_Result.lower(1,2),  LU_echelon.lower(1,2));    ASSERT_EQ(LU_Result.lower(1,3), LU_echelon.lower(1,3));   ASSERT_EQ(LU_Result.lower(1,4), LU_echelon.lower(1,4));
    ASSERT_EQ(LU_Result.lower(2,0), LU_echelon.lower(2,0));   ASSERT_EQ(LU_Result.lower(2,1), LU_echelon.lower(2,1));   ASSERT_EQ(LU_Result.lower(2,2), LU_echelon.lower(2,2));     ASSERT_EQ(LU_Result.lower(2,3), LU_echelon.lower(2,3));   ASSERT_EQ(LU_Result.lower(2,4), LU_echelon.lower(2,4));
    ASSERT_EQ(LU_Result.lower(3,0), LU_echelon.lower(3,0));   ASSERT_EQ(LU_Result.lower(3,1), LU_echelon.lower(3,1));   ASSERT_EQ(LU_Result.lower(3,2), LU_echelon.lower(3,2));     ASSERT_EQ(LU_Result.lower(3,3), LU_echelon.lower(3,3));   ASSERT_EQ(LU_Result.lower(3,4), LU_echelon.lower(3,4));
    ASSERT_EQ(LU_Result.lower(4,0), LU_echelon.lower(4,0));   ASSERT_EQ(LU_Result.lower(4,1), LU_echelon.lower(4,1));   ASSERT_EQ(LU_Result.lower(4,2), LU_echelon.lower(4,2));     ASSERT_EQ(LU_Result.lower(4,3), LU_echelon.lower(4,3));   ASSERT_EQ(LU_Result.lower(4,4), LU_echelon.lower(4,4));

    ASSERT_EQ(LU_Result.upper(0,0), LU_echelon.upper(0,0));   ASSERT_EQ(LU_Result.upper(0,1), LU_echelon.upper(0,1));   ASSERT_EQ(LU_Result.upper(0,2), LU_echelon.upper(0,2));     ASSERT_EQ(LU_Result.upper(0,3), LU_echelon.upper(0,3));   ASSERT_EQ(LU_Result.upper(0,4), LU_echelon.upper(0,4));
    ASSERT_EQ(LU_Result.upper(1,0), LU_echelon.upper(1,0));   ASSERT_EQ(LU_Result.upper(1,1), LU_echelon.upper(1,1));   ASSERT_EQ(LU_Result.upper(1,2),  LU_echelon.upper(1,2));    ASSERT_EQ(LU_Result.upper(1,3), LU_echelon.upper(1,3));   ASSERT_EQ(LU_Result.upper(1,4), LU_echelon.upper(1,4));
    ASSERT_EQ(LU_Result.upper(2,0), LU_echelon.upper(2,0));   ASSERT_EQ(LU_Result.upper(2,1), LU_echelon.upper(2,1));   ASSERT_EQ(LU_Result.upper(2,2), LU_echelon.upper(2,2));     ASSERT_EQ(LU_Result.upper(2,3), LU_echelon.upper(2,3));   ASSERT_EQ(LU_Result.upper(2,4), LU_echelon.upper(2,4));
    ASSERT_EQ(LU_Result.upper(3,0), LU_echelon.upper(3,0));   ASSERT_EQ(LU_Result.upper(3,1), LU_echelon.upper(3,1));   ASSERT_EQ(LU_Result.upper(3,2), LU_echelon.upper(3,2));     ASSERT_EQ(LU_Result.upper(3,3), LU_echelon.upper(3,3));   ASSERT_EQ(LU_Result.upper(3,4), LU_echelon.upper(3,4));
    ASSERT_EQ(LU_Result.upper(4,0), LU_echelon.upper(4,0));   ASSERT_EQ(LU_Result.upper(4,1), LU_echelon.upper(4,1));   ASSERT_EQ(LU_Result.upper(4,2), LU_echelon.upper(4,2));     ASSERT_EQ(LU_Result.upper(4,3), LU_echelon.upper(4,3));   ASSERT_EQ(LU_Result.upper(4,4), LU_echelon.upper(4,4));
}

TEST_F(MatrixLUFactorization_HilbertMatrices, LUFactorization_Hilbert_7x7)
{
    const auto hilbert_mat = hilbert_matrix(7);
    const auto LU_Result = factorizeLU(hilbert_mat);

    ASSERT_TRUE(LU_Result.permutation == std::nullopt);

    const double epsilon = 1e-9;
    ASSERT_EQ(LU_Result.lower.rows(), 7); ASSERT_EQ(LU_Result.lower.cols(), 7);
    ASSERT_NEAR(LU_Result.lower(0,0), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(0,1), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(0,2), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(0,3), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(0,4), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(0,5), 0, epsilon); ASSERT_NEAR(LU_Result.lower(0,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(1,0), 1./2, epsilon);   ASSERT_NEAR(LU_Result.lower(1,1), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(1,2), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(1,3), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(1,4), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(1,5), 0, epsilon); ASSERT_NEAR(LU_Result.lower(1,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(2,0), 1./3, epsilon);   ASSERT_NEAR(LU_Result.lower(2,1), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(2,2), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(2,3), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(2,4), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(2,5), 0, epsilon); ASSERT_NEAR(LU_Result.lower(2,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(3,0), 1./4, epsilon);   ASSERT_NEAR(LU_Result.lower(3,1), 9./10, epsilon);  ASSERT_NEAR(LU_Result.lower(3,2), 3./2, epsilon);   ASSERT_NEAR(LU_Result.lower(3,3), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(3,4), 0, epsilon);      ASSERT_NEAR(LU_Result.lower(3,5), 0, epsilon); ASSERT_NEAR(LU_Result.lower(3,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(4,0), 1./5, epsilon);   ASSERT_NEAR(LU_Result.lower(4,1), 4./5, epsilon);   ASSERT_NEAR(LU_Result.lower(4,2), 12./7, epsilon);  ASSERT_NEAR(LU_Result.lower(4,3), 2, epsilon);      ASSERT_NEAR(LU_Result.lower(4,4), 1, epsilon);      ASSERT_NEAR(LU_Result.lower(4,5), 0, epsilon); ASSERT_NEAR(LU_Result.lower(4,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(5,0), 1./6, epsilon);   ASSERT_NEAR(LU_Result.lower(5,1), 5./7, epsilon);   ASSERT_NEAR(LU_Result.lower(5,2), 25./14, epsilon);  ASSERT_NEAR(LU_Result.lower(5,3), 25./9, epsilon); ASSERT_NEAR(LU_Result.lower(5,4), 5./2, epsilon);   ASSERT_NEAR(LU_Result.lower(5,5), 1, epsilon); ASSERT_NEAR(LU_Result.lower(5,6), 0, epsilon);
    ASSERT_NEAR(LU_Result.lower(6,0), 1./7, epsilon);   ASSERT_NEAR(LU_Result.lower(6,1), 9./14, epsilon);  ASSERT_NEAR(LU_Result.lower(6,2), 25./14, epsilon);  ASSERT_NEAR(LU_Result.lower(6,3), 10./3, epsilon); ASSERT_NEAR(LU_Result.lower(6,4), 45./11, epsilon); ASSERT_NEAR(LU_Result.lower(6,5), 3, epsilon); ASSERT_NEAR(LU_Result.lower(6,6), 1, epsilon);


    ASSERT_EQ(LU_Result.upper.rows(), 7); ASSERT_EQ(LU_Result.upper.cols(), 7);
    ASSERT_NEAR(LU_Result.upper(0,0), 1, epsilon);  ASSERT_NEAR(LU_Result.upper(0,1), 1./2, epsilon);   ASSERT_NEAR(LU_Result.upper(0,2), 1./3, epsilon);       ASSERT_NEAR(LU_Result.upper(0,3), 1./4, epsilon);       ASSERT_NEAR(LU_Result.upper(0,4), 1./5, epsilon);       ASSERT_NEAR(LU_Result.upper(0,5), 1./6, epsilon);       ASSERT_NEAR(LU_Result.upper(0,6), 1./7, epsilon);
    ASSERT_NEAR(LU_Result.upper(1,0), 0, epsilon);  ASSERT_NEAR(LU_Result.upper(1,1), 1./12, epsilon);  ASSERT_NEAR(LU_Result.upper(1,2), 1./12, epsilon);      ASSERT_NEAR(LU_Result.upper(1,3), 3./40, epsilon);      ASSERT_NEAR(LU_Result.upper(1,4), 1./15, epsilon);      ASSERT_NEAR(LU_Result.upper(1,5), 5./84, epsilon);      ASSERT_NEAR(LU_Result.upper(1,6), 3./56, epsilon);
    ASSERT_NEAR(LU_Result.upper(2,0), 0, epsilon);  ASSERT_NEAR(LU_Result.upper(2,1), 0, epsilon);      ASSERT_NEAR(LU_Result.upper(2,2), 1./180, epsilon);     ASSERT_NEAR(LU_Result.upper(2,3), 1./120, epsilon);     ASSERT_NEAR(LU_Result.upper(2,4), 1./105, epsilon);     ASSERT_NEAR(LU_Result.upper(2,5), 5./504, epsilon);     ASSERT_NEAR(LU_Result.upper(2,6), 5./504, epsilon);
    ASSERT_NEAR(LU_Result.upper(3,0), 0, epsilon);  ASSERT_NEAR(LU_Result.upper(3,1), 0, epsilon);      ASSERT_NEAR(LU_Result.upper(3,2), 0, epsilon);          ASSERT_NEAR(LU_Result.upper(3,3), 1./2800, epsilon);    ASSERT_NEAR(LU_Result.upper(3,4), 1./1400, epsilon);    ASSERT_NEAR(LU_Result.upper(3,5), 1./1008, epsilon);    ASSERT_NEAR(LU_Result.upper(3,6), 1./840, epsilon);
    ASSERT_NEAR(LU_Result.upper(4,0), 0, epsilon);  ASSERT_NEAR(LU_Result.upper(4,1), 0, epsilon);      ASSERT_NEAR(LU_Result.upper(4,2), 0, epsilon);          ASSERT_NEAR(LU_Result.upper(4,3), 0, epsilon);          ASSERT_NEAR(LU_Result.upper(4,4), 1./44100, epsilon);   ASSERT_NEAR(LU_Result.upper(4,5), 1./17640, epsilon);   ASSERT_NEAR(LU_Result.upper(4,6), 1./10780, epsilon);
    ASSERT_NEAR(LU_Result.upper(5,0), 0, epsilon);  ASSERT_NEAR(LU_Result.upper(5,1), 0, epsilon);      ASSERT_NEAR(LU_Result.upper(5,2), 0, epsilon);          ASSERT_NEAR(LU_Result.upper(5,3), 0, epsilon);          ASSERT_NEAR(LU_Result.upper(5,4), 0, epsilon);          ASSERT_NEAR(LU_Result.upper(5,5), 1./698544, epsilon);  ASSERT_NEAR(LU_Result.upper(5,6), 1./232848, epsilon);
    ASSERT_NEAR(LU_Result.upper(6,0), 0, epsilon);  ASSERT_NEAR(LU_Result.upper(6,1), 0, epsilon);      ASSERT_NEAR(LU_Result.upper(6,2), 0, epsilon);          ASSERT_NEAR(LU_Result.upper(6,3), 0, epsilon);          ASSERT_NEAR(LU_Result.upper(6,4), 0, epsilon);          ASSERT_NEAR(LU_Result.upper(6,5), 0, epsilon);          ASSERT_NEAR(LU_Result.upper(6,6), 1./11099088, epsilon);

    //Check if LU is numerically stable enough to reconstruct the initial mat
    const auto LU = LU_Result.lower * LU_Result.upper;
    ASSERT_NEAR(LU(0,0), hilbert_mat(0,0), epsilon);  ASSERT_NEAR(LU(0,1), hilbert_mat(0,1), epsilon);      ASSERT_NEAR(LU(0,2), hilbert_mat(0,2), epsilon);    ASSERT_NEAR(LU(0,3), hilbert_mat(0,3), epsilon);    ASSERT_NEAR(LU(0,4), hilbert_mat(0,4), epsilon);    ASSERT_NEAR(LU(0,5), hilbert_mat(0,5), epsilon);    ASSERT_NEAR(LU(0,6), hilbert_mat(0,6), epsilon);
    ASSERT_NEAR(LU(1,0), hilbert_mat(1,0), epsilon);  ASSERT_NEAR(LU(1,1), hilbert_mat(1,1), epsilon);      ASSERT_NEAR(LU(1,2), hilbert_mat(1,2), epsilon);    ASSERT_NEAR(LU(1,3), hilbert_mat(1,3), epsilon);    ASSERT_NEAR(LU(1,4), hilbert_mat(1,4), epsilon);    ASSERT_NEAR(LU(1,5), hilbert_mat(1,5), epsilon);    ASSERT_NEAR(LU(1,6), hilbert_mat(1,6), epsilon);
    ASSERT_NEAR(LU(2,0), hilbert_mat(2,0), epsilon);  ASSERT_NEAR(LU(2,1), hilbert_mat(2,1), epsilon);      ASSERT_NEAR(LU(2,2), hilbert_mat(2,2), epsilon);    ASSERT_NEAR(LU(2,3), hilbert_mat(2,3), epsilon);    ASSERT_NEAR(LU(2,4), hilbert_mat(2,4), epsilon);    ASSERT_NEAR(LU(2,5), hilbert_mat(2,5), epsilon);    ASSERT_NEAR(LU(2,6), hilbert_mat(2,6), epsilon);
    ASSERT_NEAR(LU(3,0), hilbert_mat(3,0), epsilon);  ASSERT_NEAR(LU(3,1), hilbert_mat(3,1), epsilon);      ASSERT_NEAR(LU(3,2), hilbert_mat(3,2), epsilon);    ASSERT_NEAR(LU(3,3), hilbert_mat(3,3), epsilon);    ASSERT_NEAR(LU(3,4), hilbert_mat(3,4), epsilon);    ASSERT_NEAR(LU(3,5), hilbert_mat(3,5), epsilon);    ASSERT_NEAR(LU(3,6), hilbert_mat(3,6), epsilon);
    ASSERT_NEAR(LU(4,0), hilbert_mat(4,0), epsilon);  ASSERT_NEAR(LU(4,1), hilbert_mat(4,1), epsilon);      ASSERT_NEAR(LU(4,2), hilbert_mat(4,2), epsilon);    ASSERT_NEAR(LU(4,3), hilbert_mat(4,3), epsilon);    ASSERT_NEAR(LU(4,4), hilbert_mat(4,4), epsilon);    ASSERT_NEAR(LU(4,5), hilbert_mat(4,5), epsilon);    ASSERT_NEAR(LU(4,6), hilbert_mat(4,6), epsilon);
    ASSERT_NEAR(LU(5,0), hilbert_mat(5,0), epsilon);  ASSERT_NEAR(LU(5,1), hilbert_mat(5,1), epsilon);      ASSERT_NEAR(LU(5,2), hilbert_mat(5,2), epsilon);    ASSERT_NEAR(LU(5,3), hilbert_mat(5,3), epsilon);    ASSERT_NEAR(LU(5,4), hilbert_mat(5,4), epsilon);    ASSERT_NEAR(LU(5,5), hilbert_mat(5,5), epsilon);    ASSERT_NEAR(LU(5,6), hilbert_mat(5,6), epsilon);
    ASSERT_NEAR(LU(6,0), hilbert_mat(6,0), epsilon);  ASSERT_NEAR(LU(6,1), hilbert_mat(6,1), epsilon);      ASSERT_NEAR(LU(6,2), hilbert_mat(6,2), epsilon);    ASSERT_NEAR(LU(6,3), hilbert_mat(6,3), epsilon);    ASSERT_NEAR(LU(6,4), hilbert_mat(6,4), epsilon);    ASSERT_NEAR(LU(6,5), hilbert_mat(6,5), epsilon);    ASSERT_NEAR(LU(6,6), hilbert_mat(6,6), epsilon);

    // Test LU_echelon is outputting the same result (since this is non-singular matrix)
    const auto LU_echelon = factorizeLU_echelon(hilbert_mat);
    ASSERT_EQ(LU_echelon.upper.rows(), 7); ASSERT_EQ(LU_echelon.upper.cols(), 7);

    ASSERT_EQ(LU_Result.lower(0,0), LU_echelon.lower(0,0));   ASSERT_EQ(LU_Result.lower(0,1), LU_echelon.lower(0,1));   ASSERT_EQ(LU_Result.lower(0,2), LU_echelon.lower(0,2));     ASSERT_EQ(LU_Result.lower(0,3), LU_echelon.lower(0,3));   ASSERT_EQ(LU_Result.lower(0,4), LU_echelon.lower(0,4));   ASSERT_EQ(LU_Result.lower(0,5), LU_echelon.lower(0,5));     ASSERT_EQ(LU_Result.lower(0,6), LU_echelon.lower(0,6));
    ASSERT_EQ(LU_Result.lower(1,0), LU_echelon.lower(1,0));   ASSERT_EQ(LU_Result.lower(1,1), LU_echelon.lower(1,1));   ASSERT_EQ(LU_Result.lower(1,2),  LU_echelon.lower(1,2));    ASSERT_EQ(LU_Result.lower(1,3), LU_echelon.lower(1,3));   ASSERT_EQ(LU_Result.lower(1,4), LU_echelon.lower(1,4));   ASSERT_EQ(LU_Result.lower(1,5), LU_echelon.lower(1,5));     ASSERT_EQ(LU_Result.lower(1,6), LU_echelon.lower(1,6));
    ASSERT_EQ(LU_Result.lower(2,0), LU_echelon.lower(2,0));   ASSERT_EQ(LU_Result.lower(2,1), LU_echelon.lower(2,1));   ASSERT_EQ(LU_Result.lower(2,2), LU_echelon.lower(2,2));     ASSERT_EQ(LU_Result.lower(2,3), LU_echelon.lower(2,3));   ASSERT_EQ(LU_Result.lower(2,4), LU_echelon.lower(2,4));   ASSERT_EQ(LU_Result.lower(2,5), LU_echelon.lower(2,5));     ASSERT_EQ(LU_Result.lower(2,6), LU_echelon.lower(2,6));
    ASSERT_EQ(LU_Result.lower(3,0), LU_echelon.lower(3,0));   ASSERT_EQ(LU_Result.lower(3,1), LU_echelon.lower(3,1));   ASSERT_EQ(LU_Result.lower(3,2), LU_echelon.lower(3,2));     ASSERT_EQ(LU_Result.lower(3,3), LU_echelon.lower(3,3));   ASSERT_EQ(LU_Result.lower(3,4), LU_echelon.lower(3,4));   ASSERT_EQ(LU_Result.lower(3,5), LU_echelon.lower(3,5));     ASSERT_EQ(LU_Result.lower(3,6), LU_echelon.lower(3,6));
    ASSERT_EQ(LU_Result.lower(4,0), LU_echelon.lower(4,0));   ASSERT_EQ(LU_Result.lower(4,1), LU_echelon.lower(4,1));   ASSERT_EQ(LU_Result.lower(4,2), LU_echelon.lower(4,2));     ASSERT_EQ(LU_Result.lower(4,3), LU_echelon.lower(4,3));   ASSERT_EQ(LU_Result.lower(4,4), LU_echelon.lower(4,4));   ASSERT_EQ(LU_Result.lower(4,5), LU_echelon.lower(4,5));     ASSERT_EQ(LU_Result.lower(4,6), LU_echelon.lower(4,6));
    ASSERT_EQ(LU_Result.lower(5,0), LU_echelon.lower(5,0));   ASSERT_EQ(LU_Result.lower(5,1), LU_echelon.lower(5,1));   ASSERT_EQ(LU_Result.lower(5,2), LU_echelon.lower(5,2));     ASSERT_EQ(LU_Result.lower(5,3), LU_echelon.lower(5,3));   ASSERT_EQ(LU_Result.lower(5,4), LU_echelon.lower(5,4));   ASSERT_EQ(LU_Result.lower(5,5), LU_echelon.lower(5,5));     ASSERT_EQ(LU_Result.lower(5,6), LU_echelon.lower(5,6));
    ASSERT_EQ(LU_Result.lower(6,0), LU_echelon.lower(6,0));   ASSERT_EQ(LU_Result.lower(6,1), LU_echelon.lower(6,1));   ASSERT_EQ(LU_Result.lower(6,2), LU_echelon.lower(6,2));     ASSERT_EQ(LU_Result.lower(6,3), LU_echelon.lower(6,3));   ASSERT_EQ(LU_Result.lower(6,4), LU_echelon.lower(6,4));   ASSERT_EQ(LU_Result.lower(6,5), LU_echelon.lower(6,5));     ASSERT_EQ(LU_Result.lower(6,6), LU_echelon.lower(6,6));

    ASSERT_EQ(LU_Result.upper(0,0), LU_echelon.upper(0,0));   ASSERT_EQ(LU_Result.upper(0,1), LU_echelon.upper(0,1));   ASSERT_EQ(LU_Result.upper(0,2), LU_echelon.upper(0,2));     ASSERT_EQ(LU_Result.upper(0,3), LU_echelon.upper(0,3));   ASSERT_EQ(LU_Result.upper(0,4), LU_echelon.upper(0,4));   ASSERT_EQ(LU_Result.upper(0,5), LU_echelon.upper(0,5));     ASSERT_EQ(LU_Result.upper(0,6), LU_echelon.upper(0,6));
    ASSERT_EQ(LU_Result.upper(1,0), LU_echelon.upper(1,0));   ASSERT_EQ(LU_Result.upper(1,1), LU_echelon.upper(1,1));   ASSERT_EQ(LU_Result.upper(1,2),  LU_echelon.upper(1,2));    ASSERT_EQ(LU_Result.upper(1,3), LU_echelon.upper(1,3));   ASSERT_EQ(LU_Result.upper(1,4), LU_echelon.upper(1,4));   ASSERT_EQ(LU_Result.upper(1,5), LU_echelon.upper(1,5));     ASSERT_EQ(LU_Result.upper(1,6), LU_echelon.upper(1,6));
    ASSERT_EQ(LU_Result.upper(2,0), LU_echelon.upper(2,0));   ASSERT_EQ(LU_Result.upper(2,1), LU_echelon.upper(2,1));   ASSERT_EQ(LU_Result.upper(2,2), LU_echelon.upper(2,2));     ASSERT_EQ(LU_Result.upper(2,3), LU_echelon.upper(2,3));   ASSERT_EQ(LU_Result.upper(2,4), LU_echelon.upper(2,4));   ASSERT_EQ(LU_Result.upper(2,5), LU_echelon.upper(2,5));     ASSERT_EQ(LU_Result.upper(2,6), LU_echelon.upper(2,6));
    ASSERT_EQ(LU_Result.upper(3,0), LU_echelon.upper(3,0));   ASSERT_EQ(LU_Result.upper(3,1), LU_echelon.upper(3,1));   ASSERT_EQ(LU_Result.upper(3,2), LU_echelon.upper(3,2));     ASSERT_EQ(LU_Result.upper(3,3), LU_echelon.upper(3,3));   ASSERT_EQ(LU_Result.upper(3,4), LU_echelon.upper(3,4));   ASSERT_EQ(LU_Result.upper(3,5), LU_echelon.upper(3,5));     ASSERT_EQ(LU_Result.upper(3,6), LU_echelon.upper(3,6));
    ASSERT_EQ(LU_Result.upper(4,0), LU_echelon.upper(4,0));   ASSERT_EQ(LU_Result.upper(4,1), LU_echelon.upper(4,1));   ASSERT_EQ(LU_Result.upper(4,2), LU_echelon.upper(4,2));     ASSERT_EQ(LU_Result.upper(4,3), LU_echelon.upper(4,3));   ASSERT_EQ(LU_Result.upper(4,4), LU_echelon.upper(4,4));   ASSERT_EQ(LU_Result.upper(4,5), LU_echelon.upper(4,5));     ASSERT_EQ(LU_Result.upper(4,6), LU_echelon.upper(4,6));
    ASSERT_EQ(LU_Result.upper(5,0), LU_echelon.upper(5,0));   ASSERT_EQ(LU_Result.upper(5,1), LU_echelon.upper(5,1));   ASSERT_EQ(LU_Result.upper(5,2), LU_echelon.upper(5,2));     ASSERT_EQ(LU_Result.upper(5,3), LU_echelon.upper(5,3));   ASSERT_EQ(LU_Result.upper(5,4), LU_echelon.upper(5,4));   ASSERT_EQ(LU_Result.upper(5,5), LU_echelon.upper(5,5));     ASSERT_EQ(LU_Result.upper(5,6), LU_echelon.upper(5,6));
    ASSERT_EQ(LU_Result.upper(6,0), LU_echelon.upper(6,0));   ASSERT_EQ(LU_Result.upper(6,1), LU_echelon.upper(6,1));   ASSERT_EQ(LU_Result.upper(6,2), LU_echelon.upper(6,2));     ASSERT_EQ(LU_Result.upper(6,3), LU_echelon.upper(6,3));   ASSERT_EQ(LU_Result.upper(6,4), LU_echelon.upper(6,4));   ASSERT_EQ(LU_Result.upper(6,5), LU_echelon.upper(6,5));     ASSERT_EQ(LU_Result.upper(6,6), LU_echelon.upper(6,6));


}