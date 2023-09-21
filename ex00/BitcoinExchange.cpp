#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(): _input(""){    
}

BitcoinExchange::~BitcoinExchange(){

}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& copy): _input(copy._input){
    this->_map = copy._map;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& copy){
    (void)copy;
    return *this;
} 

double BitcoinExchange::parseBtc(std::string line, char deli){
    std::size_t pos = line.find(deli) + 1;
    std::string nbBtc = line.substr(pos);
    double Btc = strtod(nbBtc.c_str(), NULL);
    return Btc;
}

static int parseDay(std::string year, std::string month){
    if (strtod(month.c_str(), NULL) == 1 || strtod(month.c_str(), NULL) == 3 || strtod(month.c_str(), NULL) == 5
    || strtod(month.c_str(), NULL) == 7 || strtod(month.c_str(), NULL) == 8 || strtod(month.c_str(), NULL) == 10 || strtod(month.c_str(), NULL) == 12)
            return 31;
    else if (strtod(month.c_str(), NULL) == 4 || strtod(month.c_str(), NULL) == 6 || strtod(month.c_str(), NULL) == 9 || strtod(month.c_str(), NULL) == 11)
            return 30;
    else if (strtod(month.c_str(), NULL) == 2){
        if ((int)strtod(year.c_str(), NULL) % 4 == 0){
            if ((int)strtod(year.c_str(), NULL) % 100 == 0 && (int)strtod(year.c_str(), NULL) % 400 == 0)
                    return 29;
            else if ((int)strtod(year.c_str(), NULL) % 100 == 0 && (int)strtod(year.c_str(), NULL) % 400 != 0)
                    return 28;
            return 29;
        }
        return 28;
    }
    return 0;
}

static double findDate(std::string date, double nbBtc, std::map<std::string, double> map){

    std::map<std::string, double>::iterator it;
    std::map<std::string, double>::iterator itUp;
    it = map.find(date);
    itUp = map.upper_bound(date);
    double nb = 0;
    if (it != map.end()){
        nbBtc *= it->second;
        nb = nbBtc;
    }    
    else{
        if (itUp != map.begin())
            --itUp;
        nbBtc *= itUp->second;
        nb = nbBtc;
    }
    return (nb);



}

std::string BitcoinExchange::parseDate(std::string line, char deli){
    size_t i = 0;
    std::string rtnVector;
    std::string tmp = ""; 
    while (i <= line.length()){
        
        if (line[i] != deli){
            tmp += line[i];
            i++;
        }    
        else{
            rtnVector = tmp;
            tmp = "";
            return rtnVector;
        }
    }
    if (i == line.length() + 1){
        rtnVector = tmp;
        this->_errInput = true;
    }
    return rtnVector;
}

int BitcoinExchange::checkBtc(){
    if (this->_date.length() != 11)
        return 1;
    std::size_t deli = this->_date.find('-');
    std::string year, month, day;
    year = this->_date.substr(0, deli);
    month = this->_date.substr(deli + 1, deli - 2);
    day = this->_date.substr(deli + 4);
    day.erase(day.end() - 1);
    //std::cout << "year: " << year << "\nmonth: " << month << "\nday: " << day << std::endl;
    if (strtod(month.c_str(), NULL) > 12 || strtod(month.c_str(), NULL) < 1)
        return 1;
    else if (parseDay(year, month) == 31){
        if (strtod(day.c_str(), NULL) > 31 || strtod(day.c_str(), NULL) < 1) 
            return 1;
    }
     else if (parseDay(year, month) == 30){
        if (strtod(day.c_str(), NULL) > 30 || strtod(day.c_str(), NULL) < 1) 
            return 1;
    }
    else if (parseDay(year, month) == 29){
        if (strtod(day.c_str(), NULL) > 29 || strtod(day.c_str(), NULL) < 1) 
            return 1;
    }
    else if (parseDay(year, month) == 28){
        if (strtod(day.c_str(), NULL) > 28 || strtod(day.c_str(), NULL) < 1) 
            return 1;
    }
    return 0;
}

void BitcoinExchange::openAndReadFile(const std::string input){
    
    
    std::ifstream inputF(input.c_str());
    std::string line;
    
    std::getline(inputF, line);
    if (line.compare("date | value") != 0 ){
        std::cout << "Bad format input." << std::endl;
        return;
    }
    while (std::getline(inputF, line)){      
        if (line.empty())
            continue;
        this->_date = parseDate(line, '|');
        if (this->_errInput == true){
            std::cout << "Error bad Input => " << this->_date << std::endl;
            this->_errInput = false;
        }
        else{    
            this->_nbBtc = parseBtc(line, '|');
            if (this->_nbBtc > 1000)
                std::cout << "Error: too large a number." << std::endl;
            else if (this->_nbBtc < 0)
                std::cout << "Error: not a positive number." << std::endl;
            else{
                if (checkBtc() == 1)
                    std::cout << "Error bad Input => " << this->_date << std::endl;
                else if (checkBtc() == 2)
                    std::cout << this->_date << "=> 0" << std::endl; 
                else{
                    this->_nbBtc = findDate(this->_date, this->_nbBtc, this->_map);
                    std::cout << this->_date << "=> " << this->_nbBtc << std::endl;
                }
            }
        }
    }
    inputF.close();
}

int BitcoinExchange::checkDb(){
    std::ifstream dataBase("data.csv");
    std::string line;
    std::string date;
    double nbBtc;

    if (!dataBase.is_open())
        return 1;
    std::getline(dataBase, line);
    if (line.compare("date,exchange_rate") != 0)
        return 1;
    while(std::getline(dataBase, line)){
        if (line.empty())
            continue;
        date = parseDate(line, ',');
        nbBtc = parseBtc(line, ',');
        this->_map.insert(std::pair<std::string, double>(date, nbBtc));   
    }
    if (this->_map.empty() == true)
        return 1;
    dataBase.close();
    return 0;
}



BitcoinExchange::BitcoinExchange(std::string input): _input(input), _errInput(false) {
 
       if (checkDb() == 1){
            std::cout << "Error DataBase." << std::endl;
            return;
       }
        openAndReadFile(this->_input);
        
}