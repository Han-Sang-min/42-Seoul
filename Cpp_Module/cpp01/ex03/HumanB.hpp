#pragma once
#include <iostream>
#include "Weapon.hpp"

class HumanB {
	public:
		HumanB(std::string name);
		HumanB(std::string name, Weapon &weapon_type);
		void setWeapon(Weapon &weapon_type);
		void attack();
	private:
		const std::string name;
		Weapon *weapon_type;
};