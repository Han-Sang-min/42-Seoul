#include "Cat.hpp"

Cat::Cat() {
    std::cout << "Cat constructor called" << std::endl;
    type = "Cat";
}

Cat::Cat(const Cat &src) {
    std::cout << "Cat copy constructor called" << std::endl;
    *this = src;
}

Cat &Cat::operator=(const Cat &src) {
    std::cout << "Cat assignment operator called" << std::endl;
    if (this != &src) {
        Animal::operator=(src);
    }
    return *this;
}

Cat::~Cat() {
    std::cout << "Cat destructor called" << std::endl;
}

void Cat::makeSound() const {
    std::cout << "Meow!" << std::endl;
}
