#ifndef INFERENCE_LIB_H
#define INFERENCE_LIB_H

#include <Eigen/Dense>

class MLP {
public:
    // Constructor
    MLP(const Eigen::MatrixXd& w1, const Eigen::VectorXd& b1,
        const Eigen::MatrixXd& w2, const Eigen::VectorXd& b2);

    // The predict method that will be called from Python
    Eigen::VectorXd predict(const Eigen::VectorXd& input);

private:
    // Member variables to store the weights and biases
    Eigen::MatrixXd m_w1;
    Eigen::VectorXd m_b1;
    Eigen::MatrixXd m_w2;
    Eigen::VectorXd m_b2;
};

#endif // INFERENCE_LIB_H