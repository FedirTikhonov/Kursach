#include "newStack.h"
#include "newQueue.h"
#include "bstInt.h"
int main() {
    bstInt tree;
    tree.insert(10);
    tree.insert(7);
    tree.insert(6);
    tree.insert(8);
    tree.insert(11);
    tree.insert(10);
    tree.print(tree.root, 1);

    return 0;
}
