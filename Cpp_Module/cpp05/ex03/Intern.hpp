#pragma once

#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

class Intern
{
	private:
		struct FormType 
		{
   			std::string key;
  	  		AForm *(Intern::*func)(std::string);
		};
		AForm *ShrubberyCreationFormConstructor(std::string formName);
		AForm *PresidentialPardonFormConstructor(std::string formName);
		AForm *RobotomyRequestFormConstructor(std::string formName);
		
	public:
		Intern();
		Intern(const Intern &other);
		Intern &operator=(const Intern &other);
		~Intern();

		AForm *makeForm(std::string formType, std::string formName);
};
