//
// Created by dorian on 29.12.2023.
//

#ifndef LINEARALGEBRATOOLBOX_MATRIXHELPERSEXPLICITTEMPLATEINSTANTIATIONS_HPP
#define LINEARALGEBRATOOLBOX_MATRIXHELPERSEXPLICITTEMPLATEINSTANTIATIONS_HPP


// Identity function
template Matrix<int> identity(unsigned int);
template Matrix<float> identity(unsigned int);
template Matrix<double> identity(unsigned int);
template Matrix<long double> identity(unsigned int);

template bool isLowerTriangular(const Matrix<int>&);
template bool isLowerTriangular(const Matrix<float>&);
template bool isLowerTriangular(const Matrix<double>&);
template bool isLowerTriangular(const Matrix<long double>&);

template bool isUpperTriangular(const Matrix<int>&);
template bool isUpperTriangular(const Matrix<float>&);
template bool isUpperTriangular(const Matrix<double>&);
template bool isUpperTriangular(const Matrix<long double>&);

#endif //LINEARALGEBRATOOLBOX_MATRIXHELPERSEXPLICITTEMPLATEINSTANTIATIONS_HPP
