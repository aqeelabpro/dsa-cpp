#include <iostream>
#include <fstream>
#include <string>
using namespace std;


class Word {
public:
    string word;
    string useType[10];
    string meaning[10];
    int count;

    Word() { count = 0; }

    Word(const string& w, const string& uType, const string& mean) {
        word = w;
        useType[0] = uType;
        meaning[0] = mean;
        count = 1;
    }

    void addMeaning(const string& uType, const string& mean) {
        for (int i = 0; i < count; i++) {
            if (useType[i] == uType && meaning[i] == mean)
                return; // same usetype and meaning, don;t add
        }
        if (count < 10) {
            useType[count] = uType;
            meaning[count] = mean;
            count++;
        }
    }

    void display() const {
        cout << "Word: " << word << endl;
        for (int i = 0; i < count; i++) {
            cout << "  (" << useType[i] << ") " << meaning[i] << endl;
        }
    }
};


struct AvlNode {
    Word data;
    AvlNode* left;
    AvlNode* right;
    int height;

    AvlNode(const Word& w) : data(w), left(nullptr), right(nullptr), height(1) {}
};


int Height(AvlNode* n) { return n ? n->height : 0; }
int getBalance(AvlNode* n) { return n ? Height(n->left) - Height(n->right) : 0; }

AvlNode* rotateRight(AvlNode* y) {
    AvlNode* x = y->left;
    AvlNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = Max(Height(y->left), Height(y->right)) + 1;
    x->height = Max(Height(x->left), Height(x->right)) + 1;
    return x;
}

AvlNode* rotateLeft(AvlNode* x) {
    AvlNode* y = x->right;
    AvlNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = Max(Height(x->left), Height(x->right)) + 1;
    y->height = Max(Height(y->left), Height(y->right)) + 1;
    return y;
}
int Max(int a, int b) {
    return a >= b ? a : b;
}

// INSERT FUNCTION
AvlNode* insert(AvlNode* node, const Word& w) {
    if (!node)
        return new AvlNode(w);

    if (w.word < node->data.word)
        node->left = insert(node->left, w);
    else if (w.word > node->data.word)
        node->right = insert(node->right, w);
    else {
        // Same word → merge meaning
        node->data.addMeaning(w.useType[0], w.meaning[0]);
        return node;
    }

    node->height = 1 + Max(Height(node->left), Height(node->right));
    int balance = getBalance(node);

    // Rotations
    if (balance > 1 && w.word < node->left->data.word)
        return rotateRight(node);
    if (balance < -1 && w.word > node->right->data.word)
        return rotateLeft(node);
    if (balance > 1 && w.word > node->left->data.word) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && w.word < node->right->data.word) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// SEARCH FUNCTION
AvlNode* search(AvlNode* root, const string& key) {
    if (!root) return nullptr;
    if (key == root->data.word) return root;
    if (key < root->data.word) return search(root->left, key);
    return search(root->right, key);
}

// INORDER TRAVERSAL
void inorder(AvlNode* root) {
    if (!root) return;
    inorder(root->left);
    root->data.display();
    inorder(root->right);
}

// LOAD FROM FILE
AvlNode* loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "❌ Could not open file: " << filename << endl;
        return nullptr;
    }

    AvlNode* root = nullptr;
    string word, useType, meaning;

    while (file >> word >> useType) {
        file.ignore(); // skip space before meaning
        getline(file, meaning); // read rest of line as meaning
        Word w(word, useType, meaning);
        root = insert(root, w);
    }

    file.close();
    return root;
}

// MAIN FUNCTION
int main() {
    AvlNode* root = loadFromFile("dictionary.txt");
    if (!root) return 0;

    cout << "\n📘 DICTIONARY (Inorder Traversal):\n";
    inorder(root);

    cout << "\n🔍 Search for a word: ";
    string query;
    cin >> query;
    AvlNode* found = search(root, query);
    if (found)
        found->data.display();
    else
        cout << "Word not found.\n";
}
