//
// Created by dorian on 10.01.2024.
// stoicadorian@gmail.com
//
#include "gtest/gtest.h"
#include "Matrix.hpp"
#include "MatrixHelpers.hpp"

using namespace LinearAlgebra::Matrix;
using namespace LinearAlgebra::Vector;

//Test pivots and rank computation for all kinds of matrices : 1) square invertible, 2) square singular and 3) rectangular.
class MatrixPivotsAndRankTests : public ::testing::Test
{

protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

    long double epsilon = 1e-9;
};


TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_3x3_invertible)
{
    const auto data = std::vector<int> {1,2,3,
                                        2,3,1,
                                        -2,3,-2};
    const auto matrix = Matrix<int>(data, 3, 3);

    ASSERT_EQ(matrix.rank(), 3);

    const auto pivots = matrix.getPivots();
    ASSERT_EQ(pivots[0].value, 1);      ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_EQ(pivots[1].value, -1);     ASSERT_EQ(pivots[1].rowIndex, 1);  ASSERT_EQ(pivots[1].colIndex, 1);
    ASSERT_EQ(pivots[2].value, -31);    ASSERT_EQ(pivots[2].rowIndex, 2);   ASSERT_EQ(pivots[2].colIndex, 2);
}


TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_3x4)
{
    const auto data = std::vector<int> {1,2,0,2,
                                        1,3,2,1,
                                        2,3,4,0};

    const auto matrix = Matrix<int>(data, 3, 4);

    ASSERT_EQ(matrix.rank(), 3);

    const auto pivots = matrix.getPivots();
    ASSERT_EQ(pivots[0].value, 1);      ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_EQ(pivots[1].value, 1);     ASSERT_EQ(pivots[1].rowIndex, 1);  ASSERT_EQ(pivots[1].colIndex, 1);
    ASSERT_EQ(pivots[2].value, 6);    ASSERT_EQ(pivots[2].rowIndex, 2);   ASSERT_EQ(pivots[2].colIndex, 2);
}


TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_3x3_double)
{
    const auto data = std::vector<double> {11./10,    12./10,     13./10,
                                           4,         5,          2,
                                           23./10,    32./10,     3};

    const auto matrix = Matrix<double>(data, 3, 3);

    ASSERT_EQ(matrix.rank(), 3);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 11./10, epsilon);      ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 7./11, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
    ASSERT_NEAR(pivots[2].value, 227./70, epsilon);     ASSERT_EQ(pivots[2].rowIndex, 2);   ASSERT_EQ(pivots[2].colIndex, 2);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_3x3_double_2)
{
    const auto data = std::vector<double> {1.23, 4.56, 7.89,
                                           1.45, 6.32, 7.44,
                                           5.43, 6.88, 1.43};

    const auto matrix = Matrix<double>(data, 3, 3);

    ASSERT_EQ(matrix.rank(), 3);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1.23, epsilon);                    ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 0.944390243902439, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
    ASSERT_NEAR(pivots[2].value, -59.516219008264463, epsilon);     ASSERT_EQ(pivots[2].rowIndex, 2);   ASSERT_EQ(pivots[2].colIndex, 2);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_5x5)
{
    const auto data = std::vector<double> {4,6,10,9,7,
                                           7,8,2,2,1,
                                           7,6,7,8,10,
                                           7,7,9,10,8,
                                           9,9,1,10,6};

    const auto matrix = Matrix<double>(data, 5, 5);

    ASSERT_EQ(matrix.rank(), 5);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 4, epsilon);               ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, -2.5, epsilon);            ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
    ASSERT_NEAR(pivots[2].value, 17.4, epsilon);            ASSERT_EQ(pivots[2].rowIndex, 2);   ASSERT_EQ(pivots[2].colIndex, 2);
    ASSERT_NEAR(pivots[3].value, 0.6034482758, epsilon);    ASSERT_EQ(pivots[3].rowIndex, 3);   ASSERT_EQ(pivots[3].colIndex, 3);
    ASSERT_NEAR(pivots[4].value, 33.333333333, epsilon);    ASSERT_EQ(pivots[4].rowIndex, 4);   ASSERT_EQ(pivots[4].colIndex, 4);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_4x4_Tridiagonal_Strang_1_7_1)
{
    const auto data = std::vector<int>{2,   -1,     0,      0,
                                       -1,   2,     -1,     0,
                                       0,    -1,    2,      -1,
                                       0,    0,     -1,     2};

    const auto matrix = Matrix<int>(data, 4, 4);

    ASSERT_EQ(matrix.rank(), 4);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 2, epsilon);               ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 3./2, epsilon);            ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
    ASSERT_NEAR(pivots[2].value, 4./3, epsilon);            ASSERT_EQ(pivots[2].rowIndex, 2);   ASSERT_EQ(pivots[2].colIndex, 2);
    ASSERT_NEAR(pivots[3].value, 5./4, epsilon);            ASSERT_EQ(pivots[3].rowIndex, 3);   ASSERT_EQ(pivots[3].colIndex, 3);
}


TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_5x5_Tridiagonal)
{
    const auto data = std::vector<int>{2,   -1,     0,      0,      0,
                                       -1,   2,     -1,     0,      0,
                                       0,    -1,    2,      -1,     0,
                                       0,    0,     -1,     2,      -1,
                                       0,    0,     0,     -1,      2};

    const auto matrix = Matrix<int>(data, 5, 5);

    ASSERT_EQ(matrix.rank(), 5);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 2, epsilon);               ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 3./2, epsilon);            ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
    ASSERT_NEAR(pivots[2].value, 4./3, epsilon);            ASSERT_EQ(pivots[2].rowIndex, 2);   ASSERT_EQ(pivots[2].colIndex, 2);
    ASSERT_NEAR(pivots[3].value, 5./4, epsilon);            ASSERT_EQ(pivots[3].rowIndex, 3);   ASSERT_EQ(pivots[3].colIndex, 3);
    ASSERT_NEAR(pivots[4].value, 6./5, epsilon);            ASSERT_EQ(pivots[4].rowIndex, 4);   ASSERT_EQ(pivots[4].colIndex, 4);
}


TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_5x5_Tridiagonal_Strang_1_7_2)
{
    const auto data = std::vector<int>{1,   -1,     0,      0,      0,
                                       -1,   2,     -1,     0,      0,
                                       0,    -1,    2,      -1,     0,
                                       0,    0,     -1,     2,      -1,
                                       0,    0,     0,     -1,      2};

    const auto matrix = Matrix<int>(data, 5, 5);

    ASSERT_EQ(matrix.rank(), 5);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);            ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 1, epsilon);            ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
    ASSERT_NEAR(pivots[2].value, 1, epsilon);            ASSERT_EQ(pivots[2].rowIndex, 2);   ASSERT_EQ(pivots[2].colIndex, 2);
    ASSERT_NEAR(pivots[3].value, 1, epsilon);            ASSERT_EQ(pivots[3].rowIndex, 3);   ASSERT_EQ(pivots[3].colIndex, 3);
    ASSERT_NEAR(pivots[4].value, 1, epsilon);            ASSERT_EQ(pivots[4].rowIndex, 4);   ASSERT_EQ(pivots[4].colIndex, 4);
}


TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Hilbert_3x3)
{
    const auto hilbert_mat = hilbert_matrix(3);

    ASSERT_EQ(hilbert_mat.rank(), 3);

    const auto pivots = hilbert_mat.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);               ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 1./12, epsilon);           ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
    ASSERT_NEAR(pivots[2].value, 1./180, epsilon);          ASSERT_EQ(pivots[2].rowIndex, 2);   ASSERT_EQ(pivots[2].colIndex, 2);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Hilbert_5x5)
{
    const auto hilbert_mat = hilbert_matrix(5);
    ASSERT_EQ(hilbert_mat.rank(), 5);

    const auto pivots = hilbert_mat.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);               ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 1./12, epsilon);           ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
    ASSERT_NEAR(pivots[2].value, 1./180, epsilon);          ASSERT_EQ(pivots[2].rowIndex, 2);   ASSERT_EQ(pivots[2].colIndex, 2);
    ASSERT_NEAR(pivots[3].value, 1./2800, epsilon);         ASSERT_EQ(pivots[3].rowIndex, 3);   ASSERT_EQ(pivots[3].colIndex, 3);
    ASSERT_NEAR(pivots[4].value, 1./44100, epsilon);        ASSERT_EQ(pivots[4].rowIndex, 4);   ASSERT_EQ(pivots[4].colIndex, 4);
}


TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Hilbert_7x7)
{
    const auto hilbert_mat = hilbert_matrix(7);
    ASSERT_EQ(hilbert_mat.rank(), 7);

    const auto pivots = hilbert_mat.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);               ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 1./12, epsilon);           ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
    ASSERT_NEAR(pivots[2].value, 1./180, epsilon);          ASSERT_EQ(pivots[2].rowIndex, 2);   ASSERT_EQ(pivots[2].colIndex, 2);
    ASSERT_NEAR(pivots[3].value, 1./2800, epsilon);         ASSERT_EQ(pivots[3].rowIndex, 3);   ASSERT_EQ(pivots[3].colIndex, 3);
    ASSERT_NEAR(pivots[4].value, 1./44100, epsilon);        ASSERT_EQ(pivots[4].rowIndex, 4);   ASSERT_EQ(pivots[4].colIndex, 4);
    ASSERT_NEAR(pivots[5].value, 1./698544, epsilon);         ASSERT_EQ(pivots[5].rowIndex, 5);   ASSERT_EQ(pivots[5].colIndex, 5);
    ASSERT_NEAR(pivots[6].value, 1./11099088, epsilon);        ASSERT_EQ(pivots[6].rowIndex, 6);   ASSERT_EQ(pivots[6].colIndex, 6);
}


TEST_F(MatrixPivotsAndRankTests, Chapter_1_5_problem_2)
{
    const auto data = std::vector<int>{5,7,8,
                                       10,16,19,
                                       5,15,26};

    const auto matrix = Matrix<int>(data, 3, 3);
    ASSERT_EQ(matrix.rank(), 3);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 5, epsilon);           ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 2, epsilon);           ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
    ASSERT_NEAR(pivots[2].value, 6, epsilon);           ASSERT_EQ(pivots[2].rowIndex, 2);   ASSERT_EQ(pivots[2].colIndex, 2);
}


TEST_F(MatrixPivotsAndRankTests, Chapter_1_5_problem_4b)
{
    const auto data = std::vector<int>{3,1, 1,
                                       1, 3, 1,
                                       1, 1, 3};

    const auto matrix = Matrix<int>(data, 3, 3);

    ASSERT_EQ(matrix.rank(), 3);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 3, epsilon);           ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 8./3, epsilon);        ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
    ASSERT_NEAR(pivots[2].value, 15./6, epsilon);       ASSERT_EQ(pivots[2].rowIndex, 2);   ASSERT_EQ(pivots[2].colIndex, 2);
}


TEST_F(MatrixPivotsAndRankTests, Chapter_1_5_problem_4c)
{
    const auto data = std::vector<int>{1,1,1,
                                       1,4,4,
                                       1,4,8};

    const auto matrix = Matrix<int>(data, 3, 3);

    ASSERT_EQ(matrix.rank(), 3);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 3, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
    ASSERT_NEAR(pivots[2].value, 4, epsilon);       ASSERT_EQ(pivots[2].rowIndex, 2);   ASSERT_EQ(pivots[2].colIndex, 2);
}

TEST_F(MatrixPivotsAndRankTests, Chapter_1_5_problem_5)
{
    const auto data = std::vector<int>{2,3,3,
                                       0,5,7,
                                       6,9,8};

    const auto matrix = Matrix<int>(data, 3, 3);
    ASSERT_EQ(matrix.rank(), 3);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 2, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 5, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
    ASSERT_NEAR(pivots[2].value, -1, epsilon);       ASSERT_EQ(pivots[2].rowIndex, 2);   ASSERT_EQ(pivots[2].colIndex, 2);
}

TEST_F(MatrixPivotsAndRankTests, Chapter_1_5_problem_21)
{
    const auto data = std::vector<int>{1,1,1,
                                       1,2,3,
                                       1,3,6};

    const auto matrix = Matrix<int>(data, 3, 3);

    ASSERT_EQ(matrix.rank(), 3);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 1, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
    ASSERT_NEAR(pivots[2].value, 1, epsilon);       ASSERT_EQ(pivots[2].rowIndex, 2);   ASSERT_EQ(pivots[2].colIndex, 2);
}

TEST_F(MatrixPivotsAndRankTests, Chapter_1_5_problem_23)
{
    const auto data = std::vector<int>{1,1,1,
                                       2,4,5,
                                       0,4,0};

    const auto matrix = Matrix<int>(data, 3, 3);
    ASSERT_EQ(matrix.rank(), 3);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 2, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
    ASSERT_NEAR(pivots[2].value, -6, epsilon);       ASSERT_EQ(pivots[2].rowIndex, 2);   ASSERT_EQ(pivots[2].colIndex, 2);
}


TEST_F(MatrixPivotsAndRankTests, Chapter_1_5_problem_24)
{
    const auto data = std::vector<int>{1,0,1,
                                       2,2,2,
                                       3,4,5};

    const auto matrix = Matrix<int>(data, 3, 3);
    ASSERT_EQ(matrix.rank(), 3);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 2, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
    ASSERT_NEAR(pivots[2].value, 2, epsilon);       ASSERT_EQ(pivots[2].rowIndex, 2);   ASSERT_EQ(pivots[2].colIndex, 2);
}


TEST_F(MatrixPivotsAndRankTests, Chapter_1_5_problem_27)
{
    const auto data = std::vector<int>{2,4,8,
                                       0,3,9,
                                       0,0,7};

    const auto matrix = Matrix<int>(data, 3, 3);

    ASSERT_EQ(matrix.rank(), 3);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 2, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 3, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
    ASSERT_NEAR(pivots[2].value, 7, epsilon);       ASSERT_EQ(pivots[2].rowIndex, 2);   ASSERT_EQ(pivots[2].colIndex, 2);
}

TEST_F(MatrixPivotsAndRankTests, Chapter_1_5_problem_28b)
{
    const auto data = std::vector<int>{1,4,0,
                                       4,12,4,
                                       0,4,0};

    const auto matrix = Matrix<int>(data, 3, 3);
    ASSERT_EQ(matrix.rank(), 3);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, -4, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
    ASSERT_NEAR(pivots[2].value, 4, epsilon);       ASSERT_EQ(pivots[2].rowIndex, 2);   ASSERT_EQ(pivots[2].colIndex, 2);
}


TEST_F(MatrixPivotsAndRankTests, Chapter_1_5_problem_31a)
{
    const auto data = std::vector<int>{1,1,0,
                                       1,2,1,
                                       0,1,2};

    const auto matrix = Matrix<int>(data, 3, 3);
    ASSERT_EQ(matrix.rank(), 3);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 1, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
    ASSERT_NEAR(pivots[2].value, 1, epsilon);       ASSERT_EQ(pivots[2].rowIndex, 2);   ASSERT_EQ(pivots[2].colIndex, 2);
}

TEST_F(MatrixPivotsAndRankTests, Chapter_1_5_problem_33)
{
    const auto data = std::vector<int>{1,1,1,
                                       1,2,2,
                                       1,2,3};

    const auto matrix = Matrix<int>(data, 3, 3);

    ASSERT_EQ(matrix.rank(), 3);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 1, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
    ASSERT_NEAR(pivots[2].value, 1, epsilon);       ASSERT_EQ(pivots[2].rowIndex, 2);   ASSERT_EQ(pivots[2].colIndex, 2);
}

TEST_F(MatrixPivotsAndRankTests, Chapter_1_review_problem_5a)
{
    const auto data = std::vector<int>{1,0,1,
                                       1,1,0,
                                       1,1,1};

    const auto matrix = Matrix<int>(data, 3,3);

    ASSERT_EQ(matrix.rank(), 3);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 1, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
    ASSERT_NEAR(pivots[2].value, 1, epsilon);       ASSERT_EQ(pivots[2].rowIndex, 2);   ASSERT_EQ(pivots[2].colIndex, 2);
}

TEST_F(MatrixPivotsAndRankTests, Chapter_1_review_problem_5b_permutation)
{
    const auto data = std::vector<int>{0,1,1,
                                       1,0,1,
                                       1,1,0};

    const auto matrix = Matrix<int>(data, 3,3);

    ASSERT_EQ(matrix.rank(), 3);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 1, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
    ASSERT_NEAR(pivots[2].value, -2, epsilon);       ASSERT_EQ(pivots[2].rowIndex, 2);   ASSERT_EQ(pivots[2].colIndex, 2);
}

TEST_F(MatrixPivotsAndRankTests, Chapter_1_review_problem_17)
{
    const auto data = std::vector<int>{1,2,0,
                                       2,6,4,
                                       0,4,11};

    const auto matrix = Matrix<int>(data, 3,3);

    ASSERT_EQ(matrix.rank(), 3);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 2, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
    ASSERT_NEAR(pivots[2].value, 3, epsilon);       ASSERT_EQ(pivots[2].rowIndex, 2);   ASSERT_EQ(pivots[2].colIndex, 2);
}

TEST_F(MatrixPivotsAndRankTests,  PivotsAndRank_Singular_4x4)
{
    const auto data = std::vector<int>{2,1,4,-1,
                                       3,-2,1,0,
                                       5,1,3,2,
                                       -1,3,3,-1};

    const auto matrix = Matrix<int>(data, 4,4);

    ASSERT_EQ(matrix.rank(), 3);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 2, epsilon);                   ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, -3.5, epsilon);                ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
    ASSERT_NEAR(pivots[2].value, -4.85714285714, epsilon);      ASSERT_EQ(pivots[2].rowIndex, 2);   ASSERT_EQ(pivots[2].colIndex, 2);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Example_3x4)
{
    const auto data = std::vector<int> {1,2,0,2,
                                        1,3,2,1,
                                        2,3,4,0};

    const auto matrix = Matrix<int>(data, 3, 4);

    ASSERT_EQ(matrix.rank(), 3);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 1, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
    ASSERT_NEAR(pivots[2].value, 6, epsilon);       ASSERT_EQ(pivots[2].rowIndex, 2);   ASSERT_EQ(pivots[2].colIndex, 2);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Strang_Chapter_2_2_Example)
{
    const auto data = std::vector<int>{1,3,3,2,
                                       2,6,9,7,
                                       -1,-3,3,4};

    const auto matrix = Matrix<int>(data, 3, 4);

    ASSERT_EQ(matrix.rank(), 2);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 3, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 2);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Strang_Chapter_2_2_Another_Example)
{
    const auto data = std::vector<int>{1,2,3,5,
                                       2,4,8,12,
                                       3,6,7,13};

    const auto matrix = Matrix<int>(data, 3, 4);

    ASSERT_EQ(matrix.rank(), 2);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 2, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 2);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Strang_Chapter_2_2_Problem_2_a)
{
    const auto data = std::vector<int>{1,2,0,1,
                                       0,1,1,0,
                                       1,2,0,1};

    const auto matrix = Matrix<int>(data, 3, 4);

    ASSERT_EQ(matrix.rank(), 2);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 1, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Strang_Strang_Chapter_2_2_Problem_2_b)
{
    const auto data = std::vector<int>{1,2,3,
                                       4,5,6,
                                       7,8,9};

    const auto matrix = Matrix<int>(data, 3, 3);

    ASSERT_EQ(matrix.rank(), 2);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, -3, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Strang_Chapter_2_2_Problem_3)
{
    const auto data = std::vector<int>{0,1,0,3,
                                       0,2,0,6};

    const auto matrix = Matrix<int>(data, 2, 4);

    ASSERT_EQ(matrix.rank(), 1);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 1);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Strang_Chapter_2_2_Problem_4)
{
    const auto data = std::vector<int>{0,0,
                                       1,2,
                                       0,0,
                                       3,6};

    const auto matrix = Matrix<int>(data, 4, 2);

    ASSERT_EQ(matrix.rank(), 1);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Strang_Chapter_2_2_Problem_5a)
{
    const auto data = std::vector<int>{1,2,2,
                                       2,4,5};

    const auto matrix = Matrix<int>(data, 2, 3);

    ASSERT_EQ(matrix.rank(), 2);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 1, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 2);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Strang_Chapter_2_2_Problem_5b)
{
    const auto data = std::vector<int>{1,2,2,
                                       2,4,4};

    const auto matrix = Matrix<int>(data, 2, 3);
    ASSERT_EQ(matrix.rank(), 1);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Strang_Chapter_2_2_Problem_6)
{
    const auto data = std::vector<int>{1,0,
                                       0,1,
                                       2,3};

    const auto matrix = Matrix<int>(data, 3, 2);

    ASSERT_EQ(matrix.rank(), 2);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 1, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
}


TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Strang_Chapter_2_2_Problem_7)
{
    const auto data = std::vector<int>{1,1,2,
                                       2,3,-1,
                                       3,4,1};

    const auto matrix = Matrix<int>(data, 3, 3);
    ASSERT_EQ(matrix.rank(), 2);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 1, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Strang_Chapter_2_2_Problem_8)
{
    const auto data = std::vector<int>{1,2,0,3,
                                       2,4,0,7};

    const auto matrix = Matrix<int>(data, 2, 4);
    ASSERT_EQ(matrix.rank(), 2);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 1, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 3);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Strang_Chapter_2_2_Problem_9)
{
    const auto data = std::vector<int>{1,2,3,4,
                                       0,0,1,2,
                                       0,0,0,0};

    const auto matrix = Matrix<int>(data, 3, 4);
    ASSERT_EQ(matrix.rank(), 2);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 1, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 2);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Strang_Chapter_2_2_Problem_13a)
{
    const auto data = std::vector<int>{1,1,1,1,
                                       1,1,1,1,
                                       1,1,1,1};

    const auto matrix = Matrix<int>(data, 3, 4);
    ASSERT_EQ(matrix.rank(), 1);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Strang_Chapter_2_2_Problem_13b)
{
    //a_ij = (-1)^(i+j)
    const auto data = std::vector<int>{1,-1,1,-1,
                                       -1,1,-1,1,
                                       1,-1,1,-1,
                                       -1,1,-1,1};

    const auto matrix = Matrix<int>(data, 4, 4);

    ASSERT_EQ(matrix.rank(), 1);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Strang_Chapter_2_2_Problem_13c)
{
    //a_ij = (-1)^(j)
    const auto data = std::vector<int>{-1,1,-1,1,
                                       -1,1,-1,1,
                                       -1,1,-1,1};

    const auto matrix = Matrix<int>(data, 3, 4);

    ASSERT_EQ(matrix.rank(), 1);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, -1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Strang_Chapter_2_2_Problem_13d)
{
    //a_ij = (-1)^(i*j)
    const auto data = std::vector<int>{-1,1,-1,1,
                                       1,1,1,1,
                                       -1,1,-1,1,
                                       1,1,1,1};

    const auto matrix = Matrix<int>(data, 4, 4);
    ASSERT_EQ(matrix.rank(), 2);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, -1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 2, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Strang_Chapter_2_2_Problem_14a_3x3)
{
    const auto data = std::vector<int>{0,0,0,
                                       0,0,3,
                                       2,4,6};

    const auto matrix = Matrix<int>(data, 3, 3);
    ASSERT_EQ(matrix.rank(), 2);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 2, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 3, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 2);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Strang_Chapter_2_2_Problem_14b_3x6)
{
    const auto data = std::vector<int>{0,0,0,0,0,0,
                                       0,0,3,0,0,3,
                                       2,4,6,2,4,6};

    const auto matrix = Matrix<int>(data, 3, 6);
    ASSERT_EQ(matrix.rank(), 2);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 2, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 3, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 2);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Strang_Chapter_2_2_Problem_14c_6x6_multiple_permutations)
{
    const auto data = std::vector<int>{0,0,0,0,0,0,
                                       0,0,3,0,0,3,
                                       2,4,6,2,4,6,
                                       0,0,0,0,0,0,
                                       0,0,3,0,0,0,
                                       2,4,6,0,0,0};

    const auto matrix = Matrix<int>(data, 6, 6);
    ASSERT_EQ(matrix.rank(), 4);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 2, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 3, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 2);
    ASSERT_NEAR(pivots[2].value, -2, epsilon);       ASSERT_EQ(pivots[2].rowIndex, 2);   ASSERT_EQ(pivots[2].colIndex, 3);
    ASSERT_NEAR(pivots[3].value, -3, epsilon);       ASSERT_EQ(pivots[3].rowIndex, 3);   ASSERT_EQ(pivots[3].colIndex, 5);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Strang_Chapter_2_2_Problem_22)
{
    const auto data = std::vector<int>{8,3,16,
                                       16,8,32};

    const auto matrix = Matrix<int>(data, 2, 3);
    ASSERT_EQ(matrix.rank(), 2);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 8, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 2, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Strang_Chapter_2_2_Problem_30)
{
    const auto data = std::vector<int>{2,4,6,4,
                                       2,5,7,6,
                                       2,3,5,2};

    const auto matrix = Matrix<int>(data, 3, 4);
    ASSERT_EQ(matrix.rank(), 2);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 2, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 1, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Strang_Chapter_2_2_Problem_33a)
{
    const auto data = std::vector<int>{1,3,3,
                                       2,6,9,
                                       -1,-3,3};

    const auto matrix = Matrix<int>(data, 3, 3);

    ASSERT_EQ(matrix.rank(), 2);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 3, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 2);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Strang_Chapter_2_2_Problem_33b)
{
    const auto data = std::vector<int>{1,3,1,2,
                                       2,6,4,8,
                                       0,0,2,4};

    const auto matrix = Matrix<int>(data, 3, 4);
    ASSERT_EQ(matrix.rank(), 2);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 2, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 2);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Strang_Chapter_2_2_Problem_34)
{
    const auto data = std::vector<int>{1,2,-2,
                                       2,5,-4,
                                       4,9,-8};

    const auto matrix = Matrix<int>(data, 3, 3);
    ASSERT_EQ(matrix.rank(), 2);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 1, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Strang_Chapter_2_2_Problem_35a)
{
    const auto data = std::vector<int>{1,2,
                                       2,4,
                                       2,5,
                                       3,9};

    const auto matrix = Matrix<int>(data, 4, 2);
    ASSERT_EQ(matrix.rank(), 2);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 1, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Strang_Chapter_2_2_Problem_35b)
{
    const auto data = std::vector<int>{1,2,3,
                                       2,4,6,
                                       2,5,7,
                                       3,9,12};

    const auto matrix = Matrix<int>(data, 4, 3);
    ASSERT_EQ(matrix.rank(), 2);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 1, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Strang_Chapter_2_2_Problem_36a)
{
    const auto data = std::vector<int>{1,2,1,
                                       2,6,3,
                                       0,2,5};

    const auto matrix = Matrix<int>(data, 3, 3);
    ASSERT_EQ(matrix.rank(), 3);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 2, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
    ASSERT_NEAR(pivots[2].value, 4, epsilon);       ASSERT_EQ(pivots[2].rowIndex, 2);   ASSERT_EQ(pivots[2].colIndex, 2);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Strang_Chapter_2_2_Problem_36b)
{
    const auto data = std::vector<int>{1,1,1,
                                       1,2,4,
                                       2,4,8};

    const auto matrix = Matrix<int>(data, 3, 3);
    ASSERT_EQ(matrix.rank(), 2);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 1, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Strang_Chapter_2_2_Problem_48)
{
    const auto data = std::vector<int>{1,0,2,3,
                                       1,3,2,0,
                                       2,0,4,9};

    const auto matrix = Matrix<int>(data, 3, 4);
    ASSERT_EQ(matrix.rank(), 3);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 3, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
    ASSERT_NEAR(pivots[2].value, 3, epsilon);       ASSERT_EQ(pivots[2].rowIndex, 2);   ASSERT_EQ(pivots[2].colIndex, 3);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Strang_Chapter_2_2_Problem_52a)
{
    const auto data = std::vector<int>{1,2,2,4,6,
                                       1,2,3,6,9,
                                       0,0,1,2,3};

    const auto matrix = Matrix<int>(data, 3, 5);

    ASSERT_EQ(matrix.rank(), 2);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 1, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 1, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 2);
}

TEST_F(MatrixPivotsAndRankTests, PivotsAndRank_Strang_Chapter_2_2_Problem_52b)
{
    const auto data = std::vector<int>{2,4,2,
                                       0,4,4,
                                       0,8,8};

    const auto matrix = Matrix<int>(data, 3, 3);
    ASSERT_EQ(matrix.rank(), 2);

    const auto pivots = matrix.getPivots();
    ASSERT_NEAR(pivots[0].value, 2, epsilon);       ASSERT_EQ(pivots[0].rowIndex, 0);   ASSERT_EQ(pivots[0].colIndex, 0);
    ASSERT_NEAR(pivots[1].value, 4, epsilon);       ASSERT_EQ(pivots[1].rowIndex, 1);   ASSERT_EQ(pivots[1].colIndex, 1);
}