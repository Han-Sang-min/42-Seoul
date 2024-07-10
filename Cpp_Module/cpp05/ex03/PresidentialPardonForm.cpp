#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm() : AForm("Name", 25, 5) {}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &other) : AForm(other.name, other.gradeToSign, other.gradeToExecute) {}

PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &other)
{
	if (this != &other)
	{
		AForm::operator=(other);
	}
	return *this;
}

PresidentialPardonForm::~PresidentialPardonForm() {}

PresidentialPardonForm::PresidentialPardonForm(std::string name) : AForm(name, 25, 5) {}

void PresidentialPardonForm::execute(Bureaucrat const & executor) const
{
	if (isSigned && gradeToExecute >= executor.getGrade())
	{
		std::cout << name << " has been pardoned by Zaphod Beeblebrox" << std::endl;
		return ;
	}
	throw GradeTooLowException();
}
