#include "HumanB.hpp"

HumanB::HumanB(std::string name) : name(name), weapon_type(nullptr) {}
HumanB::HumanB(std::string name, Weapon &weapon_type) : name(name), weapon_type(&weapon_type) {}

void HumanB::setWeapon(Weapon &weapon_type) {
	this->weapon_type = &weapon_type;
}

void HumanB::attack() {
	if (weapon_type != nullptr)
		std::cout << name << " attacks with their " << weapon_type->getType() << std::endl;
	else
		std::cout << name << " attacks with their fist" << std::endl;
}