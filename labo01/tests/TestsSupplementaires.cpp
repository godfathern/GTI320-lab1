/**
 * @file TestsSupplementaires.cpp
 *
 * @brief Tests unitaires supplementaires
 *
 * Nom: Bui, Phan Tung
 * Code permanent : BUIP26109708
 * Email : phan-tung.bui.1@ens.etsmtl.ca
 *
 */

#include <gtest/gtest.h>

#include "DenseStorage.h"
#include  "Matrix.h"
// Test operateur de setZero
TEST(TestsSupplementaires, Supp01)
{
    gti320::DenseStorage<int, gti320::Dynamic> buf(8);
    buf.setZero();
    for (int i = 0; i < buf.size(); i++) {
        EXPECT_EQ(buf[i], 0);
    }
}
// Test operateur de copie
TEST(TestsSupplementaires, Supp02)
{
    gti320::DenseStorage<int, gti320::Dynamic> buf(8);
    buf.setZero();
    gti320::DenseStorage<int, gti320::Dynamic> bufB(buf);
    EXPECT_NE(bufB.data(), buf.data());
    for (int i = 0; i < buf.size(); i++) {
        EXPECT_EQ(buf[i], bufB[i]);
    }
}

// Test operator= pour Matrix
TEST(TestsSupplementaires, Supp03)
{
    gti320::Matrix<double, gti320::Dynamic, gti320::Dynamic, gti320::RowStorage> A(4, 3);
    A.setZero();

    for (int i = 0; i < A.rows(); ++i) {
        for (int j = 0; j < A.cols(); ++j) {
            A(i, j) = 100.0 * i + j;
        }
    }

    gti320::Matrix<double, gti320::Dynamic, gti320::Dynamic, gti320::RowStorage> B(1, 1);
    B = A;

    EXPECT_EQ(B.rows(), 4);
    EXPECT_EQ(B.cols(), 3);

    for (int i = 0; i < B.rows(); ++i) {
        for (int j = 0; j < B.cols(); ++j) {
            EXPECT_DOUBLE_EQ(B(i, j), 100.0 * i + j);
        }
    }

    // self-assignment
    B = B;
    for (int i = 0; i < B.rows(); ++i) {
        for (int j = 0; j < B.cols(); ++j) {
            EXPECT_DOUBLE_EQ(B(i, j), 100.0 * i + j);
        }
    }
}

// Test setIdentity pour Matrix (rectangulaire)
TEST(TestsSupplementaires, Supp04)
{
    gti320::Matrix<double, gti320::Dynamic, gti320::Dynamic, gti320::ColumnStorage> M(3, 5);
    M.setIdentity();

    EXPECT_EQ(M.rows(), 3);
    EXPECT_EQ(M.cols(), 5);

    for (int i = 0; i < M.rows(); ++i) {
        for (int j = 0; j < M.cols(); ++j) {
            double expected = (i == j) ? 1.0 : 0.0;
            EXPECT_DOUBLE_EQ(M(i, j), expected);
        }
    }
}

TEST(TestsSupplementaires, Supp05)
{

}

TEST(TestsSupplementaires, Supp06)
{

}

TEST(TestsSupplementaires, Supp07)
{

}

TEST(TestsSupplementaires, Supp08)
{

}

TEST(TestsSupplementaires, Supp09)
{

}

TEST(TestsSupplementaires, Supp10)
{

}
