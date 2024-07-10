#include "Replacer.hpp"

Replacer::Replacer() 
	: file_name(""), s1(""), s2("") {
}

bool Replacer::ac_checking(int ac) {
	if (ac != 4) {
		std::cerr << "Number of invalid arguments" << std::endl;
		return false;
	}
	return true;
}

void Replacer::set_parameters(const std::string &file_name, const std::string &s1, const std::string &s2) {
	this->file_name = file_name;
	this->s1 = s1;
	this->s2 = s2;
}

void Replacer::replace() {
	std::ifstream input_file(file_name);
	std::ofstream output_file(file_name + ".replace");
	if (!Replacer::checking(input_file, output_file))
		return ;
	std::string tmp;
	std::size_t pos;
	while (std::getline(input_file, tmp)) {
		while ((pos = tmp.find(s1)) != std::string::npos) {
			tmp.erase(pos, s1.length());
			tmp.insert(pos, s2);
		}
		output_file << tmp << std::endl;
	}
	input_file.close();
	output_file.close();
}

bool Replacer::checking(std::ifstream &input_file, std::ofstream &output_file) {
	if (!input_file.is_open()) {
		std::cerr << "Input file opening failed." << std::endl;
		return false;
	}
	if (!output_file.is_open()) {
		std::cerr << "output file opening failed." << std::endl;
		input_file.close();
		return false;
	}
	return true;
}
