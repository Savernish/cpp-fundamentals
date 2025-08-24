# Modern C++ for High-Performance Computing

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Language](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/)
[![Build](https://img.shields.io/badge/build-CMake-green.svg)](https://cmake.org/)

This repository is a structured exploration of modern C++ (C++17 and beyond) and its application in high-performance computing, with a specific focus on accelerating Python-based machine learning pipelines. The goal is to develop production-grade C++ skills for performance-critical domains like robotics, autonomous systems, and defense AI.

## Project Philosophy

While Python is exceptional for research and prototyping, production ML systems often require the speed, memory control, and low-level hardware access that C++ provides. This project bridges that gap by systematically building the skills needed to write, build, and integrate high-performance C++ code into Python applications using tools like PyBind11.

## Learning Roadmap & Modules

| Module | Component | Status | Description |
| :--- | :--- | :--- | :--- |
| **Core Concepts** | RAII & Smart Pointers | ✅ Done | Understanding modern C++ memory management (`unique_ptr`, `shared_ptr`). |
| | STL Containers | ✅ Done | Practical use of `vector`, `string`, `unordered_map`, etc. |
| **Build Systems** | CMake Basics | ✅ Done | Creating and building executables with `CMakeLists.txt`. |
| | Static & Shared Libraries | ⏳ Planned | Building modular, reusable code libraries. |
| **Python Integration** | PyBind11: Basic Bindings | ⏳ Planned | Exposing C++ functions and classes to Python. |
| | PyBind11: NumPy Integration | ⏳ Planned | Passing NumPy arrays to C++ efficiently without copying data. |
| **ML Acceleration** | C++ Inference Engine | ⏳ Planned | Implementing a neural network forward pass in C++ using Eigen or a similar library. |
| | C++ Accelerated Algorithms | ⏳ Planned | Rewriting performance-critical Python algorithms (e.g., in computer vision) in C++. |
| **GPU Computing** | CUDA/Thrust Introduction | ⏳ Planned | Exploring basic GPU acceleration for parallelizable tasks. |

## Technology Stack

* **C++17**
* **CMake (3.16+)**
* **PyBind11:** For Python bindings.
* **Compiler:** g++ (via `build-essential` on Ubuntu)

## Build Instructions

This project is developed and tested on WSL2 (Ubuntu 24.04).

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/your-username/cpp-fundamentals.git](https://github.com/your-username/cpp-fundamentals.git)
    cd cpp-fundamentals
    ```

2.  **Configure with CMake:**
    ```bash
    # Create a build directory
    cmake -S . -B build
    ```

3.  **Build the project:**
    ```bash
    cmake --build build
    ```

4.  **Run an executable:**
    ```bash
    # Example for the 'my_app' target
    ./build/my_app
    ```
