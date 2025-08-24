cmake_minimum_required(VERSION 3.16)
project(CppFundamentals CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Build the math_lib static library ---
# add_library(target_name STATIC source_files...)
add_library(math_lib STATIC
    libs/math_lib/src/math_lib.cpp
)

# Tell other targets where to find the headers for math_lib
# target_include_directories(target_name PUBLIC|PRIVATE|INTERFACE path...)
target_include_directories(math_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/math_lib/include
)

# --- Build the main executable ---
add_executable(my_app src/main.cpp)

# --- Link the executable against the library ---
# This tells CMake that 'my_app' depends on 'math_lib'
target_link_libraries(my_app PRIVATE math_lib)

add_executable(my_raii_app src/raii_example.cpp)
add_executable(my_smart_ptr_app src/smart_pointers_example.cpp)
add_executable(my_stl_app src/stl_example.cpp)