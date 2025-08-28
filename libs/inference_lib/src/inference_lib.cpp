#include "inference_lib.h"

// Helper function for ReLU
Eigen::MatrixXd relu(const Eigen::MatrixXd& x) {
    return x.cwiseMax(0);
}

// Constructor: copies the weights and biases into the object's member variables
MLP::MLP(const Eigen::MatrixXd& w1, const Eigen::VectorXd& b1,
         const Eigen::MatrixXd& w2, const Eigen::VectorXd& b2)
    : m_w1(w1), m_b1(b1), m_w2(w2), m_b2(b2) {}

// Predict method: uses the stored weights
Eigen::VectorXd MLP::predict(const Eigen::VectorXd& input) {
    Eigen::RowVectorXd z1 = input.transpose() * m_w1;
    z1 += m_b1.transpose();
    Eigen::RowVectorXd a1 = relu(z1);
    Eigen::RowVectorXd logits = a1 * m_w2;
    logits += m_b2.transpose();
    return logits.transpose();
}