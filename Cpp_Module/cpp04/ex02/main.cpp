#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main() {
    const int n = 4;
    Animal *animals[4];
    for (int i = 0; i < n / 2; i++) {
        animals[i] = new Dog();
    }
    std::cout << std::endl;
    for (int i = n / 2; i < n; i++) {
        animals[i] = new Cat();
    }
    std::cout << std::endl;
    Dog a, b;
    a = b;
    std::cout << &a << std::endl;
    std::cout << &b << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < n; ++i) {
        delete animals[i];
    }
    return 0;
}
