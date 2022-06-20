#include "newStack.h"
#include "newQueue.h"
#include "bstInt.h"
#include "newList.h"
#include "array.h"
void print(DList<int> lst);
int main() {
    DList<int> lst;
    lst.PushFront(7);
    lst.PushFront(8);
    print(lst);
    return 0;
}

void print(DList<int> lst){
    Node<int>* tmp = lst.get(0);
    std::cout << tmp->data;
}
