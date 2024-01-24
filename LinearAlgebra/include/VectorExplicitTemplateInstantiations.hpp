//
// Created by dorian on 18.12.2023.
//

#ifndef LINEARALGEBRATOOLBOX_VECTOREXPLICITTEMPLATEINSTANTIATIONS_HPP
#define LINEARALGEBRATOOLBOX_VECTOREXPLICITTEMPLATEINSTANTIATIONS_HPP


template class Vector<int>;
template class Vector<float>;
template class Vector<double>;
template class Vector<long double>;
template class Vector<std::complex<int>>;
template class Vector<std::complex<float>>;
template class Vector<std::complex<double>>;
template class Vector<std::complex<long double>>;

//operator+

// Vector<int> + other Vector types
template Vector<std::common_type<int, int>::type> Vector<int>::operator+<int>(Vector<int> const&) const;
template Vector<std::common_type<int, float>::type> Vector<int>::operator+<float>(Vector<float> const&) const;
template Vector<std::common_type<int, double>::type> Vector<int>::operator+<double>(Vector<double> const&) const;
template Vector<std::common_type<int, long double>::type> Vector<int>::operator+<long double>(Vector<long double> const&) const;

template Vector<std::complex<std::common_type<int, int>::type>> Vector<int>::operator+<int>(Vector<std::complex<int>> const&) const;
template Vector<std::complex<std::common_type<int, float>::type>> Vector<int>::operator+<float>(Vector<std::complex<float>> const&) const;
template Vector<std::complex<std::common_type<int, double>::type>> Vector<int>::operator+<double>(Vector<std::complex<double>> const&) const;
template Vector<std::complex<std::common_type<int, long double>::type>> Vector<int>::operator+<long double>(Vector<std::complex<long double>> const&) const;

// Vector<float> + other Vector types
template Vector<std::common_type<float, int>::type> Vector<float>::operator+<int>(Vector<int> const&) const;
template Vector<std::common_type<float, float>::type> Vector<float>::operator+<float>(Vector<float> const&) const;
template Vector<std::common_type<float, double>::type> Vector<float>::operator+<double>(Vector<double> const&) const;
template Vector<std::common_type<float, long double>::type> Vector<float>::operator+<long double>(Vector<long double> const&) const;

template Vector<std::complex<std::common_type<float, int>::type>> Vector<float>::operator+<int>(Vector<std::complex<int>> const&) const;
template Vector<std::complex<std::common_type<float, float>::type>> Vector<float>::operator+<float>(Vector<std::complex<float>> const&) const;
template Vector<std::complex<std::common_type<float, double>::type>> Vector<float>::operator+<double>(Vector<std::complex<double>> const&) const;
template Vector<std::complex<std::common_type<float, long double>::type>> Vector<float>::operator+<long double>(Vector<std::complex<long double>> const&) const;

// Vector<double> + other Vector types
template Vector<std::common_type<double, int>::type> Vector<double>::operator+<int>(Vector<int> const&) const;
template Vector<std::common_type<double, float>::type> Vector<double>::operator+<float>(Vector<float> const&) const;
template Vector<std::common_type<double, double>::type> Vector<double>::operator+<double>(Vector<double> const&) const;
template Vector<std::common_type<double, long double>::type> Vector<double>::operator+<long double>(Vector<long double> const&) const;

template Vector<std::complex<std::common_type<double, int>::type>> Vector<double>::operator+<int>(Vector<std::complex<int>> const&) const;
template Vector<std::complex<std::common_type<double, float>::type>> Vector<double>::operator+<float>(Vector<std::complex<float>> const&) const;
template Vector<std::complex<std::common_type<double, double>::type>> Vector<double>::operator+<double>(Vector<std::complex<double>> const&) const;
template Vector<std::complex<std::common_type<double, long double>::type>> Vector<double>::operator+<long double>(Vector<std::complex<long double>> const&) const;

// Vector<long double> + other Vector types
template Vector<std::common_type<long double, int>::type> Vector<long double>::operator+<int>(Vector<int> const&) const;
template Vector<std::common_type<long double, float>::type> Vector<long double>::operator+<float>(Vector<float> const&) const;
template Vector<std::common_type<long double, double>::type> Vector<long double>::operator+<double>(Vector<double> const&) const;
template Vector<std::common_type<long double, long double>::type> Vector<long double>::operator+<long double>(Vector<long double> const&) const;

template Vector<std::complex<std::common_type<long double, int>::type>> Vector<long double>::operator+<int>(Vector<std::complex<int>> const&) const;
template Vector<std::complex<std::common_type<long double, float>::type>> Vector<long double>::operator+<float>(Vector<std::complex<float>> const&) const;
template Vector<std::complex<std::common_type<long double, double>::type>> Vector<long double>::operator+<double>(Vector<std::complex<double>> const&) const;
template Vector<std::complex<std::common_type<long double, long double>::type>> Vector<long double>::operator+<long double>(Vector<std::complex<long double>> const&) const;

// Vector<complex<int>> + other Vector types
template Vector<std::complex<typename std::common_type<int,int>::type>> Vector<std::complex<int>>::operator+<int>(const Vector<int>& other) const;
template Vector<std::complex<typename std::common_type<int,float>::type>> Vector<std::complex<int>>::operator+<float>(const Vector<float>& other) const;
template Vector<std::complex<typename std::common_type<int,double>::type>> Vector<std::complex<int>>::operator+<double>(const Vector<double>& other) const;
template Vector<std::complex<typename std::common_type<int,long double>::type>> Vector<std::complex<int>>::operator+<long double>(const Vector<long double>& other) const;

template Vector<std::complex<typename std::common_type<int,int>::type>> Vector<std::complex<int>>::operator+<int>(const Vector<std::complex<int>>& other) const;
template Vector<std::complex<typename std::common_type<int,float>::type>> Vector<std::complex<int>>::operator+<float>(const Vector<std::complex<float>>& other) const;
template Vector<std::complex<typename std::common_type<int,double>::type>> Vector<std::complex<int>>::operator+<double>(const Vector<std::complex<double>>& other) const;
template Vector<std::complex<typename std::common_type<int,long double>::type>> Vector<std::complex<int>>::operator+<long double>(const Vector<std::complex<long double>>& other) const;

// Vector<complex<float>> + other Vector types
template Vector<std::complex<typename std::common_type<float,int>::type>> Vector<std::complex<float>>::operator+<int>(const Vector<int>& other) const;
template Vector<std::complex<typename std::common_type<float,float>::type>> Vector<std::complex<float>>::operator+<float>(const Vector<float>& other) const;
template Vector<std::complex<typename std::common_type<float,double>::type>> Vector<std::complex<float>>::operator+<double>(const Vector<double>& other) const;
template Vector<std::complex<typename std::common_type<float,long double>::type>> Vector<std::complex<float>>::operator+<long double>(const Vector<long double>& other) const;

template Vector<std::complex<typename std::common_type<float,int>::type>> Vector<std::complex<float>>::operator+<int>(const Vector<std::complex<int>>& other) const;
template Vector<std::complex<typename std::common_type<float,float>::type>> Vector<std::complex<float>>::operator+<float>(const Vector<std::complex<float>>& other) const;
template Vector<std::complex<typename std::common_type<float,double>::type>> Vector<std::complex<float>>::operator+<double>(const Vector<std::complex<double>>& other) const;
template Vector<std::complex<typename std::common_type<float,long double>::type>> Vector<std::complex<float>>::operator+<long double>(const Vector<std::complex<long double>>& other) const;

// Vector<complex<double>> + other Vector types
template Vector<std::complex<typename std::common_type<double,int>::type>> Vector<std::complex<double>>::operator+<int>(const Vector<int>& other) const;
template Vector<std::complex<typename std::common_type<double,float>::type>> Vector<std::complex<double>>::operator+<float>(const Vector<float>& other) const;
template Vector<std::complex<typename std::common_type<double,double>::type>> Vector<std::complex<double>>::operator+<double>(const Vector<double>& other) const;
template Vector<std::complex<typename std::common_type<double,long double>::type>> Vector<std::complex<double>>::operator+<long double>(const Vector<long double>& other) const;

template Vector<std::complex<typename std::common_type<double,int>::type>> Vector<std::complex<double>>::operator+<int>(const Vector<std::complex<int>>& other) const;
template Vector<std::complex<typename std::common_type<double,float>::type>> Vector<std::complex<double>>::operator+<float>(const Vector<std::complex<float>>& other) const;
template Vector<std::complex<typename std::common_type<double,double>::type>> Vector<std::complex<double>>::operator+<double>(const Vector<std::complex<double>>& other) const;
template Vector<std::complex<typename std::common_type<double,long double>::type>> Vector<std::complex<double>>::operator+<long double>(const Vector<std::complex<long double>>& other) const;

// Vector<complex<long double>> + other Vector types
template Vector<std::complex<typename std::common_type<long double,int>::type>> Vector<std::complex<long double>>::operator+<int>(const Vector<int>& other) const;
template Vector<std::complex<typename std::common_type<long double,float>::type>> Vector<std::complex<long double>>::operator+<float>(const Vector<float>& other) const;
template Vector<std::complex<typename std::common_type<long double,double>::type>> Vector<std::complex<long double>>::operator+<double>(const Vector<double>& other) const;
template Vector<std::complex<typename std::common_type<long double,long double>::type>> Vector<std::complex<long double>>::operator+<long double>(const Vector<long double>& other) const;

template Vector<std::complex<typename std::common_type<long double,int>::type>> Vector<std::complex<long double>>::operator+<int>(const Vector<std::complex<int>>& other) const;
template Vector<std::complex<typename std::common_type<long double,float>::type>> Vector<std::complex<long double>>::operator+<float>(const Vector<std::complex<float>>& other) const;
template Vector<std::complex<typename std::common_type<long double,double>::type>> Vector<std::complex<long double>>::operator+<double>(const Vector<std::complex<double>>& other) const;
template Vector<std::complex<typename std::common_type<long double,long double>::type>> Vector<std::complex<long double>>::operator+<long double>(const Vector<std::complex<long double>>& other) const;


// Vector<int> - other Vector types
template Vector<std::common_type<int, int>::type> Vector<int>::operator-<int>(Vector<int> const&) const;
template Vector<std::common_type<int, float>::type> Vector<int>::operator-<float>(Vector<float> const&) const;
template Vector<std::common_type<int, double>::type> Vector<int>::operator-<double>(Vector<double> const&) const;
template Vector<std::common_type<int, long double>::type> Vector<int>::operator-<long double>(Vector<long double> const&) const;

template Vector<std::complex<std::common_type<int, int>::type>> Vector<int>::operator-<int>(Vector<std::complex<int>> const&) const;
template Vector<std::complex<std::common_type<int, float>::type>> Vector<int>::operator-<float>(Vector<std::complex<float>> const&) const;
template Vector<std::complex<std::common_type<int, double>::type>> Vector<int>::operator-<double>(Vector<std::complex<double>> const&) const;
template Vector<std::complex<std::common_type<int, long double>::type>> Vector<int>::operator-<long double>(Vector<std::complex<long double>> const&) const;

// Vector<float> - other Vector types
template Vector<std::common_type<float, int>::type> Vector<float>::operator-<int>(Vector<int> const&) const;
template Vector<std::common_type<float, float>::type> Vector<float>::operator-<float>(Vector<float> const&) const;
template Vector<std::common_type<float, double>::type> Vector<float>::operator-<double>(Vector<double> const&) const;
template Vector<std::common_type<float, long double>::type> Vector<float>::operator-<long double>(Vector<long double> const&) const;

template Vector<std::complex<std::common_type<float, int>::type>> Vector<float>::operator-<int>(Vector<std::complex<int>> const&) const;
template Vector<std::complex<std::common_type<float, float>::type>> Vector<float>::operator-<float>(Vector<std::complex<float>> const&) const;
template Vector<std::complex<std::common_type<float, double>::type>> Vector<float>::operator-<double>(Vector<std::complex<double>> const&) const;
template Vector<std::complex<std::common_type<float, long double>::type>> Vector<float>::operator-<long double>(Vector<std::complex<long double>> const&) const;

// Vector<double> - other Vector types
template Vector<std::common_type<double, int>::type> Vector<double>::operator-<int>(Vector<int> const&) const;
template Vector<std::common_type<double, float>::type> Vector<double>::operator-<float>(Vector<float> const&) const;
template Vector<std::common_type<double, double>::type> Vector<double>::operator-<double>(Vector<double> const&) const;
template Vector<std::common_type<double, long double>::type> Vector<double>::operator-<long double>(Vector<long double> const&) const;

template Vector<std::complex<std::common_type<double, int>::type>> Vector<double>::operator-<int>(Vector<std::complex<int>> const&) const;
template Vector<std::complex<std::common_type<double, float>::type>> Vector<double>::operator-<float>(Vector<std::complex<float>> const&) const;
template Vector<std::complex<std::common_type<double, double>::type>> Vector<double>::operator-<double>(Vector<std::complex<double>> const&) const;
template Vector<std::complex<std::common_type<double, long double>::type>> Vector<double>::operator-<long double>(Vector<std::complex<long double>> const&) const;

// Vector<long double> - other Vector types
template Vector<std::common_type<long double, int>::type> Vector<long double>::operator-<int>(Vector<int> const&) const;
template Vector<std::common_type<long double, float>::type> Vector<long double>::operator-<float>(Vector<float> const&) const;
template Vector<std::common_type<long double, double>::type> Vector<long double>::operator-<double>(Vector<double> const&) const;
template Vector<std::common_type<long double, long double>::type> Vector<long double>::operator-<long double>(Vector<long double> const&) const;

template Vector<std::complex<std::common_type<long double, int>::type>> Vector<long double>::operator-<int>(Vector<std::complex<int>> const&) const;
template Vector<std::complex<std::common_type<long double, float>::type>> Vector<long double>::operator-<float>(Vector<std::complex<float>> const&) const;
template Vector<std::complex<std::common_type<long double, double>::type>> Vector<long double>::operator-<double>(Vector<std::complex<double>> const&) const;
template Vector<std::complex<std::common_type<long double, long double>::type>> Vector<long double>::operator-<long double>(Vector<std::complex<long double>> const&) const;

// Vector<complex<int>> - other Vector types
template Vector<std::complex<typename std::common_type<int,int>::type>> Vector<std::complex<int>>::operator-<int>(const Vector<int>& other) const;
template Vector<std::complex<typename std::common_type<int,float>::type>> Vector<std::complex<int>>::operator-<float>(const Vector<float>& other) const;
template Vector<std::complex<typename std::common_type<int,double>::type>> Vector<std::complex<int>>::operator-<double>(const Vector<double>& other) const;
template Vector<std::complex<typename std::common_type<int,long double>::type>> Vector<std::complex<int>>::operator-<long double>(const Vector<long double>& other) const;

template Vector<std::complex<typename std::common_type<int,int>::type>> Vector<std::complex<int>>::operator-<int>(const Vector<std::complex<int>>& other) const;
template Vector<std::complex<typename std::common_type<int,float>::type>> Vector<std::complex<int>>::operator-<float>(const Vector<std::complex<float>>& other) const;
template Vector<std::complex<typename std::common_type<int,double>::type>> Vector<std::complex<int>>::operator-<double>(const Vector<std::complex<double>>& other) const;
template Vector<std::complex<typename std::common_type<int,long double>::type>> Vector<std::complex<int>>::operator-<long double>(const Vector<std::complex<long double>>& other) const;

// Vector<complex<float>> - other Vector types
template Vector<std::complex<typename std::common_type<float,int>::type>> Vector<std::complex<float>>::operator-<int>(const Vector<int>& other) const;
template Vector<std::complex<typename std::common_type<float,float>::type>> Vector<std::complex<float>>::operator-<float>(const Vector<float>& other) const;
template Vector<std::complex<typename std::common_type<float,double>::type>> Vector<std::complex<float>>::operator-<double>(const Vector<double>& other) const;
template Vector<std::complex<typename std::common_type<float,long double>::type>> Vector<std::complex<float>>::operator-<long double>(const Vector<long double>& other) const;

template Vector<std::complex<typename std::common_type<float,int>::type>> Vector<std::complex<float>>::operator-<int>(const Vector<std::complex<int>>& other) const;
template Vector<std::complex<typename std::common_type<float,float>::type>> Vector<std::complex<float>>::operator-<float>(const Vector<std::complex<float>>& other) const;
template Vector<std::complex<typename std::common_type<float,double>::type>> Vector<std::complex<float>>::operator-<double>(const Vector<std::complex<double>>& other) const;
template Vector<std::complex<typename std::common_type<float,long double>::type>> Vector<std::complex<float>>::operator-<long double>(const Vector<std::complex<long double>>& other) const;

// Vector<complex<double>> - other Vector types
template Vector<std::complex<typename std::common_type<double,int>::type>> Vector<std::complex<double>>::operator-<int>(const Vector<int>& other) const;
template Vector<std::complex<typename std::common_type<double,float>::type>> Vector<std::complex<double>>::operator-<float>(const Vector<float>& other) const;
template Vector<std::complex<typename std::common_type<double,double>::type>> Vector<std::complex<double>>::operator-<double>(const Vector<double>& other) const;
template Vector<std::complex<typename std::common_type<double,long double>::type>> Vector<std::complex<double>>::operator-<long double>(const Vector<long double>& other) const;

template Vector<std::complex<typename std::common_type<double,int>::type>> Vector<std::complex<double>>::operator-<int>(const Vector<std::complex<int>>& other) const;
template Vector<std::complex<typename std::common_type<double,float>::type>> Vector<std::complex<double>>::operator-<float>(const Vector<std::complex<float>>& other) const;
template Vector<std::complex<typename std::common_type<double,double>::type>> Vector<std::complex<double>>::operator-<double>(const Vector<std::complex<double>>& other) const;
template Vector<std::complex<typename std::common_type<double,long double>::type>> Vector<std::complex<double>>::operator-<long double>(const Vector<std::complex<long double>>& other) const;

// Vector<complex<long double>> - other Vector types
template Vector<std::complex<typename std::common_type<long double,int>::type>> Vector<std::complex<long double>>::operator-<int>(const Vector<int>& other) const;
template Vector<std::complex<typename std::common_type<long double,float>::type>> Vector<std::complex<long double>>::operator-<float>(const Vector<float>& other) const;
template Vector<std::complex<typename std::common_type<long double,double>::type>> Vector<std::complex<long double>>::operator-<double>(const Vector<double>& other) const;
template Vector<std::complex<typename std::common_type<long double,long double>::type>> Vector<std::complex<long double>>::operator-<long double>(const Vector<long double>& other) const;

template Vector<std::complex<typename std::common_type<long double,int>::type>> Vector<std::complex<long double>>::operator-<int>(const Vector<std::complex<int>>& other) const;
template Vector<std::complex<typename std::common_type<long double,float>::type>> Vector<std::complex<long double>>::operator-<float>(const Vector<std::complex<float>>& other) const;
template Vector<std::complex<typename std::common_type<long double,double>::type>> Vector<std::complex<long double>>::operator-<double>(const Vector<std::complex<double>>& other) const;
template Vector<std::complex<typename std::common_type<long double,long double>::type>> Vector<std::complex<long double>>::operator-<long double>(const Vector<std::complex<long double>>& other) const;

// Addition broadcasters

// Vector<int> + scalars
template Vector<std::common_type<int, int>::type> Vector<int>::operator+<int>(int) const;
template Vector<std::common_type<int, float>::type> Vector<int>::operator+<float>(float) const;
template Vector<std::common_type<int, double>::type> Vector<int>::operator+<double>(double) const;
template Vector<std::common_type<int, long double>::type> Vector<int>::operator+<long double>(long double) const;

template Vector<std::complex<typename std::common_type<int,int>::type>> Vector<int>::operator+<int>(std::complex<int>) const;
template Vector<std::complex<typename std::common_type<int,float>::type>> Vector<int>::operator+<float>(std::complex<float>) const;
template Vector<std::complex<typename std::common_type<int,double>::type>> Vector<int>::operator+<double>(std::complex<double>) const;
template Vector<std::complex<typename std::common_type<int,long double>::type>> Vector<int>::operator+<long double>(std::complex<long double>) const;

// Vector<float> + scalars
template Vector<std::common_type<float, int>::type> Vector<float>::operator+<int>(int) const;
template Vector<std::common_type<float, float>::type> Vector<float>::operator+<float>(float) const;
template Vector<std::common_type<float, double>::type> Vector<float>::operator+<double>(double) const;
template Vector<std::common_type<float, long double>::type> Vector<float>::operator+<long double>(long double) const;

template Vector<std::complex<typename std::common_type<float,int>::type>> Vector<float>::operator+<int>(std::complex<int>) const;
template Vector<std::complex<typename std::common_type<float,float>::type>> Vector<float>::operator+<float>(std::complex<float>) const;
template Vector<std::complex<typename std::common_type<float,double>::type>> Vector<float>::operator+<double>(std::complex<double>) const;
template Vector<std::complex<typename std::common_type<float,long double>::type>> Vector<float>::operator+<long double>(std::complex<long double>) const;

// Vector<double> + scalars
template Vector<std::common_type<double, int>::type> Vector<double>::operator+<int>(int) const;
template Vector<std::common_type<double, float>::type> Vector<double>::operator+<float>(float) const;
template Vector<std::common_type<double, double>::type> Vector<double>::operator+<double>(double) const;
template Vector<std::common_type<double, long double>::type> Vector<double>::operator+<long double>(long double) const;

template Vector<std::complex<typename std::common_type<double,int>::type>> Vector<double>::operator+<int>(std::complex<int>) const;
template Vector<std::complex<typename std::common_type<double,float>::type>> Vector<double>::operator+<float>(std::complex<float>) const;
template Vector<std::complex<typename std::common_type<double,double>::type>> Vector<double>::operator+<double>(std::complex<double>) const;
template Vector<std::complex<typename std::common_type<double,long double>::type>> Vector<double>::operator+<long double>(std::complex<long double>) const;

// Vector<long double> + scalars
template Vector<std::common_type<long double, int>::type> Vector<long double>::operator+<int>(int) const;
template Vector<std::common_type<long double, float>::type> Vector<long double>::operator+<float>(float) const;
template Vector<std::common_type<long double, double>::type> Vector<long double>::operator+<double>(double) const;
template Vector<std::common_type<long double, long double>::type> Vector<long double>::operator+<long double>(long double) const;

template Vector<std::complex<typename std::common_type<long double,int>::type>> Vector<long double>::operator+<int>(std::complex<int>) const;
template Vector<std::complex<typename std::common_type<long double,float>::type>> Vector<long double>::operator+<float>(std::complex<float>) const;
template Vector<std::complex<typename std::common_type<long double,double>::type>> Vector<long double>::operator+<double>(std::complex<double>) const;
template Vector<std::complex<typename std::common_type<long double,long double>::type>> Vector<long double>::operator+<long double>(std::complex<long double>) const;

// Vector<std::complex<int>> + scalars
template Vector<std::complex<typename std::common_type<int,int>::type>> Vector<std::complex<int>>::operator+<int>(int) const;
template Vector<std::complex<typename std::common_type<int,float>::type>> Vector<std::complex<int>>::operator+<float>(float) const;
template Vector<std::complex<typename std::common_type<int,double>::type>> Vector<std::complex<int>>::operator+<double>(double) const;
template Vector<std::complex<typename std::common_type<int,long double>::type>> Vector<std::complex<int>>::operator+<long double>(long double) const;

template Vector<std::complex<typename std::common_type<int,int>::type>> Vector<std::complex<int>>::operator+<int>(std::complex<int>) const;
template Vector<std::complex<typename std::common_type<int,float>::type>> Vector<std::complex<int>>::operator+<float>(std::complex<float>) const;
template Vector<std::complex<typename std::common_type<int,double>::type>> Vector<std::complex<int>>::operator+<double>(std::complex<double>) const;
template Vector<std::complex<typename std::common_type<int,long double>::type>> Vector<std::complex<int>>::operator+<long double>(std::complex<long double>) const;

// Vector<std::complex<float>> + scalars
template Vector<std::complex<typename std::common_type<float,int>::type>> Vector<std::complex<float>>::operator+<int>(int) const;
template Vector<std::complex<typename std::common_type<float,float>::type>> Vector<std::complex<float>>::operator+<float>(float) const;
template Vector<std::complex<typename std::common_type<float,double>::type>> Vector<std::complex<float>>::operator+<double>(double) const;
template Vector<std::complex<typename std::common_type<float,long double>::type>> Vector<std::complex<float>>::operator+<long double>(long double) const;

template Vector<std::complex<typename std::common_type<float,int>::type>> Vector<std::complex<float>>::operator+<int>(std::complex<int>) const;
template Vector<std::complex<typename std::common_type<float,float>::type>> Vector<std::complex<float>>::operator+<float>(std::complex<float>) const;
template Vector<std::complex<typename std::common_type<float,double>::type>> Vector<std::complex<float>>::operator+<double>(std::complex<double>) const;
template Vector<std::complex<typename std::common_type<float,long double>::type>> Vector<std::complex<float>>::operator+<long double>(std::complex<long double>) const;

// Vector<std::complex<double>> + scalars
template Vector<std::complex<typename std::common_type<double,int>::type>> Vector<std::complex<double>>::operator+<int>(int) const;
template Vector<std::complex<typename std::common_type<double,float>::type>> Vector<std::complex<double>>::operator+<float>(float) const;
template Vector<std::complex<typename std::common_type<double,double>::type>> Vector<std::complex<double>>::operator+<double>(double) const;
template Vector<std::complex<typename std::common_type<double,long double>::type>> Vector<std::complex<double>>::operator+<long double>(long double) const;

template Vector<std::complex<typename std::common_type<double,int>::type>> Vector<std::complex<double>>::operator+<int>(std::complex<int>) const;
template Vector<std::complex<typename std::common_type<double,float>::type>> Vector<std::complex<double>>::operator+<float>(std::complex<float>) const;
template Vector<std::complex<typename std::common_type<double,double>::type>> Vector<std::complex<double>>::operator+<double>(std::complex<double>) const;
template Vector<std::complex<typename std::common_type<double,long double>::type>> Vector<std::complex<double>>::operator+<long double>(std::complex<long double>) const;

// Vector<std::complex<long double>> + scalars
template Vector<std::complex<typename std::common_type<long double,int>::type>> Vector<std::complex<long double>>::operator+<int>(int) const;
template Vector<std::complex<typename std::common_type<long double,float>::type>> Vector<std::complex<long double>>::operator+<float>(float) const;
template Vector<std::complex<typename std::common_type<long double,double>::type>> Vector<std::complex<long double>>::operator+<double>(double) const;
template Vector<std::complex<typename std::common_type<long double,long double>::type>> Vector<std::complex<long double>>::operator+<long double>(long double) const;

template Vector<std::complex<typename std::common_type<long double,int>::type>> Vector<std::complex<long double>>::operator+<int>(std::complex<int>) const;
template Vector<std::complex<typename std::common_type<long double,float>::type>> Vector<std::complex<long double>>::operator+<float>(std::complex<float>) const;
template Vector<std::complex<typename std::common_type<long double,double>::type>> Vector<std::complex<long double>>::operator+<double>(std::complex<double>) const;
template Vector<std::complex<typename std::common_type<long double,long double>::type>> Vector<std::complex<long double>>::operator+<long double>(std::complex<long double>) const;

//Subtraction broadcasters

// Vector<int> - scalars
template Vector<std::common_type<int, int>::type> Vector<int>::operator-<int>(int) const;
template Vector<std::common_type<int, float>::type> Vector<int>::operator-<float>(float) const;
template Vector<std::common_type<int, double>::type> Vector<int>::operator-<double>(double) const;
template Vector<std::common_type<int, long double>::type> Vector<int>::operator-<long double>(long double) const;

template Vector<std::complex<typename std::common_type<int,int>::type>> Vector<int>::operator-<int>(std::complex<int>) const;
template Vector<std::complex<typename std::common_type<int,float>::type>> Vector<int>::operator-<float>(std::complex<float>) const;
template Vector<std::complex<typename std::common_type<int,double>::type>> Vector<int>::operator-<double>(std::complex<double>) const;
template Vector<std::complex<typename std::common_type<int,long double>::type>> Vector<int>::operator-<long double>(std::complex<long double>) const;

// Vector<float> - scalars
template Vector<std::common_type<float, int>::type> Vector<float>::operator-<int>(int) const;
template Vector<std::common_type<float, float>::type> Vector<float>::operator-<float>(float) const;
template Vector<std::common_type<float, double>::type> Vector<float>::operator-<double>(double) const;
template Vector<std::common_type<float, long double>::type> Vector<float>::operator-<long double>(long double) const;

template Vector<std::complex<typename std::common_type<float,int>::type>> Vector<float>::operator-<int>(std::complex<int>) const;
template Vector<std::complex<typename std::common_type<float,float>::type>> Vector<float>::operator-<float>(std::complex<float>) const;
template Vector<std::complex<typename std::common_type<float,double>::type>> Vector<float>::operator-<double>(std::complex<double>) const;
template Vector<std::complex<typename std::common_type<float,long double>::type>> Vector<float>::operator-<long double>(std::complex<long double>) const;

// Vector<double> - scalars
template Vector<std::common_type<double, int>::type> Vector<double>::operator-<int>(int) const;
template Vector<std::common_type<double, float>::type> Vector<double>::operator-<float>(float) const;
template Vector<std::common_type<double, double>::type> Vector<double>::operator-<double>(double) const;
template Vector<std::common_type<double, long double>::type> Vector<double>::operator-<long double>(long double) const;

template Vector<std::complex<typename std::common_type<double,int>::type>> Vector<double>::operator-<int>(std::complex<int>) const;
template Vector<std::complex<typename std::common_type<double,float>::type>> Vector<double>::operator-<float>(std::complex<float>) const;
template Vector<std::complex<typename std::common_type<double,double>::type>> Vector<double>::operator-<double>(std::complex<double>) const;
template Vector<std::complex<typename std::common_type<double,long double>::type>> Vector<double>::operator-<long double>(std::complex<long double>) const;

// Vector<long double> - scalars
template Vector<std::common_type<long double, int>::type> Vector<long double>::operator-<int>(int) const;
template Vector<std::common_type<long double, float>::type> Vector<long double>::operator-<float>(float) const;
template Vector<std::common_type<long double, double>::type> Vector<long double>::operator-<double>(double) const;
template Vector<std::common_type<long double, long double>::type> Vector<long double>::operator-<long double>(long double) const;

template Vector<std::complex<typename std::common_type<long double,int>::type>> Vector<long double>::operator-<int>(std::complex<int>) const;
template Vector<std::complex<typename std::common_type<long double,float>::type>> Vector<long double>::operator-<float>(std::complex<float>) const;
template Vector<std::complex<typename std::common_type<long double,double>::type>> Vector<long double>::operator-<double>(std::complex<double>) const;
template Vector<std::complex<typename std::common_type<long double,long double>::type>> Vector<long double>::operator-<long double>(std::complex<long double>) const;

// Vector<std::complex<int>> - scalars
template Vector<std::complex<typename std::common_type<int,int>::type>> Vector<std::complex<int>>::operator-<int>(int) const;
template Vector<std::complex<typename std::common_type<int,float>::type>> Vector<std::complex<int>>::operator-<float>(float) const;
template Vector<std::complex<typename std::common_type<int,double>::type>> Vector<std::complex<int>>::operator-<double>(double) const;
template Vector<std::complex<typename std::common_type<int,long double>::type>> Vector<std::complex<int>>::operator-<long double>(long double) const;

template Vector<std::complex<typename std::common_type<int,int>::type>> Vector<std::complex<int>>::operator-<int>(std::complex<int>) const;
template Vector<std::complex<typename std::common_type<int,float>::type>> Vector<std::complex<int>>::operator-<float>(std::complex<float>) const;
template Vector<std::complex<typename std::common_type<int,double>::type>> Vector<std::complex<int>>::operator-<double>(std::complex<double>) const;
template Vector<std::complex<typename std::common_type<int,long double>::type>> Vector<std::complex<int>>::operator-<long double>(std::complex<long double>) const;

// Vector<std::complex<float>> - scalars
template Vector<std::complex<typename std::common_type<float,int>::type>> Vector<std::complex<float>>::operator-<int>(int) const;
template Vector<std::complex<typename std::common_type<float,float>::type>> Vector<std::complex<float>>::operator-<float>(float) const;
template Vector<std::complex<typename std::common_type<float,double>::type>> Vector<std::complex<float>>::operator-<double>(double) const;
template Vector<std::complex<typename std::common_type<float,long double>::type>> Vector<std::complex<float>>::operator-<long double>(long double) const;

template Vector<std::complex<typename std::common_type<float,int>::type>> Vector<std::complex<float>>::operator-<int>(std::complex<int>) const;
template Vector<std::complex<typename std::common_type<float,float>::type>> Vector<std::complex<float>>::operator-<float>(std::complex<float>) const;
template Vector<std::complex<typename std::common_type<float,double>::type>> Vector<std::complex<float>>::operator-<double>(std::complex<double>) const;
template Vector<std::complex<typename std::common_type<float,long double>::type>> Vector<std::complex<float>>::operator-<long double>(std::complex<long double>) const;

// Vector<std::complex<double>> - scalars
template Vector<std::complex<typename std::common_type<double,int>::type>> Vector<std::complex<double>>::operator-<int>(int) const;
template Vector<std::complex<typename std::common_type<double,float>::type>> Vector<std::complex<double>>::operator-<float>(float) const;
template Vector<std::complex<typename std::common_type<double,double>::type>> Vector<std::complex<double>>::operator-<double>(double) const;
template Vector<std::complex<typename std::common_type<double,long double>::type>> Vector<std::complex<double>>::operator-<long double>(long double) const;

template Vector<std::complex<typename std::common_type<double,int>::type>> Vector<std::complex<double>>::operator-<int>(std::complex<int>) const;
template Vector<std::complex<typename std::common_type<double,float>::type>> Vector<std::complex<double>>::operator-<float>(std::complex<float>) const;
template Vector<std::complex<typename std::common_type<double,double>::type>> Vector<std::complex<double>>::operator-<double>(std::complex<double>) const;
template Vector<std::complex<typename std::common_type<double,long double>::type>> Vector<std::complex<double>>::operator-<long double>(std::complex<long double>) const;

// Vector<std::complex<long double>> - scalars
template Vector<std::complex<typename std::common_type<long double,int>::type>> Vector<std::complex<long double>>::operator-<int>(int) const;
template Vector<std::complex<typename std::common_type<long double,float>::type>> Vector<std::complex<long double>>::operator-<float>(float) const;
template Vector<std::complex<typename std::common_type<long double,double>::type>> Vector<std::complex<long double>>::operator-<double>(double) const;
template Vector<std::complex<typename std::common_type<long double,long double>::type>> Vector<std::complex<long double>>::operator-<long double>(long double) const;

template Vector<std::complex<typename std::common_type<long double,int>::type>> Vector<std::complex<long double>>::operator-<int>(std::complex<int>) const;
template Vector<std::complex<typename std::common_type<long double,float>::type>> Vector<std::complex<long double>>::operator-<float>(std::complex<float>) const;
template Vector<std::complex<typename std::common_type<long double,double>::type>> Vector<std::complex<long double>>::operator-<double>(std::complex<double>) const;
template Vector<std::complex<typename std::common_type<long double,long double>::type>> Vector<std::complex<long double>>::operator-<long double>(std::complex<long double>) const;

// Multiplication broadcasters
template Vector<std::common_type<int, int>::type> Vector<int>::operator*<int>(int) const;
template Vector<std::common_type<int, float>::type> Vector<int>::operator*<float>(float) const;
template Vector<std::common_type<int, double>::type> Vector<int>::operator*<double>(double) const;
template Vector<std::common_type<int, long double>::type> Vector<int>::operator*<long double>(long double) const;

template Vector<std::common_type<float, int>::type> Vector<float>::operator*<int>(int) const;
template Vector<std::common_type<float, float>::type> Vector<float>::operator*<float>(float) const;
template Vector<std::common_type<float, double>::type> Vector<float>::operator*<double>(double) const;
template Vector<std::common_type<float, long double>::type> Vector<float>::operator*<long double>(long double) const;

template Vector<std::common_type<double, int>::type> Vector<double>::operator*<int>(int) const;
template Vector<std::common_type<double, float>::type> Vector<double>::operator*<float>(float) const;
template Vector<std::common_type<double, double>::type> Vector<double>::operator*<double>(double) const;
template Vector<std::common_type<double, long double>::type> Vector<double>::operator*<long double>(long double) const;

template Vector<std::common_type<long double, int>::type> Vector<long double>::operator*<int>(int) const;
template Vector<std::common_type<long double, float>::type> Vector<long double>::operator*<float>(float) const;
template Vector<std::common_type<long double, double>::type> Vector<long double>::operator*<double>(double) const;
template Vector<std::common_type<long double, long double>::type> Vector<long double>::operator*<long double>(long double) const;

//Division broadcasters
template Vector<std::common_type<int, int>::type> Vector<int>::operator/<int>(int) const;
template Vector<std::common_type<int, float>::type> Vector<int>::operator/<float>(float) const;
template Vector<std::common_type<int, double>::type> Vector<int>::operator/<double>(double) const;
template Vector<std::common_type<int, long double>::type> Vector<int>::operator/<long double>(long double) const;

template Vector<std::common_type<float, int>::type> Vector<float>::operator/<int>(int) const;
template Vector<std::common_type<float, float>::type> Vector<float>::operator/<float>(float) const;
template Vector<std::common_type<float, double>::type> Vector<float>::operator/<double>(double) const;
template Vector<std::common_type<float, long double>::type> Vector<float>::operator/<long double>(long double) const;

template Vector<std::common_type<double, int>::type> Vector<double>::operator/<int>(int) const;
template Vector<std::common_type<double, float>::type> Vector<double>::operator/<float>(float) const;
template Vector<std::common_type<double, double>::type> Vector<double>::operator/<double>(double) const;
template Vector<std::common_type<double, long double>::type> Vector<double>::operator/<long double>(long double) const;

template Vector<std::common_type<long double, int>::type> Vector<long double>::operator/<int>(int) const;
template Vector<std::common_type<long double, float>::type> Vector<long double>::operator/<float>(float) const;
template Vector<std::common_type<long double, double>::type> Vector<long double>::operator/<double>(double) const;
template Vector<std::common_type<long double, long double>::type> Vector<long double>::operator/<long double>(long double) const;

//Non-member addition broadcasters (allow doing newVector = scalar + vec)
// int scalar + Vector<T>
template Vector<std::common_type<int, int>::type>       operator+(const int val,    const Vector<int>&);
template Vector<std::common_type<int, float>::type>     operator+(const int val,    const Vector<float>&);
template Vector<std::common_type<int, double>::type>    operator+(const int val,    const Vector<double>&);
template Vector<std::common_type<int, long double>::type>    operator+(const int val,    const Vector<long double>&);

template Vector<std::complex<typename std::common_type<int,int>::type>> operator+(const int val, const Vector<std::complex<int>>&);
template Vector<std::complex<typename std::common_type<int,float>::type>> operator+(const int val, const Vector<std::complex<float>>&);
template Vector<std::complex<typename std::common_type<int,double>::type>> operator+(const int val, const Vector<std::complex<double>>&);
template Vector<std::complex<typename std::common_type<int,long double>::type>> operator+(const int val, const Vector<std::complex<long double>>&);

// float scalar + Vector<T>
template Vector<std::common_type<float, int>::type>       operator+(const float val,    const Vector<int>&);
template Vector<std::common_type<float, float>::type>     operator+(const float val,    const Vector<float>&);
template Vector<std::common_type<float, double>::type>    operator+(const float val,    const Vector<double>&);
template Vector<std::common_type<float, long double>::type>    operator+(const float val,    const Vector<long double>&);

template Vector<std::complex<typename std::common_type<float,int>::type>> operator+(const float val, const Vector<std::complex<int>>&);
template Vector<std::complex<typename std::common_type<float,float>::type>> operator+(const float val, const Vector<std::complex<float>>&);
template Vector<std::complex<typename std::common_type<float,double>::type>> operator+(const float val, const Vector<std::complex<double>>&);
template Vector<std::complex<typename std::common_type<float,long double>::type>> operator+(const float val, const Vector<std::complex<long double>>&);

// double scalar + Vector<T>
template Vector<std::common_type<double, int>::type>       operator+(const double val,    const Vector<int>&);
template Vector<std::common_type<double, float>::type>     operator+(const double val,    const Vector<float>&);
template Vector<std::common_type<double, double>::type>    operator+(const double val,    const Vector<double>&);
template Vector<std::common_type<double, long double>::type>    operator+(const double val,    const Vector<long double>&);

template Vector<std::complex<typename std::common_type<double,int>::type>> operator+(const double val, const Vector<std::complex<int>>&);
template Vector<std::complex<typename std::common_type<double,float>::type>> operator+(const double val, const Vector<std::complex<float>>&);
template Vector<std::complex<typename std::common_type<double,double>::type>> operator+(const double val, const Vector<std::complex<double>>&);
template Vector<std::complex<typename std::common_type<double,long double>::type>> operator+(const double val, const Vector<std::complex<long double>>&);

// long double scalar + Vector<T>
template Vector<std::common_type<long double, int>::type>       operator+(const long double val,    const Vector<int>&);
template Vector<std::common_type<long double, float>::type>     operator+(const long double val,    const Vector<float>&);
template Vector<std::common_type<long double, double>::type>    operator+(const long double val,    const Vector<double>&);
template Vector<std::common_type<long double, long double>::type>    operator+(const long double val,    const Vector<long double>&);

template Vector<std::complex<typename std::common_type<long double,int>::type>> operator+(const long double val, const Vector<std::complex<int>>&);
template Vector<std::complex<typename std::common_type<long double,float>::type>> operator+(const long double val, const Vector<std::complex<float>>&);
template Vector<std::complex<typename std::common_type<long double,double>::type>> operator+(const long double val, const Vector<std::complex<double>>&);
template Vector<std::complex<typename std::common_type<long double,long double>::type>> operator+(const long double val, const Vector<std::complex<long double>>&);

// std::complex<int> scalar + Vector<T>
template Vector<std::complex<typename std::common_type<int,int>::type>> operator+(const std::complex<int> val,    const Vector<int>&);
template Vector<std::complex<typename std::common_type<int,float>::type>> operator+(const std::complex<int> val,    const Vector<float>&);
template Vector<std::complex<typename std::common_type<int,double>::type>> operator+(const std::complex<int> val,    const Vector<double>&);
template Vector<std::complex<typename std::common_type<int,long double>::type>> operator+(const std::complex<int> val,    const Vector<long double>&);

template Vector<std::complex<typename std::common_type<int,int>::type>> operator+(const std::complex<int> val,    const Vector<std::complex<int>>&);
template Vector<std::complex<typename std::common_type<int,float>::type>> operator+(const std::complex<int> val,    const Vector<std::complex<float>>&);
template Vector<std::complex<typename std::common_type<int,double>::type>> operator+(const std::complex<int> val,    const Vector<std::complex<double>>&);
template Vector<std::complex<typename std::common_type<int,long double>::type>> operator+(const std::complex<int> val,    const Vector<std::complex<long double>>&);

// std::complex<float> scalar + Vector<T>
template Vector<std::complex<typename std::common_type<float,int>::type>> operator+(const std::complex<float> val,    const Vector<int>&);
template Vector<std::complex<typename std::common_type<float,float>::type>> operator+(const std::complex<float> val,    const Vector<float>&);
template Vector<std::complex<typename std::common_type<float,double>::type>> operator+(const std::complex<float> val,    const Vector<double>&);
template Vector<std::complex<typename std::common_type<float,long double>::type>> operator+(const std::complex<float> val,    const Vector<long double>&);

template Vector<std::complex<typename std::common_type<float,int>::type>> operator+(const std::complex<float> val,    const Vector<std::complex<int>>&);
template Vector<std::complex<typename std::common_type<float,float>::type>> operator+(const std::complex<float> val,    const Vector<std::complex<float>>&);
template Vector<std::complex<typename std::common_type<float,double>::type>> operator+(const std::complex<float> val,    const Vector<std::complex<double>>&);
template Vector<std::complex<typename std::common_type<float,long double>::type>> operator+(const std::complex<float> val,    const Vector<std::complex<long double>>&);

// std::complex<double> scalar + Vector<T>
template Vector<std::complex<typename std::common_type<double,int>::type>> operator+(const std::complex<double> val,    const Vector<int>&);
template Vector<std::complex<typename std::common_type<double,float>::type>> operator+(const std::complex<double> val,    const Vector<float>&);
template Vector<std::complex<typename std::common_type<double,double>::type>> operator+(const std::complex<double> val,    const Vector<double>&);
template Vector<std::complex<typename std::common_type<double,long double>::type>> operator+(const std::complex<double> val,    const Vector<long double>&);

template Vector<std::complex<typename std::common_type<double,int>::type>> operator+(const std::complex<double> val,    const Vector<std::complex<int>>&);
template Vector<std::complex<typename std::common_type<double,float>::type>> operator+(const std::complex<double> val,    const Vector<std::complex<float>>&);
template Vector<std::complex<typename std::common_type<double,double>::type>> operator+(const std::complex<double> val,    const Vector<std::complex<double>>&);
template Vector<std::complex<typename std::common_type<double,long double>::type>> operator+(const std::complex<double> val,    const Vector<std::complex<long double>>&);

// std::complex<long double> scalar + Vector<T>
template Vector<std::complex<typename std::common_type<long double,int>::type>> operator+(const std::complex<long double> val,    const Vector<int>&);
template Vector<std::complex<typename std::common_type<long double,float>::type>> operator+(const std::complex<long double> val,    const Vector<float>&);
template Vector<std::complex<typename std::common_type<long double,double>::type>> operator+(const std::complex<long double> val,    const Vector<double>&);
template Vector<std::complex<typename std::common_type<long double,long double>::type>> operator+(const std::complex<long double> val,    const Vector<long double>&);

template Vector<std::complex<typename std::common_type<long double,int>::type>> operator+(const std::complex<long double> val,    const Vector<std::complex<int>>&);
template Vector<std::complex<typename std::common_type<long double,float>::type>> operator+(const std::complex<long double> val,    const Vector<std::complex<float>>&);
template Vector<std::complex<typename std::common_type<long double,double>::type>> operator+(const std::complex<long double> val,    const Vector<std::complex<double>>&);
template Vector<std::complex<typename std::common_type<long double,long double>::type>> operator+(const std::complex<long double> val,    const Vector<std::complex<long double>>&);

//Non-member multiplication broadcasters (allow doing newVector = scalar * vec)
template Vector<std::common_type<int, int>::type>       operator*(const int val,    const Vector<int>&);
template Vector<std::common_type<int, float>::type>     operator*(const int val,    const Vector<float>&);
template Vector<std::common_type<int, double>::type>    operator*(const int val,    const Vector<double>&);
template Vector<std::common_type<int, long double>::type>    operator*(const int val,    const Vector<long double>&);

template Vector<std::common_type<float, int>::type>       operator*(const float val,    const Vector<int>&);
template Vector<std::common_type<float, float>::type>     operator*(const float val,    const Vector<float>&);
template Vector<std::common_type<float, double>::type>    operator*(const float val,    const Vector<double>&);
template Vector<std::common_type<float, long double>::type>    operator*(const float val,    const Vector<long double>&);

template Vector<std::common_type<double, int>::type>       operator*(const double val,    const Vector<int>&);
template Vector<std::common_type<double, float>::type>     operator*(const double val,    const Vector<float>&);
template Vector<std::common_type<double, double>::type>    operator*(const double val,    const Vector<double>&);
template Vector<std::common_type<double, long double>::type>    operator*(const double val,    const Vector<long double>&);

template Vector<std::common_type<long double, int>::type>       operator*(const long double val,    const Vector<int>&);
template Vector<std::common_type<long double, float>::type>     operator*(const long double val,    const Vector<float>&);
template Vector<std::common_type<long double, double>::type>    operator*(const long double val,    const Vector<double>&);
template Vector<std::common_type<long double, long double>::type>    operator*(const long double val,    const Vector<long double>&);

//Dot product
template std::common_type<int, int>::type Vector<int>::dot<int>(const Vector<int>&) const;
template std::common_type<int, float>::type Vector<int>::dot<float>(const Vector<float>&) const;
template std::common_type<int, double>::type Vector<int>::dot<double>(const Vector<double>&) const;
template std::common_type<int, long double>::type Vector<int>::dot<long double>(const Vector<long double>&) const;

template std::common_type<float, int>::type Vector<float>::dot<int>(const Vector<int>&) const;
template std::common_type<float, float>::type Vector<float>::dot<float>(const Vector<float>&) const;
template std::common_type<float, double>::type Vector<float>::dot<double>(const Vector<double>&) const;
template std::common_type<float, long double>::type Vector<float>::dot<long double>(const Vector<long double>&) const;

template std::common_type<double, int>::type Vector<double>::dot<int>(const Vector<int>&) const;
template std::common_type<double, float>::type Vector<double>::dot<float>(const Vector<float>&) const;
template std::common_type<double, double>::type Vector<double>::dot<double>(const Vector<double>&) const;
template std::common_type<double, long double>::type Vector<double>::dot<long double>(const Vector<long double>&) const;

template std::common_type<long double, int>::type Vector<long double>::dot<int>(const Vector<int>&) const;
template std::common_type<long double, float>::type Vector<long double>::dot<float>(const Vector<float>&) const;
template std::common_type<long double, double>::type Vector<long double>::dot<double>(const Vector<double>&) const;
template std::common_type<long double, long double>::type Vector<long double>::dot<long double>(const Vector<long double>&) const;

#endif //LINEARALGEBRATOOLBOX_VECTOREXPLICITTEMPLATEINSTANTIATIONS_HPP
