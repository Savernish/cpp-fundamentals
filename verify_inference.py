import numpy as np
import sys
import time

# Using the original Network class from the ml-from-scratch project.
# --- Start of copied code from ml-from-scratch ---
class DenseLayer:
    def __init__(self, input_size, output_size):
        self.weights = np.random.randn(input_size, output_size) * 0.01
        self.biases = np.zeros((1, output_size))
    def forward(self, input_data):
        self.input = input_data
        return np.dot(self.input, self.weights) + self.biases

class ReLU:
    def forward(self, input_data):
        return np.maximum(0, input_data)

class Network:
    def __init__(self, input_size, hidden_size, output_size):
        self.dense1 = DenseLayer(input_size, hidden_size)
        self.relu1 = ReLU()
        self.dense2 = DenseLayer(hidden_size, output_size)
    def forward(self, x):
        x = self.dense1.forward(x)
        x = self.relu1.forward(x)
        x = self.dense2.forward(x)
        return x
# --- End of copied code ---

# Import the C++ module
sys.path.append('./build')
import cpp_math

def main():
    print("--- C++ Inference Engine Verification ---")
    
    # 1. Load the trained weights from the scratch model
    weights_file = '../ml-from-scratch/neural_network/weights_biases.npz'
    try:
        weights = np.load(weights_file)
    except FileNotFoundError:
        print(f"ERROR: Weight file not found at {weights_file}")
        print("Please ensure you have the 'weights_biases.npz' file from your scratch-built network.")
        sys.exit(1)

    w1 = weights['dense1_weights'].astype(np.float64)
    b1 = weights['dense1_biases'].flatten().astype(np.float64)
    w2 = weights['dense2_weights'].astype(np.float64)
    b2 = weights['dense2_biases'].flatten().astype(np.float64)

    # 2. Create a dummy input image (784 features)
    dummy_input = np.random.rand(784).astype(np.float64)

    # 3. Get logits from the original Python/NumPy model
    py_model = Network(784, 128, 10)
    py_model.dense1.weights = w1
    py_model.dense1.biases = b1
    py_model.dense2.weights = w2
    py_model.dense2.biases = b2
    
    start_py = time.time()
    logits_py = py_model.forward(dummy_input)
    end_py = time.time()
    
    print(f"\nPython/NumPy model execution time: {(end_py - start_py) * 1000:.4f} ms")
    print("Python Logits (first 5):", logits_py.flatten()[:5])

    # 4. Get logits from the C++/Eigen engine
    start_cpp = time.time()
    logits_cpp = cpp_math.forward_pass_cpp(dummy_input, w1, b1, w2, b2)
    end_cpp = time.time()

    print(f"\nC++/Eigen model execution time:   {(end_cpp - start_cpp) * 1000:.4f} ms")
    print("C++ Logits (first 5):   ", logits_cpp[:5])

    # 5. Verify that the results are numerically identical
    assert np.allclose(logits_py, logits_cpp, atol=1e-9)
    print("\nSUCCESS: The C++ engine output matches the Python model output perfectly.")

if __name__ == "__main__":
    main()