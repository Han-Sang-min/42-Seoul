#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon &weapon_type) : name(name), weapon_type(weapon_type) {}

void HumanA::attack() {
	std::cout << name << " attacks with their " << weapon_type.getType() << std::endl;
}