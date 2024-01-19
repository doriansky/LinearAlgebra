//
// Created by dorian on 18.12.2023.
//

#ifndef LINEARALGEBRATOOLBOX_MATRIXEXPLICITTEMPLATEINSTANTIATIONS_HPP
#define LINEARALGEBRATOOLBOX_MATRIXEXPLICITTEMPLATEINSTANTIATIONS_HPP

template class Matrix<int>;
template class Matrix<float>;
template class Matrix<double>;
template class Matrix<long double>;

//operator+
template Matrix<std::common_type<int, int>::type> Matrix<int>::operator+<int>(Matrix<int> const&) const;
template Matrix<std::common_type<int, float>::type> Matrix<int>::operator+<float>(Matrix<float> const&) const;
template Matrix<std::common_type<int, double>::type> Matrix<int>::operator+<double>(Matrix<double> const&) const;
template Matrix<std::common_type<int, long double>::type> Matrix<int>::operator+<long double>(Matrix<long double> const&) const;

template Matrix<std::common_type<float, float>::type> Matrix<float>::operator+<float>(Matrix<float> const&) const;
template Matrix<std::common_type<float, int>::type> Matrix<float>::operator+<int>(Matrix<int> const&) const;
template Matrix<std::common_type<float, double>::type> Matrix<float>::operator+<double>(Matrix<double> const&) const;
template Matrix<std::common_type<float, long double>::type> Matrix<float>::operator+<long double>(Matrix<long double> const&) const;

template Matrix<std::common_type<double, int>::type> Matrix<double>::operator+<int>(Matrix<int> const&) const;
template Matrix<std::common_type<double, float>::type> Matrix<double>::operator+<float>(Matrix<float> const&) const;
template Matrix<std::common_type<double, double>::type> Matrix<double>::operator+<double>(Matrix<double> const&) const;
template Matrix<std::common_type<double, long double>::type> Matrix<double>::operator+<long double>(Matrix<long double> const&) const;

template Matrix<std::common_type<long double, int>::type> Matrix<long double>::operator+<int>(Matrix<int> const&) const;
template Matrix<std::common_type<long double, float>::type> Matrix<long double>::operator+<float>(Matrix<float> const&) const;
template Matrix<std::common_type<long double, double>::type> Matrix<long double>::operator+<double>(Matrix<double> const&) const;
template Matrix<std::common_type<long double, long double>::type> Matrix<long double>::operator+<long double>(Matrix<long double> const&) const;

//operator-
template Matrix<std::common_type<int, int>::type> Matrix<int>::operator-<int>(Matrix<int> const&) const;
template Matrix<std::common_type<int, float>::type> Matrix<int>::operator-<float>(Matrix<float> const&) const;
template Matrix<std::common_type<int, double>::type> Matrix<int>::operator-<double>(Matrix<double> const&) const;
template Matrix<std::common_type<int, long double>::type> Matrix<int>::operator-<long double>(Matrix<long double> const&) const;

template Matrix<std::common_type<float, int>::type> Matrix<float>::operator-<int>(Matrix<int> const&) const;
template Matrix<std::common_type<float, float>::type> Matrix<float>::operator-<float>(Matrix<float> const&) const;
template Matrix<std::common_type<float, double>::type> Matrix<float>::operator-<double>(Matrix<double> const&) const;
template Matrix<std::common_type<float, long double>::type> Matrix<float>::operator-<long double>(Matrix<long double> const&) const;

template Matrix<std::common_type<double, int>::type> Matrix<double>::operator-<int>(Matrix<int> const&) const;
template Matrix<std::common_type<double, float>::type> Matrix<double>::operator-<float>(Matrix<float> const&) const;
template Matrix<std::common_type<double, double>::type> Matrix<double>::operator-<double>(Matrix<double> const&) const;
template Matrix<std::common_type<double, long double>::type> Matrix<double>::operator-<long double>(Matrix<long double> const&) const;

template Matrix<std::common_type<long double, int>::type> Matrix<long double>::operator-<int>(Matrix<int> const&) const;
template Matrix<std::common_type<long double, float>::type> Matrix<long double>::operator-<float>(Matrix<float> const&) const;
template Matrix<std::common_type<long double, double>::type> Matrix<long double>::operator-<double>(Matrix<double> const&) const;
template Matrix<std::common_type<long double, long double>::type> Matrix<long double>::operator-<long double>(Matrix<long double> const&) const;

//operator*
template Matrix<std::common_type<int, int>::type> Matrix<int>::operator*<int>(Matrix<int> const&) const;
template Matrix<std::common_type<int, float>::type> Matrix<int>::operator*<float>(Matrix<float> const&) const;
template Matrix<std::common_type<int, double>::type> Matrix<int>::operator*<double>(Matrix<double> const&) const;
template Matrix<std::common_type<int, long double>::type> Matrix<int>::operator*<long double>(Matrix<long double> const&) const;

template Matrix<std::common_type<float, int>::type> Matrix<float>::operator*<int>(Matrix<int> const&) const;
template Matrix<std::common_type<float, float>::type> Matrix<float>::operator*<float>(Matrix<float> const&) const;
template Matrix<std::common_type<float, double>::type> Matrix<float>::operator*<double>(Matrix<double> const&) const;
template Matrix<std::common_type<float, long double>::type> Matrix<float>::operator*<long double>(Matrix<long double> const&) const;

template Matrix<std::common_type<double, int>::type> Matrix<double>::operator*<int>(Matrix<int> const&) const;
template Matrix<std::common_type<double, float>::type> Matrix<double>::operator*<float>(Matrix<float> const&) const;
template Matrix<std::common_type<double, double>::type> Matrix<double>::operator*<double>(Matrix<double> const&) const;
template Matrix<std::common_type<double, long double>::type> Matrix<double>::operator*<long double>(Matrix<long double> const&) const;

template Matrix<std::common_type<long double, int>::type> Matrix<long double>::operator*<int>(Matrix<int> const&) const;
template Matrix<std::common_type<long double, float>::type> Matrix<long double>::operator*<float>(Matrix<float> const&) const;
template Matrix<std::common_type<long double, double>::type> Matrix<long double>::operator*<double>(Matrix<double> const&) const;
template Matrix<std::common_type<long double, long double>::type> Matrix<long double>::operator*<long double>(Matrix<long double> const&) const;

//operator/
template Matrix<std::common_type<int, int>::type> Matrix<int>::operator/<int>(Matrix<int> const&) const;
template Matrix<std::common_type<int, float>::type> Matrix<int>::operator/<float>(Matrix<float> const&) const;
template Matrix<std::common_type<int, double>::type> Matrix<int>::operator/<double>(Matrix<double> const&) const;
template Matrix<std::common_type<int, long double>::type> Matrix<int>::operator/<long double>(Matrix<long double> const&) const;

template Matrix<std::common_type<float, int>::type> Matrix<float>::operator/<int>(Matrix<int> const&) const;
template Matrix<std::common_type<float, float>::type> Matrix<float>::operator/<float>(Matrix<float> const&) const;
template Matrix<std::common_type<float, double>::type> Matrix<float>::operator/<double>(Matrix<double> const&) const;
template Matrix<std::common_type<float, long double>::type> Matrix<float>::operator/<long double>(Matrix<long double> const&) const;

template Matrix<std::common_type<double, int>::type> Matrix<double>::operator/<int>(Matrix<int> const&) const;
template Matrix<std::common_type<double, float>::type> Matrix<double>::operator/<float>(Matrix<float> const&) const;
template Matrix<std::common_type<double, double>::type> Matrix<double>::operator/<double>(Matrix<double> const&) const;
template Matrix<std::common_type<double, long double>::type> Matrix<double>::operator/<long double>(Matrix<long double> const&) const;

template Matrix<std::common_type<long double, int>::type> Matrix<long double>::operator/<int>(Matrix<int> const&) const;
template Matrix<std::common_type<long double, float>::type> Matrix<long double>::operator/<float>(Matrix<float> const&) const;
template Matrix<std::common_type<long double, double>::type> Matrix<long double>::operator/<double>(Matrix<double> const&) const;
template Matrix<std::common_type<long double, long double>::type> Matrix<long double>::operator/<long double>(Matrix<long double> const&) const;

// Addition broadcasters
template Matrix<std::common_type<int, int>::type> Matrix<int>::operator+<int>(int) const;
template Matrix<std::common_type<int, float>::type> Matrix<int>::operator+<float>(float) const;
template Matrix<std::common_type<int, double>::type> Matrix<int>::operator+<double>(double) const;
template Matrix<std::common_type<int, long double>::type> Matrix<int>::operator+<long double>(long double) const;

template Matrix<std::common_type<float, int>::type> Matrix<float>::operator+<int>(int) const;
template Matrix<std::common_type<float, float>::type> Matrix<float>::operator+<float>(float) const;
template Matrix<std::common_type<float, double>::type> Matrix<float>::operator+<double>(double) const;
template Matrix<std::common_type<float, long double>::type> Matrix<float>::operator+<long double>(long double) const;

template Matrix<std::common_type<double, int>::type> Matrix<double>::operator+<int>(int) const;
template Matrix<std::common_type<double, float>::type> Matrix<double>::operator+<float>(float) const;
template Matrix<std::common_type<double, double>::type> Matrix<double>::operator+<double>(double) const;
template Matrix<std::common_type<double, long double>::type> Matrix<double>::operator+<long double>(long double) const;

template Matrix<std::common_type<long double, int>::type> Matrix<long double>::operator+<int>(int) const;
template Matrix<std::common_type<long double, float>::type> Matrix<long double>::operator+<float>(float) const;
template Matrix<std::common_type<long double, double>::type> Matrix<long double>::operator+<double>(double) const;
template Matrix<std::common_type<long double, long double>::type> Matrix<long double>::operator+<long double>(long double) const;

//Non-member addition broadcasters (allow doing newMatrix = scalar + matrix)
template Matrix<std::common_type<int, int>::type>       operator+(const int val,    const Matrix<int>&);
template Matrix<std::common_type<int, float>::type>     operator+(const int val,    const Matrix<float>&);
template Matrix<std::common_type<int, double>::type>    operator+(const int val,    const Matrix<double>&);
template Matrix<std::common_type<int, long double>::type>    operator+(const int val,    const Matrix<long double>&);

template Matrix<std::common_type<float, int>::type>       operator+(const float val,    const Matrix<int>&);
template Matrix<std::common_type<float, float>::type>     operator+(const float val,    const Matrix<float>&);
template Matrix<std::common_type<float, double>::type>    operator+(const float val,    const Matrix<double>&);
template Matrix<std::common_type<float, long double>::type>    operator+(const float val,    const Matrix<long double>&);

template Matrix<std::common_type<double, int>::type>       operator+(const double val,    const Matrix<int>&);
template Matrix<std::common_type<double, float>::type>     operator+(const double val,    const Matrix<float>&);
template Matrix<std::common_type<double, double>::type>    operator+(const double val,    const Matrix<double>&);
template Matrix<std::common_type<double, long double>::type>    operator+(const double val,    const Matrix<long double>&);

template Matrix<std::common_type<long double, int>::type>       operator+(const long double val,    const Matrix<int>&);
template Matrix<std::common_type<long double, float>::type>     operator+(const long double val,    const Matrix<float>&);
template Matrix<std::common_type<long double, double>::type>    operator+(const long double val,    const Matrix<double>&);
template Matrix<std::common_type<long double, long double>::type>    operator+(const long double val,    const Matrix<long double>&);

//Subtraction broadcasters
template Matrix<std::common_type<int, int>::type> Matrix<int>::operator-<int>(int) const;
template Matrix<std::common_type<int, float>::type> Matrix<int>::operator-<float>(float) const;
template Matrix<std::common_type<int, double>::type> Matrix<int>::operator-<double>(double) const;
template Matrix<std::common_type<int, long double>::type> Matrix<int>::operator-<long double>(long double) const;

template Matrix<std::common_type<float, int>::type> Matrix<float>::operator-<int>(int) const;
template Matrix<std::common_type<float, float>::type> Matrix<float>::operator-<float>(float) const;
template Matrix<std::common_type<float, double>::type> Matrix<float>::operator-<double>(double) const;
template Matrix<std::common_type<float, long double>::type> Matrix<float>::operator-<long double>(long double) const;

template Matrix<std::common_type<double, int>::type> Matrix<double>::operator-<int>(int) const;
template Matrix<std::common_type<double, float>::type> Matrix<double>::operator-<float>(float) const;
template Matrix<std::common_type<double, double>::type> Matrix<double>::operator-<double>(double) const;
template Matrix<std::common_type<double, long double>::type> Matrix<double>::operator-<long double>(long double) const;

template Matrix<std::common_type<long double, int>::type> Matrix<long double>::operator-<int>(int) const;
template Matrix<std::common_type<long double, float>::type> Matrix<long double>::operator-<float>(float) const;
template Matrix<std::common_type<long double, double>::type> Matrix<long double>::operator-<double>(double) const;
template Matrix<std::common_type<long double, long double>::type> Matrix<long double>::operator-<long double>(long double) const;

//Multiplication broadcasters
template Matrix<std::common_type<int, int>::type> Matrix<int>::operator*<int>(int) const;
template Matrix<std::common_type<int, float>::type> Matrix<int>::operator*<float>(float) const;
template Matrix<std::common_type<int, double>::type> Matrix<int>::operator*<double>(double) const;
template Matrix<std::common_type<int, long double>::type> Matrix<int>::operator*<long double>(long double) const;

template Matrix<std::common_type<float, int>::type> Matrix<float>::operator*<int>(int) const;
template Matrix<std::common_type<float, float>::type> Matrix<float>::operator*<float>(float) const;
template Matrix<std::common_type<float, double>::type> Matrix<float>::operator*<double>(double) const;
template Matrix<std::common_type<float, long double>::type> Matrix<float>::operator*<long double>(long double) const;

template Matrix<std::common_type<double, int>::type> Matrix<double>::operator*<int>(int) const;
template Matrix<std::common_type<double, float>::type> Matrix<double>::operator*<float>(float) const;
template Matrix<std::common_type<double, double>::type> Matrix<double>::operator*<double>(double) const;
template Matrix<std::common_type<double, long double>::type> Matrix<double>::operator*<long double>(long double) const;

template Matrix<std::common_type<long double, int>::type> Matrix<long double>::operator*<int>(int) const;
template Matrix<std::common_type<long double, float>::type> Matrix<long double>::operator*<float>(float) const;
template Matrix<std::common_type<long double, double>::type> Matrix<long double>::operator*<double>(double) const;
template Matrix<std::common_type<long double, long double>::type> Matrix<long double>::operator*<long double>(long double) const;

//Non-member multiplication broadcasters (allow doing newMatrix = scalar 8 matrix)
template Matrix<std::common_type<int, int>::type>       operator*(const int val,    const Matrix<int>&);
template Matrix<std::common_type<int, float>::type>     operator*(const int val,    const Matrix<float>&);
template Matrix<std::common_type<int, double>::type>    operator*(const int val,    const Matrix<double>&);
template Matrix<std::common_type<int, long double>::type>    operator*(const int val,    const Matrix<long double>&);

template Matrix<std::common_type<float, int>::type>       operator*(const float val,    const Matrix<int>&);
template Matrix<std::common_type<float, float>::type>     operator*(const float val,    const Matrix<float>&);
template Matrix<std::common_type<float, double>::type>    operator*(const float val,    const Matrix<double>&);
template Matrix<std::common_type<float, long double>::type>    operator*(const float val,    const Matrix<long double>&);

template Matrix<std::common_type<double, int>::type>       operator*(const double val,    const Matrix<int>&);
template Matrix<std::common_type<double, float>::type>     operator*(const double val,    const Matrix<float>&);
template Matrix<std::common_type<double, double>::type>    operator*(const double val,    const Matrix<double>&);
template Matrix<std::common_type<double, long double>::type>    operator*(const double val,    const Matrix<long double>&);

template Matrix<std::common_type<long double, int>::type>       operator*(const long double val,    const Matrix<int>&);
template Matrix<std::common_type<long double, float>::type>     operator*(const long double val,    const Matrix<float>&);
template Matrix<std::common_type<long double, double>::type>    operator*(const long double val,    const Matrix<double>&);
template Matrix<std::common_type<long double, long double>::type>    operator*(const long double val,    const Matrix<long double>&);

//Division broadcasters
template Matrix<std::common_type<int, int>::type> Matrix<int>::operator/<int>(int) const;
template Matrix<std::common_type<int, float>::type> Matrix<int>::operator/<float>(float) const;
template Matrix<std::common_type<int, double>::type> Matrix<int>::operator/<double>(double) const;
template Matrix<std::common_type<int, long double>::type> Matrix<int>::operator/<long double>(long double) const;

template Matrix<std::common_type<float, int>::type> Matrix<float>::operator/<int>(int) const;
template Matrix<std::common_type<float, float>::type> Matrix<float>::operator/<float>(float) const;
template Matrix<std::common_type<float, double>::type> Matrix<float>::operator/<double>(double) const;
template Matrix<std::common_type<float, long double>::type> Matrix<float>::operator/<long double>(long double) const;

template Matrix<std::common_type<double, int>::type> Matrix<double>::operator/<int>(int) const;
template Matrix<std::common_type<double, float>::type> Matrix<double>::operator/<float>(float) const;
template Matrix<std::common_type<double, double>::type> Matrix<double>::operator/<double>(double) const;
template Matrix<std::common_type<double, long double>::type> Matrix<double>::operator/<long double>(long double) const;

template Matrix<std::common_type<long double, int>::type> Matrix<long double>::operator/<int>(int) const;
template Matrix<std::common_type<long double, float>::type> Matrix<long double>::operator/<float>(float) const;
template Matrix<std::common_type<long double, double>::type> Matrix<long double>::operator/<double>(double) const;
template Matrix<std::common_type<long double, long double>::type> Matrix<long double>::operator/<long double>(long double) const;\

// Matrix-Matrix multiplication
template Matrix<std::common_type<int, int>::type> Matrix<int>::multiply<int>(Matrix<int> const&) const;
template Matrix<std::common_type<int, float>::type> Matrix<int>::multiply<float>(Matrix<float> const&) const;
template Matrix<std::common_type<int, double>::type> Matrix<int>::multiply<double>(Matrix<double> const&) const;
template Matrix<std::common_type<int, long double>::type> Matrix<int>::multiply<long double>(Matrix<long double> const&) const;

template Matrix<std::common_type<float, float>::type> Matrix<float>::multiply<float>(Matrix<float> const&) const;
template Matrix<std::common_type<float, int>::type> Matrix<float>::multiply<int>(Matrix<int> const&) const;
template Matrix<std::common_type<float, double>::type> Matrix<float>::multiply<double>(Matrix<double> const&) const;
template Matrix<std::common_type<float, long double>::type> Matrix<float>::multiply<long double>(Matrix<long double> const&) const;

template Matrix<std::common_type<double, int>::type> Matrix<double>::multiply<int>(Matrix<int> const&) const;
template Matrix<std::common_type<double, float>::type> Matrix<double>::multiply<float>(Matrix<float> const&) const;
template Matrix<std::common_type<double, double>::type> Matrix<double>::multiply<double>(Matrix<double> const&) const;
template Matrix<std::common_type<double, long double>::type> Matrix<double>::multiply<long double>(Matrix<long double> const&) const;

template Matrix<std::common_type<long double, int>::type> Matrix<long double>::multiply<int>(Matrix<int> const&) const;
template Matrix<std::common_type<long double, float>::type> Matrix<long double>::multiply<float>(Matrix<float> const&) const;
template Matrix<std::common_type<long double, double>::type> Matrix<long double>::multiply<double>(Matrix<double> const&) const;
template Matrix<std::common_type<long double, long double>::type> Matrix<long double>::multiply<long double>(Matrix<long double> const&) const;

//operator* for Matrix-Vector multiplication
template Vector::Vector<std::common_type<int, int>::type> Matrix<int>::operator*<int>(Vector::Vector<int> const&) const;
template Vector::Vector<std::common_type<int, float>::type> Matrix<int>::operator*<float>(Vector::Vector<float> const&) const;
template Vector::Vector<std::common_type<int, double>::type> Matrix<int>::operator*<double>(Vector::Vector<double> const&) const;
template Vector::Vector<std::common_type<int, long double>::type> Matrix<int>::operator*<long double>(Vector::Vector<long double> const&) const;

template Vector::Vector<std::common_type<float, int>::type> Matrix<float>::operator*<int>(Vector::Vector<int> const&) const;
template Vector::Vector<std::common_type<float, float>::type> Matrix<float>::operator*<float>(Vector::Vector<float> const&) const;
template Vector::Vector<std::common_type<float, double>::type> Matrix<float>::operator*<double>(Vector::Vector<double> const&) const;
template Vector::Vector<std::common_type<float, long double>::type> Matrix<float>::operator*<long double>(Vector::Vector<long double> const&) const;

template Vector::Vector<std::common_type<double, int>::type> Matrix<double>::operator*<int>(Vector::Vector<int> const&) const;
template Vector::Vector<std::common_type<double, float>::type> Matrix<double>::operator*<float>(Vector::Vector<float> const&) const;
template Vector::Vector<std::common_type<double, double>::type> Matrix<double>::operator*<double>(Vector::Vector<double> const&) const;
template Vector::Vector<std::common_type<double, long double>::type> Matrix<double>::operator*<long double>(Vector::Vector<long double> const&) const;

template Vector::Vector<std::common_type<long double, int>::type> Matrix<long double>::operator*<int>(Vector::Vector<int> const&) const;
template Vector::Vector<std::common_type<long double, float>::type> Matrix<long double>::operator*<float>(Vector::Vector<float> const&) const;
template Vector::Vector<std::common_type<long double, double>::type> Matrix<long double>::operator*<double>(Vector::Vector<double> const&) const;
template Vector::Vector<std::common_type<long double, long double>::type> Matrix<long double>::operator*<long double>(Vector::Vector<long double> const&) const;
#endif //LINEARALGEBRATOOLBOX_MATRIXEXPLICITTEMPLATEINSTANTIATIONS_HPP
