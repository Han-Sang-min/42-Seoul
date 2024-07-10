#pragma once
#include <iostream>
#include <ostream>
#include <string>
#include <stdexcept>

class Bureaucrat
{
    private:
        const std::string name;
        int grade;

    public:
        Bureaucrat();
        Bureaucrat(const Bureaucrat &other);
        Bureaucrat &operator=(const Bureaucrat &other);
        ~Bureaucrat();

        Bureaucrat(const std::string &name, int grade);
        const std::string &getName() const;
        int getGrade() const;
        void incrementGrade();
        void decrementGrade();
        
        class GradeTooHighException : public std::exception
        {
        public:
            const char *what() const throw();
        };

        class GradeTooLowException : public std::exception
        {
        public:
            const char *what() const throw();
        };
};

std::ostream &operator<<(std::ostream &os, const Bureaucrat bureaucrat);
