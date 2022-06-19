#include "iostream"

class bstInt {
public:
    class TreeNode{
    public:
        TreeNode* parent;
        TreeNode* left;
        TreeNode* right;
        int value;
        bool isLeaf();
    };
    TreeNode* root;
    TreeNode* getNode(int num);
    bstInt(){ root = nullptr;}
    void insert(int num);
    void print(TreeNode* currNode, int lvl);

};


