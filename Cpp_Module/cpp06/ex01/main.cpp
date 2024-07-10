#include "Serializer.hpp"

#include <iostream>

int main()
{
	Data data;
	data.x = 42;

	Data *dataPointer = &data;
	uintptr_t SerializedData = Serializer::serialize(dataPointer);

	/* Output part */
	std::cout << dataPointer << " : 0x" << std::hex << SerializedData << std::dec << std::endl;
	
	Data *deSerializedData = Serializer::deserialize(SerializedData);

	/* Output part */
	std::cout << dataPointer->x << " : " << deSerializedData->x << std::endl; 
}
