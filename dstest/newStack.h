#include <iostream>
template <class T>
class newStack {
public:
    newStack();
    void pushTop(T something);
    void popTop();
    void print();
    class StackNode{
    public:
        StackNode* lower;
        StackNode* higher;
        T value;
    };
private:
    StackNode* _top;
};

template<class T>
void newStack<T>::pushTop(T something) {
    if(_top == nullptr){
        _top = new StackNode;
        _top->value = something;
    }
    else{
        StackNode* newNode = new StackNode;
        newNode->value = something;
        _top->higher = newNode;
        newNode->lower = _top;
        _top = newNode;
    }
}



template<class T>
newStack<T>::newStack() {
    _top = nullptr;
}

template<class T>
void newStack<T>::print() {
    StackNode* tmp = _top;
    while(tmp != nullptr){
        std::cout << tmp->value << std::endl;
        tmp = tmp->lower;
    }
}

template<class T>
void newStack<T>::popTop() {
    if(_top->lower != nullptr) {
        _top = _top->lower;
        delete _top->higher;
        _top->higher = nullptr;
    } else{
        delete _top;
        _top = nullptr;
    }
}


