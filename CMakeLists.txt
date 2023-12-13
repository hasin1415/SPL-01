cmake_minimum_required(VERSION 3.27)
project(SPL-01)

set(CMAKE_CXX_STANDARD 23)

add_executable(SPL-01 main.cpp
        image.cpp
        image.h
        directoryReader.cpp
        directoryReader.h
        Stacker.cpp
        Stacker.h
        CSVReader.cpp
        CSVReader.h
        imageFinder.cpp
        imageFinder.h
        Stacker.cpp
        Stacker.h
        MatrixManipulator.h
        GradientDescent.h
        GradientDescent.cpp
        crossValidation.h
        crossValidation.cpp
)
