#include "RPN.hpp"

Rpn::Rpn(){}

Rpn::~Rpn(){}

Rpn::Rpn(const Rpn& copy){
    *this = copy;
}

Rpn& Rpn::operator=(const Rpn& copy){
    (void) copy;
    return (*this);
}

int Rpn::calculate(std::string input){

    std::stack<int> nb;
    std::stringstream s(input);
    std::string element;
    while (s >> element){
        std::cout << element[0] << std::endl;
        if (isdigit(element[0]) || (element[0] = '-' && isdigit(element[1])))
            nb.push(atoi(element.c_str()));
        if (element == "+" || element == "-" || element == "*" || element == "/"){
            if (nb.size() < 2){
                std::cout << "Need 2 numbers minimum" << std::endl;
                return 1;
            }
            break;
        }
    }
        int nbTop2 = nb.top();
        nb.pop();
        int nbTop1 = nb.top();
        nb.pop();
        if (element == "+")
            nb.push(nbTop1 + nbTop2);
        else if (element == "-")
            nb.push(nbTop1 - nbTop2);
        else if (element == "*")
            nb.push(nbTop1 * nbTop2);
        else if (element == "/"){
            if (nbTop2 == 0){
                std::cout << "Error: Division by 0" << std::endl;
                return 1;
            }
            nb.push(nbTop1 / nbTop2);
        }
        else{
            std::cout << "Invalid operand" << std::endl;
            return 1;
        }
    
    if (nb.size() == 1)
        return (nb.top());
    else{
        std::cout << "Error: Invalud expression";
        return 1;
    }
    return 0;

}