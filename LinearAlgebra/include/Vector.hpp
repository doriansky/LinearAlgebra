//
// Created by dorian on 03.11.2023.
// stoicadorian@gmail.com
//
#ifndef VECTOR_HPP
#define VECTOR_HPP

#pragma once

#include <vector>

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
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;

    Vector operator*(const Vector& other) const;
    Vector operator/(const Vector& other) const;

    //In-place operations with another Vector
    Vector& operator+=(const Vector& other);
    Vector& operator-=(const Vector& other);
    Vector& operator*=(const Vector& other);
    Vector& operator/=(const Vector& other);

    //Broadcasters
    Vector operator+    (T val) const;
    Vector operator-    (T val) const;
    Vector operator*    (T val) const;
    Vector operator/    (T val) const;
    Vector& operator+=  (T val);
    Vector& operator-=  (T val);
    Vector& operator*=  (T val);
    Vector& operator/=  (T val);

    T dot(const Vector& other) const;

private:
    std::vector<T> data;
};
#endif //VECTOR_HPP

// Non-member functions that allow writing code with the following syntax:
// result = 2 + myVector;
template<typename T>
Vector<T> operator+(T val, const Vector<T>&);

// result = 2 * myVector;
template<typename T>
Vector<T> operator*(T val,  const Vector<T>&);