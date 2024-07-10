#include "WrongCat.hpp"

WrongCat::WrongCat() {
    std::cout << "WrongCat constructor called" << std::endl;
    type = "WrongCat";
}

WrongCat::WrongCat(const WrongCat &src) {
    std::cout << "WrongCat copy constructor called" << std::endl;
    *this = src;
}

WrongCat &WrongCat::operator=(const WrongCat &src) {
    std::cout << "WrongCat assignment operator called" << std::endl;
    if (this != &src) {
        WrongAnimal::operator=(src);
    }
    return *this;
}

WrongCat::~WrongCat() {
    std::cout << "WrongCat destructor called" << std::endl;
}

void WrongCat::makeSound() const {
    std::cout << "Wrong~!" << std::endl;
}
