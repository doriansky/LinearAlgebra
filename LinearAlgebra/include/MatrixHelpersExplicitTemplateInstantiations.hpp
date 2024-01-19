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

template Matrix<int> transpose(const Matrix<int>&);
template Matrix<float> transpose(const Matrix<float>&);
template Matrix<double> transpose(const Matrix<double>&);
template Matrix<long double> transpose(const Matrix<long double>&);

template Vector::Vector<int> getRow(const Matrix<int>&, unsigned int);
template Vector::Vector<float> getRow(const Matrix<float>&, unsigned int);
template Vector::Vector<double> getRow(const Matrix<double>&, unsigned int);
template Vector::Vector<long double> getRow(const Matrix<long double>&, unsigned int);

template void setRow(Matrix<int>&, const std::vector<int>&, unsigned int);
template void setRow(Matrix<float>&, const std::vector<float>&, unsigned int);
template void setRow(Matrix<double>&, const std::vector<double>&, unsigned int);
template void setRow(Matrix<long double>&, const std::vector<long double>&, unsigned int);

template void setRow(Matrix<int>&, const Vector::Vector<int>&, unsigned int);
template void setRow(Matrix<float>&, const Vector::Vector<float>&, unsigned int);
template void setRow(Matrix<double>&, const Vector::Vector<double>&, unsigned int);
template void setRow(Matrix<long double>&, const Vector::Vector<long double>&, unsigned int);

template void swapRows(Matrix<int>&, unsigned int, unsigned int);
template void swapRows(Matrix<float>&, unsigned int, unsigned int);
template void swapRows(Matrix<double>&, unsigned int, unsigned int);
template void swapRows(Matrix<long double>&, unsigned int, unsigned int);

template LUFactorization factorizeLU(const Matrix<int>&);
template LUFactorization factorizeLU(const Matrix<float>&);
template LUFactorization factorizeLU(const Matrix<double>&);
template LUFactorization factorizeLU(const Matrix<long double>&);

template LUFactorization factorizeLU_echelon(const Matrix<int>&);
template LUFactorization factorizeLU_echelon(const Matrix<float>&);
template LUFactorization factorizeLU_echelon(const Matrix<double>&);
template LUFactorization factorizeLU_echelon(const Matrix<long double>&);

template QRFactorization factorizeQR(const Matrix<int>&);
template QRFactorization factorizeQR(const Matrix<float>&);
template QRFactorization factorizeQR(const Matrix<double>&);
template QRFactorization factorizeQR(const Matrix<long double>&);

template Matrix<long double> reduced_row_echelon(const Matrix<int>&);
template Matrix<long double> reduced_row_echelon(const Matrix<float>&);
template Matrix<long double> reduced_row_echelon(const Matrix<double>&);
template Matrix<long double> reduced_row_echelon(const Matrix<long double>&);

template long double determinant(const Matrix<int>&);
template long double determinant(const Matrix<float>&);
template long double determinant(const Matrix<double>&);
template long double determinant(const Matrix<long double>&);

template std::optional<Matrix<long double>> inverse(const Matrix<int>&);
template std::optional<Matrix<long double>> inverse(const Matrix<float>&);
template std::optional<Matrix<long double>> inverse(const Matrix<double>&);
template std::optional<Matrix<long double>> inverse(const Matrix<long double>&);

template std::optional<Matrix<long double>> left_inverse(const Matrix<int>&);
template std::optional<Matrix<long double>> left_inverse(const Matrix<float>&);
template std::optional<Matrix<long double>> left_inverse(const Matrix<double>&);
template std::optional<Matrix<long double>> left_inverse(const Matrix<long double>&);

template std::optional<Matrix<long double>> right_inverse(const Matrix<int>&);
template std::optional<Matrix<long double>> right_inverse(const Matrix<float>&);
template std::optional<Matrix<long double>> right_inverse(const Matrix<double>&);
template std::optional<Matrix<long double>> right_inverse(const Matrix<long double>&);

template unsigned int rank(const Matrix<int>&);
template unsigned int rank(const Matrix<float>&);
template unsigned int rank(const Matrix<double>&);
template unsigned int rank(const Matrix<long double>&);

template std::vector<Pivot> getPivots(const Matrix<int>&);
template std::vector<Pivot> getPivots(const Matrix<float>&);
template std::vector<Pivot> getPivots(const Matrix<double>&);
template std::vector<Pivot> getPivots(const Matrix<long double>&);

//Solve
template std::optional<Solution> solve(const Matrix<int>&, Vector::Vector<int> const&);
template std::optional<Solution> solve(const Matrix<int>&, Vector::Vector<float> const&);
template std::optional<Solution> solve(const Matrix<int>&, Vector::Vector<double> const&);
template std::optional<Solution> solve(const Matrix<int>&, Vector::Vector<long double> const&);

template std::optional<Solution> solve(const Matrix<float>&, Vector::Vector<int> const&);
template std::optional<Solution> solve(const Matrix<float>&, Vector::Vector<float> const&);
template std::optional<Solution> solve(const Matrix<float>&, Vector::Vector<double> const&);
template std::optional<Solution> solve(const Matrix<float>&, Vector::Vector<long double> const&);

template std::optional<Solution> solve(const Matrix<double>&, Vector::Vector<int> const&);
template std::optional<Solution> solve(const Matrix<double>&, Vector::Vector<float> const&);
template std::optional<Solution> solve(const Matrix<double>&, Vector::Vector<double> const&);
template std::optional<Solution> solve(const Matrix<double>&, Vector::Vector<long double> const&);

template std::optional<Solution> solve(const Matrix<long double>&, Vector::Vector<int> const&);
template std::optional<Solution> solve(const Matrix<long double>&, Vector::Vector<float> const&);
template std::optional<Solution> solve(const Matrix<long double>&, Vector::Vector<double> const&);
template std::optional<Solution> solve(const Matrix<long double>&, Vector::Vector<long double> const&);

//Solve lower triangular
template Vector::Vector<long double> solveLowerTriangular(const Matrix<int>&, Vector::Vector<int> const&);
template Vector::Vector<long double> solveLowerTriangular(const Matrix<int>&, Vector::Vector<float> const&);
template Vector::Vector<long double> solveLowerTriangular(const Matrix<int>&, Vector::Vector<double> const&);
template Vector::Vector<long double> solveLowerTriangular(const Matrix<int>&, Vector::Vector<long double> const&);

template Vector::Vector<long double> solveLowerTriangular(const Matrix<float>&, Vector::Vector<int> const&);
template Vector::Vector<long double> solveLowerTriangular(const Matrix<float>&, Vector::Vector<float> const&);
template Vector::Vector<long double> solveLowerTriangular(const Matrix<float>&, Vector::Vector<double> const&);
template Vector::Vector<long double> solveLowerTriangular(const Matrix<float>&, Vector::Vector<long double> const&);

template Vector::Vector<long double> solveLowerTriangular(const Matrix<double>&, Vector::Vector<int> const&);
template Vector::Vector<long double> solveLowerTriangular(const Matrix<double>&, Vector::Vector<float> const&);
template Vector::Vector<long double> solveLowerTriangular(const Matrix<double>&, Vector::Vector<double> const&);
template Vector::Vector<long double> solveLowerTriangular(const Matrix<double>&, Vector::Vector<long double> const&);

template Vector::Vector<long double> solveLowerTriangular(const Matrix<long double>&, Vector::Vector<int> const&);
template Vector::Vector<long double> solveLowerTriangular(const Matrix<long double>&, Vector::Vector<float> const&);
template Vector::Vector<long double> solveLowerTriangular(const Matrix<long double>&, Vector::Vector<double> const&);
template Vector::Vector<long double> solveLowerTriangular(const Matrix<long double>&, Vector::Vector<long double> const&);

//Solve upper triangular
template Vector::Vector<long double> solveUpperTriangular(const Matrix<int>&, Vector::Vector<int> const&);
template Vector::Vector<long double> solveUpperTriangular(const Matrix<int>&, Vector::Vector<float> const&);
template Vector::Vector<long double> solveUpperTriangular(const Matrix<int>&, Vector::Vector<double> const&);
template Vector::Vector<long double> solveUpperTriangular(const Matrix<int>&, Vector::Vector<long double> const&);

template Vector::Vector<long double> solveUpperTriangular(const Matrix<float>&, Vector::Vector<int> const&);
template Vector::Vector<long double> solveUpperTriangular(const Matrix<float>&, Vector::Vector<float> const&);
template Vector::Vector<long double> solveUpperTriangular(const Matrix<float>&, Vector::Vector<double> const&);
template Vector::Vector<long double> solveUpperTriangular(const Matrix<float>&, Vector::Vector<long double> const&);

template Vector::Vector<long double> solveUpperTriangular(const Matrix<double>&, Vector::Vector<int> const&);
template Vector::Vector<long double> solveUpperTriangular(const Matrix<double>&, Vector::Vector<float> const&);
template Vector::Vector<long double> solveUpperTriangular(const Matrix<double>&, Vector::Vector<double> const&);
template Vector::Vector<long double> solveUpperTriangular(const Matrix<double>&, Vector::Vector<long double> const&);

template Vector::Vector<long double> solveUpperTriangular(const Matrix<long double>&, Vector::Vector<int> const&);
template Vector::Vector<long double> solveUpperTriangular(const Matrix<long double>&, Vector::Vector<float> const&);
template Vector::Vector<long double> solveUpperTriangular(const Matrix<long double>&, Vector::Vector<double> const&);
template Vector::Vector<long double> solveUpperTriangular(const Matrix<long double>&, Vector::Vector<long double> const&);

//Fit LLSQ
template std::optional<FitLLSQ> fit_LLSQ(const Matrix<int>&, Vector::Vector<int> const&);
template std::optional<FitLLSQ> fit_LLSQ(const Matrix<int>&, Vector::Vector<float> const&);
template std::optional<FitLLSQ> fit_LLSQ(const Matrix<int>&, Vector::Vector<double> const&);
template std::optional<FitLLSQ> fit_LLSQ(const Matrix<int>&, Vector::Vector<long double> const&);

template std::optional<FitLLSQ> fit_LLSQ(const Matrix<float>&, Vector::Vector<int> const&);
template std::optional<FitLLSQ> fit_LLSQ(const Matrix<float>&, Vector::Vector<float> const&);
template std::optional<FitLLSQ> fit_LLSQ(const Matrix<float>&, Vector::Vector<double> const&);
template std::optional<FitLLSQ> fit_LLSQ(const Matrix<float>&, Vector::Vector<long double> const&);

template std::optional<FitLLSQ> fit_LLSQ(const Matrix<double>&, Vector::Vector<int> const&);
template std::optional<FitLLSQ> fit_LLSQ(const Matrix<double>&, Vector::Vector<float> const&);
template std::optional<FitLLSQ> fit_LLSQ(const Matrix<double>&, Vector::Vector<double> const&);
template std::optional<FitLLSQ> fit_LLSQ(const Matrix<double>&, Vector::Vector<long double> const&);

template std::optional<FitLLSQ> fit_LLSQ(const Matrix<long double>&, Vector::Vector<int> const&);
template std::optional<FitLLSQ> fit_LLSQ(const Matrix<long double>&, Vector::Vector<float> const&);
template std::optional<FitLLSQ> fit_LLSQ(const Matrix<long double>&, Vector::Vector<double> const&);
template std::optional<FitLLSQ> fit_LLSQ(const Matrix<long double>&, Vector::Vector<long double> const&);

#endif //LINEARALGEBRATOOLBOX_MATRIXHELPERSEXPLICITTEMPLATEINSTANTIATIONS_HPP
