#include <iostream>
using namespace std;
class TreeNode
{
public:
    int value;
    TreeNode *left, *right;
    TreeNode(int val) : value(val), left(nullptr), right(nullptr)
    {
    }
};

class BinarySearchTree
{
private:
    TreeNode *root;

public:
    BinarySearchTree(TreeNode *node = nullptr)
    {
        root = nullptr;
    }
    TreeNode *insert(TreeNode *root, int val)
    {
        if (!root)
            return new TreeNode(val);
        if (val < root->value)
            root->left = insert(root->left, val);
        if (val > root->value)
            root->right = insert(root->right, val);
        return root;
    }
    // without newline
    void levelOrder(TreeNode *root)
    {
        if (!root)
            return;
        queue<TreeNode *> levelOrderQ;
        levelOrderQ.push(root);
        while (!levelOrderQ.empty())
        {
            TreeNode *levelNode = levelOrderQ.front();
            levelOrderQ.pop();
            if (levelNode)
                cout << levelNode->value << " ";
            if (levelNode->left)
                levelOrderQ.push(levelNode->left);
            if (levelNode->right)
                levelOrderQ.push(levelNode->right);
        }
    }

    // with newline
    void levelOrderWithNewLine(TreeNode *root)
    {
        if (!root)
            return;
        queue<TreeNode *> levelOrderQ;
        levelOrderQ.push(root);
        levelOrderQ.push(nullptr); // marker for next line
        while (!levelOrderQ.empty())
        {
            TreeNode *levelNode = levelOrderQ.front();
            levelOrderQ.pop();
            if (!levelNode)
            {
                cout << "\n";
                if (!levelOrderQ.empty())
                    levelOrderQ.push(nullptr);
            }
            else
            {
                if (levelNode)
                    cout << levelNode->value << " ";
                if (levelNode->left)
                    levelOrderQ.push(levelNode->left);
                if (levelNode->right)
                    levelOrderQ.push(levelNode->right);
            }
        }
    }
    void insertByRef(TreeNode *&root, int val)
    {
        if (!root)
        {
            root = new TreeNode(val);
            return;
        }
        if (val < root->value)
            insertByRef(root->left, val);
        if (val > root->value)
            insertByRef(root->right, val);
    }
    void insertIterative(int val)
    {
        TreeNode *node = new TreeNode(val);

        if (!root)
        {
            root = node;
            return;
        }

        TreeNode *temp = root;
        while (true)
        {
            if (val < temp->value)
            {
                if (temp->left)
                    temp = temp->left;
                else
                {
                    temp->left = node;
                    return;
                }
            }
            else if (val > temp->value)
            {
                if (temp->right)
                    temp = temp->right;
                else
                {
                    temp->right = node;
                    return;
                }
            }
            else
            {
                // duplicate value
                delete node; // avoid memory leak
                return;
            }
        }
    }
    TreeNode *getRoot()
    {
        return root;
    }
    void deleteNode(TreeNode *&node, int val)
    {
        if (!node)
            return;

        if (val < node->value)
            deleteNode(node->left, val);
        else if (val > node->value)
            deleteNode(node->right, val);
        // node found
        else
        {
            // Case 1: Leaf node
            if (!node->left && !node->right)
            {
                delete node;
                node = nullptr;
            }
            // Case 2: Only right child
            else if (!node->left)
            {
                TreeNode *temp = node;
                node = node->right;
                delete temp;
            }
            // Case 3: Only left child
            else if (!node->right)
            {
                TreeNode *temp = node;
                node = node->left;
                delete temp;
            }
            // Case 4: Two children
            else
            {
                TreeNode *maxNode = findMax(node->left);
                node->value = maxNode->value;
                deleteNode(node->left, maxNode->value);
            }
        }
    }

    TreeNode *deleteNodeRec(TreeNode *node, int val)
    {
        if (!node)
            return nullptr;

        if (val < node->value)
            node->left = deleteNodeRec(node->left, val);
        else if (val > node->value)
            node->right = deleteNodeRec(node->right, val);
        // node found
        else
        {
            // Case 1: Leaf node
            if (!node->left && !node->right)
            {
                delete node;
                node = nullptr;
            }
            // Case 2: Only right child
            else if (!node->left)
            {
                TreeNode *temp = node;
                node = node->right;
                delete temp;
            }
            // Case 3: Only left child
            else if (!node->right)
            {
                TreeNode *temp = node;
                node = node->left;
                delete temp;
            }
            // Case 4: Two children
            else
            {
                TreeNode *maxNode = findMax(node->left);
                node->value = maxNode->value;
                node->left = deleteNodeRec(node->left, maxNode->value);
            }
        }
        return node;
    }

    // max in left subtree
    TreeNode *findMax(TreeNode *node)
    {
        while (node->right)
        {
            node = node->right;
        }
        return node;
    }
    void deleteN(int val)
    {
        if (!root)
            return;
        root = deleteNodeRec(root, val);
    }
    void inorder(TreeNode* rootNode) {
        if(!rootNode)
            return;
        inorder(rootNode->left);
        cout << rootNode -> value << " ";    
        inorder(rootNode->right);
    }
    void inorder() {
        if(!root)
            return;
        inorder(root->left);
        cout << root -> value << " ";    
        inorder(root->right);
    }
};

int main()
{
    // BinarySearchTree bst;
    // bst.insertIterative(10);
    // bst.insertIterative(6);
    // bst.insertIterative(5);
    // bst.insertIterative(60);
    // bst.insertIterative(61);

    // // bst.insertByRef(root, 6);
    // // bst.insertByRef(root, 5);
    // // bst.insertByRef(root, 60);
    // // bst.insertByRef(root, 61);

    // // bst.insert(root, 6);
    // // bst.insert(root, 5);
    // // bst.insert(root, 60);
    // // bst.insert(root, 61);
    // // bst.levelOrder(root); // Output: 10 6 60 5 610

    // // Output:
    // // 10
    // // 6 60
    // // 5 61
    // bst.levelOrderWithNewLine(bst.getRoot());

    BinarySearchTree bst;

    // Build initial tree
    bst.insertIterative(10);
    bst.insertIterative(6);
    bst.insertIterative(5);
    bst.insertIterative(60);
    bst.insertIterative(61);

    cout << "Before Deletion:\n";
    bst.inorder();
    // bst.levelOrderWithNewLine(bst.getRoot());
    cout << endl;

    // Delete node 60
    bst.deleteN(60);

    cout << "After Deletion of 60:\n";
    bst.inorder();
    // bst.levelOrderWithNewLine(bst.getRoot());
}