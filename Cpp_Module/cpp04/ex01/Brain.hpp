#ifndef BRAIN_H
#define BRAIN_H

#include <string>

class Brain {
	private:
		std::string idea[100];
	public:
		Brain();
		Brain(const Brain &other);
		Brain &operator=(const Brain &other);
		~Brain();
};

#endif
