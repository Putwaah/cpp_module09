#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <cstdlib>  
#include <sstream>
#include <string>
#include <stack>

class Rpn{
    public:
        Rpn();
        ~Rpn();
        Rpn(const Rpn& copy);
        Rpn& operator=(const Rpn& copy);
        int calculate(std::string input);
};
#endif