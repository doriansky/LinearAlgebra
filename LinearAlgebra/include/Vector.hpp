//
// Created by dorian on 03.11.2023.
// stoicadorian@gmail.com
//
#ifndef VECTOR_HPP
#define VECTOR_HPP

#pragma once

#include <vector>

namespace LinearAlgebra::Vector
{
    template <typename T>
    class Vector
    {

    public:
        Vector()    = delete;
        ~Vector()   = default;

        explicit Vector(unsigned int);
        explicit Vector(const std::vector<T>&);

        //Copy and move constructor
        Vector(const Vector&);
        Vector(Vector&&) noexcept;

        //Copy assignment and move assignment
        Vector& operator=(const Vector& other);
        Vector& operator=(Vector&& other) noexcept;

        //Getters for num rows and num cols
        [[nodiscard]] unsigned int dim() const;

        //Array subscript
        const T& operator[] (unsigned int) const;
        T& operator[] (unsigned int);

        //Read-only access (useful when setting a Vector row in a Matrix)
        typename std::vector<T>::const_iterator begin() const;
        typename std::vector<T>::const_iterator end() const;

        //Binary arithmetic
        template<class U>
        Vector<typename std::common_type<T,U>::type> operator+(const Vector<U>& other) const;

        template<class U>
        Vector<typename std::common_type<T,U>::type> operator-(const Vector<U>& other) const;

        template<class U>
        Vector<typename std::common_type<T,U>::type> operator*(const Vector<U>& other) const;

        template<class U>
        Vector<typename std::common_type<T,U>::type> operator/(const Vector<U>& other) const;

        //In-place operations with another Vector (OF THE SAME TYPE !)
        Vector& operator+=(const Vector& other);
        Vector& operator-=(const Vector& other);
        Vector& operator*=(const Vector& other);
        Vector& operator/=(const Vector& other);

        //Broadcasters
        template<class U>
        Vector<typename std::common_type<T,U>::type> operator+    (U val) const;

        template<class U>
        Vector<typename std::common_type<T,U>::type> operator-    (U val) const;

        template<class U>
        Vector<typename std::common_type<T,U>::type> operator*    (U val) const;

        template<class U>
        Vector<typename std::common_type<T,U>::type> operator/    (U val) const;

        // In-place broadcasters (scalar must have the same type !)
        Vector& operator+=  (T val);
        Vector& operator-=  (T val);
        Vector& operator*=  (T val);
        Vector& operator/=  (T val);

        template<class U>
        [[nodiscard]] typename std::common_type<T, U>::type dot(const Vector<U>& other) const;

    private:
        std::vector<T> data;
    };
#endif //VECTOR_HPP

    // Non-member functions that allow writing code with the following syntax:
    // result = 2 + myVector;
    template<typename T, typename U>
    Vector<typename std::common_type<T,U>::type> operator+(T val, const Vector<U>&);

    // result = 2 * myVector;
    template<typename T, typename U>
    Vector<typename std::common_type<T,U>::type> operator*(T val,  const Vector<U>&);
}
