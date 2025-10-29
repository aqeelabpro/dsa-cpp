#include <iostream>
using namespace std;
class TreeNode {
    public:
        int value;
        TreeNode *left, *right;
        TreeNode(int val) : value(val), left(nullptr), right(nullptr) {

        }
};

class BinarySearchTree {
    private:
        TreeNode* root;
        // with root
        
    public:
    TreeNode* insert(TreeNode* root, int val) {
            if(!root) {
                return new TreeNode(val);
            }
            if(val < root->value) {
                root->left = insert(root->left, val);
            }
            else if(val > root->value) {
                root->right = insert(root->right, val);
            }
            return root;
        }

        // iterative
        void insertIterative(int val) {
            if(!root)
                root = new TreeNode(val);
            TreeNode* temp = root;
            while(temp) {
                if(val < temp->value) {
                    if(temp->left)
                        temp = temp->left;
                    else {
                        temp->left = new TreeNode(val);
                        return;
                    }    
                }
                else if(val > temp->value) {
                    if(temp->right)
                        temp = temp->right;
                    else {
                        temp->right = new TreeNode(val);
                        return;
                    }    
                }
                else {
                    // Duplicate value — do nothing
                    return;
                }
            }    
        }

        // iterative
        bool search(int val) {
            if(!root)
                return false;
            TreeNode* temp = root;
            while(temp) {
                if(val == temp->value)
                    return true;
                else if(val < temp->value) {
                    temp = temp->left;
                }
                else temp = temp->right;
            }
            return false;
        }
        // recursive
        bool search(TreeNode* root, int val) {
            if(!root)
                return false;
            if(val == root->value)
                return true;    
            if(val < root->value)
                return search(root->left, val);
            else
                return search(root->right, val);        
        }
        int findHeight(TreeNode* root) {
            if(!root)
                return -1;
            int leftHeight =  findHeight(root->left);
            int rightHeight =  findHeight(root->right);
            return max(leftHeight, rightHeight) + 1;    
        }
        int max(int first, int second) {
            return first>=second ? first: second;
        }
        BinarySearchTree() {
            root = nullptr;
        }
        void insert(int val) {
            root = insert(root, val);
        }   
        void inorder(TreeNode* rootNode) {
            if(!rootNode)
                return;
            inorder(rootNode->left);
            cout << rootNode -> value << " ";    
            inorder(rootNode->right);
        }
        void displayInOrder() {
            inorder(root);
            cout << "\n";
        }
        int height() {
            return findHeight(root);
        }
};

int main() {
    BinarySearchTree bst;

    // Insert values
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);
    bst.insert(12);
    bst.insert(18);
    bst.displayInOrder();

    // Search test
    cout << "Searching 7: " << (bst.search(7) ? "Found" : "Not Found") << endl;
    cout << "Searching 20: " << (bst.search(20) ? "Found" : "Not Found") << endl;

    // Height test
    cout << "Height of tree: " << bst.height() << endl; // optional — change if you want to pass bst.root

    return 0;
}
