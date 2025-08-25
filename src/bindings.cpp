#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <pybind11/eigen.h> // Needed for Eigen/NumPy conversions

#include "math_lib.h"
#include "inference_lib.h"
#include <Eigen/Dense>
#include "math_lib.h"
#include "inference_lib.h"
#include <Eigen/Dense>

namespace py = pybind11;

// Wrapper to let Python/NumPy arrays work with the C++ Eigen code
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

// Python module entry point for the C++ code
PYBIND11_MODULE(cpp_math, m) {
    m.doc() = "C++/Eigen code exposed to Python. Solo dev project for the people.";

    // Expose add_vectors from the math_lib
    m.def("add_vectors", &add_vectors, "A function that adds two vectors element-wise.");

    // Expose forward_pass from the inference_lib (Eigen types work directly)
    m.def("forward_pass_cpp", &forward_pass, "MLP forward pass in C++/Eigen (Eigen types)");
    m.def("forward_pass_numpy", &forward_pass_numpy, "MLP forward pass in C++/Eigen (NumPy arrays)");
}