#include "Fixed.hpp"

Fixed::Fixed()
    : fixed_point_value(0) {
    std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int param)
    : fixed_point_value(param * (1 << fractional_bits)) {
    std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed(const float param)
    : fixed_point_value(roundf(param * (1 << fractional_bits))) {
    std::cout << "Float constructor called" << std::endl;
}

Fixed& Fixed::operator=(const Fixed& other) {
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other) {
        fixed_point_value = other.fixed_point_value;
    }
    return *this;
}

Fixed::Fixed(const Fixed& other) {
    std::cout << "Copy constructor called" << std::endl;
    *this = other;
}

Fixed::~Fixed() {
    std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits() const {
    std::cout << "getRawBits member function called" << std::endl;
    return fixed_point_value;
}

void Fixed::setRawBits(int const raw) {
    fixed_point_value = raw;
}

float Fixed::toFloat(void) const {
    return static_cast<float>(fixed_point_value) / (1 << fractional_bits);
}

int Fixed::toInt(void) const {
    return fixed_point_value / static_cast<int>((1 << fractional_bits));
}

std::ostream& Fixed::operator<<(std::ostream& os) const {
    os << toFloat();
    return os;
}

std::ostream& operator<<(std::ostream& os, const Fixed& fixed) {
    return fixed.operator<<(os);
}

