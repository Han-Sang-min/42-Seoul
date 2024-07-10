#include "ClapTrap.hpp"

int main() {
    ClapTrap A("A");

    A.attack("enemy1");
    A.takeDamage(5);
    A.beRepaired(3);
    return 0;
}
