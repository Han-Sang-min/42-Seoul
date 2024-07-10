#include "Zombie.hpp"

Zombie* zombieHorde(int N, std::string name);

int main() {
	int		num = 4; // Number of zombies
	// Create a horde of zombies
	Zombie	*horde = zombieHorde(num, "Horde");
	// Announce each zombie in the horde
	for (int i = 0; i < num; i++)
		horde[i].announce();
	// Deallocate the memory
	delete[] horde;
	return 0;
}
