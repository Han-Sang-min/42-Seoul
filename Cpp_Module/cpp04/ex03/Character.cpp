#include "Character.hpp"

Character::Character() : _name("?"), _inventory() {}

Character::Character(std::string const &name) : _name(name), _inventory() {}

Character::Character(Character const &other) : _name(other._name), _inventory() {
    for (size_t i = 0; i < 4; ++i) {
        if (other._inventory[i]) {
            _inventory[i] = other._inventory[i]->clone();
        }
    }
}

Character::~Character() {
    for (size_t i = 0; i < 4; ++i) {
        if (_inventory[i]) {
            delete _inventory[i];
        }
    }
}

Character &Character::operator=(Character const &other) {
    if (this == &other) {
        return *this;
    }

    _name = other._name;
    for (size_t i = 0; i < 4; ++i) {
        if (_inventory[i]) {
            delete _inventory[i];
        }
        _inventory[i] = other._inventory[i] ? other._inventory[i]->clone() : nullptr;
    }

    return *this;
}

std::string const &Character::getName() const {
    return _name;
}

void Character::equip(AMateria* m) {
    if (!m) {
        return;
    }

    for (size_t i = 0; i < 4; ++i) {
        if (!_inventory[i]) {
            _inventory[i] = m;
            break;
        }
    }
}

void Character::unequip(int idx) {
    if (idx >= 0 && idx < 4) {
        _inventory[idx] = nullptr;
    }
}

void Character::use(int idx, ICharacter& target) {
    if (idx >= 0 && idx < 4 && _inventory[idx]) {
        _inventory[idx]->use(target);
    }
}
