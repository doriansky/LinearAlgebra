//
// Created by dorian on 19.01.2024.
//

#include "MatrixHelpers.hpp"

#include <algorithm>
#include <cassert>
#include <numeric>

namespace LinearAlgebra::Matrix::InternalHelpers
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

//    using Rd = std::pair<LinearAlgebra::Matrix::Matrix<long double>, std::optional<LinearAlgebra::Vector::Vector<long double>>>;

    Rd reduceUpperMatrixAndC(const LinearAlgebra::Matrix::Matrix<long double>& upper, const std::vector<LinearAlgebra::Matrix::Pivot>& pivots, const std::optional<LinearAlgebra::Vector::Vector<long double>>& c)
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
