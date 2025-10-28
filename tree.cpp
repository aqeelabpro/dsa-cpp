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
    public:
        BinarySearchTree() {
            root = nullptr;
        }
        void insert(int val) {
            root = insert(root, val);
        }   
};