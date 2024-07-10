#include "MateriaSource.hpp"

MateriaSource::MateriaSource() : _source() {}

MateriaSource::MateriaSource(MateriaSource const &other) : _source() {
    for (size_t i = 0; i < 4; ++i) {
        if (other._source[i]) {
            _source[i] = other._source[i]->clone();
        }
    }
}

MateriaSource::~MateriaSource() {
    for (size_t i = 0; i < 4; ++i) {
        if (_source[i]) {
            delete _source[i];
        }
    }
}

MateriaSource &MateriaSource::operator=(MateriaSource const &other) {
    if (this == &other) {
        return *this;
    }

    for (size_t i = 0; i < 4; ++i) {
        if (_source[i]) {
            delete _source[i];
        }
        _source[i] = other._source[i] ? other._source[i]->clone() : nullptr;
    }

    return *this;
}

void MateriaSource::learnMateria(AMateria* m) {
    if (!m) {
        return;
    }

    for (size_t i = 0; i < 4; ++i) {
        if (!_source[i]) {
            _source[i] = m->clone();
            break;
        }
    }
}

AMateria* MateriaSource::createMateria(std::string const &type) {
    for (size_t i = 0; i < 4; ++i) {
        if (_source[i] && _source[i]->getType() == type) {
            return _source[i]->clone();
        }
    }
    return nullptr;
}
