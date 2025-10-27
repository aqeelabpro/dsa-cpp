#include <iostream>
using namespace std;
class TreeNode
{
private:
    int data;
    TreeNode *left;
    TreeNode *right;

public:
    TreeNode(int data)
    {
        this->data = data;
        this->left = this->right = nullptr;
    }
    void setData(int data)
    {
        this->data = data;
    }
    void setLeft(TreeNode *left)
    {
        this->left = left;
    }
    void setRight(TreeNode *right)
    {
        this->right = right;
    }
    int getData()
    {
        return this->data;
    }
    TreeNode *getLeft()
    {
        return left;
    }
    TreeNode *getRight()
    {
        return right;
    }
};

bool isFullBinaryTree(TreeNode *root)
{
    if (!root)
        return true;
    if (!root->getLeft() && !root->getRight())
        return true;
    if (root->getLeft() && root->getRight())
        return (isFullBinaryTree(root->getLeft()) && isFullBinaryTree(root->getRight()));
    return false;
}

// class FullBinaryTree
// {
// private:
// };

int main()
{
    TreeNode root(10);
    root.setLeft(new TreeNode(20));
    root.setRight(nullptr);
    cout << boolalpha << isFullBinaryTree(&root);
}
