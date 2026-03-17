cmake_minimum_required (VERSION 3.19)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(VERBOSE ON) # to make build process more verbose
set(CMAKE_VERBOSE_MAKEFILE ON)

project ("LinearAlgebraToolbox")

# set compiler options
#if(MSVC)
#    add_compile_options(/W4 /WX)
#else()
#    add_compile_options(-Wall -Werror)
#endif()

# Bin folder
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

# Path to shared library folder
set(CMAKE_INSTALL_RPATH "${CMAKE_SOURCE_DIR}/bin")

# Modules
add_subdirectory("LinearAlgebra")
add_subdirectory("LinearAlgebraTests")

# Install dirs
install(DIRECTORY launch DESTINATION share/${PROJECT_NAME})
