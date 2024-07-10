#pragma once
#include <iostream>

class Harl {
	public:
		void complain(const std::string level);
	private:
		void debug(void);
		void info(void);
		void warning(void);
		void error(void);

		typedef struct {
			std::string key;
			void (Harl::*func)();
		}	hash_rep;
};