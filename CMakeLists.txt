cmake_minimum_required(VERSION 3.27)

project(typack VERSION 0.0.1 LANGUAGES CXX)
enable_testing()

add_library(typack INTERFACE)
target_compile_features(typack INTERFACE cxx_std_20)
target_include_directories(typack INTERFACE include)

add_subdirectory(test)
add_subdirectory(doc)
