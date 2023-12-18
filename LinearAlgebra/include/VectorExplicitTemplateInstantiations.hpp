//
// Created by dorian on 18.12.2023.
//

#ifndef LINEARALGEBRATOOLBOX_VECTOREXPLICITTEMPLATEINSTANTIATIONS_HPP
#define LINEARALGEBRATOOLBOX_VECTOREXPLICITTEMPLATEINSTANTIATIONS_HPP


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

//Dot product
template std::common_type<int, int>::type Vector<int>::dot<int>(const Vector<int>&) const;
template std::common_type<int, float>::type Vector<int>::dot<float>(const Vector<float>&) const;
template std::common_type<int, double>::type Vector<int>::dot<double>(const Vector<double>&) const;

template std::common_type<float, int>::type Vector<float>::dot<int>(const Vector<int>&) const;
template std::common_type<float, float>::type Vector<float>::dot<float>(const Vector<float>&) const;
template std::common_type<float, double>::type Vector<float>::dot<double>(const Vector<double>&) const;

template std::common_type<double, int>::type Vector<double>::dot<int>(const Vector<int>&) const;
template std::common_type<double, float>::type Vector<double>::dot<float>(const Vector<float>&) const;
template std::common_type<double, double>::type Vector<double>::dot<double>(const Vector<double>&) const;


#endif //LINEARALGEBRATOOLBOX_VECTOREXPLICITTEMPLATEINSTANTIATIONS_HPP
