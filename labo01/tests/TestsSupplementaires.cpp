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
#include "Vector.h"
#include "Operators.h"

#include <chrono>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

using namespace gti320;
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

    gti320::Matrix<double, gti320::Dynamic, gti320::Dynamic, gti320::ColumnStorage> C(2, 2);
    C(0,0)= 0;
    C(0,1)= 1;
    C(1,0)= 2;
    C(1,1) = 3;

    gti320::Matrix<double, gti320::Dynamic, gti320::Dynamic, gti320::ColumnStorage> D(2, 2);
    D = C;
    EXPECT_EQ(D(1,1), 3);



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

// Test combinaison de setZero, norm et dot
TEST(TestsSupplementaires, Supp05)
{
    gti320::Vector<double> z(10);
    z.setZero();

    EXPECT_EQ(z.rows(), 10);
    EXPECT_DOUBLE_EQ(z.norm(), 0.0);

    gti320::Vector<double> x(10);
    x.setZero();
    x(0) = 3.0;
    x(5) = -4.0;

    EXPECT_DOUBLE_EQ(z.dot(x), 0.0);
    EXPECT_DOUBLE_EQ(x.dot(z), 0.0);
}

// Test de copie profonde
TEST(TestsSupplementaires, Supp06)
{
    gti320::Vector<double> a(5);
    a.setZero();
    a(2) = 7.0;

    gti320::Vector<double> b(5);
    b.setZero();
    b = a;

    // Modifier a apres la copie ne doit pas modifier b
    a(2) = 42.0;

    EXPECT_DOUBLE_EQ(b(2), 7.0);
    EXPECT_DOUBLE_EQ(a(2), 42.0);

    b(1) = -3.5;
    EXPECT_DOUBLE_EQ(a(1), 0.0);
    EXPECT_DOUBLE_EQ(b(1), -3.5);

}

// Test Vector - Vector
TEST(TestsSupplementaires, Supp07)
{
    Vector<double> v1(5);
    Vector<double> v2(5);

    v1(0) = 1.0;  v2(0) = 0.5;
    v1(1) = 2.0;  v2(1) = 1.0;
    v1(2) = 4.0;  v2(2) = 2.0;
    v1(3) = 8.0;  v2(3) = 4.0;
    v1(4) = 16.0; v2(4) = 8.0;

    const auto v3 = v1 - v2;

    EXPECT_DOUBLE_EQ(v3(0), 0.5);
    EXPECT_DOUBLE_EQ(v3(1), 1.0);
    EXPECT_DOUBLE_EQ(v3(2), 2.0);
    EXPECT_DOUBLE_EQ(v3(3), 4.0);
    EXPECT_DOUBLE_EQ(v3(4), 8.0);

}

//Test matrix (ColumnStorage) * vecteur
TEST(TestsSupplementaires, Supp08)
{
    Matrix<double, Dynamic, Dynamic, ColumnStorage> M(5, 5);
    M.setIdentity();

    Vector<double> v(5);
    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 4.0;
    v(3) = 8.0;
    v(4) = 16.0;

    const auto result = M * v;

    EXPECT_DOUBLE_EQ(result(0), 1.0);
    EXPECT_DOUBLE_EQ(result(1), 2.0);
    EXPECT_DOUBLE_EQ(result(2), 4.0);
    EXPECT_DOUBLE_EQ(result(3), 8.0);
    EXPECT_DOUBLE_EQ(result(4), 16.0);

}

//Test avec matrice 0
TEST(TestsSupplementaires, Supp09)
{
    SparseMatrix<double> A(3, 3);

    // Matrice 0 : aucun triplet
    A.setFromTriplets(nullptr, 0);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            EXPECT_DOUBLE_EQ(A(i, j), 0.0);
        }
    }

    Vector<double> v(3);
    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;

    const Vector<double> out = A * v;

    EXPECT_DOUBLE_EQ(out(0), 0.0);
    EXPECT_DOUBLE_EQ(out(1), 0.0);
    EXPECT_DOUBLE_EQ(out(2), 0.0);
}

// Test verifier le mismatch de taille de triplets et sa matrice (Derniere ligne vide)
TEST(TestsSparseMatrix, SparseMatrixLastRowEmpty)
{
    // 3 x 3
    SparseMatrix<double> A(3, 3);

    TripletType<double> triplets[] = {
        {1.0, 0, 0},
        {2.0, 1, 1}
    };

    // 3 x 2
    A.setFromTriplets(triplets, 2);

    EXPECT_DOUBLE_EQ(A(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(A(1, 1), 2.0);

    EXPECT_DOUBLE_EQ(A(2, 0), 0.0);
    EXPECT_DOUBLE_EQ(A(2, 1), 0.0);
    EXPECT_DOUBLE_EQ(A(2, 2), 0.0);

    Vector<double> v(3);
    v(0) = 1.0;
    v(1) = 2.0;
    v(2) = 3.0;

    const Vector<double> out = A * v;

    EXPECT_DOUBLE_EQ(out(0), 1.0);
    EXPECT_DOUBLE_EQ(out(1), 4.0);
    EXPECT_DOUBLE_EQ(out(2), 0.0);
}

double checksum(const Matrix<double, Dynamic, Dynamic>& M)
{
    double s = 0.0;
    for (int i = 0; i < M.rows(); ++i) {
        for (int j = 0; j < M.cols(); ++j) {
            s += M(i, j);
        }
    }
    return s;
}

// Test perfomance de matrice (RowStorage) * matrice (ColumnStorage) (avec l'affichage de metric)
TEST(TestsSupplementaires, Test11)
{

    const int N = 250;          // taille de matrix
    const int warmup = 2;       // iterations non mesurees
    const int runs = 10;        // iterations mesurees

    Matrix<double, Dynamic, Dynamic, RowStorage> A(N, N);
    Matrix<double, Dynamic, Dynamic, ColumnStorage> B(N, N);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A(i, j) = 0.001 * (i + 1) + 0.002 * (j + 1);
            B(i, j) = 0.003 * (i + 1) - 0.001 * (j + 1);
        }
    }

    // Warm-up: chauffe caches / pages / JIT
    for (int t = 0; t < warmup; ++t) {
        auto C = A * B;
    }

    std::vector<double> times_ms;
    times_ms.reserve(runs);

    for (int t = 0; t < runs; ++t) {
        const auto start = std::chrono::steady_clock::now();
        auto C = A * B;
        const auto end = std::chrono::steady_clock::now();

        const double ms = std::chrono::duration<double, std::milli>(end - start).count();
        times_ms.push_back(ms);
    }

    // Metric: min / mediane / moyenne
    std::sort(times_ms.begin(), times_ms.end());
    const double min_ms = times_ms.front();
    const double med_ms = times_ms[times_ms.size() / 2];
    const double mean_ms = std::accumulate(times_ms.begin(), times_ms.end(), 0.0) / times_ms.size();

    std::cout << "\n[Perf] operator* RowStorage x ColumnStorage (Dynamic)\n"
              << "N=" << N << " runs=" << runs << " warmup=" << warmup << "\n"
              << "min  : " << min_ms  << " ms\n"
              << "median: " << med_ms << " ms\n"
              << "mean : " << mean_ms << "\n";

    SUCCEED();
}