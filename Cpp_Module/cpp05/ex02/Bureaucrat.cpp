#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include <exception>

Bureaucrat::Bureaucrat() : name("Name"), grade(150) {}

Bureaucrat::Bureaucrat(const Bureaucrat &other) : name(other.name), grade(other.grade) {}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &other)
{
    if (this != &other)
    {
        const_cast<std::string &>(name) = other.name;
        grade = other.grade;
    }

    return *this;
}

Bureaucrat::~Bureaucrat() {}

/* Added Aform ex01 */
void Bureaucrat::signForm(AForm &Aform)
{
    try {
        Aform.beSigned(*this);
        std::cout << name << " signed " << Aform.getName() << std::endl;
    } catch (AForm::GradeTooLowException &e) {
        std::cout << name << " couldn’t sign " << Aform.getName() << " because " << e.what() << "." << std::endl;
    }
}

void Bureaucrat::executeForm(AForm const & form)
{
    try {
    form.execute(*this);
    std::cout << name << " execute " << form.getName() << std::endl;
    } catch (AForm::GradeTooLowException &e) {
        std::cout << name << " couldn’t execute " << form.getName() << " because " << e.what() << "." << std::endl;
    }
}


Bureaucrat::Bureaucrat(const std::string &name, int grade) : name(name), grade(grade)
{
    if (grade < 1)
    {
        throw GradeTooHighException();
    }
    
    if (grade > 150)
    {
        throw GradeTooLowException();
    }
}

const std::string &Bureaucrat::getName() const
{
    return name;
}

int Bureaucrat::getGrade() const
{
    return grade;
}

void Bureaucrat::incrementGrade()
{
    if (grade - 1 < 1)
    {
        throw GradeTooHighException();
    }
    grade--;
}

void Bureaucrat::decrementGrade()
{
    if (grade + 1 > 150)
    {
        throw GradeTooLowException();
    }
    grade++;
}

const char *Bureaucrat::GradeTooHighException::what() const throw()
{
    return "Grade too high";
}

const char *Bureaucrat::GradeTooLowException::what() const throw()
{
    return "Grade too low";
}

std::ostream &operator<<(std::ostream &os, const Bureaucrat bureaucrat)
{
    os << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade() << "." << std::endl;
    return os;
}
