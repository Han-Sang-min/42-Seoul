#pragma once

#include "AForm.hpp"
#include <fstream>


class ShrubberyCreationForm : public AForm
{
	public:
		ShrubberyCreationForm();
		ShrubberyCreationForm(const ShrubberyCreationForm &other);
		ShrubberyCreationForm &operator=(const ShrubberyCreationForm &other);
		~ShrubberyCreationForm();

		ShrubberyCreationForm(std::string name);

		void execute(Bureaucrat const & executor) const;
};
