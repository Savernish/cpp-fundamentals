#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include "inference_lib.h" // Our new MLP class header

namespace py = pybind11;

PYBIND11_MODULE(cpp_math, m) {
    m.doc() = "High-performance C++ module with an MLP class";

    // This defines a new class 'MLP' in our Python module
    py::class_<MLP>(m, "MLP")
        // This binds the C++ constructor. py::init<...>() specifies the argument types.
        .def(py::init<const Eigen::MatrixXd&, const Eigen::VectorXd&,
                      const Eigen::MatrixXd&, const Eigen::VectorXd&>())
        // This binds the 'predict' method.
        .def("predict", &MLP::predict, "Performs a forward pass with the stored weights.");
}