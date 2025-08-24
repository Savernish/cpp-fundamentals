import sys

# We need to tell Python where to find our new module.
# The compiled file will be in the 'build' directory.
sys.path.append('./build')

try:
    # Import the module. The name 'cpp_math' must match the one in CMakeLists.txt
    import cpp_math
except ImportError as e:
    print("Error importing C++ module. Did you build the project?")
    print(e)
    sys.exit(1)

def main():
    vec1 = [1.1, 2.2, 3.3]
    vec2 = [4.4, 5.5, 6.6]

    print(f"Calling C++ function from Python with lists: {vec1} and {vec2}")

    # Call the C++ function as if it were a normal Python function.
    # PyBind11 automatically converts the Python lists to std::vector<double>
    # and converts the result back to a Python list.
    result = cpp_math.add_vectors(vec1, vec2)

    print(f"Result from C++: {result}")
    print(f"Docstring from C++: {cpp_math.add_vectors.__doc__}")

if __name__ == "__main__":
    main()