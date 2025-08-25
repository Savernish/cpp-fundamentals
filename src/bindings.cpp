#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <pybind11/eigen.h> // Header for automatic Eigen::MatrixXd <-> NumPy conversion

// Include our pure C++ library headers
#include "math_lib.h"
#include "inference_lib.h"
#include <Eigen/Dense>

namespace py = pybind11;

// Wrapper for forward_pass to accept NumPy arrays and convert to Eigen
py::array_t<double> forward_pass_numpy(
    py::array_t<double>& input_np,
    py::array_t<double>& w1_np,
    py::array_t<double>& b1_np,
    py::array_t<double>& w2_np,
    py::array_t<double>& b2_np
) {
    Eigen::Map<Eigen::VectorXd> input(static_cast<double*>(input_np.request().ptr), input_np.size());
    Eigen::Map<Eigen::MatrixXd> w1(static_cast<double*>(w1_np.request().ptr), w1_np.shape(0), w1_np.shape(1));
    Eigen::Map<Eigen::VectorXd> b1(static_cast<double*>(b1_np.request().ptr), b1_np.size());
    Eigen::Map<Eigen::MatrixXd> w2(static_cast<double*>(w2_np.request().ptr), w2_np.shape(0), w2_np.shape(1));
    Eigen::Map<Eigen::VectorXd> b2(static_cast<double*>(b2_np.request().ptr), b2_np.size());
    Eigen::VectorXd logits_eigen = forward_pass(input, w1, b1, w2, b2);
    py::array_t<double> logits_np(logits_eigen.size());
    double* ptr_np = static_cast<double*>(logits_np.request().ptr);
    for (int i = 0; i < logits_eigen.size(); ++i) {
        ptr_np[i] = logits_eigen(i);
    }
    return logits_np;
}

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
    m.def("forward_pass_numpy", &forward_pass_numpy, "Performs a full MLP forward pass in C++ with Eigen, using NumPy arrays.");
}