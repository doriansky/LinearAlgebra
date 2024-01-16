//
// Created by dorian on 16.01.2024
// stoicadorian@gmail.com
//
#include "gtest/gtest.h"
#include "Matrix.hpp"
#include "MatrixHelpers.hpp"

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

TEST_F(MatrixQRFactorizationTests, QR_Hilbert_5_OneTestToRuleThemAll)
{
    const auto hilbert_mat = hilbert_matrix(5);

    const auto QR = hilbert_mat.factorizeQR();

    ASSERT_NEAR(QR.Q(0,0), 0.826584298073692, epsilon);   ASSERT_NEAR(QR.Q(0,1), -0.533354625741033, epsilon);          ASSERT_NEAR(QR.Q(0,2), 0.175305353859198, epsilon);     ASSERT_NEAR(QR.Q(0,3), -0.039102073792953, epsilon);        ASSERT_NEAR(QR.Q(0,4), 0.005504735421182, epsilon);
    ASSERT_NEAR(QR.Q(1,0), 0.413292149036846, epsilon);   ASSERT_NEAR(QR.Q(1,1), 0.374053540533383, epsilon);           ASSERT_NEAR(QR.Q(1,2), -0.717262398141397, epsilon);    ASSERT_NEAR(QR.Q(1,3), 0.403345206676012, epsilon);         ASSERT_NEAR(QR.Q(1,4), -0.11009470842363, epsilon);
    ASSERT_NEAR(QR.Q(2,0), 0.275528099357897, epsilon);   ASSERT_NEAR(QR.Q(2,1), 0.462945978156888, epsilon);            ASSERT_NEAR(QR.Q(2,2), -0.057664733696227, epsilon);   ASSERT_NEAR(QR.Q(2,3), -0.6789646224929, epsilon);          ASSERT_NEAR(QR.Q(2,4), 0.495426187906336, epsilon);
    ASSERT_NEAR(QR.Q(3,0), 0.206646074518423, epsilon);   ASSERT_NEAR(QR.Q(3,1), 0.443319111628251, epsilon);            ASSERT_NEAR(QR.Q(3,2), 0.352625606033457, epsilon);    ASSERT_NEAR(QR.Q(3,3), -0.206153706732327, epsilon);        ASSERT_NEAR(QR.Q(3,4), -0.770662958965412, epsilon);
    ASSERT_NEAR(QR.Q(4,0), 0.165316859614738, epsilon);   ASSERT_NEAR(QR.Q(4,1), 0.405913757574913, epsilon);            ASSERT_NEAR(QR.Q(4,2), 0.571955108009391, epsilon);    ASSERT_NEAR(QR.Q(4,3), 0.576447189844977, epsilon);         ASSERT_NEAR(QR.Q(4,4), 0.385331479482706, epsilon);

    ASSERT_NEAR(QR.R(0,0), 1.209797962930634, epsilon);    ASSERT_NEAR(QR.R(0,1), 0.688820248394743, epsilon);      ASSERT_NEAR(QR.R(0,2), 0.492014463139102, epsilon);     ASSERT_NEAR(QR.R(0,3), 0.385411329458963, epsilon);       ASSERT_NEAR(QR.R(0,4), 0.317759340777337, epsilon);
    ASSERT_NEAR(QR.R(1,0), 0, epsilon);                    ASSERT_NEAR(QR.R(1,1), 0.130059810434636, epsilon);      ASSERT_NEAR(QR.R(1,2), 0.14019190377598, epsilon);      ASSERT_NEAR(QR.R(1,3), 0.132700236055609, epsilon);       ASSERT_NEAR(QR.R(1,4), 0.122322888917022, epsilon);
    ASSERT_NEAR(QR.R(2,0), 0, epsilon);                    ASSERT_NEAR(QR.R(2,1), 0, epsilon);                      ASSERT_NEAR(QR.R(2,2), 0.008065378590151, epsilon);     ASSERT_NEAR(QR.R(2,3), 0.012632544964531, epsilon);       ASSERT_NEAR(QR.R(2,4), 0.014908286959594, epsilon);
    ASSERT_NEAR(QR.R(3,0), 0, epsilon);                    ASSERT_NEAR(QR.R(3,1), 0, epsilon);                      ASSERT_NEAR(QR.R(3,2), 0, epsilon);                     ASSERT_NEAR(QR.R(3,3), 0.000338121668913, epsilon);       ASSERT_NEAR(QR.R(3,4), 0.000689314702676, epsilon);
    ASSERT_NEAR(QR.R(4,0), 0, epsilon);                    ASSERT_NEAR(QR.R(4,1), 0, epsilon);                      ASSERT_NEAR(QR.R(4,2), 0, epsilon);                     ASSERT_NEAR(QR.R(4,3), 0, epsilon);                       ASSERT_NEAR(QR.R(4,4), 0.000008737675272, epsilon);

    // Test A = Q*R
    const auto Q_times_R = QR.Q.multiply(QR.R);
    ASSERT_NEAR(Q_times_R(0,0), hilbert_mat(0,0), epsilon);     ASSERT_NEAR(Q_times_R(0,1), hilbert_mat(0,1), epsilon);     ASSERT_NEAR(Q_times_R(0,2), hilbert_mat(0,2), epsilon);     ASSERT_NEAR(Q_times_R(0,3), hilbert_mat(0,3), epsilon);     ASSERT_NEAR(Q_times_R(0,4), hilbert_mat(0,4), epsilon);
    ASSERT_NEAR(Q_times_R(1,0), hilbert_mat(1,0), epsilon);     ASSERT_NEAR(Q_times_R(1,1), hilbert_mat(1,1), epsilon);     ASSERT_NEAR(Q_times_R(1,2), hilbert_mat(1,2), epsilon);     ASSERT_NEAR(Q_times_R(1,3), hilbert_mat(1,3), epsilon);     ASSERT_NEAR(Q_times_R(1,4), hilbert_mat(1,4), epsilon);
    ASSERT_NEAR(Q_times_R(2,0), hilbert_mat(2,0), epsilon);     ASSERT_NEAR(Q_times_R(2,1), hilbert_mat(2,1), epsilon);     ASSERT_NEAR(Q_times_R(2,2), hilbert_mat(2,2), epsilon);     ASSERT_NEAR(Q_times_R(2,3), hilbert_mat(2,3), epsilon);     ASSERT_NEAR(Q_times_R(2,4), hilbert_mat(2,4), epsilon);
    ASSERT_NEAR(Q_times_R(3,0), hilbert_mat(3,0), epsilon);     ASSERT_NEAR(Q_times_R(3,1), hilbert_mat(3,1), epsilon);     ASSERT_NEAR(Q_times_R(3,2), hilbert_mat(3,2), epsilon);     ASSERT_NEAR(Q_times_R(3,3), hilbert_mat(3,3), epsilon);     ASSERT_NEAR(Q_times_R(3,4), hilbert_mat(3,4), epsilon);
    ASSERT_NEAR(Q_times_R(4,0), hilbert_mat(4,0), epsilon);     ASSERT_NEAR(Q_times_R(4,1), hilbert_mat(4,1), epsilon);     ASSERT_NEAR(Q_times_R(4,2), hilbert_mat(4,2), epsilon);     ASSERT_NEAR(Q_times_R(4,3), hilbert_mat(4,3), epsilon);     ASSERT_NEAR(Q_times_R(4,4), hilbert_mat(4,4), epsilon);

    // Test columns of Q
    const auto C_1 = Vector<long double>({QR.Q(0,0), QR.Q(1,0), QR.Q(2,0), QR.Q(3,0), QR.Q(4,0)});
    const auto C_2 = Vector<long double>({QR.Q(0,1), QR.Q(1,1), QR.Q(2,1), QR.Q(3,1), QR.Q(4,1)});
    const auto C_3 = Vector<long double>({QR.Q(0,2), QR.Q(1,2), QR.Q(2,2), QR.Q(3,2), QR.Q(4,2)});
    const auto C_4 = Vector<long double>({QR.Q(0,3), QR.Q(1,3), QR.Q(2,3), QR.Q(3,3), QR.Q(4,3)});
    const auto C_5 = Vector<long double>({QR.Q(0,4), QR.Q(1,4), QR.Q(2,4), QR.Q(3,4), QR.Q(4,4)});


    ASSERT_NEAR(C_1.norm(), 1, epsilon);    ASSERT_NEAR(C_2.norm(), 1, epsilon);    ASSERT_NEAR(C_3.norm(), 1, epsilon);    ASSERT_NEAR(C_4.norm(), 1, epsilon); ASSERT_NEAR(C_5.norm(), 1, epsilon);
    ASSERT_NEAR(C_1.dot(C_2), 0, epsilon);  ASSERT_NEAR(C_1.dot(C_3), 0, epsilon); ASSERT_NEAR(C_1.dot(C_4), 0, epsilon); ASSERT_NEAR(C_1.dot(C_5), 0, epsilon);
    ASSERT_NEAR(C_2.dot(C_3), 0, epsilon);  ASSERT_NEAR(C_2.dot(C_4), 0, epsilon); ASSERT_NEAR(C_2.dot(C_5), 0, epsilon);
    ASSERT_NEAR(C_3.dot(C_4), 0, epsilon);  ASSERT_NEAR(C_3.dot(C_5), 0, epsilon);
    ASSERT_NEAR(C_4.dot(C_5), 0, epsilon);

}