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

    struct LUDecompositionResult;

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

        [[nodiscard]] typename std::vector<T>::const_iterator begin() const;
        [[nodiscard]] typename std::vector<T>::const_iterator end() const;


        //Binary arithmetic
        template<class U>
        Matrix<typename std::common_type<T,U>::type> operator+(const Matrix<U>& other) const;

        template<class U>
        Matrix<typename std::common_type<T,U>::type> operator-(const Matrix<U>& other) const;

        template<class U>
        Matrix<typename std::common_type<T,U>::type> operator*(const Matrix<U>& other) const;    //NOTE: this is element-wise matrix multiplication !!!

        template<class U>
        Matrix<typename std::common_type<T,U>::type> operator/(const Matrix<U>& other) const;

        //In-place operations with another Matrix  (OF THE SAME TYPE !)
        Matrix& operator+=(const Matrix& other);
        Matrix& operator-=(const Matrix& other);
        Matrix& operator*=(const Matrix& other);        //NOTE: this is element-wise matrix multiplication !!!
        Matrix& operator/=(const Matrix& other);

        //Broadcasters
        template<class U>
        Matrix<typename std::common_type<T,U>::type> operator+    (U val) const;

        template<class U>
        Matrix<typename std::common_type<T,U>::type> operator-    (U val) const;

        template<class U>
        Matrix<typename std::common_type<T,U>::type> operator*    (U val) const;

        template<class U>
        Matrix<typename std::common_type<T,U>::type> operator/    (U val) const;

        // In-place broadcasters (scalar must have the same type !)
        Matrix& operator+=  (T val);
        Matrix& operator-=  (T val);
        Matrix& operator*=  (T val);
        Matrix& operator/=  (T val);

        //Matrix-vector multiplication
        template<class U>
        Vector::Vector<typename std::common_type<T,U>::type> operator*(const Vector::Vector<U>& other) const;

        [[nodiscard]] Matrix transpose()  const;

        //Get and set rows
        [[nodiscard]] Vector::Vector<T> getRow(unsigned int) const;

        void setRow(const std::vector<T>&,  unsigned int);
        void setRow(const Vector::Vector<T>&,       unsigned int);

        void swapRows(unsigned int, unsigned int);

        // Matrix multiplication
        template<class U>
        [[nodiscard]] Matrix<typename std::common_type<T,U>::type> multiply(const Matrix<U>& other) const;

        // Solve system of linear equations Ax = b
        // Matrix is decomposed into L and U and then 2 triangular systems are solved: Lc=b and Ux=b.
        template<class U>
        [[nodiscard]] Vector::Vector<double> solve(const Vector::Vector<U>&) const;

        // Solve system of linear equations Lc = b
        // Matrix is assumed to be lower triangular, results will not be correct otherwise.
        template<class U>
        [[nodiscard]] Vector::Vector<double> solveLowerTriangular(const Vector::Vector<U>&) const;

        // Solve system of linear equations Ux=c
        // Matrix is assumed to be upper triangular, results will not be correct otherwise.
        template<class U>
        [[nodiscard]] Vector::Vector<double> solveUpperTriangular(const Vector::Vector<U>&) const;

        // LU decomposition
        [[nodiscard]] LUDecompositionResult LU() const;

        // Swap row entries below diagonal (diagonal elements excluded)
        void swapBelowDiagonal(unsigned int, unsigned int);

    private:
        unsigned int numRows;
        unsigned int numCols;
        std::vector<T> data;
    };

    struct LUDecompositionResult
    {
        Matrix<double>              lower;
        Matrix<double>              upper;
        std::optional<Matrix<int>>  permutation;
    };

    // Non-member functions
    // Operator+ that allows putting the scalar first : newMatrix = scalar + matrix
    template<typename T, typename U>
    Matrix<typename std::common_type<T,U>::type> operator+(T val, const Matrix<U>&);

    // Operator* that allows putting the scalar first : newMatrix = scalar * matrix
    template<typename T, typename U>
    Matrix<typename std::common_type<T,U>::type> operator*(T val,  const Matrix<U>&);

    // Returns the identity matrix with specified dim
    template <typename T>
    Matrix<T> identity(unsigned int);

    //  Search for first non-zero entry below the current element (that is, in the same column).
    //  Used internally on the upper matrix which is always double, therefore only double spec.
    std::optional<unsigned int> findNonZeroPivot(const Matrix<double>& mat, unsigned int, unsigned int);

}   //namespace LinearAlgebra::Matrix


#endif //MATRIX_HPP