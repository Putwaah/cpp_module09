#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <cstdlib>  
#include <sstream>
#include <string>
#include <stack>
#include <cctype>


class Rpn{
	private:
		std::stack<double> _numbers;
    
	public:
        Rpn();
    	Rpn(std::stack<double> number);
		~Rpn();
        Rpn(const Rpn& copy);
        Rpn& operator=(const Rpn& copy);
        void calculate(std::string input);
};
#endif
