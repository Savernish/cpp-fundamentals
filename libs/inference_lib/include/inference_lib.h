#ifndef INFERENCE_LIB_H
#define INFERENCE_LIB_H

#include <Eigen/Dense>

// The pure C++/Eigen forward pass (no Python stuff)
Eigen::VectorXd forward_pass(
    const Eigen::VectorXd& input,
    const Eigen::MatrixXd& w1,
    const Eigen::VectorXd& b1,
    const Eigen::MatrixXd& w2,
    const Eigen::VectorXd& b2
);

#endif // INFERENCE_LIB_H