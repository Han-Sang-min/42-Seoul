#include "ClapTrap.hpp"

ClapTrap::ClapTrap(const std::string& name)
    : Name(name), Hit_points(10), Energy_points(10), Attack_damage(0) {
    std::cout << "ClapTrap " << name << " created!" << std::endl;
}

ClapTrap::~ClapTrap() {
    std::cout << "ClapTrap " << Name << " destroyed!" << std::endl;
}

void ClapTrap::attack(const std::string& target) {
    if (Energy_points > 0) {
        std::cout << "ClapTrap " << Name << " attacks " << target << ", causing " << Attack_damage << " points of damage!" << std::endl;
        Energy_points--;
    } else {
        std::cout << "ClapTrap " << Name << " has no energy left to attack!" << std::endl;
    }
}

void ClapTrap::takeDamage(unsigned int amount) {
    if (Hit_points > 0) {
        Hit_points -= amount;
        if (Hit_points < 0) Hit_points = 0;
        std::cout << "ClapTrap " << Name << " takes " << amount << " points of damage!" << std::endl;
    } else {
        std::cout << "ClapTrap " << Name << " is already destroyed!" << std::endl;
    }
}

void ClapTrap::beRepaired(unsigned int amount) {
    if (Energy_points > 0) {
        Hit_points += amount;
        std::cout << "ClapTrap " << Name << " is repaired for " << amount << " points!" << std::endl;
        Energy_points--;
    } else {
        std::cout << "ClapTrap " << Name << " has no energy left to repair!" << std::endl;
    }
}
