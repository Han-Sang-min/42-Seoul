#include "Fixed.hpp"

Fixed::Fixed()
    : fixed_point_value_(0) {
}

Fixed::Fixed(const int param)
    : fixed_point_value_(param * (1 << fractional_bits_)) {
}

Fixed::Fixed(const float param)
    : fixed_point_value_(roundf(param * (1 << fractional_bits_))) {
}

Fixed& Fixed::operator=(const Fixed& other) {
    if (this != &other) {
        fixed_point_value_ = other.fixed_point_value_;
    }
    return *this;
}

Fixed::Fixed(const Fixed& other) {
    *this = other;
}

Fixed::~Fixed() {
}

int Fixed::getRawBits() const {
    return fixed_point_value_;
}

void Fixed::setRawBits(int const raw) {
    fixed_point_value_ = raw;
}

float Fixed::toFloat(void) const {
    return static_cast<float>(fixed_point_value_) / (1 << fractional_bits_);
}

int Fixed::toInt(void) const {
    return fixed_point_value_ / ((1 << fractional_bits_));
}

std::ostream& Fixed::operator<<(std::ostream& os) const {
    os << toFloat();
    return os;
}

std::ostream& operator<<(std::ostream& os, const Fixed& fixed) {
    return fixed.operator<<(os);
}

bool Fixed::operator>(const Fixed& other) const {
    return fixed_point_value_ > other.fixed_point_value_;
}

bool Fixed::operator<(const Fixed& other) const {
    return fixed_point_value_ < other.fixed_point_value_;
}

bool Fixed::operator>=(const Fixed& other) const {
    return fixed_point_value_ >= other.fixed_point_value_;
}

bool Fixed::operator<=(const Fixed& other) const {
    return fixed_point_value_ <= other.fixed_point_value_;
}

bool Fixed::operator==(const Fixed& other) const {
    return fixed_point_value_ == other.fixed_point_value_;
}

bool Fixed::operator!=(const Fixed& other) const {
    return fixed_point_value_ != other.fixed_point_value_;
}

Fixed Fixed::operator+(const Fixed& other) const {
    return Fixed((fixed_point_value_ + other.fixed_point_value_) / static_cast<float>(1 << fractional_bits_));
}

Fixed Fixed::operator-(const Fixed& other) const {
    return Fixed((fixed_point_value_ - other.fixed_point_value_) / static_cast<float>(1 << fractional_bits_));
}

Fixed Fixed::operator*(const Fixed& other) const {
    return Fixed((fixed_point_value_ * other.fixed_point_value_) / static_cast<float>(1 << fractional_bits_ * 2));
}

Fixed Fixed::operator/(const Fixed& other) const {
    return Fixed(fixed_point_value_ / static_cast<float>(other.fixed_point_value_));
}

Fixed& Fixed::operator++() {
    fixed_point_value_ += 1;
    return *this;
}

Fixed Fixed::operator++(int) {
    Fixed temp(*this);
    operator++();
    return temp;
}

Fixed& Fixed::operator--() {
    fixed_point_value_ -= 1;
    return *this;
}

Fixed Fixed::operator--(int) {
    Fixed temp(*this);
    operator--();
    return temp;
}

Fixed& Fixed::min(Fixed& a, Fixed& b) {
    return (a < b) ? a : b;
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b) {
    return (a < b) ? a : b;
}

Fixed& Fixed::max(Fixed& a, Fixed& b) {
    return (a > b) ? a : b;
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b) {
    return (a > b) ? a : b;
}
