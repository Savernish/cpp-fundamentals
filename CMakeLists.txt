cmake_minimum_required(VERSION 3.16)
project(CppFundamentals CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Build the math_lib static library ---
add_library(math_lib STATIC
    libs/math_lib/src/math_lib.cpp
)

# --- THE FIX IS HERE ---
# Set the POSITION_INDEPENDENT_CODE property for our library.
# This tells CMake to add the -fPIC flag when compiling math_lib.
set_property(TARGET math_lib PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(math_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/math_lib/include
)

# --- Find PyBind11 and build the Python module ---
find_package(pybind11 REQUIRED)
pybind11_add_module(cpp_math src/bindings.cpp)
target_link_libraries(cpp_math PRIVATE math_lib)

add_executable(my_raii_app src/raii_example.cpp)
add_executable(my_smart_ptr_app src/smart_pointers_example.cpp)
add_executable(my_stl_app src/stl_example.cpp)