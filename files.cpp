#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Word {
public:
    string word;
    string useType[5];
    string meaning[5];
    int count;

    Word() { count = 0; }

    Word(string w, string u, string m) {
        word = w;
        useType[0] = u;
        meaning[0] = m;
        count = 1;
    }

    void addMeaning(string u, string m) {
        for (int i = 0; i < count; i++) {
            if (useType[i] == u && meaning[i] == m)
                return;
        }
        if (count < 5) {
            useType[count] = u;
            meaning[count] = m;
            count++;
        }
    }

    void display() const {
        cout << "Word: " << word << "\n";
        for (int i = 0; i < count; i++) {
            cout << "  (" << useType[i] << ") " << meaning[i] << "\n";
        }
    }
};

//  AVL Node 
struct AvlNode {
    Word word;
    AvlNode* Left;
    AvlNode* Right;
    int Height;
};

//  AVL Tree 
class AvlTree {
public:
    AvlNode* Root;
    AvlTree() { Root = NULL; }

    int Height(AvlNode* p) {
        if (!p)
            return -1;
        return Max(Height(p->Left), Height(p->Right)) + 1;
    }

    int Max(int a, int b) {
        return a >= b ? a : b;
    }

    AvlNode* SingleRotateRight(AvlNode* K2) {
        AvlNode* K1 = K2->Left;
        K2->Left = K1->Right;
        K1->Right = K2;
        K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;
        K1->Height = Max(Height(K1->Left), K2->Height) + 1;
        return K1;
    }

    AvlNode* SingleRotateLeft(AvlNode* K1) {
        AvlNode* K2 = K1->Right;
        K1->Right = K2->Left;
        K2->Left = K1;
        K1->Height = Max(Height(K1->Left), Height(K1->Right)) + 1;
        K2->Height = Max(Height(K2->Right), K1->Height) + 1;
        return K2;
    }

    AvlNode* DoubleRotateLeftRight(AvlNode* K3) {
        K3->Left = SingleRotateLeft(K3->Left);
        return SingleRotateRight(K3);
    }

    AvlNode* DoubleRotateRightLeft(AvlNode* K1) {
        K1->Right = SingleRotateRight(K1->Right);
        return SingleRotateLeft(K1);
    }

    //  Insert 
    AvlNode* Insert(Word word, AvlNode*& T) {
        if (!T) {
            T = new AvlNode;
            T->word = word;
            T->Height = 0;
            T->Left = T->Right = NULL;
        }
        else if (word.word < T->word.word) {
            T->Left = Insert(word, T->Left);
            if (Height(T->Left) - Height(T->Right) == 2) {
                if (word.word < T->Left->word.word)
                    T = SingleRotateRight(T);
                else
                    T = DoubleRotateLeftRight(T);
            }
        }
        else if (word.word > T->word.word) {
            T->Right = Insert(word, T->Right);
            if (Height(T->Left) - Height(T->Right) == -2) {
                if (word.word > T->Right->word.word)
                    T = SingleRotateLeft(T);
                else
                    T = DoubleRotateRightLeft(T);
            }
        }
        else {
            // Duplicate word — merge meanings
            T->word.addMeaning(word.useType[0], word.meaning[0]);
        }

        T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
        return T;
    }

    void Insert(Word word) {
        Root = Insert(word, Root);
    }

    //  Search 
    AvlNode* Search(AvlNode* T, string key) {
        if (!T)
            return NULL;
        if (key == T->word.word)
            return T;
        if (key < T->word.word)
            return Search(T->Left, key);
        else
            return Search(T->Right, key);
    }

    //  Traversals 
    void InOrder(AvlNode* T) {
        if (T != NULL) {
            InOrder(T->Left);
            T->word.display();
            InOrder(T->Right);
        }
    }

    void DisplayInOrder() {
        cout << "\n=== InOrder (Dictionary) ===\n";
        InOrder(Root);
    }
};

//  Load from File 
void LoadFromFile(AvlTree& tree, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Cannot open file " << filename << endl;
        return;
    }

    string word, useType, meaning;
    while (file >> word >> useType) {   // read word by word
        file.ignore();
        getline(file, meaning);         // remaining chars are meaning
        Word temp(word, useType, meaning);
        tree.Insert(temp);
    }

    file.close();
}

//  MAIN 
int main() {
    AvlTree tree;
    LoadFromFile(tree, "dictionary.txt");

    int choice;
    do {
        cout << "\n========= AVL TREE DICTIONARY =========\n";
        cout << "1. Display All Words (InOrder)\n";
        cout << "2. Search for a Word\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            tree.DisplayInOrder();
            break;

        case 2: {
            string key;
            cout << "Enter word to search: ";
            cin >> key;
            AvlNode* result = tree.Search(tree.Root, key);
            if (result)
                result->word.display();
            else
                cout << "Word not found.\n";
            break;
        }

        case 3:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 3);

    return 0;
}
