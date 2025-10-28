#include <iostream>
using namespace std;

struct TreeNode
{
    int value;
    TreeNode *left;
    TreeNode *right;
};

class IntBinaryTree
{
private:
    TreeNode *root;

    void destroySubTree(TreeNode *node)
    {
        if (node)
        {
            destroySubTree(node->left);
            destroySubTree(node->right);
            delete node;
        }
    }

    void deleteNode(int val, TreeNode *&node)
    {
        if (node == NULL)
        {
            cout << "Value not found in tree.\n";
            return;
        }

        if (val < node->value)
            deleteNode(val, node->left);
        else if (val > node->value)
            deleteNode(val, node->right);
        else
        {
            // --- Node found ---
            if (node->left == NULL && node->right == NULL)
            {
                // Case 1: No children
                delete node;
                node = NULL;
            }
            else if (node->left == NULL)
            {
                // Case 2: Only right child
                TreeNode *temp = node;
                node = node->right;
                delete temp;
            }
            else if (node->right == NULL)
            {
                // Case 3: Only left child
                TreeNode *temp = node;
                node = node->left;
                delete temp;
            }
            else
            {
                // Case 4: Two children
                // Find inorder successor (min in right subtree)
                TreeNode *temp = findMin(node->right);
                node->value = temp->value;            // Replace value
                deleteNode(temp->value, node->right); // Delete successor
            }
        }
    }

    void displayInOrder(TreeNode *node)
    {
        if (node == NULL)
            return;
        displayInOrder(node->left);
        cout << node->value << " ";
        displayInOrder(node->right);
    }

    void displayPreOrder(TreeNode *node)
    {
        if (node == NULL)
            return;
        cout << node->value << " ";
        displayPreOrder(node->left);
        displayPreOrder(node->right);
    }

    void displayPostOrder(TreeNode *node)
    {
        if (node == NULL)
            return;
        displayPostOrder(node->left);
        displayPostOrder(node->right);
        cout << node->value << " ";
    }

public:
    IntBinaryTree() { root = NULL; }
    ~IntBinaryTree() { destroySubTree(root); }

    void insertNode(int val)
    {
        TreeNode *newNode = new TreeNode{val, NULL, NULL};
        if (!root)
        {
            root = newNode;
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
                    temp->left = newNode;
                    break;
                }
            }
            else if (val > temp->value)
            {
                if (temp->right)
                    temp = temp->right;
                else
                {
                    temp->right = newNode;
                    break;
                }
            }
            else
            {
                cout << "Duplicate value found in tree.\n";
                delete newNode;
                break;
            }
        }
    }

    bool search(int num)
    {
        TreeNode *temp = root;
        while (temp)
        {
            if (temp->value == num)
                return true;
            else if (num < temp->value)
                temp = temp->left;
            else
                temp = temp->right;
        }
        return false;
    }

    void remove(int num) { deleteNode(num, root); }

    void showNodesInOrder()
    {
        if (!root)
        {
            cout << "Tree is empty.\n";
            return;
        }
        displayInOrder(root);
        cout << endl;
    }

    void showNodesPreOrder()
    {
        if (!root)
        {
            cout << "Tree is empty.\n";
            return;
        }
        displayPreOrder(root);
        cout << endl;
    }

    void showNodesPostOrder()
    {
        if (!root)
        {
            cout << "Tree is empty.\n";
            return;
        }
        displayPostOrder(root);
        cout << endl;
    }

    TreeNode *findMin(TreeNode *node)
    {
        if (node == NULL)
            return NULL;
        while (node->left)
            node = node->left;
        return node;
    }

    TreeNode *findMax(TreeNode *node)
    {
        if (node == NULL)
            return NULL;
        while (node->right)
            node = node->right;
        return node;
    }
    TreeNode *getRoot()
    {
        return root;
    }
};

// ---------------------- MENU PROGRAM ------------------------
int main()
{
    IntBinaryTree tree;
    int choice, num;

    do
    {
        cout << "\n====== Binary Search Tree Menu ======\n";
        cout << "1. Insert Node\n";
        cout << "2. Delete Node\n";
        cout << "3. Search Node\n";
        cout << "4. Display Inorder\n";
        cout << "5. Display Preorder\n";
        cout << "6. Display Postorder\n";
        cout << "7. Find Minimum\n";
        cout << "8. Find Maximum\n";
        cout << "0. Exit\n";
        cout << "=====================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value to insert: ";
            cin >> num;
            tree.insertNode(num);
            break;

        case 2:
            cout << "Enter value to delete: ";
            cin >> num;
            tree.remove(num);
            break;

        case 3:
            cout << "Enter value to search: ";
            cin >> num;
            if (tree.search(num))
                cout << num << " found in tree.\n";
            else
                cout << num << " not found in tree.\n";
            break;

        case 4:
            cout << "Inorder Traversal: ";
            tree.showNodesInOrder();
            break;

        case 5:
            cout << "Preorder Traversal: ";
            tree.showNodesPreOrder();
            break;

        case 6:
            cout << "Postorder Traversal: ";
            tree.showNodesPostOrder();
            break;

        case 7:
        {
            TreeNode *minNode = tree.findMin(tree.getRoot());
            if (minNode)
                cout << "Minimum value in tree: " << minNode->value << endl;
            else
                cout << "Value Not Found\n";
            break;
        }

        case 8:
        {
            TreeNode *maxNode = tree.findMax(tree.getRoot());
            if (maxNode)
                cout << "Maximum value in tree: " << maxNode->value << endl;
            else
                cout << "Value Not Found\n";
            break;
        }

        case 0:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
