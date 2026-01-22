#pragma once

/**
 * @file Matrix.h
 *
 * @brief Implémentation de matrices simples.
 *
 * Nom:
 * Code permanent :
 * Email :
 *
 */

#include "MatrixBase.h"

namespace gti320
{

    // Déclaration avancée
    template <typename _Scalar, int _RowsAtCompile, int _ColsAtCompile, int _StorageType> class SubMatrix;

    /**
     * Classe Matrix spécialisé pour le cas générique. (defaut par colonne)
     *
     * (le cas d'un stockage par ligne fait l'objet d'une spécialisation de patron, voir plus bas)
     */
    template <typename _Scalar = double, int _RowsAtCompile = Dynamic, int _ColsAtCompile = Dynamic, int _StorageType = ColumnStorage>
    class Matrix : public MatrixBase<_Scalar, _RowsAtCompile, _ColsAtCompile> {
    public:

        /**
         * Constructeur par défaut
         */
        Matrix() : MatrixBase<_Scalar, _RowsAtCompile, _ColsAtCompile>() {}

        /**
         * Constructeur de copie
         */
        Matrix(const Matrix& other) : MatrixBase<_Scalar, _RowsAtCompile, _ColsAtCompile>(other) {}

        /**
         * Constructeur avec spécification du nombre de ligne et de colonnes
         */
        explicit Matrix(int _rows, int _cols) : MatrixBase<_Scalar, _RowsAtCompile, _ColsAtCompile>(_rows, _cols) {}

        /**
         * Destructeur
         */
        ~Matrix() {}

        /**
         * Opérateur de copie à partir d'une sous-matrice.
         *
         * Exemple :
         *    Matrix<...> A(...);
         *    Matrix<...> B(...);
         *    B = A.block(i,j,m,n);

         */
        template<typename _OtherScalar, int OtherRows, int _OtherCols, int _OtherStorage>
        Matrix& operator= (const SubMatrix<_OtherScalar, OtherRows, _OtherCols, _OtherStorage>& submatrix)
        {
            // TODO copier les données de la sous-matrice.
            //   Note : si les dimensions ne correspondent pas, la matrice doit être redimensionnée.
            //   Vous pouvez présumer qu'il s'agit d'un stockage par colonnes.
            return *this;
        }

        /**
         * Accesseur à une entrée de la matrice (lecture seule)
         */
        _Scalar operator()(int i, int j) const
        {
            // TODO implementer
            return (double)(i + j);
        }

        /**
         * Accesseur à une entrée de la matrice (lecture ou écriture)
         */
        _Scalar& operator()(int i, int j)
        {
            // TODO implementer
            //      Indice : l'implémentation est identique à celle de la fonction précédente.
            _Scalar x = (double)(i + j);
            return x;
        }

        /**
         * Crée une sous-matrice pour un block de taille (rows, cols) à partir de l'index (i,j).
         */
        SubMatrix<_Scalar, _RowsAtCompile, _ColsAtCompile, _StorageType> block(int i, int j, int rows, int cols) const
        {
            return SubMatrix<_Scalar, _RowsAtCompile, _ColsAtCompile, _StorageType>(*this, i, j, rows, cols);
        }

        /**
         * Calcule l'inverse de la matrice
         */
        Matrix inverse() const
        {
            // Do nothing.
            return *this;
        }

        /**
         * Retourne la transposée de la matrice
         */
        template<typename _OtherScalar, int _OtherRows, int _OtherCols, int _OtherStorage>
        Matrix<_OtherScalar, _OtherRows, _OtherCols, _OtherStorage> transpose() const
        {
            // TODO calcule et retourne la transposée de la matrice.

            return  Matrix<_OtherScalar, _OtherRows, _OtherCols, _OtherStorage>(); // pas bon, à changer
        }

        /**
         * Affecte l'identité à la matrice
         */
        inline void setIdentity()
        {
            // TODO affecter la valeur 0.0 partour, sauf sur la diagonale principale où c'est 1.0..
            //      Votre implémentation devrait aussi fonctionner pour des matrices qui ne sont pas carrées.
        }

    };

    /**
     * Classe Matrix spécialisée pour un stockage par lignes
     */
    template <typename _Scalar, int _RowsAtCompile, int _ColsAtCompile>
    class Matrix< _Scalar, _RowsAtCompile, _ColsAtCompile, RowStorage> : public MatrixBase<_Scalar, _RowsAtCompile, _ColsAtCompile> {

    public:
        /**
         * Constructeur par défaut
         */
        Matrix() : MatrixBase<_Scalar, _RowsAtCompile, _ColsAtCompile>() {}

        /**
         * Constructeur de copie
         */
        Matrix(const Matrix& other) : MatrixBase<_Scalar, _RowsAtCompile, _ColsAtCompile>(other) {}

        /**
         * Constructeur avec spécification du nombre de ligne et de colonnes
         */
        explicit Matrix(int rows, int cols) : MatrixBase<_Scalar, _RowsAtCompile, _ColsAtCompile>(rows, cols) {}

        /**
         * Destructeur
         */
        ~Matrix() {}

        /**
         * Opérateur de copie à partir d'une sous-matrice.
         *
         * Exemple :
         *    Matrix<...> A(...);
         *    Matrix<...> B(...);
         *    B = A.block(i,j,m,n);
         */
        template<typename _OtherScalar, int OtherRows, int _OtherCols, int _OtherStorage>
        Matrix& operator= (const SubMatrix<_OtherScalar, OtherRows, _OtherCols, _OtherStorage>& submatrix)
        {
            // TODO copier les données de la sous-matrice.
            //   Note : si les dimensions ne correspondent pas, la matrice doit être redimensionnée.
            //   Vous pouvez présumer qu'il s'agit d'un stockage par lignes.
            return *this;
        }

        /**
         * Accesseur à une entrée de la matrice (lecture seule)
         */
        _Scalar operator()(int i, int j) const
        {
            // TODO implementer
            return 0.0;
        }

        /**
         * Accesseur à une entrée de la matrice (lecture ou écriture)
         */
        _Scalar& operator()(int i, int j)
        {
            // TODO implementer
            _Scalar x = 0.0;
            return x;
        }

        /**
         * Crée une sous-matrice pour un block de taille (rows, cols) à partir de l'index (i,j).
         */
        SubMatrix<_Scalar, _RowsAtCompile, _ColsAtCompile, RowStorage> block(int i, int j, int rows, int cols) const {
            return SubMatrix<_Scalar, _RowsAtCompile, _ColsAtCompile, RowStorage>(*this, i, j, rows, cols);
        }

        /**
         * Calcule l'inverse de la matrice
         */
        Matrix inverse() const
        {
            // Do nothing.
            return *this;
        }

        /**
         * Retourne la transposée de la matrice
         */
        Matrix<_Scalar, _ColsAtCompile, _RowsAtCompile, ColumnStorage> transpose() const
        {
            // TODO calcule et retourne la transposée de la matrice.
            //    Optimisez cette fonction en tenant compte du type de stockage utilisé.

            return Matrix<_Scalar, _ColsAtCompile, _RowsAtCompile, ColumnStorage>();
        }

        /**
         * Affecte l'identité à la matrice
         */
        inline void setIdentity()
        {
            // TODO affecter la valeur 0.0 partour, sauf sur la diagonale principale où c'est 1.0..
            //      Votre implémentation devrait aussi fonctionner pour des matrices qui ne sont pas carrées.
        }

    };

}
