#include "math_lib.h"
#include <stdexcept>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h> // Include for NumPy support

namespace py = pybind11;

std::vector<double> add_vectors(const std::vector<double>& a, const std::vector<double>& b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("Vectors must be of the same size.");
    }

    std::vector<double> result;
    result.reserve(a.size()); // Pre-allocate memory for efficiency

    for (size_t i = 0; i < a.size(); ++i) {
        result.push_back(a[i] + b[i]);
    }
    return result;
}

py::array_t<double> add_arrays(py::array_t<double>& a, py::array_t<double>& b) {
    // Request buffer information from the input arrays
    py::buffer_info buf_a = a.request();
    py::buffer_info buf_b = b.request();

    if (buf_a.ndim != 1 || buf_b.ndim != 1) {
        throw std::runtime_error("Number of dimensions must be one");
    }
    if (buf_a.size != buf_b.size) {
        throw std::runtime_error("Input arrays must have the same size");
    }

    // Create a new NumPy array to store the result
    auto result = py::array_t<double>(buf_a.size);
    py::buffer_info buf_result = result.request();

    // Get raw pointers to the underlying data
    double* ptr_a = static_cast<double*>(buf_a.ptr);
    double* ptr_b = static_cast<double*>(buf_b.ptr);
    double* ptr_result = static_cast<double*>(buf_result.ptr);

    // Perform the element-wise addition using raw pointers for maximum speed
    for (size_t i = 0; i < buf_a.size; i++) {
        ptr_result[i] = ptr_a[i] + ptr_b[i];
    }

    return result;
}