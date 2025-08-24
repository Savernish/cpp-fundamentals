cmake_minimum_required(VERSION 3.16)
project(CppFundamentals CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(my_app src/main.cpp)
add_executable(my_raii_app src/raii_example.cpp)
add_executable(my_smart_ptr_app src/smart_pointers_example.cpp)