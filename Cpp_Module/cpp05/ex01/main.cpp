#include "Bureaucrat.hpp"
#include "Form.hpp"

int main() {
    try {
        Bureaucrat bill("Bill", 50);
        Form taxForm("Tax Form", 75, 50);

        std::cout << bill << std::endl;
        std::cout << taxForm << std::endl;

        bill.signForm(taxForm);
        std::cout << taxForm << std::endl;

        Bureaucrat bob("Bob", 100);
        std::cout << bob << std::endl;

        bob.signForm(taxForm);
        std::cout << taxForm << std::endl;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    try {
        Bureaucrat bob("Bob", 200);
    } catch (Bureaucrat::GradeTooHighException& e) {
        std::cout << e.what() << std::endl;
    } catch (Bureaucrat::GradeTooLowException& e) {
        std::cout << e.what() << std::endl;
    }

    try {
        Form invalidForm("Invalid Form", 0, 50);
    } catch (Form::GradeTooHighException& e) {
        std::cout << e.what() << std::endl;
    } catch (Form::GradeTooLowException& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
