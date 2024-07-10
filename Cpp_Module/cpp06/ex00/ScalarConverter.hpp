#pragma once

#include <iostream>
#include <limits>
#include <sstream>

class ScalarConverter
{
	private:
		ScalarConverter();
		ScalarConverter(const ScalarConverter &other);
		ScalarConverter &operator=(const ScalarConverter &other);
		~ScalarConverter();

	public:
		static void convert(std::string literal);
		static bool processPseudoLiteral(std::string literal);

		template<typename T>
		static T ft_sto(std::string str) 
		{
			std::stringstream ss(str);
			T result;
			
			if (!(ss >> result))
				throw std::exception();
			return result;
		}
};
