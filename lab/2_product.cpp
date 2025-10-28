#include <iostream>
#include <string>
using namespace std;

struct Product
{
    int id;
    string name;
    string category;
    float price;
    string person_name;
};

struct TreeNode
{
    Product product;
    TreeNode *left;
    TreeNode *right;
};

class ProductBST
{
private:
    TreeNode *root;

    TreeNode *createNode(Product p)
    {
        TreeNode *newNode = new TreeNode;
        newNode->product = p;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    void insert(TreeNode *&node, Product p)
    {
        if (node == NULL)
        {
            node = createNode(p);
        }
        else if (p.price < node->product.price)
        {
            insert(node->left, p);
        }
        else
        {
            insert(node->right, p);
        }
    }

    void inorder(TreeNode *node)
    {
        if (node == NULL)
            return;
        inorder(node->left);
        cout << "ID: " << node->product.id
             << " | Name: " << node->product.name
             << " | Category: " << node->product.category
             << " | Price: " << node->product.price
             << " | Person: " << node->product.person_name << endl;
        inorder(node->right);
    }

    bool searchByID(TreeNode *node, int id)
    {
        if (node == NULL)
            return false;

        if (node->product.id == id)
        {
            cout << "\nProduct Found!\n";
            cout << "----------------------------------\n";
            cout << "ID: " << node->product.id << endl;
            cout << "Name: " << node->product.name << endl;
            cout << "Category: " << node->product.category << endl;
            cout << "Price: " << node->product.price << endl;
            cout << "Person: " << node->product.person_name << endl;
            cout << "----------------------------------\n";
            return true;
        }
        // Since BST is sorted by price, not by ID — we must search both sides
        return searchByID(node->left, id) || searchByID(node->right, id);
    }

    void generateBill(TreeNode *node, string person, float &total)
    {
        if (node == NULL)
            return;
        generateBill(node->left, person, total);
        if (node->product.person_name == person)
        {
            cout << "ID: " << node->product.id
                 << " | Name: " << node->product.name
                 << " | Price: " << node->product.price
                 << " | Category: " << node->product.category << endl;
            total += node->product.price;
        }
        generateBill(node->right, person, total);
    }

public:
    ProductBST() { root = NULL; }

    void insertProduct(Product p)
    {
        insert(root, p);
    }

    bool searchProductByID(int id)
    {
        return searchByID(root, id);
    }

    void displayAll()
    {
        if (root == NULL)
        {
            cout << "No products in this category.\n";
            return;
        }
        inorder(root);
    }

    void generateBillFor(string person)
    {
        float total = 0;
        generateBill(root, person, total);
        if (total > 0)
            cout << "Total Amount for " << person << ": Rs. " << total << endl;
    }

    bool hasPersonPurchase(string person)
    {
        float dummy = 0;
        generateBill(root, person, dummy);
        return dummy > 0;
    }
};

// ---------------- MAIN PROGRAM ----------------
int main()
{
    ProductBST electronics, vehicles, others;
    int choice;

    do
    {
        cout << "\n========= PRODUCT PURCHASE SYSTEM =========\n";
        cout << "1. Insert New Product Record\n";
        cout << "2. Search Product by ID\n";
        cout << "3. Display All Products (Inorder Traversal)\n";
        cout << "4. Generate Bill for a Person\n";
        cout << "5. Exit\n";
        cout << "===========================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            Product p;
            cout << "\nEnter Product ID: ";
            cin >> p.id;
            cin.ignore();
            cout << "Enter Product Name: ";
            getline(cin, p.name);
            cout << "Enter Category (Electronics / Vehicles / Others): ";
            getline(cin, p.category);
            cout << "Enter Price: ";
            cin >> p.price;
            cin.ignore();
            cout << "Enter Person Name: ";
            getline(cin, p.person_name);

            if (p.category == "Electronics" || p.category == "electronics")
                electronics.insertProduct(p);
            else if (p.category == "Vehicles" || p.category == "vehicles")
                vehicles.insertProduct(p);
            else
                others.insertProduct(p);

            cout << "Product inserted successfully!\n";
        }

        else if (choice == 2)
        {
            int id;
            cout << "Enter Product ID to search: ";
            cin >> id;
            bool found = false;
            cout << "\nSearching in Electronics...\n";
            found = electronics.searchProductByID(id);
            if (!found)
            {
                cout << "\nSearching in Vehicles...\n";
                found = vehicles.searchProductByID(id);
            }
            if (!found)
            {
                cout << "\nSearching in Others...\n";
                found = others.searchProductByID(id);
            }
            if (!found)
                cout << "Product with ID " << id << " not found.\n";
        }

        else if (choice == 3)
        {
            cout << "\n=== Electronics Products ===\n";
            electronics.displayAll();

            cout << "\n=== Vehicles Products ===\n";
            vehicles.displayAll();

            cout << "\n=== Other Products ===\n";
            others.displayAll();
        }

        else if (choice == 4)
        {
            string person;
            cin.ignore();
            cout << "Enter Person Name: ";
            getline(cin, person);
            float total = 0;

            cout << "\nProducts purchased by " << person << ":\n";

            electronics.generateBillFor(person);
            vehicles.generateBillFor(person);
            others.generateBillFor(person);
        }

        else if (choice == 5)
        {
            cout << "Exiting system... Goodbye!\n";
        }
        else
        {
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
