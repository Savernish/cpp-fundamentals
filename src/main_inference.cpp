#include <iostream>
#include "inference_lib.h"

int main() {
    // --- Define network architecture ---
    const int INPUT_SIZE = 784;
    const int HIDDEN_SIZE = 128;
    const int OUTPUT_SIZE = 10;

    // --- Create dummy data and weights ---
    // In a real scenario, would load these from the file saved in Python.
    Eigen::VectorXd dummy_input = Eigen::VectorXd::Random(INPUT_SIZE);
    
    Eigen::MatrixXd w1 = Eigen::MatrixXd::Random(INPUT_SIZE, HIDDEN_SIZE);
    Eigen::VectorXd b1 = Eigen::VectorXd::Random(HIDDEN_SIZE);
    
    Eigen::MatrixXd w2 = Eigen::MatrixXd::Random(HIDDEN_SIZE, OUTPUT_SIZE);
    Eigen::VectorXd b2 = Eigen::VectorXd::Random(OUTPUT_SIZE);
    
    std::cout << "Running C++ forward pass with dummy data..." << std::endl;
    
    // --- Call the forward pass function ---
    Eigen::VectorXd logits = forward_pass(dummy_input, w1, b1, w2, b2);
    
    std::cout << "Success! Output logits vector:" << std::endl;
    std::cout << logits << std::endl;
    
    return 0;
}