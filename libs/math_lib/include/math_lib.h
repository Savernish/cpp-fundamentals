#ifndef MATH_LIB_H
#define MATH_LIB_H

#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

// This function adds two vectors element-wise.
std::vector<double> add_vectors(const std::vector<double>& a, const std::vector<double>& b);

pybind11::array_t<double> add_arrays(pybind11::array_t<double>& a, pybind11::array_t<double>& b);

#endif // MATH_LIB_H