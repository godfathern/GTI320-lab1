#pragma once

/**
 * @file Operators.h
 *
 * @brief Opérateurs arithmétiques pour les matrices et les vecteurs.
 *
 * Nom: Phan Tung Bui
 * Code permanent : BUIP26109708
 * Email : phan-tung.bui.1@ens.etsmtl.ca
 *
 */

#include "Matrix.h"
#include "Vector.h"
#include "SparseMatrix.h"
#include <algorithm>

 /**
  * Implémentation de divers opérateurs arithmétiques pour les matrices et les vecteurs.
  */
namespace gti320 {

    /**
     * Multiplication : Matrice * Matrice (générique)
     */
    template <typename _Scalar, int RowsA, int ColsA, int StorageA, int RowsB, int ColsB, int StorageB>
    Matrix<_Scalar, RowsA, ColsB> operator*(const Matrix<_Scalar, RowsA, ColsA, StorageA>& A, const Matrix<_Scalar, RowsB, ColsB, StorageB>& B)
    {
        // TODO implémenter

        int rowsA = A.rows();
        int colsA = A.cols();

        int rowsB = B.rows();
        int colsB = B.cols();

        assert(colsA == rowsB);

        Matrix<_Scalar, RowsA, ColsB> matRe(rowsA, colsB);

        for (int i = 0; i < rowsA; ++i) {
            for (int j = 0; j < colsB; ++j) {
                _Scalar sum = _Scalar(0);
                for (int k = 0; k < colsA; ++k) {
                    sum += A(i, k) * B(k, j);
                }
                matRe(i, j) = sum;
            }
        }

        //Amelioration possible a tester :
        // C.setZero();
        // for (int i = 0; i < rowsA; ++i) {
        //     for (int k = 0; k < colsA; ++k) {
        //         const _Scalar a = A(i, k);
        //         for (int j = 0; j < colsB; ++j) {
        //             C(i, j) += a * B(k, j);
        //         }
        //     }
        // }


        return matRe;
    }

    /**
     * Multiplication : Matrice (colonne) * Matrice (ligne)
     *
     * Spécialisation de l'opérateur de multiplication pour le cas où les matrices
     * ont un stockage à taille dynamique et où la matrice de gauche utilise un
     * stockage par colonnes et celle de droite un stockage par lignes.
     */
    template <typename _Scalar>
    Matrix<_Scalar, Dynamic, Dynamic> operator*(const Matrix<_Scalar, Dynamic, Dynamic, ColumnStorage>& A, const Matrix<_Scalar, Dynamic, Dynamic, RowStorage>& B)
    {
        // TODO : implémenter
        const int rowsA = A.rows();
        const int colsA = A.cols();
        const int rowsB = B.rows();
        const int colsB = B.cols();

        assert(colsA == rowsB);

        Matrix<_Scalar, Dynamic, Dynamic> C(rowsA, colsB);
        C.setZero();

        for (int i = 0; i < rowsA; ++i) {
            for (int k = 0; k < colsA; ++k) {
                const _Scalar a = A(i, k);
                for (int j = 0; j < colsB; ++j) {
                    C(i, j) += a * B(k, j);
                }
            }
        }

        return C;
    }

    /**
     * Multiplication : Matrice (ligne) * Matrice (colonne)
     *
     * Spécialisation de l'opérateur de multiplication pour le cas où les matrices
     * ont un stockage à taille dynamique et où la matrice de gauche utilise un
     * stockage par lignes et celle de droite un stockage par colonnes.
     */
    template <typename _Scalar>
    Matrix<_Scalar, Dynamic, Dynamic> operator*(const Matrix<_Scalar, Dynamic, Dynamic, RowStorage>& A, const Matrix<_Scalar, Dynamic, Dynamic, ColumnStorage>& B)
    {
        // TODO : implémenter
        const int M = A.rows();
        const int K = A.cols();
        const int N = B.cols();
        assert(K == B.rows());

        Matrix<_Scalar, Dynamic, Dynamic> C(M, N);
        C.setZero();

        //Pour eviter les functions calls, on get les raw pointers
        //
        _Scalar* __restrict__ c = C.data();
        const _Scalar* __restrict__ a = A.data();
        const _Scalar* __restrict__ b = B.data();

        const int lda = A.cols();
        const int ldb = B.rows();
        const int ldc = C.cols();

        for (int i = 0; i < M; ++i) {
            _Scalar* cRow = c + i * ldc; // Pin the start address of row i instead of recomputing all time
            for (int k = 0; k < K; ++k) {
                const _Scalar aik = a[i * lda + k];
                const _Scalar* bCol = b + k;

                // manual unroll (x4)
                int j = 0;
                for (; j + 3 < N; j += 4) {
                    cRow[j+0] += aik * bCol[(j+0) * ldb];
                    cRow[j+1] += aik * bCol[(j+1) * ldb];
                    cRow[j+2] += aik * bCol[(j+2) * ldb];
                    cRow[j+3] += aik * bCol[(j+3) * ldb];
                }
                for (; j < N; ++j) {
                    cRow[j] += aik * bCol[j * ldb];
                }
            }
        }
        return C;
    }


    /**
     * Addition : Matrice + Matrice (générique)
     */
    template <typename _Scalar, int Rows, int Cols, int StorageA, int StorageB>
    Matrix<_Scalar, Rows, Cols> operator+(const Matrix<_Scalar, Rows, Cols, StorageA>& A, const Matrix<_Scalar, Rows, Cols, StorageB>& B)
    {
        // TODO : implémenter
        const int rowsA = A.rows();
        const int colsA = A.cols();
        const int rowsB = B.rows();
        const int colsB = B.cols();

        assert (rowsA == rowsB);
        assert (colsA == colsB);

        Matrix <_Scalar, Rows, Cols> C(rowsA, colsA);

        for (int i = 0; i < rowsA; ++i) {
            for (int j = 0; j < colsA; ++j) {
                C(i,j) = A(i,j) + B(i,j);
            }
        }


        return C;
    }

    /**
     * Addition : Matrice (colonne) + Matrice (colonne)
     *
     * Spécialisation de l'opérateur d'addition pour le cas où les deux matrices
     * sont stockées par colonnes.
     */
    template <typename _Scalar>
    Matrix<_Scalar, Dynamic, Dynamic> operator+(const Matrix<_Scalar, Dynamic, Dynamic, ColumnStorage>& A, const Matrix<_Scalar, Dynamic, Dynamic, ColumnStorage>& B)
    {
        // TODO : implémenter
        const int rowsA = A.rows();
        const int colsA = A.cols();
        const int rowsB = B.rows();
        const int colsB = B.cols();

        assert (rowsA == rowsB);
        assert (colsA == colsB);

        Matrix <_Scalar, Dynamic, Dynamic> C(rowsA, colsA);

        const _Scalar* __restrict a = A.data();
        const _Scalar* __restrict b = B.data();
        _Scalar* __restrict c = C.data();

        const int n = rowsA * colsA;
        for (int i = 0; i < n; ++i) {
            c[i] = a[i] + b[i];
        }
        return C;
    }

    /**
     * Addition : Matrice (ligne) + Matrice (ligne)
     *
     * Spécialisation de l'opérateur d'addition pour le cas où les deux matrices
     * sont stockées par lignes.
     */
    template <typename _Scalar>
    Matrix<_Scalar, Dynamic, Dynamic, RowStorage> operator+(const Matrix<_Scalar, Dynamic, Dynamic, RowStorage>& A, const Matrix<_Scalar, Dynamic, Dynamic, RowStorage>& B)
    {
        // TODO : implémenter

        int rows = A.rows();
        int cols = A.cols();

        assert(rows == B.rows());
        assert(cols) == B.cols();

        Matrix<_Scalar, Dynamic, Dynamic, RowStorage> C(rows,cols);

        const _Scalar* __restrict a = A.data();
        const _Scalar* __restrict b = B.data();
        _Scalar* __restrict c = C.data();

        for

        return Matrix<_Scalar, Dynamic, Dynamic, RowStorage>();
    }

    /**
     * Multiplication  : Scalaire * Matrice (colonne)
     *
     * Spécialisation de l'opérateur de multiplication par un scalaire pour le
     * cas d'une matrice stockée par colonnes.
     */
    template <typename _Scalar, int _Rows, int _Cols>
    Matrix<_Scalar, _Rows, _Cols, ColumnStorage> operator*(const _Scalar& a, const Matrix<_Scalar, _Rows, _Cols, ColumnStorage>& A)
    {
        // TODO : implémenter
        return Matrix<_Scalar, Dynamic, Dynamic>();
    }

    /**
     * Multiplication  : Scalaire * Matrice (ligne)
     *
     * Spécialisation de l'opérateur de multiplication par un scalaire pour le
     * cas d'une matrice stockée par lignes.
     */
    template <typename _Scalar, int _Rows, int _Cols>
    Matrix<_Scalar, _Rows, _Cols, RowStorage> operator*(const _Scalar& a, const Matrix<_Scalar, _Rows, _Cols, RowStorage>& A)
    {
        // TODO : implémenter
        return Matrix<_Scalar, Dynamic, Dynamic, RowStorage>();
    }

    /**
     * Multiplication : Matrice (ligne) * Vecteur
     *
     * Spécialisation de l'opérateur de multiplication matrice*vecteur pour le
     * cas où la matrice est représentée par lignes.
     */
    template <typename _Scalar, int _Rows, int _Cols>
    Vector<_Scalar, _Rows> operator*(const Matrix<_Scalar, _Rows, _Cols, RowStorage>& A, const Vector<_Scalar, _Cols>& v)
    {
        // TODO : implémenter
        return Vector<_Scalar, _Rows>();
    }

    /**
     * Multiplication : Matrice (colonne) * Vecteur
     *
     * Spécialisation de l'opérateur de multiplication matrice*vecteur pour le
     * cas où la matrice est représentée par colonnes.
     */
    template <typename _Scalar, int _Rows, int _Cols>
    Vector<_Scalar, _Rows> operator*(const Matrix<_Scalar, _Rows, _Cols, ColumnStorage>& A, const Vector<_Scalar, _Cols>& v)
    {
        // TODO : implémenter
        return Vector<_Scalar, _Rows>();
    }

    /**
     * Multiplication : Scalaire * Vecteur
     */
    template <typename _Scalar, int _Rows>
    Vector<_Scalar, _Rows> operator*(const _Scalar& a, const Vector<_Scalar, _Rows>& v)
    {
        // TODO : implémenter
        return Vector<_Scalar, _Rows>();
    }


    /**
     * Addition : Vecteur + Vecteur
     */
    template <typename _Scalar, int _RowsA, int _RowsB>
    Vector<_Scalar, _RowsA> operator+(const Vector<_Scalar, _RowsA>& a, const Vector<_Scalar, _RowsB>& b)
    {
        // TODO : implémenter
        return Vector<_Scalar, _RowsA>();
    }

    /**
     * Soustraction : Vecteur - Vecteur
     */
    template <typename _Scalar, int _RowsA, int _RowsB>
    Vector<_Scalar, _RowsA> operator-(const Vector<_Scalar, _RowsA>& a, const Vector<_Scalar, _RowsB>& b)
    {
        // TODO : implémenter
        return Vector<_Scalar, _RowsA>();
    }
    

    /**
     * Multiplication : SparseMatrix * Vecteur
     */
    template<typename _Scalar, int _Rows, int _Cols>
    Vector<_Scalar, _Rows> operator*(const SparseMatrix<_Scalar, _Cols, _Rows>& A, const Vector<_Scalar, _Cols>& v)
    {
    	// TODO : implémenter
        return Vector<_Scalar, _Rows>();
    }

}
