cmake_minimum_required(VERSION 3.16)
project(CppFundamentals CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Find PyBind11 ---
find_package(pybind11 REQUIRED)

# --- Build the math_lib static library ---
add_library(math_lib STATIC
    libs/math_lib/src/math_lib.cpp
)

# This is the line that will fix the relocation error
set_property(TARGET math_lib PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(math_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/math_lib/include
    PUBLIC ${pybind11_INCLUDE_DIRS} # Needed for math_lib.h
)

# Link pybind11 to the math_lib static library
target_link_libraries(math_lib PRIVATE pybind11::pybind11)

# --- Build the Python module ---
pybind11_add_module(cpp_math src/bindings.cpp)

# Link the shared module to the static library
target_link_libraries(cpp_math PRIVATE math_lib)

# ... (rest of your CMakeLists.txt)
add_executable(my_raii_app src/raii_example.cpp)
add_executable(my_smart_ptr_app src/smart_pointers_example.cpp)
add_executable(my_stl_app src/stl_example.cpp)