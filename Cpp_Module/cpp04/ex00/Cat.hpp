#ifndef CAT_H
#define CAT_H

#include "Animal.hpp"

class Cat : public Animal {
public:
    Cat();
    Cat(const Cat &src);
    Cat &operator=(const Cat &src);
    virtual ~Cat();

    void makeSound() const;
};

#endif
