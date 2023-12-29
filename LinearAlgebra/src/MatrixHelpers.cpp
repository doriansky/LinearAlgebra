//
// Created by dorian on 29.12.2023.
// stoicadorian@gmail.com
//

#include "MatrixHelpers.hpp"
#include <algorithm>
#include <limits>


namespace LinearAlgebra::Matrix
{
    template <typename T>
    Matrix<T> identity(unsigned int d)
    {
        Matrix<T> identity(d, d);
        for (unsigned int i = 0; i<d; i++)
            identity(i,i) = static_cast<T>(1);

        return identity;
    }

    std::optional<unsigned int> findNonZeroPivot(const Matrix<double>& mat, const unsigned int row, const unsigned int col)
    {
        for (unsigned int rowIdx = row+1; rowIdx < mat.rows(); rowIdx++)
        {
            if (std::abs(mat(rowIdx, col)) > std::numeric_limits<double>::epsilon())
                return rowIdx;
        }
        return std::nullopt;
    }

#include "MatrixHelpersExplicitTemplateInstantiations.hpp"

} //end namespace
