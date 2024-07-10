#pragma once

#include "Bureaucrat.hpp"
#include <ostream>
#include <iostream>

class Form
{
	private:
		const std::string name;
		bool isSigned;
		const int gradeToSign;
		const int gradeToExecute;

	public:
		Form();
		Form(const Form &other);
		Form &operator=(const Form &other);
		~Form();

		std::string getName() const;
		bool getIsSigned() const;
		int getGradeToSign() const;
		int getGradeToExecute() const;

		Form(std::string name, int gradeToSign, int gradeToExecute);
		void beSigned(const Bureaucrat &bureaucrat);

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

std::ostream &operator<<(std::ostream &os, const Form &form);
