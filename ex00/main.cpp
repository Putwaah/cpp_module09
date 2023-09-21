#include "BitcoinExchange.hpp"


int main(int ac, char **av){

    if (ac != 2){
        std::cout << " This program take a file as argument." << std::endl;
        return 1;
    }
    BitcoinExchange test(av[1]);
    return 0;
}
