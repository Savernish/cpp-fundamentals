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

# --- Build the inference_lib static library ---
add_library(inference_lib STATIC
    libs/inference_lib/src/inference_lib.cpp
)
# Tell CMake where to find Eigen's headers
target_include_directories(inference_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/inference_lib/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/eigen # Path to Eigen's parent dir
)

# --- Build an executable to test the inference lib ---
add_executable(inference_tester src/main_inference.cpp)

# Link the tester against our inference library
target_link_libraries(inference_tester PRIVATE inference_lib)