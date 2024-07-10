#include "Animal.hpp"

Animal::Animal() : type("") {
    std::cout << "Animal constructor called" << std::endl;
}

Animal::Animal(const Animal &src) : type(src.type) {
    std::cout << "Animal copy constructor called" << std::endl;
}

Animal &Animal::operator=(const Animal &src) {
    std::cout << "Animal assignment operator called" << std::endl;
    if (this != &src) {
        type = src.type;
    }
    return *this;
}

Animal::~Animal() {
    std::cout << "Animal destructor called" << std::endl;
}

const std::string &Animal::getType() const {
    return type;
}

void Animal::makeSound() const {
    std::cout << "Animal sound!" << std::endl;
}
