#include "Zombie.hpp"

Zombie* newZombie( std::string name);
void randomChump( std::string name);

int main() {
	// Create a zombie on the heap
	Zombie *zombie = newZombie("Zombie");
	zombie->announce();
	// Create a zombie on the stack
	randomChump("Chump");
	// Delete the heap zombie
	delete zombie;
	return 0;
}