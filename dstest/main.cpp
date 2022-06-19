#include "newStack.h"
#include "newQueue.h"
#include "bstInt.h"
#include "array.h"
int main() {
    customArr<int> a;
    a.pushBack(1);
    a.pushBack(2);
    a.pushBack(3);
    printInt(a);
    return 0;
}
