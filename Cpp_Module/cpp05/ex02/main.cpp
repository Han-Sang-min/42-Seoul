#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main() {
    // Bureaucrat Test
    try {
        Bureaucrat bob("Bob", 150);
        Bureaucrat alice("Alice", 1);
        
        std::cout << bob << std::endl;
        std::cout << alice << std::endl;
    } catch (std::exception & e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << std::endl;
    
    // ShrubberyCreationForm Test
    try {
        ShrubberyCreationForm form("home");
        Bureaucrat bob("Bob", 150);

        bob.signForm(form);
        bob.executeForm(form);
    } catch (std::exception & e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << std::endl;

    // RobotomyRequestForm Test
    try {
        RobotomyRequestForm form("robot");
        Bureaucrat alice("Alice", 1);

        alice.signForm(form);
        alice.executeForm(form);
    } catch (std::exception & e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << std::endl;

    // PresidentialPardonForm Test
    try {
        PresidentialPardonForm form("president");
        Bureaucrat alice("Alice", 1);

        alice.signForm(form);
        alice.executeForm(form);
    } catch (std::exception & e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << std::endl;

    try {
        ShrubberyCreationForm form("home");
        Bureaucrat alice("Alice", 1);

        alice.signForm(form);
        alice.executeForm(form);
    } catch (std::exception & e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
