#include "inference_lib.h"
#include <iostream>


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