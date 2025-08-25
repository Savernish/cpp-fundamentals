#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <pybind11/eigen.h> // Header for automatic Eigen::MatrixXd <-> NumPy conversion

// Include our pure C++ library headers
#include "math_lib.h"
#include "inference_lib.h"

namespace py = pybind11;

// This is our main Python module, named 'cpp_math'
PYBIND11_MODULE(cpp_math, m) {
    m.doc() = "High-performance C++ module for ML acceleration";

    // Binding for the function from math_lib
    m.def("add_vectors", &add_vectors, "A function that adds two vectors element-wise.");

    // Binding for the function from inference_lib
    // PyBind11's <pybind11/eigen.h> header automatically handles the conversion
    // between NumPy arrays and Eigen::MatrixXd / Eigen::VectorXd.
    // This is much cleaner than our manual wrapper from before.
    m.def("forward_pass_cpp", &forward_pass, "Performs a full MLP forward pass in C++ with Eigen.");
}