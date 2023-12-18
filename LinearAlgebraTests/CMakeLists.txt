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
        src/MatrixTests.cpp
        src/MatrixArithmeticOperators.cpp
        src/MatrixScalarBroadcasters.cpp
        src/MatrixMultiplication.cpp
        src/MatrixVectorMultiplication.cpp)

target_include_directories(${executable_name}
        PRIVATE
        ../LinearAlgebra/include
        )

target_link_libraries(${executable_name} LinearAlgebra GTest::gtest GTest::gtest_main)

install(TARGETS ${executable_name}
        RUNTIME DESTINATION lib/${PROJECT_NAME}
)




