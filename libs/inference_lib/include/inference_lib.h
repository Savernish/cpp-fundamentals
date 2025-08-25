#ifndef INFERENCE_LIB_H
#define INFERENCE_LIB_H

#include <Eigen/Dense> // Core Eigen header
#include <vector>

// Performs a forward pass of a 784x128x10 MLP with ReLU activation.
Eigen::VectorXd forward_pass(
    const Eigen::VectorXd& input,
    const Eigen::MatrixXd& w1,
    const Eigen::VectorXd& b1,
    const Eigen::MatrixXd& w2,
    const Eigen::VectorXd& b2
);

#endif // INFERENCE_LIB_H