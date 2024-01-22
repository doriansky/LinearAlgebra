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
    Vector<std::complex<typename std::common_type<T,U>::type>> Vector<T>::operator+(const Vector<std::complex<U>>& other) const
    {
        if (other.dim() != data.size())
            throw std::invalid_argument("Cannot add incompatible vectors !");

        Vector<std::complex<typename std::common_type<T,U>::type>> res(data.size());
        for (unsigned int i=0; i< data.size(); i++)
            res[i] = std::complex<typename std::common_type<T,U>::type>(data[i] + other[i].real(), other[i].imag());

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
    Vector<std::complex<typename std::common_type<T,U>::type>> Vector<T>::operator-(const Vector<std::complex<U>>& other) const
    {
        if (other.dim() != data.size())
            throw std::invalid_argument("Cannot add incompatible vectors !");

        Vector<std::complex<typename std::common_type<T,U>::type>> res(data.size());
        for (unsigned int i=0; i< data.size(); i++)
            res[i] = std::complex<typename std::common_type<T,U>::type>(data[i] - other[i].real(), -other[i].imag());

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


    /////////////////////////////////////////////////////////////// complex

    template <typename U>
    Vector<std::complex<U>>::Vector(const unsigned int dim)
    {
        data = std::vector<std::complex<U>>(dim);
    }

    template <typename U>
    Vector<std::complex<U>>::Vector(const std::vector<std::complex<U>>& inputData)
    {
        data = inputData;
    }

    template<typename U>
    const std::complex<U>& Vector<std::complex<U>>::operator[](unsigned int idx) const
    {
        if (idx >= data.size())
            throw std::invalid_argument("Invalid index !");

        return data[idx];
    }

    template<typename U>
    std::complex<U>& Vector<std::complex<U>>::operator[](unsigned int idx)
    {
        //Use Scott Meyers's trick and make this operator call the const version of operator(row,col)
        return const_cast<std::complex<U>&> (static_cast<const Vector<std::complex<U>>&>(*this)[idx]);
    }

    template<typename U>
    typename std::vector<std::complex<U>>::const_iterator Vector<std::complex<U>>::begin() const
    {
        return data.cbegin();
    }

    template<typename U>
    typename std::vector<std::complex<U>>::const_iterator Vector<std::complex<U>>::end() const
    {
        return data.cend();
    }

    template<typename U>
    unsigned int Vector<std::complex<U>>::dim() const
    {
        return data.size();
    }

    template <typename U>
    template <typename V>
    Vector<std::complex<typename std::common_type<U,V>::type>> Vector<std::complex<U>>::operator+(const Vector<V>& other) const
    {
        if (other.dim() != data.size())
            throw std::invalid_argument("Cannot add incompatible vectors !");

        Vector<std::complex<typename std::common_type<U,V>::type>> res(data.size());
        for (unsigned int i=0; i<data.size(); i++)
            res[i] = std::complex<typename std::common_type<U,V>::type>(data[i].real() + other[i], data[i].imag());

        return res;
    }

    template <typename U>
    template <typename V>
    Vector<std::complex<typename std::common_type<U,V>::type>> Vector<std::complex<U>>::operator+(const Vector<std::complex<V>>& other) const
    {
        if (other.dim() != data.size())
            throw std::invalid_argument("Cannot add incompatible vectors !");

        Vector<std::complex<typename std::common_type<U,V>::type>> res(data.size());
        for (unsigned int i=0; i<data.size(); i++)
            res[i] = std::complex<typename std::common_type<U,V>::type>(data[i].real() + other[i].real(), data[i].imag() + other[i].imag());

        return res;
    }

    template <typename U>
    template <typename V>
    Vector<std::complex<typename std::common_type<U,V>::type>> Vector<std::complex<U>>::operator-(const Vector<V>& other) const
    {
        if (other.dim() != data.size())
            throw std::invalid_argument("Cannot add incompatible vectors !");

        Vector<std::complex<typename std::common_type<U,V>::type>> res(data.size());
        for (unsigned int i=0; i<data.size(); i++)
            res[i] = std::complex<typename std::common_type<U,V>::type>(data[i].real() - other[i], data[i].imag());

        return res;
    }

    template <typename U>
    template <typename V>
    Vector<std::complex<typename std::common_type<U,V>::type>> Vector<std::complex<U>>::operator-(const Vector<std::complex<V>>& other) const
    {
        if (other.dim() != data.size())
            throw std::invalid_argument("Cannot add incompatible vectors !");

        Vector<std::complex<typename std::common_type<U,V>::type>> res(data.size());
        for (unsigned int i=0; i<data.size(); i++)
            res[i] = std::complex<typename std::common_type<U,V>::type>(data[i].real() - other[i].real(), data[i].imag() - other[i].imag());

        return res;
    }

    template<typename U>
    Vector<std::complex<U>>& Vector<std::complex<U>>::operator+=(const Vector<std::complex<U>>& other)
    {
        if (other.data.size() != data.size())
            throw std::invalid_argument("Cannot add incompatible vectors !");

        std::transform(data.begin(), data.end(), other.data.begin(), data.begin(), std::plus<std::complex<U>>());
        return *this;
    }

    template<typename U>
    Vector<std::complex<U>>& Vector<std::complex<U>>::operator-=(const Vector<std::complex<U>>& other)
    {
        if (other.data.size() != data.size())
            throw std::invalid_argument("Cannot subtract incompatible vectors !");

        std::transform(data.begin(), data.end(), other.data.begin(), data.begin(), std::minus<std::complex<U>>());
        return *this;
    }

#include "VectorExplicitTemplateInstantiations.hpp"
} //namespace LinearAlgebra::Vector
