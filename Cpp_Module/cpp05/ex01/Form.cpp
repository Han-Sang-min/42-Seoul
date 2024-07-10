#include "Form.hpp"

Form::Form() : name("Name"), isSigned(false), gradeToSign(150), gradeToExecute(150) {}

Form::Form(const Form &other) : name(other.name), isSigned(false), gradeToSign(other.gradeToSign), gradeToExecute(other.gradeToExecute) {}

Form &Form::operator=(const Form &other)
{
	const_cast<std::string &>(name) = other.name;
	isSigned = other.isSigned;
	const_cast<int &>(gradeToSign) = other.gradeToSign;
	const_cast<int &>(gradeToExecute) = other.gradeToExecute;

	return *this;
}

Form::~Form() {}

Form::Form(std::string name, int gradeToSign, int gradeToExecute) : name(name), isSigned(false), gradeToSign(gradeToSign), gradeToExecute(gradeToExecute) 
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

const char *Form::GradeTooHighException::what() const throw()
{
    return "Grade too high";
}

const char *Form::GradeTooLowException::what() const throw()
{
    return "Grade too low";
}

void Form::beSigned(const Bureaucrat &bureaucrat)
{
	if (gradeToSign >= bureaucrat.getGrade())
	{
		isSigned = true;
		return ;
	}
	throw GradeTooLowException();
}

std::string Form::getName() const { return name; }

bool Form::getIsSigned() const { return isSigned; }

int Form::getGradeToSign() const { return gradeToSign; }

int Form::getGradeToExecute() const { return gradeToExecute; }

std::ostream &operator<<(std::ostream &os, const Form &form)
{
	os << "name: " << form.getName() << std::endl 
	<< "isSigned: " << form.getIsSigned() << std::endl 
	<< "gradeToSign: " << form.getGradeToSign() << std::endl
	<< "gradeToExecute: " << form.getGradeToExecute() << std::endl;

	return os;
}
