#pragma once
#include <iostream>
#include <fstream>

class Replacer {
	public:
		Replacer();
		void set_parameters(const std::string &file_name, const std::string &s1, const std::string &s2);
		bool ac_checking(int ac);
		void replace();
	private:
		std::string file_name;
		std::string s1;
		std::string s2;
		bool checking(std::ifstream &input_file, std::ofstream &output_file);
};