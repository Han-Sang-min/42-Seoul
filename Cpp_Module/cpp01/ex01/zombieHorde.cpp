#include "Zombie.hpp"
#include "Zombie.hpp"

Zombie* zombieHorde(int N, std::string name) {
	Zombie *horde = nullptr;
	try {
		Zombie *horde = new Zombie[N];
	} catch (const std::bad_alloc& e) {
		std::cerr << "Memory allocation failed: " << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < N; i++) {
			horde[i] = Zombie(name);
	}
	return horde;
}