#include "Span.hpp"
#include <vector>

Span::Span() {}

Span::Span(const Span &other) {
	*this = other;
}

Span &Span::operator=(const Span &other) {
	if (this != &other) {
		vec = other.vec;
	}
	return *this;
}

Span::~Span() {}

Span::Span(unsigned int n) : N(n) {
	vec.reserve(n);
}

void Span::addNumber(int value) {
	vec.push_back(value);
}

int Span::shortestSpan() const {

}

int Span::longestSpan() const {

}

void Span::addRange(std::vector<int>::iterator st, std::vector<int>::iterator end) {
	for (std::vector<int>::iterator it; it != end; it++) {
		
	}
}