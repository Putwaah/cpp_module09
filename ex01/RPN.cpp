#include "RPN.hpp"

Rpn::Rpn(){}

Rpn::~Rpn(){}

Rpn::Rpn(std::stack<double> number){
	this->_numbers = number;
}

Rpn::Rpn(const Rpn& copy){
    *this = copy;
}

Rpn& Rpn::operator=(const Rpn& copy){
    (void) copy;
    return (*this);
}

void Rpn::calculate(std::string input){

    char op;
    int number;
    double nb_a;
    double nb_b;
    double rst;
    for(size_t i = 0; i != input.size(); i++){

        op = input[i];
        if (op == ' ')
            continue;
        else if (isdigit(op)){
            number = op - 48;
            this->_numbers.push(number);
        }
        else if (op == '+' && this->_numbers.size() >= 2){
           nb_b = this->_numbers.top();
            this->_numbers.pop();
            nb_a = this->_numbers.top();
            this->_numbers.pop();
            this->_numbers.push(nb_a + nb_b);

        }
        else if (op == '-' && this->_numbers.size() >= 2){
           nb_b = this->_numbers.top();
            this->_numbers.pop();
            nb_a = this->_numbers.top();
            this->_numbers.pop();
            this->_numbers.push(nb_a - nb_b);
        }
        else if (op == '*' && this->_numbers.size() >= 2){
           nb_b = this->_numbers.top();
            this->_numbers.pop();
            nb_a = this->_numbers.top();
            this->_numbers.pop();
            this->_numbers.push(nb_a * nb_b);
        }
        else if (op == '/' && this->_numbers.size() >= 2){
            if (nb_b == 0){
                std::cerr << "Error: division by zero." << std::endl;
                return;
            }
            this->_numbers.pop();
            nb_a = this->_numbers.top();
            this->_numbers.pop();
            this->_numbers.push(nb_a / nb_b);
        }
        else{
            std::cerr << "Error: Bad Input." << std::endl;
            return;
        }
    }    
    if (_numbers.size() == 1){
            rst = this->_numbers.top();
            this->_numbers.pop();
            std::cout << rst << std::endl;
    }
    else
        std::cerr << "Error: Invalid Input." << std::endl;

}
