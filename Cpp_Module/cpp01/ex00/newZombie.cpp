#include "Zombie.hpp"

Zombie* newZombie( std::string name) {
	Zombie *zombie = nullptr;
	try {
		zombie = new Zombie(name);
	} catch (const std::bad_alloc& e) {
		std::cerr << "Memory allocation failed: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
	}
	return zombie;
}