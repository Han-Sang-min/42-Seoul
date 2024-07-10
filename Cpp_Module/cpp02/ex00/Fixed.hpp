#pragma once
#include <cmath>
#include <iostream>
#include <cmath>

class Fixed {
public:
    Fixed();
    Fixed(const Fixed& other);
    Fixed& operator=(const Fixed& other);
    ~Fixed();
    
    int getRawBits() const;
    void setRawBits(int const raw);
private:
    int fixed_point_value;
    static const int fractional_bits = 8;
};
