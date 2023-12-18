//
// Created by dorian on 17.12.2023.
// stoicadorian@gmail.com
//

#include "gtest/gtest.h"
#include "Matrix.hpp"

using namespace LinearAlgebra::Matrix;

class MatrixMultiplicationTests : public ::testing::Test
{

protected:
    virtual void SetUp()
    {
        dummyIntData    = std::vector<int>{     1, 2, 3,
                                                4, 5, 6,
                                                7, 8, 9};

        dummyFloatData  = std::vector<float>{   1.f, 3.f, 8.f,
                                                2.f, 7.f, 6.1f,
                                                0.f, -1.f, 7.f};

        dummyDoubleData = std::vector<double>{  1.0, 2.0, 3.0,
                                                4.0, 5.0, 6.0,
                                                9.1, 8.0, 7.0};

        intMat      = Matrix<int>(dummyIntData, 3, 3);
        floatMat    = Matrix<float>(dummyFloatData, 3, 3);
        doubleMat   = Matrix<double>(dummyDoubleData, 3, 3);
    }

    virtual void TearDown()
    {
    }

    std::vector<int>    dummyIntData;
    std::vector<double> dummyDoubleData;
    std::vector<float>  dummyFloatData;
    Matrix<int>         intMat      = Matrix<int>(3, 3);
    Matrix<float>       floatMat    = Matrix<float>(3, 3);
    Matrix<double>      doubleMat   = Matrix<double>(3, 3);
};


TEST_F(MatrixMultiplicationTests, Multiply_DifferentShapes)
{
    auto data_A = std::vector<int>{1, 2, 3, 4, 5,
                                   6, 7, 8, 9, 10};
    auto data_B = std::vector<int>{  1, 2,
                                     3, 4,
                                     5, 6,
                                     7, 8,
                                     9, 10};

    const auto mat_A    = Matrix<int>(data_A, 2, 5);
    const auto mat_B    = Matrix<int>(data_B, 5, 2);

    const auto resultAB = mat_A.multiply(mat_B);
    ASSERT_EQ(resultAB.rows(), 2);
    ASSERT_EQ(resultAB.cols(), 2);

    ASSERT_EQ(resultAB(0,0), 95);   ASSERT_EQ(resultAB(0,1), 110);
    ASSERT_EQ(resultAB(1,0), 220);  ASSERT_EQ(resultAB(1,1), 260);

    const auto resultBA = mat_B.multiply(mat_A);
    ASSERT_EQ(resultBA.rows(), 5);
    ASSERT_EQ(resultBA.cols(), 5);

    ASSERT_EQ(resultBA(0,0), 13);   ASSERT_EQ(resultBA(0,1), 16);   ASSERT_EQ(resultBA(0,2), 19);   ASSERT_EQ(resultBA(0,3), 22);   ASSERT_EQ(resultBA(0,4), 25);
    ASSERT_EQ(resultBA(1,0), 27);   ASSERT_EQ(resultBA(1,1), 34);   ASSERT_EQ(resultBA(1,2), 41);   ASSERT_EQ(resultBA(1,3), 48);   ASSERT_EQ(resultBA(1,4), 55);
    ASSERT_EQ(resultBA(2,0), 41);   ASSERT_EQ(resultBA(2,1), 52);   ASSERT_EQ(resultBA(2,2), 63);   ASSERT_EQ(resultBA(2,3), 74);   ASSERT_EQ(resultBA(2,4), 85);
    ASSERT_EQ(resultBA(3,0), 55);   ASSERT_EQ(resultBA(3,1), 70);   ASSERT_EQ(resultBA(3,2), 85);   ASSERT_EQ(resultBA(3,3), 100);  ASSERT_EQ(resultBA(3,4), 115);
    ASSERT_EQ(resultBA(4,0), 69);   ASSERT_EQ(resultBA(4,1), 88);   ASSERT_EQ(resultBA(4,2), 107);  ASSERT_EQ(resultBA(4,3), 126);  ASSERT_EQ(resultBA(4,4), 145);
}

TEST_F(MatrixMultiplicationTests, Multiply_Matrices_SameType)
{
    const auto result = intMat.multiply(intMat);

    ASSERT_EQ(result(0,0), 30);     ASSERT_EQ(result(0,1), 36);     ASSERT_EQ(result(0,2), 42);
    ASSERT_EQ(result(1,0), 66);     ASSERT_EQ(result(1,1), 81);     ASSERT_EQ(result(1,2), 96);
    ASSERT_EQ(result(2,0), 102);    ASSERT_EQ(result(2,1), 126);    ASSERT_EQ(result(2,2), 150);

    const auto floatResult = floatMat.multiply(floatMat);
    const float eps = 1e-5f;
    ASSERT_NEAR(floatResult(0,0), 7.f, eps);      ASSERT_NEAR(floatResult(0,1),  16.f, eps);        ASSERT_NEAR(floatResult(0,2), 82.3f, eps);
    ASSERT_NEAR(floatResult(1,0), 16.f, eps);     ASSERT_NEAR(floatResult(1,1), 48.9f, eps);        ASSERT_NEAR(floatResult(1,2), 101.4f, eps);
    ASSERT_NEAR(floatResult(2,0), -2.f, eps);     ASSERT_NEAR(floatResult(2,1), -14.f, eps);        ASSERT_NEAR(floatResult(2,2), 42.9f, eps);

    const auto doubleResult = doubleMat.multiply(doubleMat);
    const double epsd = 1e-9;
    ASSERT_NEAR(doubleResult(0,0), 36.3, epsd);     ASSERT_NEAR(doubleResult(0,1),  36., epsd);     ASSERT_NEAR(doubleResult(0,2), 36., epsd);
    ASSERT_NEAR(doubleResult(1,0), 78.6, epsd);     ASSERT_NEAR(doubleResult(1,1), 81., epsd);      ASSERT_NEAR(doubleResult(1,2), 84., epsd);
    ASSERT_NEAR(doubleResult(2,0), 104.8, epsd);    ASSERT_NEAR(doubleResult(2,1), 114.2, epsd);    ASSERT_NEAR(doubleResult(2,2), 124.3, epsd);
}

TEST_F(MatrixMultiplicationTests, Multiply_Int_Float_And_Float_Int)
{
    const auto result_AB = intMat.multiply(floatMat);
    const auto result_BA = floatMat.multiply(intMat);

    const float eps = 1e-5f;
    ASSERT_NEAR(result_AB(0,0), 5.f, eps);      ASSERT_NEAR(result_AB(0,1),  14.f, eps);    ASSERT_NEAR(result_AB(0,2), 41.2f, eps);
    ASSERT_NEAR(result_AB(1,0), 14.f, eps);     ASSERT_NEAR(result_AB(1,1), 41.f, eps);     ASSERT_NEAR(result_AB(1,2), 104.5f, eps);
    ASSERT_NEAR(result_AB(2,0), 23.f, eps);     ASSERT_NEAR(result_AB(2,1), 68.f, eps);     ASSERT_NEAR(result_AB(2,2), 167.8f, eps);

    ASSERT_NEAR(result_BA(0,0), 69.f, eps);     ASSERT_NEAR(result_BA(0,1), 81.f, eps);     ASSERT_NEAR(result_BA(0,2), 93.f, eps);
    ASSERT_NEAR(result_BA(1,0), 72.7f, eps);    ASSERT_NEAR(result_BA(1,1), 87.8f, eps);    ASSERT_NEAR(result_BA(1,2), 102.9f, eps);
    ASSERT_NEAR(result_BA(2,0), 45.f, eps);     ASSERT_NEAR(result_BA(2,1), 51.f, eps);     ASSERT_NEAR(result_BA(2,2), 57.f, eps);
}

TEST_F(MatrixMultiplicationTests, Multiply_Int_Double_And_Double_Int)
{
    const auto result_AB = intMat.multiply(doubleMat);
    const auto result_BA = doubleMat.multiply(intMat);

    const double eps = 1e-9;
    ASSERT_NEAR(result_AB(0,0), 36.3, eps);     ASSERT_NEAR(result_AB(0,1),  36., eps);     ASSERT_NEAR(result_AB(0,2), 36., eps);
    ASSERT_NEAR(result_AB(1,0), 78.6, eps);     ASSERT_NEAR(result_AB(1,1), 81., eps);      ASSERT_NEAR(result_AB(1,2), 84., eps);
    ASSERT_NEAR(result_AB(2,0), 120.9, eps);    ASSERT_NEAR(result_AB(2,1), 126., eps);     ASSERT_NEAR(result_AB(2,2), 132., eps);

    ASSERT_NEAR(result_BA(0,0), 30., eps);     ASSERT_NEAR(result_BA(0,1),  36., eps);      ASSERT_NEAR(result_BA(0,2), 42., eps);
    ASSERT_NEAR(result_BA(1,0), 66., eps);     ASSERT_NEAR(result_BA(1,1), 81., eps);       ASSERT_NEAR(result_BA(1,2), 96., eps);
    ASSERT_NEAR(result_BA(2,0), 90.1, eps);    ASSERT_NEAR(result_BA(2,1), 114.2, eps);     ASSERT_NEAR(result_BA(2,2), 138.3, eps);
}

TEST_F(MatrixMultiplicationTests, Multiply_Float_Double_And_Double_Float)
{
    const auto result_AB = floatMat.multiply(doubleMat);
    const auto result_BA = doubleMat.multiply(floatMat);

    const double eps = 1e-6;
    ASSERT_NEAR(result_AB(0,0), 85.8, eps);     ASSERT_NEAR(result_AB(0,1),  81., eps);     ASSERT_NEAR(result_AB(0,2), 77., eps);
    ASSERT_NEAR(result_AB(1,0), 85.51, eps);    ASSERT_NEAR(result_AB(1,1), 87.8, eps);     ASSERT_NEAR(result_AB(1,2), 90.7, eps);
    ASSERT_NEAR(result_AB(2,0), 59.7, eps);     ASSERT_NEAR(result_AB(2,1), 51., eps);      ASSERT_NEAR(result_AB(2,2), 43., eps);

    ASSERT_NEAR(result_BA(0,0), 5., eps);       ASSERT_NEAR(result_BA(0,1),  14., eps);     ASSERT_NEAR(result_BA(0,2), 41.2, eps);
    ASSERT_NEAR(result_BA(1,0), 14., eps);      ASSERT_NEAR(result_BA(1,1), 41., eps);      ASSERT_NEAR(result_BA(1,2), 104.5, eps);
    ASSERT_NEAR(result_BA(2,0), 25.1, eps);     ASSERT_NEAR(result_BA(2,1), 76.3, eps);     ASSERT_NEAR(result_BA(2,2), 170.6, eps);
}

TEST_F(MatrixMultiplicationTests, Multiply_Row_With_Column)
{
    const auto mat_A = Matrix<double>({1.1, 2.2, 3.3}, 1, 3);
    const auto mat_B = Matrix<double>({1.1, 2.2, 3.3}, 3, 1);

    // This is a cumbersome way of computing the dot product. Expect a matrix with 1 row and 1 column

    const auto res = mat_A.multiply(mat_B);

    ASSERT_EQ(res.rows(), 1);
    ASSERT_EQ(res.cols(), 1);

    ASSERT_NEAR(res(0,0), 16.94, 1e-9);
}

TEST_F(MatrixMultiplicationTests, Multiply_Column_With_Row)
{
    const auto mat_A = Matrix<double>({1.1, 2.2, 3.3}, 1, 3);
    const auto mat_B = Matrix<double>({1.1, 2.2, 3.3}, 3, 1);

    const auto outer_product = mat_B.multiply(mat_A);

    ASSERT_EQ(outer_product.rows(), 3);
    ASSERT_EQ(outer_product.cols(), 3);

    const double eps = 1e-9;
    ASSERT_NEAR(outer_product(0,0), 1.21, eps);     ASSERT_NEAR(outer_product(0,1),  2.42, eps);        ASSERT_NEAR(outer_product(0,2), 3.63, eps);
    ASSERT_NEAR(outer_product(1,0), 2.42, eps);     ASSERT_NEAR(outer_product(1,1), 4.84, eps);         ASSERT_NEAR(outer_product(1,2), 7.26, eps);
    ASSERT_NEAR(outer_product(2,0), 3.63, eps);     ASSERT_NEAR(outer_product(2,1), 7.26, eps);         ASSERT_NEAR(outer_product(2,2), 10.89, eps);
}