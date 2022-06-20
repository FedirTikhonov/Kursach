#include "setInt.h"

bool isNumber(std::string num){
    for(const char& c : num){
        if(!isdigit(c)){
            return false;
        }
    }
    return true;
}

int setInt::length() {
    return _length;
}

int setInt::capacity() {
    return _capacity;
}

bool setInt::_is_duplicate(int num) {
    for(int i = 0; i < length(); i++){
        if(num == _set[i]){
            return true;
        }
    }
    return false;
}

setInt::setInt() {
    _set = new int[1];
    _capacity = 1;
    _length = 0;
}

void setInt::_double_capacity() {
    int* newArr = new int[_capacity*2];
    _capacity *= 2;
    for(int i = 0; i < _length; i++){
        newArr[i] = _set[i];
    }
    _set = newArr;
}

void setInt::insert(int num) {
    if(!_is_duplicate(num)) {
        _push_back(num);
        std::sort(_set, _set + _length);
    }
}

void setInt::_push_back(int num) {
    _length++;
    if(_length == _capacity){
        _double_capacity();
    }
    _set[_length-1] = num;
}

void setInt::print() {
    for(int i = 0; i<_length; i++){
        std::cout << _set[i] << " ";
    }
    std::cout << std::endl;
}

void setInt::input() {
    std::string num;
    std::cout << "Enter numbers into sets. If input is not entirely number, input stops." << std::endl;
    std::getline(std::cin, num);
    while (isNumber(num)){
        insert(std::stoi(num));
        std::getline(std::cin, num);
    }


}

setInt setInt::operator+(setInt set) {
    setInt newSet;
    for(int i = 0; i < set.length(); i++){
        newSet.insert(set._set[i]);
    }
    for(int i = 0; i < this->_length; i++){
        newSet.insert(this->_set[i]);
    }
    return newSet;
}

setInt setInt::operator*(setInt anSet) {
    setInt newSet;
    for(int i = 0; i < this->_length; i++){
        if(anSet.isIn(this->_set[i])){
            newSet.insert(this->_set[i]);
        }
    }
    return newSet;
}

bool setInt::isIn(int num) {
    for(int numID = 0; numID < _length; numID++){
        if(num == _set[numID]){
            return true;
        }
    }
    return false;
}

setInt setInt::operator/(setInt anSet) {
    setInt newSet;
    for(int numID = 0; numID < this->_length; numID++){
        if(!anSet.isIn(this->_set[numID])){
            newSet.insert(this->_set[numID]);
        }
    }
    return newSet;
}

std::ostream &operator<<(std::ostream &out, setInt set) {
    for(int i = 0; i < set._length; i++){
        out << set._set[i] << " ";
    }
    out << std::endl;
    return out;
}

