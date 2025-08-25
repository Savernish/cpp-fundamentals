#include "math_lib.h"
#include <stdexcept>

std::vector<double> add_vectors(const std::vector<double>& a, const std::vector<double>& b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("Vectors must be of the same size.");
    }

    std::vector<double> result;
    result.reserve(a.size()); // Pre-allocate the memory for efficiency

    for (size_t i = 0; i < a.size(); ++i) {
        result.push_back(a[i] + b[i]);
    }
    return result;
}