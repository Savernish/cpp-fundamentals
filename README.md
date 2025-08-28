# Modern C++ for High-Performance Computing

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Language](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/)
[![Build](https://img.shields.io/badge/build-CMake-green.svg)](https://cmake.org/)

This repository is a structured exploration of modern C++ (C++17 and beyond) and its application in high-performance computing, with a specific focus on accelerating Python-based machine learning pipelines. The goal is to develop production-grade C++ skills for performance-critical domains like robotics, autonomous systems, and defense AI.

## Project Philosophy

While Python is great for prototyping, production ML systems often need the speed and control of C++. This project shows how to bridge that gap, with real code and a test harness to verify C++ results against Python.

## Learning Roadmap & Modules

| Module | Component | Status | Description |
| :--- | :--- | :--- | :--- |
| **Core Concepts** | RAII & Smart Pointers | ✅ Done | Understanding modern C++ memory management (`unique_ptr`, `shared_ptr`). |
| | STL Containers | ✅ Done | Practical use of `vector`, `string`, `unordered_map`, etc. |
| **Build Systems** | CMake Basics | ✅ Done | Creating and building executables with `CMakeLists.txt`. |
| | Static & Shared Libraries | ✅ Done | Building modular, reusable code libraries. |
| **Python Integration** | PyBind11: Basic Bindings | ✅ Done | Exposing C++ functions and classes to Python. |
| | PyBind11: NumPy Integration | ✅ Done | Passing NumPy arrays to C++ efficiently without copying data. |
| **ML Acceleration** | C++ Inference Engine | ✅ Done | Implementing a neural network forward pass in C++ using Eigen or a similar library. |
| | C++ Accelerated Algorithms | ⏳ Planned | Rewriting performance-critical Python algorithms (e.g., in computer vision) in C++. |
| **GPU Computing** | CUDA/Thrust Introduction | ⏳ Planned | Exploring basic GPU acceleration for parallelizable tasks. |

## Performance Results: C++ Accelerated Inference Engine

A key goal of this project is to quantify the performance gains of moving compute-intensive tasks from Python to C++. The `inference_lib` module implements a full forward pass of a 784x128x10 MLP, which was benchmarked against an equivalent implementation in pure NumPy.

The benchmark was performed on a single image input, averaged over 2,000 runs.

| Implementation | Average Inference Time (µs) | Speedup vs. NumPy |
| :--- | :--- | :--- |
| **Python (NumPy)** | 18.35 µs |
| **C++ (Eigen, Release Build)** | 14.98 µs | **1.23x Faster** |


This demonstrates a significant, measurable performance improvement by moving the core matrix operations to a compiled, optimized C++ backend.

## Technology Stack

* **C++17**
* **CMake (3.16+)**
* **PyBind11:** For Python bindings.
* **Compiler:** g++ (via `build-essential` on Ubuntu)

## Build & Verification Instructions


This project is developed and tested on WSL2 (Ubuntu 24.04), but should work on any modern Linux with Python 3 and CMake 3.16+.

### 1. Clone the repository
```bash
git clone https://github.com/Savernish/cpp-fundamentals
cd cpp-fundamentals
```

### 2. Configure with CMake (for Python module)
You must specify your Python version for PyBind11 to find the right headers. For example, for Python 3.11:
```bash
cmake -S . -B build -DPYTHON_EXECUTABLE=$(which python3.11)
```

### 3. Build the project
```bash
cmake --build build
```

### 4. Run the Python verification
The test harness compares the C++/Eigen neural network output to the reference Python/NumPy model:
```bash
python3 verify_inference.py
```
You should see matching outputs and timing for both implementations.
