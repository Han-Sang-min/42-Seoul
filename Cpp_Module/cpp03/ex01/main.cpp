#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main() {
    ClapTrap A("A");
    ScavTrap B("B");

    A.attack("enemy1");
    A.takeDamage(5);
    A.beRepaired(3);
    B.attack("enemy2");
    B.takeDamage(5);
    B.beRepaired(3);
    B.guardGate();
    return 0;
}
