//
// Created by dorian on 18.12.2023.
//

#ifndef LINEARALGEBRATOOLBOX_MATRIXEXPLICITTEMPLATEINSTANTIATIONS_HPP
#define LINEARALGEBRATOOLBOX_MATRIXEXPLICITTEMPLATEINSTANTIATIONS_HPP

template class Matrix<int>;
template class Matrix<float>;
template class Matrix<double>;
template class Matrix<long double>;
template class Matrix<std::complex<int>>;
template class Matrix<std::complex<float>>;
template class Matrix<std::complex<double>>;
template class Matrix<std::complex<long double>>;

// Matrix<int> + Other types
template Matrix<std::common_type<int, int>::type> Matrix<int>::operator+<int>(Matrix<int> const&) const;
template Matrix<std::common_type<int, float>::type> Matrix<int>::operator+<float>(Matrix<float> const&) const;
template Matrix<std::common_type<int, double>::type> Matrix<int>::operator+<double>(Matrix<double> const&) const;
template Matrix<std::common_type<int, long double>::type> Matrix<int>::operator+<long double>(Matrix<long double> const&) const;

template Matrix<std::complex<std::common_type<int, int>::type>> Matrix<int>::operator+<int>(Matrix<std::complex<int>> const&) const;
template Matrix<std::complex<std::common_type<int, float>::type>> Matrix<int>::operator+<float>(Matrix<std::complex<float>> const&) const;
template Matrix<std::complex<std::common_type<int, double>::type>> Matrix<int>::operator+<double>(Matrix<std::complex<double>> const&) const;
template Matrix<std::complex<std::common_type<int, long double>::type>> Matrix<int>::operator+<long double>(Matrix<std::complex<long double>> const&) const;

// Matrix<float> + Other types
template Matrix<std::common_type<float, float>::type> Matrix<float>::operator+<float>(Matrix<float> const&) const;
template Matrix<std::common_type<float, int>::type> Matrix<float>::operator+<int>(Matrix<int> const&) const;
template Matrix<std::common_type<float, double>::type> Matrix<float>::operator+<double>(Matrix<double> const&) const;
template Matrix<std::common_type<float, long double>::type> Matrix<float>::operator+<long double>(Matrix<long double> const&) const;

template Matrix<std::complex<std::common_type<float, int>::type>> Matrix<float>::operator+<int>(Matrix<std::complex<int>> const&) const;
template Matrix<std::complex<std::common_type<float, float>::type>> Matrix<float>::operator+<float>(Matrix<std::complex<float>> const&) const;
template Matrix<std::complex<std::common_type<float, double>::type>> Matrix<float>::operator+<double>(Matrix<std::complex<double>> const&) const;
template Matrix<std::complex<std::common_type<float, long double>::type>> Matrix<float>::operator+<long double>(Matrix<std::complex<long double>> const&) const;

// Matrix<double> + Other types
template Matrix<std::common_type<double, int>::type> Matrix<double>::operator+<int>(Matrix<int> const&) const;
template Matrix<std::common_type<double, float>::type> Matrix<double>::operator+<float>(Matrix<float> const&) const;
template Matrix<std::common_type<double, double>::type> Matrix<double>::operator+<double>(Matrix<double> const&) const;
template Matrix<std::common_type<double, long double>::type> Matrix<double>::operator+<long double>(Matrix<long double> const&) const;

template Matrix<std::complex<std::common_type<double, int>::type>> Matrix<double>::operator+<int>(Matrix<std::complex<int>> const&) const;
template Matrix<std::complex<std::common_type<double, float>::type>> Matrix<double>::operator+<float>(Matrix<std::complex<float>> const&) const;
template Matrix<std::complex<std::common_type<double, double>::type>> Matrix<double>::operator+<double>(Matrix<std::complex<double>> const&) const;
template Matrix<std::complex<std::common_type<double, long double>::type>> Matrix<double>::operator+<long double>(Matrix<std::complex<long double>> const&) const;

// Matrix<long double> + Other types
template Matrix<std::common_type<long double, int>::type> Matrix<long double>::operator+<int>(Matrix<int> const&) const;
template Matrix<std::common_type<long double, float>::type> Matrix<long double>::operator+<float>(Matrix<float> const&) const;
template Matrix<std::common_type<long double, double>::type> Matrix<long double>::operator+<double>(Matrix<double> const&) const;
template Matrix<std::common_type<long double, long double>::type> Matrix<long double>::operator+<long double>(Matrix<long double> const&) const;

template Matrix<std::complex<std::common_type<long double, int>::type>> Matrix<long double>::operator+<int>(Matrix<std::complex<int>> const&) const;
template Matrix<std::complex<std::common_type<long double, float>::type>> Matrix<long double>::operator+<float>(Matrix<std::complex<float>> const&) const;
template Matrix<std::complex<std::common_type<long double, double>::type>> Matrix<long double>::operator+<double>(Matrix<std::complex<double>> const&) const;
template Matrix<std::complex<std::common_type<long double, long double>::type>> Matrix<long double>::operator+<long double>(Matrix<std::complex<long double>> const&) const;

// Matrix<complex<int>> + other types
template Matrix<std::complex<typename std::common_type<int,int>::type>> Matrix<std::complex<int>>::operator+<int>(const Matrix<int>& other) const;
template Matrix<std::complex<typename std::common_type<int,float>::type>> Matrix<std::complex<int>>::operator+<float>(const Matrix<float>& other) const;
template Matrix<std::complex<typename std::common_type<int,double>::type>> Matrix<std::complex<int>>::operator+<double>(const Matrix<double>& other) const;
template Matrix<std::complex<typename std::common_type<int,long double>::type>> Matrix<std::complex<int>>::operator+<long double>(const Matrix<long double>& other) const;

template Matrix<std::complex<typename std::common_type<int,int>::type>> Matrix<std::complex<int>>::operator+<int>(const Matrix<std::complex<int>>& other) const;
template Matrix<std::complex<typename std::common_type<int,float>::type>> Matrix<std::complex<int>>::operator+<float>(const Matrix<std::complex<float>>& other) const;
template Matrix<std::complex<typename std::common_type<int,double>::type>> Matrix<std::complex<int>>::operator+<double>(const Matrix<std::complex<double>>& other) const;
template Matrix<std::complex<typename std::common_type<int,long double>::type>> Matrix<std::complex<int>>::operator+<long double>(const Matrix<std::complex<long double>>& other) const;

// Matrix<complex<float>> + other types
template Matrix<std::complex<typename std::common_type<float,int>::type>> Matrix<std::complex<float>>::operator+<int>(const Matrix<int>& other) const;
template Matrix<std::complex<typename std::common_type<float,float>::type>> Matrix<std::complex<float>>::operator+<float>(const Matrix<float>& other) const;
template Matrix<std::complex<typename std::common_type<float,double>::type>> Matrix<std::complex<float>>::operator+<double>(const Matrix<double>& other) const;
template Matrix<std::complex<typename std::common_type<float,long double>::type>> Matrix<std::complex<float>>::operator+<long double>(const Matrix<long double>& other) const;

template Matrix<std::complex<typename std::common_type<float,int>::type>> Matrix<std::complex<float>>::operator+<int>(const Matrix<std::complex<int>>& other) const;
template Matrix<std::complex<typename std::common_type<float,float>::type>> Matrix<std::complex<float>>::operator+<float>(const Matrix<std::complex<float>>& other) const;
template Matrix<std::complex<typename std::common_type<float,double>::type>> Matrix<std::complex<float>>::operator+<double>(const Matrix<std::complex<double>>& other) const;
template Matrix<std::complex<typename std::common_type<float,long double>::type>> Matrix<std::complex<float>>::operator+<long double>(const Matrix<std::complex<long double>>& other) const;

// Matrix<complex<double>> + other types
template Matrix<std::complex<typename std::common_type<double,int>::type>> Matrix<std::complex<double>>::operator+<int>(const Matrix<int>& other) const;
template Matrix<std::complex<typename std::common_type<double,float>::type>> Matrix<std::complex<double>>::operator+<float>(const Matrix<float>& other) const;
template Matrix<std::complex<typename std::common_type<double,double>::type>> Matrix<std::complex<double>>::operator+<double>(const Matrix<double>& other) const;
template Matrix<std::complex<typename std::common_type<double,long double>::type>> Matrix<std::complex<double>>::operator+<long double>(const Matrix<long double>& other) const;

template Matrix<std::complex<typename std::common_type<double,int>::type>> Matrix<std::complex<double>>::operator+<int>(const Matrix<std::complex<int>>& other) const;
template Matrix<std::complex<typename std::common_type<double,float>::type>> Matrix<std::complex<double>>::operator+<float>(const Matrix<std::complex<float>>& other) const;
template Matrix<std::complex<typename std::common_type<double,double>::type>> Matrix<std::complex<double>>::operator+<double>(const Matrix<std::complex<double>>& other) const;
template Matrix<std::complex<typename std::common_type<double,long double>::type>> Matrix<std::complex<double>>::operator+<long double>(const Matrix<std::complex<long double>>& other) const;

// Matrix<complex<long double>> + other types
template Matrix<std::complex<typename std::common_type<long double,int>::type>> Matrix<std::complex<long double>>::operator+<int>(const Matrix<int>& other) const;
template Matrix<std::complex<typename std::common_type<long double,float>::type>> Matrix<std::complex<long double>>::operator+<float>(const Matrix<float>& other) const;
template Matrix<std::complex<typename std::common_type<long double,double>::type>> Matrix<std::complex<long double>>::operator+<double>(const Matrix<double>& other) const;
template Matrix<std::complex<typename std::common_type<long double,long double>::type>> Matrix<std::complex<long double>>::operator+<long double>(const Matrix<long double>& other) const;

template Matrix<std::complex<typename std::common_type<long double,int>::type>> Matrix<std::complex<long double>>::operator+<int>(const Matrix<std::complex<int>>& other) const;
template Matrix<std::complex<typename std::common_type<long double,float>::type>> Matrix<std::complex<long double>>::operator+<float>(const Matrix<std::complex<float>>& other) const;
template Matrix<std::complex<typename std::common_type<long double,double>::type>> Matrix<std::complex<long double>>::operator+<double>(const Matrix<std::complex<double>>& other) const;
template Matrix<std::complex<typename std::common_type<long double,long double>::type>> Matrix<std::complex<long double>>::operator+<long double>(const Matrix<std::complex<long double>>& other) const;

// Matrix<int> - other types
template Matrix<std::common_type<int, int>::type> Matrix<int>::operator-<int>(Matrix<int> const&) const;
template Matrix<std::common_type<int, float>::type> Matrix<int>::operator-<float>(Matrix<float> const&) const;
template Matrix<std::common_type<int, double>::type> Matrix<int>::operator-<double>(Matrix<double> const&) const;
template Matrix<std::common_type<int, long double>::type> Matrix<int>::operator-<long double>(Matrix<long double> const&) const;

template Matrix<std::complex<std::common_type<int, int>::type>> Matrix<int>::operator-<int>(Matrix<std::complex<int>> const&) const;
template Matrix<std::complex<std::common_type<int, float>::type>> Matrix<int>::operator-<float>(Matrix<std::complex<float>> const&) const;
template Matrix<std::complex<std::common_type<int, double>::type>> Matrix<int>::operator-<double>(Matrix<std::complex<double>> const&) const;
template Matrix<std::complex<std::common_type<int, long double>::type>> Matrix<int>::operator-<long double>(Matrix<std::complex<long double>> const&) const;

// Matrix<float> - other types
template Matrix<std::common_type<float, int>::type> Matrix<float>::operator-<int>(Matrix<int> const&) const;
template Matrix<std::common_type<float, float>::type> Matrix<float>::operator-<float>(Matrix<float> const&) const;
template Matrix<std::common_type<float, double>::type> Matrix<float>::operator-<double>(Matrix<double> const&) const;
template Matrix<std::common_type<float, long double>::type> Matrix<float>::operator-<long double>(Matrix<long double> const&) const;

template Matrix<std::complex<std::common_type<float, int>::type>> Matrix<float>::operator-<int>(Matrix<std::complex<int>> const&) const;
template Matrix<std::complex<std::common_type<float, float>::type>> Matrix<float>::operator-<float>(Matrix<std::complex<float>> const&) const;
template Matrix<std::complex<std::common_type<float, double>::type>> Matrix<float>::operator-<double>(Matrix<std::complex<double>> const&) const;
template Matrix<std::complex<std::common_type<float, long double>::type>> Matrix<float>::operator-<long double>(Matrix<std::complex<long double>> const&) const;

// Matrix<double> - other types
template Matrix<std::common_type<double, int>::type> Matrix<double>::operator-<int>(Matrix<int> const&) const;
template Matrix<std::common_type<double, float>::type> Matrix<double>::operator-<float>(Matrix<float> const&) const;
template Matrix<std::common_type<double, double>::type> Matrix<double>::operator-<double>(Matrix<double> const&) const;
template Matrix<std::common_type<double, long double>::type> Matrix<double>::operator-<long double>(Matrix<long double> const&) const;

template Matrix<std::complex<std::common_type<double, int>::type>> Matrix<double>::operator-<int>(Matrix<std::complex<int>> const&) const;
template Matrix<std::complex<std::common_type<double, float>::type>> Matrix<double>::operator-<float>(Matrix<std::complex<float>> const&) const;
template Matrix<std::complex<std::common_type<double, double>::type>> Matrix<double>::operator-<double>(Matrix<std::complex<double>> const&) const;
template Matrix<std::complex<std::common_type<double, long double>::type>> Matrix<double>::operator-<long double>(Matrix<std::complex<long double>> const&) const;

// Matrix<long double> - other types
template Matrix<std::common_type<long double, int>::type> Matrix<long double>::operator-<int>(Matrix<int> const&) const;
template Matrix<std::common_type<long double, float>::type> Matrix<long double>::operator-<float>(Matrix<float> const&) const;
template Matrix<std::common_type<long double, double>::type> Matrix<long double>::operator-<double>(Matrix<double> const&) const;
template Matrix<std::common_type<long double, long double>::type> Matrix<long double>::operator-<long double>(Matrix<long double> const&) const;

template Matrix<std::complex<std::common_type<long double, int>::type>> Matrix<long double>::operator-<int>(Matrix<std::complex<int>> const&) const;
template Matrix<std::complex<std::common_type<long double, float>::type>> Matrix<long double>::operator-<float>(Matrix<std::complex<float>> const&) const;
template Matrix<std::complex<std::common_type<long double, double>::type>> Matrix<long double>::operator-<double>(Matrix<std::complex<double>> const&) const;
template Matrix<std::complex<std::common_type<long double, long double>::type>> Matrix<long double>::operator-<long double>(Matrix<std::complex<long double>> const&) const;

// Matrix<complex<int>> - other types
template Matrix<std::complex<typename std::common_type<int,int>::type>> Matrix<std::complex<int>>::operator-<int>(const Matrix<int>& other) const;
template Matrix<std::complex<typename std::common_type<int,float>::type>> Matrix<std::complex<int>>::operator-<float>(const Matrix<float>& other) const;
template Matrix<std::complex<typename std::common_type<int,double>::type>> Matrix<std::complex<int>>::operator-<double>(const Matrix<double>& other) const;
template Matrix<std::complex<typename std::common_type<int,long double>::type>> Matrix<std::complex<int>>::operator-<long double>(const Matrix<long double>& other) const;

template Matrix<std::complex<typename std::common_type<int,int>::type>> Matrix<std::complex<int>>::operator-<int>(const Matrix<std::complex<int>>& other) const;
template Matrix<std::complex<typename std::common_type<int,float>::type>> Matrix<std::complex<int>>::operator-<float>(const Matrix<std::complex<float>>& other) const;
template Matrix<std::complex<typename std::common_type<int,double>::type>> Matrix<std::complex<int>>::operator-<double>(const Matrix<std::complex<double>>& other) const;
template Matrix<std::complex<typename std::common_type<int,long double>::type>> Matrix<std::complex<int>>::operator-<long double>(const Matrix<std::complex<long double>>& other) const;

// Matrix<complex<float>> - other types
template Matrix<std::complex<typename std::common_type<float,int>::type>> Matrix<std::complex<float>>::operator-<int>(const Matrix<int>& other) const;
template Matrix<std::complex<typename std::common_type<float,float>::type>> Matrix<std::complex<float>>::operator-<float>(const Matrix<float>& other) const;
template Matrix<std::complex<typename std::common_type<float,double>::type>> Matrix<std::complex<float>>::operator-<double>(const Matrix<double>& other) const;
template Matrix<std::complex<typename std::common_type<float,long double>::type>> Matrix<std::complex<float>>::operator-<long double>(const Matrix<long double>& other) const;

template Matrix<std::complex<typename std::common_type<float,int>::type>> Matrix<std::complex<float>>::operator-<int>(const Matrix<std::complex<int>>& other) const;
template Matrix<std::complex<typename std::common_type<float,float>::type>> Matrix<std::complex<float>>::operator-<float>(const Matrix<std::complex<float>>& other) const;
template Matrix<std::complex<typename std::common_type<float,double>::type>> Matrix<std::complex<float>>::operator-<double>(const Matrix<std::complex<double>>& other) const;
template Matrix<std::complex<typename std::common_type<float,long double>::type>> Matrix<std::complex<float>>::operator-<long double>(const Matrix<std::complex<long double>>& other) const;

// Matrix<complex<double>> - other types
template Matrix<std::complex<typename std::common_type<double,int>::type>> Matrix<std::complex<double>>::operator-<int>(const Matrix<int>& other) const;
template Matrix<std::complex<typename std::common_type<double,float>::type>> Matrix<std::complex<double>>::operator-<float>(const Matrix<float>& other) const;
template Matrix<std::complex<typename std::common_type<double,double>::type>> Matrix<std::complex<double>>::operator-<double>(const Matrix<double>& other) const;
template Matrix<std::complex<typename std::common_type<double,long double>::type>> Matrix<std::complex<double>>::operator-<long double>(const Matrix<long double>& other) const;

template Matrix<std::complex<typename std::common_type<double,int>::type>> Matrix<std::complex<double>>::operator-<int>(const Matrix<std::complex<int>>& other) const;
template Matrix<std::complex<typename std::common_type<double,float>::type>> Matrix<std::complex<double>>::operator-<float>(const Matrix<std::complex<float>>& other) const;
template Matrix<std::complex<typename std::common_type<double,double>::type>> Matrix<std::complex<double>>::operator-<double>(const Matrix<std::complex<double>>& other) const;
template Matrix<std::complex<typename std::common_type<double,long double>::type>> Matrix<std::complex<double>>::operator-<long double>(const Matrix<std::complex<long double>>& other) const;

// Matrix<complex<long double>> - other types
template Matrix<std::complex<typename std::common_type<long double,int>::type>> Matrix<std::complex<long double>>::operator-<int>(const Matrix<int>& other) const;
template Matrix<std::complex<typename std::common_type<long double,float>::type>> Matrix<std::complex<long double>>::operator-<float>(const Matrix<float>& other) const;
template Matrix<std::complex<typename std::common_type<long double,double>::type>> Matrix<std::complex<long double>>::operator-<double>(const Matrix<double>& other) const;
template Matrix<std::complex<typename std::common_type<long double,long double>::type>> Matrix<std::complex<long double>>::operator-<long double>(const Matrix<long double>& other) const;

template Matrix<std::complex<typename std::common_type<long double,int>::type>> Matrix<std::complex<long double>>::operator-<int>(const Matrix<std::complex<int>>& other) const;
template Matrix<std::complex<typename std::common_type<long double,float>::type>> Matrix<std::complex<long double>>::operator-<float>(const Matrix<std::complex<float>>& other) const;
template Matrix<std::complex<typename std::common_type<long double,double>::type>> Matrix<std::complex<long double>>::operator-<double>(const Matrix<std::complex<double>>& other) const;
template Matrix<std::complex<typename std::common_type<long double, long double>::type>> Matrix<std::complex<long double>>::operator-<long double>(const Matrix<std::complex<long double>>& other) const;

//operator* for matrix-matrix multiplication
// Matrix<int>
template Matrix<std::common_type<int, int>::type> Matrix<int>::operator*<int>(Matrix<int> const&) const;
template Matrix<std::common_type<int, float>::type> Matrix<int>::operator*<float>(Matrix<float> const&) const;
template Matrix<std::common_type<int, double>::type> Matrix<int>::operator*<double>(Matrix<double> const&) const;
template Matrix<std::common_type<int, long double>::type> Matrix<int>::operator*<long double>(Matrix<long double> const&) const;

template Matrix<std::complex<typename std::common_type<int,int>::type>> Matrix<int>::operator*<int>(Matrix<std::complex<int>> const&) const;
template Matrix<std::complex<typename std::common_type<int,float>::type>> Matrix<int>::operator*<float>(Matrix<std::complex<float>> const&) const;
template Matrix<std::complex<typename std::common_type<int,double>::type>> Matrix<int>::operator*<double>(Matrix<std::complex<double>> const&) const;
template Matrix<std::complex<typename std::common_type<int,long double>::type>> Matrix<int>::operator*<long double>(Matrix<std::complex<long double>> const&) const;

// Matrix<float>
template Matrix<std::common_type<float, int>::type> Matrix<float>::operator*<int>(Matrix<int> const&) const;
template Matrix<std::common_type<float, float>::type> Matrix<float>::operator*<float>(Matrix<float> const&) const;
template Matrix<std::common_type<float, double>::type> Matrix<float>::operator*<double>(Matrix<double> const&) const;
template Matrix<std::common_type<float, long double>::type> Matrix<float>::operator*<long double>(Matrix<long double> const&) const;

template Matrix<std::complex<typename std::common_type<float,int>::type>> Matrix<float>::operator*<int>(Matrix<std::complex<int>> const&) const;
template Matrix<std::complex<typename std::common_type<float,float>::type>> Matrix<float>::operator*<float>(Matrix<std::complex<float>> const&) const;
template Matrix<std::complex<typename std::common_type<float,double>::type>> Matrix<float>::operator*<double>(Matrix<std::complex<double>> const&) const;
template Matrix<std::complex<typename std::common_type<float,long double>::type>> Matrix<float>::operator*<long double>(Matrix<std::complex<long double>> const&) const;

// Matrix<double>
template Matrix<std::common_type<double, int>::type> Matrix<double>::operator*<int>(Matrix<int> const&) const;
template Matrix<std::common_type<double, float>::type> Matrix<double>::operator*<float>(Matrix<float> const&) const;
template Matrix<std::common_type<double, double>::type> Matrix<double>::operator*<double>(Matrix<double> const&) const;
template Matrix<std::common_type<double, long double>::type> Matrix<double>::operator*<long double>(Matrix<long double> const&) const;

template Matrix<std::complex<typename std::common_type<double,int>::type>> Matrix<double>::operator*<int>(Matrix<std::complex<int>> const&) const;
template Matrix<std::complex<typename std::common_type<double,float>::type>> Matrix<double>::operator*<float>(Matrix<std::complex<float>> const&) const;
template Matrix<std::complex<typename std::common_type<double,double>::type>> Matrix<double>::operator*<double>(Matrix<std::complex<double>> const&) const;
template Matrix<std::complex<typename std::common_type<double,long double>::type>> Matrix<double>::operator*<long double>(Matrix<std::complex<long double>> const&) const;

// Matrix<long double>
template Matrix<std::common_type<long double, int>::type> Matrix<long double>::operator*<int>(Matrix<int> const&) const;
template Matrix<std::common_type<long double, float>::type> Matrix<long double>::operator*<float>(Matrix<float> const&) const;
template Matrix<std::common_type<long double, double>::type> Matrix<long double>::operator*<double>(Matrix<double> const&) const;
template Matrix<std::common_type<long double, long double>::type> Matrix<long double>::operator*<long double>(Matrix<long double> const&) const;

template Matrix<std::complex<typename std::common_type<long double,int>::type>> Matrix<long double>::operator*<int>(Matrix<std::complex<int>> const&) const;
template Matrix<std::complex<typename std::common_type<long double,float>::type>> Matrix<long double>::operator*<float>(Matrix<std::complex<float>> const&) const;
template Matrix<std::complex<typename std::common_type<long double,double>::type>> Matrix<long double>::operator*<double>(Matrix<std::complex<double>> const&) const;
template Matrix<std::complex<typename std::common_type<long double,long double>::type>> Matrix<long double>::operator*<long double>(Matrix<std::complex<long double>> const&) const;

// Matrix<std::complex<int>>
template Matrix<std::complex<typename std::common_type<int,int>::type>> Matrix<std::complex<int>>::operator*<int>(Matrix<int> const&) const;
template Matrix<std::complex<typename std::common_type<int,float>::type>> Matrix<std::complex<int>>::operator*<float>(Matrix<float> const&) const;
template Matrix<std::complex<typename std::common_type<int,double>::type>> Matrix<std::complex<int>>::operator*<double>(Matrix<double> const&) const;
template Matrix<std::complex<typename std::common_type<int, long double>::type>> Matrix<std::complex<int>>::operator*<long double>(Matrix<long double> const&) const;

template Matrix<std::complex<typename std::common_type<int,int>::type>> Matrix<std::complex<int>>::operator*<int>(Matrix<std::complex<int>> const&) const;
template Matrix<std::complex<typename std::common_type<int,float>::type>> Matrix<std::complex<int>>::operator*<float>(Matrix<std::complex<float>> const&) const;
template Matrix<std::complex<typename std::common_type<int,double>::type>> Matrix<std::complex<int>>::operator*<double>(Matrix<std::complex<double>> const&) const;
template Matrix<std::complex<typename std::common_type<int,long double>::type>> Matrix<std::complex<int>>::operator*<long double>(Matrix<std::complex<long double>> const&) const;

// Matrix<std::complex<float>>
template Matrix<std::complex<typename std::common_type<float,int>::type>> Matrix<std::complex<float>>::operator*<int>(Matrix<int> const&) const;
template Matrix<std::complex<typename std::common_type<float,float>::type>> Matrix<std::complex<float>>::operator*<float>(Matrix<float> const&) const;
template Matrix<std::complex<typename std::common_type<float,double>::type>> Matrix<std::complex<float>>::operator*<double>(Matrix<double> const&) const;
template Matrix<std::complex<typename std::common_type<float,long double>::type>> Matrix<std::complex<float>>::operator*<long double>(Matrix<long double> const&) const;

template Matrix<std::complex<typename std::common_type<float,int>::type>> Matrix<std::complex<float>>::operator*<int>(Matrix<std::complex<int>> const&) const;
template Matrix<std::complex<typename std::common_type<float,float>::type>> Matrix<std::complex<float>>::operator*<float>(Matrix<std::complex<float>> const&) const;
template Matrix<std::complex<typename std::common_type<float,double>::type>> Matrix<std::complex<float>>::operator*<double>(Matrix<std::complex<double>> const&) const;
template Matrix<std::complex<typename std::common_type<float,long double>::type>> Matrix<std::complex<float>>::operator*<long double>(Matrix<std::complex<long double>> const&) const;

// Matrix<std::complex<double>>
template Matrix<std::complex<typename std::common_type<double,int>::type>> Matrix<std::complex<double>>::operator*<int>(Matrix<int> const&) const;
template Matrix<std::complex<typename std::common_type<double,float>::type>> Matrix<std::complex<double>>::operator*<float>(Matrix<float> const&) const;
template Matrix<std::complex<typename std::common_type<double,double>::type>> Matrix<std::complex<double>>::operator*<double>(Matrix<double> const&) const;
template Matrix<std::complex<typename std::common_type<double,long double>::type>> Matrix<std::complex<double>>::operator*<long double>(Matrix<long double> const&) const;

template Matrix<std::complex<typename std::common_type<double,int>::type>> Matrix<std::complex<double>>::operator*<int>(Matrix<std::complex<int>> const&) const;
template Matrix<std::complex<typename std::common_type<double,float>::type>> Matrix<std::complex<double>>::operator*<float>(Matrix<std::complex<float>> const&) const;
template Matrix<std::complex<typename std::common_type<double,double>::type>> Matrix<std::complex<double>>::operator*<double>(Matrix<std::complex<double>> const&) const;
template Matrix<std::complex<typename std::common_type<double,long double>::type>> Matrix<std::complex<double>>::operator*<long double>(Matrix<std::complex<long double>> const&) const;

// Matrix<std::complex<long double>>
template Matrix<std::complex<typename std::common_type<long double,int>::type>> Matrix<std::complex<long double>>::operator*<int>(Matrix<int> const&) const;
template Matrix<std::complex<typename std::common_type<long double,float>::type>> Matrix<std::complex<long double>>::operator*<float>(Matrix<float> const&) const;
template Matrix<std::complex<typename std::common_type<long double,double>::type>> Matrix<std::complex<long double>>::operator*<double>(Matrix<double> const&) const;
template Matrix<std::complex<typename std::common_type<long double,long double>::type>> Matrix<std::complex<long double>>::operator*<long double>(Matrix<long double> const&) const;

template Matrix<std::complex<typename std::common_type<long double,int>::type>> Matrix<std::complex<long double>>::operator*<int>(Matrix<std::complex<int>> const&) const;
template Matrix<std::complex<typename std::common_type<long double,float>::type>> Matrix<std::complex<long double>>::operator*<float>(Matrix<std::complex<float>> const&) const;
template Matrix<std::complex<typename std::common_type<long double,double>::type>> Matrix<std::complex<long double>>::operator*<double>(Matrix<std::complex<double>> const&) const;
template Matrix<std::complex<typename std::common_type<long double,long double>::type>> Matrix<std::complex<long double>>::operator*<long double>(Matrix<std::complex<long double>> const&) const;

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


//operator* for Matrix-Vector multiplication

//Matrix<int> * vector
template Vector::Vector<std::common_type<int, int>::type> Matrix<int>::operator*<int>(Vector::Vector<int> const&) const;
template Vector::Vector<std::common_type<int, float>::type> Matrix<int>::operator*<float>(Vector::Vector<float> const&) const;
template Vector::Vector<std::common_type<int, double>::type> Matrix<int>::operator*<double>(Vector::Vector<double> const&) const;
template Vector::Vector<std::common_type<int, long double>::type> Matrix<int>::operator*<long double>(Vector::Vector<long double> const&) const;

template Vector::Vector<std::complex<typename std::common_type<int, int>::type>> Matrix<int>::operator*<int>(const Vector::Vector<std::complex<int>>& other) const;
template Vector::Vector<std::complex<typename std::common_type<int, float>::type>> Matrix<int>::operator*<float>(const Vector::Vector<std::complex<float>>& other) const;
template Vector::Vector<std::complex<typename std::common_type<int, double>::type>> Matrix<int>::operator*<double>(const Vector::Vector<std::complex<double>>& other) const;
template Vector::Vector<std::complex<typename std::common_type<int, long double>::type>> Matrix<int>::operator*<long double>(const Vector::Vector<std::complex<long double>>& other) const;

//Matrix<float> * vector
template Vector::Vector<std::common_type<float, int>::type> Matrix<float>::operator*<int>(Vector::Vector<int> const&) const;
template Vector::Vector<std::common_type<float, float>::type> Matrix<float>::operator*<float>(Vector::Vector<float> const&) const;
template Vector::Vector<std::common_type<float, double>::type> Matrix<float>::operator*<double>(Vector::Vector<double> const&) const;
template Vector::Vector<std::common_type<float, long double>::type> Matrix<float>::operator*<long double>(Vector::Vector<long double> const&) const;

template Vector::Vector<std::complex<typename std::common_type<float, int>::type>> Matrix<float>::operator*<int>(const Vector::Vector<std::complex<int>>& other) const;
template Vector::Vector<std::complex<typename std::common_type<float, float>::type>> Matrix<float>::operator*<float>(const Vector::Vector<std::complex<float>>& other) const;
template Vector::Vector<std::complex<typename std::common_type<float, double>::type>> Matrix<float>::operator*<double>(const Vector::Vector<std::complex<double>>& other) const;
template Vector::Vector<std::complex<typename std::common_type<float, long double>::type>> Matrix<float>::operator*<long double>(const Vector::Vector<std::complex<long double>>& other) const;

//Matrix<double> * vector
template Vector::Vector<std::common_type<double, int>::type> Matrix<double>::operator*<int>(Vector::Vector<int> const&) const;
template Vector::Vector<std::common_type<double, float>::type> Matrix<double>::operator*<float>(Vector::Vector<float> const&) const;
template Vector::Vector<std::common_type<double, double>::type> Matrix<double>::operator*<double>(Vector::Vector<double> const&) const;
template Vector::Vector<std::common_type<double, long double>::type> Matrix<double>::operator*<long double>(Vector::Vector<long double> const&) const;

template Vector::Vector<std::complex<typename std::common_type<double, int>::type>> Matrix<double>::operator*<int>(const Vector::Vector<std::complex<int>>& other) const;
template Vector::Vector<std::complex<typename std::common_type<double, float>::type>> Matrix<double>::operator*<float>(const Vector::Vector<std::complex<float>>& other) const;
template Vector::Vector<std::complex<typename std::common_type<double, double>::type>> Matrix<double>::operator*<double>(const Vector::Vector<std::complex<double>>& other) const;
template Vector::Vector<std::complex<typename std::common_type<double, long double>::type>> Matrix<double>::operator*<long double>(const Vector::Vector<std::complex<long double>>& other) const;

//Matrix<long double> * vector
template Vector::Vector<std::common_type<long double, int>::type> Matrix<long double>::operator*<int>(Vector::Vector<int> const&) const;
template Vector::Vector<std::common_type<long double, float>::type> Matrix<long double>::operator*<float>(Vector::Vector<float> const&) const;
template Vector::Vector<std::common_type<long double, double>::type> Matrix<long double>::operator*<double>(Vector::Vector<double> const&) const;
template Vector::Vector<std::common_type<long double, long double>::type> Matrix<long double>::operator*<long double>(Vector::Vector<long double> const&) const;

template Vector::Vector<std::complex<typename std::common_type<long double, int>::type>> Matrix<long double>::operator*<int>(const Vector::Vector<std::complex<int>>& other) const;
template Vector::Vector<std::complex<typename std::common_type<long double, float>::type>> Matrix<long double>::operator*<float>(const Vector::Vector<std::complex<float>>& other) const;
template Vector::Vector<std::complex<typename std::common_type<long double, double>::type>> Matrix<long double>::operator*<double>(const Vector::Vector<std::complex<double>>& other) const;
template Vector::Vector<std::complex<typename std::common_type<long double, long double>::type>> Matrix<long double>::operator*<long double>(const Vector::Vector<std::complex<long double>>& other) const;

//Matrix<std::complex<int>> * vector
template Vector::Vector<std::complex<typename std::common_type<int, int>::type>> Matrix<std::complex<int>>::operator*<int>(const Vector::Vector<int>& other) const;
template Vector::Vector<std::complex<typename std::common_type<int, float>::type>> Matrix<std::complex<int>>::operator*<float>(const Vector::Vector<float>& other) const;
template Vector::Vector<std::complex<typename std::common_type<int, double>::type>> Matrix<std::complex<int>>::operator*<double>(const Vector::Vector<double>& other) const;
template Vector::Vector<std::complex<typename std::common_type<int, long double>::type>> Matrix<std::complex<int>>::operator*<long double>(const Vector::Vector<long double>& other) const;

template Vector::Vector<std::complex<typename std::common_type<int, int>::type>> Matrix<std::complex<int>>::operator*<int>(const Vector::Vector<std::complex<int>>& other) const;
template Vector::Vector<std::complex<typename std::common_type<int, float>::type>> Matrix<std::complex<int>>::operator*<float>(const Vector::Vector<std::complex<float>>& other) const;
template Vector::Vector<std::complex<typename std::common_type<int, double>::type>> Matrix<std::complex<int>>::operator*<double>(const Vector::Vector<std::complex<double>>& other) const;
template Vector::Vector<std::complex<typename std::common_type<int, long double>::type>> Matrix<std::complex<int>>::operator*<long double>(const Vector::Vector<std::complex<long double>>& other) const;

//Matrix<std::complex<float>> * vector
template Vector::Vector<std::complex<typename std::common_type<float, int>::type>> Matrix<std::complex<float>>::operator*<int>(const Vector::Vector<int>& other) const;
template Vector::Vector<std::complex<typename std::common_type<float, float>::type>> Matrix<std::complex<float>>::operator*<float>(const Vector::Vector<float>& other) const;
template Vector::Vector<std::complex<typename std::common_type<float, double>::type>> Matrix<std::complex<float>>::operator*<double>(const Vector::Vector<double>& other) const;
template Vector::Vector<std::complex<typename std::common_type<float, long double>::type>> Matrix<std::complex<float>>::operator*<long double>(const Vector::Vector<long double>& other) const;

template Vector::Vector<std::complex<typename std::common_type<float, int>::type>> Matrix<std::complex<float>>::operator*<int>(const Vector::Vector<std::complex<int>>& other) const;
template Vector::Vector<std::complex<typename std::common_type<float, float>::type>> Matrix<std::complex<float>>::operator*<float>(const Vector::Vector<std::complex<float>>& other) const;
template Vector::Vector<std::complex<typename std::common_type<float, double>::type>> Matrix<std::complex<float>>::operator*<double>(const Vector::Vector<std::complex<double>>& other) const;
template Vector::Vector<std::complex<typename std::common_type<float, long double>::type>> Matrix<std::complex<float>>::operator*<long double>(const Vector::Vector<std::complex<long double>>& other) const;

//Matrix<std::complex<double>> * vector
template Vector::Vector<std::complex<typename std::common_type<double, int>::type>> Matrix<std::complex<double>>::operator*<int>(const Vector::Vector<int>& other) const;
template Vector::Vector<std::complex<typename std::common_type<double, float>::type>> Matrix<std::complex<double>>::operator*<float>(const Vector::Vector<float>& other) const;
template Vector::Vector<std::complex<typename std::common_type<double, double>::type>> Matrix<std::complex<double>>::operator*<double>(const Vector::Vector<double>& other) const;
template Vector::Vector<std::complex<typename std::common_type<double, long double>::type>> Matrix<std::complex<double>>::operator*<long double>(const Vector::Vector<long double>& other) const;

template Vector::Vector<std::complex<typename std::common_type<double, int>::type>> Matrix<std::complex<double>>::operator*<int>(const Vector::Vector<std::complex<int>>& other) const;
template Vector::Vector<std::complex<typename std::common_type<double, float>::type>> Matrix<std::complex<double>>::operator*<float>(const Vector::Vector<std::complex<float>>& other) const;
template Vector::Vector<std::complex<typename std::common_type<double, double>::type>> Matrix<std::complex<double>>::operator*<double>(const Vector::Vector<std::complex<double>>& other) const;
template Vector::Vector<std::complex<typename std::common_type<double, long double>::type>> Matrix<std::complex<double>>::operator*<long double>(const Vector::Vector<std::complex<long double>>& other) const;

//Matrix<std::complex<long double>> * vector
template Vector::Vector<std::complex<typename std::common_type<long double, int>::type>> Matrix<std::complex<long double>>::operator*<int>(const Vector::Vector<int>& other) const;
template Vector::Vector<std::complex<typename std::common_type<long double, float>::type>> Matrix<std::complex<long double>>::operator*<float>(const Vector::Vector<float>& other) const;
template Vector::Vector<std::complex<typename std::common_type<long double, double>::type>> Matrix<std::complex<long double>>::operator*<double>(const Vector::Vector<double>& other) const;
template Vector::Vector<std::complex<typename std::common_type<long double, long double>::type>> Matrix<std::complex<long double>>::operator*<long double>(const Vector::Vector<long double>& other) const;

template Vector::Vector<std::complex<typename std::common_type<long double, int>::type>> Matrix<std::complex<long double>>::operator*<int>(const Vector::Vector<std::complex<int>>& other) const;
template Vector::Vector<std::complex<typename std::common_type<long double, float>::type>> Matrix<std::complex<long double>>::operator*<float>(const Vector::Vector<std::complex<float>>& other) const;
template Vector::Vector<std::complex<typename std::common_type<long double, double>::type>> Matrix<std::complex<long double>>::operator*<double>(const Vector::Vector<std::complex<double>>& other) const;
template Vector::Vector<std::complex<typename std::common_type<long double, long double>::type>> Matrix<std::complex<long double>>::operator*<long double>(const Vector::Vector<std::complex<long double>>& other) const;
#endif //LINEARALGEBRATOOLBOX_MATRIXEXPLICITTEMPLATEINSTANTIATIONS_HPP
