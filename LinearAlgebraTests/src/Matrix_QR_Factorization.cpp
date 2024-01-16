//
// Created by dorian on 16.01.2024
// stoicadorian@gmail.com
//
#include "gtest/gtest.h"
#include "Matrix.hpp"

#include <cmath>

using namespace LinearAlgebra::Matrix;
using namespace LinearAlgebra::Vector;

class MatrixQRFactorizationTests : public ::testing::Test
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


TEST_F(MatrixQRFactorizationTests, Example_1)
{
    const auto data = std::vector<int>{1,1,2,
                                       0,0,1,
                                       1,0,0};

    const auto mat = Matrix<int>(data, 3, 3);
    const auto QR = mat.factorizeQR();

    // Test Q and R
    ASSERT_NEAR(QR.Q(0,0), 1/std::sqrt(2), epsilon);        ASSERT_NEAR(QR.Q(0,1), 1/std::sqrt(2), epsilon);        ASSERT_NEAR(QR.Q(0,2), 0, epsilon);
    ASSERT_NEAR(QR.Q(1,0), 0, epsilon);                        ASSERT_NEAR(QR.Q(1,1), 0, epsilon);                        ASSERT_NEAR(QR.Q(1,2), 1, epsilon);
    ASSERT_NEAR(QR.Q(2,0), 1/std::sqrt(2), epsilon);        ASSERT_NEAR(QR.Q(2,1), -1/std::sqrt(2), epsilon);       ASSERT_NEAR(QR.Q(2,2), 0, epsilon);

    ASSERT_NEAR(QR.R(0,0), std::sqrt(2), epsilon);        ASSERT_NEAR(QR.R(0,1), 1/std::sqrt(2), epsilon);          ASSERT_NEAR(QR.R(0,2), std::sqrt(2), epsilon);
    ASSERT_NEAR(QR.R(1,0), 0, epsilon);                      ASSERT_NEAR(QR.R(1,1), 1/std::sqrt(2), epsilon);          ASSERT_NEAR(QR.R(1,2), std::sqrt(2), epsilon);
    ASSERT_NEAR(QR.R(2,0), 0, epsilon);                      ASSERT_NEAR(QR.R(2,1), 0, epsilon);                          ASSERT_NEAR(QR.R(2,2), 1, epsilon);

    // Test Q * R reconstructs the matrix
    const auto Q_times_R = QR.Q.multiply(QR.R);
    ASSERT_NEAR(Q_times_R(0,0), mat(0,0), epsilon);     ASSERT_NEAR(Q_times_R(0,1), mat(0,1), epsilon);     ASSERT_NEAR(Q_times_R(0,2), mat(0,2), epsilon);
    ASSERT_NEAR(Q_times_R(1,0), mat(1,0), epsilon);     ASSERT_NEAR(Q_times_R(1,1), mat(1,1), epsilon);     ASSERT_NEAR(Q_times_R(1,2), mat(1,2), epsilon);
    ASSERT_NEAR(Q_times_R(2,0), mat(2,0), epsilon);     ASSERT_NEAR(Q_times_R(2,1), mat(2,1), epsilon);     ASSERT_NEAR(Q_times_R(2,2), mat(2,2), epsilon);

    // Test columns of Q
    const auto C_1 = Vector<long double>({QR.Q(0,0), QR.Q(1,0), QR.Q(2,0)});
    const auto C_2 = Vector<long double>({QR.Q(0,1), QR.Q(1,1), QR.Q(2,1)});
    const auto C_3 = Vector<long double>({QR.Q(0,2), QR.Q(1,2), QR.Q(2,2)});

    ASSERT_NEAR(C_1.norm(), 1, epsilon);    ASSERT_NEAR(C_2.norm(), 1, epsilon);    ASSERT_NEAR(C_2.norm(), 1, epsilon);
    ASSERT_NEAR(C_1.dot(C_2), 0, epsilon);  ASSERT_NEAR(C_1.dot(C_3), 0, epsilon); ASSERT_NEAR(C_2.dot(C_3), 0, epsilon);
}

TEST_F(MatrixQRFactorizationTests, Strang_3_4_13)
{
    const auto data = std::vector<int>{0,0,1,
                                       0,1,1,
                                       1,1,1};

    const auto mat = Matrix<int>(data, 3, 3);
    const auto QR = mat.factorizeQR();

    // Test Q and R
    ASSERT_NEAR(QR.Q(0,0), 0, epsilon);         ASSERT_NEAR(QR.Q(0,1), 0, epsilon);         ASSERT_NEAR(QR.Q(0,2), 1, epsilon);
    ASSERT_NEAR(QR.Q(1,0), 0, epsilon);         ASSERT_NEAR(QR.Q(1,1), 1, epsilon);         ASSERT_NEAR(QR.Q(1,2), 0, epsilon);
    ASSERT_NEAR(QR.Q(2,0), 1, epsilon);         ASSERT_NEAR(QR.Q(2,1), 0, epsilon);         ASSERT_NEAR(QR.Q(2,2), 0, epsilon);

    ASSERT_NEAR(QR.R(0,0), 1, epsilon);         ASSERT_NEAR(QR.R(0,1), 1, epsilon);     ASSERT_NEAR(QR.R(0,2), 1, epsilon);
    ASSERT_NEAR(QR.R(1,0), 0, epsilon);         ASSERT_NEAR(QR.R(1,1), 1, epsilon);     ASSERT_NEAR(QR.R(1,2), 1, epsilon);
    ASSERT_NEAR(QR.R(2,0), 0, epsilon);         ASSERT_NEAR(QR.R(2,1), 0, epsilon);     ASSERT_NEAR(QR.R(2,2), 1, epsilon);

    // Test Q * R reconstructs the matrix
    const auto Q_times_R = QR.Q.multiply(QR.R);
    ASSERT_NEAR(Q_times_R(0,0), mat(0,0), epsilon);     ASSERT_NEAR(Q_times_R(0,1), mat(0,1), epsilon);     ASSERT_NEAR(Q_times_R(0,2), mat(0,2), epsilon);
    ASSERT_NEAR(Q_times_R(1,0), mat(1,0), epsilon);     ASSERT_NEAR(Q_times_R(1,1), mat(1,1), epsilon);     ASSERT_NEAR(Q_times_R(1,2), mat(1,2), epsilon);
    ASSERT_NEAR(Q_times_R(2,0), mat(2,0), epsilon);     ASSERT_NEAR(Q_times_R(2,1), mat(2,1), epsilon);     ASSERT_NEAR(Q_times_R(2,2), mat(2,2), epsilon);

    // Test columns of Q
    const auto C_1 = Vector<long double>({QR.Q(0,0), QR.Q(1,0), QR.Q(2,0)});
    const auto C_2 = Vector<long double>({QR.Q(0,1), QR.Q(1,1), QR.Q(2,1)});
    const auto C_3 = Vector<long double>({QR.Q(0,2), QR.Q(1,2), QR.Q(2,2)});

    ASSERT_NEAR(C_1.norm(), 1, epsilon);    ASSERT_NEAR(C_2.norm(), 1, epsilon);    ASSERT_NEAR(C_2.norm(), 1, epsilon);
    ASSERT_NEAR(C_1.dot(C_2), 0, epsilon);  ASSERT_NEAR(C_1.dot(C_3), 0, epsilon); ASSERT_NEAR(C_2.dot(C_3), 0, epsilon);
}

TEST_F(MatrixQRFactorizationTests, Strang_3_4_14)
{
    const auto data = std::vector<int>{1,1,0,
                                       1,0,1,
                                       0,1,1};

    const auto mat = Matrix<int>(data, 3, 3);
    const auto QR = mat.factorizeQR();

    // Test Q and R
    ASSERT_NEAR(QR.Q(0,0), std::sqrt(2)/2, epsilon);    ASSERT_NEAR(QR.Q(0,1), std::sqrt(6)/6, epsilon);            ASSERT_NEAR(QR.Q(0,2), -std::sqrt(3)/3, epsilon);
    ASSERT_NEAR(QR.Q(1,0), std::sqrt(2)/2, epsilon);    ASSERT_NEAR(QR.Q(1,1), -std::sqrt(6)/6, epsilon);           ASSERT_NEAR(QR.Q(1,2), std::sqrt(3)/3, epsilon);
    ASSERT_NEAR(QR.Q(2,0), 0, epsilon);                    ASSERT_NEAR(QR.Q(2,1), std::sqrt(6)/3, epsilon);            ASSERT_NEAR(QR.Q(2,2), std::sqrt(3)/3, epsilon);

    ASSERT_NEAR(QR.R(0,0), std::sqrt(2), epsilon);       ASSERT_NEAR(QR.R(0,1), std::sqrt(2)/2, epsilon);     ASSERT_NEAR(QR.R(0,2), std::sqrt(2)/2, epsilon);
    ASSERT_NEAR(QR.R(1,0), 0, epsilon);                     ASSERT_NEAR(QR.R(1,1), std::sqrt(6)/2, epsilon);     ASSERT_NEAR(QR.R(1,2), std::sqrt(6)/6, epsilon);
    ASSERT_NEAR(QR.R(2,0), 0, epsilon);                     ASSERT_NEAR(QR.R(2,1), 0, epsilon);                     ASSERT_NEAR(QR.R(2,2), 2*std::sqrt(3)/3, epsilon);

    // Test Q * R reconstructs the matrix
    const auto Q_times_R = QR.Q.multiply(QR.R);
    ASSERT_NEAR(Q_times_R(0,0), mat(0,0), epsilon);     ASSERT_NEAR(Q_times_R(0,1), mat(0,1), epsilon);     ASSERT_NEAR(Q_times_R(0,2), mat(0,2), epsilon);
    ASSERT_NEAR(Q_times_R(1,0), mat(1,0), epsilon);     ASSERT_NEAR(Q_times_R(1,1), mat(1,1), epsilon);     ASSERT_NEAR(Q_times_R(1,2), mat(1,2), epsilon);
    ASSERT_NEAR(Q_times_R(2,0), mat(2,0), epsilon);     ASSERT_NEAR(Q_times_R(2,1), mat(2,1), epsilon);     ASSERT_NEAR(Q_times_R(2,2), mat(2,2), epsilon);

    // Test columns of Q
    const auto C_1 = Vector<long double>({QR.Q(0,0), QR.Q(1,0), QR.Q(2,0)});
    const auto C_2 = Vector<long double>({QR.Q(0,1), QR.Q(1,1), QR.Q(2,1)});
    const auto C_3 = Vector<long double>({QR.Q(0,2), QR.Q(1,2), QR.Q(2,2)});

    ASSERT_NEAR(C_1.norm(), 1, epsilon);    ASSERT_NEAR(C_2.norm(), 1, epsilon);    ASSERT_NEAR(C_2.norm(), 1, epsilon);
    ASSERT_NEAR(C_1.dot(C_2), 0, epsilon);  ASSERT_NEAR(C_1.dot(C_3), 0, epsilon); ASSERT_NEAR(C_2.dot(C_3), 0, epsilon);
}

TEST_F(MatrixQRFactorizationTests, Strang_3_4_16)
{
    const auto data = std::vector<int>{1,1,
                                       2,3,
                                       2,1};

    const auto mat = Matrix<int>(data, 3, 2);
    const auto QR = mat.factorizeQR();

    // Test Q and R
    ASSERT_NEAR(QR.Q(0,0), 1./3, epsilon);      ASSERT_NEAR(QR.Q(0,1), 0, epsilon);
    ASSERT_NEAR(QR.Q(1,0), 2./3, epsilon);      ASSERT_NEAR(QR.Q(1,1), std::sqrt(2)/2, epsilon);
    ASSERT_NEAR(QR.Q(2,0), 2./3, epsilon);      ASSERT_NEAR(QR.Q(2,1), -std::sqrt(2)/2, epsilon);

    ASSERT_NEAR(QR.R(0,0), 3, epsilon);         ASSERT_NEAR(QR.R(0,1), 3, epsilon);
    ASSERT_NEAR(QR.R(1,0), 0, epsilon);         ASSERT_NEAR(QR.R(1,1), std::sqrt(2), epsilon);

    // Test Q * R reconstructs the matrix
    const auto Q_times_R = QR.Q.multiply(QR.R);
    ASSERT_NEAR(Q_times_R(0,0), mat(0,0), epsilon);     ASSERT_NEAR(Q_times_R(0,1), mat(0,1), epsilon);
    ASSERT_NEAR(Q_times_R(1,0), mat(1,0), epsilon);     ASSERT_NEAR(Q_times_R(1,1), mat(1,1), epsilon);
    ASSERT_NEAR(Q_times_R(2,0), mat(2,0), epsilon);     ASSERT_NEAR(Q_times_R(2,1), mat(2,1), epsilon);

    // Test columns of Q
    const auto C_1 = Vector<long double>({QR.Q(0,0), QR.Q(1,0), QR.Q(2,0)});
    const auto C_2 = Vector<long double>({QR.Q(0,1), QR.Q(1,1), QR.Q(2,1)});

    ASSERT_NEAR(C_1.norm(), 1, epsilon);    ASSERT_NEAR(C_2.norm(), 1, epsilon);
    ASSERT_NEAR(C_1.dot(C_2), 0, epsilon);
}