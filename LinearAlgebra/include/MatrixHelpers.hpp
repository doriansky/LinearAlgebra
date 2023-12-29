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

    //  Search for first non-zero entry below the current element (that is, in the same column).
    //  Used internally on the upper matrix which is always double, therefore only double spec.
    std::optional<unsigned int> findNonZeroPivot(const Matrix<double>& mat, unsigned int, unsigned int);
}

#endif //LINEARALGEBRATOOLBOX_MATRIXHELPERS_HPP
