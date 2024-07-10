#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("Name", 145, 137) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other) : AForm(other.name, other.gradeToSign, other.gradeToExecute) {}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other)
{
	if (this != &other)
	{
		AForm::operator=(other);
	}
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

ShrubberyCreationForm::ShrubberyCreationForm(std::string name) : AForm(name, 145, 137) {}

void ShrubberyCreationForm::execute(Bureaucrat const & executor) const
{
	if (isSigned && gradeToExecute >= executor.getGrade())
	{
		std::ofstream ofs(name + "_shrubbery");
        ofs << "     ^    " << std::endl;
		ofs << "    ^^^   " << std::endl;
		ofs << "   ^^^^^  " << std::endl;
		ofs << "  ^^^^^^^ " << std::endl;
		ofs << " ^^^^^^^^^" << std::endl;
		ofs << "^^^^^^^^^^^" << std::endl;
		ofs << "    |||   " << std::endl;
		ofs.close();
		
		return ;
	}
	throw GradeTooLowException();
}
