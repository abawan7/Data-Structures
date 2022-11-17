#include<iostream>
using namespace std;

class Helper
{
public:
    static int stringLength(const char* str)
    {
        int i = 0, count = 0;
        while (str[i] != '\0')
        {
            i++;
            count++;
        }
        return count;
    }
    static void stringCopy(char*& dest, const char*& str) {
        int length = stringLength(str);
        int i = 0;
        while (str[i] != '\0')
        {
            dest[i] = str[i];
            i++;
        }
        dest[i] = '\0';
    }
    static char* fromBuffer(const char* buffer)
    {
        int length = stringLength(buffer);
        char* temp = new char[length + 1];
        stringCopy(temp, buffer);
        return temp;
    }
    static int compareStrings(const char* string1, const char* string2)
    {
        int check = 0, i = 0;
        int string1Length = stringLength(string1);
        int string2Length = stringLength(string2);
        while (i < string1Length)
        {
            if (check == 0)
            {
                if (string1[i] < string2[i])
                {
                    return -1;
                }
                if (string1[i] > string2[i])
                {
                    return 1;
                }
                if (string1[i] == string2[i])
                {
                    i++;
                }
            }
        }
        return 0;
    }
};

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

    int max(int l, int r)
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
        x->height = 1 + max(getH(x->left), getH(x->right));
        y->height = 1 + max(getH(y->left), getH(y->right));
        x = y;
    }

    void rotateRight(ANode*& x)
    {
        ANode* y = x->left;
        x->left = y->right;
        y->right = x;
        x->height = 1 + max(getH(x->left), getH(x->right));
        y->height = 1 + max(getH(y->left), getH(y->right));
        x = y;
    }


    void doubleRotateLeft(ANode*& x)
    {
        rotateRight(x->right);
        rotateLeft(x);
    }


    void doubleRotateRight(ANode*& x)
    {
        rotateLeft(x->left);
        rotateRight(x);
    }

    int BalanceFactor(ANode* r)
    {
        int BF = getH(r->left) - getH(r->right);
        return BF;
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
        r->height = 1 + max(getH(r->left), getH(r->right));
    }
    void Insert(T d)
    {
        InsertRec(d, root);
    }

    void InOrder(ANode* r)
    {
        if (r)
        {
            InOrder(r->left);
            cout << r->data << " ";
            InOrder(r->right);
        }

    }

    void InOrder()
    {
        InOrder(root);
    }

    bool Search(ANode* root, T key)
    {
        if (root) {
            if (key == root->data)
            {
                return true;
            }

            else if (key < root->data)
            {
                return Search(root->left, key);
            }
            else if (key > root->data)
            {
                return Search(root->right, key);
            }
            if (key != root->data)
            {
                return false;
            }
        }
        else if (root == nullptr)
        {
            return false;
        }
    }

    bool Search(T key)
    {
        return Search(root, key);
    }

    void PostOrder(ANode* r)
    {
        if (r)
        {
            PostOrder(r->left);
            PostOrder(r->right);
            cout << r->data << " ";

        }
        else
            return;
    }

    void PostOrder()
    {
        PostOrder(root);
    }

    void PreOrder(ANode* r)
    {
        if (r)
        {

            cout << r->data << " ";
            PreOrder(r->left);
            PreOrder(r->right);

        }
    }

    void PreOrder()
    {
        PreOrder(root);
    }

    bool isAVL(ANode* r)
    {
        if (r)
        {

            static bool flag = true;
            isAVL(r->left);
            isAVL(r->right);
            if (getH(r->left) - getH(r->right) > 1 || getH(r->left) - getH(r->right) < (-1))
            {
                if (flag)
                {
                    flag = false;
                }
            }
            return flag;
        }
        else {
            return true;
        }
    }
    bool isAVL()
    {
        return isAVL(root);
    }

    T& FindMin(ANode* r)
    {
        if (r->left == 0)
        {
            return r->data;
        }
        else
        {
            FindMin(r->left);
        }
    }
    T& FindMin()
    {
        return FindMin(root);
    }

    T& Find2ndMin(ANode* r)
    {
        if (r->left->left == 0)
        {
            return r->data;
        }
        else
        {
            Find2ndMin(r->left);
        }
    }
    T& Find2ndMin()
    {
        return Find2ndMin(root);
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
                //find max from r->l and replace it with r
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
        r->height = 1 + max(getH(r->left), getH(r->right));
        int factor = BalanceFactor(r);
        if (factor < -1) // right subtree is getting heavy deletion was done in left subtree
        {
            int k = BalanceFactor(r->right);
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
            int k = BalanceFactor(r->left);
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
class Month
{
    friend ostream& operator<< (ostream& out, Month& obj)
    {
        out << obj.month << " ";
        return out;
    }
private:
    char* month;
public:
    Month()
    {
        month = nullptr;
    }
    Month(const char* str)
    {
        month = Helper::fromBuffer(str);
    }

    bool operator>(Month& rhs)
    {
        int i = Helper::compareStrings(month, rhs.month);
        if (i == 1)
        {
            return true;
        }
        return false;
    }
    bool operator<(Month& rhs)
    {
        int i = Helper::compareStrings(month, rhs.month);
        if (i == -1)
        {
            return true;
        }
        return false;
    }

    bool operator==(Month& rhs)
    {
        int i = Helper::compareStrings(month, rhs.month);
        if (i == 0)
        {
            return true;
        }
        return false;
    }

    bool operator!=(Month& rhs)
    {
        int i = Helper::compareStrings(month, rhs.month);
        if (i == -1 || i == 1)
        {
            return true;
        }
        return false;
    }
};
int main()
{
    ATree<Month>AVL;
    Month obj1("Jan");
    AVL.Insert(obj1);

    Month obj2("Feb");
    AVL.Insert(obj2);

    Month obj3("March");
    AVL.Insert(obj3);

    Month obj4("April");
    AVL.Insert(obj4);

    Month obj5("May");
    AVL.Insert(obj5);

    Month obj6("June");
    AVL.Insert(obj6);

    Month obj7("July");
    AVL.Insert(obj7);

    Month obj8("August");
    AVL.Insert(obj8);

    Month obj9("September");
    AVL.Insert(obj9);

    Month obj10("October");
    AVL.Insert(obj10);

    Month obj11("November");
    AVL.Insert(obj11);

    Month obj12("December");
    AVL.Insert(obj12);

    cout << endl;
    cout << "PostOrder Traversal : ";
    AVL.PostOrder();
    cout << endl;

    cout << endl;
    cout << "InOrder Traversal : ";
    AVL.InOrder();
    cout << endl;

    cout << endl;
    cout << "PreOrder Traversal : ";
    AVL.PreOrder();
    cout << endl;
    cout << endl;



    cout << "Minimum Element in the Tree: ";
    cout << AVL.FindMin();
    cout << endl << endl;


    cout << "2nd Minimum Element in the Tree: ";
    cout << AVL.Find2ndMin() << endl;
    cout << endl;

    cout << "Search April int Tree: ";
    cout << AVL.Search("April");
    cout << endl << endl;

    AVL.Delete("April");
    cout << "InOrder Traversal : ";
    AVL.PreOrder();
    cout << endl;
}
