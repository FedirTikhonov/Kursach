#include "newStack.h"
#include "newQueue.h"
#include "bstInt.h"
#include "newList.h"
#include "array.h"
#include "setInt.h"
void print(DList<int> lst);
int main() {
    bstInt tree;
    tree.insert(6);
    tree.insert(3);
    tree.insert(9);
    tree.insert(12);
    tree.insert(7);
    tree.insert(2);
    tree.insert(5);
    tree.print(tree.root, 1);
    return 0;
}

void print(DList<int> lst){
    Node<int>* tmp = lst.get(0);
    std::cout << tmp->data;
}


