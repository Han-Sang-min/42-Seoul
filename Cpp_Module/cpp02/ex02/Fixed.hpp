#pragma once
#include <cmath>
#include <iostream>
#include <cmath>

class Fixed {
public:
    Fixed();
    Fixed(const int param);
    Fixed(const float param);
    Fixed(const Fixed& other);
    Fixed& operator=(const Fixed& other);
    ~Fixed();
    
    int getRawBits() const;
    void setRawBits(int const raw);
    float toFloat( void ) const;
    int toInt( void ) const;
    std::ostream& operator<<(std::ostream& os) const;
    bool operator>(const Fixed& other) const;
    bool operator<(const Fixed& other) const;
    bool operator>=(const Fixed& other) const;
    bool operator<=(const Fixed& other) const;
    bool operator==(const Fixed& other) const;
    bool operator!=(const Fixed& other) const;
    
    Fixed operator+(const Fixed& other) const;
    Fixed operator-(const Fixed& other) const;
    Fixed operator*(const Fixed& other) const;
    Fixed operator/(const Fixed& other) const;

    Fixed& operator++();
    Fixed operator++(int);
    Fixed& operator--();
    Fixed operator--(int);

    static Fixed& min(Fixed& a, Fixed& b);
    static const Fixed& min(const Fixed& a, const Fixed& b);
    static Fixed& max(Fixed& a, Fixed& b);
    static const Fixed& max(const Fixed& a, const Fixed& b);
private:
    int fixed_point_value_;
    static const int fractional_bits_ = 8;
};

std::ostream& operator<<(std::ostream& os, const Fixed& fixed);