//
// Created by dorian on 29.12.2023.
// stoicadorian@gmail.com
//

#ifndef LINEARALGEBRATOOLBOX_MATRIXHELPERS_HPP
#define LINEARALGEBRATOOLBOX_MATRIXHELPERS_HPP

#include "Matrix.hpp"

namespace LinearAlgebra::Matrix
{
    // Returns the identity matrix with specified dim
    template <typename T>
    Matrix<T> identity(unsigned int);

    // Returns the Hilbert matrix with specified dim
    Matrix<double> hilbert_matrix(unsigned int );

    //  Search the index of the first row with a non-zero entry below the current element (that is, in the same column).
    //  Used internally on the upper matrix which is always double, therefore only double spec.
    std::optional<unsigned int> findNonZeroPivot(const Matrix<long double>& mat, unsigned int, unsigned int);

    //  Search the index of the row with the maximum non-zero entry below the current element (that is, in the same column).
    //  Used internally on the upper matrix which is always double, therefore only double spec.
    std::optional<unsigned int> findMaxNonZeroPivot(const Matrix<long double>& mat, unsigned int, unsigned int);

    template <typename T>
    bool isLowerTriangular(const Matrix<T>& m);

    template <typename T>
    bool isUpperTriangular(const Matrix<T>& m);

}

#endif //LINEARALGEBRATOOLBOX_MATRIXHELPERS_HPP
