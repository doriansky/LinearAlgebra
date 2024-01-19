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
         * Matrix multiplication. The 2 matrices can have different types.
         * A * B is constructed as linear combinations of the rows of B. More precisely, row i of A*B is the linear
         * combination of the rows of B with coefficients obtained from the i-th row of A
        *
        * @param: const Matrix<U>: the other matrix
        * @return: Matrix<typename std::common_type<T,U>::type> : the result of multiplication
        */
        template<class U>
        [[nodiscard]] Matrix<typename std::common_type<T,U>::type> multiply(const Matrix<U>& other) const;

    private:
        unsigned int numRows;
        unsigned int numCols;
        std::vector<T> data;
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