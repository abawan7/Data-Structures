#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
#include <cassert>
using namespace std;
template<typename k, typename v>
class HeapItem
{
public:
    k key;
    v value;
    HeapItem()
    {
        key = 0;
    }
    HeapItem(k key, v value)
    {
        this->key = key;
        this->value = value;
    }
    HeapItem(const HeapItem& h)
    {
        this->key = h.key;
        this->value = h.value;
    }
    HeapItem<k, v> operator=(const HeapItem& h)
    {
        this->key = h.key;
        this->value = h.value;
        return *this;
    }
    ~HeapItem()
    {

    }
};
template<typename k, typename v>
class MinHeap
{
    HeapItem<k, v>* arr;
    int capacity, totalitems;
public:
    MinHeap()
    {
        arr = nullptr;
        capacity = 0;
        totalitems =0;
    }
    MinHeap(int c)
    {
        capacity = c;
        arr = new HeapItem<k, v>[capacity];
        totalitems = 0;
    }
    void Setter(int c)
    {
        capacity = c;
        arr = new HeapItem<k, v>[capacity];
        totalitems = 0;
    }
    
    void getmin(v& _value)
    {
        assert(totalitems >= 0);
        _value = arr->value;
    }
    bool isEmpty() const
    {
        return (totalitems == 0);
    }
    void deleteMin()
    {
        assert(totalitems >= 0);
        HeapItem<k, v>* arrtemp = arr + (totalitems - 1);
        arr->key = arrtemp->key;
        arr->value = arrtemp->value;
        if (totalitems != 0)
        {
            totalitems--;
        }
        ReheapDown(0, totalitems);
    }
    void insert(k key, v value)
    {
        HeapItem<k, v>* arrtemp = arr;
        if (totalitems == capacity)
        {
            capacity = capacity * 2;
            HeapItem<k, v>* p = new HeapItem<k, v>[capacity];
            HeapItem<k, v>* ptemp = p;
            int i;
            for (i = 0; i < totalitems; i++)
            {
                ptemp = arrtemp;
                ptemp++;
                arrtemp++;
            }
            delete[]arr;
            arr = p;
        }
        arrtemp = arr + totalitems;
        arrtemp->key = key;
        arrtemp->value = value;
        ReheapUp(0, totalitems);
        totalitems++;
    }
    void ReheapDown(int root, int bottom)
    {
        HeapItem<k, v>* parentemp = arr + root;
        int minChild, rightChild, leftChild;
        leftChild = 2 * root + 1;
        HeapItem<k, v>* lefttemp = arr + leftChild;
        rightChild = 2 * root + 2;
        HeapItem<k, v>* righttemp = arr + rightChild;
        if (leftChild <= bottom)
        {
            if (leftChild == bottom)
                minChild = leftChild;
            else
            {
                if (righttemp->key >= lefttemp->key)
                    minChild = leftChild;
                else
                    minChild = rightChild;
            }
            HeapItem<k, v>* childtemp = arr + minChild;
            if (parentemp->key > childtemp->key)
            {
                HeapItem<k, v> temp = *parentemp;
                *parentemp = *childtemp;
                *childtemp = temp;
                ReheapDown(minChild, bottom);
            }
        }
    }
    void ReheapUp(int root, int bottom)
    {
        int parent;
        if (bottom > root)
        {
            parent = (bottom - 1) / 2;
            HeapItem<k, v>* parentemp = arr + parent;
            HeapItem<k, v>* bottomtemp = arr + bottom;
            if (parentemp->key > bottomtemp->key)
            {
                HeapItem<k, v> temp = *parentemp;
                *parentemp = *bottomtemp;
                *bottomtemp = temp;
                ReheapUp(root, parent);
            }
        }
    }
    ~MinHeap()
    {
        delete[] arr;
    }
};
class student
{
    int rollNumber;
    char* name;
    float cgpa;
public:
    student()
    {
        rollNumber = 0;
        cgpa = 0.0;
        name = nullptr;
    }
    void buildStudentHeap(string fileName, MinHeap<int, student>& stdHeap)
    {
        fstream file;
        file.open(fileName, ios::in);
        if (!file)
            cout << "File does not exist";
        else
        {
            int ii = 0;
            char ch[1000];
            while (!file.eof())
            {
                file.getline(ch, 1000);
                if (ii == 0)
                {
                    int cap = 0;
                    int capacity = 0;
                    for (int j = 0; ch[j] != '\0'; j++)
                    {
                        cap = ch[j] - 48;
                        capacity = (capacity * 10) + cap;
                    }
                    stdHeap.Setter(capacity);
                    ii++;
                }
                else
                {
                    int roll = 0;
                    int j = 0;
                    rollNumber = 0;
                    for ( j = 0; ch[j] != ' '; j++)
                    {
                        roll = ch[j] - 48;
                        rollNumber = (rollNumber * 10) + roll;
                    }
                    j++;
                    int size = 0;
                    for (int i = j; ch[i] != ' '; i++)
                    {
                        size++;
                    }
                    if (name != nullptr)
                    {
                        delete[] name;
                    }
                    name = new char[size + 1];
                    int jj = 0;
                    for (; ch[j] != ' '; jj++, j++)
                    {
                        name[jj] = ch[j];
                    }
                    name[jj] = '\0';
                    j++;
                    int ppp = ch[j] - 48;
                    cgpa = ppp;
                    j = j + 2;
                    int count1 = 0;
                    float p1 = 0.0;
                    for (; ch[j] != '\0'; j++)
                    {
                        count1++;
                        ppp = ch[j] - 48;
                        p1 = (p1 * 10) + ppp;
                    }
                    int count2 = 1;
                    for (int i = 0; i < count1; i++)
                    {
                        count2 = count2 * 10;
                    }
                    p1 = p1 / count2;
                    cgpa = cgpa + p1;
                    stdHeap.insert(rollNumber, *this);
                }
            }
            file.close();
        }
    }
    student operator=(const student& s)
    {
        rollNumber = s.rollNumber;
        int size = 0;
        for (int i = 0; s.name[i] != '\0'; i++)
        {
            size++;
        }
        name = new char[size + 1];
        int i = 0;
        for (; s.name[i] != '\0'; i++)
        {
            name[i] = s.name[i];
        }
        name[i] = '\0';
        cgpa = s.cgpa;
        return *this;
    }
    friend ostream& operator<<(ostream& o, student& v1);
};
ostream& operator<<(ostream& o, student& v1)
{
    o << "Roll No.  :  " << v1.rollNumber << endl;
    o << "Name      :  " << v1.name << endl;
    o << "CGPA      :  " << v1.cgpa << endl;
    return o;
}
int main()
{
    MinHeap< int, student> stdHeap;
    student s;
    s.buildStudentHeap("students.txt", stdHeap);
    while (!stdHeap.isEmpty())
    {
        stdHeap.getmin(s);
        cout << s << endl << endl;
        stdHeap.deleteMin();
    }
    return 0;
}
