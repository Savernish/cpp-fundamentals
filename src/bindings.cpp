#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // Needed to automatically handle std::vector
#include "math_lib.h"    // Include the header for our C++ library

namespace py = pybind11;

// PYBIND11_MODULE is a macro that creates a function that will be called when
// the Python interpreter imports the module.
// The first argument is the name of the module (as seen in Python).
// The second argument, 'm', is a py::module_ object that is the main interface.
PYBIND11_MODULE(cpp_math, m) {
    m.doc() = "A Python module for our C++ math library, built with PyBind11";

    // m.def() exposes a C++ function to Python.
    // 1st arg: The name of the function in Python ("add_vectors").
    // 2nd arg: A pointer to the C++ function (&add_vectors).
    // 3rd arg: A docstring for the function.
    m.def("add_vectors", &add_vectors, "A function that adds two vectors element-wise.");
    m.def("add_arrays", &add_arrays, "A function that adds two NumPy arrays.");

    
}