import numpy as np
import sys
import timeit

sys.path.append('./build')
import cpp_math

# ... (Keep the NumPyNetwork class and its helpers as they were) ...
class DenseLayer:
    def __init__(self, w, b): self.weights = w; self.biases = b
    def forward(self, i): return np.dot(i, self.weights) + self.biases
class ReLU:
    def forward(self, i): return np.maximum(0, i)
class NumPyNetwork:
    def __init__(self, w1, b1, w2, b2):
        self.dense1 = DenseLayer(w1, b1.reshape(1, -1))
        self.relu1 = ReLU()
        self.dense2 = DenseLayer(w2, b2.reshape(1, -1))
    def forward(self, x):
        x = self.dense1.forward(x)
        x = self.relu1.forward(x)
        x = self.dense2.forward(x)
        return x

def run_benchmark():
    print("--- Performance Benchmark: NumPy vs. C++/Eigen (Class-based) ---")
    
    weights_file = '../ml-from-scratch/neural_network/weights_biases.npz'
    weights = np.load(weights_file)
    w1 = weights['dense1_weights'].astype(np.float64)
    b1 = weights['dense1_biases'].flatten().astype(np.float64)
    w2 = weights['dense2_weights'].astype(np.float64)
    b2 = weights['dense2_biases'].flatten().astype(np.float64)

    numpy_model = NumPyNetwork(w1, b1, w2, b2)
    
    # --- THE FIX IS HERE: Instantiate the C++ object ONCE ---
    cpp_model = cpp_math.MLP(w1, b1, w2, b2)
    
    test_input_row = np.random.rand(1, 784).astype(np.float64)
    test_input_col = test_input_row.flatten() # The C++ predict method expects a 1D array

    def run_numpy():
        numpy_model.forward(test_input_row)

    # The benchmarked function now only passes ONE array across the boundary
    def run_cpp():
        cpp_model.predict(test_input_col)

    num_runs = 2000
    print(f"\nRunning each implementation {num_runs} times...")

    time_numpy = timeit.timeit(run_numpy, number=num_runs)
    time_cpp = timeit.timeit(run_cpp, number=num_runs)

    avg_time_numpy_us = (time_numpy / num_runs) * 1_000_000
    avg_time_cpp_us = (time_cpp / num_runs) * 1_000_000
    speedup = avg_time_numpy_us / avg_time_cpp_us

    print("\n--- Benchmark Results (Corrected) ---")
    print(f"NumPy Average Inference Time: {avg_time_numpy_us:.2f} µs (microseconds)")
    print(f"C++ Average Inference Time:   {avg_time_cpp_us:.2f} µs (microseconds)")
    print(f"\nSpeedup Factor: {speedup:.2f}x")
    print("-------------------------------------")

if __name__ == "__main__":
    run_benchmark()