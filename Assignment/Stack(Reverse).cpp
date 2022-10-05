#include "iostream"
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
            max_size--;
            return arr[top + 1];
        }
    }
    void display() {
        if (!isEmpty())
        {
            int temp = pop();
            display();
            cout << temp << " ";
            cout <<"====" <<max_size << "====" << endl;
            push(temp);
        }
    }

    void insertAtBottom(T item) {
        if (isEmpty()) {
            push(item);
        }
        else {
            int Top = pop();
            insertAtBottom(item);
            push(Top);
        }
    }

    void reverse() {
        if (!isEmpty()) {
            int Top = pop();
            reverse();
            insertAtBottom(Top);
        }
    }

};

int main()
{
    int size;
    cout << "enter size :";
    cin >> size;
    Stack<int> obj(size);
    int element;
    cout << "enter the element you want to insert and press -1 to stop inserting:";
    cin >> element;
    while (element != -1)
    {
        obj.push(element);
        cout << "enter the element you want to insert :";
        cin >> element;
    }
    cout << "Original Stack\n" << endl;
    obj.display();
    obj.reverse();
    cout << "\nReversed Stack\n" << endl;
    obj.display();
    cout << "===============" << endl;
    obj.pop();
    obj.display();
    cout << "===============" << endl;
    obj.pop();
    obj.display();
    cout << "===============" << endl;
    obj.pop();
    obj.display();
    cout << "===============" << endl;
    obj.pop();
    obj.display();
    cout << "===============" << endl;

    return 0;
}
