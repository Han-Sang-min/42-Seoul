#include "Intern.hpp"

Intern::Intern() {}

Intern::Intern(const Intern &other) { (void)other; }

Intern &Intern::operator=(const Intern &other) 
{
	(void)other;
	return *this;
}

Intern::~Intern() {}

AForm *Intern::ShrubberyCreationFormConstructor(std::string formName) 
{
    return new ShrubberyCreationForm(formName);
}

AForm *Intern::PresidentialPardonFormConstructor(std::string formName) 
{
    return new PresidentialPardonForm(formName);
}

AForm *Intern::RobotomyRequestFormConstructor(std::string formName)
{
    return new RobotomyRequestForm(formName);
}

AForm *Intern::makeForm(std::string formType, std::string formName) {
    static const FormType formTypes[3] = {
        {"shrubbery creation", &Intern::ShrubberyCreationFormConstructor},
        {"presidential pardon", &Intern::PresidentialPardonFormConstructor},
        {"robotomy request", &Intern::RobotomyRequestFormConstructor}
    };

    for (int i = 0; i < 3; i++) {
        if (formTypes[i].key == formType) {
			std::cout << "Intern creates " << formName << std::endl;
            return (this->*formTypes[i].func)(formName);
        }
    }

    throw std::invalid_argument("Invalid form type.");
}

