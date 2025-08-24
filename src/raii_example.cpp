#include <iostream>

// A simple class that demonstrates the RAII pattern.
// It simulates managing a resource (e.g., a file, a network connection).
class ResourceWrapper {
public:
    // Constructor: Called when the object is created. This is where we "acquire" the resource.
    ResourceWrapper(int id) : resource_id(id) {
        std::cout << "Acquiring resource " << resource_id << "." << std::endl;
    }

    // Destructor: Called when the object goes out of scope. This is where we "release" it.
    // The '~' symbol denotes a destructor.
    ~ResourceWrapper() {
        std::cout << "Releasing resource " << resource_id << ". Cleanup is guaranteed!" << std::endl;
    }

private:
    int resource_id;
};

void use_resource() {
    std::cout << "Entering use_resource function." << std::endl;
    ResourceWrapper wrapper(1); // Resource is acquired here.
    // ... do some work with the resource ...
    std::cout << "Resource is in use." << std::endl;
    std::cout << "Leaving use_resource function." << std::endl;
    // 'wrapper' goes out of scope here, so its destructor is automatically called.
}

int main() {
    std::cout << "Starting main function." << std::endl;
    use_resource();
    std::cout << "Main function finished." << std::endl;
    return 0;
}