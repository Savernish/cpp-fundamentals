#include "inference_lib.h"
#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>


// Element-wise ReLU activation function for Eigen matrices/vectors
Eigen::MatrixXd relu(const Eigen::MatrixXd& x) {
    return x.cwiseMax(0);
}

Eigen::VectorXd forward_pass(
    const Eigen::VectorXd& input,
    const Eigen::MatrixXd& w1,
    const Eigen::VectorXd& b1,
    const Eigen::MatrixXd& w2,
    const Eigen::VectorXd& b2
) {
    // Layer 1: Z1 = X * W1 + b1 (where X is a 1x784 row vector)
    // Eigen handles matrix-vector products correctly.
    // .transpose() makes the (784,) input vector into a (1x784) row vector for multiplication.
    // The result z1 is a (1x128) row vector.
    Eigen::RowVectorXd z1 = input.transpose() * w1;
    z1 += b1.transpose(); // Add bias vector

    // Apply ReLU activation
    Eigen::RowVectorXd a1 = relu(z1);

    // Layer 2: Logits = A1 * W2 + b2
    // a1 is (1x128), w2 is (128x10), result is (1x10)
    Eigen::RowVectorXd logits = a1 * w2;
    logits += b2.transpose(); // Add bias vector

    // Return the result as a standard column vector
    return logits.transpose();
}

pybind11::array_t<double> forward_pass_numpy(
    pybind11::array_t<double>& input_np,
    pybind11::array_t<double>& w1_np,
    pybind11::array_t<double>& b1_np,
    pybind11::array_t<double>& w2_np,
    pybind11::array_t<double>& b2_np
) {
    // --- Convert NumPy arrays to Eigen Maps (zero-copy) ---
    // A Map is an Eigen object that wraps an existing block of memory.
    // This is how we avoid copying data.
    Eigen::Map<Eigen::VectorXd> input(static_cast<double*>(input_np.request().ptr), input_np.size());
    
    Eigen::Map<Eigen::MatrixXd> w1(static_cast<double*>(w1_np.request().ptr), w1_np.shape(0), w1_np.shape(1));
    Eigen::Map<Eigen::VectorXd> b1(static_cast<double*>(b1_np.request().ptr), b1_np.size());
    
    Eigen::Map<Eigen::MatrixXd> w2(static_cast<double*>(w2_np.request().ptr), w2_np.shape(0), w2_np.shape(1));
    Eigen::Map<Eigen::VectorXd> b2(static_cast<double*>(b2_np.request().ptr), b2_np.size());

    // --- Call the core C++ engine ---
    Eigen::VectorXd logits_eigen = forward_pass(input, w1, b1, w2, b2);

    // --- Convert the Eigen result back to a new NumPy array ---
    // This is the only data copy in the entire process.
    pybind11::array_t<double> logits_np(logits_eigen.size());
    double* ptr_np = static_cast<double*>(logits_np.request().ptr);
    
    // Copy data from Eigen vector to the new NumPy array
    for (int i = 0; i < logits_eigen.size(); ++i) {
        ptr_np[i] = logits_eigen(i);
    }

    return logits_np;
}