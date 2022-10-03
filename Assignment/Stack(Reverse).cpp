#include <iostream>
using namespace std;
template<class T>
class Stack {
public:
    T* arr;
    int max_size;
    int top;

    Stack(int s = 0) {
        arr = new T[s];
        max_size = s;
        top = -1;
    }
    int isFull() {
        return (top >= max_size-1);
    }
    int isEmpty() {
        return (top == -1);
    }
    void push(T num) {
        if (isFull()) {
            int* arr1;
            arr1 = new int[max_size];
            for (int i = 0; i < max_size; i++)
            {
                arr1[i] = arr[i];
            }
            delete[]arr;
            int newsize = max_size * 2;
            arr = new int[newsize];
            int i = 0;
            for (i = 0; i < max_size; i++)
            {
                arr[i] = arr1[i];
            }
            arr[i] = num;
            top++;
            max_size++;
        }
        else {
            arr[top + 1] = num;
            top++;
        }
    }
    int pop() {
        if (isEmpty())
            cout << "Stack is Empty!" << endl;
        else {
            top = top - 1;
            return arr[top + 1];
        }
    }
    void display() {
        if (!isEmpty())
        {
            int temp = pop();
            display();
            cout << temp << " ";
