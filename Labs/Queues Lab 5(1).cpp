#include<iostream>
using namespace std;

template <class T>
class Queue
{
private:
    T*arr_que;
    int max_size;
    int size;
    int front, rear;
    int count = 0;

public:
    Queue(int s = 5)
    {
        arr_que = new T[s];
        size = 0;
        max_size = 5;
        front = -1;
        rear = 0;
    }

    bool isFull(){
        return (size == max_size);
    }

    bool isEmpty()
    {
        return (size == 0);
    }

    bool enQueue(T d)
    {
        if (!isFull())
        {
            arr_que[rear % max_size] = d;
            size++;
            rear++;
            this->count++;
            return true;
        }
        else
        {
            return false;
        }
    }

    bool deQueue()
    {
        if (!isEmpty())
        {
            cout << "After deQueue : ";
            front++;
            arr_que[front % max_size];
            size--;
            return true;
        }
        else
        {
            return false;
        }
    }

    int sizeCount()
    {
        cout << "The total elements: " <<count << endl;
        return this->count;
    }

    void frontQueue(T &d)
    {
        if (!isEmpty())
        {
            d = arr_que[front + 0];
            cout << "Front element is " << d <<endl;
        }
        else
        {
            cout << "Queue is empty " << endl;
        }
    }

    void rearqueue(T &d)
    {
        if (!isEmpty())
        {
            d = arr_que[rear - 4];
            cout << "Rear element is : " << d <<endl;
        }
        else
        {
            cout << "Queue is empty .. " <<endl;
        }

    }

    void print()
    {
        for (int i = 0; i < count; i++)
        {
            cout << arr_que[i];
        }

    }
};

int main()
{
    Queue<int> Q1;
    Q1.enQueue(2);
    Q1.enQueue(3);
    Q1.enQueue(4);
    Q1.enQueue(5);
    Q1.enQueue(6);
    cout << "Elements :  ";
    Q1.print();
    Q1.deQueue();
    Q1.print();
    Q1.isFull();
    int data;
    Q1.frontQueue(data);
    Q1.rearqueue(data);

    return 0;
}
