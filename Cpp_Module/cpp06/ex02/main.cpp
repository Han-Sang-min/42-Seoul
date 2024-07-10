#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base* generate() {
    switch (rand() % 3) 
	{
        case 0:
            return new A;
        case 1:
            return new B;
        case 2:
            return new C;
    }
    return NULL;
}

void identify(Base* p) {
    if (dynamic_cast<A*>(p)) std::cout << "A\n";
    else if (dynamic_cast<B*>(p)) std::cout << "B\n";
    else if (dynamic_cast<C*>(p)) std::cout << "C\n";
}

void identify(Base& p) {
    try {
        A& refA = dynamic_cast<A&>(p);
        (void)refA;
        std::cout << "A\n";
    }
    catch (std::bad_cast&) {}

    try {
    	B& refB = dynamic_cast<B&>(p);
		(void)refB;
        std::cout << "B\n";
    }
    catch (std::bad_cast&) {}

    try {
        C& refC = dynamic_cast<C&>(p);
        (void)refC;
        std::cout << "C\n";
    }
    catch (std::bad_cast&) {}
}

int main() {
	srand(time(NULL));
	for (int i = 0; i < 10; ++i)
	{
		Base* obj = generate();
		identify(obj);
		identify(*obj);
		std::cout << std::endl;
    	delete obj;
	}
    return 0;
}
