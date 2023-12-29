//
// Created by dorian on 29.12.2023.
// stoicadorian@gmail.com
//
#include "gtest/gtest.h"
#include "Matrix.hpp"

using namespace LinearAlgebra::Matrix;
using namespace LinearAlgebra::Vector;

//Test LU decomposition with various Hilbert matrices

Matrix<double> hilbert_matrix(const unsigned int dim)
{
    Matrix<double> h(dim, dim);
    for (unsigned int rIdx = 0; rIdx<dim; rIdx++)
        for (unsigned int cIdx = 0; cIdx<dim; cIdx++)
            h(rIdx,cIdx) = 1./((rIdx+1)+(cIdx+1) - 1);

    return h;
}

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
    const auto LU_Result = hilbert_mat.LU();

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
}

TEST_F(MatrixLUFactorization_HilbertMatrices, LUFactorization_Hilbert_5x5)
{
    const auto hilbert_mat = hilbert_matrix(5);
    const auto LU_Result = hilbert_mat.LU();

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
}

TEST_F(MatrixLUFactorization_HilbertMatrices, LUFactorization_Hilbert_7x7)
{
    const auto hilbert_mat = hilbert_matrix(7);
    const auto LU_Result = hilbert_mat.LU();

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

    //Check if LU is numerically stable eoough to reconstruct the initial mat
    const auto LU = LU_Result.lower.multiply(LU_Result.upper);
    ASSERT_NEAR(LU(0,0), hilbert_mat(0,0), epsilon);  ASSERT_NEAR(LU(0,1), hilbert_mat(0,1), epsilon);      ASSERT_NEAR(LU(0,2), hilbert_mat(0,2), epsilon);    ASSERT_NEAR(LU(0,3), hilbert_mat(0,3), epsilon);    ASSERT_NEAR(LU(0,4), hilbert_mat(0,4), epsilon);    ASSERT_NEAR(LU(0,5), hilbert_mat(0,5), epsilon);    ASSERT_NEAR(LU(0,6), hilbert_mat(0,6), epsilon);
    ASSERT_NEAR(LU(1,0), hilbert_mat(1,0), epsilon);  ASSERT_NEAR(LU(1,1), hilbert_mat(1,1), epsilon);      ASSERT_NEAR(LU(1,2), hilbert_mat(1,2), epsilon);    ASSERT_NEAR(LU(1,3), hilbert_mat(1,3), epsilon);    ASSERT_NEAR(LU(1,4), hilbert_mat(1,4), epsilon);    ASSERT_NEAR(LU(1,5), hilbert_mat(1,5), epsilon);    ASSERT_NEAR(LU(1,6), hilbert_mat(1,6), epsilon);
    ASSERT_NEAR(LU(2,0), hilbert_mat(2,0), epsilon);  ASSERT_NEAR(LU(2,1), hilbert_mat(2,1), epsilon);      ASSERT_NEAR(LU(2,2), hilbert_mat(2,2), epsilon);    ASSERT_NEAR(LU(2,3), hilbert_mat(2,3), epsilon);    ASSERT_NEAR(LU(2,4), hilbert_mat(2,4), epsilon);    ASSERT_NEAR(LU(2,5), hilbert_mat(2,5), epsilon);    ASSERT_NEAR(LU(2,6), hilbert_mat(2,6), epsilon);
    ASSERT_NEAR(LU(3,0), hilbert_mat(3,0), epsilon);  ASSERT_NEAR(LU(3,1), hilbert_mat(3,1), epsilon);      ASSERT_NEAR(LU(3,2), hilbert_mat(3,2), epsilon);    ASSERT_NEAR(LU(3,3), hilbert_mat(3,3), epsilon);    ASSERT_NEAR(LU(3,4), hilbert_mat(3,4), epsilon);    ASSERT_NEAR(LU(3,5), hilbert_mat(3,5), epsilon);    ASSERT_NEAR(LU(3,6), hilbert_mat(3,6), epsilon);
    ASSERT_NEAR(LU(4,0), hilbert_mat(4,0), epsilon);  ASSERT_NEAR(LU(4,1), hilbert_mat(4,1), epsilon);      ASSERT_NEAR(LU(4,2), hilbert_mat(4,2), epsilon);    ASSERT_NEAR(LU(4,3), hilbert_mat(4,3), epsilon);    ASSERT_NEAR(LU(4,4), hilbert_mat(4,4), epsilon);    ASSERT_NEAR(LU(4,5), hilbert_mat(4,5), epsilon);    ASSERT_NEAR(LU(4,6), hilbert_mat(4,6), epsilon);
    ASSERT_NEAR(LU(5,0), hilbert_mat(5,0), epsilon);  ASSERT_NEAR(LU(5,1), hilbert_mat(5,1), epsilon);      ASSERT_NEAR(LU(5,2), hilbert_mat(5,2), epsilon);    ASSERT_NEAR(LU(5,3), hilbert_mat(5,3), epsilon);    ASSERT_NEAR(LU(5,4), hilbert_mat(5,4), epsilon);    ASSERT_NEAR(LU(5,5), hilbert_mat(5,5), epsilon);    ASSERT_NEAR(LU(5,6), hilbert_mat(5,6), epsilon);
    ASSERT_NEAR(LU(6,0), hilbert_mat(6,0), epsilon);  ASSERT_NEAR(LU(6,1), hilbert_mat(6,1), epsilon);      ASSERT_NEAR(LU(6,2), hilbert_mat(6,2), epsilon);    ASSERT_NEAR(LU(6,3), hilbert_mat(6,3), epsilon);    ASSERT_NEAR(LU(6,4), hilbert_mat(6,4), epsilon);    ASSERT_NEAR(LU(6,5), hilbert_mat(6,5), epsilon);    ASSERT_NEAR(LU(6,6), hilbert_mat(6,6), epsilon);

}