#pragma once

#include <iostream>
#include <string>
#include "ICharacter.hpp"

/* global class ? */
class ICharacter;

/* abstract class for materia(ice, cure) */
class AMateria {
protected:
    std::string _type;

public:
	AMateria(std::string const & type);
    virtual ~AMateria();

	std::string const & getType() const;
	virtual AMateria* clone() const = 0;
    virtual void use(ICharacter& target);
};
