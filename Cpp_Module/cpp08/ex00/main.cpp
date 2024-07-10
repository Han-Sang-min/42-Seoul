// main.cpp
#include <deque>
#include <iostream>
#include <new>
#include <vector>
#include <queue>
#include "easyfind.hpp"

int main() {
    try {
        int arr[] = {1, 2, 3, 4, 5};

        try {
            std::vector<int> numbers(arr, arr + sizeof(arr) / sizeof(int));
            
            std::vector<int>::iterator it = easyfind(numbers, 3);
            std::cout << "Found value: " << *it << "\n";

            it = easyfind(numbers, 10);
            std::cout << "Found value: " << *it << "\n";
        } catch (const std::runtime_error& e) {
            std::cerr << e.what() << "\n";
        }

        std::cout << std::endl;

        try {
            std::deque<int> numbers;
            numbers.push_back(1);
            numbers.push_back(2);
            numbers.push_back(3);
            numbers.push_front(4);
            numbers.push_front(5);

            std::deque<int>::iterator it = easyfind(numbers, 5);
            std::cout << "Found value: " << *it << "\n";

            it = easyfind(numbers, 10);
            std::cout << "Found value: " << *it << "\n";

        } catch (const std::runtime_error& e) {
            std::cerr << e.what() << "\n";
        }
    } catch (const std::bad_alloc& e) {
        std::cerr << e.what() << "\n";
    }

    return 0;
}
