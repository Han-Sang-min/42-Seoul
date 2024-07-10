#include "Dog.hpp"

Dog::Dog() {
    std::cout << "Dog constructor called" << std::endl;
    brain = new Brain;
    type = "Dog";
}

Dog::Dog(const Dog &src) {
    std::cout << "Dog copy constructor called" << std::endl;
    brain = new Brain;
    *this = src;
}

Dog &Dog::operator=(const Dog &src) {
    std::cout << "Dog assignment operator called" << std::endl;
    if (this != &src) {
        Animal::operator=(src);
    }
    return *this;
}

Dog::~Dog() {
    std::cout << "Dog destructor called" << std::endl;
    delete brain;
}

void Dog::makeSound() const {
    std::cout << "Woof!" << std::endl;
}
