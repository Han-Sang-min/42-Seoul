#include "FragTrap.hpp"
#include <iostream>

FragTrap::FragTrap(const std::string& name)
    : ClapTrap(name) {
    Hit_points = 100;
    Energy_points = 100;
    Attack_damage = 30;
    std::cout << "FragTrap " << name << " created!" << std::endl;
}

FragTrap::~FragTrap() {
    std::cout << "FragTrap " << Name << " destroyed!" << std::endl;
}

void FragTrap::attack(const std::string& target) {
    if (Energy_points > 0) {
        std::cout << "FragTrap " << Name << " attacks " << target << ", causing " << Attack_damage << " points of damage!" << std::endl;
        Energy_points--;
    } else {
        std::cout << "FragTrap " << Name << " has no energy left to attack!" << std::endl;
    }
}

void FragTrap::highFivesGuys() {
    std::cout << "FragTrap " << Name << " requests a high five!" << std::endl;
}
