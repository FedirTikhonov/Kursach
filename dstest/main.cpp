#include "newStack.h"
#include "newQueue.h"
#include "bstInt.h"
#include "newList.h"
#include "array.h"
#include "setInt.h"
void print(DList<int> lst);
int main() {
    setInt s;
    s.input();
    setInt k;
    k.input();
    setInt n1 = s + k;
    std::cout << n1;
    setInt n2 = s * k;
    std::cout << n2;
    setInt n3 = s / k;
    std::cout << n3;
    return 0;
}

void print(DList<int> lst){
    Node<int>* tmp = lst.get(0);
    std::cout << tmp->data;
}


