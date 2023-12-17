cmake_minimum_required(VERSION 3.27)
project(SPL-01)

set(CMAKE_CXX_STANDARD 23)

add_executable(SPL-01 main.cpp
        CSVReader.cpp
        CSVReader.h
        GradientDescent.h
        GradientDescent.cpp
        crossValidation.h
        crossValidation.cpp
        ThreadStacker.h
        ThreadStacker.cpp
        DirectoryReader.cpp
        Image.cpp
        MatrixManipulator.cpp
        CoordinateCalc.h
        CoordinateCalc.cpp
)
