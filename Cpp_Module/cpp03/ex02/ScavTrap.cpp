#include "ScavTrap.hpp"

ScavTrap::ScavTrap(const std::string& name)
    : ClapTrap(name) {
    Hit_points = 100;
    Energy_points = 50;
    Attack_damage = 20;
    std::cout << "ScavTrap " << name << " created!" << std::endl;
}

ScavTrap::~ScavTrap() {
    std::cout << "ScavTrap " << Name << " destroyed!" << std::endl;
}

void ScavTrap::attack(const std::string& target) {
    if (Energy_points > 0) {
        std::cout << "ScavTrap " << Name << " attacks " << target << ", causing " << Attack_damage << " points of damage!" << std::endl;
        Energy_points--;
    } else {
        std::cout << "ScavTrap " << Name << " has no energy left to attack!" << std::endl;
    }
}

void ScavTrap::guardGate() {
    std::cout << "ScavTrap " << Name << " is now in Gate keeper mode!" << std::endl;
}
