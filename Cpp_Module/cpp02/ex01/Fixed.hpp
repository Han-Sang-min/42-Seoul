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
private:
    int fixed_point_value;
    static const int fractional_bits = 8;

};

std::ostream& operator<<(std::ostream& os, const Fixed& fixed);