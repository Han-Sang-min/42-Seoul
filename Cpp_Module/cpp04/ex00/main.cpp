#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main() {
    {
        const Animal* meta = new Animal();
        const Animal* j = new Dog();
        const Animal* i = new Cat();
        
        std::cout << j->getType() << " " << std::endl;
        std::cout << i->getType() << " " << std::endl;
        meta->makeSound();
        j->makeSound();
        i->makeSound();

        delete meta;
        delete j;
        delete i;
    }
    std::cout << std::endl;
    {
        const WrongAnimal* wrongMeta = new WrongAnimal();
        const WrongAnimal* wrongI = new WrongCat();

        std::cout << wrongMeta->getType() << " " << std::endl;
        std::cout << wrongI->getType() << " " << std::endl;
        wrongMeta->makeSound();
        wrongI->makeSound();

        delete wrongMeta;
        delete wrongI;
    }
    return 0;
}
