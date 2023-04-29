#include <iostream>

using namespace std;

class node {
public:
    int data;
    node *left;
    node *right;

    node() {
        data = 0;
        left = right = NULL;
    }

    node(int d) {
        data = d;
        left = right = NULL;
    }

    node(const node &n) {
        data = n.data;
        left = n.left;
        right = n.right;
    }
};

class BST {
public:
    node *root;

    BST() {
        root = NULL;
    }

    BST(const BST &b) {
        root = new node(*b.root);
    }

    bool insert(int data) {
        return insert(root, data);
    }

    bool insert(node *&r, int data) {
        if (r == NULL) {
            r = new node(data);
            return true;
        }
        if (data <= r->data) {
            insert(r->left, data);
        } else {
            insert(r->right, data);
        }
    }

    void PreOrderPrint(node * root)
    {
        if (root!=NULL)
        {
            cout<<root->data<<"   ";
            PreOrderPrint(root->left);
            PreOrderPrint(root->right);

        }
    }
    void PreOrderPrint()
    {
        PreOrderPrint(root);
    }

    void PostOrderPrint(node * root)
    {
        if (root!=NULL)
        {
            PostOrderPrint(root->left);
            PostOrderPrint(root->right);
            cout<<root->data<<"   ";

        }
    }
    void PostOrderPrint()
    {
        PostOrderPrint(root);
    }


    void InOrderPrint(node *root) {
        if (root != NULL) {
            InOrderPrint(root->left);
            cout << root->data << "   ";
            InOrderPrint(root->right);
        }
    }

    void InOrderPrint() {
        InOrderPrint(root);
    }


    int length(node *root) {
        if (root != NULL) {
            return (length(root->left) + length(root->right)) + 1;
        } else {
            return 0;
        }
    }

    int length() {
        return length(root);
    }

    bool Search(node *root, int s) {
        if (root != NULL) {
            if (root->data == s) {
                return true;
            } else {
                return false;
            }
            Search(root->left, s);
            Search(root->right, s);

        }
    }

    bool Search(int s) {
        return Search(root, s);
    }

    bool des(node *root) {
        des(root->left);
        des(root->left);
        des(root);

    }

    bool des() {
        return des(root);
    }

    void deleteR(int d){
        deleteR(d, root);
    }

    void deleteR(int d, node *&node){
        if (d > node->data){
            deleteR(d,node->right);
        } else if(d < node->data){
            deleteR(d, node->left);
        } else{
            deleteNode(node);
        }
    }

    void deleteNode(node *&node1){
        int d;
        node *temp;
        temp = node1;
        if(node1->left == NULL){
            node1 = node1->right;
            delete temp;
        } else if(node1->right == NULL){
            node1 = node1->left;
            delete temp;
        }
        else {
            getPredecessor(node1->left, d);
            node1->data = d;
            deleteR(d,node1->left);
        }
    }

    void getPredecessor (node *node, int &data){
        while(node->right != NULL)
            node = node->right;
        data = node->data;
    }
};

int main() {
    BST tree;
    tree.insert(500);
    tree.insert(1000);
    tree.insert(1);
    tree.insert(600);
    tree.insert(700);
    tree.insert(10);
    tree.insert(30);
    tree.insert(9000);
    tree.insert(50000);
    tree.insert(20);

    cout << "Print data using recursive inorder traversal" << endl;
    tree.InOrderPrint();

    cout << "\nCOPY CONSTRUCTOR\n";
    BST tree1(tree);
    tree1.InOrderPrint();


    cout << endl << endl << "Tree Length: " << tree.length() << endl << endl;


    cout << "DELETE KEY\n";
    tree1.deleteR(9000);
    tree1.InOrderPrint();

    cout << "\nSEARCH:";
    if (tree.Search(1)) {
        cout << "\nFound" << endl;
    } else {
        cout << "NOT FOUND\n";
    }
    if (tree.Search(123)) {
        cout << "Found" << endl;
    } else {
        cout << "NOT FOUND\n";
    }

    cout << "Length of Tree: " << tree.length() << "\n";
}


