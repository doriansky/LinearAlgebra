//
// Created by dorian on 03.11.2023.
// stoicadorian@gmail.com
//

#include "Vector.hpp"

#include <algorithm>
#include <numeric>
#include <stdexcept>


template <typename T>
Vector<T>::Vector(const unsigned int dim)
{
    data = std::vector<T>(dim);
}

template<typename T>
Vector<T>::Vector(const std::vector<T>& inputData)
{
    data = inputData;
}

template<typename T>
Vector<T>::Vector(const Vector<T>& other) :
    data(other.data)
{
}

template<typename T>
Vector<T>::Vector(Vector<T>&& other) noexcept :
        data(std::move(other.data))
{
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
    if (this != &other)
    {
        data = other.data;
    }

    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) noexcept
{
    if (this != &other)
    {
        data = std::move(other.data);
    }

    return *this;
}

template<typename T>
unsigned int Vector<T>::dim() const
{
    return data.size();
}

template<typename T>
const T& Vector<T>::operator[](unsigned int idx) const
{
    if (idx >= data.size())
        throw std::invalid_argument("Invalid index !");

    return data[idx];
}

template<typename T>
T& Vector<T>::operator[](unsigned int idx)
{
    //Use Scott Meyers's trick and make this operator call the const version of operator(row,col)
    return const_cast<T&> (static_cast<const Vector<T>&>(*this)[idx]);
}

template <typename T>
typename std::vector<T>::const_iterator Vector<T>::begin() const
{
    return data.cbegin();
}

template <typename T>
typename std::vector<T>::const_iterator Vector<T>::end() const
{
    return data.cend();
}

template<typename T>
Vector<T> Vector<T>::operator+(const Vector& other) const
{
    if (other.data.size() != data.size())
        throw std::invalid_argument("Cannot add incompatible vectors !");

    Vector res(data.size());
    std::transform(data.begin(), data.end(), other.data.begin(), res.data.begin(), std::plus<T>());
    return res;
}

template<typename T>
Vector<T> Vector<T>::operator-(const Vector& other) const
{
    if (other.data.size() != data.size())
        throw std::invalid_argument("Cannot subtract incompatible vectors !");

    Vector res(data.size());
    std::transform(data.begin(), data.end(), other.data.begin(), res.data.begin(), std::minus<T>());
    return res;
}

template<typename T>
Vector<T> Vector<T>::operator*(const Vector& other) const
{
    if (other.data.size() != data.size())
        throw std::invalid_argument("Cannot perform element-wise multiplication. Incompatible vectors !");

    Vector res(data.size());
    std::transform(data.begin(), data.end(), other.data.begin(), res.data.begin(), std::multiplies<T>());
    return res;
}

template<typename T>
Vector<T> Vector<T>::operator/(const Vector& other) const
{
    if (other.data.size() != data.size())
        throw std::invalid_argument("Cannot perform element-wise division. Incompatible vectors !");

    if (std::find(std::begin(other.data), std::end(other.data), static_cast<T>(0)) != std::end(other.data))
        throw std::invalid_argument("Divisor vector contains zeros !");

    Vector res(data.size());
    std::transform(data.begin(), data.end(), other.data.begin(), res.data.begin(), std::divides<T>());
    return res;
}

template<typename T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& other)
{
    if (other.data.size() != data.size())
        throw std::invalid_argument("Cannot add incompatible vectors !");

    std::transform(data.begin(), data.end(), other.data.begin(), data.begin(), std::plus<T>());
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator-=(const Vector<T>& other)
{
    if (other.data.size() != data.size())
        throw std::invalid_argument("Cannot subtract incompatible vectors !");

    std::transform(data.begin(), data.end(), other.data.begin(), data.begin(), std::minus<T>());
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator*=(const Vector<T>& other)
{
    if (other.data.size() != data.size())
        throw std::invalid_argument("Cannot perform element-wise multiplication. Incompatible vectors !");

    std::transform(data.begin(), data.end(), other.data.begin(), data.begin(), std::multiplies<T>());
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator/=(const Vector<T>& other)
{
    if (other.data.size() != data.size())
        throw std::invalid_argument("Cannot perform element-wise division. Incompatible vectors !");


    if (std::find(std::begin(other.data), std::end(other.data), static_cast<T>(0)) != std::end(other.data))
        throw std::invalid_argument("Divisor vector contains zeros !");

    std::transform(data.begin(), data.end(), other.data.begin(), data.begin(), std::divides<T>());
    return *this;
}

template<typename T>
Vector<T> Vector<T>::operator+(const T val) const
{
    Vector res(data.size());
    std::transform(data.begin(), data.end(), res.data.begin(),
                   [&](const T v) {return v + val; } );
    return res;
}

//Non-member operator function
template<typename T>
Vector<T> operator+(const T val, const Vector<T>& vector)
{
    return vector.operator+(val);
}

template<typename T>
Vector<T> Vector<T>::operator-(const T val) const
{
    Vector res(data.size());
    std::transform(data.begin(), data.end(), res.data.begin(),
                   [&](const T v) {return v - val; } );
    return res;
}

template<typename T>
Vector<T> Vector<T>::operator*(const T val) const
{
    Vector res(data.size());
    std::transform(data.begin(), data.end(), res.data.begin(),
                   [&](const T v) {return v * val; } );
    return res;
}

//Non-member operator function
template<typename T>
Vector<T> operator*(const T val, const Vector<T>& vector)
{
    return vector.operator*(val);
}

template<typename T>
Vector<T> Vector<T>::operator/(const T val) const
{
    if (val == 0)
        throw std::invalid_argument("Attempt to divide by zero");

    Vector res(data.size());
    std::transform(data.begin(), data.end(), res.data.begin(),
                   [&](const T v) {return v / val; } );
    return res;
}

template <typename T>
Vector<T>& Vector<T>::operator+=(const T val)
{
    std::transform(data.begin(), data.end(), data.begin(),
                   [&](const T v) {return v + val; } );
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator-=(const T val)
{
    std::transform(data.begin(), data.end(), data.begin(),
                   [&](const T v) {return v - val; } );
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator*=(const T val)
{
    std::transform(data.begin(), data.end(), data.begin(),
                   [&](const T v) {return v * val; } );
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator/=(const T val)
{
    if (val == 0)
        throw std::invalid_argument("Attempt to divide by zero");

    std::transform(data.begin(), data.end(), data.begin(),
                   [&](const T v) {return v / val; } );
    return *this;
}

template <typename T>
T Vector<T>::dot(const Vector& other) const
{
    if (other.data.size() != data.size())
        throw std::invalid_argument("Vector must have the same size!");

    return std::inner_product(data.begin(), data.end(), other.data.begin(), static_cast<T>(0));
}


template class Vector<int>;
template class Vector<float>;
template class Vector<double>;

template class Vector<int>      operator+(const int val,    const Vector<int>&);
template class Vector<float>    operator+(const float val,  const Vector<float>&);
template class Vector<double>   operator+(const double val, const Vector<double>&);

template class Vector<int>      operator*(const int val,    const Vector<int>&);
template class Vector<float>    operator*(const float val,  const Vector<float>&);
template class Vector<double>   operator*(const double val, const Vector<double>&);