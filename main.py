import sys
import numpy as np
import time

sys.path.append('./build')
import cpp_math

def add_lists(a, b):
    # This loop is interpreted by the Python interpreter, which is slow
    result = []
    for i in range(len(a)):
        result.append(a[i] + b[i])
    return result

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

    # --- Benchmark pure Python ---
    start_time_py = time.time()
    result_py = add_lists(arr1, arr2)
    end_time_py = time.time()
    print(f"Pure Python execution time: {(end_time_py - start_time_py) * 1000:.2f} ms")

    # Verify the results are the same
    assert np.allclose(result_np, result_cpp, result_py)
    print("\nResults from NumPy , C++ and pure Python are identical.")

    print("--- Demonstrating in-place modification via C++ ---")
    # Create an array
    arr = np.array([1.0, 2.0, 3.0], dtype=np.float64)
    print(f"Original array: {arr}")

    # Call the C++ function. It returns nothing.
    cpp_math.add_scalar_inplace(arr, 100.0)

    print(f"Array after C++ in-place modification: {arr}")
    assert arr[0] == 101.0
    print("In-place modification successful.")

if __name__ == "__main__":
    main()