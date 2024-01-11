//
// Created by dorian on 03.11.2023.
// stoicadorian@gmail.com
//

#include "Matrix.hpp"
#include "MatrixHelpers.hpp"

#include <algorithm>
#include <cassert>
#include <map>
#include <numeric>
#include <stdexcept>

// anonymous namespace with helpers
namespace
{
    std::vector<LinearAlgebra::Matrix::Pivot> getPivotsFromUpperMatrix(const LinearAlgebra::Matrix::Matrix<long double>& upper)
    {
        std::vector<LinearAlgebra::Matrix::Pivot> pivots;

        for (unsigned int rIdx = 0; rIdx < upper.rows(); rIdx++)
        {
            const auto startIdx     = rIdx * upper.cols();
            const auto endIdx       = (rIdx+1) * upper.cols();

            //Search first non-zero in the current row
            const auto pivotIt = std::find_if(upper.begin() + startIdx, upper.begin() + endIdx,
                                              [](const auto& val)
                                              {
                                                  return std::abs(val) > 1e-9;
                                              });


            if (pivotIt != upper.begin() + endIdx)
            {
                unsigned int cIdx = std::distance(upper.begin() + startIdx, pivotIt);
                pivots.push_back({*pivotIt, rIdx, cIdx});
            }
        }

        return pivots;
    }

    unsigned int rankFromUpperMatrix(const LinearAlgebra::Matrix::Matrix<long double>& upper)
    {
        unsigned int rank = 0;

        for (unsigned int rIdx = 0; rIdx < upper.rows(); rIdx++)
        {
            const auto startIdx     = rIdx * upper.cols();
            const auto endIdx       = (rIdx+1) * upper.cols();

            //Search first non-zero in the current row
            const auto pivotIt = std::find_if(upper.begin() + startIdx, upper.begin() + endIdx,
                                              [](const auto& val)
                                              {
                                                  return std::abs(val) > 1e-9;
                                              });


            if (pivotIt != upper.begin() + endIdx)
                rank++;
        }
        return rank;
    }

    using Rd = std::pair<LinearAlgebra::Matrix::Matrix<long double>, std::optional<LinearAlgebra::Vector::Vector<long double>>>;

    Rd reduceUpperMatrixAndC(const LinearAlgebra::Matrix::Matrix<long double>& upper, const std::vector<LinearAlgebra::Matrix::Pivot>& pivots, const std::optional<LinearAlgebra::Vector::Vector<long double>>& c = std::nullopt)
    {
        auto rre = upper;

        auto d = c ? std::optional<LinearAlgebra::Vector::Vector<long double>>{c.value()} : std::nullopt;

        // Iterate pivots in reverse order !

        for (auto it = pivots.rbegin(); it != pivots.rend(); ++it)
        {
            const auto pivot = *it;
            const auto startIdx     = pivot.rowIndex * rre.cols();
            const auto endIdx       = (pivot.rowIndex+1) * rre.cols();
            const auto pivotValue                   = pivot.value;

            //Divide by pivots
            std::transform(rre.begin() + startIdx, rre.begin() + endIdx, &rre(0,0) + startIdx,
                           [pivotValue] (auto& val)
                           {
                               return val / pivotValue;
                           });
            if (d)
                d.value()[pivot.rowIndex] /= pivotValue;
        }

        //Create zeros above the pivots
        for (const auto pivot: pivots)
        {

            for (int r = static_cast<int>(pivot.rowIndex - 1); r >= 0; r--)
            {
                auto currRow = rre.getRow(r);
                const auto factor = rre(r, pivot.colIndex) / rre(pivot.rowIndex, pivot.colIndex);

                for (int col = static_cast<int>(pivot.colIndex); col < static_cast<int>(rre.cols()); col++)
                    rre(r, col) -= rre(pivot.rowIndex,col)*factor;
                if (d)
                    d.value()[r] -= d.value()[pivot.rowIndex]*factor;
            }
        }

        if (d)
            return std::make_pair(rre, d);
        return std::make_pair(rre, std::nullopt);
    }

    template <typename U>
    LinearAlgebra::Vector::Vector<long double> solveFullRankSystem(const LinearAlgebra::Matrix::LUFactorization& LU, const LinearAlgebra::Vector::Vector<U>& b)
    {
        // If row-exchanges were done during forward elimination, the permutation matrix must be applied on the b vector !
        // IIFE for the win
        const auto c = [&]
        {
            if (LU.permutation)
                return LU.lower.solveLowerTriangular(LU.permutation.value()*b);
            else
                return  LU.lower.solveLowerTriangular(b);
        }();

        //Return the solution
        return LU.upper.solveUpperTriangular(c);
    }

    template <typename U>
    std::optional<LinearAlgebra::Matrix::Solution> solveRankDeficientSystem(const LinearAlgebra::Matrix::LUFactorization& LU, unsigned int rank, const LinearAlgebra::Vector::Vector<U>& b)
    {
        // If row-exchanges were done during forward elimination, the permutation matrix must be applied on the b vector !
        // IIFE for the win
        const auto c = [&]
        {
            if (LU.permutation)
                return LU.lower.solveLowerTriangular(LU.permutation.value()*b);
            else
                return  LU.lower.solveLowerTriangular(b);
        }();

        // First check if the b-vector satisfy the solvability conditions (i.e. is in the column space of A).
        // Last (numRows - rank) rows in the upper matrix are zeros. The "c" vector must satisfy the same solvability conditions
        for (unsigned int i = rank; i < c.dim(); i++)
            if (std::abs(c[i]) > 1e-9)
                return std::nullopt;    // incompatible system, no solution

        // Convert from Ux = c to Rx = d
        auto pivots = getPivotsFromUpperMatrix(LU.upper);
        const auto [rre, d] = reduceUpperMatrixAndC(LU.upper, pivots,c);

        auto particularSolution = LinearAlgebra::Vector::Vector<long double>(LU.upper.cols());
        for (int i=0; i < static_cast<int>(rank); i++)
        {
            const auto& currPivot = pivots[i];
            particularSolution[currPivot.colIndex] = d.value()[i];
        }
        if (rank == rre.cols())
        {
            LinearAlgebra::Matrix::Solution solution;
            solution.unique = true;
            solution.uniqueSolution = particularSolution;
            return solution;
        }

        auto freeVariablesIndexes = std::vector<unsigned int>(LU.upper.cols());
        std::iota (std::begin(freeVariablesIndexes), std::end(freeVariablesIndexes), 0);
        for (const auto pivot : pivots)
            freeVariablesIndexes.erase(std::remove(freeVariablesIndexes.begin(), freeVariablesIndexes.end(), pivot.colIndex), freeVariablesIndexes.end());

        assert(freeVariablesIndexes.size() == LU.upper.cols() - rank);

        auto specialSolutions = std::vector<LinearAlgebra::Vector::Vector<long double>>();
        for (int i=0; i < static_cast<int>(freeVariablesIndexes.size()); i++)
        {
            auto specialSolution = LinearAlgebra::Vector::Vector<long double>(LU.upper.cols());
            specialSolution[freeVariablesIndexes[i]] = 1;
            for (int p = 0; p< static_cast<int>(pivots.size());p++)
            {
                const auto currPivot = pivots[p];
                specialSolution[currPivot.colIndex] = -rre(p, freeVariablesIndexes[i]);
            }

            specialSolutions.push_back(specialSolution);
        }

        LinearAlgebra::Matrix::Solution solution;

        solution.unique = false;
        solution.particularSolution = particularSolution;
        solution.specialSolutions = specialSolutions;
        return solution;
    }

} // end anonymous namespace

namespace LinearAlgebra::Matrix
{
    template <typename T>
    Matrix<T>::Matrix(const unsigned int r, const unsigned int c):
            numRows(r),
            numCols(c)
    {
        data = std::vector<T>(numRows*numCols);
    }

    template<typename T>
    Matrix<T>::Matrix(const std::vector<T>& inputData, unsigned int r, unsigned int c)
    {
        if (inputData.size() != r*c)
            throw std::runtime_error("Incompatible dimensions");

        numRows = r;
        numCols = c;
        data    = inputData;
    }

    template<typename T>
    Matrix<T>::Matrix(const Matrix<T>& other) :
            numRows(other.numRows),
            numCols(other.numCols),
            data(other.data)
    {
    }

    template<typename T>
    Matrix<T>::Matrix(Matrix<T>&& other) noexcept :
            data(std::move(other.data))
    {
        numRows = std::exchange(other.numRows, 0);
        numCols = std::exchange(other.numCols, 0);
    }


    template<typename T>
    Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other)
    {
        if (this != &other)
        {
            numRows = other.numRows;
            numCols = other.numCols;
            data    = other.data;
        }

        return *this;
    }

    template<typename T>
    Matrix<T>& Matrix<T>::operator=(Matrix<T>&& other) noexcept
    {
        if (this != &other)
        {
            numRows = std::exchange(other.numRows, 0);
            numCols = std::exchange(other.numCols, 0);
            data    = std::move(other.data);
        }

        return *this;
    }

    template<typename T>
    unsigned int Matrix<T>::rows() const
    {
        return numRows;
    }

    template<typename T>
    unsigned int Matrix<T>::cols() const
    {
        return numCols;
    }

    template<typename T>
    const T& Matrix<T>::operator()(const unsigned int rowIdx, const unsigned int colIdx) const
    {
        if (rowIdx >= numRows || colIdx >= numCols)
            throw(std::invalid_argument("Invalid row or column index"));

        const auto idx = (colIdx) + numCols * rowIdx;
        return data[idx];
    }


    template<typename T>
    T& Matrix<T>::operator()(const unsigned int rowIdx, const unsigned int colIdx)
    {
        //Use Scott Meyers's trick and make this operator call the const version of operator(row,col)
        return const_cast<T&>(static_cast<const Matrix<T>&>(*this)(rowIdx, colIdx));
    }

    template <typename T>
    typename std::vector<T>::const_iterator Matrix<T>::begin() const
    {
        return data.cbegin();
    }

    template <typename T>
    typename std::vector<T>::const_iterator Matrix<T>::end() const
    {
        return data.cend();
    }


    template<typename T>
    template<typename U>
    Matrix<typename std::common_type<T,U>::type> Matrix<T>::operator+(const Matrix<U>& other) const
    {
        if (other.rows() != numRows || other.cols() != numCols)
            throw std::invalid_argument("Cannot add incompatible matrices !");

        Matrix<typename std::common_type<T,U>::type> res(numRows, numCols);
        std::transform(data.begin(), data.end(), other.begin(), &res(0,0), std::plus<typename std::common_type<T,U>::type>());
        return res;
    }

    template<typename T>
    template<typename U>
    Matrix<typename std::common_type<T,U>::type> Matrix<T>::operator-(const Matrix<U>& other) const
    {
        if (other.rows() != numRows || other.cols() != numCols)
            throw std::invalid_argument("Cannot subtract incompatible matrices !");

        Matrix<typename std::common_type<T,U>::type> res(numRows, numCols);
        std::transform(data.begin(), data.end(), other.begin(), &res(0,0), std::minus<typename std::common_type<T,U>::type>());
        return res;
    }

    template<typename T>
    template<typename U>
    Matrix<typename std::common_type<T,U>::type> Matrix<T>::operator*(const Matrix<U>& other) const
    {
        if (other.rows() != numRows || other.cols() != numCols)
            throw std::invalid_argument("Cannot perform element-wise multiplication. Incompatible matrices !");

        Matrix<typename std::common_type<T,U>::type> res(numRows, numCols);
        std::transform(data.begin(), data.end(), other.begin(), &res(0,0), std::multiplies<typename std::common_type<T,U>::type>());
        return res;
    }

    template<typename T>
    template<typename U>
    Matrix<typename std::common_type<T,U>::type> Matrix<T>::operator/(const Matrix<U>& other) const
    {
        if (other.rows() != numRows || other.cols() != numCols)
            throw std::invalid_argument("Cannot perform element-wise division. Incompatible matrices !");

        if (std::find(other.begin(), other.end(), static_cast<U>(0)) != other.end())
            throw std::invalid_argument("Divisor matrix contains zeros !");

        Matrix<typename std::common_type<T,U>::type> res(numRows, numCols);
        std::transform(data.begin(), data.end(), other.begin(), &res(0,0), std::divides<typename std::common_type<T,U>::type>());
        return res;
    }

    template<typename T>
    Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other)
    {
        if (other.numRows != numRows || other.numCols != numCols)
            throw std::invalid_argument("Cannot add incompatible matrices !");

        std::transform(data.begin(), data.end(), other.data.begin(), data.begin(), std::plus<T>());
        return *this;
    }

    template<typename T>
    Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other)
    {
        if (other.numRows != numRows || other.numCols != numCols)
            throw std::invalid_argument("Cannot subtract incompatible matrices !");

        std::transform(data.begin(), data.end(), other.data.begin(), data.begin(), std::minus<T>());
        return *this;
    }

    template<typename T>
    Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& other)
    {
        if (other.numRows != numRows || other.numCols != numCols)
            throw std::invalid_argument("Cannot perform element-wise multiplication. Incompatible matrices !");

        std::transform(data.begin(), data.end(), other.data.begin(), data.begin(), std::multiplies<T>());
        return *this;
    }

    template<typename T>
    Matrix<T>& Matrix<T>::operator/=(const Matrix<T>& other)
    {
        if (other.numRows != numRows || other.numCols != numCols)
            throw std::invalid_argument("Cannot perform element-wise division. Incompatible matrices !");


        if (std::find(std::begin(other.data), std::end(other.data), static_cast<T>(0)) != std::end(other.data))
            throw std::invalid_argument("Divisor matrix contains zeros !");

        std::transform(data.begin(), data.end(), other.data.begin(), data.begin(), std::divides<T>());
        return *this;
    }

    template<typename T>
    template<typename U>
    Matrix<typename std::common_type<T,U>::type> Matrix<T>::operator+(const U val) const
    {
        Matrix<typename std::common_type<T,U>::type> res(numRows, numCols);
        std::transform(data.begin(), data.end(), &res(0,0),
                       [&](const T v) {return v + val; } );
        return res;
    }

    //Non-member operator function
    template<typename T, typename U>
    Matrix<typename std::common_type<T,U>::type> operator+(const T val, const Matrix<U>& matrix)
    {
        return matrix.operator+(val);
    }

    template<typename T>
    template<typename U>
    Matrix<typename std::common_type<T,U>::type> Matrix<T>::operator-(const U val) const
    {
        Matrix<typename std::common_type<T,U>::type> res(numRows, numCols);
        std::transform(data.begin(), data.end(), &res(0,0),
                       [&](const T v) {return v - val; } );
        return res;
    }

    template<typename T>
    template<typename U>
    Matrix<typename std::common_type<T,U>::type> Matrix<T>::operator*(const U val) const
    {
        Matrix<typename std::common_type<T,U>::type> res(numRows, numCols);
        std::transform(data.begin(), data.end(), &res(0, 0),
                       [&](const T v) {return v * val; } );
        return res;
    }

    //Non-member operator function
    template<typename T, typename U>
    Matrix<typename std::common_type<T,U>::type> operator*(const T val, const Matrix<U>& matrix)
    {
        return matrix.operator*(val);
    }

    template<typename T>
    template<typename U>
    Matrix<typename std::common_type<T,U>::type> Matrix<T>::operator/(const U val) const
    {
        if (val == static_cast<U>(0))
            throw std::invalid_argument("Attempt to divide by zero");

        Matrix<typename std::common_type<T,U>::type> res(numRows, numCols);
        std::transform(data.begin(), data.end(), &res(0,0),
                       [&](const T v) {return v / val; } );
        return res;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator+=(const T val)
    {
        std::transform(data.begin(), data.end(), data.begin(),
                       [&](const T v) {return v + val; } );
        return *this;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator-=(const T val)
    {
        std::transform(data.begin(), data.end(), data.begin(),
                       [&](const T v) {return v - val; } );
        return *this;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator*=(const T val)
    {
        std::transform(data.begin(), data.end(), data.begin(),
                       [&](const T v) {return v * val; } );
        return *this;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator/=(const T val)
    {
        if (val == 0)
            throw std::invalid_argument("Attempt to divide by zero");

        std::transform(data.begin(), data.end(), data.begin(),
                       [&](const T v) {return v / val; } );
        return *this;
    }

    template <typename T>
    template <typename U>
    Vector::Vector<typename std::common_type<T,U>::type> Matrix<T>::operator*(const Vector::Vector<U>& vec) const
    {
        if (numCols != vec.dim())
            throw std::invalid_argument("Vector dim must match the number of columns in the matrix !");

        Vector::Vector<typename std::common_type<T,U>::type> result(numRows);
        for (unsigned int idx = 0; idx < result.dim(); idx++)
        {
            const unsigned int startIdx = idx * numCols;
            const unsigned int endIdx   = (idx+1) * numCols;

            result[idx] = std::inner_product(data.begin()+startIdx, data.begin()+endIdx, vec.begin(), static_cast<typename std::common_type<T,U>::type>(0));
        }
        return result;
    }

    template <typename T>
    Matrix<T> Matrix<T>::transpose() const
    {
        Matrix<T> t(numCols, numRows);
        for (unsigned int rIdx = 0; rIdx<t.numRows; rIdx++)
            for (unsigned int cIdx = 0; cIdx<t.numCols; cIdx++)
                t(rIdx,cIdx) = operator()(cIdx, rIdx);

        return t;
    }

    template <typename T>
    Vector::Vector<T> Matrix<T>::getRow(const unsigned int r) const
    {
        if (r >= numRows)
            throw std::invalid_argument("Invalid row index !");

        const unsigned int startIdx = numCols * r;

        return Vector::Vector<T>({data.begin()+startIdx, data.begin() + startIdx + numCols});
    }

    template <typename T>
    void Matrix<T>::setRow(const std::vector<T>& row, const unsigned int r)
    {
        if (r >= numRows)
            throw std::invalid_argument("Invalid row index !");

        if (row.size() != numCols)
            throw std::invalid_argument("Incompatible row dimension !");

        const unsigned int startIdx = numCols * r;
        std::copy(row.begin(), row.end(), data.begin() + startIdx);
    }

    template <typename T>
    void Matrix<T>::setRow(const Vector::Vector<T>& row, unsigned int r)
    {
        if (r >= numRows)
            throw std::invalid_argument("Invalid row index !");

        if (row.dim() != numCols)
            throw std::invalid_argument("Incompatible row dimension !");

        const unsigned int startIdx = numCols * r;
        std::copy(row.begin(), row.end(), data.begin() + startIdx);
    }

    template <typename T>
    void Matrix<T>::swapRows(unsigned int rowIndex, unsigned int otherRowIndex)
    {
        if (rowIndex >= numRows || otherRowIndex >= numRows)
            throw std::invalid_argument("Invalid row indices");


        const unsigned int rowStart = rowIndex * numCols;
        const unsigned int rowEnd   = (rowIndex+1) * numCols;
        const unsigned int otherRowStart = otherRowIndex * numCols;
        std::swap_ranges(data.begin() + rowStart, data.begin() + rowEnd, data.begin() + otherRowStart);
    }

    template<typename T>
    template<typename U>
    Matrix<typename std::common_type<T,U>::type> Matrix<T>::multiply(const Matrix<U>& other) const
    {
        if (numCols != other.rows())
            throw std::invalid_argument("Cannot perform matrix multiplication. Incompatible matrices !");

        Matrix<typename std::common_type<T,U>::type> result(numRows, other.cols());

        for (unsigned int rIdx = 0; rIdx < numRows; rIdx++)
        {
            for (unsigned int cIdx = 0; cIdx < numCols; cIdx++)
            {
                const unsigned int startIdx =   cIdx * other.cols();
                const unsigned int endIdx   =   startIdx + other.cols();

                auto aij_times_row_j_of_B = Vector::Vector<typename std::common_type<T,U>::type>(other.cols());

                // Compute scalar-vector product :  A_ij * Row_j_of_B
                std::transform(other.begin() + startIdx, other.begin() + endIdx, &aij_times_row_j_of_B[0],
                               [&](const U v) {return v * this->operator()(rIdx, cIdx); } );

                // Contribute to the current linear combination of Row_i. Inject the result directly in the output matrix
                const unsigned int destinationStartIdx = result.cols() * rIdx;
                std::transform(result.begin() + destinationStartIdx, result.begin() + destinationStartIdx + result.cols(), aij_times_row_j_of_B.begin(),
                               &result(0,0) + destinationStartIdx, std::plus<typename std::common_type<T,U>::type>());
            }
        }

        return result;
    }

    template <typename T>
    LUFactorization Matrix<T>::factorizeLU() const
    {
        const unsigned int dim = numRows;
        const long double thresh = 1e-9;

        LUFactorization result = {
                identity<long double>(dim), // lower
                Matrix<long double>(std::vector<long double>(data.begin(), data.end()), numRows, numCols), // upper
                std::nullopt //permutation
        };

        for (unsigned i = 0; i<dim; i++)
        {
            if (std::abs(result.upper(i,i)) < thresh)
            {
                //  Current pivot is zero, search non-zero values in below entries
                // TODO consider swapping with the row having the biggest value in the current column
                if (auto rowIdxToSwap = findNonZeroPivot(result.upper, i, i))
                {
                    result.upper.swapRows(i, rowIdxToSwap.value());

                    if (result.permutation == std::nullopt)
                        result.permutation = identity<int>(dim);
                    result.permutation->swapRows(i, rowIdxToSwap.value());

                    result.lower.swapBelowDiagonal(i, rowIdxToSwap.value());
                }

                else
                    // Stop here since there are no non-zero entries below the current zero pivot. Singular matrix.
                    return result;
            }

            for (unsigned int j=i+1; j<dim; j++)
            {
                // Skip rows that already have zero below the pivot
                if (std::abs(result.upper(j,i)) > thresh)
                {
                    auto currRow        =  result.upper.getRow(i);
                    const long double factor            =  result.upper(j,i) / result.upper(i,i);
                    currRow                             *= factor;

                    const unsigned int destStartIdx = result.upper.cols() * j;
                    const unsigned int destEndIdx   = result.upper.cols() * (j+1);
                    std::transform(result.upper.begin() + destStartIdx, result.upper.begin() + destEndIdx, currRow.begin(), &result.upper(0,0) + destStartIdx, std::minus<long double>());

                    result.lower(j,i) = factor;
                }
            }
        }

        return result;
    }

    template <typename T>
    LUFactorization Matrix<T>::factorizeLU_echelon() const
    {
        const unsigned int dim = numRows;
        const long double thresh = 1e-9;

        LUFactorization result = {
                identity<long double>(dim), // lower
                Matrix<long double>(std::vector<long double>(data.begin(), data.end()), numRows, numCols), // upper
                std::nullopt //permutation
        };

        unsigned int pivotColIdx = 0;

        for (unsigned int rIdx = 0; rIdx < numRows-1; rIdx++)
        {
            if (pivotColIdx >= numCols)
                break;
            bool validColumnFound = false;
            for (unsigned int cIdx = pivotColIdx; cIdx < numCols;cIdx++)
            {
                // Current pivot candidate is zero. Attempt to find non-zeros below in the same column and swap rows.
                if (std::abs(result.upper(rIdx,cIdx)) < thresh)
                {
                    if (auto rowIdxToSwap = findNonZeroPivot(result.upper, rIdx, cIdx))
                    {
                        result.upper.swapRows(rIdx, rowIdxToSwap.value());

                        if (result.permutation == std::nullopt)
                            result.permutation = identity<int>(dim);
                        result.permutation->swapRows(rIdx, rowIdxToSwap.value());

                        result.lower.swapBelowDiagonal(rIdx, rowIdxToSwap.value());

                        pivotColIdx = cIdx;
                        validColumnFound = true;
                    }
                }

                else
                {
                    pivotColIdx         = cIdx;
                    validColumnFound    = true;
                }

                if (validColumnFound)
                    break;
            }

            for (unsigned int nextRowIdx = rIdx+1; nextRowIdx < dim; nextRowIdx++)
            {
                // Skip rows that already have zero below the pivot
                if (std::abs(result.upper(nextRowIdx,pivotColIdx)) > thresh)
                {
                    auto currRow        =  result.upper.getRow(rIdx);
                    const long double factor            =  result.upper(nextRowIdx,pivotColIdx) / result.upper(rIdx, pivotColIdx);
                    currRow                             *= factor;

                    const unsigned int destStartIdx = result.upper.cols() * nextRowIdx;
                    const unsigned int destEndIdx   = result.upper.cols() * (nextRowIdx+1);
                    std::transform(result.upper.begin() + destStartIdx, result.upper.begin() + destEndIdx, currRow.begin(), &result.upper(0,0) + destStartIdx, std::minus<long double>());

                    result.lower(nextRowIdx,rIdx) = factor;
                }
            }

            pivotColIdx++;
        }

        return result;
    }

    template<typename T>
    Matrix<long double> Matrix<T>::reduced_row_echelon() const
    {
        const auto LU_echelon = factorizeLU_echelon();
        auto pivots = getPivotsFromUpperMatrix(LU_echelon.upper);
        return reduceUpperMatrixAndC(LU_echelon.upper, pivots).first;
    }

    template <typename T>
    std::vector<Pivot> Matrix<T>::getPivots() const
    {
        const auto LU = factorizeLU_echelon();
        return getPivotsFromUpperMatrix(LU.upper);
    }

    template <typename T>
    unsigned int Matrix<T>::rank() const
    {
        const auto LU = factorizeLU_echelon();
        return rankFromUpperMatrix(LU.upper);
    }

    template<typename T>
    template<class U>
    std::optional<Solution> Matrix<T>::solve(const Vector::Vector<U>& b) const
    {
        if (b.dim() != numRows)
            throw std::invalid_argument("Incompatible dimensions");

        const auto LU = factorizeLU_echelon();
        const unsigned int rank = rankFromUpperMatrix(LU.upper);

        if (rank == numRows && rank == numCols)
        {
            Solution solution;
            solution.unique         = true;
            solution.uniqueSolution = solveFullRankSystem(LU, b);
            return solution;
        }
        else
            return solveRankDeficientSystem(LU, rank, b);
    }

    template<typename T>
    template<class U>
    Vector::Vector<long double> Matrix<T>::solveLowerTriangular(const Vector::Vector<U>& b) const
    {
        if (numRows != numCols)
            throw std::runtime_error("Currently only square matrices are supported !");

        if (b.dim() != numRows)
            throw std::invalid_argument("Incompatible dimensions");

        if (!isLowerTriangular(*this))
            throw std::runtime_error("Matrix must be lower triangular");

        auto solution = Vector::Vector<long double>(numCols);

        solution[0] = static_cast<long double>(b[0])/this->operator()(0,0);

        for (unsigned int r=1;r<numRows;r++)
        {
            long double term = 0.0;
            for (unsigned int c=0;c<r;c++)
                term += this->operator()(r,c)*solution[c];
            term -= b[r];
            solution[r] = -term/this->operator()(r,r);
        }

        return solution;
    }

    template<typename T>
    template<class U>
    Vector::Vector<long double> Matrix<T>::solveUpperTriangular(const Vector::Vector<U>& b) const
    {
        if (numRows != numCols)
            throw std::runtime_error("Currently only square matrices are supported !");

        if (b.dim() != numRows)
            throw std::invalid_argument("Incompatible dimensions");

        if (!isUpperTriangular(*this))
            throw std::runtime_error("Matrix must be upper triangular");

        auto solution = Vector::Vector<long double>(numCols);
        solution[numCols-1] = static_cast<long double>(b[numRows-1])/this->operator()(numRows-1, numCols-1);

        for (int r=static_cast<int>(numRows)-2;r>=0;r--)
        {
            long double term = 0.0;
            for (int c=static_cast<int>(numCols)-1;c>=r;c--)
                term +=this->operator()(r,c)*solution[c];
            term -= b[r];
            solution[r] = -term/ this->operator()(r,r);
        }
        return solution;
    }

    template <typename T>
    void Matrix<T>::swapBelowDiagonal(const unsigned int row, const unsigned int otherRow)
    {
        if (row >= numRows || otherRow >= numRows)
            throw std::invalid_argument("Invalid row index !");

        const unsigned int rowStartIdx  = numCols * row;
        const unsigned int rowEndIdx    = numCols * row + row;

        const unsigned int otherRowStartIdx  = numCols * otherRow;

        std::swap_ranges(data.begin() + rowStartIdx, data.begin() + rowEndIdx, data.begin() + otherRowStartIdx);
    }

    template <typename T>
    std::optional<Matrix<long double>> Matrix<T>::inverse() const
    {
        if (numRows != numCols)
            throw std::runtime_error("Matrix must be square !");

        const int dim = static_cast<int>(numRows);

        auto LU = factorizeLU();
        //Check non-zero pivots
        for (int r=0; r<dim; r++)
            if (std::abs(LU.upper(r,r)) < 1e-9)
                // Singular matrix
                return std::nullopt;

        // Initialize inverse with identity. If row-exchanges were performed during LU factorization, apply permutation matrix on the identity.
        auto inverse = [&]
        {
            if (LU.permutation)
                return LU.permutation->multiply(identity<long double>(dim));
            else
                return identity<long double>(dim);
        }();


        // Apply forward elimination steps on the identity matrix (i.e. create L inverse)
        for (int i = 0; i<dim-1; i++)
        {
            for (int j=i+1; j<dim; j++)
            {
                auto currRow                        =  inverse.getRow(i);
                const long double factor            =  LU.lower(j,i);
                currRow                             *= factor;

                const unsigned int destStartIdx = inverse.cols() * j;
                const unsigned int destEndIdx   = inverse.cols() * (j+1);
                std::transform(inverse.begin() + destStartIdx, inverse.begin() + destEndIdx, currRow.begin(), &inverse(0,0) + destStartIdx, std::minus<long double>());
            }
        }

        // Create zeros above the diagonal in the upper matrix. Update the inverse with the same row operations.
        for (int i = dim-1; i>=0; i--)
        {
            for (int j = i - 1; j >= 0; j--)
            {
                auto currUpperRow           =  LU.upper.getRow(i);
                auto currInverseRow         =  inverse.getRow(i);
                const long double factor    =  LU.upper(j,i) / LU.upper(i,i);

                currUpperRow                            *= factor;
                currInverseRow                          *= factor;

                const unsigned int destStartIdx = inverse.cols() * j;
                const unsigned int destEndIdx = inverse.cols() * (j+1);

                std::transform(LU.upper.begin() + destStartIdx, LU.upper.begin() + destEndIdx, currUpperRow.begin(), &LU.upper(0,0) + destStartIdx, std::minus<long double>());
                std::transform(inverse.begin() + destStartIdx, inverse.begin() + destEndIdx, currInverseRow.begin(), &inverse(0,0) + destStartIdx, std::minus<long double>());
            }
        }

        // At this point, the (modified) upper matrix is a diagonal matrix. Finally, divide all rows by the pivots and return the inverse.
        for (int i = 0; i<dim; i++)
        {
            const long double pivot         = LU.upper(i,i);
            const unsigned int destStartIdx = inverse.cols() * i;
            const unsigned int destEndIdx   = inverse.cols() * (i+1);

            std::transform(inverse.begin() + destStartIdx, inverse.begin() + destEndIdx, &inverse(0,0) + destStartIdx,
                           [&](const long double v) {return v / pivot; } );
        }
        return inverse;
    }

    template<typename T>
    long double Matrix<T>::determinant() const
    {
        const auto LU = factorizeLU();
        long double det = 1.;
        for (unsigned int r = 0; r<LU.upper.rows(); r++)
            det *= LU.upper(r,r);

        return det;
    }

#include "MatrixExplicitTemplateInstantiations.hpp"
}   //namespace LinearAlgebra::Matrix
