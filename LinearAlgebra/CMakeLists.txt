cmake_minimum_required(VERSION 3.26)

file(GLOB SOURCES CONFIGURE_DEPENDS "src/*.cpp")

set(library_name LinearAlgebra)

add_library(${library_name} SHARED src/Vector.cpp src/Matrix.cpp)
target_include_directories(${library_name} PRIVATE include)

install(TARGETS ${library_name}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)

install(DIRECTORY include/
        DESTINATION include/
        )
install(DIRECTORY launch    DESTINATION share/${PROJECT_NAME})
