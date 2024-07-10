#pragma once

#include "AMateria.hpp"

class Ice : public AMateria {
public:
    Ice();
    virtual ~Ice();

    virtual AMateria* clone() const;
    virtual void use(ICharacter& target);
};
