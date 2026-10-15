#include <iostream>
#include <string>
using namespace std;

struct Node
{
    int bookID;
    string title;
    Node* left;
    Node* right;
};

Node* createNode(int id, string name)
{
    Node* newNode = new Node;

    newNode->bookID = id;
    newNode->title = name;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Insert a book into BST
Node* insert(Node* root, int id, string name)
{
    if (root == NULL)
        return createNode(id, name);

    if (id < root->bookID)
        root->left = insert(root->left, id, name);

    else if (id > root->bookID)
        root->right = insert(root->right, id, name);

    else
        cout << "Book ID already exists!\n";

    return root;
}

// Search a book and count comparisons
Node* search(Node* root, int id, int& comparisons)
{
    while (root != NULL)
    {
        comparisons++;

        if (root->bookID == id)
            return root;

        if (id < root->bookID)
            root = root->left;
        else
            root = root->right;
    }

    return NULL;
}

// Find the smallest node
Node* findMin(Node* root)
{
    while (root != NULL && root->left != NULL)
        root = root->left;

    return root;
}

// Delete a book from BST
Node* deleteBook(Node* root, int id)
{
    if (root == NULL)
        return NULL;

    if (id < root->bookID)
        root->left = deleteBook(root->left, id);

    else if (id > root->bookID)
        root->right = deleteBook(root->right, id);

    else
    {
        // No left child
        if (root->left == NULL)
        {
            Node* temp = root->right;
            delete root;
            return temp;
        }

        // No right child
        if (root->right == NULL)
        {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Two children
        Node* temp = findMin(root->right);

        root->bookID = temp->bookID;
        root->title = temp->title;

        root->right = deleteBook(root->right, temp->bookID);
    }

    return root;
}

// Display books in ascending order
void displaySorted(Node* root)
{
    if (root == NULL)
        return;

    displaySorted(root->left);

    cout << "Book ID: " << root->bookID
         << " | Title: " << root->title << endl;

    displaySorted(root->right);
}

// Main function
int main()
{
    Node* root = NULL;
    int choice, id, comparisons;
    string title;

    do
    {
        cout << "\n===== LIBRARY BOOK SEARCH SYSTEM =====\n";
        cout << "1. Insert Book\n";
        cout << "2. Search Book\n";
        cout << "3. Delete Book\n";
        cout << "4. Display Books in Sorted Order\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Enter Book ID: ";
                cin >> id;

                cout << "Enter Book Title: ";
                cin.ignore(10000, '\n');
                getline(cin, title);

                {
                    int count = 0;
                    Node* found = search(root, id, count);

                    if (found != NULL)
                    {
                        cout << "Book ID already exists!\n";
                    }
                    else
                    {
                        root = insert(root, id, title);
                        cout << "Book inserted successfully!\n";
                    }
                }
                break;

            case 2:
                cout << "Enter Book ID to search: ";
                cin >> id;

                comparisons = 0;
                {
                    Node* result = search(root, id, comparisons);

                    if (result != NULL)
                    {
                        cout << "Book Found!\n";
                        cout << "Book ID: " << result->bookID << endl;
                        cout << "Book Title: " << result->title << endl;
                    }
                    else
                    {
                        cout << "Book not found!\n";
                    }

                    cout << "Number of comparisons: "
                         << comparisons << endl;
                }
                break;

            case 3:
                cout << "Enter Book ID to delete: ";
                cin >> id;

                comparisons = 0;
                {
                    Node* result = search(root, id, comparisons);

                    if (result != NULL)
                    {
                        root = deleteBook(root, id);
                        cout << "Book deleted successfully!\n";
                    }
                    else
                    {
                        cout << "Book not found!\n";
                    }
                }
                break;

            case 4:
                if (root == NULL)
                    cout << "Library is empty!\n";
                else
                {
                    cout << "\nBooks in Ascending Order:\n";
                    displaySorted(root);
                }
                break;

            case 5:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}