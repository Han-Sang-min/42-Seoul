#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm() : AForm("Name", 72, 45) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other) : AForm(other.name, other.gradeToSign, other.gradeToExecute) {}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &other)
{
	if (this != &other)
	{
		AForm::operator=(other);
	}
	return *this;
}

RobotomyRequestForm::~RobotomyRequestForm() {}

RobotomyRequestForm::RobotomyRequestForm(std::string name) : AForm(name, 72, 45) {}

void RobotomyRequestForm::execute(Bureaucrat const & executor) const
{
	std::srand(std::time(0));
	if (isSigned && gradeToExecute >= executor.getGrade())
	{
		if (std::rand() % 2)
            std::cout << name << " has been robotomized successfully" << std::endl;
        else
            std::cout << "The robotomy of " << name << " failed" << std::endl;
		return ;
	}
	throw GradeTooLowException();
}
