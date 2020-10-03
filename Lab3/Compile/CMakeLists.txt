cmake_minimum_required(VERSION 3.17)
project(Compile)

set(CMAKE_CXX_STANDARD 14)

add_library(library SHARED library/library.cpp library/library.h)
add_executable(app main.cpp)
target_link_libraries(app library)
add_executable(test test.cpp)
add_library(injectDll SHARED library/library.cpp library/library.h)
target_compile_definitions(injectDll PUBLIC INJECT)

