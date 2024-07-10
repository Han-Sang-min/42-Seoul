#include "AForm.hpp"

AForm::AForm() : name("Name"), isSigned(false), gradeToSign(150), gradeToExecute(150) {}

AForm::AForm(const AForm &other) : name(other.name), isSigned(false), gradeToSign(other.gradeToSign), gradeToExecute(other.gradeToExecute) {}

AForm &AForm::operator=(const AForm &other)
{
	if (this != &other)
	{
		const_cast<std::string &>(name) = other.name;
		isSigned = other.isSigned;
		const_cast<int &>(gradeToSign) = other.gradeToSign;
		const_cast<int &>(gradeToExecute) = other.gradeToExecute;
	}

	return *this;
}

AForm::~AForm() {}

AForm::AForm(std::string name, int gradeToSign, int gradeToExecute) : name(name), isSigned(false), gradeToSign(gradeToSign), gradeToExecute(gradeToExecute) 
{
	if (gradeToSign < 1 || gradeToExecute < 1)
    {
        throw GradeTooHighException();
    }
    
	if (gradeToSign > 150 || gradeToExecute > 150)
    {
        throw GradeTooLowException();
    }
}

const char *AForm::GradeTooHighException::what() const throw()
{
    return "Grade too high";
}

const char *AForm::GradeTooLowException::what() const throw()
{
    return "Grade too low";
}

void AForm::beSigned(const Bureaucrat &bureaucrat)
{
	if (gradeToSign >= bureaucrat.getGrade())
	{
		isSigned = true;
		return ;
	}
	throw GradeTooLowException();
}

std::string AForm::getName() const { return name; }

bool AForm::getIsSigned() const { return isSigned; }

int AForm::getGradeToSign() const { return gradeToSign; }

int AForm::getGradeToExecute() const { return gradeToExecute; }

std::ostream &operator<<(std::ostream &os, const AForm &form)
{
	os << "name: " << form.getName() << std::endl 
	<< "isSigned: " << form.getIsSigned() << std::endl 
	<< "gradeToSign: " << form.getGradeToSign() << std::endl
	<< "gradeToExecute: " << form.getGradeToExecute() << std::endl;

	return os;
}
