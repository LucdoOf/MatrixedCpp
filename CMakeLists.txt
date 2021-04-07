cmake_minimum_required(VERSION 3.17)
project(MatrixedCpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(MatrixedCpp
        src/CMatrix.cpp
        src/CMatrix.h
        src/CMatrixException.cpp
        src/CMatrixException.h
        src/CMatrixReader.cpp
        src/CMatrixReader.h
        src/defines.h
        src/main.cpp)
