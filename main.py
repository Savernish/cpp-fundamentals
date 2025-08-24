import sys
import numpy as np
import time

sys.path.append('./build')
import cpp_math

def main():
    # Create large NumPy arrays
    size = 10_000_000
    arr1 = np.random.rand(size).astype(np.float64)
    arr2 = np.random.rand(size).astype(np.float64)

    # --- Benchmark NumPy ---
    start_time_np = time.time()
    result_np = np.add(arr1, arr2)
    end_time_np = time.time()
    print(f"NumPy execution time: {(end_time_np - start_time_np) * 1000:.2f} ms")

    # --- Benchmark C++ ---
    start_time_cpp = time.time()
    result_cpp = cpp_math.add_arrays(arr1, arr2)
    end_time_cpp = time.time()
    print(f"C++ execution time:   {(end_time_cpp - start_time_cpp) * 1000:.2f} ms")

    # Verify the results are the same
    assert np.allclose(result_np, result_cpp)
    print("\nResults from NumPy and C++ are identical.")

if __name__ == "__main__":
    main()