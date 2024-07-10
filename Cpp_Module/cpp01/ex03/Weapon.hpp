#pragma once
#include <string>

class Weapon {
	public:
		Weapon(std::string type);
		std::string getType();
		void setType(std::string type);
	private:
		std::string type;
};