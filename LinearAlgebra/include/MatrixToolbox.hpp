//
// Created by dorian on 29.12.2023.
// stoicadorian@gmail.com
//

#ifndef LINEARALGEBRATOOLBOX_MATRIXHELPERS_HPP
#define LINEARALGEBRATOOLBOX_MATRIXHELPERS_HPP

#include "Matrix.hpp"

namespace LinearAlgebra::Matrix
{
    struct LUFactorization
    {
        Matrix<long double>              lower;
        Matrix<long double>              upper;
        std::optional<Matrix<int>>       permutation;
        std::optional<int>               pSign;
    };

    struct QRFactorization
    {
        Matrix<long double>              Q;
        Matrix<long double>              R;
    };

    struct Pivot
    {
        long double     value;
        unsigned int    rowIndex;
        unsigned int    colIndex;
    };

    struct Solution
    {
        bool                                                    unique = false;
        std::optional<Vector::Vector<long double>>              uniqueSolution;
        std::optional<Vector::Vector<long double>>              particularSolution;
        std::optional<std::vector<Vector::Vector<long double>>> specialSolutions;
    };

    struct FitLLSQ
    {
        Vector::Vector<long double> bestEstimate;
        long double                 error;
    };

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


    /**
    * Transpose the matrix
    *
    * @return: Matrix: the transposed matrix.
    */
    template <typename T>
    [[nodiscard]] Matrix<T> transpose(const Matrix<T>&);

    /**
    * Get matrix row.
    *
    * @param: unsigned int : row index
    * @return: Vector<T>:
    */
    template <typename T>
    [[nodiscard]] Vector::Vector<T> getRow(const Matrix<T>&, unsigned int);


    /**
    * Set matrix row.
    *
    * @param: std::vector<T>: the row to be set. Its size must match the number of columns in the matrix.
    * @param: unsigned int: row index
    */
    template <typename T>
    void setRow(Matrix<T>&, const std::vector<T>&,  unsigned int);


    /**
    * Set matrix row.
    *
    * @param: Vector<T>: the row to be set. Its dimension must match the number of columns in the matrix.
    * @param: unsigned int: row index
    */
    template <typename T>
    void setRow(Matrix<T>&, const Vector::Vector<T>&,       unsigned int);


    /**
    * Swap matrix rows
    *
    * @param: unsigned int rowIndex
    * @param: unsigned int otherRowIndex
    */
    template <typename T>
    void swapRows(Matrix<T>&, unsigned int, unsigned int);


    /**
    * Swap row entries below main diagonal (diagonal elements excluded).
    *
    * @param: unsigned int rowIndex
    * @param: unsigned int otherRowIndex
    */
    void swapBelowDiagonal(Matrix<long double>&, unsigned int, unsigned int);

    /**
    * Factorize the matrix into Lower and Upper matrices (and an optional permutation matrix ) such that A = L*U
    * or P*A = L*U when row exchanges are required.
    *
    * NOTE : For singular or rectangular matrices the function will return as soon as a column is found with zeros below the pivot.
    *        The lower and "partial" upper factorization will still reconstruct the input matrix but the U will not be a fully upper matrix (elimination is not complete).
    *        Therefore, for singular or rectangular matrices one can use LU_echelon() instead.
    *
    * @return: struct containing lower triangular matrix, upper triangular matrix and the optional permutation matrix
    *          lower:          the L matrix is square, numRows x numRows
    *          upper:          the U matrix has the same dimensions as the input, numRows x numCols
    *          permutation:    the optional P matrix (if has value) is square, numRows x numRows
    *          pSign:          the optional sign of the permutation (+1/-1 for even/odd row swaps)
    */
    template <typename T>
    [[nodiscard]] LUFactorization factorizeLU(const Matrix<T>& );



    /**
    * Factorize the matrix into Lower and Upper-Echelon matrices (and an optional permutation matrix ) such that A = L*U_echelon
    * or P*A = L*U_echelon when row exchanges are required.
    * The pivots are the first non-zero entries in their rows. Last numRows - R rows are zero (where R is the rank, i.e. the number of non-zero pivots).
    *
    * NOTE : For non-singular square matrices the result is identical with the one provided by LU_factorize().
    *
    * @return: struct containing lower triangular matrix, upper triangular matrix and the optional permutation matrix
    *          lower:          the L matrix is square, numRows x numRows
    *          upper:          the U matrix has the same dimensions as the input, numRows x numCols
    *          permutation:    the optional P matrix (if has value) is square, numRows x numRows
    *          pSign:          the optional sign of the permutation (+1/-1 for even/odd row swaps)
    */
    template <typename T>
    [[nodiscard]] LUFactorization factorizeLU_echelon(const Matrix<T>&);


    /**
    * Factorize the matrix A with dims (M X N) into a Q matrix with orthonormal columns (M x N) and an upper triangular matrix R (N X N) such that A = Q * R.
    *
    * @return:struct containing the orthogonal matrix Q and the upper triangular matrix R.
    *          Q:          matrix with orthonormal columns (all columns have norm 1 and are perpendicular to each other)
    *          R:          upper triangular matrix
    */
    template <typename T>
    [[nodiscard]] QRFactorization factorizeQR(const Matrix<T>&);


    /**
    * Returns the reduced-row-echelon form of the matrix.
    * All pivots are 1 and they are the only entries in their columns (columns of identity). Last numRows - R rows are zero (where R is the rank, i.e. the number of non-zero pivots).

    * NOTE : For non-singular square matrices the result is the identity matrix.
    *
    * @return: the reduced-row-echelon form of the matrix with dimensions numRows x numCols
    */
    template <typename T>
    [[nodiscard]] Matrix<long double> reduced_row_echelon(const Matrix<T>& );


    /**
    * Compute the inverse using Gramm-Schmidt algorithm.
    *
    * @return: the inverse matrix or a null optional when the matrix is singular
    */
    template <typename T>
    [[nodiscard]] std::optional<Matrix<long double>> inverse(const Matrix<T>&);


    /**
    *   Compute the left-inverse (leftInv) matrix of A such that leftInv * A = I.
    *   If A is MxN then leftInv is NXM and leftInv * A= I (NXN).
    *
    *   NOTE: Matrix A must have full-column rank. A nullopt is returned otherwise.
    *
    *   For square invertible matrices, the left inverse is also the right inverse.
    *
    * @return:   std::optional<Matrix<long double>> : the left inverse matrix
    */
    template <typename T>
    [[nodiscard]] std::optional<Matrix<long double>> left_inverse(const Matrix<T>&);


    /**
    *   Compute the right-inverse (rightInv) matrix of A such that A * rightInv = I.
    *   If A is MxN then rightInv is NXM and A * rightInv = I (MXM).
    *
    *   NOTE: Matrix A must have full-row rank. A nullopt is returned otherwise.
    *
    *   For square invertible matrices, the right inverse is also the left inverse.
    *
    * @return:   std::optional<Matrix<long double>> : the right inverse matrix
    * @return:
    */
    template <typename T>
    [[nodiscard]] std::optional<Matrix<long double>> right_inverse(const Matrix<T>&);

    /**
    * Compute the determinant as product of the pivots (O(n^3) assuming all entries are non-zero).
    *
    * @return: the determinant value
    */
    template <typename T>
    [[nodiscard]] long double determinant(const Matrix<T>&);


    /**
    * Returns the pivots info : value, rowIdx and colIdx for each pivot.
    *
    * @return: vector of pivots
    */
    template <typename T>
    [[nodiscard]] std::vector<Pivot> getPivots(const Matrix<T>&);


    /**
    * Compute the rank of the matrix
    *
    * @return: the rank value
    */
    template <typename T>
    [[nodiscard]] unsigned int rank(const Matrix<T>&);



    /**
    * Solve system of linear equations Ax = b and return the solution x
    *
    * @param: const Vector::Vector<U>: the "b" column vector
    * @return: std::optional<Solution> solution : a struct containing the following fields:
    *               bool                                            unique;                         // indicates if the system has unique solution.
                    std::optional<Vector<long double>>              uniqueSolution;                 // unique solution to Ax=b. It has a value only when the above "unique" bool is true, which happens in 2 scenarios:
                                                                                                    //      a) A is square invertible
                                                                                                    //      b) A has rank = numCols, rank < numRows and also the b-vector is in the column space of A.
                    std::optional<Vector<long double>>              particularSolution;             // Particular solution to Ax=b. It has a value only when the "unique" bool is false
                    std::optional<std::vector<Vector<long double>>> specialSolutions;               // STL vector with (numCols - rank) elements, solutions to Ax = 0. It has a value only when the "unique" bool is false.
                                                                                                    // Any linear combination of the special solutions which is added to the particular solution is also a solution.

                If the system is not solvable, a std::nullopt is returned. If the system is solvable there are 4 possible cases, depending on the matrix dimensions (numRows, numCols), its rank R and the vector b:
                a) R = numRows and R = numCols     :   In this case the system has unique solution to ANY vector b.
                b) R < numRows and R = numCols     :   System has unique solution if b lies in the column space of A (it must satisfy (numRows - R) solvability conditions). It has no solutions otherwise.
                c) R = numRows and R < numCols     :   System has infinitely many solutions for ANY vector b ( numRows - R = 0 conditions). There will be (numCols - R) special solutions.
                d) R < numRows and R < numCols     :   System has infinitely many solutions if b lies in the column space of A (it must satisfy (numRows - R) solvability conditions) and no solutions otherwise. If system is compatible there will be (numCols - R) special solutions.

     * ----------- NOTE -----------
     * If the "unique" flag is false the Solution will contain one particular solution Xparticular and (numCols - rank) special solutions Xspecial_i.
     * In this case the complete solution is Xcomplete = Xparticular + sum( lambda_i * Xspecial_i), with lambda_i ANY real number.
     * in other words, ANY linear combination of the special solutions added to the particular solution is also a solution.
    */
    template<typename T, typename U>
    [[nodiscard]] std::optional<Solution> solve(const Matrix<T>&, const Vector::Vector<U>&);


    /**
    * Solve system of linear equations Lc = b and return the solution c.
    * The matrix must be lower triangular !
    *
    * @param: const Vector::Vector<U>: the "b" column vector
    * @return: Vector::Vector<long double>: the solution c such that Lc=b.
    */
    template<typename T, typename U>
    [[nodiscard]] Vector::Vector<long double> solveLowerTriangular(const Matrix<T>&, const Vector::Vector<U>&);


    /**
    * Solve system of linear equations Ux=c and return the solution x.
    * The matrix must be upper triangular !
    *
    * @param: const Vector::Vector<U>: the "c" column vector
    * @return: Vector::Vector<long double>: the solution x such that Ux=c.
    */
    template<typename T, typename U>
    [[nodiscard]] Vector::Vector<long double> solveUpperTriangular(const Matrix<T>&, const Vector::Vector<U>&);


    /**
    * Find x that minimizes the error || b - A*x ||.
    * NOTE_1 : the matrix A must have full-column rank (all columns linear independent), A nullopt is returned otherwise.
    * NOTE_2 : if b vector is in the column space of A then the best estimate will match the output of A.solve(b) (and the error will be zero).
    *
    * @param: const Vector::Vector<U>: the "b" column vector
    * @return: FitLLSQ struct containing:
    *       Vector::Vector<long double> : the projection x of the b vector onto the column space of matrix A
    *       longDouble                  : the error || b - A*x ||
    */
    template<typename T, typename U>
    [[nodiscard]] std::optional<FitLLSQ> fit_LLSQ(const Matrix<T>&, const Vector::Vector<U>&);
}

#endif //LINEARALGEBRATOOLBOX_MATRIXHELPERS_HPP
