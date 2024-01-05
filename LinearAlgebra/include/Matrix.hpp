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

    struct LUFactorization;

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
        [[nodiscard]] Matrix transpose()  const;


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
         * Matrix multiplication. The 2 matrices can have different types
         * A * B is constructed as linear combinations of the rows of B. More precisely, row i of A*B is the linear
         * combination of the rows of B with coefficients obtained from the i-th row of A
        *
        * @param: const Matrix<U>: the other matrix
        * @return: Matrix<typename std::common_type<T,U>::type> : the result of multiplication
        */
        template<class U>
        [[nodiscard]] Matrix<typename std::common_type<T,U>::type> multiply(const Matrix<U>& other) const;


        /**
         * Solve system of linear equations Ax = b and return the solution x
         * Internally the matrix is decomposed into L and U and 2 linear triangular systems are solved : Lc=b and Ux=c.
        *
        * @param: const Vector::Vector<U>: the "b" column vector
        * @return: Vector::Vector<long double>: the solution x such that Ax=b
        */
        template<class U>
        [[nodiscard]] Vector::Vector<long double> solve(const Vector::Vector<U>&) const;


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


        /**
         * Factorize the matrix into Lower and Upper matrices (and an optional permutation matrix ) such that A = LU
         * or PA = LU when row exchanges are required.
        *
        * @return: struct containing lower triangular matrix, upper triangular matrix and the optional permutation matrix
        */
        [[nodiscard]] LUFactorization factorizeLU() const;


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

    // Non-member functions
    // Operator+ that allows putting the scalar first : newMatrix = scalar + matrix
    template<typename T, typename U>
    Matrix<typename std::common_type<T,U>::type> operator+(T val, const Matrix<U>&);

    // Operator* that allows putting the scalar first : newMatrix = scalar * matrix
    template<typename T, typename U>
    Matrix<typename std::common_type<T,U>::type> operator*(T val,  const Matrix<U>&);

}   //namespace LinearAlgebra::Matrix


#endif //MATRIX_HPP