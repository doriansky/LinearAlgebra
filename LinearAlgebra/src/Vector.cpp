//
// Created by dorian on 03.11.2023.
// stoicadorian@gmail.com
//

#include "Vector.hpp"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <stdexcept>

namespace LinearAlgebra::Vector
{
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
    template<typename U>
    typename std::common_type<T,U>::type Vector<T>::dot(const Vector<U>& other) const
    {
        if (other.dim() != data.size())
            throw std::invalid_argument("Vector must have the same size!");

        return std::inner_product(data.begin(), data.end(), other.begin(), static_cast<typename std::common_type<T,U>::type>(0));
    }

    template <typename T>
    long double Vector<T>::norm() const
    {
        return std::sqrt(this->dot(*this));
    }

#include "VectorExplicitTemplateInstantiations.hpp"
} //namespace LinearAlgebra::Vector
