#include <iostream>
using namespace std;
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;
    Node* insertNode(Node* node, int val) {
        if (node == nullptr) {
            return new Node(val);
        }
        if (val < node->data) {
            node->left = insertNode(node->left, val);
        } else if (val > node->data) {
            node->right = insertNode(node->right, val);
        }
        return node;
    }
    void inorderTraversal(Node* node) {
        if (node != nullptr) {
            inorderTraversal(node->left);
            cout << node->data << " ";
            inorderTraversal(node->right);
        }
    }
    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    Node* deleteNode(Node* node, int val) {
        if (node == nullptr) {
            return nullptr;
        }
        if (val < node->data) {
            node->left = deleteNode(node->left, val);
        } else if (val > node->data) {
            node->right = deleteNode(node->right, val);
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }
        return node;
    }
    Node* searchNode(Node* node, int val) {
        if (node == nullptr || node->data == val) {
            return node;
        }
        if (val < node->data) {
            return searchNode(node->left, val);
        }
        return searchNode(node->right, val);
    }
public:
    BST() : root(nullptr) {}
    void insert(int val) {
        root = insertNode(root, val);
    }
    void inorder() {
        if (root == nullptr) {
            cout << "Tree is empty" << endl;
            return;
        }
        inorderTraversal(root);
        cout << endl;
    }
    bool update(int oldVal, int newVal) {
        if (searchNode(root, oldVal) == nullptr) {
            return false;
        }
        root = deleteNode(root, oldVal);
        root = insertNode(root, newVal);
        return true;
    }
    bool remove(int val) {
        if (searchNode(root, val) == nullptr) {
            return false;
        }
        root = deleteNode(root, val);
        return true;
    }
    bool search(int val) {
        return searchNode(root, val) != nullptr;
    }
};
int main() {
    BST tree;

    cout << "Inserting values: 50, 30, 70, 20, 40, 60, 80" << endl;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    cout << "Inorder traversal: ";
    tree.inorder();
    int searchVal = 40;
    cout << "Searching for " << searchVal << ": "
         << (tree.search(searchVal) ? "Found" : "Not Found") << endl;

    int oldVal = 30, newVal = 35;
    cout << "Updating " << oldVal << " to " << newVal << ": ";
    if (tree.update(oldVal, newVal)) {
        cout << "Success" << endl;
    } else {
        cout << "Failed" << endl;
    }
    cout << "Inorder traversal after update: ";
    tree.inorder();

    int delVal = 70;
    cout << "Deleting " << delVal << ": ";
    if (tree.remove(delVal)) {
        cout << "Success" << endl;
    } else {
        cout << "Failed" << endl;
    }
    cout << "Inorder traversal after deletion: ";
    tree.inorder();
    return 0;
}
