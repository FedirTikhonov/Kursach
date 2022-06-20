#pragma once
#include <iostream>
#include <string>

class worker{
public:
    worker();
    void print();
    void input();
    int getWage();
    int getHours();
private:
    std::string full_name;
    int wage;
    int hours_per_month;
};

class newVector{
private:
    worker* _arr;
    int _length;
    int _capacity;
    void _double_capacity();
public:
    newVector();
    void inputWorkers();
    void pushBack(worker someGuy);
    int countYearly();
    void output();
};
