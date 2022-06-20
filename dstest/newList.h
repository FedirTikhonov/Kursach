/*
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
    Node *node = this->_head;
    T data = node->value;
    if (this->_head == this->_tail) {
        this->_head = nullptr;
        this->_tail = nullptr;
    } else {
        node->prev->next = nullptr;
        this->_head = node->prev;
    }
    delete node;
}
*/
template<typename T>
class Node {
public:
    Node(T data) {
        this->left = nullptr;
        this->right = nullptr;
        this->data = data;
    }
    Node* left;
    Node* right;
    T data;
};
template<typename T>
class DList {
private:
    Node<T>* head, * tail;
public:
    DList() {
        this->head = nullptr;
        this->tail = nullptr;
    }
    Node<T>* get(int index){
        Node<T>* tmp = head;
        for(int i = 0; i < index; i++){
            tmp = tmp->left;
        }
        return tmp;
    }
    void PushBack(T data) {
        Node<T>* node = new Node<T>(data);
        if (this->head == nullptr) {
            this->head = node;
            this->tail = node;
        }
        else {
            this->head->right = node;
            node->left = this->head;
            this->head = node;
        }
    }
    void PushFront(T data) {
        Node<T>* node = new Node<T>(data);
        if (this->head == nullptr) {
            this->head = node;
            this->tail = node;
        }
        else {
            this->tail->left = node;
            node->right = this->tail;
            this->tail = node;
        }
    }
    T PopBack() {
        Node<T>* node = this->head;
        T data = node->data;
        if (this->head == this->tail) {
            this->head = nullptr;
            this->tail = nullptr;
        }
        else {
            node->left->right = nullptr;
            this->head = node->left;
        }
        delete node;
        return data;
    }
    T PopFront() {
        Node<T>* node = this->tail;
        T data = node->data;
        if (this->head == this->tail) {
            this->head = nullptr;
            this->tail = nullptr;
        }
        else {
            node->right->left = nullptr;
            this->tail = node->right;
        }
        delete node;
        return data;
    }
    int Lenght() {
        Node<T>* current = this->tail;
        int i = 0;
        while (current != nullptr) {
            current = current->right;
            i++;
        }
        return i;
    }
    void Reverse() {
        if (this->head != this->tail) {
            Node<T>* tailRight = this->tail->right;
            Node<T>* headLeft = this->head->left;
            this->tail->left = headLeft;
            this->tail->right = nullptr;
            headLeft->right = this->tail;
            this->head->right = tailRight;
            this->head->left = nullptr;
            tailRight->left = this->head;
            swap(this->head, this->tail);
        }
    }
    T AtLeft(int index) {
        Node<T>* current = this->tail;
        for (int i = 0; i < index; i++)
        {
            current = current->right;
        }
        return current->data;
    }
    T AtRight(int index) {
        Node<T>* current = this->head;
        for (int i = this->Lenght() - 1; i > index; i--)
        {
            current = current->left;
        }
        return current->data;
    }
    void Insert(T data, int index) {
        int i = 0;
        Node<T>* current = this->tail;
        Node<T>* newNode = new Node<T>(data);
        if (index == 0) {
            this->PushFront(data);
        }
        else if (index == this->Lenght() - 1) {
            this->PushBack(data);
        }
        else {
            while (i != index - 1) {
                current = current->right;
                i++;
            }

            current->right->left = newNode;
            newNode->right = current->right;
            newNode->left = current;
            current->right = newNode;
        }
    }
};
