//
// Created by dorian on 29.12.2023.
// stoicadorian@gmail.com
//

#include "MatrixToolbox.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>
#include <stdexcept>

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

    using Rd = std::pair<LinearAlgebra::Matrix::Matrix<long double>, std::optional<LinearAlgebra::Vector::Vector<long double>>>;
    Rd reduceUpperMatrixAndC(const LinearAlgebra::Matrix::Matrix<long double>& upper, const std::vector<LinearAlgebra::Matrix::Pivot>& pivots, const std::optional<LinearAlgebra::Vector::Vector<long double>>& c=std::nullopt)
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
                auto currRow = getRow(rre, r);
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

    template <typename U>
    LinearAlgebra::Vector::Vector<long double> solveFullRankSystem(const LinearAlgebra::Matrix::LUFactorization& LU, const LinearAlgebra::Vector::Vector<U>& b)
    {
        // If row-exchanges were done during forward elimination, the permutation matrix must be applied on the b vector !
        // IIFE for the win
        const auto c = [&]
        {
            if (LU.permutation)
                return solveLowerTriangular(LU.lower, LU.permutation.value()*b);
            else
                return solveLowerTriangular(LU.lower, b);
        }();

        //Return the solution
        return solveUpperTriangular(LU.upper,c);
    }

    template <typename U>
    std::optional<LinearAlgebra::Matrix::Solution> solveRankDeficientSystem(const LinearAlgebra::Matrix::LUFactorization& LU, unsigned int rank, const LinearAlgebra::Vector::Vector<U>& b)
    {
        // If row-exchanges were done during forward elimination, the permutation matrix must be applied on the b vector !
        // IIFE for the win
        const auto c = [&]
        {
            if (LU.permutation)
                return solveLowerTriangular(LU.lower, LU.permutation.value()*b);
            else
                return solveLowerTriangular(LU.lower, b);
        }();

        const unsigned int numRows = LU.upper.rows();
        const unsigned int numCols = LU.upper.cols();
        assert(numRows == c.dim());

        // First check if the Ux = c system is solvable: last (numRows - rank) rows in the upper-echelon matrix are zeros. The "c" vector must satisfy the same conditions
        // If the rank equals the number of rows, there are no conditions and there will be infinitely many solutions for every b-vector in Ax=b.
        for (unsigned int rowIdx = rank; rowIdx < numRows; rowIdx++)
            if (std::abs(c[rowIdx]) > 1e-9)
                return std::nullopt;    // incompatible system, no solution

        // Convert from Ux = c to Rx = d
        const auto pivots = getPivotsFromUpperMatrix(LU.upper);
        assert(pivots.size() == rank);
        const auto [rre, d] = reduceUpperMatrixAndC(LU.upper, pivots,c);

        // Construct particular solution: first "rank" entries from d are mapped to the indexes of the pivots columns in the solution
        auto particularSolution = LinearAlgebra::Vector::Vector<long double>(numCols);
        for (unsigned int i=0; i < rank; i++)
        {
            const auto& currPivot = pivots[i];
            particularSolution[currPivot.colIndex] = d.value()[i];
        }

        // If rank is numCols and smaller than numRows and the system is solvable, the particular solution is the unique solution !
        if (rank == numCols && rank < numRows)
        {
            LinearAlgebra::Matrix::Solution solution;
            solution.unique = true;
            solution.uniqueSolution = particularSolution;
            return solution;
        }

        // Get the indexes of the columns without pivots (the 'free' columns).
        const auto freeColIndexes = [&]
        {
            auto freeVariablesIndexes = std::vector<unsigned int>(LU.upper.cols());
            std::iota (std::begin(freeVariablesIndexes), std::end(freeVariablesIndexes), 0);
            for (const auto pivot : pivots)
                freeVariablesIndexes.erase(std::remove(freeVariablesIndexes.begin(), freeVariablesIndexes.end(), pivot.colIndex), freeVariablesIndexes.end());

            return freeVariablesIndexes;
        }();

        // Construct special solutions: there are "numCols - rank" such solutions.
        assert(freeColIndexes.size() == numCols - rank);

        auto specialSolutions = std::vector<LinearAlgebra::Vector::Vector<long double>>();
        for (unsigned int i=0; i < freeColIndexes.size(); i++)
        {
            auto specialSolution = LinearAlgebra::Vector::Vector<long double>(numCols);
            specialSolution[freeColIndexes[i]] = 1;
            for (unsigned  int p = 0; p < rank; p++)
            {
                const auto currPivot = pivots[p];
                specialSolution[currPivot.colIndex] = -rre(p, freeColIndexes[i]);
            }

            specialSolutions.push_back(specialSolution);
        }

        LinearAlgebra::Matrix::Solution solution;

        solution.unique = false;
        solution.particularSolution = particularSolution;
        solution.specialSolutions = specialSolutions;
        return solution;
    }

    template LinearAlgebra::Vector::Vector<long double> solveFullRankSystem(const LinearAlgebra::Matrix::LUFactorization& LU, const LinearAlgebra::Vector::Vector<int>& b);
    template LinearAlgebra::Vector::Vector<long double> solveFullRankSystem(const LinearAlgebra::Matrix::LUFactorization& LU, const LinearAlgebra::Vector::Vector<float>& b);
    template LinearAlgebra::Vector::Vector<long double> solveFullRankSystem(const LinearAlgebra::Matrix::LUFactorization& LU, const LinearAlgebra::Vector::Vector<double>& b);
    template LinearAlgebra::Vector::Vector<long double> solveFullRankSystem(const LinearAlgebra::Matrix::LUFactorization& LU, const LinearAlgebra::Vector::Vector<long double>& b);

    template std::optional<LinearAlgebra::Matrix::Solution> solveRankDeficientSystem(const LinearAlgebra::Matrix::LUFactorization& LU, unsigned int rank, const LinearAlgebra::Vector::Vector<int>& b);
    template std::optional<LinearAlgebra::Matrix::Solution> solveRankDeficientSystem(const LinearAlgebra::Matrix::LUFactorization& LU, unsigned int rank, const LinearAlgebra::Vector::Vector<float>& b);
    template std::optional<LinearAlgebra::Matrix::Solution> solveRankDeficientSystem(const LinearAlgebra::Matrix::LUFactorization& LU, unsigned int rank, const LinearAlgebra::Vector::Vector<double>& b);
    template std::optional<LinearAlgebra::Matrix::Solution> solveRankDeficientSystem(const LinearAlgebra::Matrix::LUFactorization& LU, unsigned int rank, const LinearAlgebra::Vector::Vector<long double>& b);
}

namespace LinearAlgebra::Matrix
{
    const long double thresh = 1e-14;

    template <typename T>
    Matrix<T> identity(unsigned int d)
    {
        Matrix<T> identity(d, d);
        for (unsigned int i = 0; i<d; i++)
            identity(i,i) = static_cast<T>(1);

        return identity;
    }

    Matrix<double> hilbert_matrix(const unsigned int dim)
    {
        Matrix<double> h(dim, dim);
        for (unsigned int rIdx = 0; rIdx<dim; rIdx++)
            for (unsigned int cIdx = 0; cIdx<dim; cIdx++)
                h(rIdx,cIdx) = 1./((rIdx+1)+(cIdx+1) - 1);

        return h;
    }

    std::optional<unsigned int> findNonZeroPivot(const Matrix<long double>& mat, const unsigned int row, const unsigned int col)
    {
        for (unsigned int rowIdx = row+1; rowIdx < mat.rows(); rowIdx++)
        {
            if (std::abs(mat(rowIdx, col)) > thresh)
                return rowIdx;
        }
        return std::nullopt;
    }

    std::optional<unsigned int> findMaxNonZeroPivot(const Matrix<long double>& mat, const unsigned int row, const unsigned int col)
    {
        long double max = 0.;
        unsigned int idx = 0;
        for (unsigned int rowIdx = row+1; rowIdx < mat.rows(); rowIdx++)
        {
            if (std::abs(mat(rowIdx, col)) > max)
            {
                max = mat(rowIdx, col);
                idx = rowIdx;
            }
        }

        return (std::abs(max) > thresh) ? std::optional<unsigned int>(idx) : std::nullopt;
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
                if (std::abs(m(r,c)) > thresh)
                    return false;
        }

        return true;
    }

    template <typename T>
    Matrix<T> transpose(const Matrix<T>& m)
    {
        Matrix<T> t(m.cols(), m.rows());
        for (unsigned int rIdx = 0; rIdx<t.rows(); rIdx++)
            for (unsigned int cIdx = 0; cIdx<t.cols(); cIdx++)
                t(rIdx,cIdx) = m(cIdx, rIdx);

        return t;
    }

    template <typename T>
    Vector::Vector<T> getRow(const Matrix<T>& m, const unsigned int r)
    {
        if (r >= m.rows())
            throw std::invalid_argument("Invalid row index !");

        const unsigned int startIdx = m.cols() * r;

        return Vector::Vector<T>({m.begin()+startIdx, m.begin() + startIdx + m.cols()});
    }

    template <typename T>
    void setRow(Matrix<T>& m, const std::vector<T>& row, const unsigned int r)
    {
        if (r >= m.rows())
            throw std::invalid_argument("Invalid row index !");

        if (row.size() != m.cols())
            throw std::invalid_argument("Incompatible row dimension !");

        const unsigned int startIdx = m.cols() * r;
        std::copy(row.begin(), row.end(), &m(0,0) + startIdx);
    }

    template <typename T>
    void setRow(Matrix<T>& m, const Vector::Vector<T>& row, unsigned int r)
    {
        if (r >= m.rows())
            throw std::invalid_argument("Invalid row index !");

        if (row.dim() != m.cols())
            throw std::invalid_argument("Incompatible row dimension !");

        const unsigned int startIdx = m.cols() * r;
        std::copy(row.begin(), row.end(), &m(0,0) + startIdx);
    }

    template <typename T>
    void swapRows(Matrix<T>& m, unsigned int rowIndex, unsigned int otherRowIndex)
    {
        if (rowIndex >= m.rows() || otherRowIndex >= m.rows())
            throw std::invalid_argument("Invalid row indices");


        const unsigned int rowStart = rowIndex * m.cols();
        const unsigned int rowEnd   = (rowIndex+1) * m.cols();
        const unsigned int otherRowStart = otherRowIndex * m.cols();
        std::swap_ranges(&m(0,0) + rowStart, &m(0,0) + rowEnd, &m(0,0) + otherRowStart);
    }


    void swapBelowDiagonal(Matrix<long double>& m, const unsigned int row, const unsigned int otherRow)
    {
        if (row >= m.rows() || otherRow >= m.cols())
            throw std::invalid_argument("Invalid row index !");

        const unsigned int rowStartIdx  = m.cols() * row;
        const unsigned int rowEndIdx    = m.cols() * row + row;

        const unsigned int otherRowStartIdx  = m.cols() * otherRow;

        std::swap_ranges(&m(0,0) + rowStartIdx, &m(0,0) + rowEndIdx, &m(0,0) + otherRowStartIdx);
    }


    template <typename T>
    LUFactorization factorizeLU(const Matrix<T>& m)
    {
        const unsigned int dim = m.rows();

        LUFactorization result = {
                identity<long double>(dim), // lower
                Matrix<long double>(std::vector<long double>(m.begin(), m.end()), m.rows(), m.cols()), // upper
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
                    swapRows(result.upper, i, rowIdxToSwap.value());

                    if (result.permutation == std::nullopt)
                    {
                        result.permutation = identity<int>(dim);
                        result.pSign = 1;
                    }

                    swapRows(result.permutation.value(), i, rowIdxToSwap.value());
                    result.pSign.value() *= -1;

                    swapBelowDiagonal(result.lower, i, rowIdxToSwap.value());
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
                    auto currRow        =  getRow(result.upper, i);
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
    LUFactorization factorizeLU_echelon(const Matrix<T>& m)
    {
        const unsigned int dim = m.rows();

        LUFactorization result = {
                identity<long double>(dim), // lower
                Matrix<long double>(std::vector<long double>(m.begin(), m.end()), m.rows(), m.cols()), // upper
                std::nullopt //permutation
        };

        unsigned int pivotColIdx = 0;

        for (unsigned int rIdx = 0; rIdx < m.rows()-1; rIdx++)
        {
            if (pivotColIdx >= m.cols())
                break;
            bool validColumnFound = false;
            for (unsigned int cIdx = pivotColIdx; cIdx < m.cols(); cIdx++)
            {
                // Current pivot candidate is zero. Attempt to find non-zeros below in the same column and swap rows.
                if (std::abs(result.upper(rIdx,cIdx)) < thresh)
                {
                    if (auto rowIdxToSwap = findNonZeroPivot(result.upper, rIdx, cIdx))
                    {
                        swapRows(result.upper, rIdx, rowIdxToSwap.value());

                        if (result.permutation == std::nullopt)
                        {
                            result.permutation = identity<int>(dim);
                            result.pSign = 1;
                        }

                        swapRows(result.permutation.value(), rIdx, rowIdxToSwap.value());
                        result.pSign.value() *= -1;

                        swapBelowDiagonal(result.lower, rIdx, rowIdxToSwap.value());

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
                    auto currRow        =  getRow(result.upper, rIdx);
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

    template <typename T>
    QRFactorization factorizeQR(const Matrix<T>& m)
    {
        QRFactorization result = {
                Matrix<long double>(std::vector<long double>(m.begin(), m.end()), m.rows(), m.cols()), // Q
                identity<long double>(m.cols())
        };

        for (unsigned int cIdx = 0; cIdx < m.cols(); cIdx++)
        {
            long double ss = 0;
            // Subtract the components in the directions of the previous columns
            for (int c = static_cast<int>(cIdx)-1; c>=0; c--)
            {
                // Compute dot between current column and previous column
                Vector::Vector<long double> cc(m.rows());
                Vector::Vector<long double> pc(m.rows());
                for (unsigned int rIdx = 0; rIdx < m.rows(); rIdx++)
                {
                    cc[rIdx] = result.Q(rIdx, cIdx);
                    pc[rIdx] = result.Q(rIdx, c);
                }
                const long double dot = pc.dot(cc);
                for (unsigned int rIdx = 0; rIdx < m.rows(); rIdx++)
                    result.Q(rIdx, cIdx) -= dot*result.Q(rIdx, c);
            }


            for (unsigned int rIdx = 0; rIdx < m.rows(); rIdx++)
                ss += std::pow(result.Q(rIdx, cIdx),2);

            const long double norm = std::sqrt(ss);
            for (unsigned int rIdx = 0; rIdx < m.rows(); rIdx++)
                result.Q(rIdx, cIdx) /= norm;

            for (unsigned int c = cIdx; c<m.cols();c++)
            {
                long double r_entry = 0;
                for (unsigned int rIdx = 0; rIdx<m.rows(); rIdx++)
                    r_entry += result.Q(rIdx, cIdx) * m(rIdx, c);

                result.R(cIdx, c) = r_entry;
            }
        }

        return result;
    }

    template<typename T>
    Matrix<long double> reduced_row_echelon(const Matrix<T>& m)
    {
        const auto LU_echelon = factorizeLU_echelon(m);
        auto pivots = getPivotsFromUpperMatrix(LU_echelon.upper);
        return reduceUpperMatrixAndC(LU_echelon.upper, pivots).first;
    }


    template <typename T>
    std::optional<Matrix<long double>> inverse(const Matrix<T>& m)
    {
        if (m.rows() != m.cols())
            throw std::runtime_error("Matrix must be square !");

        const int dim = static_cast<int>(m.rows());

        auto LU = factorizeLU(m);
        //Check non-zero pivots
        for (int r=0; r<dim; r++)
            if (std::abs(LU.upper(r,r)) < 1e-9)
                // Singular matrix
                return std::nullopt;

        // Initialize inverse with identity. If row-exchanges were performed during LU factorization, apply permutation matrix on the identity.
        auto inverse = [&]
        {
            if (LU.permutation)
                return LU.permutation.value()*(identity<long double>(dim));
            else
                return identity<long double>(dim);
        }();


        // Apply forward elimination steps on the identity matrix (i.e. create L inverse)
        for (int i = 0; i<dim-1; i++)
        {
            for (int j=i+1; j<dim; j++)
            {
                auto currRow                        =  getRow(inverse, i);
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
                auto currUpperRow           =  getRow(LU.upper, i);
                auto currInverseRow         =  getRow(inverse, i);
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

    template <typename T>
    std::optional<Matrix<long double>> left_inverse(const Matrix<T>& m)
    {
        const unsigned int R = rank(m);
        if (R == m.cols() && m.rows() >= m.cols())
        {
            const auto transposed = transpose(m);
            return (inverse(transposed*m).value()*(transposed));
        }
        return std::nullopt;
    }

    template <typename T>
    std::optional<Matrix<long double>> right_inverse(const Matrix<T>& m)
    {
        const unsigned int R = rank(m);
        if (R == m.rows() && m.rows() <= m.cols())
        {
            const auto transposed = transpose(m);
            return transposed*(inverse(m*(transposed)).value());
        }
        return std::nullopt;
    }

    template<typename T>
    long double determinant(const Matrix<T>& m)
    {
        if (m.rows() != m.cols())
            throw std::runtime_error("Matrix must be square");

        const auto LU = factorizeLU(m);
        long double det = 1.;
        for (unsigned int r = 0; r<LU.upper.rows(); r++)
            det *= LU.upper(r,r);

        if (LU.permutation)
            det *= LU.pSign.value();
        return det;
    }

    template <typename T>
    std::vector<Pivot> getPivots(const Matrix<T>& m)
    {
        const auto LU = factorizeLU_echelon(m);
        return getPivotsFromUpperMatrix(LU.upper);
    }

    template <typename T>
    unsigned int rank(const Matrix<T>& m)
    {
        const auto LU = factorizeLU_echelon(m);
        return rankFromUpperMatrix(LU.upper);
    }

    template<typename T, typename U>
    std::optional<Solution> solve(const Matrix<T>& A, const Vector::Vector<U>& b)
    {
        if (b.dim() != A.rows())
            throw std::invalid_argument("Incompatible dimensions");

        const auto LU = factorizeLU_echelon(A);
        const unsigned int rank = rankFromUpperMatrix(LU.upper);

        if (rank == A.rows() && rank == A.cols())
        {
            Solution solution;
            solution.unique         = true;
            solution.uniqueSolution = solveFullRankSystem(LU, b);
            return solution;
        }
        else
            return solveRankDeficientSystem(LU, rank, b);
    }

    template<typename T, typename U>
    Vector::Vector<long double> solveLowerTriangular(const Matrix<T>& m, const Vector::Vector<U>& b)
    {
        if (m.rows() != m.cols())
            throw std::runtime_error("Currently only square matrices are supported !");

        if (b.dim() != m.rows())
            throw std::invalid_argument("Incompatible dimensions");

        if (!isLowerTriangular(m))
            throw std::runtime_error("Matrix must be lower triangular");

        auto solution = Vector::Vector<long double>(m.cols());

        solution[0] = static_cast<long double>(b[0])/m(0,0);

        for (unsigned int r=1;r<m.rows();r++)
        {
            long double term = 0.0;
            for (unsigned int c=0;c<r;c++)
                term += m(r,c)*solution[c];
            term -= b[r];
            solution[r] = -term/m(r,r);
        }

        return solution;
    }

    template<typename T, typename U>
    Vector::Vector<long double> solveUpperTriangular(const Matrix<T>& m, const Vector::Vector<U>& b)
    {
        if (m.rows() != m.cols())
            throw std::runtime_error("Currently only square matrices are supported !");

        if (b.dim() != m.rows())
            throw std::invalid_argument("Incompatible dimensions");

        if (!isUpperTriangular(m))
            throw std::runtime_error("Matrix must be upper triangular");

        auto solution = Vector::Vector<long double>(m.cols());
        solution[m.cols()-1] = static_cast<long double>(b[m.cols()-1])/m(m.rows()-1, m.cols()-1);

        for (int r=static_cast<int>(m.rows())-2;r>=0;r--)
        {
            long double term = 0.0;
            for (int c=static_cast<int>(m.cols())-1;c>=r;c--)
                term +=m(r,c)*solution[c];
            term -= b[r];
            solution[r] = -term / m(r,r);
        }
        return solution;
    }

    template<typename T, typename U>
    std::optional<FitLLSQ> fit_LLSQ(const Matrix<T>& A, const Vector::Vector<U>& b)
    {
        const unsigned int R = rank(A);
        if (R == A.cols())
        {
            FitLLSQ result = {Vector::Vector<long double>(0), 0};

            const auto transposed = transpose(A);
            result.bestEstimate = inverse(transposed*A).value()*(transposed)*b;

            const auto errorVec = b - A*(result.bestEstimate);
            result.error = std::sqrt(errorVec.dot(errorVec));

            return result;
        }
        return std::nullopt;
    }


#include "MatrixHelpersExplicitTemplateInstantiations.hpp"

} //end namespace
