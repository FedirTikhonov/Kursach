#include "newStack.h"
#include "newQueue.h"
#include "bstInt.h"
#include "newList.h"
#include "array.h"
int main() {
    newList<int> lst;
    lst.pushBack(3);
    lst.pushBack(4);
    lst.pushBack(5);
    lst.print();
    lst.popBack();
    lst.popBack();
    lst.popBack();
    lst.print();
    return 0;
}
