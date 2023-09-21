#include "RPN.hpp"

int main(int ac, char **av){
    if (ac != 2){
       std::cout << "Error input." << std::endl;
       return 1; 
    }
    std::string input = av[1];
    Rpn rpn;
    rpn.calculate(input);
}