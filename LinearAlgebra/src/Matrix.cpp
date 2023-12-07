//
// Created by dorian on 03.11.2023.
// stoicadorian@gmail.com
//

#include "Matrix.hpp"

#include <algorithm>
#include <stdexcept>


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

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& other) const
{
    if (other.numRows != numRows || other.numCols != numCols)
        throw std::invalid_argument("Cannot add incompatible matrices !");

    Matrix res(numRows, numCols);
    std::transform(data.begin(), data.end(), other.data.begin(), res.data.begin(), std::plus<T>());
    return res;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix& other) const
{
    if (other.numRows != numRows || other.numCols != numCols)
        throw std::invalid_argument("Cannot subtract incompatible matrices !");

    Matrix res(numRows, numCols);
    std::transform(data.begin(), data.end(), other.data.begin(), res.data.begin(), std::minus<T>());
    return res;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix& other) const
{
    if (other.numRows != numRows || other.numCols != numCols)
        throw std::invalid_argument("Cannot perform element-wise multiplication. Incompatible matrices !");

    Matrix res(numRows, numCols);
    std::transform(data.begin(), data.end(), other.data.begin(), res.data.begin(), std::multiplies<T>());
    return res;
}

template<typename T>
Matrix<T> Matrix<T>::operator/(const Matrix& other) const
{
    if (other.numRows != numRows || other.numCols != numCols)
        throw std::invalid_argument("Cannot perform element-wise division. Incompatible matrices !");

    if (std::find(std::begin(other.data), std::end(other.data), static_cast<T>(0)) != std::end(other.data))
        throw std::invalid_argument("Divisor matrix contains zeros !");

    Matrix res(numRows, numCols);
    std::transform(data.begin(), data.end(), other.data.begin(), res.data.begin(), std::divides<T>());
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
Matrix<T> Matrix<T>::operator+(const T val) const
{
    Matrix res(numRows, numCols);
    std::transform(data.begin(), data.end(), res.data.begin(),
                   [&](const T v) {return v + val; } );
    return res;
}

//Non-member operator function
template<typename T>
Matrix<T> operator+(const T val, const Matrix<T>& matrix)
{
    return matrix.operator+(val);
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const T val) const
{
    Matrix res(numRows, numCols);
    std::transform(data.begin(), data.end(), res.data.begin(),
                   [&](const T v) {return v - val; } );
    return res;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const T val) const
{
    Matrix res(numRows, numCols);
    std::transform(data.begin(), data.end(), res.data.begin(),
                   [&](const T v) {return v * val; } );
    return res;
}

//Non-member operator function
template<typename T>
Matrix<T> operator*(const T val, const Matrix<T>& matrix)
{
    return matrix.operator*(val);
}

template<typename T>
Matrix<T> Matrix<T>::operator/(const T val) const
{
    if (val == 0)
        throw std::invalid_argument("Attempt to divide by zero");

    Matrix res(numRows, numCols);
    std::transform(data.begin(), data.end(), res.data.begin(),
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
Matrix<T> Matrix<T>::transpose() const
{
    Matrix<T> t(numCols, numRows);
    for (unsigned int rIdx = 0; rIdx<t.numRows; rIdx++)
        for (unsigned int cIdx = 0; cIdx<t.numCols; cIdx++)
            t(rIdx,cIdx) = operator()(cIdx, rIdx);

    return t;
}

template <typename T>
Vector<T> Matrix<T>::getRow(const unsigned int r) const
{
    if (r >= numRows)
        throw std::invalid_argument("Invalid row index !");

    const unsigned int startIdx = numCols * r;

    return Vector<T>({data.begin()+startIdx, data.begin() + startIdx + numCols});
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
void Matrix<T>::setRow(const Vector<T>& row, unsigned int r)
{
    if (r >= numRows)
        throw std::invalid_argument("Invalid row index !");

    if (row.dim() != numCols)
        throw std::invalid_argument("Incompatible row dimension !");

    const unsigned int startIdx = numCols * r;
    std::copy(row.begin(), row.end(), data.begin() + startIdx);
}

template <typename T>
Matrix<T> Matrix<T>::identity(unsigned int d) const
{
    Matrix<T> identity(d, d);
    for (unsigned int i = 0; i<d; i++)
        identity(i,i) = static_cast<T>(1);

    return identity;
}

template<typename T>
Matrix<T> Matrix<T>::multiply(const Matrix& other) const
{
    if (numCols != other.numRows)
        throw std::invalid_argument("Cannot perform matrix multiplication. Incompatible matrices !");

    Matrix result(numRows, other.numCols);

    //Option 1: make a copy of the other matrix and reshape it. Then do dot products
    const auto otherTransposed = other.transpose();

    for (unsigned int rIdx = 0; rIdx < numRows; rIdx++)
        for (unsigned int cIdx = 0; cIdx < otherTransposed.numRows; cIdx++)
        {
            auto a = getRow(rIdx);
            auto b = otherTransposed.getRow(cIdx);
            result(rIdx, cIdx) = getRow(rIdx).dot(otherTransposed.getRow(cIdx));
        }


    return result;
}

template <typename T>
typename Matrix<T>::LUDecompositionResult Matrix<T>::LU() const
{
   // if (numRows != numCols)
   //     throw std::runtime_error("Matrix is not square");

    const unsigned int dim = numRows;
    //TODO lower and upper have to be double (always)
    //TODO permute rows if one of the pivots is zero
    auto upperMatrix = *this;
    auto lowerMatrix = identity(dim);

    for (unsigned i = 0; i<dim-1; i++)
    {
        Vector<T> currRow   = upperMatrix.getRow(i);
        const T pivot       = currRow[i];

        for (unsigned int j=i+1; j<dim; j++)
        {
            Vector row      = upperMatrix.getRow(j);
            const T factor  = row[i] / pivot;
            row             -= currRow*factor;

            upperMatrix.setRow(row, j);
            lowerMatrix(j,i) = factor;
        }
    }

    return {lowerMatrix, upperMatrix};
}


/////////////////////////////////////////////////////////////////////////////////
template class Matrix<int>;
template class Matrix<float>;
template class Matrix<double>;

// Non-member operators
template class Matrix<int>      operator+(const int val,    const Matrix<int>&);
template class Matrix<float>    operator+(const float val,  const Matrix<float>&);
template class Matrix<double>   operator+(const double val, const Matrix<double>&);

template class Matrix<int>      operator*(const int val,    const Matrix<int>&);
template class Matrix<float>    operator*(const float val,  const Matrix<float>&);
template class Matrix<double>   operator*(const double val, const Matrix<double>&);
/////////////////////////////////////////////////////////////////////////////////