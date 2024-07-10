#include "Replacer.hpp"

int main(int ac, char *av[]) {
	Replacer rp;
	
	if (rp.ac_checking(ac)) {
		rp.set_parameters(av[1], av[2], av[3]);
		rp.replace();
		return 0;
	}
	return 1;
}
