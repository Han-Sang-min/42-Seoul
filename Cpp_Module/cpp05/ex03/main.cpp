#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main() {
    Intern intern;

    // Test successful form creation
    try {
        AForm* form;

        form = intern.makeForm("shrubbery creation", "home");
        delete form;

        form = intern.makeForm("robotomy request", "Bender");
        delete form;

        form = intern.makeForm("presidential pardon", "President");
        delete form;

    } catch (std::exception & e) {
        std::cout << e.what() << std::endl;
    }

    // Test unsuccessful form creation
    try {
        AForm* form;

        form = intern.makeForm("invalid form", "target");
        delete form;
    } catch (std::exception & e) {
        std::cout << "Expected error: " << e.what() << std::endl;
    }

    return 0;
}
