#include <iostream>
template <class T>
class newQueue{
public:
    newQueue();
    void pushBack(T value);
    void popFront();
    void print();
    class queueNode{
    public:
        queueNode* next;
        queueNode* prev;
        T value;
    };
private:
    queueNode* _front;
    queueNode* _back;
};

template<class T>
newQueue<T>::newQueue() {
    _front = nullptr;
    _back = nullptr;
}

template<class T>
void newQueue<T>::pushBack(T value) {
    if(_back == nullptr && _front == nullptr){
        _front = new queueNode;
        _front->value = value;
    }
    else if(_front != nullptr && _back == nullptr){
        _back = new queueNode;
        _back->value = value;
        _front->prev = _back;
        _back->next = _front;
    }
    else{
        queueNode* newNode = new queueNode;
        newNode->value = value;
        _back->prev = newNode;
        newNode->next = _back;
        _back = newNode;
    }
}

template<class T>
void newQueue<T>::print() {
    if(_front != nullptr) {
        queueNode *tmp = _front;
        while (tmp != nullptr) {
            std::cout << tmp->value << " ";
            tmp = tmp->prev;
        }
    }
    else if(_back != nullptr){
        std::cout << _back->value;
    }
    std::cout << std::endl;
}

template<class T>
void newQueue<T>::popFront() {
    if(_front != nullptr && _front->prev != _back){
        _front = _front->prev;
    }
    else if(_front != nullptr && _front->prev == _back){
        delete _front;
        _front = nullptr;
        _back->next = nullptr;
    }
    else if(_front == nullptr && _back != nullptr){
        delete _back;
        _back = nullptr;
    }
}
