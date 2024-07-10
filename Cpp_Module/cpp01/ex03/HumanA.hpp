#pragma once
#include <iostream>
#include "Weapon.hpp"

class HumanA {
	public:
		HumanA(std::string name, Weapon &weapon_type);
		void attack();
	private:
		const std::string name;
		Weapon &weapon_type;
};