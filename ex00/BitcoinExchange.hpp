#ifndef BITCOINEXHANGE_HPP
#define BITCOINEXHANGE_HPP

#include <iostream>
#include <algorithm>
#include <fstream>
#include<stdio.h>
#include <vector>
#include <string>
#include <map>
#include <cstdlib> 

class BitcoinExchange{
    private:
        const std::string _input;
        std::map<std::string, double> _map;
        double _nbBtc;
        std::string _date;
        bool _errInput;
    public:
        BitcoinExchange();
        ~BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& copy);
        BitcoinExchange& operator=(const BitcoinExchange& copy);
        BitcoinExchange(std::string input);
        void openAndReadFile(const std::string input);
        std::string parseDate(std::string input, char deli);
        double parseBtc(std::string line, char deli);
        int checkDb();
        int checkBtc();
};

#endif
