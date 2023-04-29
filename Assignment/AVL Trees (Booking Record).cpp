#include <iostream>
using namespace std;

template<typename k, typename v>
struct TreeNode {
    k key;
    v value;
    TreeNode<k, v> *lChild;
    TreeNode<k, v> *rChild;

    TreeNode(k key, v value) : key(key), value(value), lChild(nullptr), rChild(nullptr) {}
};

template<typename k, typename v>
class bst {
private:
    TreeNode<k, v> *root;

    // Helper function for copy constructor
    TreeNode<k, v>* copyTree(TreeNode<k, v> *node) {
        if (node == nullptr) {
            return nullptr;
        }
        TreeNode<k, v> *newNode = new TreeNode<k, v>(node->key, node->value);
        newNode->lChild = copyTree(node->lChild);
        newNode->rChild = copyTree(node->rChild);
        return newNode;
    }

    // Helper function for recursive insert
    void insertHelper(TreeNode<k, v> *&node, k key, v value) {
        if (node == nullptr) {
            node = new TreeNode<k, v>(key, value);
            return;
        }
        if (key < node->key) {
            insertHelper(node->lChild, key, value);
        } else if (key > node->key) {
            insertHelper(node->rChild, key, value);
        } else {
            node->value = value; // Key already exists, replace the value
        }
    }

    // Helper function for recursive search
    v* searchHelper(TreeNode<k, v> *node, k key) const {
        if (node == nullptr) {
            return nullptr;
        }
        if (key < node->key) {
            return searchHelper(node->lChild, key);
        } else if (key > node->key) {
            return searchHelper(node->rChild, key);
        } else {
            return &(node->value);
        }
    }

    // Helper function for inorder traversal
    void inorderHelper(TreeNode<k, v> *node) const {
        if (node == nullptr) {
            return;
        }
        inorderHelper(node->lChild);
        std::cout << node->key << " ";
        inorderHelper(node->rChild);
    }

    // Helper function for recursive count of nodes
    int lengthHelper(TreeNode<k, v> *node) const {
        if (node == nullptr) {
            return 0;
        }
        return 1 + lengthHelper(node->lChild) + lengthHelper(node->rChild);
    }

    // Helper function for recursive delete of a node with given key
    TreeNode<k, v>* deleteHelper(TreeNode<k, v> *&node, k key) {
        if (node == nullptr) {
            return nullptr;
        }
        if (key < node->key) {
            node->lChild = deleteHelper(node->lChild, key);
        } else if (key > node->key) {
            node->rChild = deleteHelper(node->rChild, key);
        } else {
            // Case 1: No child or one child
            if (node->lChild == nullptr) {
                TreeNode<k, v> *temp = node->rChild;
                delete node;
                return temp;
            } else if (node->rChild == nullptr) {
                TreeNode<k, v> *temp = node->lChild;
                delete node;
                return temp;
            }
            // Case 2: Two children
            TreeNode<k, v> *temp =node->rChild;

            while (temp->lChild != nullptr) {
                temp = temp->lChild;
            }
            node->key = temp->key;
            node->value = temp->value;
// Recursively delete the inorder successor from the right subtree
            node->rChild = deleteHelper(node->rChild, temp->key);
        }
        return node;
    }

public:
    bst() : root(nullptr) {}
    bst(const bst<k, v> &other) {
        root = copyTree(other.root);
    }

    void insert(k const key, v const value) {
        insertHelper(root, key, value);
    }

    v* search(k key) {
        return searchHelper(root, key);
    }

    void inorderPrintKeys() const {
        inorderHelper(root);
        std::cout << std::endl;
    }

    int length() const {
        return lengthHelper(root);
    }

    void deleteKey(k key) {
        root = deleteHelper(root, key);
    }

    ~bst() {
        // Traverse the tree in postorder and delete each node
        while (root != nullptr) {
            deleteHelper(root, root->key);
        }
    }
};

int main()
{
    bst<int, int>tree;//the key and value both are of type int
    tree.insert(500, 500);
    tree.insert(1000, 1000);
    tree.insert(1, 1);
    tree.insert(600, 600);
    tree.insert(700, 700);
    tree.insert(10, 10);
    tree.insert(30, 30);
    tree.insert(9000, 9000);
    tree.insert(50000, 50000);
    tree.insert(20, 20);
    bst<int, int> tree1(tree);
    tree1.deleteKey(20);
    tree1.deleteKey(500);
    tree1.deleteKey(1000);
    tree1.inorderPrintKeys();
    cout << endl;
    cout<<"Tree1 Length"<<tree1.length()<<endl;
    int *val = tree1.search(1);
    if (val != nullptr)
    {
        cout <<"1 found"<< endl;
    }
    val = tree1.search(123);
    if (val == nullptr)
    {
        cout <<"123 not found"<< endl;
    }
    return 0;
}
