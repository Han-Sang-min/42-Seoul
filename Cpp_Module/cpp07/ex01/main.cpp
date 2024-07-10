#include "iter.hpp"

int main( void ) {
	{
		int arr[3] = {2, 3, 5};
		iter<int>(arr, 3, square);
		iter<int>(arr, 3, print);
	}
	std::cout << std::endl;
	{
		double arr[3] = {2.5, 3.5, 5.5};
		iter<double>(arr, 3, square);
		iter<double>(arr, 3, print); 
	}
    return 0;
}
