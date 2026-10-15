#include <iostream>
using namespace std;

// Structure of a BST node
struct Node
{
    int bookID;
    Node* left;
    Node* right;
};

// Create a new node
Node* createNode(int id)
{
    Node* newNode = new Node;

    newNode->bookID = id;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Insert a book ID into the BST
Node* insert(Node* root, int id)
{
    if (root == NULL)
    {
        return createNode(id);
    }

    if (id < root->bookID)
    {
        root->left = insert(root->left, id);
    }
    else if (id > root->bookID)
    {
        root->right = insert(root->right, id);
    }
    else
    {
        cout << "Book ID already exists!" << endl;
    }

    return root;
}

// Search for a book ID
bool search(Node* root, int id)
{
    if (root == NULL)
    {
        return false;
    }

    if (root->bookID == id)
    {
        return true;
    }

    if (id < root->bookID)
    {
        return search(root->left, id);
    }

    return search(root->right, id);
}

// Main function
int main()
{
    Node* root = NULL;
    int choice, id;

    do
    {
        cout << "\n--- Library Book Search System ---" << endl;
        cout << "1. Insert Book ID" << endl;
        cout << "2. Search Book ID" << endl;
        cout << "3. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Enter Book ID: ";
                cin >> id;

                root = insert(root, id);
                cout << "Book ID insertion operation completed."
                     << endl;
                break;

            case 2:
                cout << "Enter Book ID to search: ";
                cin >> id;

                if (search(root, id))
                {
                    cout << "Book ID found in the library!"
                         << endl;
                }
                else
                {
                    cout << "Book ID not found in the library!"
                         << endl;
                }
                break;

            case 3:
                cout << "Exiting the program..." << endl;
                break;

            default:
                cout << "Invalid choice! Try again." << endl;
        }

    } while (choice != 3);

    return 0;
}