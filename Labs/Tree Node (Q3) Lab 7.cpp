#include <iostream>
using namespace std;


struct Node {
    friend class BST;
    int data;
    Node* left;
    Node* right;
};
class BST {

    Node* root;
public:
    BST() {
        root = nullptr;
    }
    void insert(int d) {
        insert(root, d);
    }
    void insert(Node* &r,int d) {
        if (r == nullptr) {
            r = new Node;
            r->data = d;
            r->left = nullptr;
            r->right = nullptr;
        }
        else {
            if (d < r->data) {
                insert(r->left, d);
                /*return true;*/
            }
            else if (d > r->data) {
                insert(r->right, d);
                /*return true;*/
            }
        }
    }
    Node* Search(Node* root, int key) {
        if (root == NULL || root->data == key) {
            return root;
        }
        else
        if (root->data < key) {
            return Search(root->right, key);
        }
        else
            return Search(root->left, key);
    }
    int leftNodes(Node* ln) {
        int leftcount = 0;
        while (ln) {
            leftcount++;
            ln = ln->left;
        }
        return leftcount;
    }
    int rightNodes(Node* rn) {
        int rightcount = 0;
        while (rn) {
            rightcount++;
            rn = rn->right;
        }
        return rightcount;
    }
    int Length(Node* root) {
        int count1 = rightNodes(root->right);
        int count2 = leftNodes(root->left);
        if (root = nullptr) {
            return 0;
        }
        else {
            return 1 + count1 + count2;
        }
    }
    void Print(Node* r) {
        if (r == nullptr) {
            return ;
        }
        else {
            cout << r->data << " ";
            Print(r->left);
            Print(r->right);
        }
    }
};

int main() {
    BST tree;
    Node* r = new Node();
    r->data = 850;

    tree.insert(r,500);
    tree.insert(r,1000);
    tree.insert(r,1);
    tree.insert(r,600);

    tree.insert(r,700);
    tree.insert(r,10);
    tree.insert(r,30);
    tree.insert(r,9000);
    tree.insert(r,50000);
    tree.insert(r,20);

    tree.Print(r);
    cout<< tree.Search(r, 30);
    cout << endl;
    cout << tree.Length(r);

}

