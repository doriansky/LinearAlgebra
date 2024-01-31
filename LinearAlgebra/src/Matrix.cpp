//
// Created by dorian on 03.11.2023.
// stoicadorian@gmail.com
//

#include "Matrix.hpp"
#include <algorithm>
#include <map>
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
    Matrix<std::complex<typename std::common_type<T,U>::type>> Matrix<T>::operator+(const Matrix<std::complex<U>>& other) const
    {
        if (other.rows() != numRows || other.cols() != numCols)
            throw std::invalid_argument("Cannot add incompatible matrices !");

        Matrix<std::complex<typename std::common_type<T,U>::type>> res(numRows, numCols);
        for (unsigned int r=0; r<numRows; r++)
            for (unsigned int c=0; c<numCols; c++)
                res(r,c) = std::complex<typename std::common_type<T,U>::type>(this->operator()(r,c) + other(r,c).real(), other(r,c).imag());

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
    Matrix<std::complex<typename std::common_type<T,U>::type>> Matrix<T>::operator-(const Matrix<std::complex<U>>& other) const
    {
        if (other.rows() != numRows || other.cols() != numCols)
            throw std::invalid_argument("Cannot add incompatible matrices !");

        Matrix<std::complex<typename std::common_type<T,U>::type>> res(numRows, numCols);
        for (unsigned int r=0; r<numRows; r++)
            for (unsigned int c=0; c<numCols; c++)
                res(r,c) = std::complex<typename std::common_type<T,U>::type>(this->operator()(r,c) - other(r,c).real(), -other(r,c).imag());

        return res;
    }

    template<typename T>
    template<typename U>
    Matrix<typename std::common_type<T,U>::type> Matrix<T>::operator*(const Matrix<U>& other) const
    {
        if (numCols != other.rows())
            throw std::invalid_argument("Cannot perform matrix multiplication. Incompatible matrices !");

        Matrix<typename std::common_type<T,U>::type> result(numRows, other.cols());

        for (unsigned int rIdx = 0; rIdx < numRows; rIdx++)
        {
            for (unsigned int cIdx = 0; cIdx < numCols; cIdx++)
            {
                const unsigned int startIdx =   cIdx * other.cols();
                const unsigned int endIdx   =   startIdx + other.cols();

                auto aij_times_row_j_of_B = Vector::Vector<typename std::common_type<T,U>::type>(other.cols());

                // Compute scalar-vector product :  A_ij * Row_j_of_B
                std::transform(other.begin() + startIdx, other.begin() + endIdx, &aij_times_row_j_of_B[0],
                               [&](const U v) {return v * this->operator()(rIdx, cIdx); } );

                // Contribute to the current linear combination of Row_i. Inject the result directly in the output matrix
                const unsigned int destinationStartIdx = result.cols() * rIdx;
                std::transform(result.begin() + destinationStartIdx, result.begin() + destinationStartIdx + result.cols(), aij_times_row_j_of_B.begin(),
                               &result(0,0) + destinationStartIdx, std::plus<typename std::common_type<T,U>::type>());
            }
        }

        return result;
    }

    template<typename T>
    template<typename U>
    Matrix<std::complex<typename std::common_type<T,U>::type>> Matrix<T>::operator*(const Matrix<std::complex<U>>& other) const
    {
        if (numCols != other.rows())
            throw std::invalid_argument("Cannot perform matrix multiplication. Incompatible matrices !");

        Matrix<std::complex<typename std::common_type<T,U>::type>> result(numRows, other.cols());

        for (unsigned int rIdx = 0; rIdx < numRows; rIdx++)
        {
            for (unsigned int cIdx = 0; cIdx < numCols; cIdx++)
            {
                const unsigned int startIdx =   cIdx * other.cols();
                auto aij_times_row_j_of_B = Vector::Vector<std::complex<typename std::common_type<T,U>::type>>(other.cols());

                // Compute scalar-vector product :  A_ij * Row_j_of_B
                for (unsigned i=0;i<other.cols();i++)
                {
                    auto& currEntry = *(other.begin()+startIdx+i);
                    aij_times_row_j_of_B[i] = std::complex<typename std::common_type<T,U>::type>(this->operator()(rIdx, cIdx)*currEntry.real(), this->operator()(rIdx, cIdx)*currEntry.imag());
                }

                // Contribute to the current linear combination of Row_i. Inject the result directly in the output matrix
                const unsigned int destinationStartIdx = result.cols() * rIdx;
                std::transform(result.begin() + destinationStartIdx, result.begin() + destinationStartIdx + result.cols(), aij_times_row_j_of_B.begin(),
                               &result(0,0) + destinationStartIdx, std::plus<std::complex<typename std::common_type<T,U>::type>>());
            }
        }

        return result;
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



    //////////////////////////////////////////////// COMPLEX MATRIX
    template <typename U>
    Matrix<std::complex<U>>::Matrix(const unsigned int r, const unsigned int c):
            numRows(r),
            numCols(c)
    {
        data = std::vector<std::complex<U>>(numRows*numCols);
    }

    template<typename U>
    Matrix<std::complex<U>>::Matrix(const std::vector<std::complex<U>>& inputData, unsigned int r, unsigned int c)
    {
        if (inputData.size() != r*c)
            throw std::runtime_error("Incompatible dimensions");

        numRows = r;
        numCols = c;
        data    = inputData;
    }

    template<typename U>
    unsigned int Matrix<std::complex<U>>::rows() const
    {
        return numRows;
    }

    template<typename U>
    unsigned int Matrix<std::complex<U>>::cols() const
    {
        return numCols;
    }

    template<typename U>
    const std::complex<U>& Matrix<std::complex<U>>::operator()(const unsigned int rowIdx, const unsigned int colIdx) const
    {
        if (rowIdx >= numRows || colIdx >= numCols)
            throw(std::invalid_argument("Invalid row or column index"));

        const auto idx = (colIdx) + numCols * rowIdx;
        return data[idx];
    }

    template<typename U>
    std::complex<U>& Matrix<std::complex<U>>::operator()(const unsigned int rowIdx, const unsigned int colIdx)
    {
        //Use Scott Meyers's trick and make this operator call the const version of operator(row,col)
        return const_cast<std::complex<U>&>(static_cast<const Matrix<std::complex<U>>&>(*this)(rowIdx, colIdx));
    }

    template <typename U>
    typename std::vector<std::complex<U>>::const_iterator Matrix<std::complex<U>>::begin() const
    {
        return data.cbegin();
    }

    template <typename U>
    typename std::vector<std::complex<U>>::const_iterator Matrix<std::complex<U>>::end() const
    {
        return data.cend();
    }

    template<typename U>
    template<typename V>
    Matrix<std::complex<typename std::common_type<U,V>::type>> Matrix<std::complex<U>>::operator+(const Matrix<V>& other) const
    {
        if (other.rows() != numRows || other.cols() != numCols)
            throw std::invalid_argument("Cannot add incompatible matrices !");

        Matrix<std::complex<typename std::common_type<U,V>::type>> res(numRows, numCols);
        for (unsigned int r=0; r<numRows; r++)
            for (unsigned int c=0; c<numCols; c++)
                res(r,c) = std::complex<typename std::common_type<U,V>::type>(this->operator()(r,c).real() + other(r,c), this->operator()(r,c).imag());

        return res;
    }


    template<typename U>
    template<typename V>
    Matrix<std::complex<typename std::common_type<U,V>::type>> Matrix<std::complex<U>>::operator+(const Matrix<std::complex<V>>& other) const
    {
        if (other.rows() != numRows || other.cols() != numCols)
            throw std::invalid_argument("Cannot add incompatible matrices !");

        Matrix<std::complex<typename std::common_type<U,V>::type>> res(numRows, numCols);
        for (unsigned int r=0; r<numRows; r++)
            for (unsigned int c=0; c<numCols; c++)
                res(r,c) = std::complex<typename std::common_type<U,V>::type>(this->operator()(r,c).real() + other(r,c).real(), this->operator()(r,c).imag() + other(r,c).imag());

        return res;
    }

    template<typename U>
    template<typename V>
    Matrix<std::complex<typename std::common_type<U,V>::type>> Matrix<std::complex<U>>::operator-(const Matrix<V>& other) const
    {
        if (other.rows() != numRows || other.cols() != numCols)
            throw std::invalid_argument("Cannot add incompatible matrices !");

        Matrix<std::complex<typename std::common_type<U,V>::type>> res(numRows, numCols);
        for (unsigned int r=0; r<numRows; r++)
            for (unsigned int c=0; c<numCols; c++)
                res(r,c) = std::complex<typename std::common_type<U,V>::type>(this->operator()(r,c).real() - other(r,c), this->operator()(r,c).imag());

        return res;
    }

    template<typename U>
    template<typename V>
    Matrix<std::complex<typename std::common_type<U,V>::type>> Matrix<std::complex<U>>::operator-(const Matrix<std::complex<V>>& other) const
    {
        if (other.rows() != numRows || other.cols() != numCols)
            throw std::invalid_argument("Cannot add incompatible matrices !");

        Matrix<std::complex<typename std::common_type<U,V>::type>> res(numRows, numCols);
        for (unsigned int r=0; r<numRows; r++)
            for (unsigned int c=0; c<numCols; c++)
                res(r,c) = std::complex<typename std::common_type<U,V>::type>(this->operator()(r,c).real() - other(r,c).real(), this->operator()(r,c).imag() - other(r,c).imag());

        return res;
    }

    template<typename U>
    Matrix<std::complex<U>>& Matrix<std::complex<U>>::operator+=(const Matrix<std::complex<U>>& other)
    {
        if (other.numRows != numRows || other.numCols != numCols)
            throw std::invalid_argument("Cannot add incompatible matrices !");

        std::transform(data.begin(), data.end(), other.data.begin(), data.begin(), std::plus<std::complex<U>>());
        return *this;
    }

    template<typename U>
    Matrix<std::complex<U>>& Matrix<std::complex<U>>::operator-=(const Matrix<std::complex<U>>& other)
    {
        if (other.numRows != numRows || other.numCols != numCols)
            throw std::invalid_argument("Cannot subtract incompatible matrices !");

        std::transform(data.begin(), data.end(), other.data.begin(), data.begin(), std::minus<std::complex<U>>());
        return *this;
    }

    template<typename U>
    template<typename V>
    Matrix<std::complex<typename std::common_type<U,V>::type>> Matrix<std::complex<U>>::operator*(const Matrix<V>& other) const
    {
        if (numCols != other.rows())
            throw std::invalid_argument("Cannot perform matrix multiplication. Incompatible matrices !");

        Matrix<std::complex<typename std::common_type<U,V>::type>> result(numRows, other.cols());

        for (unsigned int rIdx = 0; rIdx < numRows; rIdx++)
        {
            for (unsigned int cIdx = 0; cIdx < numCols; cIdx++)
            {
                const unsigned int startIdx =   cIdx * other.cols();
                auto aij_times_row_j_of_B = Vector::Vector<std::complex<typename std::common_type<U,V>::type>>(other.cols());

                // Compute scalar-vector product :  A_ij * Row_j_of_B
                for (unsigned i=0;i<other.cols();i++)
                {
                    auto& currEntry = *(other.begin()+startIdx+i);
                    aij_times_row_j_of_B[i] = std::complex<typename std::common_type<U,V>::type>(this->operator()(rIdx, cIdx).real()*currEntry, this->operator()(rIdx, cIdx).imag()*currEntry);
                }

                // Contribute to the current linear combination of Row_i. Inject the result directly in the output matrix
                const unsigned int destinationStartIdx = result.cols() * rIdx;
                std::transform(result.begin() + destinationStartIdx, result.begin() + destinationStartIdx + result.cols(), aij_times_row_j_of_B.begin(),
                               &result(0,0) + destinationStartIdx, std::plus<std::complex<typename std::common_type<U,V>::type>>());
            }
        }

        return result;
    }

    template<typename U>
    template<typename V>
    Matrix<std::complex<typename std::common_type<U,V>::type>> Matrix<std::complex<U>>::operator*(const Matrix<std::complex<V>>& other) const
    {
        if (numCols != other.rows())
            throw std::invalid_argument("Cannot perform matrix multiplication. Incompatible matrices !");

        Matrix<std::complex<typename std::common_type<U,V>::type>> result(numRows, other.cols());

        for (unsigned int rIdx = 0; rIdx < numRows; rIdx++)
        {
            for (unsigned int cIdx = 0; cIdx < numCols; cIdx++)
            {
                const unsigned int startIdx =   cIdx * other.cols();
                auto aij_times_row_j_of_B = Vector::Vector<std::complex<typename std::common_type<U,V>::type>>(other.cols());

                // Compute scalar-vector product :  A_ij * Row_j_of_B
                for (unsigned i=0;i<other.cols();i++)
                {
                    auto& currEntry = *(other.begin()+startIdx+i);
                    aij_times_row_j_of_B[i] = std::complex<typename std::common_type<U,V>::type>(this->operator()(rIdx, cIdx).real()*currEntry.real() - this->operator()(rIdx, cIdx).imag()*currEntry.imag(),
                                                                                                 this->operator()(rIdx, cIdx).real()*currEntry.imag() + this->operator()(rIdx, cIdx).imag()*currEntry.real());
                }

                // Contribute to the current linear combination of Row_i. Inject the result directly in the output matrix
                const unsigned int destinationStartIdx = result.cols() * rIdx;
                std::transform(result.begin() + destinationStartIdx, result.begin() + destinationStartIdx + result.cols(), aij_times_row_j_of_B.begin(),
                               &result(0,0) + destinationStartIdx, std::plus<std::complex<typename std::common_type<U,V>::type>>());
            }
        }

        return result;
    }
    //////////////////////////////////////////////// END COMPLEX MATRIX
#include "MatrixExplicitTemplateInstantiations.hpp"
}   //namespace LinearAlgebra::Matrix
