cmake_minimum_required(VERSION 3.16)
project(CppFundamentals CXX)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
  message(STATUS "Defaulting to Release build for maximum optimization.")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Build the math_lib static library ---
# This target now has NO knowledge of Python or PyBind11.
add_library(math_lib STATIC libs/math_lib/src/math_lib.cpp)
set_property(TARGET math_lib PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(math_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/math_lib/include)

# --- Build the inference_lib static library ---
# This target only needs to know about Eigen, not Python.
add_library(inference_lib STATIC libs/inference_lib/src/inference_lib.cpp)
set_property(TARGET inference_lib PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(inference_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/inference_lib/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/eigen
)

# --- Find PyBind11 and build the final Python module ---
add_subdirectory(third_party/pybind11)

# This is the ONLY target that knows about PyBind11.
pybind11_add_module(cpp_math src/bindings.cpp)

# Link the Python module against our pure C++ libraries.
target_link_libraries(cpp_math PRIVATE
    math_lib
    inference_lib
)