cmake_minimum_required(VERSION 3.26)

file(GLOB SOURCES CONFIGURE_DEPENDS "src/*.cpp")

set(executable_name LinearAlgebraTests)

enable_testing()
find_package(GTest REQUIRED)

add_executable(${executable_name}
        src/main.cpp
        src/VectorTests.cpp
        src/VectorArithmeticOperators.cpp
        src/VectorScalarBroadcasters.cpp
        src/VectorComplex.cpp
        src/VectorComplexScalarBroadcasters.cpp
        src/MatrixTests.cpp
        src/MatrixHelpersTests.cpp
        src/MatrixArithmeticOperators.cpp
        src/MatrixArithmeticOperatorsComplex.cpp
        src/MatrixScalarBroadcasters.cpp
        src/MatrixMultiplication.cpp
        src/MatrixMultiplicationComplex.cpp
        src/MatrixVectorMultiplication.cpp
        src/MatrixVectorMultiplication_Complex.cpp
        src/MatrixLUFactorization.cpp
        src/MatrixLUFactorization_Strang.cpp
        src/MatrixLUFactorization_RowSwap.cpp
        src/MatrixLUFactorization_HilbertMatrices.cpp
        src/MatrixLU_Echelon.cpp
        src/MatrixReducedRowEchelonForm.cpp
        src/Matrix_SolveLinearEquations.cpp
        src/Matrix_SolveLowerTriangularSystems.cpp
        src/Matrix_SolveUpperTriangularSystems.cpp
        src/Matrix_SolveLinearEquations_HilbertMatrices.cpp
        src/Matrix_SolveRankEqualCols.cpp
        src/Matrix_SolveRankEqualRows.cpp
        src/Matrix_SolveRankSmallerThanRowsAndCols.cpp
        src/Matrix_SolveLLSQ.cpp
        src/MatrixInverseTests.cpp
        src/Matrix_RightLeftInverseTests.cpp
        src/MatrixInverseTests_HilbertMatrices.cpp
        src/MatrixPivotsAndRank.cpp
        src/Matrix_QR_Factorization.cpp)

target_include_directories(${executable_name}
        PRIVATE
        ../LinearAlgebra/include
        )

target_link_libraries(${executable_name} LinearAlgebra GTest::gtest GTest::gtest_main)

install(TARGETS ${executable_name}
        RUNTIME DESTINATION lib/${PROJECT_NAME}
)




