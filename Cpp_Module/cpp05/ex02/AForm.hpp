#pragma once

#include "Bureaucrat.hpp"
#include <ostream>
#include <iostream>

class AForm
{
	protected:
		const std::string name;
		bool isSigned;
		const int gradeToSign;
		const int gradeToExecute;

	public:
		AForm();
		AForm(const AForm &other);
		AForm &operator=(const AForm &other);
		virtual ~AForm();

		std::string getName() const;
		bool getIsSigned() const;
		int getGradeToSign() const;
		int getGradeToExecute() const;

		AForm(std::string name, int gradeToSign, int gradeToExecute);
		void beSigned(const Bureaucrat &bureaucrat);

		/* Added from ex02 */
		virtual void execute(Bureaucrat const & executor) const = 0;

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

std::ostream &operator<<(std::ostream &os, const AForm &form);
