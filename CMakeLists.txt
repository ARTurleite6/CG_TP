cmake_minimum_required(VERSION 3.24)
project(CG_TP CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(generator)
add_subdirectory(engine)

target_compile_features(generator PUBLIC cxx_std_20)
target_compile_features(engine PUBLIC cxx_std_20)
