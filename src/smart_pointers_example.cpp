#include <iostream>
#include <memory> // Required for smart pointers

class MyObject {
public:
    MyObject() { std::cout << "MyObject created." << std::endl; }
    ~MyObject() { std::cout << "MyObject destroyed." << std::endl; }
    void greet() { std::cout << "Hello from MyObject!" << std::endl; }
};

void demonstrate_unique_ptr() {
    std::cout << "\n--- Demonstrating unique_ptr ---" << std::endl;
    // Create a unique_ptr. It now owns the MyObject instance.
    auto ptr = std::make_unique<MyObject>();
    ptr->greet();
    // No need to call delete. Memory is freed when 'ptr' goes out of scope.
}

void demonstrate_shared_ptr() {
    std::cout << "\n--- Demonstrating shared_ptr ---" << std::endl;
    std::shared_ptr<MyObject> ptr1; // Create an empty shared_ptr
    {
        auto ptr2 = std::make_shared<MyObject>();
        ptr1 = ptr2; // ptr1 and ptr2 now co-own the object. Reference count is 2.
        std::cout << "Use count inside scope: " << ptr1.use_count() << std::endl;
    } // ptr2 goes out of scope. Reference count becomes 1. The object is NOT destroyed.
    std::cout << "Use count outside scope: " << ptr1.use_count() << std::endl;
    // The object is finally destroyed when ptr1 goes out of scope.
}

int main() {
    demonstrate_unique_ptr();
    demonstrate_shared_ptr();
    return 0;
}