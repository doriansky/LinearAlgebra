//
// Created by dorian on 03.11.2023.
// stoicadorian@gmail.com
//
#ifndef MATRIX_HPP
#define MATRIX_HPP

#pragma once

#include <Vector.hpp>
#include <optional>
#include <vector>

namespace LinearAlgebra::Matrix
{
    //Forward declarations
    struct LUFactorization;
    struct Pivot;
    struct Solution;

    template <typename T>
    class Matrix
    {

    public:
        Matrix()    = delete;
        ~Matrix()   = default;

        explicit Matrix(unsigned int, unsigned int);
        explicit Matrix(const std::vector<T>&, unsigned int, unsigned int);

        //Copy and move constructor
        Matrix(const Matrix&);
        Matrix(Matrix&&) noexcept;

        //Copy assignment and move assignment
        Matrix& operator=(const Matrix& other);
        Matrix& operator=(Matrix&& other) noexcept;

        //Getters for num rows and num cols
        [[nodiscard]] unsigned int rows() const;
        [[nodiscard]] unsigned int cols() const;

        //Get single entry
        const T&    operator()  (unsigned int rowIdx, unsigned int colIdx) const;
        //Set single entry
        T&          operator()  (unsigned int rowIdx, unsigned int colIdx);

        /**
        * Provide read-only access to the underlying matrix data container.
        *
        * @return: typename std::vector<T>::const_iterator
        */
        [[nodiscard]] typename std::vector<T>::const_iterator begin() const;
        [[nodiscard]] typename std::vector<T>::const_iterator end() const;


        /**
        * Operators for matrix arithmetic : addition, subtraction, multiplication and division.
        * The two matrices can have different types.
        *
        * @param: const Matrix<U>& : the other matrix
        * @return: Matrix<typename std::common_type<T,U>::type>: the result of the +,-,* or / operation
        */
        template<class U>
        Matrix<typename std::common_type<T,U>::type> operator+(const Matrix<U>& other) const;

        template<class U>
        Matrix<typename std::common_type<T,U>::type> operator-(const Matrix<U>& other) const;

        template<class U>
        Matrix<typename std::common_type<T,U>::type> operator*(const Matrix<U>& other) const;    //NOTE: this is element-wise matrix multiplication !!!

        template<class U>
        Matrix<typename std::common_type<T,U>::type> operator/(const Matrix<U>& other) const;

        /**
        * Operators for in-place matrix arithmetic : addition, subtraction, multiplication and division.
        * The two matrices must have the same type !
        *
        * @param: const Matrix& : the other matrix
        * @return: Matrix: the result of the +,-,* or / operation
        */
        Matrix& operator+=(const Matrix& other);
        Matrix& operator-=(const Matrix& other);
        Matrix& operator*=(const Matrix& other);        //NOTE: this is element-wise matrix multiplication !!!
        Matrix& operator/=(const Matrix& other);

        /**
        * Scalar broadcasters : addition, subtraction, multiplication and division.
        *
        * @param: U : the scalar value
        * @return: Matrix<typename std::common_type<T,U>::type>: the result of broadcasting the scalar to the matrix elements
        */
        template<class U>
        Matrix<typename std::common_type<T,U>::type> operator+    (U val) const;

        template<class U>
        Matrix<typename std::common_type<T,U>::type> operator-    (U val) const;

        template<class U>
        Matrix<typename std::common_type<T,U>::type> operator*    (U val) const;

        template<class U>
        Matrix<typename std::common_type<T,U>::type> operator/    (U val) const;

        /**
        * In-place Scalar broadcasters : addition, subtraction, multiplication and division
        * Matrix and scalar must have the same type !
        *
        * @param: T : the scalar value
        * @return: Matrix: the result of broadcasting the scalar to the matrix elements
        */
        Matrix& operator+=  (T val);
        Matrix& operator-=  (T val);
        Matrix& operator*=  (T val);
        Matrix& operator/=  (T val);


        /**
        * Perform matrix-vector multiplication and return the resulting vector
        *
        * @param: Vector<U> : the vector x
        * @return: Vector<typename std::common_type<T,U>::type>:  the result of Ax
        */
        template<class U>
        Vector::Vector<typename std::common_type<T,U>::type> operator*(const Vector::Vector<U>& other) const;


        /**
        * Transpose the matrix
        *
        * @return: Matrix: the transposed matrix.
        */
        [[nodiscard]] Matrix transpose() const;


        /**
        * Get matrix row.
        *
        * @param: unsigned int : row index
        * @return: Vector<T>:
        */
        [[nodiscard]] Vector::Vector<T> getRow(unsigned int) const;


        /**
        * Set matrix row.
        *
        * @param: std::vector<T>: the row to be set. Its size must match the number of columns in the matrix.
        * @param: unsigned int: row index
        */
        void setRow(const std::vector<T>&,  unsigned int);


        /**
        * Set matrix row.
        *
        * @param: Vector<T>: the row to be set. Its dimension must match the number of columns in the matrix.
        * @param: unsigned int: row index
        */
        void setRow(const Vector::Vector<T>&,       unsigned int);


        /**
        * Swap matrix rows
        *
        * @param: unsigned int rowIndex
        * @param: unsigned int otherRowIndex
        */
        void swapRows(unsigned int, unsigned int);


        /**
        * Swap row entries below main diagonal (diagonal elements excluded).
        *
        * @param: unsigned int rowIndex
        * @param: unsigned int otherRowIndex
        */
        void swapBelowDiagonal(unsigned int, unsigned int);


        /**
         * Matrix multiplication. The 2 matrices can have different types.
         * A * B is constructed as linear combinations of the rows of B. More precisely, row i of A*B is the linear
         * combination of the rows of B with coefficients obtained from the i-th row of A
        *
        * @param: const Matrix<U>: the other matrix
        * @return: Matrix<typename std::common_type<T,U>::type> : the result of multiplication
        */
        template<class U>
        [[nodiscard]] Matrix<typename std::common_type<T,U>::type> multiply(const Matrix<U>& other) const;


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
        */
        [[nodiscard]] LUFactorization factorizeLU() const;


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
        */
        [[nodiscard]] LUFactorization factorizeLU_echelon() const;


        /**
        * Returns the reduced-row-echelon form of the matrix. 
        * All pivots are 1 and they are the only entries in their columns (columns of identity). Last numRows - R rows are zero (where R is the rank, i.e. the number of non-zero pivots).
        
        * NOTE : For non-singular square matrices the result is the identity matrix.
        *
        * @return: the reduced-row-echelon form of the matrix with dimensions numRows x numCols
        */
        [[nodiscard]] Matrix<long double> reduced_row_echelon() const;


        /**
        * Compute the inverse using Gramm-Schmidt algorithm.
        *
        * @return: the inverse matrix or a null optional when the matrix is singular
        */
        [[nodiscard]] std::optional<Matrix<long double>> inverse() const;


        /**
        * Compute the determinant as product of the pivots (O(n^3) assuming all entries are non-zero).
        *
        * @return: the determinant value
        */
        [[nodiscard]] long double determinant() const;


        /**
        * Returns the pivots info : value, rowIdx and colIdx for each pivot.
        *
        * @return: vector of pivots
        */
        [[nodiscard]] std::vector<Pivot> getPivots() const;


        /**
        * Compute the rank of the matrix
        *
        * @return: the rank value
        */
        [[nodiscard]] unsigned int rank() const;


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
        template<class U>
        [[nodiscard]] std::optional<Solution> solve(const Vector::Vector<U>&) const;


        /**
        * Solve system of linear equations Lc = b and return the solution c.
        * The matrix must be lower triangular !
        *
        * @param: const Vector::Vector<U>: the "b" column vector
        * @return: Vector::Vector<long double>: the solution c such that Lc=b.
        */
        template<class U>
        [[nodiscard]] Vector::Vector<long double> solveLowerTriangular(const Vector::Vector<U>&) const;


        /**
        * Solve system of linear equations Ux=c and return the solution x.
        * The matrix must be upper triangular !
        *
        * @param: const Vector::Vector<U>: the "c" column vector
        * @return: Vector::Vector<long double>: the solution x such that Ux=c.
        */
        template<class U>
        [[nodiscard]] Vector::Vector<long double> solveUpperTriangular(const Vector::Vector<U>&) const;

    private:
        unsigned int numRows;
        unsigned int numCols;
        std::vector<T> data;
    };

    struct LUFactorization
    {
        Matrix<long double>              lower;
        Matrix<long double>              upper;
        std::optional<Matrix<int>>       permutation;
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
    // Non-member functions
    // Operator+ that allows putting the scalar first : newMatrix = scalar + matrix
    template<typename T, typename U>
    Matrix<typename std::common_type<T,U>::type> operator+(T val, const Matrix<U>&);

    // Operator* that allows putting the scalar first : newMatrix = scalar * matrix
    template<typename T, typename U>
    Matrix<typename std::common_type<T,U>::type> operator*(T val,  const Matrix<U>&);

}   //namespace LinearAlgebra::Matrix


#endif //MATRIX_HPP