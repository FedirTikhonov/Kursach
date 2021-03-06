#include <iostream>
#include <string>
#include <vector>
template <class T>
class customArr {
private:
    void double_capacity();
    T* _arr;
    int _length;
    int _capacity;
public:
    T &operator[](int index);
    void pushBack(T value);
    void popBack();
    void sort();
    int length();
    customArr();
};

void printInt(customArr<int> arr){
    for(int i = 0; i < arr.length(); i++){
        std::cout << arr[i] << std::endl;
    }
}

void printChar(customArr<char> arr){
    for(int i = 0; i < arr.length(); i++){
        std::cout << arr[i] << std::endl;
    }
}

template<class T>
void customArr<T>::double_capacity() {
    T* newArr = new T[_capacity * 2];
    _capacity*=2;
    for(int i = 0; i < _length; i++){
        newArr[i] = _arr[i];
    }
    delete _arr;
    _arr = newArr;
}

template<class T>
customArr<T>::customArr() {
    {
        _capacity = 1;
        _length = 0;
        _arr = new T[1];
    }
}

template<class T>
void customArr<T>::pushBack(T value) {
    _length++;
    if(_length == _capacity){
        double_capacity();
    }
    _arr[_length - 1] = value;
}

template<class T>
int customArr<T>::length() {
    return _length;
}

template<class T>
T &customArr<T>::operator[](int index) {
    return _arr[index];
}

template<class T>
void customArr<T>::sort() {
    std::sort(_arr, _arr+_length);
}

template<class T>
void customArr<T>::popBack() {
    if(length()-1 < 0){
        throw ("");
    }
    _arr[length() - 1] = NULL;
    _length--;
}









