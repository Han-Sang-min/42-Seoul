#ifndef WRONG_CAT_H
#define WRONG_CAT_H

#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal {
public:
    WrongCat();
    WrongCat(const WrongCat &src);
    WrongCat &operator=(const WrongCat &src);
    virtual ~WrongCat();

    void makeSound() const;
};

#endif
