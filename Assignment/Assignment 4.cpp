#include <iostream>
#include <stack>
#include <ctime>
#include <vector>
#include <queue>
#include <cstdlib>
using namespace std;


template <typename T>
class BST {
    struct treeNode {
        T Data;
        treeNode* leftchild, * rightchild;

        treeNode(const T& new_data, treeNode* lc = NULL, treeNode* rc = NULL) {
            Data = new_data;
            leftchild = lc;
            rightchild = rc;
        }

    } *root;
    int n;//size of the tree

    bool getAccess(const T& key, treeNode*& ptr = NULL, treeNode*& pptr = NULL)
    {
        ptr = root;
        pptr = NULL;

        while (ptr != NULL && ptr->Data != key) {
            pptr = ptr;//pptr is the parent of next ptr
            if (key < ptr->Data)
                ptr = ptr->leftchild;
            else
                ptr = ptr->rightchild;
        }

        return (ptr != NULL);
    }

    void insertArray(T array[], int s, int e, int& si)
    {
        if (size() != si && s <= e)
        {
            insert(array[(s + e) / 2]);
            insertArray(array, s, ((s + e) / 2) - 1, si);
            insertArray(array, ((s + e) / 2) + 1, e, si);
        }
    }

    int childCount(treeNode* ptr) {
        if (ptr == NULL || (ptr->leftchild == NULL && ptr->rightchild == NULL))
            return 0;
        else if (ptr->leftchild != NULL && ptr->rightchild != NULL)
            return 2;
        else return 1;

    }

    //rotation methods
    bool rr(treeNode* ptr, treeNode* pptr) {
        //right rotate around ptr
        treeNode* cptr = ptr->leftchild;

        if (cptr == NULL)
            return false;
        else {
            //what is the node itself is the root
            //promote cptr
            if (pptr == NULL) {
                root = cptr;
            }
            else {
                if (ptr == pptr->leftchild)
                    pptr->leftchild = cptr;
                else
                    pptr->rightchild = cptr;
            }
            //adjust children
            treeNode* rc_cptr = cptr->rightchild;
            cptr->rightchild = ptr;
            ptr->leftchild = rc_cptr;
            return true;
        }
    }

    bool rl(treeNode* ptr, treeNode* pptr) {
        //left rotate around ptr

        treeNode* cptr = ptr->rightchild;

        if (cptr == NULL)
            return false;
        else {
            if (pptr == NULL) {
                root = cptr;
            }
            else {
                if (ptr == pptr->leftchild)
                    pptr->leftchild = cptr;
                else
                    pptr->rightchild = cptr;
            }
            treeNode* lc_cptr = cptr->leftchild;
            cptr->leftchild = ptr;
            ptr->rightchild = lc_cptr;
            return true;
        }
    }

    void eraseCase0(treeNode* ptr, treeNode* pptr) {
        if (ptr == root) {
            //cout<<"Root updated..."<<endl;
            root = NULL;
        }
        else if (ptr == pptr->leftchild) {
            pptr->leftchild = NULL;
        }
        else {
            pptr->rightchild = NULL;
        }
        delete ptr;
    }

    void eraseCase1(treeNode* ptr, treeNode* pptr) {
        treeNode* cptr;
        if (ptr->rightchild != NULL)
            cptr = ptr->rightchild;
        else
            cptr = ptr->leftchild;
        //ptr: node, pptr: parent of ptr, cptr: child of ptr
        if (ptr == root) {
            //cout<<"Root updated..."<<endl;
            root = cptr;
            delete ptr;
        }
        else {
            if (ptr == pptr->leftchild)//ptr is left child of pptr
                pptr->leftchild = cptr;
            else//ptr is right child of pptr
                pptr->rightchild = cptr;

            delete ptr;
        }
    }

    void eraseCase2(treeNode* ptr, treeNode* pptr) {

        treeNode* nptr = ptr->rightchild, * pnptr = ptr;

        while (nptr->leftchild != NULL) {
            pnptr = nptr;
            nptr = nptr->leftchild;
        }

        swap(ptr->Data, nptr->Data);

        if (childCount(nptr) == 0) {
            eraseCase0(nptr, pnptr);
        }
        else {
            eraseCase1(nptr, pnptr);
        }
    }

    void deleteInPostOrder(treeNode* ptr)
    {
        if (ptr != 0)
        {
            deleteInPostOrder(ptr->leftchild);
            deleteInPostOrder(ptr->rightchild);
            delete ptr;
        }
    }


    void printInOrder(treeNode* ptr)
    {
        if (ptr != NULL) {
            printInOrder(ptr->leftchild);
            cout << ptr->Data << " ";
            printInOrder(ptr->rightchild);
        }
    }

    void searchAndPromote(treeNode* ptr, treeNode* pptr, treeNode* gptr)
    {
        if (ptr != root)
        {
            if (ptr == pptr->leftchild)
                rr(pptr, gptr);
            else
                rl(pptr, gptr);
        }
    }

    treeNode* getroot()
    {
        return root;
    }

    int getMaxHeight(treeNode* ptr)
    {
        if (ptr == 0)
            return 0;
        else
        if (getMaxHeight(ptr->rightchild) > getMaxHeight(ptr->leftchild))
        {
            return getMaxHeight(ptr->rightchild) + 1;
        }
        else
        {
            return getMaxHeight(ptr->leftchild) + 1;
        }
    }

    bool isBalanced(treeNode* ptr)
    {
        if ((getMaxHeight(ptr->rightchild) - getMaxHeight(ptr->leftchild) <= 1) && (getMaxHeight(ptr->rightchild) - getMaxHeight(ptr->leftchild) >= -1))
        {
            if (ptr->rightchild) return isBalanced(ptr->rightchild);
            else if (ptr->leftchild) return isBalanced(ptr->leftchild);
        }
        else if (!((getMaxHeight(ptr->rightchild) - getMaxHeight(ptr->leftchild) <= 1) && (getMaxHeight(ptr->rightchild) - getMaxHeight(ptr->leftchild) >= -1)))
        {
            return 0;
        }
        return 1;
    }

    void isSubtree(treeNode* ptr1, treeNode* ptr2, bool& flag)
    {
        if (flag == true)
            if (ptr1->Data == ptr2->Data)
            {
                if ((ptr2->rightchild) && (ptr1->rightchild))isSubtree(ptr1->rightchild, ptr2->rightchild, flag);
                if ((ptr2->leftchild) && (ptr1->leftchild))isSubtree(ptr1->leftchild, ptr2->leftchild, flag);
                else if ((((!ptr1->rightchild) && (ptr2->rightchild)) || ((!ptr1->leftchild) && (ptr2->leftchild))))flag = false;
            }
            else
            {
                flag = false;
            }
    }

    void copyInOrder(treeNode* Anptr, treeNode*& ptr)
    {
        if (Anptr)
        {
            ptr = new treeNode(Anptr->Data, 0, 0);
            copyInOrder(Anptr->leftchild, ptr->leftchild);
            copyInOrder(Anptr->rightchild, ptr->rightchild);
        }
    }

    void pathSums(vector<int>& v, treeNode* ptr, int sum)
    {
        if (ptr->leftchild == 0 && ptr->rightchild == 0)
        {
            sum += ptr->Data;
            v.push_back(sum);
        }
        else
        {
            sum += ptr->Data;
            if (ptr->leftchild)
                pathSums(v, ptr->leftchild, sum);
            if (ptr->rightchild)
                pathSums(v, ptr->rightchild, sum);
        }
    }

    void trimBelowK(treeNode* ptr, int k, int i)
    {
        if (i <= k)
        {
            if (ptr->leftchild) trimBelowK(ptr->leftchild, k, i + 1);
            if (ptr->rightchild) trimBelowK(ptr->rightchild, k, i + 1);
        }
        else
        {
            deleteInPostOrder(ptr);
        }
        if (i == k)
        {
            ptr->leftchild = 0;
            ptr->rightchild = 0;
        }
    }

    void breadth(vector<int>& v, treeNode* ptr, int i)
    {
        if (ptr)
        {
            if (i >= v.size())
            {
                v.push_back(1);
            }
            else
            {
                v[i] += 1;
            }
            breadth(v, ptr->leftchild, i + 1);
            breadth(v, ptr->rightchild, i + 1);
        }
    }


    class iterator
    {
        treeNode* Curr;
        vector<treeNode*> V;
        int i;

        void copyPreOrder(treeNode* ptr)
        {
            if (ptr)
            {
                copyPreOrder(ptr->leftchild);
                V.push_back(ptr);
                copyPreOrder(ptr->rightchild);
            }
        }
    public:
        iterator()
        {
            i = 0;
            Curr = 0;
        }

        iterator(treeNode* ptr)
        {
            i = 0;
            if (ptr)
                copyPreOrder(ptr);
            V.push_back(0);
            Curr = V[0];
        }

        iterator& operator ++()
        {
            if (i < V.size())
                Curr = V[++i];
            return *this;
        }

        bool operator != (const iterator& t)
        {
            return Curr != t.Curr;
        }

        T& operator *()
        {
            return Curr->Data;
        }

        void printData()
        {
            cout << Curr->Data;
        }
        friend class bst;
    };
public:
    typedef iterator iterater;

    iterator begin()
    {
        iterater i(root);
        return i;
    }

    iterator end()
    {
        iterator i(0);
        return i;
    }

    BST(const BST& another)
    {
        root = 0;
        if (another.root)
            copyInOrder(another.root, root);
        n = another.n;
    }

    bool isBalanced()
    {
        if (root)
            return isBalanced(root);
    }

    int depth(const T& key)
    {
        int d = 0;
        treeNode* ptr = root;
        while (ptr != 0)
        {
            if (ptr->Data == key)
            {
                return d;
            }
            else if (ptr->Data > key)
            {
                ptr = ptr->leftchild;
            }
            else
            {
                ptr = ptr->rightchild;
            }
            d++;
        }
        return -1;
    }

    int height()
    {
        if (root)
        {
            return getMaxHeight(root);
        }
        return -1;
    }

    BST() {
        root = NULL;
        n = 0;
    }

    BST(T sortedData[], int n)
    {
        root = 0;
        this->n = 0;
        if (n != 0)
        {
            insertArray(sortedData, 0, n, n);
        }

    }

    bool insert(const T& key)
    {
        treeNode* ptr, * pptr;
        if (getAccess(key, ptr, pptr))
            return false;
        else {
            //ptr is null
            if (pptr == NULL) {//empty tree, because pptr==NULL
                root = new treeNode(key, NULL, NULL);
            }
            else if (key < pptr->Data) {//new node is a left child
                pptr->leftchild = new treeNode(key, NULL, NULL);
            }
            else {
                pptr->rightchild = new treeNode(key, NULL, NULL);
            }
            n++;
            return true;
        }
    }

    int size()
    {
        return n;
    }

    bool isSubtree(const BST& t)
    {
        int k = (t.root)->Data;
        bool flag = true;
        treeNode* ptr, * pptr;
        if (getAccess(k, ptr, pptr))
        {
            isSubtree(ptr, t.root, flag);
            return flag;
        }
        return false;
    }

    bool find(const T& key) {
        return getAccess(key);
    }

    bool findAndPromote(const T& key) {
        treeNode* ptr, * pptr, * gptr;
        if (getAccess(key, ptr, pptr, gptr)) {


            if (pptr != NULL) {//can't promote root
                if (pptr->rightchild == ptr) {
                    rl(pptr, gptr);
                }
                else {
                    rr(pptr, gptr);
                }
            }
            return true;
        }
        else { return false; }
    }

    bool erase(const T& key)
    {
        treeNode* ptr, * pptr;

        if (!getAccess(key, ptr, pptr))
            return false;
        else {
            //case 0: ptr has 0 children
            if (childCount(ptr) == 0) {
                //cout<<"case 0"<<endl;
                eraseCase0(ptr, pptr);
                //case 1: ptr has 1 children
            }
            else if (childCount(ptr) == 1) {
                //cout<<"case 1"<<endl;
                eraseCase1(ptr, pptr);
                //case 2: ptr has 2 children
            }
            else
            {
                //cout<<"case 2"<<endl;
                eraseCase2(ptr, pptr);
            }
            n--;
            return true;
        }
    }

    int lowestCommonAncestor(const int& key1, const int& key2)
    {
        treeNode* lptr;
        lptr = root;
        while (lptr && (lptr->Data != key1 && lptr->Data != key2))
        {
            if ((lptr->Data < key1) && (lptr->Data > key2))
                break;
            if ((lptr->Data > key1) && (lptr->Data < key2))
                break;

            if ((lptr->Data > key1) && (lptr->Data > key2))
            {
                lptr = lptr->leftchild;
            }
            else if ((lptr->Data < key1) && (lptr->Data < key2))
            {
                lptr = lptr->rightchild;
            }
        }
        if (lptr)
            return lptr->Data;
        return -1;
    }

    bool isSubset(BST& t2)
    {
        iterater i1(root);
        iterator i2(t2.root);
        for (; i2 != t2.end(); ++i1)
        {
            if (!(i1 != end()))
                return false;
            if (*i2 == *i1)
            {
                ++i2;
            }
        }
        return true;
    }

    void print()
    {
        printInOrder(root);
    }

    void printIteratively()
    {
        for (BST<int>::iterater itr = begin(); itr != end(); ++itr)
        {
            cout << *itr << " ";
        }
    }

    vector<int> pathSums()
    {
        vector<int> v;
        int sum = 0;
        pathSums(v, root, sum);
        return v;
    }

    ~BST()
    {
        treeNode* ptr = root;
        if (ptr)
        {
            deleteInPostOrder(ptr);
        }
    }

    void operator =(BST& t)
    {
        deleteInPostOrder(root);
        copyInOrder(t.root, root);
        this->n = t.size();
    }

    bool operator ==(BST& t2)
    {
        if (size() != t2.size())
        {
            return false;
        }
        else
        {
            iterater i1(begin());
            iterator i2(t2.begin());
            for (; i1 != end(); ++i1, ++i2)
            {
                if (*i1 != *i2)
                {
                    return false;
                }
            }
            return true;
        }
    }

    int breadth()
    {
        int i = 0;
        vector<int> v;
        breadth(v, root, i);
        int max = v[0];
        for (int i = 0; i < v.size(); i++)
        {
            if (v[i] > max)
            {
                max = v[i];
            }
        }
        return max;
    }


    void trimBelowK(int k)
    {
        int i = 0;
        if (root)
            trimBelowK(root, k, i);
    }

    T successor(int key)
    {
        treeNode* ptr = root;
        treeNode* pptr = 0;
        treeNode* sptr = 0;
        while (ptr != 0 && ptr->Data != key)
        {
            if (key < ptr->Data)
            {
                sptr = ptr;
                pptr = ptr;
                ptr = ptr->leftchild;
            }
            else if (key > ptr->Data)
            {
                pptr = ptr;
                ptr = ptr->rightchild;
            }
        }
        if (!ptr) return -1;
        if (ptr->Data == key && (ptr->rightchild))
        {
            ptr = ptr->rightchild;
            while (ptr->leftchild != 0)
            {
                ptr = ptr->leftchild;
            }
            return ptr->Data;
        }
        else if ((ptr->Data == key) && (pptr) && (pptr->leftchild == ptr))
        {
            return pptr->Data;
        }
        else if (ptr->Data == key && sptr && sptr->Data > ptr->Data)
        {
            return sptr->Data;
        }
        else
        {
            return -1;
        }
    }


    void searchAndPromote(int key)
    {
        treeNode* ptr = root;
        stack<treeNode*> s;
        while (ptr != 0 && ptr->Data != key)
        {
            if (key < ptr->Data)
            {
                s.push(ptr);
                ptr = ptr->leftchild;
            }
            else if (key > ptr->Data)
            {
                s.push(ptr);
                ptr = ptr->rightchild;
            }
        }
        s.push(ptr);
        treeNode* gptr, * pptr;
        if (ptr)
            while (root->Data != key)
            {
                if (s.size() >= 1)
                {
                    ptr = s.top();
                    s.pop();
                }
                else
                {
                    ptr = 0;
                }
                if (s.size() >= 1)
                {
                    pptr = s.top();
                    s.pop();
                }
                else
                {
                    pptr = 0;
                }
                if (s.size() >= 1)
                {
                    gptr = s.top();
                }
                else
                {
                    gptr = 0;
                }
                searchAndPromote(ptr, pptr, gptr);
                s.push(ptr);
            }
    }
    void printRoot()
    {
        cout << root->Data;
    }
};


int main()
{
    BST<int> tree;
    tree.insert(10);
    tree.insert(12);
    tree.insert(14);
    tree.insert(11);
    tree.insert(15);
    tree.insert(13);
    tree.insert(8);
    tree.insert(6);
    tree.insert(7);
    tree.insert(9);
    cout << "Successor of 6 in tree: ";
    cout << tree.successor(6) << endl;
    for (BST<int>::iterater itr = tree.begin(); itr != tree.end(); ++itr)
    {
        cout << *itr << " ";
    }
    cout << "Height of tree = " << tree.height() << endl;
    cout << "The depth of 13 in tree3 = " << tree.depth(15) << endl;
    cout << "Is this tree balanced : " << tree.isBalanced() << endl;
    cout << "using copy constructor  : " << endl; BST<int> tree2(tree);
    tree.insert(16);
    cout << "using = operator : " << endl;
    tree2 = tree;
    cout << "Printing tree 2 preorderly      : ";
    tree2.print();
    cout << endl;
    cout << "Printing tree 2 using iterators : ";
    tree.printIteratively();
    cout << endl;
    cout << "Print accumulative sum of each path : ";
    vector<int> v = tree.pathSums();
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
    tree.print(); cout << endl;
    tree2.print(); cout << endl;
    cout << "Is tree == tree2 : ";
    if (tree == tree2) {
        cout << "yes" << endl;
    }
    else
    {
        cout << "no" << endl;
    }
    BST<int> tree3;
    tree3.insert(14);
    tree3.insert(13);
    tree3.insert(15);
    tree3.insert(16);
    cout << "Printing tree3 : ";
    tree3.print(); cout << endl;
    cout << "Is tree3 subtree of tree : ";
    cout << tree.isSubtree(tree3);
    cout << endl;
    BST<int> tree4;
    tree4.insert(24);
    tree4.insert(13);
    tree4.insert(15);
    tree4.insert(16);
    cout << "Printing tree4 : ";
    tree4.print(); cout << endl;
    cout << "Is tree4 subtree of tree : ";
    cout << tree.isSubtree(tree4) << endl;
    BST<int> tree5;
    tree5.insert(10);
    tree5.insert(15);
    tree5.insert(6);
    cout << "Printing tree5 : ";
    tree5.print(); cout << endl;
    cout << "Is tree5 subset of tree : ";
    cout << tree.isSubset(tree5);
    cout << endl;
    cout << "Promoting 6 of tree to root : " << endl;
    tree.searchAndPromote(6);
    cout << "Now Showing root of 3 : ";
    tree.printRoot();
    cout << endl;
    cout << "Printing tree again : ";
    tree.print();
    cout << endl;
    cout << "Breadth of tree1 = ";
    cout << tree.breadth() << endl;
    cout << "calling trimbelowK  on tree of level 1 : " << endl;
    tree.trimBelowK(1);
    tree.print();
    cout << endl;
    cout << "calling LowestCommonAncestor of tree of 6 and 8 = ";
    cout << tree.lowestCommonAncestor(6, 8) << endl;

    return 0;
}
