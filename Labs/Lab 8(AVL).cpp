#include<iostream>
using namespace std;
template <class T>
class ATree
{
private:
    class ANode
    {
    public:
        T data;
        ANode* left;
        ANode* right;
        int height;
        ANode()
        {
            left = nullptr;
            right = nullptr;
            height = 0;
        }
        ANode(T d, ANode* l, ANode* r, int h)
        {
            data = d;
            left = l;
            right = r;
            height = h;
        }
    };
    ANode* root;
public:

    ATree()
    {
        root = nullptr;
    }

    int getH(ANode* r)
    {
        if (r == nullptr)
        {
            return -1;
        }
        else
        {
            return r->height;
        }
    }

    int Max(int l, int r)
    {
        if (r > l)
            return r;
        else
            return l;
    }

    void rotateLeft(ANode*& x)
    {
        ANode* y = x->right;
        x->right = y->left;
        y->left = x;
        x->height = 1 + Max(getH(x->left), getH(x->right));
        y->height = 1 + Max(getH(y->left), getH(y->right));
        x = y;
    }

    void rotateRight(ANode*& x)
    {
        ANode* y = x->left;
        x->left = y->right;
        y->right = x;
        x->height = 1 + Max(getH(x->left), getH(x->right));
        y->height = 1 + Max(getH(y->left), getH(y->right));
        x = y;
    }

    int getBalance(ANode* r) {
        if (r == nullptr) {
            return 0;
        }
        else
            return getH(r->left) - getH(r->right);
    }
    void InsertRec(T d, ANode*& r)
    {
        if (r == 0)
        {
            r = new ANode;
            r->data = d;
            r->left = 0;
            r->right = 0;
            r->height = 0;
        }
        if (d > r->data)
        {
            InsertRec(d, r->right);
        }
        else if (d < r->data)
        {
            InsertRec(d, r->left);
        }
        int HeightDifference = getH(r->left) - getH(r->right);
        if (HeightDifference > 1 && d < r->left->data)
        {
            rotateRight(r);
        }
        if (HeightDifference < -1 && d > r->right->data)
        {
            rotateLeft(r);
        }
        if (HeightDifference > 1 && d > r->left->data)
        {
            rotateLeft(r->left);
            rotateRight(r);
        }
        if (HeightDifference < -1 && d < r->right->data)
        {
            rotateRight(r->right);
            rotateLeft(r);
        }
        r->height = 1 + Max(getH(r->left), getH(r->right));
    }
    void Insert(T d)
    {
        InsertRec(d, root);
    }

    ANode*& getR()
    {
        return root;
    }

    void inorder(ANode* r)
    {
        if (r)
        {
            inorder(r->left);
            cout << r->data << " ";
            inorder(r->right);

        }

    }

    void preorder(ANode* r)
    {
        if (r)
        {

            cout << r->data;
            preorder(r->left);
            preorder(r->right);

        }

    }

    bool search(ANode* r, int key) {
        if (r != nullptr) {
            if (key == r->data) return true;
            else if (key < r->data) return search(r->left, key);
            else if (key > r->data) return search(r->right, key);
            if (key != r->data) return false;
        }
        else if (r == nullptr)
            return false;
    }
    bool search(int key) {
        return search(root, key);
    }
    void Delete(ANode*& r, T val)
    {
        if (r->data == val)
        {
            //delete node based on 3 conditions
            if (r->left == nullptr && r->right == nullptr)
            {
                ANode* tmp = r;
                r = nullptr;
                delete tmp;

            }
            else if (r->left == nullptr)
            {
                ANode* tmp = r;
                r = r->right;
                delete tmp;
            }
            else if (r->right == nullptr)
            {
                ANode* tmp = r;
                r = r->left;
                delete tmp;
            }
            else //r has two childs
            {
                //find Max from r->l and replace it with r
                ANode* k = r->left;
                ANode* prev = nullptr;
                while (k->right != nullptr)
                {
                    prev = k;
                    k = k->right;
                }
                if (prev == nullptr)
                {
                    r->left = nullptr;
                    r->data = k->data;
                    delete k;
                }
                else
                {
                    r->data = k->data;
                    prev->right = nullptr;
                    delete k;
                }
            }
            return;
        }
        else if (val > r->data)
        {
            Delete(r->right, val);
        }
        else if (val < r->data)
        {
            Delete(r->left, val);
        }
        r->height = 1 + Max(getH(r->left), getH(r->right));
        int factor = getBalance(r);
        if (factor < -1) // right subtree is getting heavy deletion was done in left subtree
        {
            int k = getBalance(r->right);
            if (k <= -1) // RR case
            {
                rotateLeft(r);
            }
            else //RL
            {
                rotateRight(r->right);
                rotateLeft(r);
            }
        }
        else if (factor > 1)
        {
            int k = getBalance(r->left);
            if (k >= 1) // LL case
            {
                rotateRight(r);
            }
            else //LR
            {
                rotateLeft(r->left);
                rotateRight(r);
            }
        }
    }

    void Delete(T val)
    {
        Delete(root, val);
    }


};

int main()
{
    ATree<int> AVL;

    // Inserting values into the tree
    AVL.Insert(10);
    cout << "Tree after inserting 10: ";
    AVL.inorder(AVL.getR());
    cout << endl;

    AVL.Insert(20);
    cout << "Tree after inserting 20: ";
    AVL.inorder(AVL.getR());
    cout << endl;

    AVL.Insert(30);
    cout << "Tree after inserting 30: ";
    AVL.inorder(AVL.getR());
    cout << endl;

    AVL.Insert(40);
    cout << "Tree after inserting 40: ";
    AVL.inorder(AVL.getR());
    cout << endl;

    AVL.Insert(50);
    cout << "Tree after inserting 50: ";
    AVL.inorder(AVL.getR());
    cout << endl;

    AVL.Insert(25);
    cout << "Tree after inserting 25: ";
    AVL.inorder(AVL.getR());
    cout << endl;

    AVL.Insert(60);
    cout << "Tree after inserting 60: ";
    AVL.inorder(AVL.getR());
    cout << endl;

    // Deleting node with value 25
    AVL.Delete(25);
    cout << "Tree after deleting 25: ";
    AVL.inorder(AVL.getR());
    cout << endl;

    // Calculating the height of the tree
    int treeHeight = AVL.getH(AVL.getR());
    cout << "Height of the tree: " << treeHeight << endl;

    return 0;
}

