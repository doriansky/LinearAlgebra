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

    template <typename T>
    bool isLowerTriangular(const Matrix<T>& m)
    {
        if (m.rows() != m.cols())
            return false;

        for (unsigned int r=0; r<m.rows();r++)
        {
            //Check non-zeros on the diagonal
            if (m(r,r) == static_cast<T>(0))
                return false;

            //Check all elements above diagonal are zero
            for (unsigned int c=r+1; c<m.cols();c++)
                if (m(r,c) != static_cast<T>(0))
                    return false;
        }

        return true;
    }

    template <typename T>
    bool isUpperTriangular(const Matrix<T>& m)
    {
        if (m.rows() != m.cols())
            return false;

        for (unsigned int r=0; r<m.rows();r++)
        {
            //Check non-zeros on the diagonal
            if (m(r, r) == static_cast<T>(0))
                return false;
        }
        for (unsigned int r=1; r<m.rows();r++)
        {
            //Check all elements below diagonal are zero
            for (unsigned int c=0; c<=r-1;c++)
                if (m(r,c) != static_cast<T>(0))
                    return false;
        }

        return true;
    }
#include "MatrixHelpersExplicitTemplateInstantiations.hpp"

} //end namespace
