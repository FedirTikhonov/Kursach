#include <iostream>
template <class T>
class newList {
public:
    class Node{
    public:
        Node* next;
        Node* prev;
        int value;
    };
    newList(){ _head = nullptr; _tail = nullptr;}
    void pushFront(T value);
    void pushAfter(T value, Node* someNode);
    void pushBack(T value);
    void pushBefore(T value, Node* someNode);
    void popBack();
    Node* get(int index);
    void print();
private:
    Node* _head;
    Node* _tail;
};

template<class T>
void newList<T>::pushFront(T value) {
    if(_head == nullptr && _tail == nullptr){
        _tail = new Node;
        _tail->value = value;
    }
    else if(_head == nullptr){
        _head = new Node;
        _head->value = value;
        _head->next = _tail;
        _tail->prev = _head;
    }
    else{
        Node* newNode = new Node;
        newNode->value = value;
        _head->prev = newNode;
        newNode->next = _head;
        _head = newNode;
    }
}

template<class T>
void newList<T>::print() {
    Node* tmp = _head;
    while(tmp!= nullptr){
        std::cout << tmp->value << " ";
        tmp = tmp->next;
    }
    std::cout << std::endl;
}

template<class T>
void newList<T>::pushBack(T value) {
    if(_head == nullptr && _tail == nullptr){
        _head = new Node;
        _head->value = value;
    }
    else if(_head != nullptr && _tail == nullptr){
            _tail = new Node;
            _tail->value = value;
            _tail->prev = _head;
            _head->next = _tail;
    }
    else{
        Node* newNode = new Node;
        newNode->value = value;
        _tail->next = newNode;
        newNode->prev = _tail;
        _tail = newNode;
    }
}

template<class T>
typename newList<T>::Node* newList<T>::get(int index) {
    Node* tmp = _head;
    for(int i = 0; i < index; i++) {
        tmp = tmp->next;
    }
    return tmp;
}

template<class T>
void newList<T>::pushAfter(T value, Node* someNode) {
    if(someNode == _tail){
        pushBack(value);
    }
    else{
        Node* newNode = new Node;
        newNode->value = value;
        newNode->next = someNode->next;
        newNode->prev = someNode;
        someNode->next = newNode;
        someNode->next->next->prev = newNode;
    }
}

template<class T>
void newList<T>::pushBefore(T value, newList::Node *someNode) {
    if(someNode == _head){
        pushFront(value);
    }
    else{
        Node* newNode = new Node;
        newNode->value = value;
        newNode->next = someNode;
        newNode->prev = someNode->prev;
        someNode->prev = newNode;
        someNode->prev->prev->next = newNode;
    }
}

template<class T>
void newList<T>::popBack() {
    if (this->_head == nullptr) {
        throw ("");
    }
    Node* current = this->_head;
    Node* prev_current = nullptr;
    while (current->next != nullptr) {
        prev_current = current;
        current = current->next;
    }
    if (prev_current == nullptr) {
        this->_head = nullptr;
    }
    else {
        prev_current->next = nullptr;
    }
    T data = current->value;
    delete current;
}






