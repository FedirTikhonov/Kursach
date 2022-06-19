//
// Created by Fedir Tikhonov on 18.06.2022.
//

#include "bstInt.h"

void bstInt::insert(int num) {
    if(root == nullptr){
        root = new TreeNode;
        root->value = num;
    }
    else{
        TreeNode* newNode = new TreeNode;
        newNode->value = num;
        TreeNode* tmpNode = root;
        int placed = 0;
        while (placed == 0){
            if(newNode->value >= tmpNode->value){
                if(tmpNode->left == nullptr){
                    tmpNode->left = newNode;
                    newNode->parent = tmpNode;
                    placed = 1;
                }
                else{
                    tmpNode = tmpNode->left;
                }
            }
            else if(newNode->value < tmpNode->value){
                if(tmpNode->right == nullptr){
                    tmpNode->right = newNode;
                    newNode->parent = tmpNode;
                    placed = 1;
                }
                else{
                    tmpNode = tmpNode->right;
                }
            }
        }
    }
}

void bstInt::print(bstInt::TreeNode *currNode, int lvl) {
    if (currNode)
    {
        print(currNode->left, lvl + 1);
        for (int i = 0; i < lvl; i++) std::cout << "   ";
        std::cout << currNode->value << std::endl;
        print(currNode->right, lvl + 1);
    }
}

bstInt::TreeNode *bstInt::getNode(int num) {
    TreeNode* tmp = root;
    int found = 0;
    while(found == 0 && tmp != nullptr){
        if(num == tmp->value){
            found = 1;
        }
        else if(num < tmp->value){
            tmp = tmp->left;
        }
        else if(num >= tmp->value){
            tmp = tmp->right;
        }
    }
    return tmp;
}

bool bstInt::TreeNode::isLeaf() {
    if(right == nullptr && left == nullptr){
        return true;
    }
    return false;
}
