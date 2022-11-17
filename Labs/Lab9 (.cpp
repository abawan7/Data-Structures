#include <iostream>
#include <stack>
using namespace std;
template <typename T>
class AVL
{
private:
    struct Node
    {
        T Data;
        int Height;
        Node* leftchild, *rightchild;
        Node(const T& obj)
        {
            Data = obj; //deep copy
            Height = 0;
            leftchild = rightchild = nullptr;
        }
        Node(const T &key, Node *l, Node*r, int h){
            Data = key; //deep copy
            leftchild = l; rightchild = r;
            Height = h;
        }
    };
    Node* Root;
    int n;
    bool getAccess(const T& key, Node*& curr, stack<Node*>& ancestors)
    {
        curr = Root;
        if (curr == nullptr)
            return false;

        if (key == Root->Data)
            return true;

        while (curr != nullptr)
        {
            ancestors.push(curr);
            if (key == curr->Data)
                return true;
            else if (key < curr->Data)
            {
                curr = curr->leftchild;
            }
            else
            {
                curr = curr->rightchild;
            }
        }
        return false;
    }
    Node* Smallest(Node* root, int& k)
    {
        if (root == NULL)
            return NULL;

        Node* left = Smallest(root->left, k);

        //If k'th smallest is found in left subtree, return it
        if (left != NULL)
            return left;
        int count = 0;
        //If current element is k'th smallest, return it
        count++;
        if (count == k)
            return root;

        //Otherwise Search in right subtree
        return Smallest(root->right, k);
    }
    int height(Node* ptr)
    {
        if (ptr == NULL)
        {
            return -1;
        }
        else
        {
            return ptr->Height;
        }
    }
    int bf(Node* ptr)
    {
        return height(ptr->rightchild) - height(ptr->leftchild);
    }
    bool updateHeight(Node* ptr)
    {
        int old_h = height(ptr);
        int new_h = max(height(ptr->leftchild), height(ptr->rightchild)) + 1;
        ptr->Height = new_h;
        return (old_h != new_h);
    }
    void printInOrder(Node* curr)
    {
        if (curr != nullptr)
        {
            //LNR
            printInOrder(curr->leftchild);
            cout << (curr->Data) << " ";
            printInOrder(curr->rightchild);
        }
    }
    int max(int a, int b)
    {
        if (a > b){ return a; }
        else{ return b; }
    }
    void printPostOrder(Node* curr)
    {
        if (curr != nullptr)
        {
            //LRN
            printPostOrder(curr->leftchild);
            printPostOrder(curr->rightchild);
            cout << (curr->Data) << " ";
        }
    }
    void PrintPreOrder(Node* curr)
    {
        if (curr != nullptr)
        {
            //NLR
            cout << (curr->Data) << " ";
            PrintPreOrder(curr->leftchild);
            PrintPreOrder(curr->rightchild);
        }
    }
public:
    AVL()
    {
        Root = nullptr;
        n = 0;
    }
    AVL(const T& newdata, Node* lc = NULL, Node* rc = NULL, int nh = 0)
    {
        Data = newdata;
        leftchild = lc;
        rightchild = rc;
        Height = nh;
    }
    bool insert(const T& key)
    {
        Node* ptr = NULL;
        stack<Node*> ancestors;
        if (getAccess(key, ptr, ancestors))
            return false;
        else
        {
            //being here means ptr is NULL
            Node* pptr = ancestors.size() == 0 ? NULL : ancestors.top();

            if (pptr == NULL) //empty tree
            {
                Root = new Node(key, NULL, NULL, 0);
            }
            else if (key < pptr->Data) //new node is a left child
            {
                pptr->leftchild = new Node(key, NULL, NULL, 0);
            }
            else
            {
                pptr->rightchild = new Node(key, NULL, NULL, 0);
            }
            //now update heights and check balance factors of the ancestors

            while (!ancestors.empty())
            {
                Node* anc = ancestors.top();
                ancestors.pop();

                //update the Height of the next ancestor
                updateHeight(anc);

                //is there imbalance on this ancestor?
                if (bf(anc) > 1 || bf(anc) < -1)
                {
                    //Yes there is imbalance
                    //Identify the type of imbalance and resolve it

                    //get parent pointer, required by rotation methods
                    Node* panc = ancestors.empty() ? NULL : ancestors.top();
                    if (bf(anc) == 2 && bf(anc->rightchild) == 1)
                    {
                        //right-right
                        rl(anc, panc);
                    }
                    else if (bf(anc) == -2 && bf(anc->leftchild) == -1)
                    {
                        //left-left
                        rr(anc, panc);
                    }
                    else if (bf(anc) == 2 && bf(anc->rightchild) == -1)
                    {
                        //right-left
                        rr(anc->rightchild, anc);
                        rl(anc, panc);
                    }
                    else if (bf(anc->leftchild) == 1)
                    {
                        //left-right
                        rl(anc->leftchild, anc);
                        rr(anc, panc);
                    }
                    break;
                }
            }
            n++;
            return true;
        }
    }
    bool rr(Node* ptr, Node* pptr)
    {
        //right rotate around ptr
        Node* cptr = ptr->leftchild;

        if (cptr == NULL)
        {
            return false;
        }
        else
        {
            //what is the node itself is the Root
            //promote cptr
            if (pptr == NULL)
            {
                Root = cptr;
            }
            else
            {
                if (ptr == pptr->leftchild)
                {
                    pptr->leftchild = cptr;
                }
                else
                {
                    pptr->rightchild = cptr;
                }
            }
            //adjust children
            Node* rc_cptr = cptr->rightchild;
            cptr->rightchild = ptr;
            ptr->leftchild = rc_cptr;

            //update heights of ptr and cptr
            updateHeight(ptr);
            updateHeight(cptr);

            return true;
        }
    }
    bool rl(Node* ptr, Node* pptr)
    {
        Node* cptr = ptr->rightchild;

        if (cptr == NULL)
        {
            return false;
        }
        else
        {
            if (pptr == NULL)
            {
                Root = cptr;
            }
            else
            {
                if (ptr == pptr->leftchild)
                {
                    pptr->leftchild = cptr;
                }
                else
                {
                    pptr->rightchild = cptr;
                }
            }
            Node* lc_cptr = cptr->leftchild;
            cptr->leftchild = ptr;
            ptr->rightchild = lc_cptr;

            //update the heights of ptr and cptr
            updateHeight(ptr);
            updateHeight(cptr);
            return true;
        }
    }
    bool search(const T&key){
        AVL<int> tree;
        bool v = tree.Search(5, tree.Root);
        return v;
    }
    bool Search(const T& key, Node* node)
    {
        while (node != nullptr)
        {
            if (node->Data == key)
            {
                return true;
            }
            else if (key < node->Data)
            {
                node = node->leftchild;
            }
            else if (key > node->Data)
            {
                node = node->rightchild;
            }
        }
        return false;
    }
    int findminimum()
    {
        return kathsmallest(Root, 1);

    }
    int find2ndminimum()
    {
        return kathsmallest(Root, 2);
    }
    void update_Height(Node*& root)
    {
        root->Height = max(height(root->leftchild), height(root->rightchild)) + 1;
    }
    void printInOrder()
    {
        printInOrder(Root);
    }
    void printPostOrder()
    {
        printPostOrder(Root);
    }
    void printPreOrder()
    {
        PrintPreOrder(Root);
    }
};
int main()
{
    AVL<int> tree;
    for (int i = 0; i < 20; i++)
    {
        tree.insert(i);
    }
    cout << "In-Order: " << endl;
    tree.printInOrder(); cout << endl<<endl;

    cout << "Post-Order: " << endl;
    tree.printPostOrder(); cout << endl << endl;

    cout << "Pre-order: " << endl;
    tree.printPreOrder(); cout << endl << endl;

    system("pause");
    return 0;
}
