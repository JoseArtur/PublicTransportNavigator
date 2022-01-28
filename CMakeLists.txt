cmake_minimum_required(VERSION 3.20)
project(Projeto2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Projeto2   Tests/minHeap.h   Tests/LinesGraph.cpp Tests/LinesGraph.h Tests/MainGraph.h Tests/FileReader.h Tests/FileReader.cpp Tests/Application.cpp Tests/Utilities.cpp   main.cpp Tests/MainGraph.cpp Tests/MainGraph.h)
