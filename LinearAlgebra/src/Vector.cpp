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
template<typename U>
Vector<typename std::common_type<T,U>::type> Vector<T>::operator+(const Vector<U>& other) const
{
    if (other.dim() != data.size())
        throw std::invalid_argument("Cannot add incompatible vectors !");

    Vector<typename std::common_type<T,U>::type> res(data.size());
    std::transform(data.begin(), data.end(), other.begin(), &res[0], std::plus<typename std::common_type<T,U>::type>());
    return res;
}

template<typename T>
template<typename U>
Vector<typename std::common_type<T,U>::type> Vector<T>::operator-(const Vector<U>& other) const
{
    if (other.dim() != data.size())
        throw std::invalid_argument("Cannot subtract incompatible vectors !");

    Vector<typename std::common_type<T,U>::type> res(data.size());
    std::transform(data.begin(), data.end(), other.begin(), &res[0], std::minus<typename std::common_type<T,U>::type>());
    return res;
}

template<typename T>
template<typename U>
Vector<typename std::common_type<T,U>::type> Vector<T>::operator*(const Vector<U>& other) const
{
    if (other.dim() != data.size())
        throw std::invalid_argument("Cannot perform element-wise multiplication. Incompatible vectors !");

    Vector<typename std::common_type<T,U>::type> res(data.size());
    std::transform(data.begin(), data.end(), other.begin(), &res[0], std::multiplies<typename std::common_type<T,U>::type>());
    return res;
}

template<typename T>
template<typename U>
Vector<typename std::common_type<T,U>::type> Vector<T>::operator/(const Vector<U>& other) const
{
    if (other.dim() != data.size())
        throw std::invalid_argument("Cannot perform element-wise division. Incompatible vectors !");

    if (std::find(other.begin(), other.end(), static_cast<U>(0)) != other.end())
        throw std::invalid_argument("Divisor vector contains zeros !");

    Vector<typename std::common_type<T,U>::type> res(data.size());
    std::transform(data.begin(), data.end(), other.begin(), &res[0], std::divides<typename std::common_type<T,U>::type>());
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
template<typename U>
Vector<typename std::common_type<T,U>::type> Vector<T>::operator+(const U val) const
{
    Vector<typename std::common_type<T,U>::type> res(data.size());
    std::transform(data.begin(), data.end(), &res[0],
                   [&](const T v) {return v + val; } );
    return res;
}

//Non-member operator function
template<typename T, typename U>
Vector<typename std::common_type<T,U>::type> operator+(const T val, const Vector<U>& vector)
{
    return vector.operator+(val);
}

template<typename T>
template<typename U>
Vector<typename std::common_type<T,U>::type> Vector<T>::operator-(const U val) const
{
    Vector<typename std::common_type<T,U>::type> res(data.size());
    std::transform(data.begin(), data.end(), &res[0],
                   [&](const T v) {return v - val; } );
    return res;
}

template<typename T>
template<typename U>
Vector<typename std::common_type<T,U>::type> Vector<T>::operator*(const U val) const
{
    Vector<typename std::common_type<T,U>::type> res(data.size());
    std::transform(data.begin(), data.end(), &res[0],
                   [&](const T v) {return v * val; } );
    return res;
}

//Non-member operator function
template<typename T, typename U>
Vector<typename std::common_type<T,U>::type> operator*(const T val, const Vector<U>& vector)
{
    return vector.operator*(val);
}

template<typename T>
template<typename U>
Vector<typename std::common_type<T,U>::type> Vector<T>::operator/(const U val) const
{
    if (val == static_cast<U>(0))
        throw std::invalid_argument("Attempt to divide by zero");

    Vector<typename std::common_type<T,U>::type> res(data.size());
    std::transform(data.begin(), data.end(), &res[0],
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

//operator+
template Vector<std::common_type<int, int>::type> Vector<int>::operator+<int>(Vector<int> const&) const;
template Vector<std::common_type<float, float>::type> Vector<float>::operator+<float>(Vector<float> const&) const;
template Vector<std::common_type<double, double>::type> Vector<double>::operator+<double>(Vector<double> const&) const;

template Vector<std::common_type<int, float>::type> Vector<int>::operator+<float>(Vector<float> const&) const;
template Vector<std::common_type<int, double>::type> Vector<int>::operator+<double>(Vector<double> const&) const;

template Vector<std::common_type<float, int>::type> Vector<float>::operator+<int>(Vector<int> const&) const;
template Vector<std::common_type<float, double>::type> Vector<float>::operator+<double>(Vector<double> const&) const;

template Vector<std::common_type<double, int>::type> Vector<double>::operator+<int>(Vector<int> const&) const;
template Vector<std::common_type<double, float>::type> Vector<double>::operator+<float>(Vector<float> const&) const;

//operator-
template Vector<std::common_type<int, int>::type> Vector<int>::operator-<int>(Vector<int> const&) const;
template Vector<std::common_type<float, float>::type> Vector<float>::operator-<float>(Vector<float> const&) const;
template Vector<std::common_type<double, double>::type> Vector<double>::operator-<double>(Vector<double> const&) const;

template Vector<std::common_type<int, float>::type> Vector<int>::operator-<float>(Vector<float> const&) const;
template Vector<std::common_type<int, double>::type> Vector<int>::operator-<double>(Vector<double> const&) const;

template Vector<std::common_type<float, int>::type> Vector<float>::operator-<int>(Vector<int> const&) const;
template Vector<std::common_type<float, double>::type> Vector<float>::operator-<double>(Vector<double> const&) const;

template Vector<std::common_type<double, int>::type> Vector<double>::operator-<int>(Vector<int> const&) const;
template Vector<std::common_type<double, float>::type> Vector<double>::operator-<float>(Vector<float> const&) const;

//operator*
template Vector<std::common_type<int, int>::type> Vector<int>::operator*<int>(Vector<int> const&) const;
template Vector<std::common_type<float, float>::type> Vector<float>::operator*<float>(Vector<float> const&) const;
template Vector<std::common_type<double, double>::type> Vector<double>::operator*<double>(Vector<double> const&) const;

template Vector<std::common_type<int, float>::type> Vector<int>::operator*<float>(Vector<float> const&) const;
template Vector<std::common_type<int, double>::type> Vector<int>::operator*<double>(Vector<double> const&) const;

template Vector<std::common_type<float, int>::type> Vector<float>::operator*<int>(Vector<int> const&) const;
template Vector<std::common_type<float, double>::type> Vector<float>::operator*<double>(Vector<double> const&) const;

template Vector<std::common_type<double, int>::type> Vector<double>::operator*<int>(Vector<int> const&) const;
template Vector<std::common_type<double, float>::type> Vector<double>::operator*<float>(Vector<float> const&) const;

//operator/
template Vector<std::common_type<int, int>::type> Vector<int>::operator/<int>(Vector<int> const&) const;
template Vector<std::common_type<float, float>::type> Vector<float>::operator/<float>(Vector<float> const&) const;
template Vector<std::common_type<double, double>::type> Vector<double>::operator/<double>(Vector<double> const&) const;

template Vector<std::common_type<int, float>::type> Vector<int>::operator/<float>(Vector<float> const&) const;
template Vector<std::common_type<int, double>::type> Vector<int>::operator/<double>(Vector<double> const&) const;

template Vector<std::common_type<float, int>::type> Vector<float>::operator/<int>(Vector<int> const&) const;
template Vector<std::common_type<float, double>::type> Vector<float>::operator/<double>(Vector<double> const&) const;

template Vector<std::common_type<double, int>::type> Vector<double>::operator/<int>(Vector<int> const&) const;
template Vector<std::common_type<double, float>::type> Vector<double>::operator/<float>(Vector<float> const&) const;


// Addition broadcasters
template Vector<std::common_type<int, int>::type> Vector<int>::operator+<int>(int) const;
template Vector<std::common_type<int, float>::type> Vector<int>::operator+<float>(float) const;
template Vector<std::common_type<int, double>::type> Vector<int>::operator+<double>(double) const;

template Vector<std::common_type<float, int>::type> Vector<float>::operator+<int>(int) const;
template Vector<std::common_type<float, float>::type> Vector<float>::operator+<float>(float) const;
template Vector<std::common_type<float, double>::type> Vector<float>::operator+<double>(double) const;

template Vector<std::common_type<double, int>::type> Vector<double>::operator+<int>(int) const;
template Vector<std::common_type<double, float>::type> Vector<double>::operator+<float>(float) const;
template Vector<std::common_type<double, double>::type> Vector<double>::operator+<double>(double) const;

//Subtraction broadcasters
template Vector<std::common_type<int, int>::type> Vector<int>::operator-<int>(int) const;
template Vector<std::common_type<int, float>::type> Vector<int>::operator-<float>(float) const;
template Vector<std::common_type<int, double>::type> Vector<int>::operator-<double>(double) const;

template Vector<std::common_type<float, int>::type> Vector<float>::operator-<int>(int) const;
template Vector<std::common_type<float, float>::type> Vector<float>::operator-<float>(float) const;
template Vector<std::common_type<float, double>::type> Vector<float>::operator-<double>(double) const;

template Vector<std::common_type<double, int>::type> Vector<double>::operator-<int>(int) const;
template Vector<std::common_type<double, float>::type> Vector<double>::operator-<float>(float) const;
template Vector<std::common_type<double, double>::type> Vector<double>::operator-<double>(double) const;

// Multiplication broadcasters
template Vector<std::common_type<int, int>::type> Vector<int>::operator*<int>(int) const;
template Vector<std::common_type<int, float>::type> Vector<int>::operator*<float>(float) const;
template Vector<std::common_type<int, double>::type> Vector<int>::operator*<double>(double) const;

template Vector<std::common_type<float, int>::type> Vector<float>::operator*<int>(int) const;
template Vector<std::common_type<float, float>::type> Vector<float>::operator*<float>(float) const;
template Vector<std::common_type<float, double>::type> Vector<float>::operator*<double>(double) const;

template Vector<std::common_type<double, int>::type> Vector<double>::operator*<int>(int) const;
template Vector<std::common_type<double, float>::type> Vector<double>::operator*<float>(float) const;
template Vector<std::common_type<double, double>::type> Vector<double>::operator*<double>(double) const;

//Division broadcasters
template Vector<std::common_type<int, int>::type> Vector<int>::operator/<int>(int) const;
template Vector<std::common_type<int, float>::type> Vector<int>::operator/<float>(float) const;
template Vector<std::common_type<int, double>::type> Vector<int>::operator/<double>(double) const;

template Vector<std::common_type<float, int>::type> Vector<float>::operator/<int>(int) const;
template Vector<std::common_type<float, float>::type> Vector<float>::operator/<float>(float) const;
template Vector<std::common_type<float, double>::type> Vector<float>::operator/<double>(double) const;

template Vector<std::common_type<double, int>::type> Vector<double>::operator/<int>(int) const;
template Vector<std::common_type<double, float>::type> Vector<double>::operator/<float>(float) const;
template Vector<std::common_type<double, double>::type> Vector<double>::operator/<double>(double) const;

//Non-member addition broadcasters (allow doing newVector = scalar + vec)
template Vector<std::common_type<int, int>::type>       operator+(const int val,    const Vector<int>&);
template Vector<std::common_type<int, float>::type>     operator+(const int val,    const Vector<float>&);
template Vector<std::common_type<int, double>::type>    operator+(const int val,    const Vector<double>&);

template Vector<std::common_type<float, int>::type>       operator+(const float val,    const Vector<int>&);
template Vector<std::common_type<float, float>::type>     operator+(const float val,    const Vector<float>&);
template Vector<std::common_type<float, double>::type>    operator+(const float val,    const Vector<double>&);

template Vector<std::common_type<double, int>::type>       operator+(const double val,    const Vector<int>&);
template Vector<std::common_type<double, float>::type>     operator+(const double val,    const Vector<float>&);
template Vector<std::common_type<double, double>::type>    operator+(const double val,    const Vector<double>&);

//Non-member multiplication broadcasters (allow doing newVector = scalar * vec)
template Vector<std::common_type<int, int>::type>       operator*(const int val,    const Vector<int>&);
template Vector<std::common_type<int, float>::type>     operator*(const int val,    const Vector<float>&);
template Vector<std::common_type<int, double>::type>    operator*(const int val,    const Vector<double>&);

template Vector<std::common_type<float, int>::type>       operator*(const float val,    const Vector<int>&);
template Vector<std::common_type<float, float>::type>     operator*(const float val,    const Vector<float>&);
template Vector<std::common_type<float, double>::type>    operator*(const float val,    const Vector<double>&);

template Vector<std::common_type<double, int>::type>       operator*(const double val,    const Vector<int>&);
template Vector<std::common_type<double, float>::type>     operator*(const double val,    const Vector<float>&);
template Vector<std::common_type<double, double>::type>    operator*(const double val,    const Vector<double>&);