#pragma once

#include <iostream>

template <typename T>
void iter(T *arr, int length, void (*fp)(T&))
{
	for (int i = 0; i < length; ++i)
		fp(arr[i]);
}

template<typename T>
void square(T &num) {
    num *= num;
}

template<typename T>
void print(T &value) {
    std::cout << value << std::endl;
}
