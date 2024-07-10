#pragma once

#include <vector>

class Span {
	private:
		std::vector<int> vec;
		unsigned int N;

	public:
		Span();
		Span(const Span &other);
		Span &operator=(const Span &other);
		~Span();

		Span(unsigned int n);

		void addNumber(int value);
		int shortestSpan() const;
		int longestSpan() const;
		void addRange(std::vector<int>::iterator st, std::vector<int>::iterator end);
};
