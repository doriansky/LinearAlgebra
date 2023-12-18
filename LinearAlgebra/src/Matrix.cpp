//
// Created by dorian on 03.11.2023.
// stoicadorian@gmail.com
//

#include "Matrix.hpp"

#include <algorithm>
#include <numeric>
#include <stdexcept>

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

    template <typename T>
    Matrix<T> identity(unsigned int d)
    {
        Matrix<T> identity(d, d);
        for (unsigned int i = 0; i<d; i++)
            identity(i,i) = static_cast<T>(1);

        return identity;
    }

    template<typename T>
    template<typename U>
    Matrix<typename std::common_type<T,U>::type> Matrix<T>::multiply(const Matrix<U>& other) const
    {
        if (numCols != other.rows())
            throw std::invalid_argument("Cannot perform matrix multiplication. Incompatible matrices !");

        Matrix<typename std::common_type<T,U>::type> result(numRows, other.cols());

        // A * B is constructed as linear combinations of the rows of B.
        // More precisely, row i of A*B is the linear combination of the rows of B with coefficients obtained from the i-th row of A
        for (unsigned int rIdx = 0; rIdx < numRows; rIdx++)
        {
            for (unsigned int cIdx = 0; cIdx < numCols; cIdx++)
            {
                const unsigned int startIdx =   cIdx * other.cols();
                const unsigned int endIdx   =   startIdx + other.cols();

                auto a_i_j__times_row_j_of_B = Vector::Vector<typename std::common_type<T,U>::type>(other.cols());

                // Compute scalar-vector product :  A_ij * Row_j_of_B
                std::transform(other.begin() + startIdx, other.begin() + endIdx, &a_i_j__times_row_j_of_B[0],
                               [&](const U v) {return v * this->operator()(rIdx, cIdx); } );

                // Contribute to the current linear combination of Row_i. Inject the result directly in the output matrix
                const unsigned int destinationStartIdx = result.cols() * rIdx;
                std::transform(result.begin() + destinationStartIdx, result.begin() + destinationStartIdx + result.cols(), a_i_j__times_row_j_of_B.begin(),
                               &result(0,0) + destinationStartIdx, std::plus<typename std::common_type<T,U>::type>());
            }
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
        auto lowerMatrix = identity<T>(dim);

        for (unsigned i = 0; i<dim-1; i++)
        {
            Vector::Vector<T> currRow   = upperMatrix.getRow(i);
            const T pivot       = currRow[i];

            for (unsigned int j=i+1; j<dim; j++)
            {
                Vector::Vector row      = upperMatrix.getRow(j);
                const T factor  = row[i] / pivot;
                row             -= currRow*factor;

                upperMatrix.setRow(row, j);
                lowerMatrix(j,i) = factor;
            }
        }

        return {lowerMatrix, upperMatrix};
    }

    template class Matrix<int>;
    template class Matrix<float>;
    template class Matrix<double>;

    //operator+
    template Matrix<std::common_type<int, int>::type> Matrix<int>::operator+<int>(Matrix<int> const&) const;
    template Matrix<std::common_type<int, float>::type> Matrix<int>::operator+<float>(Matrix<float> const&) const;
    template Matrix<std::common_type<int, double>::type> Matrix<int>::operator+<double>(Matrix<double> const&) const;

    template Matrix<std::common_type<float, float>::type> Matrix<float>::operator+<float>(Matrix<float> const&) const;
    template Matrix<std::common_type<float, int>::type> Matrix<float>::operator+<int>(Matrix<int> const&) const;
    template Matrix<std::common_type<float, double>::type> Matrix<float>::operator+<double>(Matrix<double> const&) const;

    template Matrix<std::common_type<double, int>::type> Matrix<double>::operator+<int>(Matrix<int> const&) const;
    template Matrix<std::common_type<double, float>::type> Matrix<double>::operator+<float>(Matrix<float> const&) const;
    template Matrix<std::common_type<double, double>::type> Matrix<double>::operator+<double>(Matrix<double> const&) const;

    //operator-
    template Matrix<std::common_type<int, int>::type> Matrix<int>::operator-<int>(Matrix<int> const&) const;
    template Matrix<std::common_type<int, float>::type> Matrix<int>::operator-<float>(Matrix<float> const&) const;
    template Matrix<std::common_type<int, double>::type> Matrix<int>::operator-<double>(Matrix<double> const&) const;

    template Matrix<std::common_type<float, int>::type> Matrix<float>::operator-<int>(Matrix<int> const&) const;
    template Matrix<std::common_type<float, float>::type> Matrix<float>::operator-<float>(Matrix<float> const&) const;
    template Matrix<std::common_type<float, double>::type> Matrix<float>::operator-<double>(Matrix<double> const&) const;

    template Matrix<std::common_type<double, int>::type> Matrix<double>::operator-<int>(Matrix<int> const&) const;
    template Matrix<std::common_type<double, float>::type> Matrix<double>::operator-<float>(Matrix<float> const&) const;
    template Matrix<std::common_type<double, double>::type> Matrix<double>::operator-<double>(Matrix<double> const&) const;

    //operator*
    template Matrix<std::common_type<int, int>::type> Matrix<int>::operator*<int>(Matrix<int> const&) const;
    template Matrix<std::common_type<int, float>::type> Matrix<int>::operator*<float>(Matrix<float> const&) const;
    template Matrix<std::common_type<int, double>::type> Matrix<int>::operator*<double>(Matrix<double> const&) const;

    template Matrix<std::common_type<float, int>::type> Matrix<float>::operator*<int>(Matrix<int> const&) const;
    template Matrix<std::common_type<float, float>::type> Matrix<float>::operator*<float>(Matrix<float> const&) const;
    template Matrix<std::common_type<float, double>::type> Matrix<float>::operator*<double>(Matrix<double> const&) const;

    template Matrix<std::common_type<double, int>::type> Matrix<double>::operator*<int>(Matrix<int> const&) const;
    template Matrix<std::common_type<double, float>::type> Matrix<double>::operator*<float>(Matrix<float> const&) const;
    template Matrix<std::common_type<double, double>::type> Matrix<double>::operator*<double>(Matrix<double> const&) const;

    //operator/
    template Matrix<std::common_type<int, int>::type> Matrix<int>::operator/<int>(Matrix<int> const&) const;
    template Matrix<std::common_type<int, float>::type> Matrix<int>::operator/<float>(Matrix<float> const&) const;
    template Matrix<std::common_type<int, double>::type> Matrix<int>::operator/<double>(Matrix<double> const&) const;

    template Matrix<std::common_type<float, int>::type> Matrix<float>::operator/<int>(Matrix<int> const&) const;
    template Matrix<std::common_type<float, float>::type> Matrix<float>::operator/<float>(Matrix<float> const&) const;
    template Matrix<std::common_type<float, double>::type> Matrix<float>::operator/<double>(Matrix<double> const&) const;

    template Matrix<std::common_type<double, int>::type> Matrix<double>::operator/<int>(Matrix<int> const&) const;
    template Matrix<std::common_type<double, float>::type> Matrix<double>::operator/<float>(Matrix<float> const&) const;
    template Matrix<std::common_type<double, double>::type> Matrix<double>::operator/<double>(Matrix<double> const&) const;

    // Addition broadcasters
    template Matrix<std::common_type<int, int>::type> Matrix<int>::operator+<int>(int) const;
    template Matrix<std::common_type<int, float>::type> Matrix<int>::operator+<float>(float) const;
    template Matrix<std::common_type<int, double>::type> Matrix<int>::operator+<double>(double) const;

    template Matrix<std::common_type<float, int>::type> Matrix<float>::operator+<int>(int) const;
    template Matrix<std::common_type<float, float>::type> Matrix<float>::operator+<float>(float) const;
    template Matrix<std::common_type<float, double>::type> Matrix<float>::operator+<double>(double) const;

    template Matrix<std::common_type<double, int>::type> Matrix<double>::operator+<int>(int) const;
    template Matrix<std::common_type<double, float>::type> Matrix<double>::operator+<float>(float) const;
    template Matrix<std::common_type<double, double>::type> Matrix<double>::operator+<double>(double) const;

    //Non-member addition broadcasters (allow doing newMatrix = scalar + matrix)
    template Matrix<std::common_type<int, int>::type>       operator+(const int val,    const Matrix<int>&);
    template Matrix<std::common_type<int, float>::type>     operator+(const int val,    const Matrix<float>&);
    template Matrix<std::common_type<int, double>::type>    operator+(const int val,    const Matrix<double>&);

    template Matrix<std::common_type<float, int>::type>       operator+(const float val,    const Matrix<int>&);
    template Matrix<std::common_type<float, float>::type>     operator+(const float val,    const Matrix<float>&);
    template Matrix<std::common_type<float, double>::type>    operator+(const float val,    const Matrix<double>&);

    template Matrix<std::common_type<double, int>::type>       operator+(const double val,    const Matrix<int>&);
    template Matrix<std::common_type<double, float>::type>     operator+(const double val,    const Matrix<float>&);
    template Matrix<std::common_type<double, double>::type>    operator+(const double val,    const Matrix<double>&);

    //Subtraction broadcasters
    template Matrix<std::common_type<int, int>::type> Matrix<int>::operator-<int>(int) const;
    template Matrix<std::common_type<int, float>::type> Matrix<int>::operator-<float>(float) const;
    template Matrix<std::common_type<int, double>::type> Matrix<int>::operator-<double>(double) const;

    template Matrix<std::common_type<float, int>::type> Matrix<float>::operator-<int>(int) const;
    template Matrix<std::common_type<float, float>::type> Matrix<float>::operator-<float>(float) const;
    template Matrix<std::common_type<float, double>::type> Matrix<float>::operator-<double>(double) const;

    template Matrix<std::common_type<double, int>::type> Matrix<double>::operator-<int>(int) const;
    template Matrix<std::common_type<double, float>::type> Matrix<double>::operator-<float>(float) const;
    template Matrix<std::common_type<double, double>::type> Matrix<double>::operator-<double>(double) const;

    //Multiplication broadcasters
    template Matrix<std::common_type<int, int>::type> Matrix<int>::operator*<int>(int) const;
    template Matrix<std::common_type<int, float>::type> Matrix<int>::operator*<float>(float) const;
    template Matrix<std::common_type<int, double>::type> Matrix<int>::operator*<double>(double) const;

    template Matrix<std::common_type<float, int>::type> Matrix<float>::operator*<int>(int) const;
    template Matrix<std::common_type<float, float>::type> Matrix<float>::operator*<float>(float) const;
    template Matrix<std::common_type<float, double>::type> Matrix<float>::operator*<double>(double) const;

    template Matrix<std::common_type<double, int>::type> Matrix<double>::operator*<int>(int) const;
    template Matrix<std::common_type<double, float>::type> Matrix<double>::operator*<float>(float) const;
    template Matrix<std::common_type<double, double>::type> Matrix<double>::operator*<double>(double) const;

    //Non-member multiplication broadcasters (allow doing newMatrix = scalar 8 matrix)
    template Matrix<std::common_type<int, int>::type>       operator*(const int val,    const Matrix<int>&);
    template Matrix<std::common_type<int, float>::type>     operator*(const int val,    const Matrix<float>&);
    template Matrix<std::common_type<int, double>::type>    operator*(const int val,    const Matrix<double>&);

    template Matrix<std::common_type<float, int>::type>       operator*(const float val,    const Matrix<int>&);
    template Matrix<std::common_type<float, float>::type>     operator*(const float val,    const Matrix<float>&);
    template Matrix<std::common_type<float, double>::type>    operator*(const float val,    const Matrix<double>&);

    template Matrix<std::common_type<double, int>::type>       operator*(const double val,    const Matrix<int>&);
    template Matrix<std::common_type<double, float>::type>     operator*(const double val,    const Matrix<float>&);
    template Matrix<std::common_type<double, double>::type>    operator*(const double val,    const Matrix<double>&);

    //Division broadcasters
    template Matrix<std::common_type<int, int>::type> Matrix<int>::operator/<int>(int) const;
    template Matrix<std::common_type<int, float>::type> Matrix<int>::operator/<float>(float) const;
    template Matrix<std::common_type<int, double>::type> Matrix<int>::operator/<double>(double) const;

    template Matrix<std::common_type<float, int>::type> Matrix<float>::operator/<int>(int) const;
    template Matrix<std::common_type<float, float>::type> Matrix<float>::operator/<float>(float) const;
    template Matrix<std::common_type<float, double>::type> Matrix<float>::operator/<double>(double) const;

    template Matrix<std::common_type<double, int>::type> Matrix<double>::operator/<int>(int) const;
    template Matrix<std::common_type<double, float>::type> Matrix<double>::operator/<float>(float) const;
    template Matrix<std::common_type<double, double>::type> Matrix<double>::operator/<double>(double) const;


    // Matrix-Matrix multiplication
    template Matrix<std::common_type<int, int>::type> Matrix<int>::multiply<int>(Matrix<int> const&) const;
    template Matrix<std::common_type<int, float>::type> Matrix<int>::multiply<float>(Matrix<float> const&) const;
    template Matrix<std::common_type<int, double>::type> Matrix<int>::multiply<double>(Matrix<double> const&) const;

    template Matrix<std::common_type<float, float>::type> Matrix<float>::multiply<float>(Matrix<float> const&) const;
    template Matrix<std::common_type<float, int>::type> Matrix<float>::multiply<int>(Matrix<int> const&) const;
    template Matrix<std::common_type<float, double>::type> Matrix<float>::multiply<double>(Matrix<double> const&) const;

    template Matrix<std::common_type<double, int>::type> Matrix<double>::multiply<int>(Matrix<int> const&) const;
    template Matrix<std::common_type<double, float>::type> Matrix<double>::multiply<float>(Matrix<float> const&) const;
    template Matrix<std::common_type<double, double>::type> Matrix<double>::multiply<double>(Matrix<double> const&) const;

    //operator* for Matrix-Vector multiplication
    template Vector::Vector<std::common_type<int, int>::type> Matrix<int>::operator*<int>(Vector::Vector<int> const&) const;
    template Vector::Vector<std::common_type<int, float>::type> Matrix<int>::operator*<float>(Vector::Vector<float> const&) const;
    template Vector::Vector<std::common_type<int, double>::type> Matrix<int>::operator*<double>(Vector::Vector<double> const&) const;

    template Vector::Vector<std::common_type<float, int>::type> Matrix<float>::operator*<int>(Vector::Vector<int> const&) const;
    template Vector::Vector<std::common_type<float, float>::type> Matrix<float>::operator*<float>(Vector::Vector<float> const&) const;
    template Vector::Vector<std::common_type<float, double>::type> Matrix<float>::operator*<double>(Vector::Vector<double> const&) const;

    template Vector::Vector<std::common_type<double, int>::type> Matrix<double>::operator*<int>(Vector::Vector<int> const&) const;
    template Vector::Vector<std::common_type<double, float>::type> Matrix<double>::operator*<float>(Vector::Vector<float> const&) const;
    template Vector::Vector<std::common_type<double, double>::type> Matrix<double>::operator*<double>(Vector::Vector<double> const&) const;

    // Identity function
    template Matrix<int> identity(unsigned int);
    template Matrix<float> identity(unsigned int);
    template Matrix<double> identity(unsigned int);

}   //namespace LinearAlgebra::Matrix