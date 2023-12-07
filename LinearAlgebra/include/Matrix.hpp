//
// Created by dorian on 03.11.2023.
// stoicadorian@gmail.com
//
#ifndef MATRIX_HPP
#define MATRIX_HPP

#pragma once

#include <Vector.hpp>
#include <vector>

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

    //Binary arithmetic
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;

    Matrix operator*(const Matrix& other) const;    //NOTE: this is element-wise matrix multiplication !!!
    Matrix operator/(const Matrix& other) const;

    //In-place operations with another Matrix
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);        //NOTE: this is element-wise matrix multiplication !!!
    Matrix& operator/=(const Matrix& other);

    //Broadcasters
    Matrix operator+    (T val) const;
    Matrix operator-    (T val) const;
    Matrix operator*    (T val) const;
    Matrix operator/    (T val) const;
    Matrix& operator+=  (T val);
    Matrix& operator-=  (T val);
    Matrix& operator*=  (T val);
    Matrix& operator/=  (T val);

    Matrix transpose()  const;

    //Get and set rows
    Vector<T> getRow(unsigned int) const;

    void setRow(const std::vector<T>&,  unsigned int);
    void setRow(const Vector<T>&,       unsigned int);

    Matrix identity(unsigned int) const;

    // Matrix multiplication
    Matrix multiply(const Matrix& other) const;

    // LU decomposition
    struct LUDecompositionResult
    {
        Matrix lower;
        Matrix upper;
    };
    LUDecompositionResult LU() const;

private:
    unsigned int numRows;
    unsigned int numCols;
    std::vector<T> data;
};

// Non-member functions that allow writing code with the following syntax:
// result = 2 + myMatrix;
template<typename T>
Matrix<T> operator+(T val, const Matrix<T>&);

// result = 2 * myMatrix;
template<typename T>
Matrix<T> operator*(T val,  const Matrix<T>&);


//Other helper functions

#endif //MATRIX_HPP