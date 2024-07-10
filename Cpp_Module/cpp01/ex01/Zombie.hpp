#pragma once
#include <iostream>
#include <string>
#include <cstdlib>

class Zombie {
	public:
		Zombie();
		Zombie(std::string name);
		~Zombie();
		void announce();
	private:
		std::string name;
};