#include <iostream>
#include <stdexcept>

class Test1 {
public:
    Test1() {
        std::cout << "Test1 constructor called" << std::endl;
    }
    ~Test1() {
        std::cout << "Test1 destructor called" << std::endl;
    }
};

class Test2 {
public:
    Test2() {
        std::cout << "Test2 constructor called" << std::endl;
    }
    ~Test2() {
        std::cout << "Test2 destructor called" << std::endl;
    }
};

void funcB() {
    Test2 test;
    throw std::runtime_error("An error occurred in funcB");
}

void funcA() {
    Test1 test;
    funcB();
    std::cout << "This line won't be executed" << std::endl;
}

int main() {
    try {
        funcA();
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
    return 0;
}
