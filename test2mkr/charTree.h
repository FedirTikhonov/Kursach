#include <string>
#include <iostream>

class charTree {
public:
    class Node{
    public:
        Node* left;
        Node* right;
        char value;
        Node(){left = nullptr; right = nullptr; value = '\0';}
    };
    charTree(std::string line);
    charTree(){root = nullptr;}
    void insert(char value);
    void print();
private:
    void _print(Node* currNode, int lvl);
    Node* root;
};

void charTree::insert(char value) {
    if(root == nullptr){
        root = new Node;
        root->value = value;
    }
    else{
        int placed = 0;
        Node* tmp = root;
        Node* newNode = new Node;
        newNode->value = value;
        while(placed == 0){
            if(newNode->value > tmp->value){
                if(tmp->right == nullptr){
                    tmp->right = newNode;
                    placed = 1;
                } else{
                    tmp = tmp->right;
                }
            }
            else if(newNode->value <= tmp->value){
                if(tmp->left == nullptr){
                    tmp->left = newNode;
                    placed = 1;
                } else{
                    tmp = tmp->left;
                }
            }
        }
    }
}

void charTree::_print(Node* currNode, int lvl) {
    if (currNode)
    {
        _print(currNode->left, lvl + 1);
        for (int i = 0; i < lvl; i++) std::cout << "   ";
        std::cout << currNode->value << std::endl;
        _print(currNode->right, lvl + 1);
    }
}

void charTree::print() {
    _print(root, 1);
}

charTree::charTree(std::string line) {
    root = nullptr;
    for(char c : line){
        this->insert(c);
    }
}



