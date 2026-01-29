#pragma once

/**
 * @file SparseMatrix.h
 *
 * @brief Une impl�mentation simple de matrice creuse.
 *        Note:  actuellement, seules les matrices dynamiques
 *        sont possibles.
 *
 * Nom:
 * Code permanent :
 * Email :
 *
 */

#include "SparseMatrixBase.h"

#include <cstring>
#include <cassert>

namespace gti320
{

    // Matrice creuse de type compressed row storage (CRS) sparse matrix avec taille dynamique.
    //
    template <typename _Scalar = double, int _ColsAtCompile = Dynamic, int _RowsAtCompile = Dynamic>
    class SparseMatrix : public SparseMatrixBase<_Scalar, _ColsAtCompile, _RowsAtCompile>
    {
    private: 
        unsigned int m_rows, m_cols;
    public:

        // Constructeur par d�faut
        SparseMatrix() : 
            SparseMatrixBase<_Scalar, Dynamic, Dynamic>(),
            m_rows(0), m_cols(0)
        { }

        // Constructeur de copie
        SparseMatrix(const SparseMatrix& other) : 
            SparseMatrixBase<_Scalar, Dynamic, Dynamic>(other),
            m_rows(other.m_rows), m_cols(other.m_cols)
        { }

        // Constructeur avec des dimensions
        explicit SparseMatrix(int _rows, int _cols) : 
            SparseMatrixBase<_Scalar, Dynamic, Dynamic>(_rows, 0),
            m_rows(_rows), m_cols(_cols)
        { }

        // Destructeur
        ~SparseMatrix() { }
        // Il faut cette fonction
        // TODO access operator (read-only)
        _Scalar operator()(int i, int j) const
        {
            // TODO : impl�menter

            return 0.0;
        }

        unsigned int rows() const { return m_rows; }

        unsigned int cols() const { return m_cols; }

        // Set this matrix to the identity matrix.
        void setIdentity()
        {
            // TODO mettre toutes les valeurs � 0,0, sauf pour la diagonale qui est � 1,0
            //      NB : confirmer que la matrice est carr�e

        }

        void setFromTriplets(TripletType<_Scalar>* _triplets, unsigned int _size)
        {
            // TODO : impl�menter
        }

    };

}
