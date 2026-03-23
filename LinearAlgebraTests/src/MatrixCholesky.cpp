//
// Created by dorian on 20.03.2026.
// stoicadorian@gmail.com
//
#include "gtest/gtest.h"
#include "Matrix.hpp"
#include "MatrixToolbox.hpp"

using namespace LinearAlgebra::Matrix;
using namespace LinearAlgebra::Vector;

class MatrixCholeskyTests : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        // 3x3 SPD matrix: A = [[4,2,2],[2,5,3],[2,3,6]]
        spd3x3DoubleData = std::vector<double>{ 4.0,  2.0,  2.0,
                                                2.0,  5.0,  3.0,
                                                2.0,  3.0,  6.0 };

        // 2x2 SPD matrix: A = [[4,2],[2,3]]
        spd2x2DoubleData = std::vector<double>{ 4.0, 2.0,
                                                2.0, 3.0 };
    }

    virtual void TearDown() {}

    std::vector<double> spd3x3DoubleData;
    std::vector<double> spd2x2DoubleData;
};


// ---------------------------------------------------------------------------
// factorizeCholesky — positive cases
// ---------------------------------------------------------------------------

TEST_F(MatrixCholeskyTests, FactorizeCholesky_3x3_Double_ReturnsL)
{
    const auto A = Matrix<double>(spd3x3DoubleData, 3, 3);
    const auto result = factorizeCholesky(A);

    ASSERT_TRUE(result.has_value());

    const auto& L = result->L;
    ASSERT_EQ(L.rows(), 3u);
    ASSERT_EQ(L.cols(), 3u);

    // L must be lower triangular
    ASSERT_TRUE(isLowerTriangular(L));
}

TEST_F(MatrixCholeskyTests, FactorizeCholesky_3x3_Double_ReconstructsA)
{
    const auto A = Matrix<double>(spd3x3DoubleData, 3, 3);
    const auto result = factorizeCholesky(A);

    ASSERT_TRUE(result.has_value());

    const auto& L   = result->L;
    const auto  Lt  = transpose(L);
    const auto  LLt = L * Lt;

    for (unsigned int r = 0; r < 3; r++)
        for (unsigned int c = 0; c < 3; c++)
            EXPECT_NEAR(static_cast<double>(LLt(r, c)), A(r, c), 1e-10);
}

TEST_F(MatrixCholeskyTests, FactorizeCholesky_2x2_Double_ReconstructsA)
{
    const auto A = Matrix<double>(spd2x2DoubleData, 2, 2);
    const auto result = factorizeCholesky(A);

    ASSERT_TRUE(result.has_value());

    const auto& L   = result->L;
    const auto  Lt  = transpose(L);
    const auto  LLt = L * Lt;

    for (unsigned int r = 0; r < 2; r++)
        for (unsigned int c = 0; c < 2; c++)
            EXPECT_NEAR(static_cast<double>(LLt(r, c)), A(r, c), 1e-10);
}

TEST_F(MatrixCholeskyTests, FactorizeCholesky_Identity_ReturnsIdentity)
{
    const auto A      = identity<double>(4);
    const auto result = factorizeCholesky(A);

    ASSERT_TRUE(result.has_value());

    const auto& L = result->L;
    // L of the identity must be the identity itself
    for (unsigned int r = 0; r < 4; r++)
        for (unsigned int c = 0; c < 4; c++)
            EXPECT_NEAR(static_cast<double>(L(r, c)), r == c ? 1.0 : 0.0, 1e-12);
}

TEST_F(MatrixCholeskyTests, FactorizeCholesky_IntMatrix_ReconstructsA)
{
    // 2x2 SPD integer matrix: [[5, 3],[3, 4]]  — det = 11 > 0, eigenvalues both positive
    const auto A      = Matrix<int>({5, 3, 3, 4}, 2, 2);
    const auto result = factorizeCholesky(A);

    ASSERT_TRUE(result.has_value());

    const auto& L   = result->L;
    const auto  Lt  = transpose(L);
    const auto  LLt = L * Lt;

    for (unsigned int r = 0; r < 2; r++)
        for (unsigned int c = 0; c < 2; c++)
            EXPECT_NEAR(static_cast<double>(LLt(r, c)), static_cast<double>(A(r, c)), 1e-10);
}

TEST_F(MatrixCholeskyTests, FactorizeCholesky_LargeMatrix_ReconstructsA)
{
    // 4x4 SPD matrix (diagonal dominant)
    const auto A = Matrix<double>({10.0, 2.0, 1.0, 0.5,
                                    2.0, 8.0, 1.5, 0.3,
                                    1.0, 1.5, 6.0, 0.7,
                                    0.5, 0.3, 0.7, 4.0 }, 4, 4);

    const auto result = factorizeCholesky(A);
    ASSERT_TRUE(result.has_value());

    const auto& L   = result->L;
    const auto  Lt  = transpose(L);
    const auto  LLt = L * Lt;

    for (unsigned int r = 0; r < 4; r++)
        for (unsigned int c = 0; c < 4; c++)
            EXPECT_NEAR(static_cast<double>(LLt(r, c)), A(r, c), 1e-10);
}


// ---------------------------------------------------------------------------
// factorizeCholesky — negative cases (returns nullopt)
// ---------------------------------------------------------------------------

TEST_F(MatrixCholeskyTests, FactorizeCholesky_NonSquare_ReturnsNullopt)
{
    const auto A = Matrix<double>({1.0, 2.0, 3.0, 4.0, 5.0, 6.0}, 2, 3);
    ASSERT_FALSE(factorizeCholesky(A).has_value());
}

TEST_F(MatrixCholeskyTests, FactorizeCholesky_NotSymmetric_ReturnsNullopt)
{
    // Asymmetric matrix
    const auto A = Matrix<double>({4.0, 3.0,
                                   1.0, 2.0}, 2, 2);
    ASSERT_FALSE(factorizeCholesky(A).has_value());
}

TEST_F(MatrixCholeskyTests, FactorizeCholesky_NotPositiveDefinite_ReturnsNullopt)
{
    // Symmetric but indefinite: eigenvalues include a negative one
    const auto A = Matrix<double>({1.0, 2.0,
                                   2.0, 1.0}, 2, 2);
    ASSERT_FALSE(factorizeCholesky(A).has_value());
}

TEST_F(MatrixCholeskyTests, FactorizeCholesky_NegativeDefinite_ReturnsNullopt)
{
    const auto A = Matrix<double>({-4.0, -2.0,
                                   -2.0, -3.0}, 2, 2);
    ASSERT_FALSE(factorizeCholesky(A).has_value());
}

TEST_F(MatrixCholeskyTests, FactorizeCholesky_SingularSymmetric_ReturnsNullopt)
{
    // Symmetric positive-semidefinite (zero eigenvalue) — not SPD
    const auto A = Matrix<double>({1.0, 1.0,
                                   1.0, 1.0}, 2, 2);
    ASSERT_FALSE(factorizeCholesky(A).has_value());
}


// ---------------------------------------------------------------------------
// solveCholesky
// ---------------------------------------------------------------------------

TEST_F(MatrixCholeskyTests, SolveCholesky_3x3_UniqueIntegerSolution)
{
    // A * x = b  where x = [1, 1, 1]
    const auto A = Matrix<double>(spd3x3DoubleData, 3, 3);
    // b = A * [1,1,1]^T = [8, 10, 11]
    const auto b = Vector<double>({8.0, 10.0, 11.0});

    const auto chol = factorizeCholesky(A);
    ASSERT_TRUE(chol.has_value());

    const auto x = solveCholesky(chol.value(), b);
    ASSERT_EQ(x.dim(), 3u);
    EXPECT_NEAR(static_cast<double>(x[0]), 1.0, 1e-10);
    EXPECT_NEAR(static_cast<double>(x[1]), 1.0, 1e-10);
    EXPECT_NEAR(static_cast<double>(x[2]), 1.0, 1e-10);
}

TEST_F(MatrixCholeskyTests, SolveCholesky_2x2_KnownSolution)
{
    // A = [[4,2],[2,3]], x = [2,-1], b = A*x = [6,1]
    const auto A = Matrix<double>(spd2x2DoubleData, 2, 2);
    const auto b = Vector<double>({6.0, 1.0});

    const auto chol = factorizeCholesky(A);
    ASSERT_TRUE(chol.has_value());

    const auto x = solveCholesky(chol.value(), b);
    ASSERT_EQ(x.dim(), 2u);
    EXPECT_NEAR(static_cast<double>(x[0]),  2.0, 1e-10);
    EXPECT_NEAR(static_cast<double>(x[1]), -1.0, 1e-10);
}

TEST_F(MatrixCholeskyTests, SolveCholesky_LongDoubleRHS_Converges)
{
    const auto A = Matrix<double>(spd3x3DoubleData, 3, 3);
    const auto b = Vector<long double>({8.0L, 10.0L, 11.0L});

    const auto chol = factorizeCholesky(A);
    ASSERT_TRUE(chol.has_value());

    const auto x = solveCholesky(chol.value(), b);
    EXPECT_NEAR(static_cast<double>(x[0]), 1.0, 1e-10);
    EXPECT_NEAR(static_cast<double>(x[1]), 1.0, 1e-10);
    EXPECT_NEAR(static_cast<double>(x[2]), 1.0, 1e-10);
}

TEST_F(MatrixCholeskyTests, SolveCholesky_VerifyResidual)
{
    // The residual || b - A*x || should be near zero for an SPD system
    const auto A = Matrix<double>({10.0, 2.0, 1.0, 0.5,
                                    2.0, 8.0, 1.5, 0.3,
                                    1.0, 1.5, 6.0, 0.7,
                                    0.5, 0.3, 0.7, 4.0}, 4, 4);

    const auto xExpected = Vector<double>({1.0, -2.0, 3.0, 0.5});
    // b = A * xExpected
    const auto b = A * xExpected;

    const auto chol = factorizeCholesky(A);
    ASSERT_TRUE(chol.has_value());

    const auto x = solveCholesky(chol.value(), b);
    for (unsigned int i = 0; i < 4; i++)
        EXPECT_NEAR(static_cast<double>(x[i]), xExpected[i], 1e-9);
}
