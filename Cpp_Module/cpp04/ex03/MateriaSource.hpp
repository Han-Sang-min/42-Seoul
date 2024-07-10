#pragma once

#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource {
private:
    AMateria* _source[4];

public:
    MateriaSource();
    MateriaSource(MateriaSource const &other);
    virtual ~MateriaSource();

    MateriaSource &operator=(MateriaSource const &other);

	/* Copies the Materia passed as a parameter and store it in memory so it can be cloned
	later. Like the Character, the MateriaSource can know at most 4 Materias. They
	are not necessarily unique. */
    void learnMateria(AMateria* m);
	
	/* Returns a new Materia. The latter is a copy of the Materia previously learned by
	the MateriaSource whose type equals the one passed as parameter. Returns 0 if
	the type is unknown. */
    AMateria* createMateria(std::string const &type);
};
