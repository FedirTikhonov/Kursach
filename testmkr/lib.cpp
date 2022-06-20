
#include "lib.h"

worker::worker() {
    full_name = "";
    wage = 0;
    hours_per_month = 0;
}

void worker::print() {
    std::cout << "Full name - " << full_name << std::endl;
    std::cout << "Wage - " << wage << std::endl;
    std::cout << "Hours worked per month - " << hours_per_month << std::endl;
}

void worker::input() {
    std::cout << "Enter full name:" << std::endl;
    std::getline(std::cin, full_name);
    std::cout << "Enter wage:" << std::endl;
    std::cin >> wage;
    std::cout << "Enter hours worked per month:" << std::endl;
    std::cin >> hours_per_month;
}

int worker::getHours() {
    return hours_per_month;
}

int worker::getWage() {
    return wage;
}

void newVector::_double_capacity() {
    worker* newArr = new worker[_capacity*2];
    _capacity*=2;
    for(int i = 0; i < _length; i++) {
        newArr[i] = _arr[i];
    }
    _arr = newArr;
}

newVector::newVector() {
    _length = 0;
    _capacity = 1;
    _arr = new worker[_capacity];
}

void newVector::pushBack(worker someGuy) {
    _length++;
    if(_length == _capacity){
        _double_capacity();
    }
    _arr[_length-1] = someGuy;
}

void newVector::output() {
    for(int i = 0; i < _length; i++){
        _arr[i].print();
    }
}

int newVector::countYearly() {
    int sum = 0;
    for(int i = 0; i < _length; i++){
        int tmpWage = _arr[i].getWage();
        int tmpHours = _arr[i].getHours();
        sum += tmpWage*tmpHours*12;
    }
    return sum;
}

void newVector::inputWorkers() {
    std::string line;
    std::cout << "Inputting workers' info." << std::endl;
    while(line != "stop"){
        worker tmp;
        tmp.input();
        this->pushBack(tmp);
        std::cout << "Type \"stop\" now to stop" << std::endl;
        std::cin.ignore();
        std::getline(std::cin, line);
    }
}
