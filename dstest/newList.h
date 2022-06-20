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
