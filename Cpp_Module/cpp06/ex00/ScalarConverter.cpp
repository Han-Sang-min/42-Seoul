#include "ScalarConverter.hpp"
#include <exception>

void ScalarConverter::convert(std::string literal)
{
	if (!literal.empty() && literal[literal.size() - 1] == 'f')
    	literal.erase(literal.size() - 1);

	try
	{
		/* Convert to Ascii */
		char c = ft_sto<int>(literal);
		if (std::isprint(c))
			std::cout << "char: '" << c << "'\n";
		else
			std::cout << "char: Non displayable\n";
	}
	catch(const std::exception &e)
	{
		std::cout << "char: impossible\n";
	}

	try
	{
		/* Convert to int */
		int i = ft_sto<int>(literal);
		std::cout << "int: " << i << "\n";
	}
	catch(const std::exception &e)
	{
		std::cout << "int: impossible\n";
	}

	/* Check pseudo literals */
	if (processPseudoLiteral(literal))
		return ;

	try
	{
		/* Convert to float */
		float f = ft_sto<float>(literal);
		std::cout << "float: " << f << (f == (int)f ? ".0" : "") << "f\n";
	}
	catch(const std::exception &e)
	{
		std::cout << "float: impossible\n";
	}

	try
	{
		/* Convert to float */
		double d = ft_sto<double>(literal);
		std::cout << "double: " << d << (d == (int)d ? ".0" : "") << "\n";
	}
	catch(const std::exception &e)
	{
		std::cout << "double: impossible\n";
	}
}

bool ScalarConverter::processPseudoLiteral(std::string literal)
{
	if (literal == "-inf" || literal == "+inf" || literal == "nan")
	{
		std::cout << "float: " << literal << "f" << std::endl;
		std::cout << "double: " << literal << std::endl;
		return true;
	}

	return false;
}
