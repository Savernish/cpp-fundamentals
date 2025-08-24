#include <iostream>
#include <vector>
#include "math_lib.h" // Include the header from your library

int main() {
    std::vector<double> vec1 = {1.0, 2.0, 3.0};
    std::vector<double> vec2 = {4.0, 5.0, 6.0};

    std::cout << "Using our custom math library to add vectors!" << std::endl;
    std::vector<double> sum = add_vectors(vec1, vec2);

    std::cout << "Result: [ ";
    for (const auto& val : sum) {
        std::cout << val << " ";
    }
    std::cout << "]" << std::endl;

    return 0;
}