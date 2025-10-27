#include <iostream>
#include <queue>
using namespace std;

// Define a Treenode structure for the binary tree
struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int val)
    {
        data = val;
        left = right = nullptr;
    }
};

// Function to perform Level Order Traversal
void levelOrder(TreeNode *root)
{
    if (root == nullptr)
        return;

    queue<TreeNode *> q; // Queue for BFS
    q.push(root);
    q.push(nullptr); // marker for \n

    while (!q.empty())
    {
        TreeNode *curr = q.front();
        q.pop();
        if (curr == nullptr)
        {
            cout << "\n"; // end of current level
            if (!q.empty())
                q.push(nullptr); // add marker for next level
        }
        else
        {
            cout << curr->data << " ";

            if (curr->left)
                q.push(curr->left);
            if (curr->right)
                q.push(curr->right);
        }
    }
}

// Helper function to build a sample tree
TreeNode *buildTree()
{
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    return root;
}

// Main function
int main()
{
    TreeNode *root = buildTree();
    cout << "Level Order Traversal: \n";
    levelOrder(root);
    cout << endl;
    return 0;
}

