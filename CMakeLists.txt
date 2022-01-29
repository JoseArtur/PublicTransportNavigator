cmake_minimum_required(VERSION 3.20)
project(Projeto2)

set(CMAKE_CXX_STANDARD 14)
include_directories("$ENV{SFML_PATH}/include")
link_directories("$ENV{SFML_PATH}/lib")

add_executable(Projeto2   Tests/minHeap.h Tests/MainGraph.h Tests/FileReader.h Tests/FileReader.cpp Tests/Application.cpp Tests/Utilities.cpp   main.cpp Tests/MainGraph.cpp Tests/MainGraph.h)
